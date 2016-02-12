#include <iostream>
#include <TH1.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

// Load library, see https://root.cern.ch/phpBB2/viewtopic.php?f=3&t=19471
namespace {
  int loadMyLibraryTriggerFunc() {
    gSystem->Load("libRutgersIAFAnalysisPresenter.so");
    return 0;
  }
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void applyUncertaintiesAndScaleFactors(Assembler* assembler, PhysicsContribution* contribution) {
	if(!contribution->isMC()) {
		return;
	}
	
	// do some stuff
}

void init(Assembler* assembler) {
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
	
	// create some bundles
}

void prepare(Assembler* assembler) {
	// define bundle hierarchy
	
	if(assembler->getDefaultBundle()) {
		assembler->getDefaultBundle()->print();
	}
}

void setupData(Assembler* assembler) {
	PhysicsContribution* data = new PhysicsContribution("data", "/cms/thomassen/2015/Analysis/data/results/20151203_data.root", 2198, "2.20/fb@13TeV");
	data->addWeight("TRIGGERACCEPT");
	
	std::vector<string> vetoFilenames = {
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/csc2015_Dec01.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/ecalscn1043093_Dec01.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/badResolutionTrack_Jan13.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/muonBadTrack_Jan13.txt",
	};
	
	for(auto vetoFilename : vetoFilenames) {
		cout << "adding vetos from " << vetoFilename << " ..." << flush;
		int nDuplicates = 0;
		ifstream ifile(vetoFilename);
		std::string line;
		while(getline(ifile, line)) {
			if(line.size() == 0 || line.at(0) == '#') {
				continue;
			}
			
			if(!data->addVetoEvent(line)) {
				++nDuplicates;
			}
		}
		ifile.close();
		cout << " (" << nDuplicates << " duplicates)" << endl;
	}
	
	assembler->addContribution(data);
	
	// Pile-up weights
	cout << "Notice: Applying pileup weights" << endl;
	TFile* f = new TFile("/cms/thomassen/2015/Analysis/data/DataPileup_2015-12-18.root");
	if(f->IsZombie()) {
		throw std::runtime_error("couldn't open pileup file");
	}
	TH1D* hPileup = (TH1D*)f->Get("pileup");
	TH1D* hPileupUnc = 0;
	
	if(assembler->getMode("fullPrecision")) {
		TFile* fUnc = new TFile("/cms/thomassen/2015/Analysis/data/DataPileup+5%_2015-12-18.root");
		if(fUnc->IsZombie()) {
			throw std::runtime_error("couldn't open pileup uncertainty file");
		}
		hPileupUnc = (TH1D*)fUnc->Get("pileup");
	} else {
		cout << "Notice: Not applying MET smearing and pile-up. Set fullPrecision mode to do so." << endl;
	}
	assembler->setPileupHistogram(hPileup, hPileupUnc);
}

void setupBackgroundMC(Assembler* assembler, bool dilep = false) {
	// Filenames are usually prefix + sampleName + infix + suffix
	std::string prefix = "/cms/thomassen/2015/Analysis/simulation/results/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".simulation.root";
	
	std::vector<PhysicsContribution*> mc;
	
	// Add backgrounds
	
	for(auto &contribution : mc) {
		contribution->addWeight("WEIGHT[0]");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		applyUncertaintiesAndScaleFactors(assembler, contribution);
		assembler->addContribution(contribution);
	}
}

void setupBackgroundDD(Assembler* assembler) {
}

void setupFakeRates(Assembler* assembler) {
}
