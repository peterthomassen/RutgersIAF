#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"

#include <assert.h>
#include <exception>

#include "RutgersIAF/debug.h"

using namespace std;

ClassImp(Channel)

Channel::Channel(Assembler* assembler, TString name) : AssemblerProjection(assembler, std::vector<std::string>(), false) {
	m_name = name;
}

Channel::Channel(const Channel* parent, Bundle* bundle, TString missingName) : AssemblerProjection(parent, bundle, missingName) {
}

Channel::Channel() {
	/* no-op */
}

Channel::~Channel() {
	/* no-op */
}

Channel* Channel::bundle(Bundle* bundle, TString missingName) {
	return bundle ? new Channel(this, bundle, missingName) : this;
}

void Channel::datacard(TString datacardName, bool isData, double statFactor, double systFactor) {
	ChannelCollection* cc = new ChannelCollection(datacardName.Length() > 0 ? datacardName : this->getName());
	cc->addChannel(this);
	cc->datacard(cc->getName(), isData, statFactor, systFactor);
}

double Channel::get(TString type) const {
	return getBin(type, 1);
}

double Channel::get(TString type, TString bundleName) const {
	return getBin(type, 1, bundleName);
}

TString Channel::getName() const {
	return m_name;
}

double Channel::getStat(TString type) const {
	return getBinStat(type, 1);
}

double Channel::getStat(TString type, TString bundleName) const {
	return getBinStat(type, 1, bundleName);
}

double Channel::getSyst(TString type) const {
	return getBinSyst(type, 1);
}

double Channel::getSyst(TString type, TString name) const {
	return getBinSyst(type, 1, name);
}

double Channel::getSyst(TString type, TString name, TString bundleName) const {
	return getBinSyst(type, 1, name, bundleName);
}

AssemblerProjection* Channel::project(std::vector<std::string> varNames, const bool binForOverflow) {
	auto ranges = m_assembler->getRanges();
	m_assembler->setRanges(m_ranges);
	auto projection = new AssemblerProjection(m_assembler, varNames, binForOverflow);
	m_assembler->setRanges(ranges);
	
	return projection;
}
