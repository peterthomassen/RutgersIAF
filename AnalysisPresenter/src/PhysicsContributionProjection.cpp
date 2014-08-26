#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContributionProjection.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TH1D.h"
#include "THnBase.h"

#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

using namespace std;

ClassImp(PhysicsContributionProjection)

PhysicsContributionProjection::PhysicsContributionProjection() {
	/* no-op */
}

PhysicsContributionProjection::PhysicsContributionProjection(const TString name, const TString title, const PhysicsContribution* contribution, const char* varName, const std::map<TString, THnBase*>* uncertaintyMap, const double zerostat) : m_contribution(contribution), m_name(name), m_title(title) {
	TAxis* axis = (TAxis*)contribution->getContent()->GetListOfAxes()->FindObject(varName);
	if(!axis) {
		cerr << "Could not find axis " << varName << endl;
		throw std::runtime_error("");
	}
	int dim = contribution->getContent()->GetListOfAxes()->IndexOf(axis);
	
	m_histogram = m_contribution->getContent()->Projection(dim, "E");
	m_histogram->SetName(name);
	m_histogram->SetTitle(title);
	
	// Zerostat uncertainty for background and signal samples
	if(!contribution->isData() && zerostat >= 0) {
		for(int i = 1; i <= m_histogram->GetXaxis()->GetNbins() + 1; ++i) {
			if(m_histogram->GetBinContent(i) == 0) {
				m_histogram->SetBinError(i, zerostat);
			}
		}
	}
	
	if(uncertaintyMap) {
		for(auto &uncertainty : *uncertaintyMap) {
			m_uncertainties.insert(make_pair(uncertainty.first, uncertainty.second->Projection(dim, "E")));
		}
	}
}

PhysicsContributionProjection::~PhysicsContributionProjection() {
	delete m_histogram;
	for(auto &uncertainty : m_uncertainties) {
		delete uncertainty.second;
	}
	m_uncertainties.clear();
}

const PhysicsContribution* PhysicsContributionProjection::getPhysicsContribution() const {
	return m_contribution;
}

TH1D* PhysicsContributionProjection::getHistogram() const {
	return m_histogram;
}

std::map<TString, TH1D*> PhysicsContributionProjection::getUncertainties() const {
	return m_uncertainties;
}

void PhysicsContributionProjection::incorporateOverflow(TH1D* &h) {
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

void PhysicsContributionProjection::incorporateOverflow() {
	incorporateOverflow(m_histogram);
	for(auto &uncertainty : m_uncertainties) {
		incorporateOverflow(uncertainty.second);
	}
}

void PhysicsContributionProjection::scale(const double scale) {
	m_histogram->Scale(scale);
	for(auto &uncertainty : m_uncertainties) {
		uncertainty.second->Scale(scale);
	}
}
