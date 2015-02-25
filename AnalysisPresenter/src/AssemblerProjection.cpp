#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/AssemblerProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContributionProjection.h"

#include "Math/QuantFuncMathCore.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TPaveStats.h"
#include "TStyle.h"

#include <assert.h>
#include <boost/bind.hpp>
#include <boost/range/join.hpp>
#include <cmath>
#include <exception>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h> 
#include <unistd.h>
#include <iomanip>
#include <stdlib.h>

#include "RutgersIAF/debug.h"

using namespace std;

ClassImp(AssemblerProjection)

AssemblerProjection::AssemblerProjection(Assembler* assembler, TString name, bool binForOverflow) : m_assembler(assembler), m_binForOverflow(binForOverflow), m_name(name), m_title(assembler->getVarName(name)), m_ranges(assembler->getRanges()) {
	std::map<TString, std::vector<PhysicsContributionProjection*>> hProjections;
	
	// Project event counts and uncertainty histograms
	auto vData = m_assembler->getContributions("data");
	auto vBackground = m_assembler->getContributions("background");
	for(auto &contribution : boost::join(vData, vBackground)) {
		if(hProjections.find(contribution->getType()) == hProjections.end()) {
			hProjections.insert(make_pair(contribution->getType(), std::vector<PhysicsContributionProjection*>()));
		}
		
		hProjections[contribution->getType()].push_back(contribution->project(name, binForOverflow));
	}
	
	// Prepare projection for output: Put projections together
	for(const auto &typeProjection : hProjections) {
		add(typeProjection, assembler->getVarExp(), assembler->getSelection());
	}
}

AssemblerProjection::AssemblerProjection() {
	/* no-op */
}

AssemblerProjection::~AssemblerProjection() {
	//delete m_canvas; // TODO this causes a segfault -- probably something to do with http://root.cern.ch/phpBB3/viewtopic.php?f=14&t=11472
	for(auto &component : m_components) {
		delete component.second.first;
		delete component.second.second;
	}
	
	return;
	for(auto &typeProjection : m_typeProjections) {
		for(auto &projection : typeProjection.second) {
			delete projection;
		}
	}
}

// Combine correlated uncertainties and assemble contributions into sorted histogram stack
void AssemblerProjection::add(std::pair<TString, std::vector<PhysicsContributionProjection*>> typeProjection, TString varexp, TString selection) {
	m_typeProjections.insert(typeProjection);
	
	// Intermediate structure for main histogram, and stack for systematic uncertainties (statistical ones are taken care of in main histogram
	std::vector<std::pair<TH1D*, double>> vh;
	THStack* hsSyst = new THStack("hsSyst", varexp + TString(" {") + selection + TString("}"));
	
	// Also, break things down by correlation class (for datacards and such)
	std::vector<TString> correlationClasses;
	std::map<TString, std::pair<THStack*, THStack*>> hsByCorrelationClass;
	for(const auto &contributionProjection : typeProjection.second) {
		TString correlationClass = contributionProjection->getPhysicsContribution()->getCorrelationClass();
		if(std::find(correlationClasses.begin(), correlationClasses.end(), correlationClass) == correlationClasses.end()) {
			correlationClasses.push_back(correlationClass);
			THStack* hs2 = new THStack((TString("hs_") + correlationClass).Data(), varexp + TString(" {") + selection + TString("}"));
			THStack* hsSyst2 = new THStack((TString("hsSyst_") + correlationClass).Data(), varexp + TString(" {") + selection + TString("}"));
			hsByCorrelationClass.insert(make_pair(correlationClass, make_pair(hs2, hsSyst2)));
		}
		
		vh.push_back(make_pair(contributionProjection->getHistogram(), contributionProjection->getHistogram()->Integral()));
		hsByCorrelationClass[correlationClass].first->Add((TH1*)contributionProjection->getHistogram()->Clone());
		
		for(const auto &uncertainty : contributionProjection->getUncertainties()) {
			// Combine uncertainties into main histograms
			TH1D* hUncertainty = (TH1D*)hsSyst->FindObject(uncertainty.first);
			if(hUncertainty) {
				for(int j = 1; j <= hUncertainty->GetNbinsX(); ++j) {
					double value = hUncertainty->GetBinContent(j);
					value = sqrt(value*value + pow(uncertainty.second->GetBinContent(j), 2));
					hUncertainty->SetBinContent(j, value);
				}
			} else {
				hsSyst->Add(uncertainty.second);
			}
			
			// Combine uncertainties into correlation class histograms
			hUncertainty = (TH1D*)hsByCorrelationClass[correlationClass].second->FindObject(uncertainty.first);
			if(hUncertainty) {
				for(int j = 1; j <= hUncertainty->GetNbinsX(); ++j) {
					double value = hUncertainty->GetBinContent(j);
					value = sqrt(value*value + pow(uncertainty.second->GetBinContent(j), 2));
					hUncertainty->SetBinContent(j, value);
				}
			} else {
				hsByCorrelationClass[correlationClass].second->Add((TH1*)uncertainty.second->Clone());
			}
		}
		
		m_projections.insert(contributionProjection);
	}
	
	// Sort by amount of contribution
	std::sort(vh.begin()
		, vh.end()
		, boost::bind(&std::pair<TH1D*, double>::second, _1) < boost::bind(&std::pair<TH1D*, double>::second, _2)
	);
	
	// Prepare content stack
	THStack* hs = new THStack("hs", varexp + TString(" {") + selection + TString("}"));
	for(const auto &contribution : vh) {
		contribution.first->SetLineWidth(0);
		hs->Add(contribution.first);
	}
	
	if(m_components.find(typeProjection.first) != m_components.end()) {
		throw std::runtime_error("overwriting projection components not supported");
	}
	m_components.insert(make_pair(typeProjection.first, make_pair(hs, hsSyst)));
	m_componentsByCorrelationClass.insert(make_pair(typeProjection.first, hsByCorrelationClass));
}

double AssemblerProjection::addStackBinInQuadrature(THStack* stack, int i) const {
	TList* hists = stack->GetHists();
	double val2 = 0;
	TIterator* iter = new TListIter(hists);
	// If hists was 0, Next() returns 0, so we're fine. This happens if the stack is empty (common use case: stack for systematic uncertainties).
	while(TH1* obj = (TH1*)iter->Next()) {
		val2 += pow(obj->GetBinContent(i), 2);
	}
	return sqrt(val2);
}

double AssemblerProjection::extractStackBin(THStack* stack, int i, TString name) const {
	if(!stack->GetHists()) {
		return 0;
	}
	TH1D* hUncertainty = (TH1D*)stack->GetHists()->FindObject(name);
	return hUncertainty ? hUncertainty->GetBinContent(i) : 0;
}

double AssemblerProjection::getBin(TString type, int i) const {
	assert(has(type));
	TObjArray* stack = m_components.find(type)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinContent(i) : 0;
}

double AssemblerProjection::getBin(TString type, int i, TString correlationClass) const {
	assert(has(type, correlationClass));
	TObjArray* stack = m_componentsByCorrelationClass.find(type)->second.find(correlationClass)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinContent(i) : 0;
}

double AssemblerProjection::getBinStat(TString type, int i) const {
	assert(has(type));
	TObjArray* stack = m_components.find(type)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinError(i) : 0;
}

double AssemblerProjection::getBinStat(TString type, int i, TString correlationClass) const {
	assert(has(type, correlationClass));
	TObjArray* stack = m_componentsByCorrelationClass.find(type)->second.find(correlationClass)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinError(i) : 0;
}

double AssemblerProjection::getBinSyst(TString type, int i) const {
	assert(has(type));
	return addStackBinInQuadrature(m_components.find(type)->second.second, i);
}

double AssemblerProjection::getBinSyst(TString type, int i, TString name) const {
	assert(has(type));
	return extractStackBin(m_components.find(type)->second.second, i, name);
}

double AssemblerProjection::getBinSyst(TString type, int i, TString name, TString correlationClass) const {
	assert(has(type, correlationClass));
	return extractStackBin(m_componentsByCorrelationClass.find(type)->second.find(correlationClass)->second.second, i, name);
}

std::vector<TString> AssemblerProjection::getCorrelationClasses(TString type) {
	assert(has(type));
	std::vector<TString> correlationClasses;
	for(auto &componentByCorrelationClass: m_componentsByCorrelationClass.find(type)->second) {
		correlationClasses.push_back(componentByCorrelationClass.first);
	}
	return correlationClasses;
}

TH1* AssemblerProjection::getHistogram(TString type) const {
	assert(has(type));
	TObjArray* stack = m_components.find(type)->second.first->GetStack();
	return stack ? (TH1*)((TH1*)stack->Last())->Clone() : 0;
}

TH1* AssemblerProjection::getHistogram(TString type, TString correlationClass) const {
	assert(has(type, correlationClass));
	TObjArray* stack = m_componentsByCorrelationClass.find(type)->second.find(correlationClass)->second.first->GetStack();
	return stack ? (TH1*)((TH1*)stack->Last())->Clone() : 0;
}

std::set<PhysicsContribution::metadata_t> AssemblerProjection::getMeta(TString type) const {
	if(type != "data" || m_typeProjections.at(type).size() > 1) {
		throw std::runtime_error("meta information currently only supported for one set of data");
	}
	
	auto ranges = m_assembler->getRanges();
	m_assembler->setRanges(m_ranges);
	auto meta = m_typeProjections.at(type)[0]->getPhysicsContribution()->getMeta();
	m_assembler->setRanges(ranges);
	
	return meta;
}

std::vector<std::pair<int, int>> AssemblerProjection::getRanges() const {
	return m_ranges;
}

std::set<TString> AssemblerProjection::getUncertainties() const {
	std::set<TString> uncertainties;
	for(auto &projection : m_projections) {
		for(auto &projectionUncertainties : projection->getUncertainties()) {
			uncertainties.insert(projectionUncertainties.first);
		}
	}
	return uncertainties;
}

bool AssemblerProjection::has(TString type) const {
	return (m_components.find(type) != m_components.end() && m_components.find(type)->second.first->GetHists());
}

bool AssemblerProjection::has(TString type, TString correlationClass) const {
	return (
		m_componentsByCorrelationClass.find(type) != m_componentsByCorrelationClass.end()
		&& m_componentsByCorrelationClass.find(type)->second.find(correlationClass) != m_componentsByCorrelationClass.find(type)->second.end()
	);
}

bool AssemblerProjection::hasOverflowIncluded() const {
	return m_binForOverflow;
}

bool AssemblerProjection::isDistribution() const {
	return (m_name != "_");
}

TCanvas* AssemblerProjection::plot(bool log, TF1* f1, double xminFit, double xmaxFit) {
	bool hasBackground = has("background");
	m_canvas = new TCanvas("c1", "c1", 700, hasBackground ? 700 : 490);
	
	TPad *pad1 = new TPad("pad1", "pad1", 0, hasBackground ? 0.3 : 0, 1, 1);
	if(hasBackground) {
		pad1->SetBottomMargin(0.025);
	}
	pad1->Draw();
	pad1->cd();
	pad1->SetTicks(1, 1);
	
	TString title = (isDistribution() && m_title != m_name)
		? TString::Format("%s (%s)", m_title.Data(), m_name.Data())
		: m_title;
	
	// TODO Not cloning causes segfault ...
	TH1* hData = (TH1*)m_components.find("data")->second.first->GetStack()->Last()->Clone();
	if(hasOverflowIncluded()) {
		// Set overflow bin content to make it show up in statistics box
		auto nEntries = hData->GetEntries();
		hData->SetBinContent(hData->GetNbinsX() + 1, hData->GetBinContent(hData->GetNbinsX()));
		hData->SetEntries(nEntries);
	}
	hData->SetLineWidth(1);
	hData->SetMarkerStyle(9);
	
	TH1* hSignal = 0;
	if(has("signal")) {
		hSignal = (TH1*)m_components.find("signal")->second.first->GetStack()->Last()->Clone();
		for(int i = 0; i < hSignal->GetNbinsX() + 1; ++i) {
			double error2 = pow(hSignal->GetBinError(i), 2) + pow(getBinSyst("signal", i), 2);
			hSignal->SetBinError(i, sqrt(error2));
		}
	}
	
	TH1* hBackground = 0;
	TH1* hBackgroundErr = 0;
	TH1* hRatio = 0;
	TH1* hRatioBkg = 0;
	if(hasBackground) {
		hBackground = (TH1*)m_components.find("background")->second.first->GetStack()->Last()->Clone("background");
		for(int i = 0; i < hBackground->GetNbinsX() + 1; ++i) {
			// Add up stat. error in the background stack (ideally 0 with infinite MC) and the systematic uncertainties
			// Those are together to "comprehensive systematic uncertainty"
			double error2 = pow(hBackground->GetBinError(i), 2) + pow(getBinSyst("background", i), 2);
			hBackground->SetBinError(i, sqrt(error2));
		}
		
		hBackgroundErr = (TH1*)hBackground->Clone("backgroundErr");
		hBackgroundErr->Reset();
		const double alpha = 1 - 0.6827;
		for(int i = 0; i < hBackgroundErr->GetNbinsX() + 1; ++i) {
			double n = hBackground->GetBinContent(i);
			double lo = (n == 0) ? 0 : ROOT::Math::gamma_quantile(alpha/2, n, 1.);
			double hi = ROOT::Math::gamma_quantile_c(alpha/2, n+1, 1);
			// Now, combine Poisson fluctuation range with "comprehensive systematic uncertainty" from above
			lo = sqrt(pow(n - lo, 2) + pow(hBackground->GetBinError(i), 2));
			hi = sqrt(pow(hi - n, 2) + pow(hBackground->GetBinError(i), 2));
			lo = n - lo;
			hi = n + hi;
			n = (lo + hi) / 2;
			hBackgroundErr->SetBinContent(i, n);
			hBackgroundErr->SetBinError(i, (hi - lo) / 2);
		}
		
		hRatio = (TH1*)hData->Clone("hRatio");
		hRatioBkg = (TH1*)hBackgroundErr->Clone("hRatioBkg");
		
		if(hSignal) {
			hData->SetMaximum(max(1., max(hData->GetMaximum(), max(hBackground->GetMaximum(), hSignal->GetMaximum()))));
		} else {
			hData->SetMaximum(max(1., max(hData->GetMaximum(), hBackground->GetMaximum())));
		}
	}
	
	hData->SetMaximum(1.5 * hData->GetMaximum());
	if(log) {
		hData->SetMinimum(hasBackground ? min(0.1, 0.5 * hBackground->GetMinimum(0)) : 0.1);
		// Make sure the range spans at least one order of magnitude
		if(hData->GetMinimum() > hData->GetMaximum() / 15) {
			hData->SetMinimum(hData->GetMaximum() / 15);
		}
	} else {
		hData->SetMinimum(0);
	}
	hData->GetXaxis()->SetTitle(title);
	hData->SetLineColor(kRed);
	
	if(hasBackground) {
		hData->GetXaxis()->SetLabelFont(43);
		hData->GetXaxis()->SetLabelSize(0);
	}
	hData->GetYaxis()->SetLabelFont(43);
	hData->GetYaxis()->SetLabelSize(16);
	
	hData->Clone("dummy")->Draw("EP"); // use dummy name to allow unique name in TCanvas for the actual data histogram
	
	if(hasBackground) {
		((THStack*)m_components.find("background")->second.first->Clone())->Draw("HIST SAME"); // TODO crashes when not cloning
		hBackground->SetFillColor(kRed);
		hBackground->SetFillStyle(3002);
		hBackground->Draw("E2 SAME");
		hBackgroundErr->SetFillColor(kBlack);
		hBackgroundErr->SetFillStyle(3013);
		hBackgroundErr->SetMarkerStyle(20);
		hBackgroundErr->SetMarkerSize(0);
		hBackgroundErr->Draw("SAME E2");
		if(hSignal) {
			hSignal->SetMarkerColor(kWhite);
			hSignal->SetMarkerStyle(21);
			hSignal->SetFillColor(kPink);
			hSignal->SetFillStyle(3008);
			hSignal->Draw("SAME E2 P");
		}
	}
	
	hData->Clone("dummy")->Draw("AXIS SAME"); // Documentation says that statistics box is not drawn with SAME. However, it is for this specific Draw(), and it has the title "dummy". We don't want that. So, ...
	hData->Draw("EP SAMES"); // ... let's request a statistics box for the actual data with SAMES. (Here, SAME doesn't draw the box. I propose a CERN experiment to study and develop a theory of the mysteries of ROOT.)
	gStyle->SetOptStat(111111);
	pad1->SetLogy(log);
	
	if(hasBackground) {
		double ratio = hData->Integral() / hBackground->Integral();
		
		TLegend* legend = new TLegend(0.84,0.15,0.98,0.55);
		legend->SetHeader(TString::Format("%.1f (r = %.3f)", hBackground->Integral(), ratio).Data());
		TList* hists = m_components.find("background")->second.first->GetHists();
		TIterator* iter = new TListIter(hists, false);
		while(TH1* obj = (TH1*)iter->Next()) {
			legend->AddEntry(obj, TString::Format("%s [%.1f]", obj->GetTitle(), obj->Integral()).Data());
		}
		delete iter;
		legend->Draw();
		
		m_canvas->cd();
		TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
		pad2->SetTopMargin(0.025);
		pad2->Draw();
		pad2->cd();
		
		TLine* line1 = new TLine(hData->GetBinLowEdge(1), 1, hData->GetBinLowEdge(hData->GetNbinsX()+1), 1);
		TLine* line2 = new TLine(hData->GetBinLowEdge(1), ratio, hData->GetBinLowEdge(hData->GetNbinsX()+1), ratio);
		line2->SetLineColor(kRed);
		line2->SetLineWidth(2);
		hRatio->GetXaxis()->SetTitle(title);
		hRatio->SetTitle("");
		for(int i = 0; i < hRatio->GetXaxis()->GetNbins() + 1; ++i) {
			hRatio->SetBinContent(i, hRatio->GetBinContent(i) / hBackground->GetBinContent(i));
			hRatio->SetBinError(i, hRatio->GetBinError(i) / hBackground->GetBinContent(i));
		}
		if(isDistribution()) {
			hRatio->GetXaxis()->SetLabelFont(43);
			hRatio->GetXaxis()->SetLabelSize(16);
		} else {
			hRatio->GetXaxis()->SetLabelFont(43);
			hRatio->GetXaxis()->SetLabelSize(0);
		}
		hRatio->GetYaxis()->SetLabelFont(43);
		hRatio->GetYaxis()->SetLabelSize(16);
		hRatio->GetYaxis()->SetTitle("data/background");
		hRatio->SetFillColor(kBlack);
		hRatio->SetFillStyle(3001);
		hRatio->SetMinimum(0);
		if(hRatio->GetMaximum() > 1) {
			hRatio->SetMaximum(3);
		} else if(hRatio->GetMaximum() < 0.5) {
			hRatio->SetMaximum(0.5);
		}
		hRatio->GetYaxis()->SetRangeUser(hRatio->GetMinimum(0), hRatio->GetMaximum());
		hRatio->Draw("AXIS");
		double hRatioBkgErrorSum = 0;
		for(int i = 0; i < hRatioBkg->GetXaxis()->GetNbins() + 1; ++i) {
			double yield = hBackground->GetBinContent(i);
			if(yield == 0) {
				continue;
			}
			hRatioBkg->SetBinContent(i, hRatioBkg->GetBinContent(i) / yield);
			hRatioBkg->SetBinError(i, hRatioBkg->GetBinError(i) / yield);
			
			if(hRatioBkg->GetBinContent(i) > hRatio->GetMaximum()) {
				double lo = hRatioBkg->GetBinContent(i) - hRatioBkg->GetBinError(i);
				hRatioBkg->SetBinContent(i, hRatio->GetMaximum());
				hRatioBkg->SetBinError(i, max(hRatioBkg->GetBinContent(i) - lo, 0.0));
			}
			hRatioBkgErrorSum += hRatioBkg->GetBinError(i);
		}
		// If all the uncertiancies in hRatioBkg are 0 (this happens when the error bars are all out of y-axis range), ROOT would draw error bars filling all of the histogram frame. We don't want to draw anything in this case.
		if(hRatioBkgErrorSum > 0) {
			hRatioBkg->SetFillColor(kBlack);
			hRatioBkg->SetFillStyle(3002);
			hRatioBkg->SetMarkerStyle(20);
			hRatioBkg->SetMarkerSize(0);
			line1->Draw();
			line2->Draw();
			hRatioBkg->Draw("E2 SAME");
		}
		gStyle->SetOptFit(1111);
		((TPaveStats*)hRatio->GetListOfFunctions()->FindObject("stats"))->SetOptStat(0);
		if(f1) {
			hRatio->Fit(f1, "", "SAME AXIS", xminFit, xmaxFit);
		}
		hRatio->Draw("SAME");
	}
	
	return m_canvas;
}

void AssemblerProjection::print() const {
	double sumData = 0;
	double sumBackground = 0;
	double sumBackgroundStat2 = 0;
	double sumBackgroundSyst = 0;
	double sumSignal = 0;
	double sumSignalStat2 = 0;
	double sumSignalSyst = 0;
	
	TH1* hData = (TH1*)m_components.find("data")->second.first->GetStack()->Last()->Clone();
	//cout << "data entries: " << hData->GetEntries() << endl;
	//cout << "data integral: " << hData->Integral() << endl;
	//cout << "data integral w/ overflow: " << hData->Integral(0, hData->GetNbinsX() + 1) << endl;
	cout << ((TH1*)m_components.find("data")->second.first->GetStack()->Last())->GetTitle() << endl;
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
		double lo = hData->GetXaxis()->GetBinLowEdge(i);
		double hi = hData->GetXaxis()->GetBinUpEdge(i);
		
		if(isDistribution()) {
			if(i < hData->GetNbinsX() || !hasOverflowIncluded()) {
				cout << m_name << " " << lo << "-" << hi;
			} else {
				cout << m_name << " " << lo << "-" << "inf";
			}
		}
		
		double contentData = getBin("data", i);
		sumData += contentData;
		
		if(isDistribution()) {
			printf("	%.0f", contentData);
		}
		
		if(has("background")) {
			double contentBackground = getBin("background", i);
			double contentBackgroundStat = getBinStat("background", i);
			double contentBackgroundSyst = getBinSyst("background", i);
			sumBackground += contentBackground;
			sumBackgroundStat2 += contentBackgroundStat*contentBackgroundStat;
			sumBackgroundSyst += contentBackgroundSyst;
			
			// TODO Replace by Poisson error
			if(isDistribution()) {
				printf(" : %.2f ± %.2f ± %.2f ± %.2f", contentBackground, sqrt(contentBackground), contentBackgroundStat, contentBackgroundSyst);
			}
		}
		
		if(has("signal")) {
			double contentSignal = getBin("signal", i);
			double contentSignalStat = getBinStat("signal", i);
			double contentSignalSyst = getBinSyst("signal", i);
			sumSignal += contentSignal;
			sumSignalStat2 += contentSignalStat*contentSignalStat;
			sumSignalSyst += contentSignalSyst;
			
			if(isDistribution()) {
				printf(" : %.2f ± %.2f ± %.2f", contentSignal, contentSignalStat, contentSignalSyst);
			}
		}
		
		if(isDistribution()) {
			cout << endl;
		}
	}
	if(isDistribution()) {
		printf("Sum:		%.0f", sumData);
	} else {
		printf("%s:	%.0f", m_title.Data(), sumData);
	}
	if(has("background")) {
		// TODO Replace by Poisson error
		printf(" : %.2f ± %.2f ± %.2f ± %.2f", sumBackground, sqrt(sumBackground), sqrt(sumBackgroundStat2), sumBackgroundSyst);
	}
	if(has("signal")) {
		printf(" : %.2f ± %.2f ± %.2f", sumSignal, sqrt(sumSignalStat2), sumSignalSyst);
	}
	cout << endl;
}

void AssemblerProjection::printMeta(TString type) const {
	for(auto &meta : getMeta(type)) {
		cout << meta.event << " " << meta.run << " " << meta.lumi << " " << meta.fakeIncarnation << endl;
	}
}

void AssemblerProjection::datacard(TString datacardName, bool isData, double statFactor, double systFactor) {

	std::cout << "Creating datacard..." << std::endl;
	
	TH1* hData = (TH1*)m_components.find("data")->second.first->GetStack()->Last()->Clone();
	int bins = hData->GetNbinsX();
	std::vector<TString> correlationClassesSignal;
	correlationClassesSignal = getCorrelationClasses("signal");
	int NumberCorClassesSignal = correlationClassesSignal.size();
	std::vector<TString> correlationClassesBckgrd;
	correlationClassesBckgrd = getCorrelationClasses("background");
	int NumberCorClassesBackgrd = correlationClassesBckgrd.size();

	
	//Create datacard
	ofstream datacard;
	TString basicName = "/datacard_";
	TString endName = ".txt";
	TString completeName = "";
	TString directory = "";
	char buffer[1024]; 
	if(getcwd(buffer, 1024) == NULL ) 
		perror("***Directory Error***");  
	directory = buffer;
	completeName = directory + basicName + m_name + "_" + datacardName + endName;
	datacard.open(completeName);	
	datacard << std::fixed << std::setprecision(0);
	datacard << "#Datacard Version 0.1" << '\n' << "#Dec. 2014" << '\n' << '\n';
	datacard << "imax " << bins << " number of channels" << '\n' << "jmax " << NumberCorClassesBackgrd+NumberCorClassesSignal - 1 << " number of background" << '\n' << "kmax " << getUncertainties().size() + hData->GetNbinsX()*(NumberCorClassesBackgrd+NumberCorClassesSignal) << " number nuisance parameters" << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	datacard << "Observation";
	
	//Calculate values for datacard
	if (isData) {
	
		for (int i = 1; i <= hData->GetNbinsX(); ++i) {
		
			double contentData = getBin("data", i);
			datacard << '\t' << contentData;
		}
	}
	else {
		for(int i = 1; i <= hData->GetNbinsX(); ++i) {	
	
			double contentData = getBin("background", i);
			datacard << '\t' << contentData;
		}
	}
	datacard << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	datacard << "bin";
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {	
	
		for (int j = 0; j < (NumberCorClassesSignal + NumberCorClassesBackgrd); j++) {
		
			double lo = hData->GetXaxis()->GetBinLowEdge(i);
			double hi = hData->GetXaxis()->GetBinUpEdge(i);
		
			if(i < hData->GetNbinsX() || !hasOverflowIncluded()) {
				datacard << '\t' << m_name << lo << "_" << hi;
			} else {
				datacard << '\t' << m_name << lo << "_" << "inf";
			}
		}
	}
	datacard << std::fixed << std::setprecision(3);
	datacard << '\n';
	datacard << "process";
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {	
	
		for (int j = 0; j < NumberCorClassesSignal; j++) {
		
			if(correlationClassesSignal[j]=="") {
				datacard << '\t' << "remain_signal";
			}
			else {
				datacard << '\t' << "signal_" << correlationClassesSignal[j];
			}
		}
		
		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			if(correlationClassesBckgrd[j]=="") {
				datacard << '\t' << "remain_bckgrd";
			}
			else {
				datacard << '\t' << "bckgrd_" << correlationClassesBckgrd[j];
			}
		}
			
	}
	datacard << '\n';
	datacard << "process";
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {	
	
		for (int j = 0; j < NumberCorClassesSignal; j++) {
		
			datacard << '\t' << (NumberCorClassesSignal - j)*(-1)+1;
		}
		
		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			datacard << '\t' << j + 1;
		}
		
	}
	datacard << '\n';
	datacard << "rate";
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
	
		if(has("signal")) {
		
			for (int j = 0; j < NumberCorClassesSignal; j++) {
			
				double contentSignal = getBin("signal", i, correlationClassesSignal[j]);	
				datacard << '\t' << contentSignal;
			}
		}
		else {
			perror("***Error: No Signal***");
		}
		
		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			double contentBackground = getBin("background", i, correlationClassesBckgrd[j]);
			datacard << '\t' << contentBackground;
		}
	}
	datacard << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	
	for (auto &uncertainty : getUncertainties()) {
	
		datacard << uncertainty << "  lnN";
		
		for(int i = 1; i <= hData->GetNbinsX(); ++i) {
		
			if(has("signal")) {
			
				for (int j = 0; j < NumberCorClassesSignal; j++) {
				
					double contentSignalSyst = getBinSyst("signal", i, uncertainty, correlationClassesSignal[j]);		
					double contentSignal = getBin("signal", i, correlationClassesSignal[j]);	
					double ratio = systFactor * contentSignalSyst/contentSignal;
					if (contentSignal == 0) {ratio = 0.05;}
					datacard << '\t' << 1 + ratio;
				}
			}
			else {
				perror("***Error: No Signal -> No variance***");
			}

			for (int j = 0; j < NumberCorClassesBackgrd; j++) {
			
				double contentBackgroundSyst = getBinSyst("background", i, uncertainty, correlationClassesBckgrd[j]);		
				double contentBackground = getBin("background", i, correlationClassesBckgrd[j]);	
				double ratio = systFactor * contentBackgroundSyst/contentBackground;
				if (contentBackground == 0) {ratio = 0.05;}
				datacard << '\t' << 1 + ratio;
			}
		}
		datacard << '\n';
	}
		
	int NumberBins = (NumberCorClassesBackgrd + NumberCorClassesSignal)*(hData->GetNbinsX());
	double StatUncertainty[NumberBins][NumberBins];
	
	for (int n = 0; n < NumberBins; n++) {
	
		for (int m = 0; m < NumberBins; m++) {
		
			StatUncertainty[n][m] = 1;
		}
	}
	
	int LoopIndex = 0;
	
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
	
		if(has("signal")) {
		
			for (int j = 0; j < NumberCorClassesSignal; j++) {
			
				double contentSignalStat = getBinStat("signal", i, correlationClassesSignal[j]);		
				double contentSignal = getBin("signal", i, correlationClassesSignal[j]);	
				double ratio = statFactor * contentSignalStat/contentSignal;
				if (contentSignal == 0) {ratio = 0.05;}
				StatUncertainty[LoopIndex][LoopIndex] += ratio;
				LoopIndex++;
			}
		}
		else {
			perror("***Error: No Signal -> No variance***");
		}
		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			double contentBackgroundStat = getBinStat("background", i, correlationClassesBckgrd[j]);		
			double contentBackground = getBin("background", i, correlationClassesBckgrd[j]);	
			double ratio = statFactor * contentBackgroundStat/contentBackground;
			if (contentBackground == 0) {ratio = 0.05;}
			StatUncertainty[LoopIndex][LoopIndex] += ratio;
			LoopIndex++;
		}
	}
	
	for (int n = 0; n < NumberBins; n++) {
	
		datacard << "Stat" << n + 1 << "  lnN";
	
		for (int m = 0; m < NumberBins; m++) {
		
			datacard << '\t' << StatUncertainty[n][m];
		}
		
		datacard << '\n';
	}
	
	datacard.close();
}
