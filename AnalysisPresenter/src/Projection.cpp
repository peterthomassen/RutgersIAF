#include "RutgersIAF2012/AnalysisPresenter/interface/Projection.h"

#include <assert.h>
#include <exception>

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(Projection)

Projection::Projection(TString name, bool binForOverflow) : m_binForOverflow(binForOverflow), m_name(name) {
}

Projection::Projection() {
	/* no-op */
}

Projection::~Projection() {
	for(auto &component : m_components) {
		delete component.second.first;
		delete component.second.second;
	}
}

void Projection::add(TString type, THStack* content, THStack* contentSyst) {
	if(m_components.find(type) != m_components.end()) {
		throw std::runtime_error("overwriting projection components not supported");
	}
	m_components.insert(make_pair(type, make_pair(content, contentSyst)));
}

double Projection::getBin(TString type, int i) const {
	TObjArray* stack = m_components.find(type)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinContent(i) : 0;
}

double Projection::getBinStat(TString type, int i) const {
	TObjArray* stack = m_components.find(type)->second.first->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinError(i) : 0;
}

double Projection::getBinSyst(TString type, int i) const {
	TObjArray* stack = m_components.find(type)->second.second->GetStack();
	return stack ? ((TH1*)stack->Last())->GetBinContent(i) : 0;
}

bool Projection::has(TString type) const {
	return (m_components.find(type) != m_components.end());
}

bool Projection::hasOverflowIncluded() const {
	return m_binForOverflow;
}
