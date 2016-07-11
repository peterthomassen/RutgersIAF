#include "RutgersIAF/AnalysisPresenter/interface/BaseBundleProjection.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TH1.h"
#include "THnBase.h"

#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"

using namespace std;

ClassImp(BaseBundleProjection)

BaseBundleProjection::BaseBundleProjection() {
	/* no-op */
}

BaseBundleProjection::BaseBundleProjection(const BaseBundle* source, std::vector<std::string> varNames) : m_source(source), m_varNames(varNames) {
	if(m_varNames.size() > 2) {
		cerr << "was processing projection onto " << m_varNames.size() << " axes" << endl;
		throw std::runtime_error("only 1-d and 2-d projections are supported");
	}
}

BaseBundleProjection::~BaseBundleProjection() {
//	delete m_histogram; // for some reason, this statement makes ROOT crash after running an AnalysisPresenter macro (tried ROOT 5.34)
	for(auto &uncertainty : m_uncertainties) {
		delete uncertainty.second;
	}
	m_uncertainties.clear();
}

TH1* BaseBundleProjection::getHistogram() const {
	return m_histogram;
}

std::set<const PhysicsContribution*> BaseBundleProjection::getPhysicsContributions() const {
	return m_contributions;
}

const BaseBundle* BaseBundleProjection::getSource() const {
	return m_source;
}

std::map<TString, TH1*> BaseBundleProjection::getUncertainties() const {
	return m_uncertainties;
}

void BaseBundleProjection::incorporateOverflow(TH1* &h) {
	assert(m_varNames.size() <= 1);
	
	// Adapted from http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=6764
	UInt_t nx = h->GetNbinsX() + 1;
	Double_t* xbins = new Double_t[nx + 1];
	for (UInt_t i = 0; i < nx; ++i) {
		xbins[i] = h->GetBinLowEdge(i+1);
	}
	xbins[nx] = xbins[nx - 1] + h->GetBinWidth(nx);
	TH1* htmp = (TH1*)h->Clone(h->GetName());
	htmp->SetBins(nx, xbins);
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
