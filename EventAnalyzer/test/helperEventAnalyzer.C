typedef double (TLorentzVector::*SOfunction)();

TString makeName(int qMu, int nMu,int qEl,int nEl, int qTr, int nTr)
{

  TString name = "El";
  name += nEl;
  if(qEl == 0){
    name += "q";
  }else if(qEl < 0){
    name += "m";
  }else{
    name += "p";
  }

  name += abs(qEl);
  name += "Mu";
  name += nMu;

  if(qMu == 0){
    name += "q";
  }else if(qMu < 0){
    name += "m";
  }else{
    name += "p";
  }
  name += abs(qMu);
  name += "T";
  name += nTr;

  if(qTr == 0){
    name += "q";
  }else if(qTr < 0){
    name += "m";
  }else{
    name += "p";
  }
  name += abs(qTr);

  return name;
}

void setupProducts(BaseHandler* handler)
{
  //////////////////
  ///General Cuts///
  //////////////////


  SOfunction TLVPT = &TLorentzVector::Pt;
  SOfunction TLVETA = &TLorentzVector::Eta;

  ObjectVariableLorentzVectorInRange* leptonPtCut = new ObjectVariableLorentzVectorInRange(TLVPT,10.0,10000.0,"leptonPtCut");
  ObjectVariableLorentzVectorInRange* leptonEtaCut = new ObjectVariableLorentzVectorInRange(TLVETA,-2.4,2.4,"leptonEtaCut");
  ObjectVariableLorentzVectorInRange* PT40 = new ObjectVariableLorentzVectorInRange(TLVPT,40.0,10000.0,"PT40");

  handler->addObjectVariable("PT10",leptonPtCut);
  handler->addObjectVariable("PT20",new ObjectVariableLorentzVectorInRange(TLVPT,20.0,10000.0,"PT20"));
  handler->addObjectVariable("PT30",new ObjectVariableLorentzVectorInRange(TLVPT,30.0,10000.0,"PT30"));
  handler->addObjectVariable("PT40",PT40);
  handler->addObjectVariable("ETA2p3",new ObjectVariableLorentzVectorInRange(TLVETA,-2.3,2.3,"ETA2p3"));
  handler->addObjectVariable("ETA2p4",leptonEtaCut);
  handler->addObjectVariable("ETA2p5",new ObjectVariableLorentzVectorInRange(TLVETA,-2.5,2.5,"ETA2p3"));
  handler->addObjectVariable("IREL0p15",new ObjectVariableInRange<double>("RELISO",0,0.15));
  handler->addObjectVariable("BARREL",new ObjectVariableLorentzVectorInRange(TLVETA,-1.5,1.5,"barrelEta"));
  handler->addObjectVariable("ENDCAP",new ObjectVariableReversed("BARREL"));
  handler->addObjectVariable("POSITIVE",new ObjectVariableInRange<double>("CHARGE",0,10));
  handler->addObjectVariable("NEGATIVE",new ObjectVariableInRange<double>("CHARGE",-10,0));

  handler->addObjectVariable("MUONTOTALISO",new ObjectVariableMuonTotalIso("TOTALISO"));
  handler->addObjectVariable("ELECTRONTOTALISO",new ObjectVariableElectronTotalIso("TOTALISO"));
  handler->addObjectVariable("RELISO",new ObjectVariableRelIso("RELISO"));

  /////////////////
  ///Muon Cuts ///
  ////////////////

  handler->addObjectVariable("MUON_VALID_INNER_PIXEL_HITS",new ObjectVariableInRange<int>("INNERNUMBEROFVALIDPIXELHITS",1,10000));
  handler->addObjectVariable("MUON_TRACK_LAYERS_WM", new ObjectVariableInRange<int>("NTRACKERLAYERSWM",6,10000));
  handler->addObjectVariable("MUON_MATCHES",new ObjectVariableInRange<int>("NUMBEROFMATCHES",2,100000));
  handler->addObjectVariable("ISPF",new ObjectVariableValue<int>("ISPF",1));
  handler->addObjectVariable("MUON_ISGLOBAL",new ObjectVariableValue<int>("ISGLOBALMUON",1));
  handler->addObjectVariable("MUON_VALID_MUON_HITS",new ObjectVariableInRange<int>("NVALIDMUONHITS",1,10000));
  handler->addObjectVariable("MUON_NORMALIZED_CHI2",new ObjectVariableInRange<double>("NORMALIZEDCHI2",0,10));
  handler->addObjectVariable("MUON_INNER_VERT_DZ",new ObjectVariableInRange<double>("INNERVERTDZ",-0.5,0.5));
  handler->addObjectVariable("MUON_PROMPT",new ObjectVariableInRange<double>("INNERVERTDXY",0,0.02));
  handler->addObjectVariable("MUON_NONPROMPT",new ObjectVariableInRange<double>("INNERVERTDXY",0.03,1000));

  handler->addProduct("goodMuons","ALLMUONS");
  handler->addProductCut("goodMuons","PT10");
  handler->addProductCut("goodMuons","ETA2p4");
  handler->addProductCut("goodMuons","IREL0p15");
  handler->addProductCut("goodMuons","MUON_VALID_INNER_PIXEL_HITS");
  handler->addProductCut("goodMuons","MUON_TRACK_LAYERS_WM");
  handler->addProductCut("goodMuons","MUON_MATCHES");
  handler->addProductCut("goodMuons","ISPF");
  handler->addProductCut("goodMuons","MUON_ISGLOBAL");
  handler->addProductCut("goodMuons","MUON_VALID_MUON_HITS");
  handler->addProductCut("goodMuons","MUON_NORMALIZED_CHI2");
  handler->addProductCut("goodMuons","MUON_INNER_VERT_DZ");
  handler->addProductCut("goodMuons","MUON_PROMPT");

  handler->addProduct("posGoodMuons","goodMuons");
  handler->addProductCut("posGoodMuons","POSITIVE");
  handler->addProduct("negGoodMuons","goodMuons");
  handler->addProductCut("negGoodMuons","NEGATIVE");

  ///////////////////
  ///Electron Cuts///
  //////////////////

  handler->addObjectVariable("ELECTRON_INGAP",new ObjectVariableInRange<double>("FMVAVAR_ETA",1.4442,1.566));
  handler->addObjectVariable("ELECTRON_NOTGAP",new ObjectVariableReversed("ELECTRON_INGAP"));
  handler->addObjectVariable("ELECTRON_BARREL_DETA",new ObjectVariableInRange<double>("DELTAETA",-0.007,0.007));
  handler->addObjectVariable("ELECTRON_ENDCAP_DETA",new ObjectVariableInRange<double>("DELTAETA",-0.009,0.009));
  handler->addObjectVariable("ELECTRON_BARREL_DPHI",new ObjectVariableInRange<double>("DELTAPHI",-0.15,0.15));
  handler->addObjectVariable("ELECTRON_ENDCAP_DPHI",new ObjectVariableInRange<double>("DELTAPHI",-0.10,0.10));
  handler->addObjectVariable("ELECTRON_BARREL_HADOVEREM",new ObjectVariableInRange<double>("HADOVEREM",0.0,0.12));
  handler->addObjectVariable("ELECTRON_ENDCAP_HADOVEREM",new ObjectVariableInRange<double>("HADOVEREM",0.0,0.10));
  handler->addObjectVariable("ELECTRON_BARREL_SIGMAIETAIETA",new ObjectVariableInRange<double>("SIGMAIETAIETA",-0.01,0.01));
  handler->addObjectVariable("ELECTRON_ENDCAP_SIGMAIETAIETA",new ObjectVariableInRange<double>("SIGMAIETAIETA",-0.03,0.03));
  handler->addObjectVariable("ELECTRON_MISSING_HITS",new ObjectVariableInRange<int>("NUMBEROFEXPECTEDINNERHITS",0,1));
  handler->addObjectVariable("ELECTRON_EMINUSP",new ObjectVariableInRange<double>("FMVAVAR_IOEMIOP",-0.05,0.05));
  handler->addObjectVariable("ELECTRON_CONVERSION",new ObjectVariableValue<int>("ISCONVERSION",0));
  handler->addObjectVariable("ELECTRON_VERT_DZ", new ObjectVariableInRange<double>("FMVAVAR_DZ",-0.2,0.2));
  handler->addObjectVariable("ELECTRON_PROMPT", new ObjectVariableInRange<double>("FMVAVAR_D0",-0.02,0.02));

  ObjectVariableCombined* electron_barrel = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_DETA",true,"electron_barrel_good");
  electron_barrel->addVariable("ELECTRON_BARREL_DPHI");
  electron_barrel->addVariable("ELECTRON_BARREL_HADOVEREM");
  electron_barrel->addVariable("ELECTRON_BARREL_SIGMAIETAIETA");
  handler->addObjectVariable("ELECTRON_BARREL",electron_barrel);

  ObjectVariableCombined* electron_endcap = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_DETA",true,"electron_endcap_good");
  electron_endcap->addVariable("ELECTRON_ENDCAP_DPHI");
  electron_endcap->addVariable("ELECTRON_ENDCAP_HADOVEREM");
  electron_endcap->addVariable("ELECTRON_ENDCAP_SIGMAIETAIETA");
  handler->addObjectVariable("ELECTRON_ENDCAP",electron_endcap);

  handler->addObjectVariable("ELECTRON_COMBINED",new ObjectVariableCombined("ELECTRON_BARREL","ELECTRON_ENDCAP",false,"ELECTRON_COMBINED"));

  handler->addProduct("goodElectrons","ALLELECTRONS");
  handler->addProductCut("goodElectrons","PT10");
  handler->addProductCut("goodElectrons","ETA2p4");
  handler->addProductCut("goodElectrons","IREL0p15");
  handler->addProductCut("goodElectrons","ELECTRON_COMBINED");
  handler->addProductCut("goodElectrons","ELECTRON_PROMPT");
  handler->addProductCut("goodElectrons","ELECTRON_MISSING_HITS");
  handler->addProductCut("goodElectrons","ELECTRON_EMINUSP");
  handler->addProductCut("goodElectrons","ELECTRON_CONVERSION");
  handler->addProductCut("goodElectrons","ELECTRON_VERT_DZ");

  handler->addProduct("posGoodElectrons","goodElectrons");
  handler->addProductCut("posGoodElectrons","POSITIVE");
  handler->addProduct("negGoodElectrons","goodElectrons");
  handler->addProductCut("negGoodElectrons","NEGATIVE");

  //////////////
  ///Tau Cuts///
  //////////////

  handler->addObjectVariable("TAU_DECAYMODFINDING",new ObjectVariableValue<int>("DISC_DECAYMODEFINDING",1));
  handler->addObjectVariable("TAU_AGAINSTELECTRONMVA",new ObjectVariableValue<int>("DISC_AGAINSTELECTRONMVA",1));
  handler->addObjectVariable("TAU_AGAINSTMUONTIGHT",new ObjectVariableValue<int>("DISC_AGAINSTMUONTIGHT",1));
  handler->addObjectVariable("TAU_BYLOOSECOMBINEDISODBSUMPTCORR",new ObjectVariableValue<int>("DISC_BYLOOSECOMBINEDISODBSUMPTCORR",1));
  handler->addObjectVariable("TAU_CHARGE_ZERO",new ObjectVariableInRange<double>("PF_SIGNALCHARGE",-0.9,0.9));
  handler->addObjectVariable("TAU_SIGNAL_CHARGE",new ObjectVariableReversed("TAU_CHARGE_ZERO"));

  handler->addProduct("goodTaus","ALLTAUS");
  handler->addProductCut("goodTaus","PT20");
  handler->addProductCut("goodTaus","ETA2p3");
  handler->addProductCut("goodTaus","TAU_DECAYMODEFINDING");
  handler->addProductCut("goodTaus","TAU_AGAINSTELECTRONMVA");
  handler->addProductCut("goodTaus","TAU_AGAINSTMUONTIGHT");
  handler->addProductCut("goodTaus","TAU_BYLOOSECOMBINEDISODBSUMPTCORR");
  handler->addProductCut("goodTaus","TAU_SIGNAL_CHARGE");


  //////////////
  ///Jet Cuts///
  /////////////

  handler->addObjectVariable("JET_CHARGEDEMFRACTION",new ObjectVariableInRange<double>("CHARGEDEMFRACTION",0,0.99));
  handler->addObjectVariable("JET_CHARGEDMULTIPLICITY",new ObjectVariableInRange<int>("CHARGEDHADRONMULTIPLICITY",1,10000));
  handler->addObjectVariable("JET_CHARGEDHADRONFRACTION", new ObjectVariableInRange<double>("CHARGEDHADRONFRACTION",0.00001,1.0));
  handler->addObjectVariable("JET_NCONSTITUENTS", new ObjectVariableInRange<int>("NUMBERCONSTITUENTS",2,10000));
  handler->addObjectVariable("JET_NEUTRALEMFRACTION", new ObjectVariableInRange<double>("NEUTRALEMFRACTION",0.0,0.99));
  handler->addObjectVariable("JET_NEUTRALHADRONFRACTION",new ObjectVariableInRange<double>("NEUTRALHADRONFRACTION",0.0,0.99));


  handler->addProduct("goodJets","ALLJETS");
  handler->addProductCut("goodJets","PT30");
  handler->addProductCut("goodJets","ETA2p5");
  handler->addProductCut("goodJets","JET_CHARGEDEMFRACTION");
  handler->addProductCut("goodJets","JET_CHARGEDMULTIPLICITY");
  handler->addProductCut("goodJets","JET_CHARGEDHADRONFRACTION");
  handler->addProductCut("goodJets","JET_NCONSTITUENTS");
  handler->addProductCut("goodJets","JET_NEUTRALEMFRACTION");
  handler->addProductCut("goodJets","JET_NEUTRLAHADRONFRACTION");

  handler->addObjectVariable("BJET_CSVL", new ObjectVariableInRange<double>("BDISCPOS_COMBINEDSECONDARYVERTEXBJETTAGS",0.244,1000.0));
  handler->addObjectVariable("BJET_CSVM", new ObjectVariableInRange<double>("BDISCPOS_COMBINEDSECONDARYVERTEXBJETTAGS",0.679,1000.0));

  handler->addProduct("bJetsCSVL","goodJets");
  handler->addProduct("bJetsCSVM","bJetsCSVL");
  handler->addProductCut("bJetsCSVL","BJET_CSVL");
  handler->addProductCut("bJetsCSVM","BJET_CSVM");

  ////////////////
  ///Track Cuts///
  /////////////////

  handler->addObjectVariable("TRACK_NDOF",new ObjectVariableInRange<double>("NDOF",1,10000));
  handler->addObjectVariable("TRACK_VALID_HITS",new ObjectVariableInRange<int>("NVALIDTRACKERHITS",10,10000));
  handler->addObjectVariable("TRACK_BEAM_D0", new ObjectVariableInRange<double>("BEAM_D0",-0.2,0.2));
  handler->addObjectVariable("TRACK_VERT_DZ", new ObjectVariableInRange<double>("VERT_DZ",-1.0,1.0));
  handler->addObjectVariable("TRACK_PROMPT", new ObjectVariableInRange<double>("VERT_DXY",-0.02,0.02));

  handler->addProduct("goodTracks","ALLRECOTRACKS");
  handler->addProductCut("goodTracks","PT10");
  handler->addProductCut("goodTracks","ETA2p4");
  handler->addProductCut("goodTracks","IREL0p15");
  handler->addProductCut("goodTracks","TRACK_NDOF");
  handler->addProductCut("goodTracks","TRACK_VALID_HITS");
  handler->addProductCut("goodTracks","TRACK_BEAM_D0");
  handler->addProductCut("goodTracks","TRACK_VERT_DZ");
  handler->addProductCut("goodTracks","TRACK_PROMPT");

  handler->addProduct("posGoodTracks","goodTracks");
  handler->addProductCut("posGoodTracks","POSITIVE");
  handler->addProduct("negGoodTracks","goodTracks");
  handler->addProductCut("negGoodTracks","NEGATIVE");


  /////////////////////////
  ///handler comparisons///
  /////////////////////////

  ObjectComparisonDeltaR* deltaR0p005 = new ObjectComparisonDeltaR(0.005);
  ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonDeltaR* deltaR0p3 = new ObjectComparisonDeltaR(0.3);
  ObjectComparisonDeltaR* deltaR0p4 = new ObjectComparisonDeltaR(0.4);

  handler->addProductSelfComparison("goodMuons",deltaR0p1);
  handler->addProductSelfComparison("goodElectrons",deltaR0p1);
  handler->addProductSelfComparison("goodTracks",deltaR0p005);

  handler->addProductComparison("goodElectrons","goodMuons",deltaR0p1);
  handler->addProductComparison("goodTaus","goodMuons",deltaR0p1);
  handler->addProductComparison("goodTaus","goodElectrons",deltaR0p1);

  handler->addProductComparison("goodTracks","goodMuons",deltaR0p1);
  handler->addProductComparison("goodTracks","goodElectrons",deltaR0p1);
  handler->addProductComparison("goodTracks","goodTaus",deltaR0p3);

  handler->addProductComparison("goodJets","goodMuons",deltaR0p4);
  handler->addProductComparison("goodJets","goodElectrons",deltaR0p4);
  handler->addProductComparison("goodJets","goodTaus",deltaR0p4);

}


void setupVariables(BaseHandler* handler)
{
  EventVariableSumPT* ST = new EventVariableSumPT("ST","goodMuons");
  ST->addProduct("goodElectrons");
  ST->addProduct("goodTaus");
  ST->addProduct("goodJets");
  ST->addProduct("MET");

  EventVariableSumPT* HT = new EventVariableSumPT("HT","goodJets");

  EventVariableSumPT* MET = new EventVariableSumPT("MET","MET");

  EventVariableOSSF* OSSF = new EventVariableOSSF("OSSF","goodMuons","",91,15);
  OSSF->addProduct("goodElectrons");

  handler->addEventVariable("ST",ST);
  handler->addEventVariable("HT",HT);
  handler->addEventVariable("MET",MET);
  handler->addEventVariable("OSSF",OSSF);

}

void addHistograms(BaseHandler* handler)
{
  SignatureTH1F_EventVariable<double>* h_ht = new SignatureTH1F_EventVariable<double>("HT","HT","H_{T} Distribution",200,0,2000);
  SignatureTH1F_EventVariable<double>* h_met = new SignatureTH1F_EventVariable<double>("MET","MET","MET Distribution",50,0,500);
  handler->addHistogram(h_ht);
  handler->addHistogram(h_met);
}


void setupFilterCuts(BaseHandler* handler)
{
  handler->addHandlerCut("PRIMARYVERTEXFILTER");
  handler->addHandlerCut("NOSCRAPINGFILTER");
  handler->addHandlerCut("HBHENOISEFILTER");
  handler->addHandlerCut("CSCTIGHTHALOFILTER");
  handler->addHandlerCut("HCALLASEREVENTFILTER");
  handler->addHandlerCut("ECALDEADCELLTRIGGERPRIMITIVEFILTER");
  handler->addHandlerCut("TRACKINGFAILUREFILTER");
  handler->addHandlerCut("EEBADSCFILTER");

}

void setupSignatures(BaseHandler* handler)
{
  TString products[6] = {"posGoodMuons","negGoodMuons","posGoodElectrons","negGoodElectrons","posGoodTracks","negGoodTracks"};
  for(int i = 0; i < 6; i++){
    //products[i].ToUpper();
    TString varname = TString::Format("N%s",products[i].Data());
    varname.ToUpper();
    handler->addEventVariable(varname,new EventVariableN(varname,products[i]));
    for(int j = 0; j < 4; j++){
      TString varname1 = TString::Format("N%sEQ%i",products[i].Data(),j);
      handler->addEventVariable(varname1,new EventVariableInRange<int>(varname,j,j,varname1));
    }
  }

  for(int i_posMuons = 0; i_posMuons < 4; i_posMuons++){
    for(int i_negMuons = 0; i_negMuons < 4; i_negMuons++){
      for(int i_posElectrons = 0; i_posElectrons < 4; i_posElectrons++){
	for(int i_negElectrons = 0; i_negElectrons < 4; i_negElectrons++){
	  for(int i_posTracks = 0; i_posTracks < 4; i_posTracks++){
	    for(int i_negTracks = 0; i_negTracks < 4; i_negTracks++){
	      if(i_posMuons + i_negMuons + i_posElectrons + i_negElectrons + i_posTracks + i_negTracks != 3)continue;
	      int nMu = i_posMuons + i_negMuons;
	      int nEl = i_posElectrons + i_negElectrons;
	      int nTr = i_posTracks + i_negTracks;
	      int qMu = i_posMuons - i_negMuons;
	      int qEl = i_posElectrons - i_negElectrons;
	      int qTr = i_posTracks - i_negTracks;
	      TString chanName = makeName(qMu,nMu,qEl,nEl,qTr,nTr);

	      TString cut_posMuons = TString::Format("NPOSGOODMUONSEQ%i",i_posMuons);
	      TString cut_negMuons = TString::Format("NNEGGOODMUONSEQ%i",i_negMuons);
	      TString cut_posElectrons = TString::Format("NPOSGOODELECTRONSEQ%i",i_posElectrons);
	      TString cut_negElectrons = TString::Format("NNEGGOODELECTRONSEQ%i",i_negElectrons);
	      TString cut_posTracks = TString::Format("NPOSGOODTRACKSEQ%i",i_posTracks);
	      TString cut_negTracks = TString::Format("NNEGGOODTRACKSEQ%i",i_negTracks);

	      handler->addSignature(chanName)
		->addCut(cut_posMuons)
		->addCut(cut_negMuons)
		->addCut(cut_posElectrons)
		->addCut(cut_negElectrons)
		->addCut(cut_posTracks)
		->addCut(cut_negTracks)
		;
	    }
	  }
	}
      }
    }
  }



}
