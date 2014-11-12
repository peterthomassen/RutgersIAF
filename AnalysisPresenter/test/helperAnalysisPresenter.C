#include <iostream>
#include <TH1.h>
#include <TLatex.h>
#include <TLegend.h>
#include "TStyle.h"
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
		? new PhysicsContribution("data", prefix + "20140923_fakeTracks" + infix + suffix, 19500, "2012trackFakeSeed")
		: new PhysicsContribution("data", prefix + "20140923_data" + infix + suffix, 19500, "2012data");
	
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

void setupBackgroundMC(Assembler* assembler, bool dilep = false, bool ttbar = true) {
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
	Double_t xsec_ttw = 0.23;
	Double_t xsec_ttz = 0.208;
	
	// Peter's numbers
	double xsec_ttbar_fullLep = 23.08;
	double xsec_ttbar_semiLep = 97.97;
	double xsec_wz = 1.2451;
	xsec_wz *= 0.98;
//	double xsec_zz = 0.181;
//	double xsec_ttw = 0.2149;
//	double xsec_ttz = 0.208;
	
	//ttbar = false;
	
	std::vector<PhysicsContribution*> mc;
	
	//PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZJetsTo3LNu" + infix + suffix, 1.2030, "WZ");
	PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZJetsTo3LNu" + infix + suffix, xsec_wz, "WZ");
	//wz->addWeight("(NGOODJETS < 2) * 0.897051 + (NGOODJETS >= 2) * 2.0084"); // Richard's numbers
	//wz->addWeight("(NGOODJETS == 0) * 1.024 + (NGOODJETS == 1) * 0.86 + (NGOODJETS == 2) * 1.1 + (NGOODJETS > 2) * 1"); // without ttbar MC
	wz->addWeight("(NGOODJETS == 0) * 1.024 + (NGOODJETS == 1) * 0.81 + (NGOODJETS == 2) * 1.0 + (NGOODJETS > 2) * 1"); // with ttbar MC
	
	PhysicsContribution* zz = new PhysicsContribution("backgroundMC", prefix + "ZZJetsTo4L" + infix + suffix, xsec_zz, "ZZ");
	zz->addWeight("(NGOODJETS == 0) * 1.084 + (NGOODJETS == 1) * 0.75 + (NGOODJETS == 2) * 0.333 + (NGOODJETS > 2) * 1");
	
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWWJets" + infix + suffix, 0.002037, "TTWW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWJets" + infix + suffix, xsec_ttw, "TTW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTZJets" + infix + suffix, xsec_ttz, "TTZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WWWJets" + infix + suffix, 0.08217, "WWW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WWZJets" + infix + suffix, 0.0633, "WWZ"));
	mc.push_back(wz);
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WZZJets" + infix + suffix, 0.019, "WZZ"));
	mc.push_back(zz);
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "ZZZNoGstarJets" + infix + suffix, 0.004587, "ZZZ"));
	if(ttbar) mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTJetsSemiLeptonic" + infix + suffix, xsec_ttbar_semiLep, "TT_SemiL"));
	
	PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullL");
	ttbarF->addWeight("(NLEPTONS >= 3) * 1.5 + !(NLEPTONS >= 3) * 1");
	//ttbarF->addWeight("(NGOODJETS < 2) * 1.42 + (NGOODJETS == 2) * 1.18 + (NGOODJETS == 3) * 1.04 + (NGOODJETS > 3) * 1"); // Richard's numbers
	ttbarF->addWeight("(NGOODJETS < 2) * 1.30 + (NGOODJETS == 2) * 1.15 + (NGOODJETS == 3) * 1.10 + (NGOODJETS == 4) * 1.076 + (NGOODJETS > 4) * 1"); // Peter's numbers, regular bkgs + DY MC
	//ttbarF->addWeight("nTrackFakeElectrons + nTrackFakeMuons == 0");
//	ttbarF->addFlatUncertainty("xsec", 0.3);
	if(ttbar) mc.push_back(ttbarF);
	
	if(dilep) {
//		mc.push_back(new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-10To50" + infix + suffix, 762.45, "DY10to50"));
//		mc.push_back(new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-50" + infix + suffix, 2950.0, "DYgt50"));
	}
	
	for(auto &contribution : mc) {
		assembler->addContribution(contribution);
	}
	
	assembler->addWeight("WEIGHT", "backgroundMC");
}

void setupBackgroundDD(Assembler* assembler) {
	std::vector<PhysicsContribution*> dd;
	
	PhysicsContribution* fakeTracks = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140923_fakeTracks.3L.root", assembler->getLumi(), "fakeTracks");
	//fakeTracks->addFlatUncertainty("fakeTracks", 0.25);
	dd.push_back(fakeTracks);
	
	PhysicsContribution* fakePhotons = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140923_fakePhotons.3L.root", assembler->getLumi(), "fakePhotons");
	//fakePhotons->setEnsembleFakeRateParam(fakeTracks, "NPROMPTTRACKS7", "0*(x < [0]) + 1*(x > 2*[0]) + (x/[0] - 1)*(x >= [0] && x <= 2*[0])");
	dd.push_back(fakePhotons);
	
	//dd.push_back(new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140618_fakeMixed.root", assembler->getLumi(), "fakeMixed"));
	
	for(auto &contribution : dd) {
		assembler->addContribution(contribution);
	}
}

void setupFakeRates(Assembler* assembler) {
	// [PT] These numbers were obtained from the MOSSF plots on Z
	//assembler->setFakeRate("nTrackFakeMuons", "(NLEPTONS > 2) * 0.01544");
	//assembler->setFakeRate("nTrackFakeElectrons", "(NLEPTONS > 2) * 0.02538");
	
	// Matt's numbers
	//assembler->setFakeRate("nTrackFakeMuons", "(NBJETSCSVM == 0) * 0.018 + (NBJETSCSVM >= 1) * 0.13");
	//assembler->setFakeRate("nTrackFakeElectrons", "(NBJETSCSVM == 0) * ( (HT < 200) * 0.028 + (HT > 200) * 0.05 ) + (NBJETSCSVM >= 1) * 0.11");
	
	// Peter's numbers based on Matt's method
	//assembler->setFakeRate("nTrackFakePosMuons",     "(NBJETSCSVM == 0) * ( (HT < 200) * ((NGOODELECTRONS == 2) * 0.0122 + (NGOODELECTRONS == 0) * 0.0165) + (HT > 200) * 0.0412961 ) + (NBJETSCSVM >= 1 && ONZ) * 0.0412961");
	//assembler->setFakeRate("nTrackFakeNegMuons",     "(NBJETSCSVM == 0) * ( (HT < 200) * ((NGOODELECTRONS == 2) * 0.0145 + (NGOODELECTRONS == 0) * 0.0193) + (HT > 200) * 0.0412961 ) + (NBJETSCSVM >= 1 && ONZ) * 0.0412961");
	//assembler->setFakeRate("nTrackFakePosElectrons", "(NBJETSCSVM == 0) * ( (HT < 200) * 0.0241 + (HT > 200) * 0.0612284 ) + (NBJETSCSVM >= 1 && ONZ) * 0.0612284");
	//assembler->setFakeRate("nTrackFakeNegElectrons", "(NBJETSCSVM == 0) * ( (HT < 200) * 0.0299 + (HT > 200) * 0.0612284 ) + (NBJETSCSVM >= 1 && ONZ) * 0.0612284");
	
	// We found that NGOODJETS and HT binning does not work very well; NPROMPTINCLUSIVETRACK7 binning does a good job at least in 0b regions.
	assembler->setFakeRate("nTrackFakeMuons",
		"(NBJETSCSVM == 0 || ONZ) * (0.0238693 - 0.00175457 * NPROMPTINCLUSIVETRACKS7) * (1 + (NBJETSCSVM > 0))"
		//" + (NBJETSCSVM > 0 && !ONZ) * 0.14"
	);
	assembler->setFakeRate("nTrackFakeElectrons",
		"(NBJETSCSVM == 0 || ONZ) * (-0.00698188 + 0.00706028 * NPROMPTINCLUSIVETRACKS7) * (1 + (NBJETSCSVM > 0))"
		//" + (NBJETSCSVM > 0 && !ONZ) * 0.125"
	);
	
	// Photon fake rates for Asymmetric Internal Conversions (AIC)
	// AIC reduces the pt of the emitting lepton, and can push on-Z pairs below the Z peak. This causes migration between on-Z/off-Z etc.
	// In regions where cuts don't depend (indirectly) on lepton pT cuts (like DY0), such events remain in the same bin.
	// Thus, we only apply this fake rate in regions where events could migrate to, i.e. OSSF regions ONZ.
	// Looking at the AIC control region, we find that we should halve the fake rate outside MLEPTONS = 75..100.
	assembler->setFakeRate("nPhotonFakeMuons", "(NOSSF > 0 && !ONZ) * 0.0034 / (1 + (MLEPTONS < 75 || MLEPTONS > 100))");
	assembler->setFakeRate("nPhotonFakeElectrons", "(NOSSF > 0 && !ONZ) * 0.0119 / (1 + (MLEPTONS < 75 || MLEPTONS > 100))");
}

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

