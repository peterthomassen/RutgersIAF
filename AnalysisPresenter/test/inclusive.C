#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter.C"

void inclusive(TString ofname = "test.root") {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	float z = 91; float zWidth = 10;
	//float z = 90; float zWidth = 15;
	
	// Specify axes and bins of multidimensional histogram
	// For inclusive table
	std::string varexp = "NLEPTONS{2,6}:MOSSF{11,131,120}:NOSSF{0,3}:NGOODTAUS{0,3}:NBJETSCSVM{0,3}:HT{0,200,1}:MET{0,200,4}:ST{0,1500,5}";
	varexp += ":NPROMPTTRACKS7{0,100,1}:OSSFMAXMLL{11,131,36}:OSSFMINMLL{11,131,36}";
	varexp += ":MLIGHTLEPTONS{1,201,20}";
	varexp += std::string(TString::Format(":(abs(MOSSF-%f)<%f){0,2,\"ONZ\"}", z, zWidth).Data());
	varexp += std::string(TString::Format(":(NLEPTONS-NGOODTAUS == 3 && (abs(MOSSF-%f)>%f) && abs(MLIGHTLEPTONS-%f) < %f){0,2,\"AIC\"}", z, zWidth, 87.5, 12.5).Data());
	varexp += ":NVERTICES[0]{0,50}";
	
	// Global cuts, if desired
	TString selection = "PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler(ofname, "RECREATE");
	init(assembler);
	
	assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	//assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("noRatioPlot");
	//assembler->setMode("fullPrecision");
	
	setupData(assembler);
	setupBackgroundMC(assembler);
	//setupBackgroundMC(assembler, false, false);
	setupBackgroundDD(assembler, "", true);
	//setupBackgroundDD(assembler, "justTaus", true);
	//assembler->addContribution(signal); // It is important to add the signal before setting up the rake rates
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	//assembler->save();
	
	TF1* f1 = new TF1("f", "pol1", 2, 24);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("inclusive", 0755);
	chdir("inclusive");
	mkdir("ST", 0755);
	mkdir("coarse", 0755);
	mkdir("coarse/coarser", 0755);
	
	makeNicePlot(assembler->project("NVERTICES[0]", true)->plot(false, f1, 2, 24), "nVertices")->SaveAs("NVERTICES.pdf");
	
	assembler->setRange("NGOODTAUS", 0, 0);
	makeNicePlot(assembler->project("NVERTICES[0]", true)->plot(false, f1, 2, 24), "nVertices")->SaveAs("NVERTICES_Tau0.pdf");
	
	assembler->setRange();
	
	chdir("coarse");
		assembler->setRange("NLEPTONS", 3, 3);
		assembler->setRange("NGOODTAUS", 0, 0);
		
		assembler->setRange("NOSSF", 0, 0);
		assembler->setRange("HT", 0, 200, false);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DY0HT0to200_MET.pdf");
		assembler->setRange("HT", 200);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DY0HTgt200_MET.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ", 1, 1);
		assembler->setRange("HT", 0, 200, false);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1HT0to200_MET.pdf");
		assembler->setRange("HT", 200);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1HTgt200_MET.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
		assembler->setRange("MOSSF", 12, z-zWidth, false);
		assembler->setRange("HT", 0, 200, false);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1HT0to200_MET.pdf");
		assembler->setRange("HT", 200);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1HTgt200_MET.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
		assembler->setRange("MOSSF", z+zWidth);
		assembler->setRange("HT", 0, 200, false);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1HT0to200_MET.pdf");
		assembler->setRange("HT", 200);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1HTgt200_MET.pdf");
		
		assembler->setRange("HT");
		assembler->setRange("MOSSF", 12, z-zWidth);
		assembler->setRange("MET", 0, 50);
		assembler->project("HT", true)->plot(true)->SaveAs("L3DYl1MET0to50_HT.pdf");
		
		assembler->setRange("MOSSF", z+zWidth);
		assembler->setRange("MET", 0, 50);
		assembler->project("HT", true)->plot(true)->SaveAs("L3DYh1MET0to50_HT.pdf");
		
		assembler->setRange();
	chdir("..");
	
	
	// ST plots
	chdir("ST");
		assembler->setRange("NLEPTONS", 3, 3);
		assembler->setRange("NGOODTAUS", 0, 0);
		assembler->setRange("NBJETSCSVM", 0, 0);
		
		assembler->setRange("NOSSF", 0, 0);
		assembler->project("ST", true)->print();
		assembler->project("ST", true)->plot(true)->SaveAs("L3DY0B0_ST.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ", 1, 1);
		assembler->project("ST", true)->print();
		assembler->project("ST", true)->plot(true)->SaveAs("L3DYz1B0_ST.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ", 0, 0);
		assembler->project("ST", true)->print();
		assembler->project("ST", true)->plot(true)->SaveAs("L3DYn1B0_ST.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
		assembler->setRange("MOSSF", 12, z-zWidth, false);
		assembler->project("ST", true)->print();
		assembler->project("ST", true)->plot(true)->SaveAs("L3DYl1B0_ST.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
		assembler->setRange("MOSSF", z+zWidth);
		assembler->project("ST", true)->print();
		assembler->project("ST", true)->plot(true)->SaveAs("L3DYh1B0_ST.pdf");
		
		assembler->setRange();
	chdir("..");
	
	// Inclusive plots: L3Tau0
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 12, z-zWidth, false);
	
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("AIC", 0, 0);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0HT0to200AIC0_MET.pdf");
	
	assembler->setRange("AIC", 1, 1);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0HT0to200AIC1_MET.pdf");
	
	assembler->setRange("HT", 200);
	assembler->setRange("AIC", 0, 0);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0HTgt200AIC0_MET.pdf");

	assembler->setRange("AIC", 1, 1);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0HTgt200AIC0_MET.pdf");
	
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("AIC", 0, 0);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1HT0to200AIC0_MET.pdf");
	
	assembler->setRange("AIC", 1, 1);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1HT0to200AIC0_MET.pdf");
	
	assembler->setRange("HT", 200);
	assembler->setRange("AIC", 0, 0);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1HTgt200AIC0_MET.pdf");
	assembler->setRange("AIC", 1, 1);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1HTgt200AIC0_MET.pdf");
	
	assembler->setRange("AIC");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", z+zWidth);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange();
	
	// Inclusive plots: L4Tau0
	assembler->setRange("NLEPTONS", 4);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DY0Tau0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DY0Tau0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DY0Tau0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DY0Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz1Tau0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz1Tau0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz1Tau0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz1Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 2);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz2Tau0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz2Tau0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz2Tau0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz2Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 2);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn2Tau0B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn2Tau0B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn2Tau0B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn2Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange();
	
	
	// Some aggregate 3L inclusive plots
	chdir("coarse");
		assembler->setRange("NLEPTONS", 3, 3);
		assembler->setRange("NGOODTAUS", 0, 0);
		
		assembler->setRange("NOSSF", 0, 0);
		assembler->setRange("NBJETSCSVM", 0, 0);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0B0_MET.pdf");
		assembler->project("HT", true)->plot(true)->SaveAs("L3DY0Tau0B0_HT.pdf");
		assembler->setRange("NBJETSCSVM", 1);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0B1_MET.pdf");
		assembler->project("HT", true)->plot(true)->SaveAs("L3DY0Tau0B1_HT.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ", 1, 1);
		assembler->setRange("NBJETSCSVM", 0, 0);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B0_MET.pdf");
		assembler->project("HT", true)->plot(true)->SaveAs("L3DYz1Tau0B0_HT.pdf");
		assembler->setRange("NBJETSCSVM", 1);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1_MET.pdf");
		assembler->project("HT", true)->plot(true)->SaveAs("L3DYz1Tau0B1_HT.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
		assembler->setRange("MOSSF", 12, z-zWidth, false);
		assembler->setRange("NBJETSCSVM", 0, 0);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0_MET.pdf");
		assembler->project("HT", true)->plot(true)->SaveAs("L3DYl1Tau0B0_HT.pdf");
		assembler->setRange("NBJETSCSVM", 1);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1_MET.pdf");
		assembler->project("HT", true)->plot(true)->SaveAs("L3DYl1Tau0B1_HT.pdf");
		
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
		assembler->setRange("MOSSF", z+zWidth);
		assembler->setRange("NBJETSCSVM", 0, 0);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau0B0_MET.pdf");
		assembler->project("HT", true)->plot(true)->SaveAs("L3DYh1Tau0B0_HT.pdf");
		assembler->setRange("NBJETSCSVM", 1);
		assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau0B1_MET.pdf");
		assembler->project("HT", true)->plot(true)->SaveAs("L3DYh1Tau0B1_HT.pdf");
		
		assembler->setRange();
		
		// Some even coarser 3L inclusive plots
		chdir("coarser");
			assembler->setRange("NLEPTONS", 3, 3);
			assembler->setRange("NGOODTAUS", 0, 0);
			
			assembler->setRange("NOSSF", 0, 0);
			assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0_MET.pdf");
			assembler->project("HT", true)->plot(true)->SaveAs("L3DY0Tau0_HT.pdf");
			
			assembler->setRange("NOSSF", 1, 1);
			assembler->setRange("ONZ", 1, 1);
			assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0_MET.pdf");
			assembler->project("HT", true)->plot(true)->SaveAs("L3DYz1Tau0_HT.pdf");
			
			assembler->setRange("NOSSF", 1, 1);
			assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
			assembler->setRange("MOSSF", 12, z-zWidth, false);
			assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0_MET.pdf");
			assembler->project("HT", true)->plot(true)->SaveAs("L3DYl1Tau0_HT.pdf");
			
			assembler->setRange("NOSSF", 1, 1);
			assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
			assembler->setRange("MOSSF", z+zWidth);
			assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau0_MET.pdf");
			assembler->project("HT", true)->plot(true)->SaveAs("L3DYh1Tau0_HT.pdf");
			
			assembler->setRange();
		chdir("..");
	chdir("..");
	
	
	/////////////////
	// Make tables //
	/////////////////
	
	// So far, no taus
	assembler->setRange("NGOODTAUS", 0, 0);
	
	cout << endl;
	cout << "3L DYz1 with trileptons on Z" << endl;
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("MLIGHTLEPTONS", z-zWidth, z+zWidth, false);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->print();
	//assembler->project("MET", true)->plot()->SaveAs("test.pdf");
	assembler->setRange("MLIGHTLEPTONS");
	
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
					assembler->setRange("MOSSF", 12, z-zWidth, false);
					assembler->project("MET", true)->print();
					
					// DYh1
					cout << endl;
					cout << "DYh1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 0, 0);
					assembler->setRange("MOSSF", z+zWidth);
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
					assembler->setRange("NOSSF", 2);
					assembler->setRange("ONZ", 1, 1);
					assembler->project("MET", true)->print();
					
					// DYn2
					cout << endl;
					cout << "DYn2" << endl;
					assembler->setRange("NOSSF", 2);
					assembler->setRange("ONZ", 0, 0);
					assembler->project("MET", true)->print();
				}
			}
		}
	}
	
	delete assembler;
}
