#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContributionProjection.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TH1.h"
#include "THnBase.h"

#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

using namespace std;

ClassImp(PhysicsContributionProjection)

PhysicsContributionProjection::PhysicsContributionProjection() {
	/* no-op */
}

PhysicsContributionProjection::PhysicsContributionProjection(const PhysicsContribution* contribution, const char* varName, const double zerostat) : BaseBundleProjection(contribution, varName) {
	TAxis* axis = (TAxis*)contribution->getContent()->GetListOfAxes()->FindObject(varName);
	if(!axis) {
		cerr << "Could not find axis " << varName << endl;
		throw std::runtime_error("");
	}
	int dim = contribution->getContent()->GetListOfAxes()->IndexOf(axis);
	
	m_histogram = contribution->getContent()->Projection(dim, "E O");
	
	if(contribution->getContent(true)) {
		TH1* histogramAbs = contribution->getContent(true)->Projection(dim, "E O");
		for(int i = 1; i <= m_histogram->GetXaxis()->GetNbins() + 1; ++i) {
			if(histogramAbs->GetBinContent(i) == 0) {
				continue;
			}
			double nominalWeightScale = abs(m_histogram->GetBinContent(i) / histogramAbs->GetBinContent(i));
			m_histogram->SetBinError(i, nominalWeightScale * m_histogram->GetBinError(i));
		}
	}
	
	for(auto &uncertainty : contribution->getUncertaintyMap()) {
		TH1* hProjection = uncertainty.second.second->Projection(dim, "E");
		hProjection->SetName(uncertainty.first);
		m_uncertainties.insert(make_pair(uncertainty.first, hProjection));
	}
	
	m_histogram->SetName(contribution->getName());
	TString title = contribution->isData()
		? contribution->getSelectionString()
		: contribution->getName();
	m_histogram->SetTitle(title);
	
	if(!m_source->isData()) {
		for(int i = 1; i <= m_histogram->GetXaxis()->GetNbins() + 1; ++i) {
			// Set negative bins to 0 (this can happen due to fake subtraction, negative MC weights etc.)
			if(!m_source->getAllowNegative() && m_histogram->GetBinContent(i) < 0) {
				m_histogram->SetBinContent(i, 0);
				// Also set negative uncertainties to 0 (would otherwise affect uncertainty bundling)
				for(auto &uncertainty : getUncertainties()) {
					if(uncertainty.second->GetBinContent(i) < 0) {
						uncertainty.second->SetBinContent(i, 0);
					}
				}
			}
			
			// Zerostat uncertainty for background and signal samples
			if(m_histogram->GetBinContent(i) == 0 && (m_histogram->GetBinError(i) == 0 || zerostat < m_histogram->GetBinError(i))) {
				m_histogram->SetBinError(i, zerostat);
			}
		}
	}
	
	m_contributions.insert(contribution);
}

PhysicsContributionProjection::~PhysicsContributionProjection() {
	/* no-op */
}

void PhysicsContributionProjection::scale(const double scale) {
	m_histogram->Scale(scale);
	for(auto &uncertainty : m_uncertainties) {
		uncertainty.second->Scale(scale);
	}
}
