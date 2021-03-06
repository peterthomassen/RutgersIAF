#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/AssemblerProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/BaseBundleProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "Math/QuantFuncMathCore.h"
#include "TH2.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TPaveStats.h"
#include "TStyle.h"

#include <assert.h>
#include <boost/algorithm/string/join.hpp>
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

AssemblerProjection::AssemblerProjection(Assembler* assembler, std::vector<std::string> varNames, bool binForOverflow) : m_assembler(assembler), m_binForOverflow(binForOverflow), m_ranges(assembler->getRanges()), m_varNames(varNames) {
	m_name = boost::algorithm::join(m_varNames, ":");
	
	// Somehow putting all of this inline in the for loop doesn't work
	auto vData = m_assembler->getPhysicsContributions("data");
	auto vBackground = m_assembler->getPhysicsContributions("background");
	auto vSignal = m_assembler->getPhysicsContributions("signal");
	auto contributionsModel = boost::join(vBackground, vSignal);
	
	// Project event counts and uncertainty histograms
	for(auto &contribution : boost::join(vData, contributionsModel)) {
		if(m_typeProjections.find(contribution->getType()) == m_typeProjections.end()) {
			m_typeProjections.insert(make_pair(contribution->getType(), std::vector<BaseBundleProjection*>()));
		}
		
		m_typeProjections[contribution->getType()].push_back(contribution->project(m_varNames, binForOverflow));
	}
	
	prepareStacks();
}

AssemblerProjection::AssemblerProjection(const AssemblerProjection* parent, Bundle* bundle, TString missingName) : m_assembler(parent->m_assembler), m_binForOverflow(parent->m_binForOverflow), m_bundle(bundle), m_parent(parent), m_ranges(parent->m_ranges), m_name(parent->m_name), m_varNames(parent->m_varNames) {
	auto ranges = m_assembler->getRanges();
	m_assembler->setRanges(m_ranges);
	
	for(auto &parentTypeProjection : m_parent->m_typeProjections) {
		TString type = parentTypeProjection.first;
		
		if(bundle->getType() != type) {
			m_typeProjections[type] = m_parent->m_typeProjections.at(type);
			continue;
		
		}
		m_typeProjections.insert(make_pair(type, std::vector<BaseBundleProjection*>()));
		
		std::set<const PhysicsContribution*> contributions;
		for(auto &component : bundle->getComponents()) {
			BaseBundleProjection* projection = component->project(m_varNames, m_binForOverflow);
			m_typeProjections[type].push_back(projection);
			
			size_t oldSize = contributions.size();
			// Doing the next two lines in one line (without extra projectionContributions) gives infinite loop
			std::set<const PhysicsContribution*> projectionContributions = projection->getPhysicsContributions();
			contributions.insert(projectionContributions.begin(), projectionContributions.end());
			assert(contributions.size() == oldSize + projectionContributions.size());
		}
		
		Bundle* missing = new Bundle(type, missingName);
		for(auto &contribution : m_assembler->getPhysicsContributions(type)) {
			if(contributions.find(contribution) == contributions.end()) {
				if(missingName == "") {
					auto projection = contribution->project(m_varNames, m_binForOverflow);
					m_typeProjections[type].push_back(projection);
					
					size_t oldSize = contributions.size();
					// Doing the next two lines in one line (without extra projectionContributions) gives infinite loop
					std::set<const PhysicsContribution*> projectionContributions = projection->getPhysicsContributions();
					contributions.insert(projectionContributions.begin(), projectionContributions.end());
					assert(contributions.size() == oldSize + projectionContributions.size());
				} else {
					missing->addComponent(contribution);
				}
			}
		}
		if(missing->getComponents().size() > 0) {
			auto projection = missing->project(m_varNames, m_binForOverflow);
			m_typeProjections[type].push_back(projection);
			
			size_t oldSize = contributions.size();
			// Doing the next two lines in one line (without extra projectionContributions) gives infinite loop
			std::set<const PhysicsContribution*> projectionContributions = projection->getPhysicsContributions();
			contributions.insert(projectionContributions.begin(), projectionContributions.end());
			assert(contributions.size() == oldSize + projectionContributions.size());
		}
	}
	
	m_assembler->setRanges(ranges);
	
	prepareStacks();
}

AssemblerProjection::AssemblerProjection() {
	/* no-op */
}

AssemblerProjection::~AssemblerProjection() {
	//delete m_canvas; // TODO doing this causes a segfault -- probably something to do with http://root.cern.ch/phpBB3/viewtopic.php?f=14&t=11472
	for(auto &component : m_stacks) {
		delete component.second.first;
		delete component.second.second;
	}
	
	for(auto &typeProjection : m_typeProjections) {
		for(auto &projection : typeProjection.second) {
			delete projection;
		}
	}
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

AssemblerProjection* AssemblerProjection::bundle(Bundle* bundle, TString missingName) {
	return bundle ? new AssemblerProjection(this, bundle, missingName) : this;
}

double AssemblerProjection::extractStackBin(THStack* stack, int i, TString name) const {
	if(!stack->GetHists()) {
		return 0;
	}
	TH1* hUncertainty = (TH1*)stack->GetHists()->FindObject(name);
	return hUncertainty ? hUncertainty->GetBinContent(i) : 0;
}

double AssemblerProjection::getBin(TString type, int i) const {
	assert(has(type));
	TObjArray* stack = m_stacks.find(type)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinContent(i) : 0;
}

double AssemblerProjection::getBin(TString type, int i, TString bundleName) const {
	assert(has(type, bundleName));
	TObjArray* stack = m_bundles.find(type)->second.find(bundleName)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinContent(i) : 0;
}

double AssemblerProjection::getBinStat(TString type, int i) const {
	assert(has(type));
	TObjArray* stack = m_stacks.find(type)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinError(i) : 0;
}

double AssemblerProjection::getBinStat(TString type, int i, TString bundleName) const {
	assert(has(type, bundleName));
	TObjArray* stack = m_bundles.find(type)->second.find(bundleName)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinError(i) : 0;
}

double AssemblerProjection::getBinSyst(TString type, int i) const {
	assert(has(type));
	return addStackBinInQuadrature(m_stacks.find(type)->second.second, i);
}

double AssemblerProjection::getBinSyst(TString type, int i, TString name) const {
	assert(has(type));
	return extractStackBin(m_stacks.find(type)->second.second, i, name);
}

double AssemblerProjection::getBinSyst(TString type, int i, TString name, TString bundleName) const {
	assert(has(type, bundleName));
	return extractStackBin(m_bundles.find(type)->second.find(bundleName)->second.second, i, name);
}

std::vector<TString> AssemblerProjection::getBundleNames(TString type) const {
	assert(has(type));
	std::vector<TString> bundleNames;
	for(auto &bundle : m_bundles.find(type)->second) {
		bundleNames.push_back(bundle.first);
	}
	return bundleNames;
}

int AssemblerProjection::getDimensionality() const {
	return m_varNames.size();
}

TH1* AssemblerProjection::getHistogram(TString type) const {
	assert(has(type));
	TObjArray* stack = m_stacks.find(type)->second.first->GetStack();
	return stack ? (TH1*)((TH1*)stack->Last())->Clone() : 0;
}

std::vector<TH1*> AssemblerProjection::getHistograms(TString type) const {
	std::vector<TH1*> v;
	auto it = m_bundles.find(type);
	if(it != m_bundles.end()) {
		for(auto const &bundle : it->second) {
			TH1* h = (TH1*)bundle.second.first->GetStack()->Last()->Clone();
			for(int i = 0; i < h->GetNcells(); ++i) {
				double error2 = pow(h->GetBinError(i), 2);
				// Add up systematics for this bundle only
				for(auto const &uncertaintyName : getUncertaintyNames()) {
					error2 += pow(getBinSyst(type, i, uncertaintyName, bundle.first), 2);
				}
				h->SetBinError(i, sqrt(error2));
			}
			v.push_back(h);
		}
	}
	return v;
}

std::set<PhysicsContribution::metadata_t> AssemblerProjection::getMeta(TString type) const {
	if(type != "data") {
		throw std::runtime_error("meta information currently only supported for data");
	}
	
	std::set<PhysicsContribution::metadata_t> s;
	unsigned int nDuplicates = 0;
	
	auto ranges = m_assembler->getRanges();
	m_assembler->setRanges(m_ranges);
	
	for(auto &typeProjection : m_typeProjections.at(type)) {
		for(auto &contribution : typeProjection->getPhysicsContributions()) {
			for(auto &metadata : contribution->getMeta()) {
				auto ins = s.insert(metadata);
				if(!ins.second) {
					if(nDuplicates < 10) {
						cout << "Notice: duplicate entry in " << contribution->getName() << ": " << metadata.event << " " << metadata.run << " " << metadata.lumi << " " << metadata.fakeIncarnation << endl;
					}
					++nDuplicates;
				}
			}
		}
	}
	
	m_assembler->setRanges(ranges);
	
	if(nDuplicates > 0) {
		cout << "Notice: " << nDuplicates << " duplicate entries in (showing no more than 10)" << endl;
	}
	
	return s;
}

double AssemblerProjection::getMoment(TH1* h, int k, bool center) const {
	assert(getDimensionality() == 1);
	double moment = 0;
	for(int i = 1; i <= h->GetNbinsX(); ++i) {
		double idx = center
			? ((h->GetXaxis()->GetBinLowEdge(i) + h->GetXaxis()->GetBinUpEdge(i)) / 2)
			: h->GetXaxis()->GetBinLowEdge(i);
		moment += pow(idx, k) * h->GetBinContent(i);
	}
	return moment;
}

double AssemblerProjection::getMoment(TString type, int k, bool center) const {
	assert(getDimensionality() == 1);
	assert(has(type));
	TObjArray* stack = m_stacks.find(type)->second.first->GetStack();
	if(!stack) {
		return 0;
	}
	TH1* h = (TH1*)stack->Last();
	if(hasOverflowIncluded() && h->GetBinContent(h->GetNbinsX() + 1) != 0) {
		throw std::runtime_error("can't compute moment when overflow bin is not empty");
	}
	return getMoment(h, k, center);
}

std::vector<std::pair<int, int>> AssemblerProjection::getRanges() const {
	return m_ranges;
}

std::set<TString> AssemblerProjection::getUncertaintyNames() const {
	std::set<TString> uncertaintyNames;
	for(auto &typeProjection : m_typeProjections) {
		for(auto &projection : typeProjection.second) {
			for(auto &projectionUncertainties : projection->getUncertainties()) {
				uncertaintyNames.insert(projectionUncertainties.first);
			}
		}
	}
	return uncertaintyNames;
}

std::vector<string> AssemblerProjection::getVarNames() const {
	return m_varNames;
}

bool AssemblerProjection::has(TString type) const {
	return (m_stacks.find(type) != m_stacks.end() && m_stacks.find(type)->second.first->GetHists());
}

bool AssemblerProjection::has(TString type, TString bundleName) const {
	return (
		m_bundles.find(type) != m_bundles.end()
		&& m_bundles.find(type)->second.find(bundleName) != m_bundles.find(type)->second.end()
	);
}

bool AssemblerProjection::hasOverflowIncluded() const {
	return m_binForOverflow;
}

bool AssemblerProjection::isDistribution() const {
	return (getDimensionality() > 0);
}

TCanvas* AssemblerProjection::plot(bool log, TF1* f1, double xminFit, double xmaxFit) {
	assert(getDimensionality() <= 2);
	
	if(getDimensionality() == 2) {
		return plot2D(log);
	}
	
	bool hasBackground = has("background");
	bool doRatio  = (getDimensionality() <= 1) && hasBackground && !m_assembler->getMode("noRatioPlot");
	bool doZscore = m_assembler->getMode("ZscorePlot");
	bool debug = m_assembler->getMode("debug");
	m_canvas = new TCanvas("c1", "c1", 1200, doRatio ? 750 : 490);
	
	TPad *pad1 = new TPad("pad1", "pad1", 0, doRatio ? 0.3 : 0, 1, 1);
	if(doRatio) {
		pad1->SetBottomMargin(0.025);
		pad1->SetRightMargin(0.3);
	}
	pad1->Draw();
	pad1->cd();
	pad1->SetTicks(1, 1);
	
	TString title = m_name;
	if(getDimensionality() == 1) {
		TString name = m_assembler->getVarName(m_varNames.at(0));
		if(title != name) {
			title = TString::Format("%s (%s)", name.Data(), m_varNames.at(0).c_str());
		}
	}
	
	// TODO Not cloning causes segfault ...
	TH1* hData = (TH1*)m_stacks.find("data")->second.first->GetStack()->Last()->Clone();
	if(hasOverflowIncluded()) {
		// Set overflow bin content to make it show up in statistics box
		auto nEntries = hData->GetEntries();
		hData->SetBinContent(hData->GetNbinsX() + 1, hData->GetBinContent(hData->GetNbinsX()));
		hData->SetEntries(nEntries);
	}
	hData->SetLineWidth(1);
	hData->SetMarkerStyle(9);
	
	std::vector<TH1*> hSignals = getHistograms("signal");
	
	TH1* hBackground = 0;
	TH1* hBackgroundErr = 0;
	TH1* hRatio = 0;
	TH1* hRatioBkg = 0;
	if(hasBackground) {
		hBackground = (TH1*)m_stacks.find("background")->second.first->GetStack()->Last()->Clone("background");
		for(int i = 0; i < hBackground->GetNcells(); ++i) {
			// Add up stat. error in the background stack (ideally 0 with infinite MC) and the systematic uncertainties
			// Those are together the "comprehensive systematic uncertainty"
			double error2 = pow(hBackground->GetBinError(i), 2) + pow(getBinSyst("background", i), 2);
			hBackground->SetBinError(i, sqrt(error2));
		}
		
		hBackgroundErr = (TH1*)hBackground->Clone("backgroundErr");
		hBackgroundErr->Reset();
		const double alpha = 1 - 0.6827;
		for(int i = 0; i < hBackgroundErr->GetNcells(); ++i) {
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
		hRatioBkg = debug ? (TH1*)hBackgroundErr->Clone("hRatioBkg") : (TH1*)hBackground->Clone("hRatioBkg");
		
		double signalMax = 0;
		for(auto const &hSignal : hSignals) {
			signalMax = max(signalMax, hSignal->GetMaximum());
		}
		hData->SetMaximum(max(1., max(hData->GetMaximum(), max(hBackground->GetMaximum(), signalMax))));
	}
	
	hData->SetMaximum(max(log ? 50. : 5., (log ? 5. : 1.5) * hData->GetMaximum()));
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
	hData->SetLineColor(kBlack);
	
	if(doRatio) {
		hData->GetXaxis()->SetLabelFont(43);
		hData->GetXaxis()->SetLabelSize(0);
	}
	hData->GetYaxis()->SetLabelFont(43);
	hData->GetYaxis()->SetLabelSize(16);
	
	hData->Clone("dummy")->Draw("EP"); // use dummy name to allow unique name in TCanvas for the actual data histogram
	
	if(hasBackground) {
		((THStack*)m_stacks.find("background")->second.first->Clone())->Draw("HIST SAME"); // TODO crashes when not cloning
		hBackground->SetFillColor(kBlack);
		hBackground->SetFillStyle(3002);
		hBackground->Draw("E2 SAME");
		if(debug) {
			hBackgroundErr->SetFillColor(kBlack);
			hBackgroundErr->SetFillStyle(3013);
			hBackgroundErr->SetMarkerStyle(20);
			hBackgroundErr->SetMarkerSize(0);
			hBackgroundErr->Draw("SAME E2");
		}
		for(auto const &hSignal : hSignals) {
			hSignal->SetMarkerColor(kWhite);
			hSignal->SetMarkerStyle(21);
			hSignal->SetFillStyle(3008);
			hSignal->Draw("SAME E2 P");
		}
	}
	
	hData->Clone("dummy")->Draw("AXIS SAME"); // Documentation says that statistics box is not drawn with SAME. However, it is for this specific Draw(), and it has the title "dummy". We don't want that. So, ...
	hData->Draw("EP SAMES"); // ... let's request a statistics box for the actual data with SAMES. (Here, SAME doesn't draw the box. I propose a CERN experiment to study and develop a theory of the mysteries of ROOT.)
	gStyle->SetOptStat(111111);
	pad1->SetLogy(log);
	
	m_canvas->cd();
	TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, doRatio ? 0.3 : 0);
	pad2->SetTopMargin(0.025);
	pad2->SetRightMargin(0.3);
	pad2->SetBottomMargin(0.2);
	pad2->SetTickx(1);
	pad2->SetTicky(1);
	pad2->SetGridy(1);
	pad2->Draw();
	pad2->cd();

	double ratio = 0;	
	if(doRatio) {
		ratio = hData->Integral() / hBackground->Integral();
		TLine* line1 = new TLine(hData->GetBinLowEdge(1), 1, hData->GetBinLowEdge(hData->GetNbinsX()+1), 1);
		TLine* line2 = new TLine(hData->GetBinLowEdge(1), ratio, hData->GetBinLowEdge(hData->GetNbinsX()+1), ratio);
		line2->SetLineColor(kBlack);
		line2->SetLineWidth(2);
		hRatio->GetXaxis()->SetTitle(title);
		hRatio->SetTitle("");
		for(int i = 0; i < hRatio->GetXaxis()->GetNbins() + 1; ++i) {
			double yield = hBackground->GetBinContent(i);
			hRatio->SetBinContent(i, (yield == 0) ? 0 : hRatio->GetBinContent(i) / yield);
			hRatio->SetBinError(i, (yield == 0) ? 0 : hRatio->GetBinError(i) / yield);
			if(doZscore){
			  cout<<"Calculate ZScore: "<<endl;
			}
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
		hRatio->GetYaxis()->SetTitle("Obs/Exp");
		hRatio->GetYaxis()->CenterTitle();
		hRatio->GetYaxis()->SetTitleSize(0.1);
		hRatio->GetXaxis()->SetTitleSize(0.1);
		hRatio->GetYaxis()->SetTitleOffset(0.25);
		hRatio->GetXaxis()->SetTitleOffset(0.8);
		hRatio->GetXaxis()->SetTickLength(0.1);
		hRatio->SetFillColor(kBlack);
		hRatio->SetFillStyle(3001);
		hRatio->SetMinimum(0);
		//if(hRatio->GetMaximum() < 0.5) {
		//	hRatio->SetMaximum(2 * hRatio->GetMaximum());
		//} else if(hRatio->GetMaximum() < 2) {
		//	hRatio->SetMaximum(2);
		//}
		hRatio->GetYaxis()->SetRangeUser(0,2.5);
		hRatio->GetYaxis()->SetRangeUser(hRatio->GetMinimum(0), hRatio->GetMaximum());
		hRatio->Draw("AXIS");
		double hRatioBkgErrorSum = 0;
		for(int i = 0; i < hRatioBkg->GetXaxis()->GetNbins() + 1; ++i) {
			double yield = hBackground->GetBinContent(i);
			hRatioBkg->SetBinContent(i, (yield == 0) ? 0 : hRatioBkg->GetBinContent(i) / yield);
			hRatioBkg->SetBinError(i, (yield == 0) ? 0 : hRatioBkg->GetBinError(i) / yield);
			
			if(hRatioBkg->GetBinContent(i) > hRatio->GetMaximum()) {
				double lo = hRatioBkg->GetBinContent(i) - hRatioBkg->GetBinError(i);
				hRatioBkg->SetBinContent(i, hRatio->GetMaximum());
				hRatioBkg->SetBinError(i, max(hRatioBkg->GetBinContent(i) - lo, 0.0));
			}
			hRatioBkgErrorSum += hRatioBkg->GetBinError(i);
		}
		// If all the uncertainties in hRatioBkg are 0 (this happens when the error bars are all out of y-axis range), ROOT would draw error bars filling all of the histogram frame. We don't want to draw anything in this case.
		if(hRatioBkgErrorSum > 0) {
			hRatioBkg->SetFillColor(kBlack);
			hRatioBkg->SetFillStyle(3002);
			hRatioBkg->SetMarkerStyle(20);
			hRatioBkg->SetMarkerSize(0);
			line1->Draw();
			if(debug) {
				line2->Draw();
			}
			hRatioBkg->Draw("E2 SAME");
		}
		gStyle->SetOptFit(1111);
		((TPaveStats*)hRatio->GetListOfFunctions()->FindObject("stats"))->SetOptStat(0);
		if(f1) {
			hRatio->Fit(f1, "", "SAME AXIS", xminFit, xmaxFit);
		}
		hRatio->Draw("SAME");
	}
	

	if(hasBackground) {
		ratio = hData->Integral() / hBackground->Integral();
		TLegend* legend = new TLegend(0.73,0.02,0.98,0.68);
		//TLegend* legend = new TLegend(0.73,0.1,0.98,0.92);
		legend->SetHeader(TString::Format("%.1f (r = %.3f)", hBackground->Integral(), ratio).Data());
		TList* hists = m_stacks.find("background")->second.first->GetHists();
		TIterator* iter = new TListIter(hists, false);
		while(TH1* obj = (TH1*)iter->Next()) {
			legend->AddEntry(obj, TString::Format("%s [%.1f]", obj->GetTitle(), obj->Integral()).Data());
		}
		delete iter;
		for(auto const &hSignal : hSignals) {
			legend->AddEntry((TObject*)0, "", "");
			hSignal->SetLineColor(kWhite);
			TString legendTitle = hSignal->GetTitle();
			legendTitle.ReplaceAll("[X]", TString::Format("[%.1f]", hSignal->Integral()));
			legend->AddEntry(hSignal, legendTitle.Data(), "FP");
		}
		m_canvas->cd();
		legend->Draw();
	}
	
	return m_canvas;
}

TCanvas* AssemblerProjection::plot2D(bool log) {
	assert(getDimensionality() == 2);
	
	bool hasBackground = has("background");
	bool doRatio = hasBackground && !m_assembler->getMode("noRatioPlot");
	//bool debug = m_assembler->getMode("debug");
	m_canvas = new TCanvas("c1", "c1", 700, doRatio ? 700 : 490);
	
	TPad *pad1 = new TPad("pad1", "pad1", 0, doRatio ? 0.3 : 0, 1, 1);
	pad1->Draw();
	pad1->cd();
	pad1->SetTicks(1, 1);
	
	// TODO Not cloning causes segfault ...
	TH2* hData = (TH2*)m_stacks.find("data")->second.first->GetStack()->Last()->Clone();
	if(hasOverflowIncluded()) {
		// Set overflow bin content to make it show up in statistics box
		auto nEntries = hData->GetEntries();
		hData->SetBinContent(hData->GetNbinsX() + 1, hData->GetBinContent(hData->GetNbinsX()));
		hData->SetEntries(nEntries);
	}
	hData->SetLineWidth(1);
	hData->SetMarkerStyle(9);
	
	auto hSignals = getHistograms("signal");
	
	TH2* hBackground = 0;
	TH2* hRatio = 0;
	if(hasBackground) {
		hBackground = (TH2*)m_stacks.find("background")->second.first->GetStack()->Last()->Clone("background");
		for(int i = 0; i < hBackground->GetNcells(); ++i) {
			// Add up stat. error in the background stack (ideally 0 with infinite MC) and the systematic uncertainties
			// Those are together the "comprehensive systematic uncertainty"
			double error2 = pow(hBackground->GetBinError(i), 2) + pow(getBinSyst("background", i), 2);
			hBackground->SetBinError(i, sqrt(error2));
		}
		
		hRatio = (TH2*)hData->Clone("hRatio");
		
		double signalMax = 0;
		for(auto const &hSignal : hSignals) {
			signalMax = max(signalMax, hSignal->GetMaximum());
		}
		hData->SetMaximum(max(1., max(hData->GetMaximum(), max(hBackground->GetMaximum(), signalMax))));
	}
	
	hData->SetMaximum(max(log ? 50. : 5., (log ? 5. : 1.5) * hData->GetMaximum()));
	if(log) {
		hData->SetMinimum(hasBackground ? min(0.1, 0.5 * hBackground->GetMinimum(0)) : 0.1);
		// Make sure the range spans at least one order of magnitude
		if(hData->GetMinimum() > hData->GetMaximum() / 15) {
			hData->SetMinimum(hData->GetMaximum() / 15);
		}
	} else {
		hData->SetMinimum(0);
	}
	
	THStack* hStack = (THStack*)m_stacks.find("background")->second.first->Clone();
	hStack->SetMinimum(hData->GetMinimum());
	hStack->SetMaximum(hData->GetMaximum());
	hStack->Draw();
	
	TString titleX = m_varNames.at(0).c_str();
	TString nameX = m_assembler->getVarName(m_varNames.at(0));
	if(titleX != nameX) {
		titleX = TString::Format("%s (%s)", nameX.Data(), m_varNames.at(0).c_str());
	}
	//hData->GetXaxis()->SetTitle(titleX);
	hStack->GetXaxis()->SetTitle(titleX);
	hStack->GetXaxis()->SetTitleOffset(1.6);
	
	TString titleY = m_varNames.at(1).c_str();
	TString nameY = m_assembler->getVarName(m_varNames.at(1));
	if(titleY != nameY) {
		titleY = TString::Format("%s (%s)", nameY.Data(), m_varNames.at(1).c_str());
	}
	//hData->GetYaxis()->SetTitle(titleY);
	hStack->GetYaxis()->SetTitle(titleY);
	hStack->GetYaxis()->SetTitleOffset(1.6);
	
	if(hasBackground) {
		hStack->Draw("LEGO1");
		
		for(auto const &hSignal : hSignals) {
			hSignal->SetMarkerColor(kWhite);
			hSignal->SetMarkerStyle(21);
			hSignal->SetFillStyle(3008);
			hSignal->Draw("SAME E2 P");
		}
	}
	
	hData->SetLineColor(kBlack);
	hData->SetLineWidth(1);
	hData->SetMarkerColor(kBlack);
	hData->SetMarkerStyle(8);
	hData->SetMarkerSize(0.7);
	hData->Draw("E2 P SAME");
	
	gStyle->SetOptStat(111111);
	pad1->SetLogz(log);
	pad1->SetPhi(210);
	
	double ratio = 0;
	if(hasBackground) {
		ratio = hData->Integral() / hBackground->Integral();
		
		TLegend* legend = new TLegend(0.64,0.6,0.98,0.92);
		legend->SetHeader(TString::Format("%.1f (r = %.3f)", hBackground->Integral(), ratio).Data());
		TList* hists = m_stacks.find("background")->second.first->GetHists();
		TIterator* iter = new TListIter(hists, false);
		while(TH2* obj = (TH2*)iter->Next()) {
			legend->AddEntry(obj, TString::Format("%s [%.1f]", obj->GetTitle(), obj->Integral()).Data());
		}
		delete iter;
		for(auto const &hSignal : hSignals) {
			legend->AddEntry((TObject*)0, "", "");
			hSignal->SetLineColor(kWhite);
			TString legendTitle = hSignal->GetTitle();
			legendTitle.ReplaceAll("[X]", TString::Format("[%.1f]", hSignal->Integral()));
			legend->AddEntry(hSignal, legendTitle.Data(), "FP");
		}
		legend->Draw();
	}
	
	m_canvas->cd();
	TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, doRatio ? 0.3 : 0);
	pad2->SetTopMargin(0.025);
	pad2->Draw();
	pad2->cd();
	
	if(doRatio) {
		for(int i = 0; i < hRatio->GetNcells(); ++i) {
			// Compute residual (t-statistic)
			double residual = hRatio->GetBinContent(i) - hBackground->GetBinContent(i);
			double error2 = hBackground->GetBinContent(i); // this is (sqrt(n))^2
			error2 += pow(hBackground->GetBinError(i), 2);
			
			hRatio->SetBinContent(i, residual / sqrt(error2));
			
			// Uncertainty on residual doesn't have much meaning
			hRatio->SetBinError(i, 0);
		}
		hRatio->SetTitle("");
		hRatio->GetZaxis()->SetTitle("(data #minus background) / uncertainty");
		hRatio->SetMinimum();
		hRatio->SetMaximum();
		hRatio->Draw("COLZ");
		gStyle->SetOptFit(1111);
		((TPaveStats*)hRatio->GetListOfFunctions()->FindObject("stats"))->SetOptStat(0);
		hRatio->Draw("COLZ");
	}
	
	//pad2->SetPhi(210);
	
	return m_canvas;
}

void AssemblerProjection::prepareStacks() {
	// Combine correlated uncertainties and assemble contributions / bundle components into sorted histogram stack
	for(const auto &typeProjection : m_typeProjections) {
		// Intermediate structure for main histogram, and stack for systematic uncertainties (statistical ones are taken care of in main histogram
		std::vector<std::pair<TH1*, double>> vh;
		THStack* hsSyst = new THStack("hsSyst", m_assembler->getVarExp() + TString(" {") + m_assembler->getSelection() + TString("}"));
		
		// Bundle-wise structure (for datacard correlation bundles and such)
		m_bundles.insert(make_pair(typeProjection.first, std::map<TString, std::pair<THStack*, THStack*>>()));
		
		// Loop over signal / background components
		for(const auto &baseBundleProjection : typeProjection.second) {
			TString bundleName = baseBundleProjection->getSource()->getName();
			
			// Prepare bundle-wise stacks
			THStack* hsBundle = new THStack((TString("hs_") + bundleName).Data(), m_assembler->getVarExp() + TString(" {") + m_assembler->getSelection() + TString("}"));
			THStack* hsSystBundle = new THStack((TString("hsSyst_") + bundleName).Data(), m_assembler->getVarExp() + TString(" {") + m_assembler->getSelection() + TString("}"));
			m_bundles[typeProjection.first].insert(make_pair(bundleName, make_pair(hsBundle, hsSystBundle)));
			
			// Add histogram contents
			vh.push_back(make_pair(baseBundleProjection->getHistogram(), baseBundleProjection->getHistogram()->Integral()));
			
			// Same in the bundle-wise structure
			hsBundle->Add(baseBundleProjection->getHistogram());
			
			for(const auto &uncertainty : baseBundleProjection->getUncertainties()) {
				// Combine uncertainties into main histograms
				TH1* hUncertainty = hsSyst->GetHists()
					? (TH1*)hsSyst->GetHists()->FindObject(uncertainty.first)
					: 0;
				if(hUncertainty) {
					for(int j = 0; j < hUncertainty->GetNcells(); ++j) {
						double value = hUncertainty->GetBinContent(j);
						value = sqrt(value*value + pow(uncertainty.second->GetBinContent(j), 2));
						hUncertainty->SetBinContent(j, value);
					}
				} else {
					// We need to add a clone because we will manipulate this later
					hsSyst->Add((TH1*)uncertainty.second->Clone());
				}
				
				// Same in the bundle-wise structure (but uncertainty names can occur only once)
				hsSystBundle->Add(uncertainty.second);
			}
		}
		
		// Sort by amount of contribution
		std::sort(vh.begin()
			, vh.end()
			, boost::bind(&std::pair<TH1*, double>::second, _1) < boost::bind(&std::pair<TH1*, double>::second, _2)
		);
		
		// Prepare content stack
		THStack* hs = new THStack("hs", m_assembler->getVarExp() + TString(" {") + m_assembler->getSelection() + TString("}"));
		for(const auto &contribution : vh) {
			contribution.first->SetLineWidth(0);
			hs->Add(contribution.first);
		}
		
		if(m_stacks.find(typeProjection.first) != m_stacks.end()) {
			throw std::runtime_error("overwriting projection components not supported");
		}
		m_stacks.insert(make_pair(typeProjection.first, make_pair(hs, hsSyst)));
	}
}

void AssemblerProjection::print() const {
	assert(getDimensionality() <= 1);
	
	double sumData = 0;
	double sumBackground = 0;
	double sumBackgroundStat2 = 0;
	double sumBackgroundSyst = 0;
	double sumSignal = 0;
	double sumSignalStat2 = 0;
	double sumSignalSyst = 0;
	
	TH1* hData = (TH1*)m_stacks.find("data")->second.first->GetStack()->Last()->Clone();
	//cout << "data entries: " << hData->GetEntries() << endl;
	//cout << "data integral: " << hData->Integral() << endl;
	//cout << "data integral w/ overflow: " << hData->Integral(0, hData->GetNbinsX() + 1) << endl;
	cout << ((TH1*)m_stacks.find("data")->second.first->GetStack()->Last())->GetTitle() << endl;
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
		double lo = hData->GetXaxis()->GetBinLowEdge(i);
		double hi = hData->GetXaxis()->GetBinUpEdge(i);
		
		if(isDistribution()) {
			if(i < hData->GetNbinsX() || !hasOverflowIncluded()) {
				cout << m_varNames.at(0) << " " << lo << "-" << hi;
			} else {
				cout << m_varNames.at(0) << " " << lo << "-" << "inf";
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
		printf("%s:	%.0f", m_name.Data(), sumData);
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

TString AssemblerProjection::printRA7table() const {
	assert(getDimensionality() <= 1);
	
	double sumData = 0;
	double sumBackground = 0;
	double sumBackgroundStat2 = 0;
	double sumBackgroundSyst = 0;
	double sumSignal = 0;
	double sumSignalStat2 = 0;
	double sumSignalSyst = 0;
	TString SRvalue = "";
	
	TH1* hData = (TH1*)m_stacks.find("data")->second.first->GetStack()->Last()->Clone();
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
		double contentData = getBin("data", i);
		sumData += contentData;
		
		if(!has("signal")) {
			double contentBackground = getBin("background", i);
			double contentBackgroundStat = getBinStat("background", i);
			double contentBackgroundSyst = getBinSyst("background", i);
			sumBackground += contentBackground;
			sumBackgroundStat2 += contentBackgroundStat*contentBackgroundStat;
			sumBackgroundSyst += contentBackgroundSyst;
		}
		
		if(has("signal")) {
			double contentSignal = getBin("signal", i);
			double contentSignalStat = getBinStat("signal", i);
			double contentSignalSyst = getBinSyst("signal", i);
			sumSignal += contentSignal;
			sumSignalStat2 += contentSignalStat*contentSignalStat;
			sumSignalSyst += contentSignalSyst;
		}
	}
	if(!has("signal")) {
		// TODO Replace by Poisson error
		SRvalue = TString::Format("%.0f : %.2f $\\pm$ %.2f $\\pm$ %.2f", sumData, sumBackground, sqrt(sumBackgroundStat2), sumBackgroundSyst);
	}
	if(has("signal")) {
		SRvalue = TString::Format("%.0f : %.2f $\\pm$ %.2f $\\pm$ %.2f", sumData, sumSignal, sqrt(sumSignalStat2), sumSignalSyst);
	}
	return SRvalue;
}

void AssemblerProjection::printMeta(TString type) const {
	for(auto &meta : getMeta(type)) {
		cout << meta.event << " " << meta.run << " " << meta.lumi << " " << meta.fakeIncarnation << endl;
	}
}

void AssemblerProjection::datacard(TString datacardName, bool isData, double statFactor, double systFactor) {
	cerr << "Datacards on projections currently not implemented. Please create a ChannelCollection." << endl;
}
