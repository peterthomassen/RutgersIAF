#include <unistd.h>

void ttbarFudge() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// for ttbar 2L
	std::string varexp = "PTGOODMUONS[0]{0,200,40}:NLEPTONS{0,4}:NGOODMUONS{0,4}:NBJETSCSVM{0,2}:HT{0,1000,20}:MET{0,500,10}:ST{0,2000,20}:NGOODJETS{0,6}";
	varexp += ":Alt$(RELISONONPROMPTMUONS[0], -999){-0.15,9.15,31,\"relIsoNonPromptMu\"}";
	varexp += ":Alt$(PTGOODJETS[2], -999){0,100,10,\"PT3Jet\"}";
	varexp += ":(QGOODMUONS[0] + QNONPROMPTMUONS[0] != 0){0,1,\"SS\"}";
	varexp += ":(NPOSGOODELECTRONS == NNEGGOODMUONS && NNEGGOODELECTRONS == NPOSGOODMUONS){0,1,\"OSOF\"}";
	varexp += ":PTNONPROMPTMUONS@.size(){0,1,\"nonPromptMu\"}";
	varexp += ":QGOODMUONS[0]{-1,2,3}:QNONPROMPTMUONS[0]{-1,2,3}";
	
	// Global cuts, if desired
	TString selection = "PTGOODMUONS[0] > 30";
	selection += " && NGOODTAUS[0] == 0 && NBJETSCSVM[0] > 0 && ST[0] > 300";
	
	//selection += "NLEPTONS == 2 && NGOODTAUS == 0 && NPOSGOODELECTRONS == NNEGGOODMUONS && NNEGGOODELECTRONS == NPOSGOODMUONS && NBJETSCSVM >= 1 && ST >= 300";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	
	// Data
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = "";
	std::string suffix = ".root";
	
	PhysicsContribution* data = new PhysicsContribution("data", prefix + "20141124_dataSingle" + infix + suffix, 19500, "2012data");
	assembler->addContribution(data);
	
	// MC Background
	prefix = "/cms/thomassen/2014/Analysis/simulation/histograms/";
	infix = ".noFakes";
	suffix = ".simulation.root";
	
	double xsec_ttbar_fullLep = 23.08;
	double xsec_ttbar_semiLep = 97.97; // * 1.32;
	
	double fudge = 1;
	//fudge *= 1.27; // make number of 1mu + 1 non-prompt mu (no iso requirement) match
	
	TString weightNjet = "(NGOODJETS[0] < 2) * 1.11 + (NGOODJETS[0] == 2) * 1.08 + (NGOODJETS[0] == 3) * 1.065 + (NGOODJETS[0] == 4) * 1.065 + (NGOODJETS[0] == 5) * 1.04 + (NGOODJETS[0] > 5) * 1"; // Peter's numbers
	
	PhysicsContribution* ttbarS = new PhysicsContribution("backgroundMC", prefix + "TTJetsSemiLeptonic" + infix + suffix, xsec_ttbar_semiLep * fudge, "TT_SemiL");
	ttbarS->addWeight(weightNjet);
	ttbarS->addWeight("WEIGHT[0]");
	
	PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep * fudge, "TT_FullL");
	ttbarF->addWeight(weightNjet);
	ttbarF->addWeight("WEIGHT[0]");
	
	infix = "";
	PhysicsContribution* wjets = new PhysicsContribution("backgroundMC", prefix + "WJetsToLNu" + infix + suffix, 37509, "WJetsToLNu");
	wjets->addWeight("WEIGHT[0]");
	
	assembler->addContribution(ttbarS);
	assembler->addContribution(ttbarF);
	assembler->addContribution(wjets);
	
	// Other stuff
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("ttbarFudge", 0755);
	chdir("ttbarFudge");
	
	// We probably only need the muon cut, since getting and triggering (single-lepton) 
	// on a 30 GeV muon from W is much more likely than getting and triggering on a 85 GeV electron
	//assembler->setRange("PTGOODELECTRONS[0]", 85);
	assembler->setRange("NLEPTONS", 2, 2);
	assembler->setRange("OSOF", 1, 1);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbarFudge_OSOF-noFake_NGOODJETS.pdf");
	assembler->setRange("nonPromptMu", 1, 1);
	assembler->project("PTGOODMUONS[0]", true)->plot(false)->SaveAs("ttbarFudge_OSOF_PTGOODMUONS.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbarFudge_OSOF_NGOODJETS.pdf");
	assembler->project("relIsoNonPromptMu", true)->plot(false, -0.15, 0.15)->SaveAs("ttbarFudge_OSOF_RELISONONPROMPTMUONS.pdf");
	assembler->project("relIsoNonPromptMu", true)->print();
	
	assembler->setRange();
	assembler->setRange("NLEPTONS", 1, 1);
	assembler->setRange("PT3Jet", 40);
	
/*	std::vector<double> list1, list2;
	list1 = getFirst(assembler->project("relIsoNonPromptMu", true)->getMeta());
	list2 = getSecond(assembler->project("relIsoNonPromptMu", true)->getMeta());
	cout << "data: " << list1.size() << endl;
	for(size_t i = 0; i < list1.size(); ++i) {
		cout << (long)list1[i] << " " << (long)list2[i] << endl;
	}
	
	return;
*/	
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbarFudge_noFake_NGOODJETS.pdf");
	assembler->setRange("nonPromptMu", 1, 1);
	assembler->project("PTGOODMUONS[0]", true)->plot(false)->SaveAs("ttbarFudge_PTGOODMUONS.pdf");
	assembler->project("PTGOODMUONS[0]", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbarFudge_NGOODJETS.pdf");
	assembler->project("SS", true)->plot(false)->SaveAs("ttbarFudge_SS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->project("relIsoNonPromptMu", true)->plot(false, -0.15, 0.15)->SaveAs("ttbarFudge_RELISONONPROMPTMUONS.pdf");
	assembler->project("relIsoNonPromptMu", true)->print();
	
	assembler->setRange("relIsoNonPromptMu", -0.15, 0.15);
	assembler->project("QGOODMUONS[0]", false)->plot(false)->SaveAs("ttbarFudge_QGOODMUONS.pdf");
	assembler->project("QNONPROMPTMUONS[0]", false)->plot(false)->SaveAs("ttbarFudge_QNONPROMPTMUONS.pdf");
	assembler->setRange("relIsoNonPromptMu");
	
	assembler->setRange("SS", 0, 0);
	assembler->project("PTGOODMUONS[0]", true)->plot(false)->SaveAs("ttbarFudge_OS_PTGOODMUONS.pdf");
	assembler->project("PTGOODMUONS[0]", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbarFudge_OS_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->project("relIsoNonPromptMu", true)->plot(false, -0.15, 0.15)->SaveAs("ttbarFudge_OS_RELISONONPROMPTMUONS.pdf");
	assembler->project("relIsoNonPromptMu", true)->print();
	
	assembler->setRange("SS", 1, 1);
	assembler->project("PTGOODMUONS[0]", true)->plot(false)->SaveAs("ttbarFudge_SS_PTGOODMUONS.pdf");
	assembler->project("PTGOODMUONS[0]", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbarFudge_SS_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->project("relIsoNonPromptMu", true)->plot(false, -0.15, 0.15)->SaveAs("ttbarFudge_SS_RELISONONPROMPTMUONS.pdf");
	assembler->project("relIsoNonPromptMu", true)->print();
	
	delete assembler;
}
