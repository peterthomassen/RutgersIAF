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
	if(projections.size() == 0) {
		cerr << "Error: no projections in " << bundle->getName() << " bundle" << endl;
	}
	assert(projections.size() > 0);
	
	m_histogram = (TH1D*)projections[0]->getHistogram()->Clone();
	m_histogram->Reset();
	m_histogram->SetTitle(bundle->getName());
	
	for(int i = 1; i <= m_histogram->GetNbinsX() + 1; ++i) {
		double zerostat = 0;
		double stat2 = 0;
		
		for(auto &projection : projections) {
			double projectionContent = projection->getHistogram()->GetBinContent(i);
			double projectionError = projection->getHistogram()->GetBinError(i);
			
			if(projectionContent == 0) {
				if(zerostat == 0 || zerostat > projectionError) {
					zerostat = projectionError;
				}
			} else {
				m_histogram->SetBinContent(i, m_histogram->GetBinContent(i) + projectionContent);
				stat2 += pow(projectionError, 2);
			}
		}
		
		m_histogram->SetBinError(i, (m_histogram->GetBinContent(i) == 0) ? zerostat : sqrt(stat2));
	}
	
	for(auto &projection : projections) {
		for(auto &uncertainty : projection->getUncertainties()) {
			if(m_uncertainties.find(uncertainty.first) == m_uncertainties.end()) {
				m_uncertainties.insert(make_pair(uncertainty.first, (TH1D*)uncertainty.second->Clone()));
			} else {
				for(int i = 1; i <= uncertainty.second->GetNbinsX() + 1; ++i) {
					double value = m_uncertainties[uncertainty.first]->GetBinContent(i);
					value += uncertainty.second->GetBinContent(i);
					m_uncertainties[uncertainty.first]->SetBinContent(i, value);
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
