#include "RutgersIAF2012/AnalysisPresenter/interface/Projection.h"

#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TPaveStats.h"
#include "TStyle.h"

#include <assert.h>
#include <exception>

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(Projection)

Projection::Projection(TString name, bool binForOverflow) : m_binForOverflow(binForOverflow), m_name(name) {
}

Projection::Projection() {
	/* no-op */
}

Projection::~Projection() {
	//delete m_canvas; // TODO this causes a segfault -- probably something to do with http://root.cern.ch/phpBB3/viewtopic.php?f=14&t=11472
	for(auto &component : m_components) {
		delete component.second.first;
		delete component.second.second;
	}
}

void Projection::add(TString type, THStack* content, THStack* contentSyst) {
	if(m_components.find(type) != m_components.end()) {
		throw std::runtime_error("overwriting projection components not supported");
	}
	m_components.insert(make_pair(type, make_pair(content, contentSyst)));
}

double Projection::getBin(TString type, int i) const {
	assert(has(type));
	TObjArray* stack = m_components.find(type)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinContent(i) : 0;
}

double Projection::getBinStat(TString type, int i) const {
	assert(has(type));
	TObjArray* stack = m_components.find(type)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinError(i) : 0;
}

double Projection::getBinSyst(TString type, int i) const {
	assert(has(type));
	TObjArray* stack = m_components.find(type)->second.second->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinContent(i) : 0;
}

bool Projection::has(TString type) const {
	return (m_components.find(type) != m_components.end());
}

bool Projection::hasOverflowIncluded() const {
	return m_binForOverflow;
}

TCanvas* Projection::plot(bool log, double xminFit, double xmaxFit) {
	m_canvas = new TCanvas("c1", "c1", 700, 700);
	
	TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
	pad1->SetBottomMargin(0.025);
	pad1->Draw();
	pad1->cd();
	
	// TODO Not cloning causes segfault ...
	TH1* hData = (TH1*)m_components.find("data")->second.first->GetStack()->Last()->Clone();
	TH1* hBackground = (TH1*)m_components.find("background")->second.first->GetStack()->Last()->Clone();
	
	TH1* hRatio = (TH1*)hData->Clone("hRatio");
	hData->SetMaximum(max(hData->GetMaximum(), hBackground->GetMaximum()) * (1 + 0.5));
	hData->SetMinimum(log ? max(0.01, ((TH1*)m_components.find("background")->second.first->GetStack()->First())->Integral()) : 0);
	hData->SetLineColor(kRed);
	
	hData->Draw();
	hData->GetXaxis()->SetLabelFont(43);
	hData->GetXaxis()->SetLabelSize(0);
	hData->GetYaxis()->SetLabelFont(43);
	hData->GetYaxis()->SetLabelSize(16);
	((TH1*)m_components.find("background")->second.first->Clone())->Draw("HIST SAME"); // TODO crashes when not cloning
	hBackground->SetFillColor(kBlack);
	hBackground->SetFillStyle(3001);
	hBackground->Draw("E2 SAME");
	hData->Draw("SAME");
	hData->Draw("AXIS SAME");
	pad1->SetLogy(log);
	
	TLegend* legend = new TLegend(0.84,0.15,0.98,0.55);
	TList* hists = m_components.find("background")->second.first->GetHists();
	TIterator* iter = new TListIter(hists, false);
	while(TH1* obj = (TH1*)iter->Next()) {
		legend->AddEntry(obj);
	}
	delete iter;
	legend->Draw();
	
	m_canvas->cd();
	TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
	pad2->SetTopMargin(0.025);
	pad2->Draw();
	pad2->cd();
	
	TLine* line1 = new TLine(hData->GetBinLowEdge(1), 1, hData->GetBinLowEdge(hData->GetNbinsX()+1), 1);
	hRatio->SetTitle("");
	hRatio->Divide(hBackground);
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
	hRatio->Fit("pol0", "", "SAME", xminFit, xmaxFit);
	
	return m_canvas;
}
