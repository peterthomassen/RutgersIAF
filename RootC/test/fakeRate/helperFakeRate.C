/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void setupFakeRateSignatures(SignatureHandler* handler)
{
	SignatureCutPairMass* dyBelow12 = new SignatureCutPairMass("goodElectrons",0,12,true,0,2,"dybelow12cut");
	dyBelow12->addProduct("goodMuons");
	handler->addHandlerCut(new SignatureCutReversed(dyBelow12, "notDYbelow12cut"));
	
	// Cuts for fake rate signature definitions
	SignatureCutN* zeroBjets = new SignatureCutN("bJetsCSVM",0,0);
	SignatureCutN* geoneBjets = new SignatureCutN("bJetsCSVM",1,-1);
	
	SignatureCutMET* met0to50 = new SignatureCutMET(0,50,"METCUT0to50");
	SignatureCutMET* met50to100 = new SignatureCutMET(50,100,"METCUT50to100");
	SignatureCutMET* metgt50 = new SignatureCutMET(50,-1,"METCUTgt50");
	SignatureCutHT* ht0to200 = new SignatureCutHT(0,200,"HTCUT0to200");
	SignatureCutHT* htgt200 = new SignatureCutHT(200,-1,"HTCUTgt200");

	SignatureCutN* zeroElectrons = new SignatureCutN("goodElectrons",0,0);
	SignatureCutN* oneElectrons = new SignatureCutN("goodElectrons",1,1);
	SignatureCutN* twoElectrons = new SignatureCutN("goodElectrons",2,2);

	SignatureCutN* zeroPosElectrons = new SignatureCutN("goodElectronsPos",0,0);
	SignatureCutN* onePosElectrons = new SignatureCutN("goodElectronsPos",1,1);
	SignatureCutN* twoPosElectrons = new SignatureCutN("goodElectronsPos",2,2);

	SignatureCutN* zeroNegElectrons = new SignatureCutN("goodElectronsNeg",0,0);
	SignatureCutN* oneNegElectrons = new SignatureCutN("goodElectronsNeg",1,1);
	SignatureCutN* twoNegElectrons = new SignatureCutN("goodElectronsNeg",2,2);

	SignatureCutN* zeroBasicElectrons = new SignatureCutN("basicElectrons",0,0);
	SignatureCutN* oneBasicElectrons = new SignatureCutN("basicElectrons",1,1);
	SignatureCutN* twoBasicElectrons = new SignatureCutN("basicElectrons",2,2);

	SignatureCutN* zeroBasicPosElectrons = new SignatureCutN("basicElectronsPos",0,0);
	SignatureCutN* oneBasicPosElectrons = new SignatureCutN("basicElectronsPos",1,1);
	SignatureCutN* twoBasicPosElectrons = new SignatureCutN("basicElectronsPos",2,2);

	SignatureCutN* zeroBasicNegElectrons = new SignatureCutN("basicElectronsNeg",0,0);
	SignatureCutN* oneBasicNegElectrons = new SignatureCutN("basicElectronsNeg",1,1);
	SignatureCutN* twoBasicNegElectrons = new SignatureCutN("basicElectronsNeg",2,2);

	SignatureCutN* zeroMuons = new SignatureCutN("goodMuons",0,0);
	SignatureCutN* oneMuons = new SignatureCutN("goodMuons",1,1);
	SignatureCutN* twoMuons = new SignatureCutN("goodMuons",2,2);

	SignatureCutN* zeroPosMuons = new SignatureCutN("goodMuonsPos",0,0);
	SignatureCutN* onePosMuons = new SignatureCutN("goodMuonsPos",1,1);
	SignatureCutN* twoPosMuons = new SignatureCutN("goodMuonsPos",2,2);

	SignatureCutN* zeroNegMuons = new SignatureCutN("goodMuonsNeg",0,0);
	SignatureCutN* oneNegMuons = new SignatureCutN("goodMuonsNeg",1,1);
	SignatureCutN* twoNegMuons = new SignatureCutN("goodMuonsNeg",2,2);

	SignatureCutN* zeroBasicMuons = new SignatureCutN("basicMuons",0,0);
	SignatureCutN* oneBasicMuons = new SignatureCutN("basicMuons",1,1);
	SignatureCutN* twoBasicMuons = new SignatureCutN("basicMuons",2,2);

	SignatureCutN* zeroBasicPosMuons = new SignatureCutN("basicMuonsPos",0,0);
	SignatureCutN* oneBasicPosMuons = new SignatureCutN("basicMuonsPos",1,1);
	SignatureCutN* twoBasicPosMuons = new SignatureCutN("basicMuonsPos",2,2);

	SignatureCutN* zeroBasicNegMuons = new SignatureCutN("basicMuonsNeg",0,0);
	SignatureCutN* oneBasicNegMuons = new SignatureCutN("basicMuonsNeg",1,1);
	SignatureCutN* twoBasicNegMuons = new SignatureCutN("basicMuonsNeg",2,2);

	SignatureCutQ* electronQ0Cut = new SignatureCutQ("goodElectrons",-0.1,0.1,"CUTELQ0");
	SignatureCutQ* muonQ0Cut = new SignatureCutQ("goodMuons",-0.1,0.1,"CUTMUQ0");

	SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);
	SignatureCutNDYPairs* dy1offZcut = new SignatureCutNDYPairs(1,1,false);

	SignatureCutN* oneOrMoreTaus = new SignatureCutN("goodTaus",1,-1);
	SignatureCutN* oneOrMoreSidebandTaus = new SignatureCutN("sidebandTaus",1,-1);

	// Signatures for Rdxy
	Signature* El2Mu1B0onZMET0to50 = new Signature("El2Mu1B0onZMET0to50","");
	El2Mu1B0onZMET0to50->addCut(zeroBjets);
	El2Mu1B0onZMET0to50->addCut(twoElectrons);
	El2Mu1B0onZMET0to50->addCut(oneBasicMuons);
	El2Mu1B0onZMET0to50->addCut(dy1onZcut);
	El2Mu1B0onZMET0to50->addCut(met0to50);
	handler->addSignature(El2Mu1B0onZMET0to50);

	Signature* El1Mu2B0onZMET0to50 = new Signature("El1Mu2B0onZMET0to50","");
	El1Mu2B0onZMET0to50->addCut(zeroBjets);
	El1Mu2B0onZMET0to50->addCut(oneBasicElectrons);
	El1Mu2B0onZMET0to50->addCut(twoMuons);
	El1Mu2B0onZMET0to50->addCut(dy1onZcut);
	El1Mu2B0onZMET0to50->addCut(met0to50);
	handler->addSignature(El1Mu2B0onZMET0to50);

	Signature* Elp1Mun1B0METgt50HTgt200 = new Signature("Elp1Mun1B0METgt50HTgt200","");
	Elp1Mun1B0METgt50HTgt200->addCut(zeroBjets);
	Elp1Mun1B0METgt50HTgt200->addCut(onePosElectrons);
	Elp1Mun1B0METgt50HTgt200->addCut(oneNegMuons);
	Elp1Mun1B0METgt50HTgt200->addCut(metgt50);
	Elp1Mun1B0METgt50HTgt200->addCut(htgt200);
	handler->addSignature(Elp1Mun1B0METgt50HTgt200);

	Signature* Eln1Mup1B0METgt50HTgt200 = new Signature("Eln1Mup1B0METgt50HTgt200","");
	Eln1Mup1B0METgt50HTgt200->addCut(zeroBjets);
	Eln1Mup1B0METgt50HTgt200->addCut(oneNegElectrons);
	Eln1Mup1B0METgt50HTgt200->addCut(onePosMuons);
	Eln1Mup1B0METgt50HTgt200->addCut(metgt50);
	Eln1Mup1B0METgt50HTgt200->addCut(htgt200);
	handler->addSignature(Eln1Mup1B0METgt50HTgt200);

	Signature* Elp1Mun1B1METgt50HTgt200 = new Signature("Elp1Mun1B1METgt50HTgt200","");
	Elp1Mun1B1METgt50HTgt200->addCut(geoneBjets);
	Elp1Mun1B1METgt50HTgt200->addCut(onePosElectrons);
	Elp1Mun1B1METgt50HTgt200->addCut(oneNegMuons);
	Elp1Mun1B1METgt50HTgt200->addCut(metgt50);
	Elp1Mun1B1METgt50HTgt200->addCut(htgt200);
	handler->addSignature(Elp1Mun1B1METgt50HTgt200);

	Signature* Eln1Mup1B1METgt50HTgt200 = new Signature("Eln1Mup1B1METgt50HTgt200","");
	Eln1Mup1B1METgt50HTgt200->addCut(geoneBjets);
	Eln1Mup1B1METgt50HTgt200->addCut(oneNegElectrons);
	Eln1Mup1B1METgt50HTgt200->addCut(onePosMuons);
	Eln1Mup1B1METgt50HTgt200->addCut(metgt50);
	Eln1Mup1B1METgt50HTgt200->addCut(htgt200);
	handler->addSignature(Eln1Mup1B1METgt50HTgt200);

	// Signatures for FtFsb
	// -- Here, we calculate the FtFsb plot
	Signature* SeedEl2q0ONZMET0to50 = new Signature("SeedEl2q0ONZMET0to50", "");
	SeedEl2q0ONZMET0to50->addCut(twoElectrons);
	SeedEl2q0ONZMET0to50->addCut(dy1onZcut);
	SeedEl2q0ONZMET0to50->addCut(met0to50);
	handler->addSignature(SeedEl2q0ONZMET0to50);
	
	Signature* SeedMu2q0ONZMET0to50 = new Signature("SeedMu2q0ONZMET0to50", "");
	SeedMu2q0ONZMET0to50->addCut(twoMuons);
	SeedMu2q0ONZMET0to50->addCut(dy1onZcut);
	SeedMu2q0ONZMET0to50->addCut(met0to50);
	handler->addSignature(SeedMu2q0ONZMET0to50);
	
	Signature* SeedEl2q0ONZMET50to100 = new Signature("SeedEl2q0ONZMET50to100", "");
	SeedEl2q0ONZMET50to100->addCut(twoElectrons);
	SeedEl2q0ONZMET50to100->addCut(dy1onZcut);
	SeedEl2q0ONZMET50to100->addCut(met50to100);
	handler->addSignature(SeedEl2q0ONZMET50to100);
	
	Signature* SeedMu2q0ONZMET50to100 = new Signature("SeedMu2q0ONZMET50to100", "");
	SeedMu2q0ONZMET50to100->addCut(twoMuons);
	SeedMu2q0ONZMET50to100->addCut(dy1onZcut);
	SeedMu2q0ONZMET50to100->addCut(met50to100);
	handler->addSignature(SeedMu2q0ONZMET50to100);
	
	// Here, we calculate Fsb, and we look up the corresponding fT from above
	Signature* SeedEl2q0Tau1ONZMET50to100 = new Signature("SeedEl2q0Tau1ONZMET50to100", "");
	SeedEl2q0Tau1ONZMET50to100->addCut(twoElectrons);
	SeedEl2q0Tau1ONZMET50to100->addCut(oneOrMoreTaus); // this requires at least one isolated tau
	SeedEl2q0Tau1ONZMET50to100->addCut(dy1onZcut);
	SeedEl2q0Tau1ONZMET50to100->addCut(met50to100);
	handler->addSignature(SeedEl2q0Tau1ONZMET50to100);
	
	Signature* SeedMu2q0Tau1ONZMET50to100 = new Signature("SeedMu2q0Tau1ONZMET50to100", "");
	SeedMu2q0Tau1ONZMET50to100->addCut(twoMuons);
	SeedMu2q0Tau1ONZMET50to100->addCut(oneOrMoreTaus);
	SeedMu2q0Tau1ONZMET50to100->addCut(dy1onZcut);
	SeedMu2q0Tau1ONZMET50to100->addCut(met50to100);
	handler->addSignature(SeedMu2q0Tau1ONZMET50to100);
	
	// Here, we apply fT (in the sideband only)
	Signature* SeedEl2q0SidebandTau1ONZMET50to100 = new Signature("SeedEl2q0SidebandTau1ONZMET50to100", "");
	SeedEl2q0SidebandTau1ONZMET50to100->addCut(twoElectrons);
	SeedEl2q0SidebandTau1ONZMET50to100->addCut(oneOrMoreSidebandTaus);
	SeedEl2q0SidebandTau1ONZMET50to100->addCut(dy1onZcut);
	SeedEl2q0SidebandTau1ONZMET50to100->addCut(met50to100);
	handler->addSignature(SeedEl2q0SidebandTau1ONZMET50to100);
	
	Signature* SeedMu2q0SidebandTau1ONZMET50to100 = new Signature("SeedMu2q0SidebandTau1ONZMET50to100", "");
	SeedMu2q0SidebandTau1ONZMET50to100->addCut(twoMuons);
	SeedMu2q0SidebandTau1ONZMET50to100->addCut(oneOrMoreSidebandTaus);
	SeedMu2q0SidebandTau1ONZMET50to100->addCut(dy1onZcut);
	SeedMu2q0SidebandTau1ONZMET50to100->addCut(met50to100);
	handler->addSignature(SeedMu2q0SidebandTau1ONZMET50to100);
	
	// Histograms for Rdxy
	SignatureTH1F_N* n_electronsNINP = new SignatureTH1F_N("n_electronsNINP","electronsNINP");
	SignatureTH1F_N* n_electronsINP = new SignatureTH1F_N("n_electronsINP","electronsINP");
	SignatureTH1F_N* n_electronsNIP = new SignatureTH1F_N("n_electronsNIP","electronsNIP");
	SignatureTH2F_RelIsoVsDxy* risovdxy_electrons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_electrons","basicElectrons");
	SignatureTH2F_RelIsoVsDxy* risovdxy_poselectrons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_posElectrons","basicElectronsPos");
	SignatureTH2F_RelIsoVsDxy* risovdxy_negelectrons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_negElectrons","basicElectronsNeg");

	handler->addHistogram(n_electronsNINP);
	handler->addHistogram(n_electronsINP);
	handler->addHistogram(n_electronsNIP);
	handler->addHistogram(risovdxy_electrons);
	handler->addHistogram(risovdxy_poselectrons);
	handler->addHistogram(risovdxy_negelectrons);

	SignatureTH1F_N* n_muonsNINP = new SignatureTH1F_N("n_muonsNINP","muonsNINP");
	SignatureTH1F_N* n_muonsINP = new SignatureTH1F_N("n_muonsINP","muonsINP");
	SignatureTH1F_N* n_muonsNIP = new SignatureTH1F_N("n_muonsNIP","muonsNIP");
	SignatureTH2F_RelIsoVsDxy* risovdxy_muons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_muons","basicMuons");
	SignatureTH2F_RelIsoVsDxy* risovdxy_posmuons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_posMuons","basicMuonsPos");
	SignatureTH2F_RelIsoVsDxy* risovdxy_negmuons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_negMuons","basicMuonsNeg");

	handler->addHistogram(n_muonsNINP);
	handler->addHistogram(n_muonsINP);
	handler->addHistogram(n_muonsNIP);
	handler->addHistogram(risovdxy_muons);
	handler->addHistogram(risovdxy_posmuons);
	handler->addHistogram(risovdxy_negmuons);

	SignatureTH1F_N* n_tracksNINP = new SignatureTH1F_N("n_tracksNINP","tracksNINP");
	SignatureTH1F_N* n_tracksINP = new SignatureTH1F_N("n_tracksINP","tracksINP");
	SignatureTH1F_N* n_tracksNIP = new SignatureTH1F_N("n_tracksNIP","tracksNIP");
	SignatureTH2F_RelIsoVsDxy* risovdxy_tracks = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_tracks","basicTracks");
	SignatureTH2F_RelIsoVsDxy* risovdxy_postracks = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_posTracks","basicTracksPos");
	SignatureTH2F_RelIsoVsDxy* risovdxy_negtracks = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_negTracks","basicTracksNeg");

	handler->addHistogram(n_tracksNINP);
	handler->addHistogram(n_tracksINP);
	handler->addHistogram(n_tracksNIP);
	handler->addHistogram(risovdxy_tracks);
	handler->addHistogram(risovdxy_postracks);
	handler->addHistogram(risovdxy_negtracks);

	// Histograms for Ftfsb
	std::vector<int> sumBins;
	sumBins.push_back(40);
	sumBins.push_back(60);
	sumBins.push_back(80);
	sumBins.push_back(100);
	sumBins.push_back(140);
	sumBins.push_back(180);
	sumBins.push_back(220);
	sumBins.push_back(400);
	
	TString name = "";
	SignatureTH1F_TauIso* dummy = 0;
	for(int i = 0; i < sumBins.size() - 1; ++i) {
		int edgeLow = sumBins[i];
		int edgeHigh = sumBins[i + 1];
		
		name = TString::Format("tauIsoSum%dto%d", edgeLow, edgeHigh);
		dummy = new SignatureTH1F_TauIso(name.Data(), "basicTaus", edgeLow, edgeHigh, "SUM");
		handler->addHistogram(dummy);
		
		name = TString::Format("tauIsoLead%dto%d", edgeLow, edgeHigh);
		dummy = new SignatureTH1F_TauIso(name.Data(), "basicTaus", edgeLow, edgeHigh, "LEAD");
		handler->addHistogram(dummy);
	}
	name = "tauIso";
	dummy = new SignatureTH1F_TauIso(name.Data(), "basicTaus", -1, -1, "SUM");
	handler->addHistogram(dummy);
	name = "goodTauIso";
	dummy = new SignatureTH1F_TauIso(name.Data(), "goodTaus", -1, -1, "SUM");
	handler->addHistogram(dummy);
}
