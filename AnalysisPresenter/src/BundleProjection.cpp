#include "RutgersIAF/AnalysisPresenter/interface/BundleProjection.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TH1D.h"
#include "THnBase.h"

#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/BaseBundleProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

using namespace std;

ClassImp(BundleProjection)

BundleProjection::BundleProjection() {
	/* no-op */
}

BundleProjection::BundleProjection(const Bundle* bundle, const char* varName) : BaseBundleProjection(bundle, varName) {
	std::vector<BaseBundleProjection*> projections;
	for(auto &component : bundle->getComponents()) {
		// Don't make overflow bin visible; this is handled by the code that called us (it will call includeOverflow() on our histogram)
		BaseBundleProjection* projection = component->project(varName, false);
		for(auto contribution : projection->getPhysicsContributions()) {
			auto insPair = m_contributions.insert(contribution);
			if(!insPair.second) {
				cerr << "Hierarchy for bundle " << bundle->getName() << " contains contribution " << contribution->getName() << " twice" << endl;
				throw std::runtime_error("");
			}
		}
		projections.push_back(projection);
	}
	assert(projections.size() > 0);
	
	m_histogram = (TH1D*)projections[0]->getHistogram()->Clone();
	m_histogram->Reset();
	m_histogram->SetTitle(bundle->getName());
	
	for(auto &projection : projections) {
		m_histogram->Add(projection->getHistogram());
		
		for(auto &uncertainty : projection->getUncertainties()) {
			if(m_uncertainties.find(uncertainty.first) == m_uncertainties.end()) {
				m_uncertainties.insert(make_pair(uncertainty.first, (TH1D*)uncertainty.second->Clone()));
			} else {
				for(int j = 1; j <= uncertainty.second->GetNbinsX() + 1; ++j) {
					double value = m_uncertainties[uncertainty.first]->GetBinContent(j);
					value = sqrt(value*value + pow(uncertainty.second->GetBinContent(j), 2));
					m_uncertainties[uncertainty.first]->SetBinContent(j, value);
				}
			}
		}
	}
	
	if(!m_source->isData()) {
		for(int i = 1; i <= m_histogram->GetXaxis()->GetNbins() + 1; ++i) {
			// Set negative bins to 0 (this can happen due to fake subtraction etc.)
			if(!m_source->getAllowNegative() && m_histogram->GetBinContent(i) < 0) {
				m_histogram->SetBinContent(i, 0);
			}
		}
	}
}

BundleProjection::~BundleProjection() {
	/* no-op */
}
