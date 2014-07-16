#include <vector>

void lightFakeRates() {
	gSystem->Load("libRutgersIAF2012AnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For fake rate measurement
	std::string varexp1 = "NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,100,2}";
	std::string varexp2 = varexp1 + std::string(":nTrackFakeElectrons{0,3}:nTrackFakeMuons{0,3}:nTrackFakePosElectrons{0,3}:nTrackFakePosMuons{0,3}:nTrackFakeNegElectrons{0,3}:nTrackFakeNegMuons{0,3}");
	
	// Global cuts, if desired
	TString selection1 = "NOTTRILEPTONONZ";
	selection1 += " && NLEPTONS == 3";
	selection2 = selection1 + TString(" && nPhotonFakeElectrons == 0 && nPhotonFakeMuons == 0");
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler1 = new Assembler;
	init(assembler1);
	setupData(assembler1);
	setupBackgroundMC(assembler1);
	setupFakeRates(assembler1);
	assembler1->setDebug(true);
	assembler1->process(varexp1, selection1);
	
	Assembler* assembler2 = new Assembler;
	init(assembler2);
	setupData(assembler2, true);
	assembler2->setDebug(true);
	assembler2->process(varexp2, selection2);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	std::vector<Assembler*> assemblers;
	assemblers.push_back(assembler1);
	assemblers.push_back(assembler2);
	
	std::vector<char*> cuts;
	cuts.push_back("assembler->setRange(\"MET\", 0, 50, false);");
	cuts.push_back("assembler->setRange(\"MET\", 50, 100, false);");
	cuts.push_back("assembler->setRange(\"HT\", 0, 200, false);");
	cuts.push_back("assembler->setRange(\"HT\", 200);");
	
	// Measure light lepton fake rates
	for(int nMuons = 3; nMuons >= 0; --nMuons) {
		bool muFake = (nMuons % 2 == 1);
		std::string fakeName = muFake ? "muon" : "electron";
		for(int charge = -1; charge <= 1; charge += 2) {
			for(size_t j = 0; j < cuts.size(); ++j) {
				cout << endl;
				cout << "=== Now computing " << fakeName << " (charge: " << charge << ") fake rate for: nMuons = " << nMuons << ", nElectrons = " << (3 - nMuons) << ", " << cuts[j] << endl;
				double data = 0, dataErr = 0, mc = 0, mcErr = 0, fake = 0, fakeErr = 0;
				for(size_t i = 1; i <= 2; ++i) {
					Assembler* assembler = assemblers[i-1];
					if(i == 2) {
						if(muFake) {
							assembler->setRange("nTrackFakeElectrons", 0, 0);
							assembler->setRange("nTrackFakeMuons", 1, 1);
							if(charge > 0) {
								assembler->setRange("nTrackFakePosMuons", 1, 1);
							} else if(charge < 0) {
								assembler->setRange("nTrackFakeNegMuons", 1, 1);
							}
						} else {
							assembler->setRange("nTrackFakeMuons", 0, 0);
							assembler->setRange("nTrackFakeElectrons", 1, 1);
							if(charge > 0) {
								assembler->setRange("nTrackFakePosElectrons", 1, 1);
							} else if(charge < 0) {
								assembler->setRange("nTrackFakeNegElectrons", 1, 1);
							}
						}
					}
					
					assembler->setRange();
//					assembler->setRange("NGOODMUONS", nMuons, nMuons);
//					assembler->setRange("NGOODELECTRONS", 3 - nMuons, 3 - nMuons);
					assembler->setRange("NPOSGOODMUONS", nMuons / 2 + (muFake && charge > 0));
					assembler->setRange("NNEGGOODMUONS", nMuons / 2 + (muFake && charge < 0));
					assembler->setRange("NPOSGOODELECTRONS", (3 - nMuons) / 2 + (!muFake && charge > 0));
					assembler->setRange("NNEGGOODELECTRONS", (3 - nMuons) / 2 + (!muFake && charge < 0));
					assembler->setRange("ONZ", 1, 1);
					assembler->setRange("NBJETSCSVM", 0, 0);
					gROOT->ProcessLineFast(cuts[j]);
					Projection* projection = assembler->project("ONZ", true);
					if(i == 1) {
						data = projection->getHistogram("data")->IntegralAndError(1, projection->getHistogram("data")->GetNbinsX(), dataErr);
						mc = projection->getHistogram("background")->IntegralAndError(1, projection->getHistogram("data")->GetNbinsX(), mcErr);
					}
					if(i == 2) {
						fake = projection->getHistogram("data")->IntegralAndError(1, projection->getHistogram("data")->GetNbinsX(), fakeErr);
					}
					//projection->print();
				}
				cout << mc << "/" << mcErr << endl;
				cout << data << "/" << dataErr << endl;
				cout << fake << "/" << fakeErr << endl;
				double fakeRate = (data - mc) / fake;
				double fakeRateErr = sqrt(dataErr*dataErr + pow(fakeErr*(data-mc)/fake, 2) + mcErr*mcErr) / fake;
				printf("fake rate: %.4f ± %.4f (%.0f%%)\n", fakeRate, fakeRateErr, fakeRateErr / fakeRate * 100);
			}
		}
	}
	
	delete assembler1;
	delete assembler2;
}
