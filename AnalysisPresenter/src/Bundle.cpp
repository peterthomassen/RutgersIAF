#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TFile.h"
#include "TH1D.h"
#include "THnBase.h"
#include "TTree.h"

using namespace std;

ClassImp(Bundle)

Bundle::Bundle() {
	/* no-op */
}

Bundle::Bundle(TString type, TString name, bool allowNegative, Int_t fillColor) : BaseBundle(type, name, allowNegative, fillColor) {
}

Bundle::~Bundle() {
}

bool Bundle::addComponent(BaseBundle* component) {
	if(std::find(m_components.begin(), m_components.end(), component) != m_components.end()) {
		cerr << "Warning: Trying to add component " << component->getName() << " to bundle " << getName() << " twice" << endl;
		throw std::runtime_error("oops");
		return false;
	}
	
	m_components.push_back(component);
	return true;
}
