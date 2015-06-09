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
	
	//float z = 91; float zWidth = 10;
	float z = 90; float zWidth = 15;
	
	// Specify axes and bins of multidimensional histogram
	// For inclusive table
	//std::string varexp = "NLEPTONS{2,6}:MOSSF{11,131,36}:NOSSF{0,3}:ONZ{0,2}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,200,4}:ST{0,1500,5}:MLEPTONS{70,110}";
	std::string varexp = "NLEPTONS{2,6}:MOSSF{11,131,120}:NOSSF{0,3}:NGOODTAUS{0,3}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,200,4}:ST{0,1500,5}:MLEPTONS{70,110}";
	//std::string varexp = "NLEPTONS{2,6}:MOSSF{11,131,36}:NOSSF{0,3}:ONZ{0,2}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,100,2}:MLEPTONS{70,110}";
	varexp += ":NPROMPTTRACKS7{0,100,1}:OSSFMAXMLL{11,131,36}:OSSFMINMLL{11,131,36}";
	varexp += ":MLIGHTLEPTONS{1,201,20}";
	varexp += std::string(TString::Format(":(abs(MOSSF-%f)<%f){0,2,\"ONZ\"}", z, zWidth).Data());
	varexp += std::string(TString::Format(":(NLEPTONS-NGOODTAUS == 3 && (abs(MOSSF-%f)>%f) && abs(MLIGHTLEPTONS-%f) < %f){0,2,\"AIC\"}", z, zWidth, 87.5, 12.5).Data());
	
	// Global cuts, if desired
	//TString selection = "NOTTRILEPTONONZ";
	//TString selection = "(NOSSF != 1 || NOTTRILEPTONONZ)";
	//selection += " && (NLEPTONS != 3 || (NGOODMUONS == 3 || NGOODELECTRONS == 3 || abs(NPOSGOODMUONS+NPOSGOODELECTRONS-NNEGGOODMUONS-NNEGGOODELECTRONS) != 3))";
	TString selection = "";
	//TString selection = "(!(NLEPTONS == 3 && abs(MLEPTONS-91) < 10))";
	
	
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
	//setupBackgroundMC(assembler, false, false);
	setupBackgroundDD(assembler, "", true);
	//setupBackgroundDD(assembler, "justTaus", true);
	//assembler->addContribution(signal); // It is important to add the signal before setting up the rake rates
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	assembler->save();
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("inclusive", 0755);
	chdir("inclusive");
	
/*	assembler->setRange("NLEPTONS", 3, 3);
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
	
	return;
	
	assembler->setRange();

	
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
	
	return;
*/	
	
/*	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0B0HT0to200_MET-window10.pdf");
	assembler->project("MET", true)->print();
	
	assembler->setRange("NGOODTAUS", 1, 1);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau1B0HT0to200_MET-window10.pdf");
	assembler->project("MET", true)->print();
	return;
*/	
	// Inclusive plots: L3Tau0
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("AIC", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau0B0HT0to200_MET.pdf");
	cout << ".........................." << endl;
	assembler->project("MET", true)->print();
	cout << ".........................." << endl;
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
	cout << ".........................." << endl;
	assembler->project("MET", true)->print();
	cout << ".........................." << endl;
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1HT0to200_MET.pdf");
cout << endl << endl << endl << endl << endl;
cout << "This is L3DYz1Tau0B1HT0to200" << endl;
	assembler->project("MET", true)->print();
Bundle* prevBundle = assembler->getDefaultBundle();
assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
assembler->setRange("MET", 0, 50, false);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1HT0to200_MET0to50.pdf");
assembler->setRange("MET", 50, 100, false);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1HT0to200_MET50to100.pdf");
assembler->setRange("MET", 100, 150, false);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1HT0to200_MET100to150.pdf");
assembler->setRange("MET", 150, 200, false);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1HT0to200_MET150to200.pdf");
assembler->setDefaultBundle(prevBundle);
assembler->setRange("MET");
cout << endl << endl << endl << endl << endl;
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau0B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 12, z-zWidth, false);
//assembler->setRange("ONZ", 0, 0);
//assembler->setRange("OSSFMAXMLL", 0, z-zWidth, false);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0HT0to200_MET.pdf");
	assembler->project("MET", true)->print();
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0HT0to200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0HTgt200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B0HTgt200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1HT0to200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1HT0to200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1HTgt200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau0B1HTgt200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
//assembler->setRange("OSSFMAXMLL");
//assembler->setRange("ONZ");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", z+zWidth);
//assembler->setRange("ONZ", 0, 0);
//assembler->setRange("OSSFMAXMLL", z-zWidth);
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
//assembler->setRange("OSSFMAXMLL");
//assembler->setRange("ONZ");
	
	assembler->setRange();
	
	// Inclusive plots: L3Tau1
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 1, 1);
	
	assembler->setRange("AIC", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau1B0HT0to200_MET.pdf");
	cout << ".........................." << endl;
	assembler->project("MET", true)->print();
	cout << ".........................." << endl;
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DY0Tau1B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau1B0HTgt200_MET.pdf");
	cout << ".........................." << endl;
	assembler->project("MET", true)->print();
	cout << ".........................." << endl;
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYz1Tau1B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 12, z-zWidth, false);
//assembler->setRange("ONZ", 0, 0);
//assembler->setRange("OSSFMAXMLL", 0, z-zWidth, false);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau1B0HT0to200_MET.pdf");
	assembler->project("MET", true)->print();
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau1B0HT0to200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau1B0HTgt200_MET.pdf");
assembler->setRange("AIC", 1);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau1B0HTgt200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau1B1HT0to200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau1B1HT0to200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau1B1HTgt200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L3DYl1Tau1B1HTgt200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
//assembler->setRange("OSSFMAXMLL");
//assembler->setRange("ONZ");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", z+zWidth);
//assembler->setRange("ONZ", 0, 0);
//assembler->setRange("OSSFMAXMLL", z-zWidth);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3DYh1Tau1B1HTgt200_MET.pdf");
//assembler->setRange("OSSFMAXMLL");
//assembler->setRange("ONZ");
	
	assembler->setRange();
	
	// Inclusive plots: L4Tau0
	assembler->setRange("NLEPTONS", 4);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("AIC", 0, 0);
	
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
	
	// Inclusive plots: L4Tau1
	assembler->setRange("NLEPTONS", 4);
	assembler->setRange("NGOODTAUS", 1, 1);
	
	assembler->setRange("AIC", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DY0Tau1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DY0Tau1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DY0Tau1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DY0Tau1B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz1Tau1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz1Tau1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz1Tau1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz1Tau1B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau1B0HT0to200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau1B0HT0to200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
assembler->setRange("ONZ");
assembler->setRange("MOSSF", 12, z-zWidth, false);
assembler->project("MET", true)->plot(true)->SaveAs("L4DYl1Tau1B0HT0to200_MET.pdf");
assembler->setRange("MOSSF", z+zWidth);
assembler->project("MET", true)->plot(true)->SaveAs("L4DYh1Tau1B0HT0to200_MET.pdf");
assembler->setRange("MOSSF");
assembler->setRange("ONZ", 0, 0);
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau1B0HTgt200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau1B0HTgt200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau1B1HT0to200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau1B1HT0to200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau1B1HTgt200_MET.pdf");
assembler->setRange("AIC", 1, 1);
assembler->project("MET", true)->plot(true)->SaveAs("L4DYn1Tau1B1HTgt200AIC_MET.pdf");
assembler->setRange("AIC", 0, 0);
	
	assembler->setRange("NOSSF", 2);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz2Tau1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz2Tau1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz2Tau1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYz2Tau1B1HTgt200_MET.pdf");
	
	assembler->setRange("NOSSF", 2);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn2Tau1B0HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn2Tau1B0HTgt200_MET.pdf");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn2Tau1B1HT0to200_MET.pdf");
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L4DYn2Tau1B1HTgt200_MET.pdf");
	
	assembler->setRange();
	
	
	// Some aggregate 3L inclusive plots
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("AIC", 0, 0);
	
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
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("AIC", 0, 0);
	
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
	
/*	assembler->setRange();
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(true)->SaveAs("L3Tau0DYz1Tau0B0HT0to200_MET.pdf");
	
	assembler->setRange("HT", 200);
	assembler->project("MET", true)->plot(true)->SaveAs("L3Tau0DYz1Tau0B0HTgt200_MET.pdf");
	
*/	assembler->setRange();
	
	
	/////////////////
	// Make tables //
	/////////////////
	
	// So far, no taus
	assembler->setRange("NGOODTAUS", 0, 0);
	
	cout << endl;
	cout << "3L DYz1 with trileptons on Z" << endl;
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("MLEPTONS", z-zWidth, z+zWidth, false);
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
