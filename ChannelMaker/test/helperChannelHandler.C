void addDataFiles(ChannelHandler* handler,TString filelist, double lum, double lumunc)
{
  handler->setLuminosity(lum);
  handler->setLuminosityError(lum*lumunc);

  ifstream files(filelist);
  while(1){
    TString fname;
    files >> fname;
    if(!files.good())break;
    handler->addDataFile(fname);
  }
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void addSimulations(ChannelHandler* handler, TString filelist)
{
  ifstream files(filelist);
  while(1){
    TString label,fname;
    double xsec,xsecerr;
    files >> label >> fname >> xsec >> xsecerr;
    if(!files.good())break;
    handler->addSimulationFileAndXsec(label,fname,xsec,xsec*xsecerr);
  }
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void setConstants2011(ChannelHandler* handler)
{

  handler->setTrackToMuonFakeRate(0.0145);
  handler->setTrackToMuonFakeRateError(0.0015);
  handler->setTrackToElectronFakeRate(0.013);
  handler->setTrackToElectronFakeRateError(0.0035);

  handler->setPhotonToMuonFakeRate(0.0032);
  handler->setPhotonToMuonFakeRateError(0.0033);
  handler->setPhotonToElectronFakeRate(0.0145);
  handler->setPhotonToElectronFakeRateError(0.0146);

  handler->setElectronChargeFlipRate(0.00419);
  handler->setElectronChargeFlipRateError(4.28e-4);
  handler->setMuonChargeFlipRate(1.72e-5);
  handler->setMuonChargeFlipRateError(1.72e-5);

}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void addChannels2011(ChannelHandler* handler)
{

  TString lep_channels[9] = {"Mu4El0","Mu3El1","Mu2El2","Mu1El3","Mu0El4","Mu3El0","Mu2El1","Mu1El2","Mu0El3"};
  TString met_tags[2] = {"","MET"};
  TString ht_tags[2] = {"","HT"};
  TString b_tags[3] = {"B0","B1","B2"};
  TString dy_tags[3] = {"DY0","DY1","DY2"};
  TString zv_tags[2] = {"offZ","onZ"};
  int lep_maxdy[9] = {2,2,2,2,2,1,1,1,1};
  int nlep[9] = {4,4,4,4,4,3,3,3,3};

  TString lep2_channels[9] = {"Mu2El0DY0","Mu2El0DY1onZ","Mu2El0DY1offZ","Mu1El1OS","Mu1El1SSP","Mu1El1SSN","Mu0El2DY0","Mu0El2DY1onZ","Mu0El2DY1offZ"};
  TString attr2_names[3] = {"L2OSoffZ","L2OSonZ","L2SS"};
  int lep2_attr[9] = {2,1,0,0,2,2,2,1,0};
  for(int n = 0; n < 9; n++){
    for(int i = 0; i < 2; i++){
      for(int l = 0; l < 2; l++){
	for(int b = 0; b < 3; b++){
	  TString name = lep2_channels[n];
	  name += b_tags[b]+ht_tags[i]+met_tags[l];
	  TString attribute = attr2_names[lep2_attr[n]]+b_tags[b]+ht_tags[i]+met_tags[l];
	  Channel* channel = new Channel(name);
	  channel->setAttribute(attribute,1.0);
	  handler->addInputChannel(channel);
	  if(n < 3){
	    handler->addSumChannelAttribute(attribute,attribute,1.0);
	  }
	}
      }
    }
  }

  for(int n = 0; n < 9; n++){
    for(int i = 0; i < 2; i++){
      for(int l = 0; l < 2; l++){
	for(int b = 0; b < 3; b++){
	  for(int j = 0; j < 3 && j<=lep_maxdy[n]; j++){
	    for(int k = 0; k < 2; k++){
	      if(j == 0; &&k > 0)continue;
	      TString attribute = "L";
	      attribute += nlep[n];
	      attribute += zv_tags[j];
	      attribute += b_tags[b];
	      attribute += ht_tags[i];
	      attribute += met_tags[i];
	      if(j == 0){
		addSumChannelAttribute(attribute,attribute,1.0);
	      }
	      TString name = lep_channels[n];
	      name += dy_tags[j];
	      name += zv_tags[k];
	      name += b_tags[b];
	      name += ht_tags[i];
	      name += met_tags[l];
	      Channel* channel = new Channel(name);
	      channel->setAttribute(attribute,1.0);
	      handler->addInputChannel(name,channel);
	    }
	  }
	}
      }
    }
  }
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void addChannels2012TTW(ChannelHandler* handler)
{
  TString met_tags[2] = {"","MET"};
  TString ht_tags[2] = {"","HT"};
  TString b_tags[3] = {"B0","B1","B2"};
  //TString sumChannels[6] = {"2LSS","2LDY1onZ","2LOSoffZ","3LDY0","3LDY1onZ","3LDY1offZ"};
  TString sumChannels[8] = {"L2SS","L2DY1onZ","L2OSoffZ","L3DY0","L3DY1onZ","L3DY1offZ","L4onZ","L4offZ"};
  double efr[2][3] = {{0.111,0.0676,0.0583},{0.117,0.052,0.076}};
  double mfr[2][3] = {{0.046,0.0185,0.0322},{0.0207,0.0125,0.0212}};
  double efe[2][3] = {{0.05,0.033,0.029},{0.06,0.026,0.038}};
  double mfe[2][3] = {{0.023,0.01,0.016},{0.01,0.006,0.01}};
  double negToPosFlipRate = 0.000704;
  double negToPosFlipErr = 0.2 * negToPosFlipRate;
  double posToNegFlipRate = 0.000469;
  double posToNegFlipErr = 0.2 * posToNegFlipRate;

  for(int m = 0; m < 2; m++){
    for(int h = 0; h < 2; h++){
      for(int b= 0; b < 3; b++){
	TString suffix = b_tags[b]+ht_tags[h]+met_tags[m];
	for(int s = 0; s < 8; s++){
	  TString attribute = sumChannels[s]+suffix;
	  handler->addSumChannelAttribute(attribute,attribute,1.0);
	  cout<<"attribute: "<<attribute<<endl;
	}
      }
    }
  }

  for(int m = 0; m < 2; m++){
    for(int h = 0; h < 2; h++){
      for(int b= 0; b < 3; b++){
	TString suffix = b_tags[b]+ht_tags[h]+met_tags[m];
	TString name;

	name = "Mu1El0Pos"+suffix;
	Channel* caa = new Channel(name);
	handler->addInputChannel(name,caa);
	name = "Mu1El0Neg"+suffix;
	Channel* cab = new Channel(name);
	handler->addInputChannel(name,cab);
	name = "Mu0El1Pos"+suffix;
	Channel* cac = new Channel(name);
	handler->addInputChannel(name,cac);
	name = "Mu0El1Neg"+suffix;
	Channel* cad = new Channel(name);
	handler->addInputChannel(name,cad);
	name = "Mu2El0DY1onZ"+suffix;
	Channel* cae = new Channel(name);
	handler->addInputChannel(name,cae);
	name = "Mu2El0DY1offZ"+suffix;
	Channel* caf = new Channel(name);
	handler->addInputChannel(name,caf);
	name = "Mu0El2DY1onZ"+suffix;
	Channel* cag = new Channel(name);
	handler->addInputChannel(name,cag);
	name = "Mu0El2DY1offZ"+suffix;
	Channel* cah = new Channel(name);
	handler->addInputChannel(name,cah);
	name = "Mu1El1OS"+suffix;
	Channel* cai = new Channel(name);
	handler->addInputChannel(name,cai);

	name = "Mu0El2DY0Track"+suffix;
	Channel* caj = new Channel(name);
	handler->addInputChannel(name,caj);

	name = "Mu0El2DY1offZTrack"+suffix;
	Channel* cak = new Channel(name);
	handler->addInputChannel(name,cak);

	name = "Mu0El2DY1onZTrack"+suffix;
	Channel* cal = new Channel(name);
	handler->addInputChannel(name,cal);

	name = "Mu2El0DY0Track"+suffix;
	Channel* cam = new Channel(name);
	handler->addInputChannel(name,cam);

	name = "Mu2El0DY1offZTrack"+suffix;
	Channel* can = new Channel(name);
	handler->addInputChannel(name,can);

	name = "Mu2El0DY1onZTrack"+suffix;
	Channel* cao = new Channel(name);
	handler->addInputChannel(name,cao);

	name = "Mu1El1OSTrack"+suffix;
	Channel* cap = new Channel(name);
	handler->addInputChannel(name,cap);

	name = "Mu1El1SSPTrack"+suffix;
	Channel* caq = new Channel(name);
	handler->addInputChannel(name,caq);

	name = "Mu1El1SSNTrack"+suffix;
	Channel* car = new Channel(name);
	handler->addInputChannel(name,car);


	name = "Mu3El0DY0offZTrack"+suffix;
	Channel* cas = new Channel(name);
	handler->addInputChannel(name,cas);

	name = "Mu3El0DY1offZTrack"+suffix;
	Channel* cat = new Channel(name);
	handler->addInputChannel(name,cat);

	name = "Mu3El0DY1onZTrack"+suffix;
	Channel* cau = new Channel(name);
	handler->addInputChannel(name,cau);

	name = "Mu2El1DY0offZTrack"+suffix;
	Channel* cav = new Channel(name);
	handler->addInputChannel(name,cav);

	name = "Mu2El1DY1offZTrack"+suffix;
	Channel* caw = new Channel(name);
	handler->addInputChannel(name,caw);

	name = "Mu2El1DY1onZTrack"+suffix;
	Channel* cax = new Channel(name);
	handler->addInputChannel(name,cax);

	name = "Mu1El2DY0offZTrack"+suffix;
	Channel* cay = new Channel(name);
	handler->addInputChannel(name,cay);

	name = "Mu1El2DY1offZTrack"+suffix;
	Channel* caz = new Channel(name);
	handler->addInputChannel(name,caz);

	name = "Mu1El2DY1onZTrack"+suffix;
	Channel* cba = new Channel(name);
	handler->addInputChannel(name,cba);

	name = "Mu0El3DY0offZTrack"+suffix;
	Channel* cbb = new Channel(name);
	handler->addInputChannel(name,cbb);

	name = "Mu0El3DY1offZTrack"+suffix;
	Channel* cbc = new Channel(name);
	handler->addInputChannel(name,cbc);

	name = "Mu0El3DY1onZTrack"+suffix;
	Channel* cbd = new Channel(name);
	handler->addInputChannel(name,cbd);


	name = "Mu2El0DY0"+suffix;
	Channel* c0 = new Channel(name);
	c0->setAttribute("L2SS"+suffix,1.0);
	c0->addFakeObjectChannel("fakeMuonPos","Mu1El0Pos"+suffix,1.0);
	c0->addFakeObjectChannel("fakeMuonNeg","Mu1El0Neg"+suffix,1.0);
	c0->addFakeObjectChannel("fakePhotonToMuon","Mu1El0Pos"+suffix,0.5);
	c0->addFakeObjectChannel("fakePhotonToMuon","Mu1El0Neg"+suffix,0.5);
	c0->setFakeRateAndError("fakeMuonPos",mfr[h][b],mfe[h][b]);
	c0->setFakeRateAndError("fakeMuonNeg",mfr[h][b],mfe[h][b]);
	handler->addInputChannel(name,c0);
	
	name = "Mu0El2DY0"+suffix;
	Channel* c1 = new Channel(name);
	c1->setAttribute("L2SS"+suffix,1.0);
	c1->addFakeObjectChannel("fakeElectronPos","Mu0El1Pos"+suffix,1.0);
	c1->addFakeObjectChannel("fakeElectronNeg","Mu0El1Neg"+suffix,1.0);
	c1->setFakeRateAndError("fakeElectronPos",efr[h][b],efe[h][b]);
	c1->setFakeRateAndError("fakeElectronNeg",efr[h][b],efe[h][b]);
	c1->addFakeObjectChannel("fakePhotonToElectron","Mu0El1Pos"+suffix,0.5);
	c1->addFakeObjectChannel("fakePhotonToElectron","Mu0El1Neg"+suffix,0.5);
	c1->addFakeChannel("flipElectronPos","Mu0El2DY1onZ"+suffix,1.0);
	c1->addFakeChannel("flipElectronNeg","Mu0El2DY1onZ"+suffix,1.0);
	c1->addFakeChannel("flipElectronPos","Mu0El2DY1offZ"+suffix,1.0);
	c1->addFakeChannel("flipElectronNeg","Mu0El2DY1offZ"+suffix,1.0);
	handler->addInputChannel(name,c1);

	name = "Mu1El1SSN"+suffix;
	Channel* c2 = new Channel(name);
	c2->setAttribute("L2SS"+suffix,1.0);
	c2->addFakeObjectChannel("fakeElectronNeg","Mu1El0Neg"+suffix,1.0);
	c2->addFakeObjectChannel("fakeMuonNeg","Mu0El1Neg"+suffix,1.0);
	c2->setFakeRateAndError("fakeElectronNeg",efr[h][b],efe[h][b]);
	c2->setFakeRateAndError("fakeMuonNeg",mfr[h][b],mfe[h][b]);
	c2->addFakeChannel("flipElectronNeg","Mu1El1OS"+suffix,0.5);
	c2->addFakeObjectChannel("fakePhotonToElectron","Mu1El0Neg"+suffix,0.5);
	c2->addFakeObjectChannel("fakePhotonToMuon","Mu0El1Neg"+suffix,0.5);
	handler->addInputChannel(name,c2);

	name = "Mu1El1SSP"+suffix;
	Channel* c3 = new Channel(name);
	c3->setAttribute("L2SS"+suffix,1.0);
	c3->addFakeObjectChannel("fakeElectronPos","Mu1El0Pos"+suffix,1.0);
	c3->addFakeObjectChannel("fakeMuonPos","Mu0El1Pos"+suffix,1.0);
	c3->setFakeRateAndError("fakeElectronPos",efr[h][b],efe[h][b]);
	c3->setFakeRateAndError("fakeMuonPos",mfr[h][b],mfe[h][b]);
	c3->addFakeChannel("flipElectronPos","Mu1El1OS"+suffix,0.5);
	c2->addFakeObjectChannel("fakePhotonToElectron","Mu1El0Pos"+suffix,0.5);
	c2->addFakeObjectChannel("fakePhotonToMuon","Mu0El1Pos"+suffix,0.5);
	handler->addInputChannel(name,c3);

	name = "Mu3El0DY0offZ"+suffix;
	Channel* c4 = new Channel(name);
	c4->setAttribute("L3DY0"+suffix,1.0);
	c4->addCFOChannel("fakeMuon","Mu2El0DY0Track"+suffix,0.5);
	//c4->setFakeRateAndError("fakeMuon",mfr[h][b],mfe[h][b]);
	c4->addFakeObjectChannel("fakePhotonToMuon","Mu2El0DY0"+suffix,0.5);
	handler->addInputChannel(name,c4);

	name = "Mu3El0DY1offZ"+suffix;
	Channel* c5 = new Channel(name);
	c5->setAttribute("L3DY1offZ"+suffix,1.0);
	c5->addCFOChannel("fakeMuon","Mu2El0DY0Track"+suffix,0.5);
	c5->addCFOChannel("fakeMuon","Mu2El0DY1offZTrack"+suffix,1.0);
	c5->addFakeObjectChannel("fakePhotonToMuon","Mu2El0DY0"+suffix,0.5);
	c5->addFakeObjectChannel("fakePhotonToMuon","Mu2El0DY1offZ"+suffix,1.0);
	c5->setFakeRateAndError("fakeMuon",mfr[h][b],mfe[h][b]);
	handler->addInputChannel(name,c5);

	name = "Mu3El0DY1onZ"+suffix;
	Channel* c6 = new Channel(name);
	c6->setAttribute("L3DY1onZ"+suffix,1.0);
	//c6->setFakeRateAndError("fakeMuon",mfr[h][b],mfe[h][b]);
	c6->addCFOChannel("fakeMuon","Mu2El0DY1onZTrack"+suffix,1.0);
	c6->addFakeObjectChannel("fakePhotonToMuon","Mu2El0DY1onZ"+suffix,1.0);
	handler->addInputChannel(name,c6);

	name = "Mu2El1DY0offZ"+suffix;
	Channel* c7 = new Channel(name);
	c7->setAttribute("L3DY0"+suffix,1.0);
	//c7->setFakeRateAndError("fakeMuon",mfr[h][b],mfe[h][b]);
	c7->setFakeRateAndError("fakeMuonPos",mfr[h][b],mfe[h][b]);
	c7->setFakeRateAndError("fakeMuonNeg",mfr[h][b],mfe[h][b]);
	//c7->setFakeRateAndError("fakeElectron",efr[h][b],efe[h][b]);
	c7->addCFOChannel("fakeMuon","Mu1El1OSTrack"+suffix,0.5);
	//c7->addCFOChannel("fakeMuon","Mu1El1OSTrack"+suffix,0.5);
	c7->addCFOChannel("fakeMuon","Mu1El1SSNTrack"+suffix,0.5);
	c7->addCFOChannel("fakeMuon","Mu1El1SSPTrack"+suffix,0.5);
	c7->addCFOChannel("fakeElectron","Mu2El0DY0Track"+suffix,1.0);
	c7->addFakeObjectChannel("fakePhotonToElectron","Mu2El0DY0"+suffix,1.0);
	c7->addFakeObjectChannel("fakePhotonToMuon","Mu1El1OS"+suffix,0.5);
	c7->addFakeObjectChannel("fakePhotonToMuon","Mu1El1SSN"+suffix,0.5);
	c7->addFakeObjectChannel("fakePhotonToMuon","Mu1El1SSP"+suffix,0.5);
	handler->addInputChannel(name,c7);

	name = "Mu2El1DY1offZ"+suffix;
	Channel* c8 = new Channel(name);
	c8->setAttribute("L3DY1offZ"+suffix,1.0);
	//c8->setFakeRateAndError("fakeMuon",mfr[h][b],mfe[h][b]);
	c8->setFakeRateAndError("fakeMuonPos",mfr[h][b],mfe[h][b]);
	c8->setFakeRateAndError("fakeMuonNeg",mfr[h][b],mfe[h][b]);
	//c8->setFakeRateAndError("fakeElectron",efr[h][b],efe[h][b]);
	c8->addCFOChannel("fakeMuon","Mu1El1OSTrack"+suffix,0.5);
	//c8->addCFOChannel("fakeMuon","Mu1El1OSTrack"+suffix,0.5);
	c8->addCFOChannel("fakeMuon","Mu1El1SSPTrack"+suffix,0.5);
	c8->addCFOChannel("fakeMuon","Mu1El1SSNTrack"+suffix,0.5);
	c8->addCFOChannel("fakeElectron","Mu2El0DY1offZTrack"+suffix,1.0);
	c8->addFakeObjectChannel("fakePhotonToElectron","Mu2El0DY1offZ"+suffix,1.0);
	c8->addFakeObjectChannel("fakePhotonToMuon","Mu1El1OS"+suffix,0.5);
	c8->addFakeObjectChannel("fakePhotonToMuon","Mu1El1SSP"+suffix,0.5);
	c8->addFakeObjectChannel("fakePhotonToMuon","Mu1El1SSN"+suffix,0.5);

	handler->addInputChannel(name,c8);

	name = "Mu2El1DY1onZ"+suffix;
	Channel* c9 = new Channel(name);
	c9->setAttribute("L3DY1onZ"+suffix,1.0);
	c9->setFakeRateAndError("fakeElectron",efr[h][b],efe[h][b]);
	c9->addCFOChannel("fakeElectron","Mu2El0DY1onZTrack"+suffix,1.0);
	c9->addFakeObjectChannel("fakePhotonToElectron","Mu2El0DY1onZ"+suffix,1.0);
	handler->addInputChannel(name,c9);

	name = "Mu1El2DY0offZ"+suffix;
	Channel* c10 = new Channel(name);
	c10->setAttribute("L3DY0"+suffix,1.0);
	//c10->setFakeRateAndError("fakeElectron",efr[h][b],efe[h][b]);
	c10->setFakeRateAndError("fakeElectronPos",efr[h][b],efe[h][b]);
	c10->setFakeRateAndError("fakeElectronNeg",efr[h][b],efe[h][b]);
	//c10->setFakeRateAndError("fakeMuon",mfr[h][b],mfe[h][b]);
	c10->addCFOChannel("fakeElectron","Mu1El1OSTrack"+suffix,0.5);
	//c10->addCFOChannel("fakeElectron","Mu1El1OS"+suffix,0.5);
	c10->addCFOChannel("fakeElectron","Mu1El1SSNTrack"+suffix,0.5);
	c10->addCFOChannel("fakeElectron","Mu1El1SSPTrack"+suffix,0.5);
	c10->addCFOChannel("fakeMuon","Mu0El2DY0Track"+suffix,1.0);
	c10->addFakeObjectChannel("fakePhotonToMuon","Mu0El2DY0"+suffix,1.0);
	c10->addFakeObjectChannel("fakePhotonToElectron","Mu1El1OS"+suffix,0.5);
	c10->addFakeObjectChannel("fakePhotonToElectron","Mu1El1SSN"+suffix,0.5);
	c10->addFakeObjectChannel("fakePhotonToElectron","Mu1El1SSP"+suffix,0.5);
	handler->addInputChannel(name,c10);

	name = "Mu1El2DY1offZ"+suffix;
	Channel* c11 = new Channel(name);
	c11->setAttribute("L3DY1offZ"+suffix,1.0);
	//c11->setFakeRateAndError("fakeElectron",efr[h][b],efe[h][b]);
	c11->setFakeRateAndError("fakeElectronPos",efr[h][b],efe[h][b]);
	c11->setFakeRateAndError("fakeElectronNeg",efr[h][b],efe[h][b]);
	//c11->setFakeRateAndError("fakeMuon",mfr[h][b],mfe[h][b]);
	c11->addCFOChannel("fakeElectron","Mu1El1OSTrack"+suffix,0.5);
	//c11->addCFOChannel("fakeElectron","Mu1El1OS"+suffix,0.5);
	c11->addCFOChannel("fakeElectron","Mu1El1SSPTrack"+suffix,0.5);
	c11->addCFOChannel("fakeElectron","Mu1El1SSNTrack"+suffix,0.5);
	c11->addCFOChannel("fakeMuon","Mu0El2DY1offZTrack"+suffix,1.0);
	c11->addFakeObjectChannel("fakePhotonToMuon","Mu0El2DY1offZ"+suffix,1.0);
	c11->addFakeObjectChannel("fakePhotonToElectron","Mu1El1OS"+suffix,0.5);
	c11->addFakeObjectChannel("fakePhotonToElectron","Mu1El1SSP"+suffix,0.5);
	c11->addFakeObjectChannel("fakePhotonToElectron","Mu1El1SSN"+suffix,0.5);
	handler->addInputChannel(name,c11);

	name = "Mu1El2DY1onZ"+suffix;
	Channel* c12 = new Channel(name);
	c12->setAttribute("L3DY1onZ"+suffix,1.0);
	//c12->setFakeRateAndError("fakeMuon",mfr[h][b],mfe[h][b]);
	c12->addCFOChannel("fakeMuon","Mu0El2DY1onZTrack"+suffix,1.0);
	c12->addFakeObjectChannel("fakePhotonToMuon","Mu0El2DY1onZ"+suffix,1.0);
	handler->addInputChannel(name,c12);

	name = "Mu0El3DY0offZ"+suffix;
	Channel* c13 = new Channel(name);
	c13->setAttribute("L3DY0"+suffix,1.0);
	c13->addCFOChannel("fakeElectron","Mu0El2DY0Track"+suffix,0.5);
	c13->addFakeObjectChannel("fakePhotonToElectron","Mu0El2DY0"+suffix,0.5);
	//c13->setFakeRateAndError("fakeElectron",efr[h][b],efe[h][b]);
	handler->addInputChannel(name,c13);

	name = "Mu0El3DY1offZ"+suffix;
	Channel* c14 = new Channel(name);
	c14->setAttribute("L3DY1offZ"+suffix,1.0);
	c14->addCFOChannel("fakeElectron","Mu0El2DY0Track"+suffix,0.5);
	c14->addFakeObjectChannel("fakePhotonToElectron","Mu0El2DY0"+suffix,0.5);
	c14->addCFOChannel("fakeElectron","Mu0El2DY1offZTrack"+suffix,1.0);
	c14->addFakeObjectChannel("fakePhotonToElectron","Mu0El2DY1offZ"+suffix,1.0);
	//c14->setFakeRateAndError("fakeElectron",efr[h][b],efe[h][b]);
	handler->addInputChannel(name,c14);

	name = "Mu0El3DY1onZ"+suffix;
	Channel* c15 = new Channel(name);
	c15->setAttribute("L3DY1onZ"+suffix,1.0);
	//c15->setFakeRateAndError("fakeElectron",efr[h][b],efe[h][b]);
	c15->addCFOChannel("fakeElectron","Mu0El2DY1onZTrack"+suffix,1.0);
	c15->addFakeObjectChannel("fakePhotonToElectron","Mu0El2DY1onZ"+suffix,1.0);
	handler->addInputChannel(name,c15);

	name = "Mu4El0DY0offZ"+suffix;
	Channel* c16 = new Channel(name);
	c16->setAttribute("L4offZ"+suffix,1.0);
	c16->addCFOChannel("fakeMuon","Mu3El0DY0offZTrack"+suffix,0.5);
	c16->addFakeObjectChannel("fakePhotonToMuon","Mu3El0DY0offZ"+suffix,0.5);
	handler->addInputChannel(name,c16);

	name = "Mu4El0DY1offZ"+suffix;
	Channel* c17 = new Channel(name);
	c17->setAttribute("L4offZ"+suffix,1.0);
	c17->addCFOChannel("fakeMuon","Mu3El0DY0offZTrack"+suffix,0.5);
	c17->addCFOChannel("fakeMuon","Mu3El0DY1offZTrack"+suffix,0.5);
	c17->addFakeObjectChannel("fakePhotonToMuon","Mu3El0DY0offZ"+suffix,0.5);
	c17->addFakeObjectChannel("fakePhotonToMuon","Mu3El0DY1offZ"+suffix,0.5);
	handler->addInputChannel(name,c17);

	name = "Mu4El0DY1onZ"+suffix;
	Channel* c18 = new Channel(name);
	c18->setAttribute("L4onZ"+suffix,1.0);
	c18->addCFOChannel("fakeMuon","Mu3El0DY1onZTrack"+suffix,0.5);
	c18->addFakeObjectChannel("fakePhotonToMuon","Mu3El0DY1onZ"+suffix,0.5);
	handler->addInputChannel(name,c18);

	name = "Mu4El0DY2offZ"+suffix;
	Channel* c19 = new Channel(name);
	c19->setAttribute("L4offZ"+suffix,1.0);
	c19->addCFOChannel("fakeMuon","Mu3El0DY1offZTrack"+suffix,0.5);
	c19->addFakeObjectChannel("fakePhotonToMuon","Mu3El0DY1offZ"+suffix,0.5);
	handler->addInputChannel(name,c19);

	name = "Mu4El0DY2onZ"+suffix;
	Channel* c20 = new Channel(name);
	c20->setAttribute("L4onZ"+suffix,1.0);
	c20->addCFOChannel("fakeMuon","Mu3El0DY1onZTrack"+suffix,0.5);
	c20->addFakeObjectChannel("fakePhotonToMuon","Mu3El0DY1onZ"+suffix,0.5);
	handler->addInputChannel(name,c20);

	name = "Mu3El1DY0offZ"+suffix;
	Channel* c21 = new Channel(name);
	c21->setAttribute("L4offZ"+suffix,1.0);
	c21->addCFOChannel("fakeMuon","Mu2El1DY0offZTrack"+suffix,0.5);
	c21->addFakeObjectChannel("fakePhotonToMuon","Mu2El1DY0offZ"+suffix,0.5);
	c21->addCFOChannel("fakeElectron","Mu3El0DY0offZTrack"+suffix,1.0);
	c21->addFakeObjectChannel("fakePhotonToElectron","Mu3El0DY0offZ"+suffix,1.0);
	handler->addInputChannel(name,c21);

	name = "Mu3El1DY1offZ"+suffix;
	Channel* c22 = new Channel(name);
	c22->setAttribute("L4offZ"+suffix,1.0);
	c22->addCFOChannel("fakeMuon","Mu2El1DY0offZTrack"+suffix,0.5);
	c22->addFakeObjectChannel("fakePhotonToMuon","Mu2El1DY0offZ"+suffix,0.5);
	c22->addCFOChannel("fakeMuon","Mu2El1DY1offZTrack"+suffix,1.0);
	c22->addFakeObjectChannel("fakePhotonToMuon","Mu2El1DY1offZ"+suffix,1.0);
	c22->addCFOChannel("fakeElectron","Mu3El0DY1offZTrack"+suffix,1.0);
	c22->addFakeObjectChannel("fakePhotonToElectron","Mu3El0DY1offZ"+suffix,1.0);
	handler->addInputChannel(name,c22);

	name = "Mu3El1DY1onZ"+suffix;
	Channel* c23 = new Channel(name);
	c23->setAttribute("L4onZ"+suffix,1.0);
	c23->addCFOChannel("fakeMuon","Mu2El1DY1onZTrack"+suffix,1.0);
	c23->addFakeObjectChannel("fakePhotonToMuon","Mu2El1DY1onZ"+suffix,1.0);
	c23->addCFOChannel("fakeElectron","Mu3El0DY1onZTrack"+suffix,1.0);
	c23->addFakeObjectChannel("fakePhotonToElectron","Mu3El0DY1onZ"+suffix,1.0);
	handler->addInputChannel(name,c23);

	name = "Mu2El2DY0offZ"+suffix;
	Channel* c24 = new Channel(name);
	c24->setAttribute("L4offZ"+suffix,1.0);
	c24->addCFOChannel("fakeMuon","Mu1El2DY0offZTrack"+suffix,0.5);
	c24->addFakeObjectChannel("fakePhotonToMuon","Mu1El2DY0offZ"+suffix,0.5);
	c24->addCFOChannel("fakeElectron","Mu2El1DY0offZTrack"+suffix,0.5);
	c24->addFakeObjectChannel("fakePhotonToElectron","Mu2El1DY0offZ"+suffix,0.5);
	handler->addInputChannel(name,c24);

	name = "Mu2El2DY1offZ"+suffix;
	Channel* c25 = new Channel(name);
	c25->setAttribute("L4offZ"+suffix,1.0);
	c25->addCFOChannel("fakeMuon","Mu1El2DY0offZTrack"+suffix,0.5);
	c25->addFakeObjectChannel("fakePhotonToMuon","Mu1El2DY0offZ"+suffix,0.5);
	c25->addCFOChannel("fakeMuon","Mu1El2DY1offZTrack"+suffix,0.5);
	c25->addFakeObjectChannel("fakePhotonToMuon","Mu1El2DY1offZ"+suffix,0.5);
	c25->addCFOChannel("fakeElectron","Mu2El1DY0offZTrack"+suffix,0.5);
	c25->addFakeObjectChannel("fakePhotonToElectron","Mu2El1DY0offZ"+suffix,0.5);
	c25->addCFOChannel("fakeElectron","Mu2El1DY1offZTrack"+suffix,0.5);
	c25->addFakeObjectChannel("fakePhotonToElectron","Mu2El1DY1offZ"+suffix,0.5);
	handler->addInputChannel(name,c25);

	name = "Mu2El2DY1onZ"+suffix;
	Channel* c26 = new Channel(name);
	c26->setAttribute("L4onZ"+suffix,1.0);
	c26->addCFOChannel("fakeElectron","Mu2El1DY1onZTrack"+suffix,0.5);
	c26->addFakeObjectChannel("fakePhotonToElectron","Mu2El1DY1onZ"+suffix,0.5);
	c26->addCFOChannel("fakeMuon","Mu1El2DY1onZTrack"+suffix,0.5);
	c26->addFakeObjectChannel("fakePhotonToMuon","Mu1El2DY1onZ"+suffix,0.5);
	handler->addInputChannel(name,c26);

	name = "Mu2El2DY2offZ"+suffix;
	Channel* c27 = new Channel(name);
	c27->setAttribute("L4offZ"+suffix,1.0);
	c27->addCFOChannel("fakeMuon","Mu1El2DY1offZTrack"+suffix,0.5);
	c27->addFakeObjectChannel("fakePhotonToMuon","Mu1El2DY1offZ"+suffix,0.5);
	c27->addCFOChannel("fakeElectron","Mu2El1DY1offZTrack"+suffix,0.5);
	c27->addFakeObjectChannel("fakePhotonToElectron","Mu2El1DY1offZ"+suffix,0.5);
	handler->addInputChannel(name,c27);

	name = "Mu2El2DY2onZ"+suffix;
	Channel* c28 = new Channel(name);
	c28->setAttribute("L4onZ"+suffix,1.0);
	c28->addCFOChannel("fakeElectron","Mu2El1DY1onZTrack"+suffix,0.5);
	c28->addFakeObjectChannel("fakePhotonToElectron","Mu2El1DY1onZ"+suffix,0.5);
	c28->addCFOChannel("fakeMuon","Mu1El2DY1onZTrack"+suffix,0.5);
	c28->addFakeObjectChannel("fakePhotonToMuon","Mu1El2DY1onZ"+suffix,0.5);
	handler->addInputChannel(name,c28);


	name = "Mu1El3DY0offZ"+suffix;
	Channel* c29 = new Channel(name);
	c29->setAttribute("L4offZ"+suffix,1.0);
	c29->addCFOChannel("fakeMuon","Mu0El3DY0offZTrack"+suffix,1.0);
	c29->addFakeObjectChannel("fakePhotonToMuon","Mu0El3DY0offZ"+suffix,1.0);
	c29->addCFOChannel("fakeElectron","Mu1El2DY0offZTrack"+suffix,0.5);
	c29->addFakeObjectChannel("fakePhotonToElectron","Mu1El2DY0offZ"+suffix,0.5);
	handler->addInputChannel(name,c29);

	name = "Mu1El3DY1offZ"+suffix;
	Channel* c30 = new Channel(name);
	c30->setAttribute("L4offZ"+suffix,1.0);
	c30->addCFOChannel("fakeMuon","Mu0El3DY0offZTrack"+suffix,1.0);
	c30->addFakeObjectChannel("fakePhotonToMuon","Mu0El3DY0offZ"+suffix,1.0);
	c30->addCFOChannel("fakeElectron","Mu1El2DY0offZTrack"+suffix,0.5);
	c30->addFakeObjectChannel("fakePhotonToElectron","Mu1El2DY0offZ"+suffix,0.5);
	c30->addCFOChannel("fakeElectron","Mu1El2DY1offZTrack"+suffix,1.0);
	c30->addFakeObjectChannel("fakePhotonToElectron","Mu1El2DY1offZ"+suffix,1.0);
	handler->addInputChannel(name,c30);

	name = "Mu1El3DY1onZ"+suffix;
	Channel* c31 = new Channel(name);
	c31->setAttribute("L4onZ"+suffix,1.0);
	c31->addCFOChannel("fakeMuon","Mu0El3DY1onZTrack"+suffix,1.0);
	c31->addFakeObjectChannel("fakePhotonToMuon","Mu0El3DY1onZ"+suffix,1.0);
	c31->addCFOChannel("fakeElectron","Mu1El2DY1onZTrack"+suffix,1.0);
	c31->addFakeObjectChannel("fakePhotonToElectron","Mu1El2DY1onZ"+suffix,1.0);
	handler->addInputChannel(name,c31);

	name = "Mu0El4DY0offZ"+suffix;
	Channel* c32 = new Channel(name);
	c32->setAttribute("L4offZ"+suffix,1.0);
	c32->addCFOChannel("fakeElectron","Mu0El3DY0offZTrack"+suffix,0.5);
	c32->addFakeObjectChannel("fakePhotonToElectron","Mu0El3DY0offZ"+suffix,0.5);
	handler->addInputChannel(name,c32);

	name = "Mu0El4DY1offZ"+suffix;
	Channel* c33 = new Channel(name);
	c33->setAttribute("L4offZ"+suffix,1.0);
	c33->addCFOChannel("fakeElectron","Mu0El3DY0offZTrack"+suffix,0.5);
	c33->addFakeObjectChannel("fakePhotonToElectron","Mu0El3DY0offZ"+suffix,0.5);
	c33->addCFOChannel("fakeElectron","Mu0El3DY1offZTrack"+suffix,0.5);
	c33->addFakeObjectChannel("fakePhotonToElectron","Mu0El3DY1offZ"+suffix,0.5);
	handler->addInputChannel(name,c33);

	name = "Mu0El4DY1onZ"+suffix;
	Channel* c34 = new Channel(name);
	c34->setAttribute("L4onZ"+suffix,1.0);
	c34->addCFOChannel("fakeElectron","Mu0El3DY1onZTrack"+suffix,0.5);
	c34->addFakeObjectChannel("fakePhotonToElectron","Mu0El3DY1onZ"+suffix,0.5);
	handler->addInputChannel(name,c34);

	name = "Mu0El4DY2offZ"+suffix;
	Channel* c35 = new Channel(name);
	c35->setAttribute("L4offZ"+suffix,1.0);
	c35->addCFOChannel("fakeElectron","Mu0El3DY1offZTrack"+suffix,0.5);
	c35->addFakeObjectChannel("fakePhotonToElectron","Mu0El3DY1offZ"+suffix,0.5);
	handler->addInputChannel(name,c35);

	name = "Mu0El4DY2onZ"+suffix;
	Channel* c36 = new Channel(name);
	c36->setAttribute("L4onZ"+suffix,1.0);
	c36->addCFOChannel("fakeElectron","Mu0El3DY1onZTrack"+suffix,0.5);
	c36->addFakeObjectChannel("fakePhotonToElectron","Mu0El3DY1onZ"+suffix,0.5);
	handler->addInputChannel(name,c36);

      }
    }
  }

  handler->addFakeObjectNames("fakePhotonToMuon","nphotons");
  handler->addFakeObjectNames("fakePhotonToElectron","nphotons");
  handler->addFakeObjectNames("CFO_nonIsoTracks","nonIsoTracksPrompt_n");
  handler->addFakeObjectNames("CFO_isoTracks","isoTracksPrompt_n");
  handler->addFakeObjectNames("CFO_nonIsoElectrons","nonIsoElectronsPrompt_n");
  handler->addFakeObjectNames("CFO_nonIsoMuons","nonIsoMuonsPrompt_n");
  handler->addFakeObjectNames("CFO_nonIsoTracksElectron","nonIsoTracksPromptElectrons_n");
  handler->addCFOObjectNames("fakeMuon","CFO_nonIsoMuons","CFO_isoTracks","CFO_nonIsoTracks");
  handler->addCFOObjectNames("fakeElectron","CFO_nonIsoElectrons","CFO_isoTracks","CFO_nonIsoTracksElectron");
  //handler->addFakeObjectNames("fakeMuon","nonIsoMuons_n");
  handler->addFakeObjectNames("fakeMuonPos","posNonIsoMuons_n");
  handler->addFakeObjectNames("fakeMuonNeg","negNonIsoMuons_n");
  //handler->addFakeObjectNames("fakeElectron","nonIsoElectrons_n");
  handler->addFakeObjectNames("fakeElectronPos","posNonIsoElectrons_n");
  handler->addFakeObjectNames("fakeElectronNeg","negNonIsoElectrons_n");
  handler->addFakeRateAndError("flipElectronNeg",posToNegFlipRate,posToNegFlipErr);
  handler->addFakeRateAndError("flipElectronPos",negToPosFlipRate,negToPosFlipErr);
  handler->addFakeRateAndError("fakePhotonToElectron",0.0161,0.0019);
  handler->addFakeRateAndError("fakePhotonToMuon",0.0105,0.0012);
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void readAndWriteRdxyValues(ChannelHandler* handler, TString fname)
{
  ifstream infile(fname.Data());
  while(1){
    TString chanName;
    double rdxy,muonRatio,electronRatio;
    infile >> chanName >> rdxy >> muonRatio >> electronRatio;
    if(!infile.good())break;
    Channel* c = handler->getInputChannel(chanName);
    if(!c){
      cout<<"channel "<<chanName<<" not found"<<endl;
      continue;
    }
    //cout<<chanName<<" "<<muonRatio<<" "<<electronRatio<<endl;
    c->setFakeRateAndError("fakeMuon",muonRatio,muonRatio*0.3);
    c->setFakeRateAndError("fakeElectron",electronRatio,muonRatio*0.3);
  }

}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void addChannels2012TTV(ChannelHandler* handler)
{

  //handler->addInputChannel("sidebandTTW",new Channel("sidebandTTW"));
  //handler->addInputChannel("sidebandL3T1offZ",new Channel("sidebandL3T1offZ"));
  //handler->addInputChannel("sidebandL3T1offZMu",new Channel("sidebandL3T1offZMu"));
  //handler->addInputChannel("sidebandL3T1offZEl",new Channel("sidebandL3T1offZEl"));
  //handler->addInputChannel("sidebandL3T1onZ",new Channel("sidebandL3T1onZ"));
  //handler->addInputChannel("sidebandL3T1onZMu",new Channel("sidebandL3T1onZMu"));
  //handler->addInputChannel("sidebandL3T1onZEl",new Channel("sidebandL3T1onZEl"));
  handler->addInputChannel("L3onZsideband",new Channel("L3onZsideband"));
  handler->addInputChannel("L3onZsidebandloose",new Channel("L3onZsidebandloose"));
  handler->addInputChannel("L3onZB1sideband",new Channel("L3onZB1sideband"));

  Channel* c0 = new Channel("L3T0offZ");
  c0->setAttribute("L3T0offZ",1);
  c0->addFakeChannel("fakeMuon","sidebandTTW",1.0);
  c0->addFakeChannel("fakeElectron","sidebandTTW",1.0);
  //handler->addInputChannel("L3T0offZ",c0);

  Channel* c1 = new Channel("L3T1offZ");
  c1->setAttribute("L3T1offZ",1);
  c1->addFakeChannel("fakeTau","sidebandL3T1offZ",1.0);
  c1->addFakeChannel("fakeMuon","sidebandL3T1offZMu",1.0);
  c1->addFakeChannel("fakeElectron","sidebandL3T1offZEl",1.0);
  //handler->addInputChannel("L3T1offZ",c1);

  Channel* c2 = new Channel("L3T1onZ");
  c2->setAttribute("L3T1onZ",1);
  c2->addFakeChannel("fakeTau","sidebandL3T1onZ",1.0);
  c2->addFakeChannel("fakeMuon","sidebandL3T1onZMu",1.0);
  c2->addFakeChannel("fakeElectron","sidebandL3T1onZEl",1.0);
  //handler->addInputChannel("L3T1onZ",c2);

  Channel* c3 = new Channel("L4onZ");
  c3->setAttribute("L4onZ",1);
  c3->addFakeChannel("fakeMuon","L3onZsideband",1.0);
  c3->addFakeChannel("fakeElectron","L3onZsideband",1.0);
  handler->addInputChannel("L4onZ",c3);

  Channel* c4 = new Channel("L4onZloose");
  c4->setAttribute("L4onZloose",1);
  c4->addFakeChannel("fakeMuon","L3onZsidebandloose",1.0);
  c4->addFakeChannel("fakeElectron","L3onZsidebandloose",1.0);
  //handler->addInputChannel("L4onZloose",c4);

  Channel* c5 = new Channel("L4onZB1");
  c5->setAttribute("L4onZB1",1);
  c5->addFakeChannel("fakeMuon","L3onZB1sideband",1.0);
  c5->addFakeChannel("fakeElectron","L3onZB1sideband",1.0);
  handler->addInputChannel("L4onZB1",c5);

  handler->addFakeRateAndError("fakeTau",0.15,0.045);
  handler->addFakeRateAndError("fakeMuon",0.0155,0.0045);
  handler->addFakeRateAndError("fakeElectron",0.074,0.022);
  //handler->addFakeRateAndError("fakeMuon",0.102,0.03);
  //handler->addFakeRateAndError("fakeElectron",0.045,0.0135);
  //handler->addSumChannelAttribute("L3T0offZout","L3T0offZ",1.0);
  //handler->addSumChannelAttribute("L3T1offZout","L3T1offZ",1.0);
  //handler->addSumChannelAttribute("L3T1onZout","L3T1onZ",1.0);
  handler->addSumChannelAttribute("L4onZout","L4onZ",1.0);
  //handler->addSumChannelAttribute("L4onZlooseout","L4onZloose",1.0);
  handler->addSumChannelAttribute("L4onZB1out","L4onZB1",1.0);
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
