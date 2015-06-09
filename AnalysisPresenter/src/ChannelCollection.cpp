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

bool ChannelCollection::addChannel(Channel* channel) {
	auto ins = m_channels.insert(channel);
	if(!ins.second) {
		cout << "ChannelCollection " << getName() << ": not adding channel " << channel->getName() << " twice" << endl;
		return false;
	}
	
	unsigned int nDuplicates = 0;
	
	auto meta = channel->getMeta();
	for(auto &metadata : meta) {
		auto insEvent = m_meta["data"].insert(metadata);
		if(!insEvent.second) {
			cout << "Warning: duplicate event in " << getName() << ": " << metadata.event << " " << metadata.run << " " << metadata.lumi << " " << metadata.fakeIncarnation << endl;
			++nDuplicates;
		}
	}
	return true;
}

std::vector<TString> ChannelCollection::getCollectionBundleNames(TString type) const {
	assert(CollectionHas(type));
	std::vector<TString> bundleNames;
	bundleNames.clear();
	std::vector<TString> ChannelBundles;
	for(auto &channel : getChannels()) {
		ChannelBundles.clear();
		ChannelBundles = channel->getChannelBundleNames(type);
		for (int i = 0; i < abs(ChannelBundles.size()); i++) {
			bool duplicateBundle = false;
			for (int j = 0; j < abs(bundleNames.size()); j++) {
				 if (bundleNames[j]==ChannelBundles[i]) {
					 duplicateBundle = true;
					 break;
				 }
					 
			}
			if (duplicateBundle == false) bundleNames.push_back(ChannelBundles[i]);
		}
	}
	return bundleNames;
}

std::set<TString> ChannelCollection::getCollectionUncertainties() const {
	std::set<TString> uncertaintyNames;
	uncertaintyNames.clear();
	std::set<TString> ChannelUncertainties;
	for(auto &channel : getChannels()) {
		ChannelUncertainties.clear();
		ChannelUncertainties = channel->getChannelUncertainties();
		for (auto &uncertainties : ChannelUncertainties) {
			bool duplicateUncertainty = false;
			for (std::set<TString>::iterator it2=uncertaintyNames.begin(); it2!=uncertaintyNames.end(); ++it2) {
				 if (uncertainties==*it2) {
					 duplicateUncertainty = true;
					 break;
				 }
			}
			if (duplicateUncertainty == false) uncertaintyNames.insert(uncertainties);
		}	
	}
	return uncertaintyNames;
}

bool ChannelCollection::CollectionHas(TString type) const {
	bool has = true;
	
	for(auto &channel : getChannels()) {
		has = channel->ChannelHas(type);
		
		if (has==false) break;
	}
	
	return has;
}

bool ChannelCollection::CollectionHas(TString type, TString bundleName) const {
	bool has = true;
	
	for(auto &channel : getChannels()) {
		has = channel->ChannelHas(type, bundleName);
		
		if (has==false) break;
	}
	
	return has;	
}

void ChannelCollection::datacard(TString datacardName, bool isData, double statFactor, double systFactor) {

	std::cout << "Creating datacard..." << std::endl;
	
	if(!CollectionHas("signal")) {
		std::cout << "*** Error: No signal added -> BREAK! ***" << std::endl;
		return;
	}
	
	auto channels = getChannels();
	int NumberChannels = channels.size();
	
	std::vector<TString> BundlesSignal;
	BundlesSignal = getCollectionBundleNames("signal");
	std::vector<TString> BundlesSignalName;
	BundlesSignalName = getCollectionBundleNames("signal");
	int NumberBundlesSignal = BundlesSignal.size();
	
	std::vector<TString> BundlesBckgrd;
	BundlesBckgrd = getCollectionBundleNames("background");
	std::vector<TString> BundlesBckgrdName;
	BundlesBckgrdName = getCollectionBundleNames("background");
	int NumberBundlesBackgrd = BundlesBckgrd.size();

	
	//Create datacard
	ofstream datacard;
	TString basicName = "/datacard_";
	TString endName = ".txt";
	TString completeName = "";
	TString directory = "";
	char buffer[1024]; 
	if(getcwd(buffer, 1024) == NULL ) 
		perror("***Directory Error***");  
	directory = buffer;
	completeName = directory + basicName + m_name + "_" + datacardName + endName;
	datacard.open(completeName);	
	datacard << std::fixed << std::setprecision(0);
	datacard << "#Datacard Version 2.0" << '\n' << "#Jun 2015" << '\n' << '\n';
	datacard << "imax " << NumberChannels << " number of channels" << '\n' << "jmax " << NumberBundlesBackgrd+NumberBundlesSignal - 1 << " number of background" << '\n' << "kmax " << getCollectionUncertainties().size() + NumberChannels*(NumberBundlesBackgrd+NumberBundlesSignal) << " number nuisance parameters" << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	datacard << "Observation";
	
	//Calculate values for datacard
	if (isData) {
	
		for (auto &channel : channels) {
		
			double contentData = channel->get("data");
			datacard << '\t' << contentData;
		}
	}
	else {
		for(auto &channel : channels) {	
	
			double contentData = channel->get("background");
			datacard << '\t' << contentData;
		}
	}
	datacard << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	datacard << "bin\t";
	for(auto &channel : channels) {	
	
		for (int j = 0; j < (NumberBundlesSignal + NumberBundlesBackgrd); j++) {
			datacard << '\t' << channel->getName();
		}
	}
	datacard << std::fixed << std::setprecision(3);
	datacard << '\n';
	datacard << "process\t";
	for(int i = 0; i < NumberChannels; i++) {	
	
		for (int j = 0; j < NumberBundlesSignal; j++) {
		
			if(BundlesSignal[j]=="") {
				datacard << '\t' << "remain_signal";
			}
			else {
				BundlesSignalName[j].ReplaceAll(" ", "_");
				datacard << '\t' << "signal_" << BundlesSignalName[j];
			}
		}
		
		for (int j = 0; j < NumberBundlesBackgrd; j++) {
		
			if(BundlesBckgrd[j]=="") {
				datacard << '\t' << "remain_bckgrd";
			}
			else {
				BundlesBckgrdName[j].ReplaceAll(" ", "_");
				datacard << '\t' << "bckgrd_" << BundlesBckgrdName[j];
			}
		}
			
	}
	datacard << '\n';
	datacard << "process\t";
	for(int i = 0; i < NumberChannels; i++) {	
	
		for (int j = 0; j < NumberBundlesSignal; j++) {
		
			datacard << '\t' << (NumberBundlesSignal - j)*(-1)+1;
		}
		
		for (int j = 0; j < NumberBundlesBackgrd; j++) {
		
			datacard << '\t' << j + 1;
		}
		
	}
	datacard << '\n';
	datacard << "rate\t";
	for(auto &channel : channels) {
	
		for (int j = 0; j < NumberBundlesSignal; j++) {
		
			double contentSignal = channel->get("signal", BundlesSignal[j]);
			if (contentSignal < 0.001) {contentSignal = 0.001;}				
			datacard << '\t' << contentSignal;
		}
		
		for (int j = 0; j < NumberBundlesBackgrd; j++) {
		
			double contentBackground = channel->get("background", BundlesBckgrd[j]);
			if (contentBackground < 0.001) {contentBackground = 0.001;}
			datacard << '\t' << contentBackground;
		}
	}
	datacard << '\n';
	datacard << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';
	
	for (auto &uncertainty : getCollectionUncertainties()) {
		
		TString UncertaintyName = uncertainty;
		UncertaintyName.ReplaceAll(" ", "_");
		datacard << UncertaintyName << " lnN";
		
		for(auto &channel : channels) {
		
			for (int j = 0; j < NumberBundlesSignal; j++) {
			
				double contentSignalSyst = channel->getSyst("signal", uncertainty, BundlesSignal[j]);		
				double contentSignal = channel->get("signal", BundlesSignal[j]);
				if (contentSignal < 0.001) {contentSignal = 0.001;}					
				double ratio = systFactor * contentSignalSyst/contentSignal;
				datacard << '\t' << 1 + ratio;
			}

			for (int j = 0; j < NumberBundlesBackgrd; j++) {
			
				double contentBackgroundSyst = channel->getSyst("background", uncertainty, BundlesBckgrd[j]);		
				double contentBackground = channel->get("background", BundlesBckgrd[j]);
				if (contentBackground < 0.001) {contentBackground = 0.001;}				
				double ratio = systFactor * contentBackgroundSyst/contentBackground;
				datacard << '\t' << 1 + ratio;
			}
		}
		datacard << '\n';
	}
		
	int NumberBins = (NumberBundlesBackgrd + NumberBundlesSignal)*NumberChannels;
	double StatUncertainty[NumberBins][NumberBins];
	
	for (int n = 0; n < NumberBins; n++) {
	
		for (int m = 0; m < NumberBins; m++) {
		
			StatUncertainty[n][m] = 1;
		}
	}
	
	int LoopIndex = 0;
	
	for(auto &channel : channels) {
	
		for (int j = 0; j < NumberBundlesSignal; j++) {
		
			double contentSignalStat = channel->getStat("signal", BundlesSignal[j]);		
			double contentSignal = channel->get("signal", BundlesSignal[j]);
			if (contentSignal < 0.001) {contentSignal = 0.001;}				
			double ratio = statFactor * contentSignalStat/contentSignal;
			StatUncertainty[LoopIndex][LoopIndex] += ratio;
			LoopIndex++;
		}
		
		for (int j = 0; j < NumberBundlesBackgrd; j++) {
		
			double contentBackgroundStat = channel->getStat("background", BundlesBckgrd[j]);		
			double contentBackground = channel->get("background", BundlesBckgrd[j]);
			if (contentBackground < 0.001) {contentBackground = 0.001;}
			double ratio = statFactor * contentBackgroundStat/contentBackground;
			StatUncertainty[LoopIndex][LoopIndex] += ratio;
			LoopIndex++;
		}
	}
	
	for (int n = 0; n < NumberBins; n++) {
	
		datacard << "Stat" << n + 1 << " lnN";
	
		for (int m = 0; m < NumberBins; m++) {
		
			datacard << '\t' << StatUncertainty[n][m];
		}
		
		datacard << '\n';
	}
	
	datacard.close();
}


std::set<Channel*> ChannelCollection::getChannels() const {
	return m_channels;
}

std::set<PhysicsContribution::metadata_t> ChannelCollection::getMeta(TString type) const {
	return m_meta.at(type);
}

TString ChannelCollection::getName() const {
	return m_name;
}

void ChannelCollection::printMeta(TString type) const {
	for(auto &meta : getMeta(type)) {
		cout << meta.event << " " << meta.run << " " << meta.lumi << " " << meta.fakeIncarnation << endl;
	}
}