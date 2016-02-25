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
	assembler->project("LT+MET", true)->bundle(assembler->getBundle("SignalBundle"))->plot(true)->SaveAs(name + TString(".pdf"));
	makeNicePlot(assembler->project("LT+MET", true)->bundle(assembler->getBundle("SignalBundle"))->plot(true), "L_{T} + E_{T}^{miss}", "GeV")->SaveAs(TString("../nicePlots/") + name + TString(".pdf"));
	//assembler->project("LT", true)->plot(true)->SaveAs(name + TString("_LT.pdf"));
	//makeNicePlot(assembler->project("LT", true)->plot(true), "LT [GeV]")->SaveAs(TString("../nicePlots/") + name + TString("_LT.pdf"));
	//assembler->project("LT+MET", true)->plot(true)->SaveAs(name + TString("_LT+MET.pdf"));
	//makeNicePlot(assembler->project("LT+MET", true)->plot(true), "L_{T} + E_{T}^{miss} [GeV]")->SaveAs(TString("../nicePlots/") + name + TString("_LT+MET.pdf"));
	
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

void SeesawInclusiveBins13(std::string mass = "420", TString ofname = "test.root") {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	double z = 91;
	double zWidth = 10;
	
	// Specify axes and bins of multidimensional histogram
	// For inclusive table
	std::string varexp = "NLIGHTLEPTONS{2,6}:MOSSF{11,131,36}:NOSSF{0,3}:ONZ{0,2}:NGOODTAUS{0,2}:NGOODJETS{0,5}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,500,10}";
	varexp += std::string(TString::Format(":(NLIGHTLEPTONS == 3 && (abs(MOSSF-%f)>%f) && abs(MLIGHTLEPTONS-%f) < %f){0,2,\"AIC\"}", z, zWidth, 87.5, 12.5).Data());
	varexp += ":(Sum$(QGOODMUONS) + Sum$(QGOODELECTRONS)){-2.5,2.5,\"QLIGHTLEPTONS\"}";
	varexp += ":Alt$(PTGOODELECTRONS[0],0){20,320,15,\"minElectronPT\"}";
	varexp += ":Alt$(PTGOODMUONS[0],0){20,320,15,\"minMuonPT\"}";
	varexp += ":LT{0,600,30}";
	varexp += ":Alt$(MT,-1){0,200,5,\"MT\"}";
	//varexp += ":LT+MET{-50,1150,6}";
	varexp += ":LT+MET{350,1150,4}";
	varexp += ":PTGOODLEPTONS[0]{0,500,25}";
	varexp += ":MLIGHTLEPTONS{0,600,15}";
	varexp += ":(sqrt(2) * 18.5 * sqrt(-log(rndm())) * cos(6.2831853 * rndm())){-50,50,100,\"gaus\"}";
	varexp += ":(NLIGHTLEPTONS[0] == 3 && ONZ && MET[0] > 50 && MET[0] < 100){0,2,\"WZ\"}";
	
	// Global cuts, if desired
	TString selection = "PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10";
	//selection += " && NGOODTAUS[0] == 0 && NBJETSCSVM[0] == 0"; // no taus or b-tags
	selection += " && !(NLIGHTLEPTONS[0] == 3 && ONZ && MET[0] < 100)"; // veto WZ and Z+jets control regions
	selection += " && !(NLIGHTLEPTONS[0] == 4 && NOSSF[0] == 2 && ONZ && MET[0] < 50)"; // veto ZZ control region
	selection += " && !(NLIGHTLEPTONS[0] == 3 && NOSSF[0] == 1 && MOSSF[0] < 81)";
	selection += " && !(NLIGHTLEPTONS[0] > 3 && NOSSF[0] == 0)";
	
	// Padova style
/*	selection = "NLIGHTLEPTONS[0] == 3 && (Alt$((NGOODMUONS == 3 && PTGOODMUONS[0] > 30 && PTGOODMUONS[1] > 20 && PTGOODMUONS[2] > 20), 0) || Alt$((NGOODELECTRONS == 3 && PTGOODELECTRONS[0] > 30 && PTGOODELECTRONS[1] > 20 && PTGOODELECTRONS[2] > 20), 0) || Alt$((NGOODELECTRONS == 2 && PTGOODELECTRONS[0] > PTGOODMUONS[0] && PTGOODELECTRONS[0] > 30 && PTGOODELECTRONS[1] > 20 && PTGOODMUONS[0] > 20), 0) || Alt$((NGOODELECTRONS == 2 && PTGOODELECTRONS[0] < PTGOODMUONS[0] && PTGOODMUONS[0] > 30 && PTGOODELECTRONS[1] > 20 && PTGOODELECTRONS[0] > 20), 0) || Alt$((NGOODMUONS == 2 && PTGOODMUONS[0] > PTGOODELECTRONS[0] && PTGOODMUONS[0] > 30 && PTGOODMUONS[1] > 20 && PTGOODELECTRONS[0] > 20), 0) || Alt$((NGOODMUONS == 2 && PTGOODMUONS[0] < PTGOODELECTRONS[0] && PTGOODELECTRONS[0] > 30 && PTGOODMUONS[1] > 20 && PTGOODMUONS[0] > 20), 0))";
	selection += " && abs(Sum$(QGOODMUONS) + Sum$(QGOODELECTRONS)) == 1 && MET[0] > 50 && HT[0] < 150 && NBJETSCSVL[0] == 0 && (NOSSF[0] == 0 || abs(MOSSF[0]-91) > 15) && abs(MLIGHTLEPTONS[0]-91) > 15";
	selection += " && !(NLIGHTLEPTONS[0] == 3 && ONZ && MET[0] < 100)"; // veto WZ and Z+jets control regions
*/
	//TString selection = "";
	// Cut down charge flips
	//selection += " && (NLIGHTLEPTONS != 3 || (NGOODMUONS == 3 || NGOODELECTRONS == 3 || abs(NPOSGOODMUONS+NPOSGOODELECTRONS-NNEGGOODMUONS-NNEGGOODELECTRONS) != 3))";
	
	
	///////////////////////
	// Signal definition //
	///////////////////////
	
	//std::string mass = "220";
	//std::string mass = "340";
	//std::string mass = "380";
	//std::string mass = "420";
	//std::string mass = "500";
	//std::string mass = "660";
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
		double k = (tokens.size() == 5) ? stod(tokens[4]) : 1.0;
		
		//std::string filename = directory + "_old/" + process + "/output/10_15_update_results.root";
		//std::string filename = directory + "/" + process + "/output/validation_Nov3.root";
		//std::string filename = directory + "/" + process + "/output/validation_Nov6.root";
		//std::string filename = directory + "/" + process + "/output/validation_Dec9.root";
		//std::string filename = directory + "_Moriond/" + process + "/output/Moriond_prediction.root";
		std::string filename = directory + "/" + process + "/output/Moriond_prediction_fixedFakes.root";
		
		PhysicsContribution* signal = new PhysicsContribution("signal", filename, xsec*br*filterEff*k, TString::Format("Seesaw%d", i), false, "treeR", -1, 0);
		signal->addWeight("WEIGHT[0]");
		signal->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		signal->addWeight("EVENT[0] == EVENT[0]");
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
	assembler->setMode("fullPrecision");
	//assembler->setMode("noRatioPlot");
	
	setupData(assembler);
	setupBackgroundMC(assembler);
	setupBackgroundDD(assembler, "", true);
	
	TString bundleName = TString::Format("#splitline{Seesaw [X]}{(m_{#Sigma} = %s GeV)}", mass.c_str());
	assembler->addBundle(new Bundle("signal", bundleName));
	assembler->addBundle(new Bundle("signal", "SignalBundle"));
	assembler->getBundle("SignalBundle")->addComponent(assembler->getBundle(bundleName));
	
	for(const auto &signal : signals) {
		applyUncertaintiesAndScaleFactors(assembler, signal);
		signal->addFlatUncertainty("lumi", 0.046);
		//signal->addFlatUncertainty("signalXsec", 0.3);
		assembler->addContribution(signal);
		assembler->getBundle(bundleName)->addComponent(signal);
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
	
	assembler->setRange("WZ", 1, 1);
	makeNicePlot(assembler->project("MT", true)->bundle(assembler->getBundle("SignalBundle"))->plot(true), "M_{T} [GeV]")->SaveAs("WZ_contamination.pdf");
	assembler->project("MT", true)->print();
	assembler->setRange("WZ");
	
	assembler->setRange("NLIGHTLEPTONS", 3);
	
	assembler->project("LT+MET", true)->print();
	
	assembler->setRange("AIC", 0, 0);
/*	makeNicePlot(assembler->project("LT+MET", true)->bundle(assembler->getBundle("SignalBundle"))->plot(true), "L_{T} + E_{T}^{miss}", "GeV")->SaveAs("LT+MET.pdf");
	//makeNicePlot(assembler->project("LT+MET", true)->bundle(assembler->getBundle("SignalBundle"))->plot(true), "L_{T} + E_{T}^{miss}", "GeV", "Simulation Preliminary", true)->SaveAs("LT+MET.pdf");
	assembler->setRange("AIC");
	assembler->setRange("LT+MET", -50, 350);
	makeNicePlot(assembler->project("MET", true)->bundle(assembler->getBundle("SignalBundle"))->plot(false), "E_{T}^{miss} [GeV]")->SaveAs("LTMET0to350_MET.pdf");
	makeNicePlot(assembler->project("MT", true)->bundle(assembler->getBundle("SignalBundle"))->plot(false), "M_{T} [GeV]")->SaveAs("LTMET0to350_MT.pdf");
	makeNicePlot(assembler->project("NGOODJETS", true)->bundle(assembler->getBundle("SignalBundle"))->plot(false), "nJets")->SaveAs("LTMET0to350_NGOODJETS.pdf");
	makeNicePlot(assembler->project("PTGOODLEPTONS[0]", true)->bundle(assembler->getBundle("SignalBundle"))->plot(false), "leading lepton pT [GeV]")->SaveAs("LTMET0to350_PTGOODLEPTONS0.pdf");
	makeNicePlot(assembler->project("MLIGHTLEPTONS", true)->bundle(assembler->getBundle("SignalBundle"))->plot(false), "all lepton invariant mass [GeV]")->SaveAs("LTMET0to350_MLIGHTLEPTONS.pdf");*/
	
	assembler->setRange();
	
	// Inclusive plots: L3Tau0
	assembler->setRange("NLIGHTLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	makeNicePlot(assembler->project("QLIGHTLEPTONS", false)->bundle(assembler->getBundle("SignalBundle"))->plot(false), "Sum of lepton charges")->SaveAs("L3Tau0_Q.pdf");
	assembler->channel("L3Tau0")->datacard();
	
	ChannelCollection* ccQ = new ChannelCollection("L3Tau0_Q");
	
	assembler->setRange("QLIGHTLEPTONS", -1.5, -0.5);
	assembler->channel("L3Tau0QN")->datacard();
	ccQ->addChannel(assembler->channel("L3Tau0QN")->bundle(assembler->getBundle("SignalBundle")));
	
	assembler->setRange("QLIGHTLEPTONS", 0.5, 1.5);
	assembler->channel("L3Tau0QP")->datacard();
	ccQ->addChannel(assembler->channel("L3Tau0QP")->bundle(assembler->getBundle("SignalBundle")));
	
	ccQ->datacard(ccQ->getName() + TString(".txt"), false);
	assembler->setRange("QLIGHTLEPTONS");
	
	assembler->setRange("AIC", 0, 0);
	
	assembler->setRange("LT+MET", 350);
	makeNicePlot(assembler->project("MET", true)->plot(false), "E_{T}^{miss} [GeV]")->SaveAs("L3Tau0LTMETgt350_MET.pdf");
	makeNicePlot(assembler->project("MT", true)->plot(false), "M_{T} [GeV]")->SaveAs("L3Tau0LTMETgt350_MT.pdf");
	makeNicePlot(assembler->project("NGOODJETS", true)->plot(false), "nJets")->SaveAs("L3Tau0LTMETgt350_NGOODJETS.pdf");
	makeNicePlot(assembler->project("PTGOODLEPTONS[0]", true)->plot(false), "leading lepton pT [GeV]")->SaveAs("L3Tau0LTMETgt350_PTGOODLEPTONS0.pdf");
	makeNicePlot(assembler->project("MLIGHTLEPTONS", true)->plot(false), "all lepton invariant mass [GeV]")->SaveAs("L3Tau0LTMETgt350_MLIGHTLEPTONS.pdf");
	assembler->setRange("LT+MET");
	assembler->setRange("NGOODTAUS");
	
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
	assembler->setRange("NLIGHTLEPTONS", 4);
	//assembler->setRange("NGOODTAUS", 0, 0);
	
	//assembler->setRange("NOSSF", 0, 0);
	//addMETchannels(channels, assembler, "L4DY0");
	
	assembler->setRange("NOSSF", 1);
	addMETchannels(channels, assembler, "L4DYgt0");
	
	/*assembler->setRange("NOSSF", 1, 1);
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
*/
	assembler->setRange();
	
	std::vector<TString> channelNames = {
		"L3DYh1LTMET550to750",
		"L3DYh1LTMET350to550",
		"L3DY0LTMET350to550",
		"L3DY0LTMET550to750",
		"L4DYgt0LTMET550to750",
		"L4DYgt0LTMET350to550",
		"L3DYz1LTMET350to550",
		"L3DYz1LTMET550to750",
		"L3DYh1LTMET750to950",
		"L3DY0LTMET750to950",
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
		ccSingle->datacard(ccSingle->getName() + TString(".txt"), true);
	}
	ccGrand->datacard(ccGrand->getName() + TString(".txt"), true, 1., 1., 0.1);
	if(ccSelected->getChannels().size() > 0) {
		ccSelected->datacard(ccSelected->getName() + TString(".txt"), true);
	}
	
	delete assembler;
	
	cout << dirname << endl;
}
