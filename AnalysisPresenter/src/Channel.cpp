#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContributionProjection.h"

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

Channel::Channel(Assembler* assembler, TString title) : AssemblerProjection(assembler, "_", false) {
	m_title = title; // needs to be specified here because inherited variable is not visible in initialization list
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

double Channel::get(TString type, TString correlationClass) const {
	return getBin(type, 1, correlationClass);
}

double Channel::getStat(TString type) const {
	return getBinStat(type, 1);
}

double Channel::getStat(TString type, TString correlationClass) const {
	return getBinStat(type, 1, correlationClass);
}

double Channel::getSyst(TString type) const {
	return getBinSyst(type, 1);
}

double Channel::getSyst(TString type, TString name) const {
	return getBinSyst(type, 1, name);
}

double Channel::getSyst(TString type, TString name, TString correlationClass) const {
	return getBinSyst(type, 1, name, correlationClass);
}
