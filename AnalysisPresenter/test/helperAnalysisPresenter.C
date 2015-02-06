#include <iostream>
#include <TH1.h>
#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

void init(Assembler* assembler) {
	assembler = assembler; // Avoid compiler message about unused variable
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
}

void setupData(Assembler* assembler, bool fake = false, bool dilep = false) {
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".root";
	
	PhysicsContribution* data = fake
		? new PhysicsContribution("data", prefix + "20141215_fakeTracks" + infix + suffix, 19500, "2012data")
		: new PhysicsContribution("data", prefix + "20141215_data" + infix + suffix, 19500, "2012data");
	
	assembler->addContribution(data);
}

void setupDataSingle(Assembler* assembler, bool fake = false, bool dilep = false) {
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".root";
	
	PhysicsContribution* data = fake
		? new PhysicsContribution("data", prefix + "20140827_fakeTracksSingle+Double" + infix + suffix, 19500, "2012trackFakeSeed")
		: new PhysicsContribution("data", prefix + "20140827_dataSingle" + infix + suffix, 19500, "2012data");
	
	assembler->addContribution(data);
}

void setupBackgroundMC(Assembler* assembler, bool dilep = false, bool ttbar = true, bool onlyTTF = false) {
	std::string prefix = "/cms/thomassen/2014/Analysis/simulation/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".simulation.root";
	
	// Richard's numbers
	// Branching ratios
//	Double_t WtoLNu = 0.3203;
//	Double_t Wto2J = (1.0-0.3203);
	// Cross sections [pb]
//	Double_t xsec_ttbar = 225.0;
//	Double_t xsec_ttbar_fullLep = pow(WtoLNu,2)*xsec_ttbar;
//	Double_t xsec_ttbar_semiLep = 2.0*WtoLNu*Wto2J*xsec_ttbar;
//	Double_t xsec_wz = 32.3*(0.3257*0.10095)*1.20;
	Double_t xsec_zz = 0.92*17.7*(0.10095*0.10095)*1.08;
	xsec_zz *= 0.97 * 1.028;
	Double_t xsec_ttw = 0.23;
	Double_t xsec_ttz = 0.208;
	
	// Peter's numbers
	double xsec_ttbar_fullLep = 23.08;
	double xsec_ttbar_semiLep = 97.97 * 1.32;
	double xsec_wz = 1.2451;
	xsec_wz *= 0.957;
//	double xsec_zz = 0.181;
//	double xsec_ttw = 0.2149;
//	double xsec_ttz = 0.208;
	
	//ttbar = false;
	
	std::vector<PhysicsContribution*> mc;
	std::vector<PhysicsContribution*> mcH;
	
	PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZJetsTo3LNu" + infix + suffix, xsec_wz, "WZ");
	wz->addWeight("exp(-0.005 * PTMCZ[0]/sqrt(MMCZ[0]))", 1.038);
	wz->addWeight("(NGOODJETS[0] == 0) * 1.06 + (NGOODJETS[0] == 1) * 0.89 + (NGOODJETS[0] == 2) * 1.18 + (NGOODJETS[0] > 2) * 1.32");
	wz->addWeight("!(NGOODJETS > 1) + (NGOODJETS > 1) * Alt$((PTGOODJETS[0] < 70) * 0.75 + (PTGOODJETS[0] >= 70 && PTGOODJETS[0] < 110) * 1.16 + (PTGOODJETS[0] >= 110 && PTGOODJETS[0] < 150) * 0.88 + (PTGOODJETS[0] >= 150) * 1.26, 0)");
	wz->addFlatUncertainty("normalizationWZ", 0.05);
	wz->setCorrelationClass("wz");
	
	PhysicsContribution* zz = new PhysicsContribution("backgroundMC", prefix + "ZZJetsTo4L" + infix + suffix, xsec_zz, "ZZ");
	zz->addWeight("(NGOODJETS[0] == 0) * 1.084 + (NGOODJETS[0] == 1) * 0.75 + (NGOODJETS[0] == 2) * 0.333 + (NGOODJETS[0] > 2) * 1");
	
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWWJets" + infix + suffix, 0.002037, "TTWW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWJets" + infix + suffix, xsec_ttw, "TTW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTZJets" + infix + suffix, xsec_ttz, "TTZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WWWJets" + infix + suffix, 0.08217, "WWW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WWZJets" + infix + suffix, 0.0633, "WWZ"));
	mc.push_back(wz);
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WZZJets" + infix + suffix, 0.019, "WZZ"));
	mc.push_back(zz);
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "ZZZNoGstarJets" + infix + suffix, 0.004587, "ZZZ"));
	
	TString nJetWeight = "(NGOODJETS[0] < 2) * 1.11 + (NGOODJETS[0] == 2) * 1.08 + (NGOODJETS[0] == 3) * 1.065 + (NGOODJETS[0] == 4) * 1.065 + (NGOODJETS[0] == 5) * 1.04 + (NGOODJETS[0] > 5) * 1"; // Peter's numbers
	
	PhysicsContribution* ttbarS = new PhysicsContribution("backgroundMC", prefix + "TTJetsSemiLeptonic" + infix + suffix, xsec_ttbar_semiLep, "TT_SemiL");
	ttbarS->addWeight(nJetWeight);
	
	//PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + ".3LonZ" + suffix, xsec_ttbar_fullLep, "TT_FullL");
	PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullL");
	ttbarF->addWeight(nJetWeight);
	//ttbarF->addWeight("nTrackFakeElectrons + nTrackFakeMuons == 0");
	ttbarF->addWeight("1 + (NLEPTONS[0] >= 3) * 0.66");
//	ttbarF->addFlatUncertainty("xsec", 0.3);
	ttbarF->addFlatUncertainty("fudge", 0.194);
	if(ttbar) {
		if(dilep) mc.push_back(ttbarS);
		mc.push_back(ttbarF);
	}

	if(dilep) {
//		mc.push_back(new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-10To50" + infix + suffix, 762.45, "DY10to50"));
//		mc.push_back(new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-50" + infix + suffix, 2950.0, "DYgt50"));
	}
	
	if(onlyTTF) {
		mc.clear();
		mc.push_back(ttbarF);
	}
	
	for(auto &contribution : mc) {
		contribution->addWeight("WEIGHT[0]");
		assembler->addContribution(contribution);
	}
	
	if(onlyTTF) {
		return;
	}
	
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToTauTau" + infix + suffix, 1.2466, "GluGluToHToTauTau"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToWWTo2LAndTau2Nu" + infix + suffix, 0.4437, "GluGluToHToWWTo2LAndTau2Nu"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToZZTo4L" + infix + suffix, 0.0053, "GluGluToHToZZTo4L"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToTauTau" + infix + suffix, 0.0992, "VBF_HToTauTau"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToWWTo2LAndTau2Nu" + infix + suffix, 0.0282, "VBF_HToWWTo2LAndTau2Nu"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToZZTo4L" + infix + suffix, 0.000423, "VBF_HToZZTo4L"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToTauTau" + infix + suffix, 0.0778, "WH_ZH_TTH_HToTauTau"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToWW" + infix + suffix, 0.254, "WH_ZH_TTH_HToWW"));
	
	for(auto &contribution : mcH) {
		contribution->addFlatUncertainty("xsecH", 0.5); // TODO correlations?
		contribution->addWeight("WEIGHT[0]");
		assembler->addContribution(contribution);
	}
}

void setupBackgroundDD(Assembler* assembler, TString option = "", bool syst = false) {
	std::vector<PhysicsContribution*> dd;
	
	PhysicsContribution* fakeTracks = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20141215_fakeTracks.3L.root", assembler->getLumi(), "fakeTracks", (option == "justTracks") ? kWhite : -1);
/*	fakeTracks->addWeight(
		"(Sum$(fakeRoleGOODELECTRONS) + Sum$(fakeRoleGOODMUONS) == 0)"
		" + (Sum$(fakeRoleGOODELECTRONS) > 0)"
			" * 4 * ("
				"(Min$(PTGOODELECTRONS) > 10 && Min$(PTGOODELECTRONS) < 15) * 0.09"
				" + (Min$(PTGOODELECTRONS) > 15 && Min$(PTGOODELECTRONS) < 20) * 0.26"
				" + (Min$(PTGOODELECTRONS) > 20 && Min$(PTGOODELECTRONS) < 25) * 0.58"
				" + (Min$(PTGOODELECTRONS) > 25)"
		")"
		" + (Sum$(fakeRoleGOODMUONS) > 0)"
			" * ("
				"(Min$(PTGOODMUONS) > 10 && Min$(PTGOODMUONS) < 15) * 1.13"
				" + (Min$(PTGOODMUONS) > 15)"
		")"
	);
*/	
	if(syst) {
		fakeTracks->addFlatUncertainty("trackFit", 0.17);
	}
	if(option != "noTracks" && option != "justTaus" && option != "justPhotons") dd.push_back(fakeTracks);
	
	PhysicsContribution* fakeTaus = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20141215_fakeTaus.3L.root", assembler->getLumi(), "fakeTaus");
	if(option != "noTaus" && option != "justTracks" && option != "justPhotons") dd.push_back(fakeTaus);
	
	PhysicsContribution* fakePhotons = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20141215_fakePhotons.3L.root", assembler->getLumi(), "fakePhotons");
	if(syst) {
		fakePhotons->addFlatUncertainty("photonElFake", 0.15);
		//fakePhotons->addFlatUncertainty("photonFudge", 0.25);
		//fakePhotons->setEnsembleFakeRateParam(fakeTracks, "NPROMPTTRACKS7", "0*(x < [0]) + 1*(x > 2*[0]) + (x/[0] - 1)*(x >= [0] && x <= 2*[0])");
	}
	if(option != "noPhotons" && option != "justTracks" && option != "justTaus") dd.push_back(fakePhotons);
	
	for(auto &contribution : dd) {
		assembler->addContribution(contribution);
	}
}

void setupFakeRates(Assembler* assembler) {
	// We found that NGOODJETS and HT binning does not work very well; NPROMPTINCLUSIVETRACK7 binning does a good job at least in 0b regions.
	assembler->setFakeRate("nTrackFakeMuons",
		"0.0154" // "(NGOODMUONS[0]==1)*(0.01384 + -0.0003956*NPROMPTNONISOINCLUSIVETRACKS7[0]) + (NGOODMUONS[0]==3)*(0.01697 + -0.0001669*NPROMPTNONISOINCLUSIVETRACKS7[0])"
		" * (1 + 1.4 * (NBJETSCSVM[0] > 0))"
	);
	assembler->setFakeRate("nTrackFakeElectrons",
		"((NLEPTONS[0]==3&&NGOODELECTRONS[0]==1)*(0.006771 + 0.005532*NPROMPTNONISOINCLUSIVETRACKS7[0]) + (NLEPTONS[0]==3&&NGOODELECTRONS[0]==3)*(0.009287 + -0.001487*NPROMPTNONISOINCLUSIVETRACKS7[0])"
		"+ (NLEPTONS[0]!=3||!(NGOODELECTRONS[0]%2))*(0.007453 + 0.003052*NPROMPTNONISOINCLUSIVETRACKS7[0]))" // this is not the average of the above, but measured (because of relative fractions)
		" * (1 + 1.4 * (NBJETSCSVM[0] > 0))"
	);
	
	assembler->setFakeRate("nSidebandFakeTaus", "(HT[0] < 200) * 0.022 + !(HT[0] < 200) * 0.019");
	
	// Photon fake rates for Asymmetric Internal Conversions (AIC)
	// AIC reduces the pt of the emitting lepton, and can push on-Z pairs below the Z peak. This causes migration between on-Z/off-Z etc.
	// Looking at the AIC control region, we find that we should adjust the fake rate outside MLEPTONS = 75..100.
	assembler->setFakeRate("nPhotonFakeMuons", "(NOSSF == 1 && !ONZ && MOSSF < 91) * 0.00295 / ( (1 + 0.5 * (MLEPTONS[0] < 75 || MLEPTONS[0] > 100) ) * (1 + ONZ) ) * (1 + 1.4 * (NBJETSCSVM[0] > 0))");
	assembler->setFakeRate("nPhotonFakeElectrons", "0.0088 / ( (1 + 0.5 * (MLEPTONS[0] < 75 || MLEPTONS[0] > 100) ) * (1 + ONZ) ) * (1 + 1.4 * (NBJETSCSVM[0] > 0))");
}

#include <TLatex.h>
#include <TLegend.h>
#include "TStyle.h"

TCanvas* makeNicePlot(TCanvas* c, const char* axistitle="")
{
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  c->cd();
  c->SetTopMargin(0.001);
  c->SetRightMargin(0.001);
  c->SetBottomMargin(0.001);
  c->SetLeftMargin(0.001);

  TPad* pad1 = (TPad*)c->GetPrimitive("pad1");
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.01);
  TPad* pad2 = (TPad*)c->GetPrimitive("pad2");
  pad2->SetBottomMargin(0.15);
  pad2->SetTopMargin(0.01);

  //pad1->RedrawAxis();
  pad2->RedrawAxis();


  TList* list = pad1->GetListOfPrimitives();
  cout<<"make nice plot "<<list->GetEntries()<<endl;
  for(int i = 0; i < list->GetEntries(); i++){
    TObject* obj = list->At(i);
    TString cname(obj->ClassName());
    if(cname.Contains("TH1")){
      ((TH1*)obj)->SetStats(false);
    }else if(cname == "TLegend"){
      ((TLegend*)obj)->SetFillColor(kWhite);
    }
  }

  TList* list2 = pad2->GetListOfPrimitives();
  for(int i = 0; i < list2->GetEntries(); i++){
    TObject* obj = list2->At(i);
    TString cname(obj->ClassName());
    if(cname.Contains("TH1")){
      float offset = ((TH1*)obj)->GetXaxis()->GetTitleOffset();
      float fontsize = ((TH1*)obj)->GetXaxis()->GetTitleSize();
      ((TH1*)obj)->GetXaxis()->SetTitleOffset(1.1*offset);
      ((TH1*)obj)->GetXaxis()->SetTitleFont(42);
      ((TH1*)obj)->GetXaxis()->SetTitleSize(1.1*fontsize);
      if(TString(axistitle) != "" && TString(((TH1*)obj)->GetXaxis()->GetTitle()) != ""){
        ((TH1*)obj)->GetXaxis()->SetTitle(axistitle);
      }
    }
  }

  c->cd();

  TLatex* latex = new TLatex;
  latex->SetNDC();
  latex->SetTextFont(61);
  latex->SetTextSize(0.04);
  latex->DrawLatex(0.16,0.915,"CMS Simulation");

  latex->SetTextSize(0.03);
  latex->SetTextFont(42);
  latex->DrawLatex(0.75,0.97,"20 fb^{-1} (13 TeV)");

  c->Update();
  pad1->Update();
  pad2->Update();

  return c;

}

std::vector<double> getFirst(std::vector<std::pair<double, double> > list) {
	std::vector<double> list2;
	for(size_t i = 0; i < list.size(); ++i) {
		list2.push_back(list[i].first);
	}
	return list2;
}

std::vector<double> getSecond(std::vector<std::pair<double, double> > list) {
	std::vector<double> list2;
	for(size_t i = 0; i < list.size(); ++i) {
		list2.push_back(list[i].second);
	}
	return list2;
}
