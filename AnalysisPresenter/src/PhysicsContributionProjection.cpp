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

PhysicsContributionProjection::PhysicsContributionProjection(const PhysicsContribution* contribution, std::vector<std::string> varNames, const double zerostat) : BaseBundleProjection(contribution, varNames) {
	assert(m_varNames.size() <= 2);
	
	TAxis* axis1 = (TAxis*)contribution->getContent()->GetListOfAxes()->FindObject(m_varNames.size() ? m_varNames[0].c_str() : "_");
	if(!axis1) {
		cerr << "Could not find axis " << m_varNames[0] << endl;
		throw std::runtime_error("");
	}
	int dim1 = contribution->getContent()->GetListOfAxes()->IndexOf(axis1);
	
	int dim2 = -1;
	if(m_varNames.size() <= 1) {
		m_histogram = contribution->getContent()->Projection(dim1, "E O");
	} else if(m_varNames.size() == 2) {
		TAxis* axis2 = (TAxis*)contribution->getContent()->GetListOfAxes()->FindObject(m_varNames[1].c_str());
		if(!axis2) {
			cerr << "Could not find axis " << m_varNames[1] << endl;
			throw std::runtime_error("");
		}
		dim2 = contribution->getContent()->GetListOfAxes()->IndexOf(axis2);
		
		// Note that the order here is y, x
		m_histogram = (TH1*)contribution->getContent()->Projection(dim2, dim1, "E O");
	}
	
	if(contribution->getContent(true)) {
		TH1* histogramAbs = 0;
		if(m_varNames.size() <= 1) {
			histogramAbs = contribution->getContent(true)->Projection(dim1, "E O");
		} else if(m_varNames.size() == 2) {
			// Note that the order here is y, x
			histogramAbs = (TH1*)contribution->getContent(true)->Projection(dim2, dim1, "E O");
		}
		for(int i = 0; i < m_histogram->GetNcells(); ++i) {
			if(histogramAbs->GetBinContent(i) == 0) {
				continue;
			}
			double nominalWeightScale = abs(m_histogram->GetBinContent(i) / histogramAbs->GetBinContent(i));
			m_histogram->SetBinError(i, nominalWeightScale * m_histogram->GetBinError(i));
		}
	}
	
	for(auto &uncertainty : contribution->getUncertaintyMap()) {
		TH1* hProjection = 0;
		if(m_varNames.size() <= 1) {
			hProjection = uncertainty.second.second->Projection(dim1, "E");
		} else if(m_varNames.size() == 2) {
			// Note that the order here is y, x
			hProjection = (TH1*)uncertainty.second.second->Projection(dim2, dim1, "E");
		}
		hProjection->SetName(uncertainty.first);
		m_uncertainties.insert(make_pair(uncertainty.first, hProjection));
	}
	
	m_histogram->SetName(contribution->getName());
	TString title = contribution->isData()
		? contribution->getSelectionString()
		: contribution->getName();
	m_histogram->SetTitle(title);
	
	if(!m_source->isData()) {
		for(int i = 0; i < m_histogram->GetNcells(); ++i) {
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
