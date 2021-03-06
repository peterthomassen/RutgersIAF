#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TFile.h"
#include "THnBase.h"
#include "TTree.h"

#include "RutgersIAF/AnalysisPresenter/interface/BaseBundleProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/BundleProjection.h"

using namespace std;

ClassImp(Bundle)

Bundle::Bundle() {
	/* no-op */
}

Bundle::Bundle(TString type, TString name, bool allowNegative, Int_t fillColor) : BaseBundle(type, name, allowNegative, (fillColor < 0 && type.BeginsWith("signal")) ? kPink : fillColor) {
}

Bundle::~Bundle() {
}

bool Bundle::addComponent(BaseBundle* component) {
	if(std::find(m_components.begin(), m_components.end(), component) != m_components.end()) {
		cerr << "Warning: Trying to add component " << component->getName() << " to bundle " << getName() << " twice" << endl;
		throw std::runtime_error("oops");
		return false;
	}
	
	if(getType() != component->getType()) {
		cerr << "Warning: Trying to add component " << component->getName() << " of type " << component->getType() << " to bundle " << getName() << " which is of type " << getType() << endl;
		throw std::runtime_error("oops");
		return false;
	}
	
	m_components.push_back(component);
	return true;
}

std::vector<BaseBundle*> Bundle::getComponents() const {
	return m_components;
}

void Bundle::print(int level) const {
	std::string prefix = std::string(2 * level, ' ');
	cout << prefix << getName() << " (" << m_components.size() << ")" << endl;
	for(auto &component : m_components) {
		component->print(level + 1);
	}
}

BaseBundleProjection* Bundle::project(std::vector<std::string> varNames, const bool binForOverflow) const {
	BundleProjection* projection = new BundleProjection(this, varNames);
	
	if(binForOverflow) {
		projection->incorporateOverflow();
	}
	
	if(m_fillColor >= 0) {
		projection->getHistogram()->SetFillColor(m_fillColor);
	}
	
	return projection;
}
