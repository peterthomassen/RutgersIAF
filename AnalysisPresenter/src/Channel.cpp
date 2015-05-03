#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"

#include <assert.h>
#include <boost/bind.hpp>
#include <cmath>
#include <exception>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h> 
#include <unistd.h>
#include <iomanip>
#include <stdlib.h>

#include "RutgersIAF/debug.h"

using namespace std;

ClassImp(Channel)

Channel::Channel(Assembler* assembler, TString name) : AssemblerProjection(assembler, "_", false) {
	m_name = name; // needs to be specified here because inherited variable is not visible in initialization list
}

Channel::Channel() {
	/* no-op */
}

Channel::~Channel() {
	/* no-op */
}

double Channel::get(TString type) const {
	return getBin(type, 1);
}

TString Channel::getName() const {
	return m_name;
}

double Channel::getStat(TString type) const {
	return getBinStat(type, 1);
}

double Channel::getSyst(TString type) const {
	return getBinSyst(type, 1);
}

double Channel::getSyst(TString type, TString name) const {
	return getBinSyst(type, 1, name);
}

AssemblerProjection* Channel::project(const char* name, const bool binForOverflow) {
	auto ranges = m_assembler->getRanges();
	m_assembler->setRanges(m_ranges);
	auto projection = new AssemblerProjection(m_assembler, name, binForOverflow);
	m_assembler->setRanges(ranges);
	
	return projection;
}
