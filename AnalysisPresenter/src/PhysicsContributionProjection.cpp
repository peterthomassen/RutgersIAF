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

PhysicsContributionProjection::PhysicsContributionProjection(const PhysicsContribution* contribution, const char* varName, const std::map<TString, THnBase*>* uncertaintyMap, const double zerostat) : BaseBundleProjection(contribution, varName) {
	TAxis* axis = (TAxis*)contribution->getContent()->GetListOfAxes()->FindObject(varName);
	if(!axis) {
		cerr << "Could not find axis " << varName << endl;
		throw std::runtime_error("");
	}
	int dim = contribution->getContent()->GetListOfAxes()->IndexOf(axis);
	
	m_histogram = contribution->getContent()->Projection(dim, "E");
	m_histogram->SetName(contribution->getName());
	TString title = contribution->isData()
		? contribution->getSelectionString()
		: contribution->getName();
	m_histogram->SetTitle(title);
	
	if(!m_source->isData()) {
		for(int i = 1; i <= m_histogram->GetXaxis()->GetNbins() + 1; ++i) {
			// Set negative bins to 0 (this can happen due to fake subtraction etc.)
			if(!m_source->getAllowNegative() && m_histogram->GetBinContent(i) < 0) {
				m_histogram->SetBinContent(i, 0);
			}
			
			// Zerostat uncertainty for background and signal samples
			if(zerostat >= 0 && m_histogram->GetBinContent(i) == 0) {
				m_histogram->SetBinError(i, zerostat);
			}
		}
	}
	
	if(uncertaintyMap) {
		for(auto &uncertainty : *uncertaintyMap) {
			TH1D* hProjection = uncertainty.second->Projection(dim, "E");
			hProjection->SetName(uncertainty.second->GetName());
			m_uncertainties.insert(make_pair(uncertainty.first, hProjection));
		}
	}
	
	m_contributions.insert(contribution);
}

PhysicsContributionProjection::~PhysicsContributionProjection() {
	cout << "Called ~PhysicsContributionProjection() -- check that ~BaseBundleProjection() is also called" << endl;
}

void PhysicsContributionProjection::scale(const double scale) {
	m_histogram->Scale(scale);
	for(auto &uncertainty : m_uncertainties) {
		uncertainty.second->Scale(scale);
	}
}
