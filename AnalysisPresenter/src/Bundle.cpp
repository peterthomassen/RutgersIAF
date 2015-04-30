#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TFile.h"
#include "TH1D.h"
#include "THnBase.h"
#include "TTree.h"

//#include "RutgersIAF/AnalysisPresenter/interface/BundleProjection.h"

using namespace std;

ClassImp(Bundle)

Bundle::Bundle() {
	/* no-op */
}

Bundle::Bundle(TString type, TString name, bool allowNegative, Int_t fillColor) : m_allowNegative(allowNegative), m_fillColor(fillColor), m_name(name), m_type(type) {
}

Bundle::~Bundle() {
}

bool Bundle::getAllowNegative() const {
	return m_allowNegative;
}

Int_t Bundle::getFillColor() const {
	return m_fillColor;
}

TString Bundle::getName() const {
	return m_name;
}

TString Bundle::getType(const bool detailed) const {
	if(detailed) {
		return m_type;
	}
	
	if(isData()) return "data";
	if(isBackground()) return "background";
	if(isSignal()) return "signal";
	
	throw std::runtime_error("should never make it here");
}

bool Bundle::isBackground() const {
	return m_type.BeginsWith("background");
}

bool Bundle::isData() const {
	return m_type.BeginsWith("data");
}

bool Bundle::isSignal() const {
	return m_type.BeginsWith("signal");
}

void Bundle::setFillColor(const Int_t fillColor) {
	m_fillColor = fillColor;
}
