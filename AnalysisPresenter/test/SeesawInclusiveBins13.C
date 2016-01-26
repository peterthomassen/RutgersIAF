#include <sys/stat.h>
#include <unistd.h>
#include <boost/algorithm/string.hpp>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h" 
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"
#include "RutgersIAF/AnalysisPresenter/src/ChannelCollection.cpp"
#include "helperAnalysisPresenter.C"

void addMETchannels(std::vector<Channel*> &channels, Assembler* assembler, TString name) {
	auto ranges = assembler->getRanges();
	
	assembler->setRange("LT+MET");
	assembler->project("LT+MET", true)->plot(true)->SaveAs(name + TString(".pdf"));
makeNicePlot(assembler->project("LT+MET", true)->plot(true), "LT+MET [GeV]")->SaveAs(TString("../nicePlots/") + name + TString(".pdf"));
	assembler->project("minElectronPT", true)->plot(true)->SaveAs(name + TString("_minElectronPT.pdf"));
makeNicePlot(assembler->project("minElectronPT", true)->plot(true), "min electron pT [GeV]")->SaveAs(TString("../nicePlots/") + name + TString("_minElectronPT.pdf"));
	assembler->project("minMuonPT", true)->plot(true)->SaveAs(name + TString("_minMuonPT.pdf"));
makeNicePlot(assembler->project("minMuonPT", true)->plot(true), "min muon pT [GeV]")->SaveAs(TString("../nicePlots/") + name + TString("_minMuonPT.pdf"));
	assembler->project("LT", true)->plot(true)->SaveAs(name + TString("_LT.pdf"));
makeNicePlot(assembler->project("LT", true)->plot(true), "LT [GeV]")->SaveAs(TString("../nicePlots/") + name + TString("_LT.pdf"));
	assembler->project("LT+MET", true)->plot(true)->SaveAs(name + TString("_LT+MET.pdf"));
makeNicePlot(assembler->project("LT+MET", true)->plot(true), "LT+MET [GeV]")->SaveAs(TString("../nicePlots/") + name + TString("_LT+MET.pdf"));
	
	int start = 350;
	int step = 200;
	int nSteps = 4;
	for(int met = start; met < start + nSteps * step; met += step) {
		TString metName = name + TString::Format("LTMET%dto%d", met, met + step);
		//cout << "Creating channel " << metName << endl;
		
		assembler->setRange("LT+MET", met, met + step, false);
		channels.push_back(assembler->channel(metName));
	}
	
	TString metName = name + TString::Format("LTMETgt%d", nSteps * step);
	//cout << "Creating channel " << metName << endl;
	
	assembler->setRange("LT+MET", start + nSteps * step);
	channels.push_back(assembler->channel(metName));
	
	assembler->setRanges(ranges);
}

void SeesawInclusiveBins13(TString ofname = "test.root") {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	double z = 91;
	double zWidth = 10;
	
	// Specify axes and bins of multidimensional histogram
	// For inclusive table
	std::string varexp = "NLEPTONS{2,6}:MOSSF{11,131,36}:NOSSF{0,3}:ONZ{0,2}:NGOODTAUS{0,2}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,250,5}";
	varexp += std::string(TString::Format(":(NLIGHTLEPTONS == 3 && (abs(MOSSF-%f)>%f) && abs(MLIGHTLEPTONS-%f) < %f){0,2,\"AIC\"}", z, zWidth, 87.5, 12.5).Data());
	varexp += ":(Sum$(QGOODMUONS) + Sum$(QGOODELECTRONS)){-3,3,\"QLIGHTLEPTONS\"}";
	varexp += ":Alt$(PTGOODELECTRONS[0],0){20,320,15,\"minElectronPT\"}";
	varexp += ":Alt$(PTGOODMUONS[0],0){20,320,15,\"minMuonPT\"}";
	varexp += ":LT{0,600,30}";
	varexp += ":LT+MET{350,1150,4}";
	varexp += ":(sqrt(2) * 18.5 * sqrt(-log(rndm())) * cos(6.2831853 * rndm())){-50,50,100,\"gaus\"}";
	
	// Global cuts, if desired
	TString selection = "PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10";
	selection += " && NGOODTAUS[0] == 0 && NBJETSCSVM[0] == 0"; // no taus or b-tags
	selection += " && !(NLEPTONS[0] == 3 && ONZ && NBJETSCSVM[0] == 0 && NGOODTAUS[0] == 0 && MET[0] < 100)"; // veto WZ and Z+jets control regions
	selection += " && !(NLEPTONS[0] == 4 && NOSSF[0] == 2 && ONZ && NBJETSCSVM[0] == 0 && NGOODTAUS[0] == 0 && MET[0] < 50)"; // veto ZZ control region
	
	// Padova style
//	TString selection ="NLIGHTLEPTONS[0] == 3 && (Alt$((NGOODMUONS == 3 && PTGOODMUONS[0] > 30 && PTGOODMUONS[1] > 20 && PTGOODMUONS[2] > 20), 0) || Alt$((NGOODELECTRONS == 3 && PTGOODELECTRONS[0] > 30 && PTGOODELECTRONS[1] > 20 && PTGOODELECTRONS[2] > 20), 0) || Alt$((NGOODELECTRONS == 2 && PTGOODELECTRONS[0] > PTGOODMUONS[0] && PTGOODELECTRONS[0] > 30 && PTGOODELECTRONS[1] > 20 && PTGOODMUONS[0] > 20), 0) || Alt$((NGOODELECTRONS == 2 && PTGOODELECTRONS[0] < PTGOODMUONS[0] && PTGOODMUONS[0] > 30 && PTGOODELECTRONS[1] > 20 && PTGOODELECTRONS[0] > 20), 0) || Alt$((NGOODMUONS == 2 && PTGOODMUONS[0] > PTGOODELECTRONS[0] && PTGOODMUONS[0] > 30 && PTGOODMUONS[1] > 20 && PTGOODELECTRONS[0] > 20), 0) || Alt$((NGOODMUONS == 2 && PTGOODMUONS[0] < PTGOODELECTRONS[0] && PTGOODELECTRONS[0] > 30 && PTGOODMUONS[1] > 20 && PTGOODMUONS[0] > 20), 0))";
//	selection += " && abs(Sum$(QGOODMUONS) + Sum$(QGOODELECTRONS)) == 1 && MET[0] > 50 && HT[0] < 150 && NBJETSCSVL[0] == 0 && (NOSSF[0] == 0 || abs(MOSSF[0]-91) > 15) && abs(MLIGHTLEPTONS[0]-91) > 15";

	//TString selection = "";
	// Cut down charge flips
	//selection += " && (NLEPTONS != 3 || (NGOODMUONS == 3 || NGOODELECTRONS == 3 || abs(NPOSGOODMUONS+NPOSGOODELECTRONS-NNEGGOODMUONS-NNEGGOODELECTRONS) != 3))";
	
	
	///////////////////////
	// Signal definition //
	///////////////////////
	
	//std::string mass = "220";
	std::string mass = "340";
	std::string xsecfile = mass + "_xsecs_and_procs.txt";
	std::string directory = "/cms/data23/feigelis/SeesawProject/Analysis/output/" + mass;
	
	std::vector<PhysicsContribution*> signals;
	
	ifstream ifile(xsecfile);
	int i = 0;
	for(std::string line; getline(ifile, line); ++i) {
		if(line.size() == 0 || line.at(0) == '#') {
			continue;
		}
		
		std::vector<std::string> tokens;
		boost::split(tokens, line, boost::is_any_of("\t "));
		assert(tokens.size() == 4 || tokens.size() == 5);
		
		std::string process = tokens[0];
		double xsec = stod(tokens[1]);
		double br = stod(tokens[2]);
		double filterEff = stod(tokens[3]);
		
		//std::string filename = directory + "_old/" + process + "/output/10_15_update_results.root";
		//std::string filename = directory + "/" + process + "/output/validation_Nov3.root";
		//std::string filename = directory + "/" + process + "/output/validation_Nov6.root";
		std::string filename = directory + "/" + process + "/output/validation_Dec9.root";
		
		PhysicsContribution* signal = new PhysicsContribution("signal", filename, xsec*br*filterEff, TString::Format("Seesaw%d", i), false, "treeR", -1, 0);
		signal->addWeight("WEIGHT[0]");
		signal->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		signals.push_back(signal);
	}
	ifile.close();
	
	////////////////////////
	// Prepare directory //
	////////////////////////
	time_t now = time(0);
	tm* localtm = localtime(&now);
	char buffer [14];
	strftime (buffer,14,"%y%m%d%H%M%S",localtm);
	TString timestamp = string(buffer);
	
	TString base = "Seesaw_";
	TString dirname = timestamp + base + mass;
	
	mkdir(dirname, 0755);
	chdir(dirname);
	system("cp -L ../SeesawInclusiveBins13.C ../helperAnalysisPresenter.C .");
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler(ofname, "RECREATE");
	init(assembler);
	
	assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	//assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("fullPrecision");
	assembler->setMode("noRatioPlot");
	
	setupData(assembler);
	setupBackgroundMC(assembler);
	setupBackgroundDD(assembler, "", true);
	
	assembler->addBundle(new Bundle("signal", "Seesaw"));
	assembler->addBundle(new Bundle("signal", "SignalBundle"));
	assembler->getBundle("SignalBundle")->addComponent(assembler->getBundle("Seesaw"));
	
	for(const auto &signal : signals) {
		applyUncertainties(assembler, signal);
		signal->addFlatUncertainty("lumi", 0.046);
		signal->addFlatUncertainty("signalXsec", 0.3);
		assembler->addContribution(signal);
		assembler->getBundle("Seesaw")->addComponent(signal);
	}
	
	assembler->getBundle("SignalBundle")->print();

	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
//	assembler->save();
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	std::vector<Channel*> channels;
	
	assembler->project("gaus", false)->plot(false)->SaveAs("gaus.pdf");
	
	// Inclusive plots: L3Tau0
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->project("QLIGHTLEPTONS", false)->plot(false)->SaveAs("L3Tau0_Q.pdf");
	assembler->channel("L3Tau0")->datacard();
	
	ChannelCollection* ccQ = new ChannelCollection("L3Tau0_Q");
	
	assembler->setRange("QLIGHTLEPTONS", -2, 0);
	assembler->channel("L3Tau0QN")->datacard();
	ccQ->addChannel(assembler->channel("L3Tau0QN")->bundle(assembler->getBundle("SignalBundle")));
	
	assembler->setRange("QLIGHTLEPTONS", 0, +2);
	assembler->channel("L3Tau0QP")->datacard();
	ccQ->addChannel(assembler->channel("L3Tau0QP")->bundle(assembler->getBundle("SignalBundle")));
	
	ccQ->datacard(ccQ->getName() + TString(".txt"), false);
	assembler->setRange("QLIGHTLEPTONS");
	
	assembler->setRange("AIC", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	addMETchannels(channels, assembler, "L3DY0");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	addMETchannels(channels, assembler, "L3DYz1");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 11, z-zWidth, false);
	assembler->setRange("AIC", 0, 0);
	//addMETchannels(channels, assembler, "L3DYl1AIC0");
	assembler->setRange("AIC", 1, 1);
	//addMETchannels(channels, assembler, "L3DYl1AIC1");
	assembler->setRange("AIC");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", z+zWidth);
	addMETchannels(channels, assembler, "L3DYh1");
	
	assembler->setRange();
	
	// Inclusive plots: L4Tau0
	assembler->setRange("NLEPTONS", 4);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	//addMETchannels(channels, assembler, "L4DY0");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	addMETchannels(channels, assembler, "L4DYz1");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 0, 0);
	addMETchannels(channels, assembler, "L4DYn1");
	
	assembler->setRange("NOSSF", 2);
	assembler->setRange("ONZ", 1, 1);
	addMETchannels(channels, assembler, "L4DYz2");
	
	assembler->setRange("NOSSF", 2);
	assembler->setRange("ONZ", 0, 0);
	addMETchannels(channels, assembler, "L4DYn2");

	assembler->setRange();
	
	std::vector<TString> channelNames = {
		"L3DY0LTMET350to550",
		"L3DYh1LTMET350to550",
		"L3DYh1LTMET550to750",
		"L3DY0LTMET550to750",
		"L4DYz1LTMET550to750",
		"L4DYz1LTMET350to550",
		"L3DYh1LTMET750to950",
		"L3DYz1LTMET350to550",
		"L3DY0LTMET750to950",
		"L3DYz1LTMET550to750",
	};
	
	ChannelCollection* ccGrand = new ChannelCollection("grandCollection");
	ChannelCollection* ccSelected = new ChannelCollection("selectedCollection");
	for(auto &channel : channels) {
		// Bundle the signal and add to grand collection
		channel = channel->bundle(assembler->getBundle("SignalBundle"));
		ccGrand->addChannel(channel);
		if(std::find(channelNames.begin(), channelNames.end(), channel->getName()) != channelNames.end()) {
			ccSelected->addChannel(channel);
		}
		
		//channel->plot(false)->SaveAs(channel->getName() + TString(".pdf"));
		
		ChannelCollection* ccSingle = new ChannelCollection(channel->getName());
		ccSingle->addChannel(channel);
		ccSingle->datacard(ccSingle->getName() + TString(".txt"), false);
	}
	ccGrand->datacard(ccGrand->getName() + TString(".txt"));
	if(ccSelected->getChannels().size() > 0) {
		ccSelected->datacard(ccSelected->getName() + TString(".txt"), false);
	}
	
	delete assembler;
	
	cout << dirname << endl;
}
