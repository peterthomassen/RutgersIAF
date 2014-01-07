#include <iostream>
#include <limits>
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"

#include "/cms/thomassen/2013/RdxyReproduction/CMSSW_5_2_2/src/RutgersIAF2012/RootC/interface/debug.h"

Double_t rangeIntegral(TH1* hist, double x1, double x2, Option_t* option = "") {
	int binx1 = hist->GetXaxis()->FindFixBin(x1);
	int binx2 = hist->GetXaxis()->FindFixBin(x2);
	if(x2 - hist->GetXaxis()->GetBinLowEdge(binx2) < 1E-12) {
		binx2--;
	}
	std::cerr << "[PT] Integrating " << hist->GetName() << " X range " << x1 << ".." << x2 << ", equivalent to bins " << binx1 << ".." << binx2;
	// TODO Allow other integrals with swapped range boundaries, too; need to fix ROOT behavior, though
	assert(binx2 > binx1);
	std::cerr << "; result: " << hist->Integral(binx1, binx2, option) << std::endl;
	return hist->Integral(binx1, binx2, option);
}

Double_t rangeIntegral(TH2* hist, double x1, double x2, double y1, double y2, Option_t* option = "") {
	int binx1 = hist->GetXaxis()->FindFixBin(x1);
	int binx2 = hist->GetXaxis()->FindFixBin(x2);
	if(x2 - hist->GetXaxis()->GetBinLowEdge(binx2) < 1E-12) {
		binx2--;
	}
	int biny1 = hist->GetYaxis()->FindFixBin(y1);
	int biny2 = hist->GetYaxis()->FindFixBin(y2);
	if(y2 - hist->GetYaxis()->GetBinLowEdge(biny2) < 1E-12) {
		biny2--;
	}
	std::cerr << "[PT] Integrating " << hist->GetName() << " X range " << x1 << ".." << x2 << ", equivalent to bins " << binx1 << ".." << binx2 << " and Y range " << y1 << ".." << y2 << ", equivalent to bins " << biny1 << ".." << biny2;
	// TODO Allow other integrals with swapped range boundaries, too; need to fix ROOT behavior, though
	assert(binx2 > binx1);
	assert(biny2 > biny1);
	std::cerr << "; result: " << hist->Integral(binx1, binx2, biny1, biny2, option) << std::endl;
	return hist->Integral(binx1, binx2, biny1, biny2, option);
}

template <class T>
T inf() {
	assert(std::numeric_limits<T>::has_infinity);
	return std::numeric_limits<T>::infinity();
/*
	return std::numeric_limits<T>::has_infinity
		? std::numeric_limits<T>::infinity()
		: std::numeric_limits<T>::max();
*/
}

// CFO method
double calculateRdxy1D(TString filename) {
	TFile* f = new TFile(filename);
	TH1F* histNINP = (TH1F*)f->Get("El2Mu1B0onZMET0to50_n_tracksNINP");
	TH1F* histNIP = (TH1F*)f->Get("El2Mu1B0onZMET0to50_n_tracksNIP");
	
	Double_t statsNINP[4], statsNIP[4];
	histNINP->GetStats(statsNINP);
	histNIP->GetStats(statsNIP);
	double nNINP = statsNINP[2];
	double nNIP = statsNIP[2];
	
	double Rdxy = nNINP / nNIP;
	std::cout << "Rdxy1D = " << nNINP << "/" << nNIP << " = " << Rdxy << std::endl;
	f->Close();
	delete f;
	return Rdxy;
}

double calculateRdxy2D(TString filename) {
	TFile* f = new TFile(filename);
	TH2F* hist = (TH2F*)f->Get("El2Mu1B0onZMET0to50_RelIsoVsDxy_tracks");
	
	double nNINP = rangeIntegral(hist, 0.02, inf<double>(), 0.15, inf<double>());
	double nNIP = rangeIntegral(hist, 0.00, 0.02, 0.15, inf<double>());
	
//	hist->Draw("COLZTEXT");
	
	double Rdxy = nNINP / nNIP;
	std::cout << "Rdxy2D = " << nNINP << "/" << nNIP << " = " << Rdxy << std::endl;
	f->Close();
	delete f;
	return Rdxy;
}

double calculateEfficiencyRatio(TString filename) {
	TFile* f = new TFile(filename);
	double effRat = 0;
	f->Close();
	delete f;
	
//	f->Close();
	return effRat;
}

// FtFsb
double getTauIso_isolated(TH1* hist) {
	return rangeIntegral(hist, 0.0, 2.0);
}

double getTauIso_sideband(TH1* hist) {
	return rangeIntegral(hist, 6.0, 15.0);
}

double getTauIso_other(TH1* hist) {
	return rangeIntegral(hist, 15.0, inf<double>());
}

void getFsb(TH1* hist, double &fSB, double &efSB) {
	double nSideband = getTauIso_sideband(hist);
	double nOther    = getTauIso_other(hist);
	
	fSB = nSideband / (nSideband + nOther);
	efSB = 1/pow(nSideband + nOther, 2) * sqrt(nOther * nOther * nSideband + nSideband * nSideband * nOther);
}

void getFt(TH1* hist, double &fT, double &efT) {
	double nIsolated = getTauIso_isolated(hist);
	double nSideband = getTauIso_sideband(hist);
	
	fT  = nIsolated / nSideband;
	efT  = sqrt( pow(1/nSideband, 2) * nIsolated + pow(nIsolated/pow(nSideband, 2), 2) * nSideband );
}

void plotFsbFt(TString filename) {
	TFile* f = new TFile(filename);
	
	std::vector<TString> flavors;
	flavors.push_back("El");
	flavors.push_back("Mu");
	
	std::vector<int> sumBins;
	sumBins.push_back(40);
	sumBins.push_back(60);
	sumBins.push_back(80);
	sumBins.push_back(100);
	sumBins.push_back(140);
	sumBins.push_back(180);
	sumBins.push_back(220);
	sumBins.push_back(400);
	
	TH2F* hist = new TH2F("ftfsb", "ftfsb", 100, 0, 1, 100, 0, 0.5);
	hist->GetXaxis()->SetTitle("f_{SB}");
	hist->GetYaxis()->SetTitle("f_{T}");
	hist->Draw("AXIS");
	
	TLegend* legend = new TLegend(0.2, 0.7, 0.4, 0.85);
	
	double fSB, efSB, fT, efT;
	TH1F* tauIsoHist = 0;
	TString histName;
	
	// Make fSBfT plot
	for(uint iFlavor = 0; iFlavor < flavors.size(); ++iFlavor) {
		TGraphErrors* plot = new TGraphErrors(0);
		for(uint iSum = 0; iSum < sumBins.size() - 1; ++iSum) {
			int edgeLow = sumBins[iSum];
			int edgeHigh = sumBins[iSum + 1];
			histName = TString::Format("Seed%s2q0ONZMET0to50_tauIsoSum%dto%d", flavors[iFlavor].Data(), edgeLow, edgeHigh);
			tauIsoHist = (TH1F*)f->Get(histName.Data());
			getFsb(tauIsoHist, fSB, efSB);
			getFt(tauIsoHist, fT, efT);
			uint iPoint = plot->GetN();
			std::cout << iPoint << " " << fSB << "+-" << efSB << " " << fT << "+-" << efT << std::endl;
			plot->SetPoint(iPoint, fSB, fT);
			plot->SetPointError(iPoint, efSB, efT);
		}
		plot->SetFillColor(kWhite);
		plot->SetMarkerStyle(7);
		plot->SetMarkerColor(iFlavor + 1);
		plot->Draw("PSAME");
		legend->AddEntry(plot, flavors[iFlavor]);
	}
	legend->Draw();
	
	// Write out numbers for closure test
	for(uint iFlavor = 0; iFlavor < flavors.size(); ++iFlavor) {
		histName = TString::Format("Seed%s2q0SidebandTau1ONZMET50to100_tauIso", flavors[iFlavor].Data());
		tauIsoHist = (TH1F*)f->Get(histName.Data());
		getFsb(tauIsoHist, fSB, efSB);
		std::cout << histName << " fSB = " << fSB << "+-" << efSB << ", nSidebandTaus = " << getTauIso_sideband(tauIsoHist) << std::endl;
	}
	
	for(uint iFlavor = 0; iFlavor < flavors.size(); ++iFlavor) {
		histName = TString::Format("Seed%s2q0Tau1ONZMET50to100_tauIso", flavors[iFlavor].Data());
		tauIsoHist = (TH1F*)f->Get(histName.Data());
		getFsb(tauIsoHist, fSB, efSB);
		std::cout << histName << " fSB = " << fSB << "+-" << efSB << ", nSidebandTaus = " << getTauIso_sideband(tauIsoHist) << std::endl;
	}
	
	return;
	
	f->Close();
	delete f;
}
