#include <sys/stat.h>
#include <unistd.h>

void inclusive(TString ofname = "test.root") {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For inclusive table
	std::string varexp = "NLEPTONS{2,6}:MOSSF{11,131,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,200,4}:ST{0,1500,5}:MLEPTONS{81,101}";
	//std::string varexp = "NLEPTONS{2,6}:MOSSF{11,131,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,100,2}:MLEPTONS{81,101}";
	varexp += ":NPROMPTTRACKS7{0,100,1}:OSSFMAXMLL{11,131,36}:OSSFMINMLL{11,131,36}";
	
	// Global cuts, if desired
	//TString selection = "NOTTRILEPTONONZ";
	TString selection = "(NOSSF != 1 || NOTTRILEPTONONZ)";
	selection += " && (NLEPTONS != 3 || (NGOODMUONS == 3 || NGOODELECTRONS == 3 || abs(NPOSGOODMUONS+NPOSGOODELECTRONS-NNEGGOODMUONS-NNEGGOODELECTRONS) != 3))";
	//TString selection = "";
	
	
	///////////////////////
	// Signal definition //
	///////////////////////
	PhysicsContribution* signal = new PhysicsContribution("signal", "/cms/data25/maritader/sim/SeesawTo3Lminus_M-140_Complete.root", 126612. / 0.0669, "SeesawTo3Lminus_SyncedMC");
	signal->addWeight("WEIGHT");
	signal->addFlatUncertainty("dummy", 0.2);
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler(ofname, "RECREATE");
	init(assembler);
	setupData(assembler);
	setupBackgroundMC(assembler);
	setupBackgroundDD(assembler);
	//assembler->addContribution(signal); // It is important to add the signal before setting up the rake rates
	setupFakeRates(assembler);
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	assembler->save();
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("inclusive", 0755);
	chdir("inclusive");
	
/*	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 0, 81, false);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 101);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1HTgt200_MET.pdf");
	
	assembler->setRange("HT");
	assembler->setRange("MOSSF", 0, 81);
	assembler->setRange("MET", 0, 50);
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYl1MET0to50_HT.pdf");
	
	assembler->setRange("MOSSF", 101);
	assembler->setRange("MET", 0, 50);
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYh1MET0to50_HT.pdf");
	
	return;
	
	assembler->setRange();

	
	// ST plots
	chdir("ST");
	
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->project("ST", true)->print();
	assembler->project("ST", true)->plot(true, true)->SaveAs("L3DY0B0_ST.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->project("ST", true)->print();
	assembler->project("ST", true)->plot(true, true)->SaveAs("L3DYz1B0_ST.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 0, 0);
	assembler->project("ST", true)->print();
	assembler->project("ST", true)->plot(true, true)->SaveAs("L3DYn1B0_ST.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 0, 81, false);
	assembler->project("ST", true)->print();
	assembler->project("ST", true)->plot(true, true)->SaveAs("L3DYl1B0_ST.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 101);
	assembler->project("ST", true)->print();
	assembler->project("ST", true)->plot(true, true)->SaveAs("L3DYh1B0_ST.pdf");
	
	return;
*/	
	// Inclusive plots: 3L
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0B0HT0to200_MET.pdf");
	cout << ".........................." << endl;
	assembler->project("MET", true)->print();
	cout << ".........................." << endl;
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1B0HTgt200_MET.pdf");
	cout << ".........................." << endl;
	assembler->project("MET", true)->print();
	cout << ".........................." << endl;
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 0, 81, false);
//assembler->setRange("ONZ", 0, 0);
//assembler->setRange("OSSFMAXMLL", 0, 81, false);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1B0HT0to200_MET.pdf");
	assembler->project("MET", true)->print();
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1B1HTgt200_MET.pdf");
//assembler->setRange("OSSFMAXMLL");
//assembler->setRange("ONZ");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 101);
//assembler->setRange("ONZ", 0, 0);
//assembler->setRange("OSSFMAXMLL", 81);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1B1HTgt200_MET.pdf");
//assembler->setRange("OSSFMAXMLL");
//assembler->setRange("ONZ");
	
	assembler->setRange();
	
/*	// Inclusive plots: 4L
	assembler->setRange("NLEPTONS", 4);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DY0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DY0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DY0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DY0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYz1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYz1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYz1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYz1B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYn1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYn1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYn1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYn1B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 2, 2);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYz2B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYz2B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYz2B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYz2B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 2, 2);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYn2B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYn2B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYn2B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L4DYn2B1HTgt200_MET.pdf");
	
	assembler->setRange();
*/	
	
	// Some aggregate 3L inclusive plots
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0B0_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DY0B0_HT.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0B1_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DY0B1_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1B0_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYz1B0_HT.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1B1_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYz1B1_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 0, 81, false);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1B0_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYl1B0_HT.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1B1_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYl1B1_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 101);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1B0_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYh1B0_HT.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1B1_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYh1B1_HT.pdf");
	
	assembler->setRange();
	
	// Some even coarser 3L inclusive plots
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DY0_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DY0_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYz1_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYz1_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 0, 81, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYl1_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYl1_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 101);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3DYh1_MET.pdf");
	assembler->project("HT", true)->plot(true, true)->SaveAs("L3DYh1_HT.pdf");
	
/*	assembler->setRange();
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3Tau0DYz1B0HT0to200_MET.pdf");
	
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true, true)->SaveAs("L3Tau0DYz1B0HTgt200_MET.pdf");
	
*/	assembler->setRange();
	
	
	/////////////////
	// Make tables //
	/////////////////
	
	// So far, no taus
	assembler->setRange("NGOODTAUS", 0, 0);
	
	cout << endl;
	cout << "3L DYz1 with trileptons on Z" << endl;
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("MLEPTONS", 81, 101, false);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->print();
	//assembler->project("MET", true)->plot()->SaveAs("test.pdf");
	assembler->setRange("MLEPTONS");
	
	assembler->setRange();
	assembler->setRange("NGOODTAUS", 0, 0);
	
	// nLeptons loop
	for(int nLeptons = 3; nLeptons <= 4; nLeptons += 1) {
		if(nLeptons == 3) {
			assembler->setRange("NLEPTONS", 3, 3);
			cout << "\n==== 3L" << endl;
		} else {
			assembler->setRange("NLEPTONS", 4);
			cout << "\n==== >=4L" << endl;
		}
		
		// HT loop
		for(int i = 0; i <= 200; i += 200) {
			if(i == 0) {
				assembler->setRange("HT", 0, 200, false);
				cout << "\n==== HT 0-200" << endl;
			} else {
				assembler->setRange("HT", 200);
				cout << "\n==== HT 200-inf" << endl;
			}
			
			// b-tag loop
			for(int j = 0; j <= 0*1; ++j) {
				if(j == 0) {
					//assembler->setRange("NBJETSCSVM", 0, 0);
					//cout << "\n==== 0b" << endl;
				} else {
					//delete assembler;
					//return;
					assembler->setRange("NBJETSCSVM", 1);
					cout << "\n==== >=1b" << endl;
				}
				
				// Reset any OSSF mass cuts from previous loop iteration
				assembler->setRange("MOSSF");
				
				if(nLeptons == 3) {
					// DY0, no requirements on ONZ
					cout << "DY0" << endl;
					assembler->setRange("NOSSF", 0, 0);
					assembler->setRange("ONZ");
					assembler->project("MET", true)->print();
					
					// DYz1
					cout << endl;
					cout << "DYz1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 1, 1);
					assembler->project("MET", true)->print();
					assembler->save("MET");
					//assembler->save("MET", "L3Tau0DYz1B0HT0to200");
					
					// DYl1
					cout << endl;
					cout << "DYl1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 0, 0);
					assembler->setRange("MOSSF", 0, 81, false);
					assembler->project("MET", true)->print();
					
					// DYh1
					cout << endl;
					cout << "DYh1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 0, 0);
					assembler->setRange("MOSSF", 101);
					assembler->project("MET", true)->print();
				}
				
				if(nLeptons == 4) {
					// DY0, no requirements on ONZ
					cout << "DY0" << endl;
					assembler->setRange("NOSSF", 0, 0);
					assembler->setRange("ONZ");
					assembler->project("MET", true)->print();
					
					// DYz1
					cout << endl;
					cout << "DYz1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 1, 1);
					assembler->project("MET", true)->print();
					
					// DYn1
					cout << endl;
					cout << "DYn1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 0, 0);
					assembler->project("MET", true)->print();
					
					// DYz2
					cout << endl;
					cout << "DYz2" << endl;
					assembler->setRange("NOSSF", 2, 2);
					assembler->setRange("ONZ", 1, 1);
					assembler->project("MET", true)->print();
					
					// DYn2
					cout << endl;
					cout << "DYn2" << endl;
					assembler->setRange("NOSSF", 2, 2);
					assembler->setRange("ONZ", 0, 0);
					assembler->project("MET", true)->print();
				}
			}
		}
	}
	
	delete assembler;
}