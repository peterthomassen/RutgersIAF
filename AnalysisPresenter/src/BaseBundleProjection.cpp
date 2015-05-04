#include "RutgersIAF/AnalysisPresenter/interface/BaseBundleProjection.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TH1D.h"
#include "THnBase.h"

#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"

using namespace std;

ClassImp(BaseBundleProjection)

BaseBundleProjection::BaseBundleProjection() {
	/* no-op */
}

BaseBundleProjection::BaseBundleProjection(const BaseBundle* source, const char* varName) : m_source(source) {
}

BaseBundleProjection::~BaseBundleProjection() {
	cout << "Called ~BaseBundleProjection()" << endl;
	delete m_histogram;
	for(auto &uncertainty : m_uncertainties) {
		delete uncertainty.second;
	}
	m_uncertainties.clear();
}

TH1D* BaseBundleProjection::getHistogram() const {
	return m_histogram;
}

std::set<const PhysicsContribution*> BaseBundleProjection::getPhysicsContributions() const {
	return m_contributions;
}

const BaseBundle* BaseBundleProjection::getSource() const {
	return m_source;
}

std::map<TString, TH1D*> BaseBundleProjection::getUncertainties() const {
	return m_uncertainties;
}

void BaseBundleProjection::incorporateOverflow(TH1D* &h) {
	// Adapted from http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=6764
	UInt_t nx = h->GetNbinsX() + 1;
	Double_t* xbins = new Double_t[nx + 1];
	for (UInt_t i = 0; i < nx; ++i) {
		xbins[i] = h->GetBinLowEdge(i+1);
	}
	xbins[nx] = xbins[nx - 1] + h->GetBinWidth(nx);
	TH1D* htmp = new TH1D(h->GetName(), h->GetTitle(), nx, xbins);
	htmp->SetXTitle(h->GetXaxis()->GetTitle());
	htmp->SetYTitle(h->GetYaxis()->GetTitle());
	for (UInt_t i = 0; i <= nx; ++i) {
		htmp->SetBinContent(i, h->GetBinContent(i));
		htmp->SetBinError(i, h->GetBinError(i));
	}
	htmp->SetEntries(h->GetEntries());
	delete h;
	h = htmp;
}

void BaseBundleProjection::incorporateOverflow() {
	incorporateOverflow(m_histogram);
	for(auto &uncertainty : m_uncertainties) {
		incorporateOverflow(uncertainty.second);
	}
}
