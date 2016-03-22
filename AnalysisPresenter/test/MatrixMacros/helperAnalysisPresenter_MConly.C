#include <iostream>
#include <TH1.h>
#include <boost/algorithm/string.hpp>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

// ----------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------
// Load library, see https://root.cern.ch/phpBB2/viewtopic.php?f=3&t=19471
namespace {
  int loadMyLibraryTriggerFunc() {
    gSystem->Load("libRutgersIAFAnalysisPresenter.so");
    return 0;
  }
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------
/*
void applyUncertaintiesAndScaleFactors(Assembler* assembler, PhysicsContribution* contribution) {
	if(!contribution->isMC()) {
		return;
	}
	
	// Approximate implementation of https://twiki.cern.ch/twiki/bin/view/CMS/SUSLeptonSF?rev=92#Summary_of_needed_SF_for_Decembe
	// MET identity condition is to work around https://sft.its.cern.ch/jira/browse/ROOT-7993
	contribution->addWeight("(EVENT[0] == EVENT[0]) * pow(0.991*0.999*1.000, Sum$(abs(ETAGOODMUONS) < 2.4)) * pow(0.968*0.993*0.992, Sum$(abs(ETAGOODMUONS) > 2.4))");
	contribution->addWeight("(EVENT[0] == EVENT[0]) * pow(0.99, Sum$(abs(ETAGOODELECTRONS) < 1.442)) * pow(0.98, Sum$(abs(ETAGOODELECTRONS) > 1.442))");
	contribution->addRelativeUncertainty("lepIDTrigger", "0.03");
	if(!assembler->getMode("noTTsystematics")) {
		//contribution->addRelativeUncertainty("bTag", (contribution->getName()).BeginsWith("TT", TString::kIgnoreCase) ? "0.1" : "0");
	}
	
	if(assembler->getMode("fullPrecision") && !assembler->getMode("noSystVariations")) {
		// See https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
		contribution->addVariation("METunc", make_pair("MET", "0.5 * (18.5*sqrt(2)) * sqrt(-log(rndm())) * cos(6.2831853 * rndm()) + _MET"));
	}
}
*/
// ----------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------
void init(Assembler* assembler) {
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
	//gStyle->SetErrorX(0);
	//
	assembler->addBundle(new Bundle("data", "Data", false, 1));
	//

	assembler->addBundle(new Bundle("background", "presentationBundle"));
	//
	assembler->addBundle(new Bundle("background", "Misidentified",                 false, 42));
	//
	assembler->addBundle(new Bundle("background", "QCD_Pt-170to300_MuEnrichedPt5", false, 2));
	assembler->addBundle(new Bundle("background", "QCD_Pt-170to300_EMEnriched",    false, 2));
	assembler->addBundle(new Bundle("background", "TTJets_DiLept",                 false, 2));
	assembler->addBundle(new Bundle("background", "DYJets",                        false, 2));
	assembler->addBundle(new Bundle("background", "WJetsToLNu",                    false, 2));
	//
	assembler->addBundle(new Bundle("background", "WZ",      false, 38 ));
	assembler->addBundle(new Bundle("background", "Higgs",   false, 38 ));
	assembler->addBundle(new Bundle("background", "Rare MC", false, 33 ));
}

std::string getDataFileName() {
	return "20151203_data";
}

void prepare(Assembler* assembler) {

        Bundle* presentationBundle = assembler->getBundle("presentationBundle");
	for(const auto &bundleName : {"TTJets_DiLept"}) {
		Bundle* bundle = assembler->getBundle(bundleName);
		if(bundle->getComponents().size() > 0) {
			presentationBundle->addComponent(bundle);
		}
	}
	//
	if(assembler->getDefaultBundle()) {
		assembler->getDefaultBundle()->print();
	}

}

/*
void setupData(Assembler* assembler, bool dilep = false, int fakeMode = 0, bool applyEventVetos = false) {
  cout<<"setupData RUN"<<endl;
  //std::string prefix = "/cms/thomassen/2015/Analysis/data/results/";
        std::string prefix = "";
	std::string infix = dilep ? "" : ".3L";
	std::string body = getDataFileName();
	std::string suffix = ".root";
	
	PhysicsContribution* data = 0;
	
	if(fakeMode == 0) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2251, "2.25/fb@13TeV");
	} else if(fakeMode == 1) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2251, "2.25/fb@13TeV", false, "treeRfakeTracks");
	} else if(fakeMode == 2) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2251, "2.25/fb@13TeV", false, "treeRfakePhotons");
	} else if(fakeMode == 3) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2251, "2.25/fb@13TeV", false, "treeRfakeTaus");
	} else {
		cout << "unsure what to do";
		exit(1);
	}
	
	data->addWeight("TRIGGERACCEPT");
	//data->addVariation("JECv6", make_pair("MET", "1.03 * _MET"));
	
	std::vector<string> vetoFilenames = {
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/csc2015_Dec01.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/ecalscn1043093_Dec01.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/badResolutionTrack_Jan13.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/muonBadTrack_Jan13.txt",
	};
	if(!applyEventVetos) {
		vetoFilenames.clear();
	}
	
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
*/

/*
void setupDataSingle(Assembler* assembler, bool fake = false, bool dilep = false) {
  cout<<"setupDataSingle RUN"<<endl;
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".root";
	
	PhysicsContribution* data = 0;
	
	assembler->addContribution(data);
}
*/

void setupBackgroundMC(Assembler* assembler, bool dilep = false, bool ttbar = true, bool onlyTTF = false) {
  cout<<"setupBackgroundMC RUN"<<endl;
        //std::string prefix = "/cms/thomassen/2015/Analysis/simulation/results/";
	std::string prefix = "/afs/cern.ch/user/h/hsaka/Multilepton/TEST-Mar5/CMSSW_7_6_3_patch2/src/RootFiles/EAtreesMatrix/";
	//std::string prefix = "/afs/cern.ch/user/h/hsaka/Multilepton/TEST-Mar5/CMSSW_7_6_3_patch2/src/RootFiles/EAtreesRA7/";
	//std::string infix = dilep ? "" : ".3L";
	std::string infix = "";
	std::string suffix = ".simulation.root";
	
	double xsec_dummy    = 1;

	
	std::vector<PhysicsContribution*> mc;
	std::vector<PhysicsContribution*> mcH;
	std::vector<PhysicsContribution*> mcRare;

	//PhysicsContribution* dyjetstollM50 = new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-50" + infix + suffix, xsec_dummy, "DYJetsToLL_M-50", false, "treeR", -1, 0);
	//mc.push_back(dyjetstollM50);

	PhysicsContribution* ttjetsdilep = new PhysicsContribution("backgroundMC", prefix + "TTJets_DiLept" + infix + suffix, xsec_dummy, "TTJets_DiLept", false, "treeR", -1, 0);
	mc.push_back(ttjetsdilep);

	
	for(auto &contribution : mc) {
	  //contribution->addWeight("WEIGHT[0]");
	  //contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
	  //applyUncertaintiesAndScaleFactors(assembler, contribution);
	  assembler->addContribution(contribution);
	}


	//PhysicsContribution* dataDummy = new PhysicsContribution("data", prefix + "DYJetsToLL_M-50" + infix + suffix, 2300, "2.3/fb@13TeV");
	PhysicsContribution* dataDummy = new PhysicsContribution("data", prefix + "TTJets_DiLept" + infix + suffix, 2300, "2.3/fb@13TeV");
	dataDummy->addWeight("0");
	assembler->addContribution(dataDummy);
}

/*
void setupBackgroundDD(Assembler* assembler, TString option = "", bool syst = true) {
        //std::string prefix = "/cms/thomassen/2015/Analysis/data/results/";
        std::string prefix = "";
	std::string body = getDataFileName();
	std::string suffix = ".3L.root";
	
	TString nVertexWeight = "0.773 + 0.0218 * NVERTICES[0]";
	//nVertexWeight = "1";
	
	////// Tracks
	PhysicsContribution* fakeTracks = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakeTracks", false, "treeRfakeTracks", (option == "justTracks") ? kWhite : -1);
	fakeTracks->addWeight("TRIGGERACCEPT");
	fakeTracks->addWeight(
		"(Sum$(fakeRoleGOODELECTRONS) > 0)"
			" * ( (Min$(PTGOODELECTRONS) < 100) * (-0.23 + 0.07 * Min$(PTGOODELECTRONS)) + !(Min$(PTGOODELECTRONS) < 100) )"
		" + (Sum$(fakeRoleGOODMUONS) > 0)"
			" * ( (Min$(PTGOODMUONS) < 25) * (0.00 + 0.07 * Min$(PTGOODMUONS)) + !(Min$(PTGOODMUONS) < 25) )"
	);
	fakeTracks->addWeight(nVertexWeight);
	fakeTracks->addRelativeUncertainty("fakePileupWeight", TString::Format("1 - 1/(%s)", nVertexWeight.Data()));
	applyUncertaintiesAndScaleFactors(assembler, fakeTracks);
	if(syst && !assembler->getMode("noTrackSystematics")) {
		//fakeTracks->addFlatUncertainty("trackFakeRateFit", 0.06);
		//fakeTracks->addFlatUncertainty("trackPtFit", 0.10);
		fakeTracks->addFlatUncertainty("trackFakes", 0.14);
		fakeTracks->addFlatUncertainty("photonFakes", -0.080); // based on 52% variation of photon contribution in track fake rate measurement region
		fakeTracks->addFlatUncertainty("normalizationWZ", -0.033); // based on 7.3% variation of WZ in track fake rate measurement region
	}
	if(option != "noTracks" && option != "justTaus" && option != "justPhotons" && option != "fakeTaus2L") {
		assembler->getBundle("TrackFakes")->addComponent(fakeTracks);
		assembler->addContribution(fakeTracks);
	}
	
	////// Photons
	PhysicsContribution* fakePhotons = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakePhotons", false, "treeRfakePhotons");
	fakePhotons->addWeight("TRIGGERACCEPT");
	fakePhotons->addWeight(nVertexWeight);
	fakePhotons->addRelativeUncertainty("fakePileupWeight", TString::Format("1 - 1/(%s)", nVertexWeight.Data()));
	applyUncertaintiesAndScaleFactors(assembler, fakePhotons);
	if(syst && !assembler->getMode("noPhotonSystematics")) {
		fakePhotons->addFlatUncertainty("photonFakes", 0.52); // due to photonDR
		fakePhotons->addFlatUncertainty("trackFakes", -0.056); // based on 14% variation of track contribution in photon fake rate measurement region
		fakePhotons->addFlatUncertainty("normalizationWZ", -0.0018); // based on 7.3% variation of WZ in photon fake rate measurement region
	}
	if(option != "noPhotons" && option != "justTracks" && option != "justTaus" && option != "fakeTaus2L") {
		assembler->getBundle("PhotonFakes")->addComponent(fakePhotons);
		assembler->addContribution(fakePhotons);
	}
}

void setupFakeRates(Assembler* assembler) {
	// We found that NGOODJETS and HT binning does not work very well; NPROMPTINCLUSIVETRACK7 binning does a good job at least in 0b regions.
	assembler->setFakeRate("nTrackFakeMuons",
		"0.0149"
		" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	assembler->setFakeRate("nTrackFakeElectrons",
		"(NGOODELECTRONS[0] == 1) * 0.0175 + (NGOODELECTRONS[0] == 3) * 0.0137 + !(NGOODELECTRONS[0] == 1 || NGOODELECTRONS[0] == 3) * 0.0159"
		" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	
	// Photon fake rates for Asymmetric Internal Conversions (AIC)
	// AIC reduces the pt of the emitting lepton, and can push on-Z pairs below the Z peak. This causes migration between on-Z/off-Z etc.
	// Looking at the AIC control region, we find that we should adjust the fake rate outside MLEPTONS = 75..100.
	assembler->setFakeRate("nPhotonFakeMuons",
//		"(NLIGHTLEPTONS[0]==3)*0.0175"
		"((NLIGHTLEPTONS[0]==3&&NGOODMUONS[0]==1)*0.0160"
		" + (NLIGHTLEPTONS[0]==3&&NGOODMUONS[0]==3)*0.0105"
		" + (NLIGHTLEPTONS[0]!=3||!(NGOODMUONS[0]%2))*0.014)" // this is currently a wild guess, but should be measured (because of relative fractions)
		" * (1 + 0.8 * (abs(MLIGHTLEPTONS[0]-87.5) > 12.5))"
//		" * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		" * Alt$(Sum$(abs(goodMuonsDRgoodLeptons - 0.45) < 0.15 && fakeRoleGOODMUONS > 0) > 0, 0)" // only stuff emitted close to leptons
		" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	assembler->setFakeRate("nPhotonFakeElectrons",
//		"(NLIGHTLEPTONS[0]==3)*0.035"
		"((NLIGHTLEPTONS[0]==3&&NGOODELECTRONS[0]==1)*0.035"
		" + (NLIGHTLEPTONS[0]==3&&NGOODELECTRONS[0]==3)*0.045"
		" + (NLIGHTLEPTONS[0]!=3||!(NGOODELECTRONS[0]%2))*0.040)" // this is currently a wild guess, but should be measured (because of relative fractions)
		" * (1 + 0.8 * (abs(MLIGHTLEPTONS[0]-87.5) > 12.5))"
//		" * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		" * Alt$(Sum$(abs(goodElectronsDRgoodLeptons - 0.45) < 0.15 && fakeRoleGOODELECTRONS > 0) > 0, 0)" // only stuff emitted close to leptons
		" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
}
*/

// ----------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------

#include <TCanvas.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TStyle.h>

TCanvas* makeNicePlot(TCanvas* c, TString axistitle = "", TString unit = "", TString preliminary = "Preliminary", bool noRatio = false) {
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	c->cd();
	c->SetTopMargin(0.001);
	c->SetRightMargin(0.001);
	c->SetBottomMargin(0.001);
	c->SetLeftMargin(0.001);

	TPad* pad1 = (TPad*)c->GetPrimitive("pad1");
	pad1->SetRightMargin(0.03);
	//pad1->SetBottomMargin(0.01);
	pad1->SetTopMargin(0.07);
	TPad* pad2 = (TPad*)c->GetPrimitive("pad2");
	pad2->SetTopMargin(0.01);
	pad2->SetRightMargin(0.03);
	pad2->SetBottomMargin(0.25);

	//pad1->RedrawAxis();
	pad2->RedrawAxis();

	pad1->cd();
	TList* list = pad1->GetListOfPrimitives();
	cout<<"make nice plot "<<list->GetEntries()<<endl;
	TH1* h = 0;
	TLegend* legend = 0;
	for(int i = 0; i < list->GetEntries(); i++) {
		TObject* obj = list->At(i);
		TString cname(obj->ClassName());
		if(cname.Contains("TH1")){
			h = ((TH1*)obj);
			((TH1*)obj)->SetStats(false);
		} else if(cname == "TLegend") {
			legend = ((TLegend*)obj);
		}
	}
	legend->SetFillColor(kWhite);
	double max = h->GetMaximum();
	double min = h->GetMinimum();
	pad1->Range(0, 0, 1, 1);
	legend->SetX1(0.63); legend->SetX2(1.0);
	legend->SetY1(0.51); legend->SetY2(0.9);

	for(auto pad : {pad1, pad2}) {
		TList* list2 = pad->GetListOfPrimitives();
		for(int i = 0; i < list2->GetEntries(); i++){
			TObject* obj = list2->At(i);
			TString cname(obj->ClassName());
			if(cname.Contains("TH1")) {
				if(pad == pad1) {
					if(!noRatio) {
						((TH1*)obj)->GetXaxis()->SetTitle("");
					}
					if(unit != "") {
						float offsetY = ((TH1*)obj)->GetYaxis()->GetTitleOffset();
						float fontsizeY = ((TH1*)obj)->GetYaxis()->GetTitleSize();
						((TH1*)obj)->GetYaxis()->SetTitleOffset(1*offsetY);
						((TH1*)obj)->GetYaxis()->SetTitleSize(1.3*fontsizeY);
						TString axisTitleY = TString::Format("Events / %d %s", (int)(((TH1*)obj)->GetBinWidth(1)), unit.Data());
						((TH1*)obj)->GetYaxis()->SetTitle(axisTitleY);
					}
				}
				if(pad == pad2 || noRatio) {
					float offsetX = ((TH1*)obj)->GetXaxis()->GetTitleOffset();
					float fontsizeX = ((TH1*)obj)->GetXaxis()->GetTitleSize();
					((TH1*)obj)->GetXaxis()->SetTitleOffset(1*offsetX);
					((TH1*)obj)->GetXaxis()->SetTitleFont(42);
					if(noRatio) {
						((TH1*)obj)->GetXaxis()->SetTitleSize(1.25*fontsizeX);
						((TH1*)obj)->GetXaxis()->SetLabelSize(0.05);
					} else {
						((TH1*)obj)->GetXaxis()->SetTitleSize(1.75*fontsizeX);
					}
					if(axistitle != "" && TString(((TH1*)obj)->GetXaxis()->GetTitle()) != ""){
						TString axisTitleX = axistitle;
						if(unit != "") {
							axisTitleX += TString::Format(" [%s]", unit.Data());
						}
						((TH1*)obj)->GetXaxis()->SetTitle(axisTitleX);
					}
				}
				if(pad == pad2) {
					((TH1*)obj)->GetYaxis()->SetNdivisions(50206);
					float offsetY = ((TH1*)obj)->GetYaxis()->GetTitleOffset();
					float fontsizeY = ((TH1*)obj)->GetYaxis()->GetTitleSize();
					((TH1*)obj)->GetYaxis()->SetTitleOffset(0.65*offsetY);
					((TH1*)obj)->GetYaxis()->SetTitleSize(1.75*fontsizeY);
				}
			}
		}
	}
	
	c->cd();
	
	TLatex* latex = new TLatex;
	latex->SetNDC();
	latex->SetTextFont(61);
	latex->SetTextSize(0.04);
	latex->DrawLatex(0.13, noRatio ? 0.86 : 0.89, "CMS");
	latex->SetTextFont(52);
	latex->DrawLatex(0.13, noRatio ? 0.81 : 0.84, preliminary);
	
	latex->SetTextSize(0.035);
	latex->SetTextFont(42);
	if(!preliminary.Contains("Simulation", TString::kIgnoreCase)) {
		latex->DrawLatex(0.76, 0.96, "2.3 fb^{-1} (13 TeV)");
	}
	
	c->Update();
	pad1->Update();
	pad2->Update();
	
	return c;
}

void writeUncertainties(AssemblerProjection* projection, TString type) {
	cout << endl << "====== now printing uncertainties for contributions of type " << type << endl;
	if(!projection->has(type)) {
		cerr << "Projection does not have contributions of type " << type << endl;
		return;
	}
	
	auto uncertaintyNames = projection->getUncertaintyNames();
	for(int i = 1; i <= 5; ++i) {
		cout << endl;
		cout << "BIN " << i << endl;
		cout << "TOTAL:";
		cout << " " << projection->getBin(type, i);
		cout << " pm " << projection->getBinStat(type, i) << " pm " << projection->getBinSyst(type, i) << endl;
		for(const auto &uncertaintyName : uncertaintyNames) {
			cout << "uncertainty name: " << uncertaintyName << " " << projection->getBinSyst(type, i, uncertaintyName) << endl;
		}
		cout << endl;
		
		for(const auto &bundleName : projection->getBundleNames(type)) {
			cout << "bundleName: " << bundleName;
			cout << " " << projection->getBin(type, i, bundleName);
			cout << " pm " << projection->getBinStat(type, i, bundleName) << endl;
			for(const auto &uncertaintyName : uncertaintyNames) {
				cout << "uncertainty name: " << uncertaintyName << " " << projection->getBinSyst(type, i, uncertaintyName, bundleName) << endl;
			}
		}
	}
}


void SaveHistograms(TCanvas* c, TString outfilename)
{
  bool isdebug=false;
  c->cd();
  TPad* pad1 = (TPad*)c->GetPrimitive("pad1");
  TPad* pad2 = (TPad*)c->GetPrimitive("pad2");
  
  pad1->cd();
  TList* list = pad1->GetListOfPrimitives();
  TH1* h = 0;
  THStack* ths = 0;
  std::vector<TH1*> histVector;
  //
  for(int i = 0; i < list->GetEntries(); i++){
    //
    TObject* obj = list->At(i);
    TString cname(obj->ClassName());
    if(isdebug) std::cout<<"cname: "<<cname<<std::endl;
    //
    // MC stack histos
    if(cname.Contains("THStack")){
      ths = ((THStack*)obj);
      TList* hists = ths->GetHists();
      TIterator* iter = new TListIter(hists);
      while(TH1* h = (TH1*)iter->Next()) {
        if(isdebug){ 
            std::cout<<h->GetName()<<std::endl;
            std::cout<<"new Integral(): "<<h->Integral(0,h->GetNbinsX()+1)<<std::endl;
            for( int ibin=0; ibin<h->GetNbinsX()+1; ibin++){
              std::cout<<"Bin("<<ibin<<"): "<<h->GetBinContent(ibin)<<" +/- "<<h->GetBinError(ibin)<<std::endl;
            }
        }
        histVector.push_back(h);
      }
    }
    //
    // Data
    if(cname.Contains("TH1")){
      h = ((TH1*)obj);
      TString histoname(h->GetName());
      if(histoname.Contains("13TeV")){
        if(isdebug){ 
            std::cout<<h->GetName()<<std::endl;
            std::cout<<"new Integral(): "<<h->Integral(0,h->GetNbinsX()+1)<<std::endl;
            for( int ibin=0; ibin<h->GetNbinsX()+1; ibin++){
                std::cout<<"Bin("<<ibin<<"): "<<h->GetBinContent(ibin)<<" +/- "<<h->GetBinError(ibin)<<std::endl;
            }
        }
        histVector.push_back(h);
      }
    }
    //
  }
  
  TFile* outfile = new TFile(outfilename,"RECREATE");
  outfile->cd();
  for(std::vector<TH1*>::iterator it = histVector.begin(); it != histVector.end(); ++it) {
    if(isdebug) std::cout<<"histVector name: "<<(*it)->GetName()<<std::endl;
    TString histoname((*it)->GetName());
    if(histoname.Contains("13TeV")){//Clean up data histo name and title
      (*it)->SetTitle("Data");
      (*it)->Write("Data");
    }
    else{
      (*it)->SetTitle(histoname);
      (*it)->Write(histoname);
    }
  }
  outfile->ls();
  outfile->Close();
}
