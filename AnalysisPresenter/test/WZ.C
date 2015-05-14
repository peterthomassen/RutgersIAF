#include <sys/stat.h>
#include <unistd.h>

void WZ() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For WZ
	std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLEPTONS{76,106,9}:MT{0,300,30}:NGOODJETS{0,6}:ST{0,1000,100}";
	varexp += ":NGOODMUONS{0,4}:NGOODELECTRONS{0,4}";
	varexp += ":NGOODMUONS%2{0,2}";
	//varexp += ":MINJETPT{0,400,40}:MAXJETPT{0,400,40}";
	
	// Global cuts, if desired
	TString selection = "NOTTRILEPTONONZ";
	//selection += " && NGOODELECTRONS == 3";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	setupData(assembler);
	setupBackgroundMC(assembler, false, false);
	//setupBackgroundMC(assembler, false, true);
	//setupBackgroundMC(assembler);
	setupBackgroundDD(assembler, "noTaus");
//	setupBackgroundDD(assembler, "justTracks");
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("WZ", 0755);
	chdir("WZ");
	
	// Check for duplicate events
	
	assembler->project("NLEPTONS", true)->getMeta(); // printMeta();
	assembler->project("NLEPTONS", true)->print();
	
	// WZ control plot
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
cout << "check again" << endl;
assembler->project("NLEPTONS", true)->getMeta(); // printMeta();
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("MET", 50, 100, false);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_MT.pdf");

assembler->project("MT", true)->print();
Channel* ch = assembler->channel("WZ");
ch->print();
//ch->getMeta();
ch->plot(false)->SaveAs("WZ_channel.pdf");
cout << "number of events: " << ch->getHistogram("data")->GetEntries() << endl;
//ch->printMeta();

/*cout << "=========" << endl;

cout << ch->get("data") << endl;
cout << ch->get("background") << endl;

cout << ch->getStat("background") << endl;
cout << ch->getSyst("background") << endl;
cout << ch->getSyst("background", "normalizationWZ") << endl;

cout << "wz correlation class" << endl;
cout << ch->getStat("background", "wz") << endl;
cout << ch->getSyst("background", "normalizationWZ", "wz") << endl;

cout << "empty correlation class" << endl;
cout << ch->getStat("background", "") << endl;
cout << ch->getSyst("background", "normalizationWZ", "") << endl;

std::vector<TString> classes = ch->getCorrelationClasses("background");

cout << classes.size() << " correlation classes" << endl;
for(size_t i = 0; i < classes.size(); ++i) {
	cout << classes[i] << endl;
}
*/
assembler->setRange("MT", 50);

//ch->project("HT", true)->plot(false)->SaveAs("WZ_channel_HT.pdf");
//assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100MT50to100_HT.pdf");

/*assembler->setRanges(ch->getRanges());
std::vector<std::pair<int, int>> ranges = ch->getRanges();
cout << "ranges size: " << ranges.size() << endl;
*/
ChannelCollection* cc = new ChannelCollection("SR");
cc->addChannel(ch);
cc->addChannel(ch);

Channel* ch2 = assembler->channel("WZ_MT");
cout << "number of events: " << ch2->getHistogram("data")->GetEntries() << endl;
ch2->printMeta();
cc->addChannel(ch2);
cc->addChannel(ch2);

cc->getChannels();

//return;
	assembler->setRange("NGOODMUONS%2", 0, 0);
/*cout << "creating projection" << endl;
AssemblerProjection* projection = assembler->project("MT", true);
cout << "calling delete" << endl;
delete projection;
cout << "called delete" << endl;
return;
*/	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_evenMuon_MT.pdf");
	assembler->setRange("NGOODMUONS%2", 1);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_oddMuon_MT.pdf");
	assembler->setRange("NGOODMUONS%2");
	
	assembler->setRange("NGOODMUONS", 0, 0);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_Mu0_MT.pdf");
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_Mu1_MT.pdf");
	assembler->setRange("NGOODMUONS", 2, 2);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_Mu2_MT.pdf");
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_Mu3_MT.pdf");
	assembler->setRange("NGOODMUONS");
	
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100_HT.pdf");
	assembler->project("HT", true)->plot(true)->SaveAs("WZ_MET50to100_HT_log.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("NGOODJETS", 0, 0);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS0_HT.pdf");
	assembler->setRange("NGOODJETS", 1, 1);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS1_HT.pdf");
	assembler->setRange("NGOODJETS", 2, 2);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS2_HT.pdf");
	assembler->setRange("NGOODJETS", 3, 3);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS3_HT.pdf");
	assembler->setRange("NGOODJETS");
	
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100HT0to200_MT.pdf");
	assembler->project("MT", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100HT0to200_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("HT", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100HTgt200_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("MET");

	assembler->setRange("MT", 50, 100, false);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(false)->SaveAs("WZ_MT50to100HT0to200_MET.pdf");
	assembler->project("MET", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HT0to200_NGOODJETS.pdf");
	assembler->setRange("HT", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HTgt200_NGOODJETS.pdf");
	
	assembler->setRange();
	
	delete assembler;
}
