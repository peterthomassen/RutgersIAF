#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"

#include <assert.h>
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

ClassImp(ChannelCollection)

ChannelCollection::ChannelCollection(TString name) : m_name(name) {
}

ChannelCollection::ChannelCollection() {
	/* no-op */
}

ChannelCollection::~ChannelCollection() {
	/* no-op */
}

bool ChannelCollection::addChannel(Channel* channel, bool allowDuplicates) {
	if(std::find(m_channels.begin(), m_channels.end(), channel) != m_channels.end()) {
		cout << "ChannelCollection " << getName() << ": not adding channel " << channel->getName() << " twice" << endl;
		return false;
	}
	
	m_channels.push_back(channel);
	
	unsigned int nDuplicates = 0;
	
	auto meta = channel->getMeta();
	for(auto &metadata : meta) {
		auto insEvent = m_meta["data"].insert(metadata);
		if(!insEvent.second) {
			cout << "Warning: Channel " << channel->getName() << " introduces duplicate event into ChannelCollection " << getName() << ": " << metadata.event << " " << metadata.run << " " << metadata.lumi << " " << metadata.fakeIncarnation << endl;
			++nDuplicates;
		}
	}
	
	if(!allowDuplicates) {
		assert(nDuplicates == 0);
	}
	
	return true;
}

void ChannelCollection::datacard(TString datacardName, bool isData, double statFactor, double systFactor) {
	std::cout << "Creating datacard " << datacardName << " ..." << std::endl;
	
	assert(getChannels().size() > 0);
	assert(has("signal"));
	
	double minYield = 0.001;
	
	std::vector<TString> bundleNamesSig = getBundleNames("signal");
	std::vector<TString> bundleNamesBkg = getBundleNames("background");
	
	// Create datacard
	ofstream datacard;
	datacard.open(datacardName);
	datacard << std::fixed << std::setprecision(0);
	
	datacard << "# Datacard " << datacardName << endl << endl;
	datacard << "imax " << getChannels().size() << " number of channels" << endl;
	datacard << "jmax " << bundleNamesBkg.size() + bundleNamesSig.size() - 1 << " number of backgrounds and signals minus 1" << endl;
	datacard << "kmax " << getUncertaintyNames().size() + getChannels().size() * (bundleNamesBkg.size() + bundleNamesSig.size()) << " number nuisance parameters" << endl;
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	datacard << "Observation";
	
	// Calculate values for datacard
	for(auto &channel : getChannels()) {
		int yield = channel->get(isData ? "data" : "background") + 0.5;
		datacard << '\t' << yield;
	}
	datacard << endl;
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	
	datacard << "bin\t";
	for(auto &channel : getChannels()) {
		for(size_t j = 0; j < bundleNamesSig.size() + bundleNamesBkg.size(); j++) {
			datacard << '\t' << channel->getName().Copy().ReplaceAll(" ", "_");
		}
	}
	datacard << std::fixed << std::setprecision(3);
	datacard << endl;
	
	datacard << "process\t";
	for(size_t i = 0; i < getChannels().size(); i++) {
		for(auto &bundleName : bundleNamesSig) {
			datacard << '\t' << "sig_" << bundleName.Copy().ReplaceAll(" ", "_");
		}
		
		for(auto &bundleName : bundleNamesBkg) {
			datacard << '\t' << "bkg_" << bundleName.Copy().ReplaceAll(" ", "_");
		}
	}
	datacard << endl;
	
	datacard << "process\t";


	for(size_t i = 0; i < getChannels().size(); i++) {
		for(Int_t n = 0; n < (Int_t)bundleNamesSig.size(); n++) {
			datacard << '\t' << (n - Int_t(bundleNamesSig.size())) + 1;

		}
		
		for(Int_t l = 0; l < (Int_t)bundleNamesBkg.size(); l++) {
			datacard << '\t' << l + 1;
		}
	}
	datacard << endl;
	
	datacard << "rate\t";
	for(auto &channel : getChannels()) {
		for(auto &bundleName : bundleNamesSig) {
			datacard << '\t' << max(minYield, channel->get("signal", bundleName));
		}
		
		for(auto &bundleName : bundleNamesBkg) {
			datacard << '\t' << max(minYield, channel->get("background", bundleName));
		}
	}
	datacard << endl;
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	
	for(auto &uncertaintyName : getUncertaintyNames()) {
		datacard << uncertaintyName.Copy().ReplaceAll(" ", "_") << " lnN";
		
		for(auto &channel : getChannels()) {
			for(auto &bundleName : bundleNamesSig) {
				double contentSignalSyst = channel->getSyst("signal", uncertaintyName, bundleName);
				double contentSignal = max(minYield, channel->get("signal", bundleName));
				double ratio = systFactor * contentSignalSyst/contentSignal;
				datacard << '\t' << max(0., 1 + ratio);
			}
			
			for(auto &bundleName : bundleNamesBkg) {
				double contentBackgroundSyst = channel->getSyst("background", uncertaintyName, bundleName);
				double contentBackground = max(minYield, channel->get("background", bundleName));
				double ratio = systFactor * contentBackgroundSyst/contentBackground;
				datacard << '\t' << max(0., 1 + ratio);
			}
		}
		datacard << endl;
	}
	
	int nYields = (bundleNamesBkg.size() + bundleNamesSig.size()) * getChannels().size();
	double statUncertainty[nYields];
	
	for(int n = 0; n < nYields; n++) {
	  statUncertainty[n] = 1;
	}
	
	int loopIndex = 0;
	
	for(auto &channel : getChannels()) {
		for(auto &bundleName : bundleNamesSig) {
			double contentSignalStat = channel->getStat("signal", bundleName);
			double contentSignal = max(minYield, channel->get("signal", bundleName));
			double ratio = statFactor * contentSignalStat/contentSignal;
			statUncertainty[loopIndex] += ratio;
			loopIndex++;
		}
		
		for(auto &bundleName : bundleNamesBkg) {
			double contentBackgroundStat = channel->getStat("background", bundleName);
			double contentBackground = max(minYield, channel->get("background", bundleName));
			double ratio = statFactor * contentBackgroundStat/contentBackground;
			statUncertainty[loopIndex] += ratio;
			loopIndex++;
		}
	}
	
	for(int n = 0; n < nYields; n++) {
		datacard << "Stat" << n + 1 << " lnN";
	
		for(int m = 0; m < nYields; m++) {
		  if(n == m)
			datacard << '\t' << statUncertainty[n];
		  else 
		    datacard << '\t' << 1;
		}
		
		datacard << endl;
	}
	
	datacard.close();
}

std::vector<TString> ChannelCollection::getBundleNames(TString type) const {
	assert(has(type));
	std::vector<TString> bundleNames;
	for(auto &channel : getChannels()) {
		for(auto &bundleName : channel->getBundleNames(type)) {
			if(std::find(bundleNames.begin(), bundleNames.end(), bundleName) == bundleNames.end()) {
				bundleNames.push_back(bundleName);
			}
		}
	}
	return bundleNames;
}

std::vector<Channel*> ChannelCollection::getChannels() const {
	return m_channels;
}

std::set<PhysicsContribution::metadata_t> ChannelCollection::getMeta(TString type) const {
	return m_meta.at(type);
}

TString ChannelCollection::getName() const {
	return m_name;
}

std::set<TString> ChannelCollection::getUncertaintyNames() const {
	std::set<TString> uncertaintyNames;
	for(auto &channel : getChannels()) {
		for(auto &uncertaintyName : channel->getUncertaintyNames()) {
			if(uncertaintyNames.find(uncertaintyName) == uncertaintyNames.end()) {
				uncertaintyNames.insert(uncertaintyName);
			}
		}
	}
	return uncertaintyNames;
}

bool ChannelCollection::has(TString type) const {
	for(auto &channel : getChannels()) {
		if(!channel->has(type)) {
			return false;
		}
	}
	return true;
}

bool ChannelCollection::has(TString type, TString bundleName) const {
	for(auto &channel : getChannels()) {
		if(!channel->has(type, bundleName)) {
			return false;
		}
	}
	return true;
}

void ChannelCollection::printMeta(TString type) const {
	for(auto &meta : getMeta(type)) {
		cout << meta.event << " " << meta.run << " " << meta.lumi << " " << meta.fakeIncarnation << endl;
	}
}
