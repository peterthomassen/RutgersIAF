#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter.C"

void RA7table() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	std::string varexp = "NLEPTONS[0]{2,6}:MOSSF[0]{0,150,150}:(abs(MOSSF[0]-91)<15){0,2, \"ONZ\"}:NGOODTAUS[0]{0,2}:NBJETSCSVM[0]{0,3}:HT[0]{0,600,30}:MET[0]{0,300,6}";
	
	// Global cuts, if desired
	TString selection = "NLEPTONS[0] == 3 && NGOODTAUS[0] == 0 && PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10 && MET[0] > 50 && NGOODJETS[0] >= 2";
	
	///////////////////////
	// Signal definition //
	///////////////////////
	//PhysicsContribution* signal = new PhysicsContribution("signal", "/cms/multilepton/mheindl/2016/LQ_analysis/EventAnalyzer/AnalysisTree/LQ200_TopMu.simulation.root", 0.123, "LQ200_TopMu");
	//signal->addWeight("WEIGHT");
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler("", "RECREATE");
	init(assembler);
	assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	setupData(assembler);
	setupBackgroundMC(assembler, false, true);
	setupBackgroundDD(assembler);
	//assembler->addContribution(signal);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	///////////////////////////////////////////
	// RA7 signal regions (SR) for RA7 table //
	///////////////////////////////////////////
	ofstream RA7table;
	RA7table.open("RA7table.txt");
	
	std::cout << "Create input for RA7table..." << std::endl;
		
	//OnZ signal regions
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OnZ_SR1")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OnZ_SR2")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OnZ_SR3")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OnZ_SR4")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 1, 1);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OnZ_SR5")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 1, 1);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OnZ_SR6")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 1, 1);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OnZ_SR7")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 1, 1);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OnZ_SR8")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 2, 2);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OnZ_SR9")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 2, 2);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OnZ_SR10")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 2, 2);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OnZ_SR11")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 2, 2);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OnZ_SR12")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM[0]", 3);
	assembler->setRange("HT[0]", 60, 600, false);
	assembler->setRange("MET[0]", 50, 300, false);
	RA7table << assembler->channel("OnZ_SR13")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("HT[0]", 600);
	assembler->setRange("MET[0]", 50, 300, false);
	RA7table << assembler->channel("OnZ_SR14")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 1);
	assembler->setRange("MET[0]", 300);
	RA7table << assembler->channel("OnZ_SR15")->printRA7table() << endl;
	assembler->setRange();
	
	//OffZ signal regions
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OffZ_SR1")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OffZ_SR2")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OffZ_SR3")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OffZ_SR4")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 1, 1);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OffZ_SR5")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 1, 1);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OffZ_SR6")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 1, 1);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OffZ_SR7")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 1, 1);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OffZ_SR8")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 2, 2);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OffZ_SR9")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 2, 2);
	assembler->setRange("HT[0]", 60, 400, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OffZ_SR10")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 2, 2);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 50, 150, false);
	RA7table << assembler->channel("OffZ_SR11")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 2, 2);
	assembler->setRange("HT[0]", 400, 600, false);
	assembler->setRange("MET[0]", 150, 300, false);
	RA7table << assembler->channel("OffZ_SR12")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("NBJETSCSVM[0]", 3);
	assembler->setRange("HT[0]", 60, 600, false);
	assembler->setRange("MET[0]", 50, 300, false);
	RA7table << assembler->channel("OffZ_SR13")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("HT[0]", 600);
	assembler->setRange("MET[0]", 50, 300, false);
	RA7table << assembler->channel("OffZ_SR14")->printRA7table() << endl;
	assembler->setRange();
	
	assembler->setRange("ONZ", 0, 0, true);
	assembler->setRange("MET[0]", 300);
	RA7table << assembler->channel("OffZ_SR15")->printRA7table() << endl;
	assembler->setRange();
	
	RA7table.close();
	delete assembler;
}
