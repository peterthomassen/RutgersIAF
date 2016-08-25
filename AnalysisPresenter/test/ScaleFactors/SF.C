void SF(){
  /*
  static TFile *feSF1=0;
  static TFile *feSF2=0;
  if(!feSF1)feSF1= new TFile("egammaEffi.txt_SF2D_Gsf_12p9ifb.root");
  if(!feSF2)feSF2= new TFile("egammaEffi.txt_SF2D_Med_12p9ifb.root");
  for(int p=0;p<=1;p++){
    TH2F *heSF;
    if(p==0)
      heSF = (TH2F*)feSF1->Get("EGamma_SF2D");
    if(p==1)
      heSF = (TH2F*)feSF2->Get("EGamma_SF2D");
    TAxis *EtaAxis=heSF->GetXaxis();
    TAxis *PtAxis=heSF->GetYaxis();
    double EtaMax=EtaAxis->GetXmax();
    double EtaMin=EtaAxis->GetXmin();
    int EtaBins=EtaAxis->GetNbins();
    double PtMax=PtAxis->GetXmax();
    double PtMin=PtAxis->GetXmin();
    int PtBins=PtAxis->GetNbins();
    cout<<"This is for file "<<p<<endl;
    for(int PBin=1;PBin<=PtBins;PBin++){
      cout<<"if(Pt>"<<PtAxis->GetBinLowEdge(PBin)<<"&& Pt<="
	  <<PtAxis->GetBinUpEdge(PBin)<<"){"<<endl;
      for(int EBin=1;EBin<=EtaBins;EBin++){
	cout<<"if(Eta>"<<EtaAxis->GetBinLowEdge(EBin)<<"&& Eta<="
	    <<EtaAxis->GetBinUpEdge(EBin)<<")SF=SF*"
	    <<heSF->GetBinContent(EBin,PBin)<<";"<<endl;
      }
      cout<<"}"<<endl;
    }
    
  }
  */
  static TFile *fmSF1=0;
  static TDirectory *dmSF1=0;
  if(!fmSF1)fmSF1= new TFile("MuonID_Z_RunBCD_prompt80X_7p65ifb.root");
  if(!dmSF1)dmSF1= (TDirectoryFile*)fmSF1->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_spliteta_bin1");
  TH2F *hmSF;
  hmSF = (TH2F*)dmSF1->Get("abseta_pt_ratio");
  TAxis *EtaAxis=hmSF->GetXaxis();                                                                                 
  TAxis *PtAxis=hmSF->GetYaxis();                                                                                  
  double EtaMax=EtaAxis->GetXmax();                                                                                
  double EtaMin=EtaAxis->GetXmin();                                                                                
  int EtaBins=EtaAxis->GetNbins();                                                                                 
  double PtMax=PtAxis->GetXmax();                                                                                  
  double PtMin=PtAxis->GetXmin();                                                                                  
  int PtBins=PtAxis->GetNbins();                                                                                   
  //  cout<<"This is for file "<<p<<endl;                                                                           

  cout<<"double muSF(double Pt,double Eta, int NVertices, bool VertexWeight=true){"<<endl;
  cout<<"if(Pt==-1&&Eta==543)return 1;"<<endl;
  cout<<"double SF=1;"<<endl;   
  for(int PBin=1;PBin<=PtBins;PBin++){                                                                             
    cout<<"if(Pt>"<<PtAxis->GetBinLowEdge(PBin)<<"&& Pt<="                                                         
	<<PtAxis->GetBinUpEdge(PBin)<<"){"<<endl;                                                                  
    for(int EBin=1;EBin<=EtaBins;EBin++){                                                                          
      cout<<"if(abs(Eta)>"<<EtaAxis->GetBinLowEdge(EBin)<<"&& abs(Eta)<="
	  <<EtaAxis->GetBinUpEdge(EBin)<<")SF=SF*"                                                                 
	  <<hmSF->GetBinContent(EBin,PBin)<<";"<<endl;                                                             
    }                                                                                                              
    cout<<"}"<<endl;                                                                                               
  }                                                    
  static TDirectory *dmVSF1=0;
  if(!dmVSF1)dmVSF1= (TDirectoryFile*)fmSF1->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_vtx");
  TH1F *hVSF=(TH1F*)dmVSF1->Get("tag_nVertices_ratio");
  TAxis *VAxis=hVSF->GetXaxis();
  double VMax=VAxis->GetXmax();
  double VMin=VAxis->GetXmin();
  int VBins=VAxis->GetNbins();
  cout<<"if(VertexWeight){"<<endl;
  for(int VBin=1;VBin<=VBins;VBin++){
    cout<<"if(NVertices>"<<VAxis->GetBinLowEdge(VBin)<<"&& NVertices<="
	<<VAxis->GetBinUpEdge(VBin)<<")SF=SF*"
	<<hVSF->GetBinContent(VBin)/hVSF->GetBinContent(8)<<";"<<endl;
  }
  cout<<"}"<<endl;
  static TFile *TrPOG_SF1=0;
  if(!TrPOG_SF1)TrPOG_SF1=new TFile("ratios_Tracking_efficiency_12p9ifb.root");
  TGraphAsymmErrors *etaRatio=(TGraphAsymmErrors*) TrPOG_SF1->Get("ratio_eta");
  Double_t xp,yp;
  for(int i=0;i<etaRatio->GetN();i++){
    etaRatio->GetPoint(i,xp,yp);
    cout<<"if(Eta<="<<xp+etaRatio->GetErrorXhigh(i)<<"&&Eta>"<<xp-etaRatio->GetErrorXlow(i)<<")"
	<<"SF=SF*"<<yp<<";"<<endl;  
  }
  cout<<"return SF;"<<endl;
  cout<<"}"<<endl;
  
}
