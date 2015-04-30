#include "RutgersIAF/AnalysisPresenter/interface/BaseBundle.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TFile.h"
#include "TH1D.h"
#include "THnBase.h"
#include "TTree.h"

using namespace std;

ClassImp(BaseBundle)

BaseBundle::BaseBundle() {
	/* no-op */
}

BaseBundle::BaseBundle(TString type, TString name, bool allowNegative, Int_t fillColor) : m_allowNegative(allowNegative), m_fillColor(fillColor), m_name(name), m_type(type) {
}

BaseBundle::~BaseBundle() {
}

bool BaseBundle::getAllowNegative() const {
	return m_allowNegative;
}

Int_t BaseBundle::getFillColor() const {
	return m_fillColor;
}

TString BaseBundle::getName() const {
	return m_name;
}

TString BaseBundle::getType(const bool detailed) const {
	if(detailed) {
		return m_type;
	}
	
	if(isData()) return "data";
	if(isBackground()) return "background";
	if(isSignal()) return "signal";
	
	throw std::runtime_error("should never make it here");
}

bool BaseBundle::isBackground() const {
	return m_type.BeginsWith("background");
}

bool BaseBundle::isData() const {
	return m_type.BeginsWith("data");
}

bool BaseBundle::isSignal() const {
	return m_type.BeginsWith("signal");
}

void BaseBundle::setFillColor(const Int_t fillColor) {
	m_fillColor = fillColor;
}
