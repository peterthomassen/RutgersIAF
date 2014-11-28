#include "RutgersIAF/AnalysisPresenter/interface/AssemblerProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "Math/QuantFuncMathCore.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TPaveStats.h"
#include "TStyle.h"

#include <assert.h>
#include <boost/bind.hpp>
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

AssemblerProjection::AssemblerProjection(TString name, TString title, bool binForOverflow) : m_binForOverflow(binForOverflow), m_name(name), m_title(title) {
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
}

void AssemblerProjection::add(std::pair<TString, std::vector<PhysicsContributionProjection*>> typeProjection, TString varexp, TString selection) {
	// Combine correlated uncertainties and assemble contributions into sorted histogram stack

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
	TH1D* hUncertainty = (TH1D*)stack->FindObject(name);
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
	assert(has(type));
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
	return (m_components.find(type) != m_components.end());
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

TCanvas* AssemblerProjection::plot(bool log, double xminFit, double xmaxFit, const char* fitFormula) {
	m_canvas = new TCanvas("c1", "c1", 700, 700);
	
	TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
	pad1->SetBottomMargin(0.025);
	pad1->Draw();
	pad1->cd();
	pad1->SetTicks(1, 1);
	
	TString title = (m_title != m_name)
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
	for(int i = 0; i < hData->GetNbinsX() + 1; ++i) {
		hData->SetBinError(i, 1e-3);
	}
	hData->SetMarkerStyle(9);
	
	TH1* hBackground = (TH1*)m_components.find("background")->second.first->GetStack()->Last()->Clone();
	for(int i = 0; i < hBackground->GetNbinsX() + 1; ++i) {
		// Add up stat. error in the background stack (ideally 0 with infinite MC) and the systematic uncertainties
		// Those are together to "comprehensive systematic uncertainty"
		double error2 = pow(hBackground->GetBinError(i), 2) + pow(getBinSyst("background", i), 2);
		hBackground->SetBinError(i, sqrt(error2));
	}
	
	TH1* hBackgroundErr = (TH1*)hBackground->Clone();
	hBackgroundErr->Reset();
	TH1* hBackgroundFullError = (TH1*)hBackground->Clone();
	hBackgroundFullError->Reset();
	const double alpha = 1 - 0.6827;
	for(int i = 0; i < hBackgroundErr->GetNbinsX() + 1; ++i) {
		double n = hBackground->GetBinContent(i);
		double lo = (n == 0) ? 0 : ROOT::Math::gamma_quantile(alpha/2, n, 1.);
		double hi = ROOT::Math::gamma_quantile_c(alpha/2, n+1, 1);
		// Now, combine Poisson fluctuation range with "comprehensive systematic uncertainty" from above
		lo = sqrt(pow(n - lo, 2) + pow(hBackground->GetBinError(i), 2));
		hi = sqrt(pow(hi - n, 2) + pow(hBackground->GetBinError(i), 2));
		hBackgroundFullError->SetBinContent(i, hBackground->GetBinContent(i));
		hBackgroundFullError->SetBinError(i, lo);
		lo = n - lo;
		hi = n + hi;
		n = (lo + hi) / 2;
		hBackgroundErr->SetBinContent(i, n);
		hBackgroundErr->SetBinError(i, (hi - lo) / 2);
	}
	
	TH1* hSignal = 0;
	if(has("signal")) {
		hSignal = (TH1*)m_components.find("signal")->second.first->GetStack()->Last()->Clone();
		for(int i = 0; i < hSignal->GetNbinsX() + 1; ++i) {
			double error2 = pow(hSignal->GetBinError(i), 2) + pow(getBinSyst("signal", i), 2);
			hSignal->SetBinError(i, sqrt(error2));
		}
	}
	
	TH1* hRatio = (TH1*)hData->Clone("hRatio");
	if(hSignal) {
		hData->SetMaximum(max(1., max(hData->GetMaximum(), max(hBackground->GetMaximum(), hSignal->GetMaximum()))));
	} else {
		hData->SetMaximum(max(1., max(hData->GetMaximum(), hBackground->GetMaximum())));
	}
	hData->SetMaximum(1.5 * hData->GetMaximum());
	//hData->SetMinimum(log ? max(0.1, 0.1 * ((TH1*)m_components.find("background")->second.first->GetStack()->First())->Integral()) : 0);
	hData->SetMinimum(log ? min(0.1, 0.5 * hBackground->GetMinimum(0)) : 0);
	// Make sure the range spans at least one order of magnitude in log plots
	if(log && hData->GetMinimum() > hData->GetMaximum() / 15) {
		hData->SetMinimum(hData->GetMaximum() / 15);
	}
	hData->GetXaxis()->SetTitle(title);
	hData->SetLineColor(kRed);
	
	hData->Draw("EP");
	hData->GetXaxis()->SetLabelFont(43);
	hData->GetXaxis()->SetLabelSize(0);
	hData->GetYaxis()->SetLabelFont(43);
	hData->GetYaxis()->SetLabelSize(16);
	((TH1*)m_components.find("background")->second.first->Clone())->Draw("HIST SAME"); // TODO crashes when not cloning
	hBackground->SetFillColor(kRed);
	hBackground->SetFillStyle(3001);
	hBackground->Draw("E2 SAME");
	hBackgroundErr->SetFillColor(kBlack);
	hBackgroundErr->SetFillStyle(3002);
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
	hData->Draw("EP SAME");
	hData->Draw("EP AXIS SAME");
	gStyle->SetOptStat(111111);
	pad1->SetLogy(log);
	
	TLegend* legend = new TLegend(0.84,0.15,0.98,0.55);
	legend->SetHeader(TString::Format("Background [%.1f]", hBackgroundFullError->Integral()).Data());
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
	hRatio->GetXaxis()->SetTitle(title);
	hRatio->SetTitle("");
	for(int i = 0; i <= hRatio->GetXaxis()->GetNbins() + 1; ++i) {
		hRatio->SetBinError(i, 0);
	}
	hRatio->Divide(hBackgroundFullError);
	hRatio->GetXaxis()->SetLabelFont(43);
	hRatio->GetXaxis()->SetLabelSize(16);
	hRatio->GetYaxis()->SetLabelFont(43);
	hRatio->GetYaxis()->SetLabelSize(16);
	hRatio->SetFillColor(kBlack);
	hRatio->SetFillStyle(3001);
	hRatio->SetMinimum(0);
	if(hRatio->GetMaximum() > 3) {
		hRatio->SetMaximum(3);
	}
	hRatio->Draw("AXIS");
	line1->Draw();
	hRatio->Draw("E2 SAME");
	TH1* hRatio2 = (TH1*)hRatio->Clone("hRatio2");
	for(int j = 1; j < hRatio2->GetXaxis()->GetNbins(); ++j) {
		hRatio2->SetBinError(j, 1E-6);
	}
	hRatio2->Draw("E SAME");
	gStyle->SetOptFit(1111);
	((TPaveStats*)hRatio->GetListOfFunctions()->FindObject("stats"))->SetOptStat(0);
	hRatio->Fit(fitFormula, "", "SAME", xminFit, xmaxFit);
	
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
		
		if(i < hData->GetNbinsX() || !hasOverflowIncluded()) {
			cout << m_name << " " << lo << "-" << hi;
		} else {
			cout << m_name << " " << lo << "-" << "inf";
		}
		
		double contentData = getBin("data", i);
		sumData += contentData;
		
		printf("	%.0f", contentData);
		
		if(has("background")) {
			double contentBackground = getBin("background", i);
			double contentBackgroundStat = getBinStat("background", i);
			double contentBackgroundSyst = getBinSyst("background", i);
			sumBackground += contentBackground;
			sumBackgroundStat2 += contentBackgroundStat*contentBackgroundStat;
			sumBackgroundSyst += contentBackgroundSyst;
			
			// TODO Replace by Poisson error
			printf(" : %.2f ± %.2f ± %.2f ± %.2f", contentBackground, sqrt(contentBackground), contentBackgroundStat, contentBackgroundSyst);
		}
		
		if(has("signal")) {
			double contentSignal = getBin("signal", i);
			double contentSignalStat = getBinStat("signal", i);
			double contentSignalSyst = getBinSyst("signal", i);
			sumSignal += contentSignal;
			sumSignalStat2 += contentSignalStat*contentSignalStat;
			sumSignalSyst += contentSignalSyst;
			
			printf(" : %.2f ± %.2f ± %.2f", contentSignal, contentSignalStat, contentSignalSyst);
		}
		cout << endl;
	}
	printf("Sum:		%.0f", sumData);
	if(has("background")) {
		// TODO Replace by Poisson error
		printf(" : %.2f ± %.2f ± %.2f ± %.2f", sumBackground, sqrt(sumBackground), sqrt(sumBackgroundStat2), sumBackgroundSyst);
	}
	if(has("signal")) {
		printf(" : %.2f ± %.2f ± %.2f", sumSignal, sqrt(sumSignalStat2), sumSignalSyst);
	}
	cout << endl;
}


void AssemblerProjection::datacard(TString datacardName) {
	
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
	TString basicName = "/datacard_tcH_";
	TString endName = ".txt";
	TString completeName = "";
	TString directory = "";
	char buffer[1024]; 
    if(getcwd(buffer, 1024) == NULL ) 
		perror("***Directory Error***");  
    directory = buffer;
	completeName = directory + basicName + m_name + "_" + datacardName + endName;
	datacard.open(completeName);	
	datacard << std::fixed << std::setprecision(2);
	datacard << "#Datacard for t->cH with H->tautau/WW/ZZ" << '\n' << "#m_H=126.0 GeV" << '\n' << "#Version 0.1    Nov. 2014" << '\n' << '\n';
	datacard << "imax " << bins << " number of channels" << '\n' << "jmax " << NumberCorClassesBackgrd+NumberCorClassesSignal - 1 << " number of background" << '\n' << "kmax 2 number nuisance parameters" << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	datacard << "Observation";
	
	//Calculate values for datacard
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {	
	
		double contentData = getBin("data", i);
		datacard << '\t' << '\t' << contentData;
	}
	datacard << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	datacard << "bin" << '\t' << '\t' << '\t';
	datacard << std::fixed << std::setprecision(0);
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {	
	
		for (int j = 0; j < (NumberCorClassesSignal + NumberCorClassesBackgrd); j++) {
		
			double lo = hData->GetXaxis()->GetBinLowEdge(i);
			double hi = hData->GetXaxis()->GetBinUpEdge(i);
		
			if(i < hData->GetNbinsX() || !hasOverflowIncluded()) {
				datacard << m_name << lo << "-" << hi << " " << '\t' << '\t';
			} else {
				datacard << m_name << lo << "-" << "inf" << '\t' << '\t';
			}
		}
	}
	datacard << std::fixed << std::setprecision(2);
	datacard << '\n';
	datacard << "process" << '\t';
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {	
	
		for (int j = 0; j < NumberCorClassesSignal; j++) {
		
			if(correlationClassesSignal[j]=="") {
				datacard << '\t' << "remain signal";
			}
			else {
				datacard << '\t' << "signal" << correlationClassesSignal[j];
			}
		}
		
		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			if(correlationClassesBckgrd[j]=="") {
				datacard << '\t' << "remain bckgrd";
			}
			else {
				datacard << '\t' << "bckgrd" << correlationClassesBckgrd[j];
			}
		}
			
	}
	datacard << '\n';
	datacard << "process" << '\t';
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {	
	
		for (int j = 0; j < NumberCorClassesSignal; j++) {
		
			datacard << '\t' << (NumberCorClassesSignal - j)*(-1)+1 << '\t' << '\t' << '\t';
		}
		
		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			datacard << '\t' << j + 1 << '\t' << '\t' << '\t';
		}
		
	}
	datacard << '\n';
	datacard << "rate" << '\t';
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
	
		if(has("signal")) {
		
			for (int j = 0; j < NumberCorClassesSignal; j++) {
			
				double contentSignal = getBin("signal", i, correlationClassesSignal[j]);	
				datacard << '\t' << contentSignal << '\t' << '\t';
			}
		}
		else {
			perror("***Error: No Signal***");
		}
		
		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			double contentBackground = getBin("background", i, correlationClassesBckgrd[j]);
			datacard << '\t' << contentBackground << '\t' << '\t';
		}
	}
	datacard << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	datacard << "Stat  lnN";
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
	
		if(has("signal")) {
		
			for (int j = 0; j < NumberCorClassesSignal; j++) {
			
				double contentSignalStat = getBinStat("signal", i, correlationClassesSignal[j]);		
				double contentSignal = getBin("signal", i, correlationClassesSignal[j]);	
				double ratio = contentSignalStat/contentSignal;
				if (contentSignal == 0) {ratio = 0.1;}
				datacard << '\t' << 1 + ratio << '\t' << '\t';
			}
		}
		else {
			perror("***Error: No Signal -> No variance***");
		}

		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			double contentBackgroundStat = getBinStat("background", i, correlationClassesBckgrd[j]);		
			double contentBackground = getBin("background", i, correlationClassesBckgrd[j]);	
			double ratio = contentBackgroundStat/contentBackground;
			if (contentBackground == 0) {ratio = 0.1;}
			datacard << '\t' << 1 + ratio << '\t' << '\t';
		}
	}
	datacard << '\n';
	datacard << "Syst  lnN";
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
	
		if(has("signal")) {
		
			for (int j = 0; j < NumberCorClassesSignal; j++) {
			
				double contentSignalSyst = getBinSyst("signal", i, correlationClassesSignal[j]);		
				double contentSignal = getBin("signal", i, correlationClassesSignal[j]);	
				double ratio = contentSignalSyst/contentSignal;
				if (contentSignal == 0) {ratio = 0.1;}
				datacard << '\t' << 1 + ratio << '\t' << '\t';
			}
		}
		else {
			perror("***Error: No Signal -> No variance***");
		}

		for (int j = 0; j < NumberCorClassesBackgrd; j++) {
		
			double contentBackgroundSyst = getBinSyst("background", i, correlationClassesBckgrd[j]);		
			double contentBackground = getBin("background", i, correlationClassesBckgrd[j]);	
			double ratio = contentBackgroundSyst/contentBackground;
			if (contentBackground == 0) {ratio = 0.1;}
			datacard << '\t' << 1 + ratio << '\t' << '\t';
		}
	}
	datacard << '\n';
	
	datacard.close();
}
