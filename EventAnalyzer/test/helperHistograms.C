#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableN.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_N.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_ObjectVariable.h"

void addHistograms(BaseHandler* handler)
{
  SignatureTH1F_EventVariable<double>* h_ht = new SignatureTH1F_EventVariable<double>("HT","HT","H_{T} Distribution",200,0,2000);
  handler->addHistogram(h_ht);
  
  SignatureTH1F_EventVariable<double>* h_met = new SignatureTH1F_EventVariable<double>("MET","MET","MET Distribution",50,0,500);
  handler->addHistogram(h_met);

  SignatureTH1F_EventVariable<double>* h_mossf = new SignatureTH1F_EventVariable<double>("MLL","MOSSF","M_{ll} Distribution",200,0,200);
  handler->addHistogram(h_mossf);
  
  SignatureTH1F_ObjectVariable<double>* h_ptEl = new SignatureTH1F_ObjectVariable<double>("PTel","PT","goodElectrons","PT Distribution",100,0,1000);
  handler->addHistogram(h_ptEl);
  
  SignatureTH1F_ObjectVariable<double>* h_etaEl = new SignatureTH1F_ObjectVariable<double>("ETAel","ETA","goodElectrons","ETA Distribution",100,-3,3);
  handler->addHistogram(h_etaEl);
  
  SignatureTH1F_ObjectVariable<double>* h_ptMu = new SignatureTH1F_ObjectVariable<double>("PTmu","PT","goodMuons","PT Distribution",100,0,1000);
  handler->addHistogram(h_ptMu);
  
  SignatureTH1F_ObjectVariable<double>* h_etaMu = new SignatureTH1F_ObjectVariable<double>("ETAmu","ETA","goodMuons","ETA Distribution",100,-3,3);
  handler->addHistogram(h_etaMu);
}

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

  if(nTr == 0)return name;

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

void setupOnZSignatures(BaseHandler* handler)
{
  handler->addEventVariable("getwoGoodMuons", new EventVariableInRange<int>("NGOODMUONS",2,100000));
  handler->addEventVariable("getwoGoodElectrons",new EventVariableInRange<int>("NGOODELECTRONS",2,100000));

  handler->addSignature("Mu2OnZ")
    ->addCut("getwoGoodMuons")
    ->addCut("ONZ")
    ;
  handler->addSignature("El2OnZ")
    ->addCut("getwoGoodElectrons")
    ->addCut("ONZ")
    ;

  SignatureTH1F_N* nnegmuons = new SignatureTH1F_N("nmuonsneg","negGoodMuons");
  SignatureTH1F_N* nposmuons = new SignatureTH1F_N("nmuonspos","posGoodMuons");
  SignatureTH1F_N* nnegelectrons = new SignatureTH1F_N("nelectronsneg","negGoodElectrons");
  SignatureTH1F_N* nposelectrons = new SignatureTH1F_N("nelectronspos","posGoodElectrons");
  SignatureTH1F_N* nnegtracks = new SignatureTH1F_N("ntracksneg","negGoodTracks");
  SignatureTH1F_N* npostracks = new SignatureTH1F_N("ntrackspos","posGoodTracks");

  handler->addHistogram(nnegmuons,"OnZ");
  handler->addHistogram(nposmuons,"OnZ");
  handler->addHistogram(nnegelectrons,"OnZ");
  handler->addHistogram(nposelectrons,"OnZ");
  handler->addHistogram(nnegtracks,"OnZ");
  handler->addHistogram(npostracks,"OnZ");

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
      varname1.ToUpper();
      handler->addEventVariable(varname1,new EventVariableInRange<int>(varname,j,j,varname1));
    }
  }

  //Signal channels
  for(int i_posMuons = 0; i_posMuons < 4; i_posMuons++){
    for(int i_negMuons = 0; i_negMuons < 4; i_negMuons++){
      for(int i_posElectrons = 0; i_posElectrons < 4; i_posElectrons++){
	for(int i_negElectrons = 0; i_negElectrons < 4; i_negElectrons++){
	  if(i_posMuons + i_negMuons + i_posElectrons + i_negElectrons != 3)continue;
	  int nMu = i_posMuons + i_negMuons;
	  int nEl = i_posElectrons + i_negElectrons;
	  //int nTr = i_posTracks + i_negTracks;
	  int qMu = i_posMuons - i_negMuons;
	  int qEl = i_posElectrons - i_negElectrons;
	  //int qTr = i_posTracks - i_negTracks;
	  TString chanName = makeName(qMu,nMu,qEl,nEl,0,0);
	  
	  //cout<<chanName<<" mu+: "<<i_posMuons<<" mu-: "<<i_negMuons<<" el+: "<<i_posElectrons<<" el-: "<<i_negElectrons<<" tr+: "<<i_posTracks<<" tr-: "<<i_negTracks<<" "<<endl;
	  
	  TString cut_posMuons = TString::Format("NPOSGOODMUONSEQ%i",i_posMuons);
	  TString cut_negMuons = TString::Format("NNEGGOODMUONSEQ%i",i_negMuons);
	  TString cut_posElectrons = TString::Format("NPOSGOODELECTRONSEQ%i",i_posElectrons);
	  TString cut_negElectrons = TString::Format("NNEGGOODELECTRONSEQ%i",i_negElectrons);
	  
	  handler->addSignature(chanName)
	    ->addCut(cut_posMuons)
	    ->addCut(cut_negMuons)
	    ->addCut(cut_posElectrons)
	    ->addCut(cut_negElectrons)
	    ;
	}
      }
    }
  }

  cout<<"test"<<endl;


  //Sideband channels
  for(int i_posMuons = 0; i_posMuons < 4; i_posMuons++){
    for(int i_negMuons = 0; i_negMuons < 4; i_negMuons++){
      for(int i_posElectrons = 0; i_posElectrons < 4; i_posElectrons++){
	for(int i_negElectrons = 0; i_negElectrons < 4; i_negElectrons++){
	  if(i_posMuons + i_negMuons + i_posElectrons + i_negElectrons != 2)continue;
	  //cout<<i_posMuons<<" "<<i_negMuons<<" "<<i_posElectrons<<" "<<i_negElectrons<<endl;
	  for(int i_tracks = 1; i_tracks < 4; i_tracks++){
	    int nMu = i_posMuons + i_negMuons;
	    int nEl = i_posElectrons + i_negElectrons;
	    int nTr = i_tracks;
	    int qMu = i_posMuons - i_negMuons;
	    int qEl = i_posElectrons - i_negElectrons;
	    int qTrp = i_tracks;
	    int qTrn = -i_tracks;
	    TString chanNamep = makeName(qMu,nMu,qEl,nEl,qTrp,nTr);
	    TString chanNamem = makeName(qMu,nMu,qEl,nEl,qTrn,nTr);
	    
	    cout<<chanNamep<<" mu+: "<<i_posMuons<<" mu-: "<<i_negMuons<<" el+: "<<i_posElectrons<<" el-: "<<i_negElectrons<<" tr: "<<i_tracks<<endl;
	    
	    TString cut_posMuons = TString::Format("NPOSGOODMUONSEQ%i",i_posMuons);
	    TString cut_negMuons = TString::Format("NNEGGOODMUONSEQ%i",i_negMuons);
	    TString cut_posElectrons = TString::Format("NPOSGOODELECTRONSEQ%i",i_posElectrons);
	    TString cut_negElectrons = TString::Format("NNEGGOODELECTRONSEQ%i",i_negElectrons);
	    TString cut_posTracks = TString::Format("NPOSGOODTRACKSEQ%i",i_tracks);
	    TString cut_negTracks = TString::Format("NNEGGOODTRACKSEQ%i",i_tracks);
	    
	    handler->addSignature(chanNamep)
	      ->addCut(cut_posMuons)
	      ->addCut(cut_negMuons)
	      ->addCut(cut_posElectrons)
	      ->addCut(cut_negElectrons)
	      ->addCut(cut_posTracks)
	      ;
	    handler->addSignature(chanNamem)
	      ->addCut(cut_posMuons)
	      ->addCut(cut_negMuons)
	      ->addCut(cut_posElectrons)
	      ->addCut(cut_negElectrons)
	      ->addCut(cut_negTracks)
	      ;
	  }
	}
      }
    }
  }

}
