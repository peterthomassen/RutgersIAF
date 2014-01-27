void setupFakeRateSignatures(SignatureHandler* handler)
{
	SignatureCutPairMass* dyBelow12 = new SignatureCutPairMass("goodElectrons",0,12,true,0,2,"dybelow12cut");
	dyBelow12->addProduct("goodMuons");
	handler->addHandlerCut(new SignatureCutReversed(dyBelow12, "notDYbelow12cut"));
	
	// Cuts for fake rate signature definitions
	SignatureCutN* zeroBjets = new SignatureCutN("bJetsCSVM",0,0);
	SignatureCutN* geoneBjets = new SignatureCutN("bJetsCSVM",1,-1);
	
	SignatureCutThreshold* geThreeJets40 = new SignatureCutThreshold("goodJets", "threeJetsThreshold40");
	geThreeJets40->addThreshold(40);
	geThreeJets40->addThreshold(40);
	geThreeJets40->addThreshold(40);

	SignatureCutThresholdElectron* thresholdElectron30 = new SignatureCutThresholdElectron();
	thresholdElectron30->addThreshold(30);
	SignatureCutThresholdMuon* thresholdMuon30 = new SignatureCutThresholdMuon();
	thresholdMuon30->addThreshold(30);
	
	SignatureCutMET* met0to50 = new SignatureCutMET(0,50,"METCUT0to50");
	SignatureCutMET* met50to100 = new SignatureCutMET(50,100,"METCUT50to100");
	SignatureCutMET* met100to150 = new SignatureCutMET(100,150,"METCUT100to150");
	SignatureCutMET* metgt50 = new SignatureCutMET(50,-1,"METCUTgt50");
	SignatureCutHT* ht0to200 = new SignatureCutHT(0,200,"HTCUT0to200");
	SignatureCutHT* htgt200 = new SignatureCutHT(200,-1,"HTCUTgt200");
	SignatureCutST* stgt300 = new SignatureCutST(300,-1,"STCUTgt300");

	SignatureCutN* zeroElectrons = new SignatureCutN("goodElectrons",0,0);
	SignatureCutN* oneElectrons = new SignatureCutN("goodElectrons",1,1);
	SignatureCutN* twoElectrons = new SignatureCutN("goodElectrons",2,2);
	SignatureCutN* threeElectrons = new SignatureCutN("goodElectrons",3,3);

	SignatureCutN* zeroPosElectrons = new SignatureCutN("goodElectronsPos",0,0);
	SignatureCutN* onePosElectrons = new SignatureCutN("goodElectronsPos",1,1);
	SignatureCutN* oneOrMorePosElectrons = new SignatureCutN("goodElectronsPos",1,-1);
	SignatureCutN* twoPosElectrons = new SignatureCutN("goodElectronsPos",2,2);

	SignatureCutN* zeroNegElectrons = new SignatureCutN("goodElectronsNeg",0,0);
	SignatureCutN* oneNegElectrons = new SignatureCutN("goodElectronsNeg",1,1);
	SignatureCutN* oneOrMoreNegElectrons = new SignatureCutN("goodElectronsNeg",1,-1);
	SignatureCutN* twoNegElectrons = new SignatureCutN("goodElectronsNeg",2,2);

	SignatureCutN* zeroBasicElectrons = new SignatureCutN("basicElectrons",0,0);
	SignatureCutN* oneBasicElectrons = new SignatureCutN("basicElectrons",1,1);
	SignatureCutN* twoBasicElectrons = new SignatureCutN("basicElectrons",2,2);

	SignatureCutN* zeroBasicPosElectrons = new SignatureCutN("basicElectronsPos",0,0);
	SignatureCutN* oneBasicPosElectrons = new SignatureCutN("basicElectronsPos",1,1);
	SignatureCutN* oneOrMoreBasicPosElectrons = new SignatureCutN("basicElectronsPos",1,-1);
	SignatureCutN* twoBasicPosElectrons = new SignatureCutN("basicElectronsPos",2,2);

	SignatureCutN* zeroBasicNegElectrons = new SignatureCutN("basicElectronsNeg",0,0);
	SignatureCutN* oneBasicNegElectrons = new SignatureCutN("basicElectronsNeg",1,1);
	SignatureCutN* oneOrMoreBasicNegElectrons = new SignatureCutN("basicElectronsNeg",1,-1);
	SignatureCutN* twoBasicNegElectrons = new SignatureCutN("basicElectronsNeg",2,2);

	SignatureCutN* zeroMuons = new SignatureCutN("goodMuons",0,0);
	SignatureCutN* oneMuons = new SignatureCutN("goodMuons",1,1);
	SignatureCutN* twoMuons = new SignatureCutN("goodMuons",2,2);
	SignatureCutN* threeMuons = new SignatureCutN("goodMuons",3,3);

	SignatureCutN* zeroPosMuons = new SignatureCutN("goodMuonsPos",0,0);
	SignatureCutN* onePosMuons = new SignatureCutN("goodMuonsPos",1,1);
	SignatureCutN* oneOrMorePosMuons = new SignatureCutN("goodMuonsPos",1,-1);
	SignatureCutN* twoPosMuons = new SignatureCutN("goodMuonsPos",2,2);

	SignatureCutN* zeroNegMuons = new SignatureCutN("goodMuonsNeg",0,0);
	SignatureCutN* oneNegMuons = new SignatureCutN("goodMuonsNeg",1,1);
	SignatureCutN* oneOrMoreNegMuons = new SignatureCutN("goodMuonsNeg",1,-1);
	SignatureCutN* twoNegMuons = new SignatureCutN("goodMuonsNeg",2,2);

	SignatureCutN* zeroBasicMuons = new SignatureCutN("basicMuons",0,0);
	SignatureCutN* oneBasicMuons = new SignatureCutN("basicMuons",1,1);
	SignatureCutN* twoBasicMuons = new SignatureCutN("basicMuons",2,2);

	SignatureCutN* zeroBasicPosMuons = new SignatureCutN("basicMuonsPos",0,0);
	SignatureCutN* oneBasicPosMuons = new SignatureCutN("basicMuonsPos",1,1);
	SignatureCutN* oneOrMoreBasicPosMuons = new SignatureCutN("basicMuonsPos",1,-1);
	SignatureCutN* twoBasicPosMuons = new SignatureCutN("basicMuonsPos",2,2);

	SignatureCutN* zeroBasicNegMuons = new SignatureCutN("basicMuonsNeg",0,0);
	SignatureCutN* oneBasicNegMuons = new SignatureCutN("basicMuonsNeg",1,1);
	SignatureCutN* oneOrMoreBasicNegMuons = new SignatureCutN("basicMuonsNeg",1,-1);
	SignatureCutN* twoBasicNegMuons = new SignatureCutN("basicMuonsNeg",2,2);

	SignatureCutQ* electronQ0Cut = new SignatureCutQ("goodElectrons",-0.1,0.1,"CUTELQ0");
	SignatureCutQ* muonQ0Cut = new SignatureCutQ("goodMuons",-0.1,0.1,"CUTMUQ0");

	SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);
	SignatureCutNDYPairs* dy1offZcut = new SignatureCutNDYPairs(1,1,false);
	SignatureCutNDYPairs* dy2onZcut = new SignatureCutNDYPairs(2,2,true);

	SignatureCutN* oneOrMoreTaus = new SignatureCutN("goodTaus",1,-1);
	SignatureCutN* oneOrMoreSidebandTaus = new SignatureCutN("sidebandTaus",1,-1);

	// Signatures for Rdxy
	handler->addSignature("SeedEl2B0onZMET0to50","")
		->addCut(zeroBjets)
		->addCut(twoElectrons)
		->addCut(dy1onZcut)
		->addCut(met0to50)
	;
	
	handler->addSignature("SeedMu2B0onZMET0to50","")
		->addCut(zeroBjets)
		->addCut(twoMuons)
		->addCut(dy1onZcut)
		->addCut(met0to50)
	;

	handler->addSignature("SeedEl2B0onZMET50to100","")
		->addCut(zeroBjets)
		->addCut(twoElectrons)
		->addCut(dy1onZcut)
		->addCut(met50to100)
	;

	handler->addSignature("SeedMu2B0onZMET50to100","")
		->addCut(zeroBjets)
		->addCut(twoMuons)
		->addCut(dy1onZcut)
		->addCut(met50to100)
	;

	handler->addSignature("SeedEl3B0onZMET0to50","")
		->addCut(zeroBjets)
		->addCut(threeElectrons)
		->addCut(dy1onZcut)
		->addCut(met0to50)
	;
	
	handler->addSignature("SeedMu3B0onZMET0to50","")
		->addCut(zeroBjets)
		->addCut(threeMuons)
		->addCut(dy1onZcut)
		->addCut(met0to50)
	;

	handler->addSignature("SeedEl3B0onZMET50to10","")
		->addCut(zeroBjets)
		->addCut(threeElectrons)
		->addCut(dy1onZcut)
		->addCut(met50to100)
	;

	handler->addSignature("SeedMu3B0onZMET50to10","")
		->addCut(zeroBjets)
		->addCut(threeMuons)
		->addCut(dy1onZcut)
		->addCut(met50to100)
	;

	Signature* SeedEl2Mu1B0onZMET0to50 = new Signature("SeedEl2Mu1B0onZMET0to50","");
	SeedEl2Mu1B0onZMET0to50->addCut(zeroBjets);
	SeedEl2Mu1B0onZMET0to50->addCut(twoElectrons);
	SeedEl2Mu1B0onZMET0to50->addCut(oneBasicMuons);
	SeedEl2Mu1B0onZMET0to50->addCut(dy1onZcut);
	SeedEl2Mu1B0onZMET0to50->addCut(met0to50);
	handler->addSignature(SeedEl2Mu1B0onZMET0to50);

	Signature* SeedEl1Mu2B0onZMET0to50 = new Signature("SeedEl1Mu2B0onZMET0to50","");
	SeedEl1Mu2B0onZMET0to50->addCut(zeroBjets);
	SeedEl1Mu2B0onZMET0to50->addCut(oneBasicElectrons);
	SeedEl1Mu2B0onZMET0to50->addCut(twoMuons);
	SeedEl1Mu2B0onZMET0to50->addCut(dy1onZcut);
	SeedEl1Mu2B0onZMET0to50->addCut(met0to50);
	handler->addSignature(SeedEl1Mu2B0onZMET0to50);

	Signature* SeedEl2Mu1B0onZMET50to100 = new Signature("SeedEl2Mu1B0onZMET50to100","");
	SeedEl2Mu1B0onZMET50to100->addCut(zeroBjets);
	SeedEl2Mu1B0onZMET50to100->addCut(twoElectrons);
	SeedEl2Mu1B0onZMET50to100->addCut(oneBasicMuons);
	SeedEl2Mu1B0onZMET50to100->addCut(dy1onZcut);
	SeedEl2Mu1B0onZMET50to100->addCut(met50to100);
	handler->addSignature(SeedEl2Mu1B0onZMET50to100);

	Signature* SeedEl1Mu2B0onZMET50to100 = new Signature("SeedEl1Mu2B0onZMET50to100","");
	SeedEl1Mu2B0onZMET50to100->addCut(zeroBjets);
	SeedEl1Mu2B0onZMET50to100->addCut(oneBasicElectrons);
	SeedEl1Mu2B0onZMET50to100->addCut(twoMuons);
	SeedEl1Mu2B0onZMET50to100->addCut(dy1onZcut);
	SeedEl1Mu2B0onZMET50to100->addCut(met50to100);
	handler->addSignature(SeedEl1Mu2B0onZMET50to100);

	Signature* SeedEl1p1Mu1m1B0METgt50HTgt200 = new Signature("SeedEl1p1Mu1m1B0METgt50HTgt200","");
	SeedEl1p1Mu1m1B0METgt50HTgt200->addCut(zeroBjets);
	SeedEl1p1Mu1m1B0METgt50HTgt200->addCut(oneOrMorePosElectrons);
	SeedEl1p1Mu1m1B0METgt50HTgt200->addCut(oneOrMoreNegMuons);
	SeedEl1p1Mu1m1B0METgt50HTgt200->addCut(metgt50);
	SeedEl1p1Mu1m1B0METgt50HTgt200->addCut(htgt200);
	handler->addSignature(SeedEl1p1Mu1m1B0METgt50HTgt200);

	Signature* SeedEl1m1Mu1p1B0METgt50HTgt200 = new Signature("SeedEl1m1Mu1p1B0METgt50HTgt200","");
	SeedEl1m1Mu1p1B0METgt50HTgt200->addCut(zeroBjets);
	SeedEl1m1Mu1p1B0METgt50HTgt200->addCut(oneOrMoreNegElectrons);
	SeedEl1m1Mu1p1B0METgt50HTgt200->addCut(oneOrMorePosMuons);
	SeedEl1m1Mu1p1B0METgt50HTgt200->addCut(metgt50);
	SeedEl1m1Mu1p1B0METgt50HTgt200->addCut(htgt200);
	handler->addSignature(SeedEl1m1Mu1p1B0METgt50HTgt200);

	Signature* SeedEl1p1Mu1m1B1METgt50HTgt200 = new Signature("SeedEl1p1Mu1m1B1METgt50HTgt200","");
	SeedEl1p1Mu1m1B1METgt50HTgt200->addCut(geoneBjets);
	SeedEl1p1Mu1m1B1METgt50HTgt200->addCut(oneOrMorePosElectrons);
	SeedEl1p1Mu1m1B1METgt50HTgt200->addCut(oneOrMoreNegMuons);
	SeedEl1p1Mu1m1B1METgt50HTgt200->addCut(metgt50);
	SeedEl1p1Mu1m1B1METgt50HTgt200->addCut(htgt200);
	handler->addSignature(SeedEl1p1Mu1m1B1METgt50HTgt200);

	Signature* SeedEl1m1Mu1p1B1METgt50HTgt200 = new Signature("SeedEl1m1Mu1p1B1METgt50HTgt200","");
	SeedEl1m1Mu1p1B1METgt50HTgt200->addCut(geoneBjets);
	SeedEl1m1Mu1p1B1METgt50HTgt200->addCut(oneOrMoreNegElectrons);
	SeedEl1m1Mu1p1B1METgt50HTgt200->addCut(oneOrMorePosMuons);
	SeedEl1m1Mu1p1B1METgt50HTgt200->addCut(metgt50);
	SeedEl1m1Mu1p1B1METgt50HTgt200->addCut(htgt200);
	handler->addSignature(SeedEl1m1Mu1p1B1METgt50HTgt200);

	Signature* SeedEl1p1Mu1m1B1METgt50 = new Signature("SeedEl1p1Mu1m1B1METgt50","");
	SeedEl1p1Mu1m1B1METgt50->addCut(geoneBjets);
	SeedEl1p1Mu1m1B1METgt50->addCut(oneOrMorePosElectrons);
	SeedEl1p1Mu1m1B1METgt50->addCut(oneOrMoreNegMuons);
	SeedEl1p1Mu1m1B1METgt50->addCut(metgt50);
	handler->addSignature(SeedEl1p1Mu1m1B1METgt50);

	Signature* SeedEl1m1Mu1p1B1METgt50 = new Signature("SeedEl1m1Mu1p1B1METgt50","");
	SeedEl1m1Mu1p1B1METgt50->addCut(geoneBjets);
	SeedEl1m1Mu1p1B1METgt50->addCut(oneOrMoreNegElectrons);
	SeedEl1m1Mu1p1B1METgt50->addCut(oneOrMorePosMuons);
	SeedEl1m1Mu1p1B1METgt50->addCut(metgt50);
	handler->addSignature(SeedEl1m1Mu1p1B1METgt50);

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
	
	Signature* SeedEl2q0ONZMET0to50HT0to200 = new Signature("SeedEl2q0ONZMET0to50HT0to200", "");
	SeedEl2q0ONZMET0to50HT0to200->addCut(twoElectrons);
	SeedEl2q0ONZMET0to50HT0to200->addCut(dy1onZcut);
	SeedEl2q0ONZMET0to50HT0to200->addCut(met0to50);
	SeedEl2q0ONZMET0to50HT0to200->addCut(ht0to200);
	handler->addSignature(SeedEl2q0ONZMET0to50HT0to200);
	
	Signature* SeedMu2q0ONZMET0to50HT0to200 = new Signature("SeedMu2q0ONZMET0to50HT0to200", "");
	SeedMu2q0ONZMET0to50HT0to200->addCut(twoMuons);
	SeedMu2q0ONZMET0to50HT0to200->addCut(dy1onZcut);
	SeedMu2q0ONZMET0to50HT0to200->addCut(met0to50);
	SeedMu2q0ONZMET0to50HT0to200->addCut(ht0to200);
	handler->addSignature(SeedMu2q0ONZMET0to50HT0to200);
	
	Signature* SeedEl2q0ONZMET50to100HT0to200 = new Signature("SeedEl2q0ONZMET50to100HT0to200", "");
	SeedEl2q0ONZMET50to100HT0to200->addCut(twoElectrons);
	SeedEl2q0ONZMET50to100HT0to200->addCut(dy1onZcut);
	SeedEl2q0ONZMET50to100HT0to200->addCut(met50to100);
	SeedEl2q0ONZMET50to100HT0to200->addCut(ht0to200);
	handler->addSignature(SeedEl2q0ONZMET50to100HT0to200);
	
	Signature* SeedMu2q0ONZMET50to100HT0to200 = new Signature("SeedMu2q0ONZMET50to100HT0to200", "");
	SeedMu2q0ONZMET50to100HT0to200->addCut(twoMuons);
	SeedMu2q0ONZMET50to100HT0to200->addCut(dy1onZcut);
	SeedMu2q0ONZMET50to100HT0to200->addCut(met50to100);
	SeedMu2q0ONZMET50to100HT0to200->addCut(ht0to200);
	handler->addSignature(SeedMu2q0ONZMET50to100HT0to200);
	
	Signature* SeedEl2q0ONZMET0to50HTgt200 = new Signature("SeedEl2q0ONZMET0to50HTgt200", "");
	SeedEl2q0ONZMET0to50HTgt200->addCut(twoElectrons);
	SeedEl2q0ONZMET0to50HTgt200->addCut(dy1onZcut);
	SeedEl2q0ONZMET0to50HTgt200->addCut(met0to50);
	SeedEl2q0ONZMET0to50HTgt200->addCut(htgt200);
	handler->addSignature(SeedEl2q0ONZMET0to50HTgt200);
	
	Signature* SeedMu2q0ONZMET0to50HTgt200 = new Signature("SeedMu2q0ONZMET0to50HTgt200", "");
	SeedMu2q0ONZMET0to50HTgt200->addCut(twoMuons);
	SeedMu2q0ONZMET0to50HTgt200->addCut(dy1onZcut);
	SeedMu2q0ONZMET0to50HTgt200->addCut(met0to50);
	SeedMu2q0ONZMET0to50HTgt200->addCut(htgt200);
	handler->addSignature(SeedMu2q0ONZMET0to50HTgt200);
	
	Signature* SeedEl2q0ONZMET50to100HTgt200 = new Signature("SeedEl2q0ONZMET50to100HTgt200", "");
	SeedEl2q0ONZMET50to100HTgt200->addCut(twoElectrons);
	SeedEl2q0ONZMET50to100HTgt200->addCut(dy1onZcut);
	SeedEl2q0ONZMET50to100HTgt200->addCut(met50to100);
	SeedEl2q0ONZMET50to100HTgt200->addCut(htgt200);
	handler->addSignature(SeedEl2q0ONZMET50to100HTgt200);
	
	Signature* SeedMu2q0ONZMET50to100HTgt200 = new Signature("SeedMu2q0ONZMET50to100HTgt200", "");
	SeedMu2q0ONZMET50to100HTgt200->addCut(twoMuons);
	SeedMu2q0ONZMET50to100HTgt200->addCut(dy1onZcut);
	SeedMu2q0ONZMET50to100HTgt200->addCut(met50to100);
	SeedMu2q0ONZMET50to100HTgt200->addCut(htgt200);
	handler->addSignature(SeedMu2q0ONZMET50to100HTgt200);
	
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
	
	Signature* SeedEl2q0Tau1ONZMET50to100HT0to200 = new Signature("SeedEl2q0Tau1ONZMET50to100HT0to200", "");
	SeedEl2q0Tau1ONZMET50to100HT0to200->addCut(twoElectrons);
	SeedEl2q0Tau1ONZMET50to100HT0to200->addCut(oneOrMoreTaus); // this requires at least one isolated tau
	SeedEl2q0Tau1ONZMET50to100HT0to200->addCut(dy1onZcut);
	SeedEl2q0Tau1ONZMET50to100HT0to200->addCut(met50to100);
	SeedEl2q0Tau1ONZMET50to100HT0to200->addCut(ht0to200);
	handler->addSignature(SeedEl2q0Tau1ONZMET50to100HT0to200);
	
	Signature* SeedMu2q0Tau1ONZMET50to100HT0to200 = new Signature("SeedMu2q0Tau1ONZMET50to100HT0to200", "");
	SeedMu2q0Tau1ONZMET50to100HT0to200->addCut(twoMuons);
	SeedMu2q0Tau1ONZMET50to100HT0to200->addCut(oneOrMoreTaus);
	SeedMu2q0Tau1ONZMET50to100HT0to200->addCut(dy1onZcut);
	SeedMu2q0Tau1ONZMET50to100HT0to200->addCut(met50to100);
	SeedMu2q0Tau1ONZMET50to100HT0to200->addCut(ht0to200);
	handler->addSignature(SeedMu2q0Tau1ONZMET50to100HT0to200);
	
	Signature* SeedEl2q0Tau1ONZMET50to100HTgt200 = new Signature("SeedEl2q0Tau1ONZMET50to100HTgt200", "");
	SeedEl2q0Tau1ONZMET50to100HTgt200->addCut(twoElectrons);
	SeedEl2q0Tau1ONZMET50to100HTgt200->addCut(oneOrMoreTaus); // this requires at least one isolated tau
	SeedEl2q0Tau1ONZMET50to100HTgt200->addCut(dy1onZcut);
	SeedEl2q0Tau1ONZMET50to100HTgt200->addCut(met50to100);
	SeedEl2q0Tau1ONZMET50to100HTgt200->addCut(htgt200);
	handler->addSignature(SeedEl2q0Tau1ONZMET50to100HTgt200);
	
	Signature* SeedMu2q0Tau1ONZMET50to100HTgt200 = new Signature("SeedMu2q0Tau1ONZMET50to100HTgt200", "");
	SeedMu2q0Tau1ONZMET50to100HTgt200->addCut(twoMuons);
	SeedMu2q0Tau1ONZMET50to100HTgt200->addCut(oneOrMoreTaus);
	SeedMu2q0Tau1ONZMET50to100HTgt200->addCut(dy1onZcut);
	SeedMu2q0Tau1ONZMET50to100HTgt200->addCut(met50to100);
	SeedMu2q0Tau1ONZMET50to100HTgt200->addCut(htgt200);
	handler->addSignature(SeedMu2q0Tau1ONZMET50to100HTgt200);
	
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
	
	// Signatures for ttbar MC control region
	Signature* SeedEl1p1Mu1m1B1STgt300 = new Signature("SeedEl1p1Mu1m1B1STgt300","");
	SeedEl1p1Mu1m1B1STgt300->addCut(geoneBjets);
	SeedEl1p1Mu1m1B1STgt300->addCut(onePosElectrons);
	SeedEl1p1Mu1m1B1STgt300->addCut(oneNegMuons);
	SeedEl1p1Mu1m1B1STgt300->addCut(stgt300);
	handler->addSignature(SeedEl1p1Mu1m1B1STgt300);
	
	Signature* SeedEl1m1Mu1p1B1STgt300 = new Signature("SeedEl1m1Mu1p1B1STgt300","");
	SeedEl1m1Mu1p1B1STgt300->addCut(geoneBjets);
	SeedEl1m1Mu1p1B1STgt300->addCut(onePosElectrons);
	SeedEl1m1Mu1p1B1STgt300->addCut(oneNegMuons);
	SeedEl1m1Mu1p1B1STgt300->addCut(stgt300);
	handler->addSignature(SeedEl1m1Mu1p1B1STgt300);
	
	Signature* SeedEl1B1STgt300 = new Signature("SeedEl1B1STgt300","");
	SeedEl1B1STgt300->addCut(oneElectrons);
	SeedEl1B1STgt300->addCut(thresholdElectron30);
	SeedEl1B1STgt300->addCut(geThreeJets40);
	SeedEl1B1STgt300->addCut(geoneBjets);
	SeedEl1B1STgt300->addCut(stgt300);
	handler->addSignature(SeedEl1B1STgt300);
	
	Signature* SeedMu1B1STgt300 = new Signature("SeedMu1B1STgt300","");
	SeedMu1B1STgt300->addCut(oneMuons);
	SeedMu1B1STgt300->addCut(thresholdMuon30);
	SeedMu1B1STgt300->addCut(geThreeJets40);
	SeedMu1B1STgt300->addCut(geoneBjets);
	SeedMu1B1STgt300->addCut(stgt300);
	handler->addSignature(SeedMu1B1STgt300);

	Signature* SeedEl1p1Mu1m1B1 = new Signature("SeedEl1p1Mu1m1B1","");
	SeedEl1p1Mu1m1B1->addCut(geoneBjets);
	SeedEl1p1Mu1m1B1->addCut(onePosElectrons);
	SeedEl1p1Mu1m1B1->addCut(oneNegMuons);
	handler->addSignature(SeedEl1p1Mu1m1B1);
	
	Signature* SeedEl1m1Mu1p1B1 = new Signature("SeedEl1m1Mu1p1B1","");
	SeedEl1m1Mu1p1B1->addCut(geoneBjets);
	SeedEl1m1Mu1p1B1->addCut(onePosElectrons);
	SeedEl1m1Mu1p1B1->addCut(oneNegMuons);
	handler->addSignature(SeedEl1m1Mu1p1B1);
	
	Signature* SeedEl1B1 = new Signature("SeedEl1B1","");
	SeedEl1B1->addCut(oneElectrons);
	SeedEl1B1->addCut(thresholdElectron30);
	SeedEl1B1->addCut(geThreeJets40);
	SeedEl1B1->addCut(geoneBjets);
	handler->addSignature(SeedEl1B1);
	
	Signature* SeedMu1B1 = new Signature("SeedMu1B1","");
	SeedMu1B1->addCut(oneMuons);
	SeedMu1B1->addCut(thresholdMuon30);
	SeedMu1B1->addCut(geThreeJets40);
	SeedMu1B1->addCut(geoneBjets);
	handler->addSignature(SeedMu1B1);

	// Signatures for the WZ MC control region
	SignatureCutN* threeLeptons = new SignatureCutN("goodElectrons", 3, 3);
	threeLeptons->addProduct("goodMuons");
	
	SignatureCutN* fourLeptons = new SignatureCutN("goodElectrons", 4, 4);
	fourLeptons->addProduct("goodMuons");
	
	SignatureCutMT* mt0to50 = new SignatureCutMT(0,50,"MTCUT0to50");
	SignatureTH1F_MT* histMT = new SignatureTH1F_MT("MT");
	SignatureTH2F_METvsMT* histMETvsMT = new SignatureTH2F_METvsMT("METvsMT");
	
	handler->addSignature("SeedL3DYz1B0MET100to150HT0to200", "")
		->addCut(threeLeptons)
		->addCut(dy1onZcut)
		->addCut(met100to150)
		->addCut(ht0to200)
		->addCut(zeroBjets)
	;
	handler->addHistogram(histMT, "SeedL3DYz1B0MET100to150HT0to200");
	
	handler->addSignature("SeedL3DYz1B0MT0to50HT0to200", "")
		->addCut(threeLeptons)
		->addCut(dy1onZcut)
		->addCut(mt0to50)
		->addCut(ht0to200)
		->addCut(zeroBjets)
	;
	
	handler->addSignature("SeedL3DYz1B0HT0to200", "")
		->addCut(threeLeptons)
		->addCut(dy1onZcut)
		->addCut(ht0to200)
		->addCut(zeroBjets)
	;
	handler->addHistogram(histMETvsMT, "SeedL3DYz1B0HT0to200");
	
	// Signatures for the ZZ MC control region
	SignatureTH2F_METvsAllMass* histMETvsAllMassLepton = new SignatureTH2F_METvsAllMass("METvsAllMassLepton");
	histMETvsAllMassLepton->addProduct("goodElectrons");
	histMETvsAllMassLepton->addProduct("goodMuons");
	
	handler->addSignature("SeedL4DYz1B0MET0to50HT0to200", "")
		->addCut(fourLeptons)
		->addCut(dy1onZcut)
		->addCut(met0to50)
		->addCut(ht0to200)
		->addCut(zeroBjets)
	;
	handler->addHistogram(histMETvsAllMassLepton, "SeedL4DYz1B0MET0to50HT0to200");
	
	handler->addSignature("SeedL4DYz2B0MET0to50HT0to200", "")
		->addCut(fourLeptons)
		->addCut(dy2onZcut)
		->addCut(met0to50)
		->addCut(ht0to200)
		->addCut(zeroBjets)
	;
	handler->addHistogram(histMETvsAllMassLepton, "SeedL4DYz2B0MET0to50HT0to200");

	// Histograms for Rdxy
	SignatureTH1F_N* n_electronsNINP = new SignatureTH1F_N("n_electronsNINP","electronsNINP");
	SignatureTH1F_N* n_electronsINP = new SignatureTH1F_N("n_electronsINP","electronsINP");
	SignatureTH1F_N* n_electronsNIP = new SignatureTH1F_N("n_electronsNIP","electronsNIP");
	SignatureTH1F_N* n_electronsIP = new SignatureTH1F_N("n_electronsIP","electronsIP");
	SignatureTH2F_RelIsoVsDxy* risovdxy_electrons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_electrons","basicElectrons");
	SignatureTH2F_RelIsoVsDxy* risovdxy_poselectrons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_posElectrons","basicElectronsPos");
	SignatureTH2F_RelIsoVsDxy* risovdxy_negelectrons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_negElectrons","basicElectronsNeg");

	handler->addHistogram(n_electronsNINP);
	handler->addHistogram(n_electronsINP);
	handler->addHistogram(n_electronsNIP);
	handler->addHistogram(n_electronsIP);
	handler->addHistogram(risovdxy_electrons);
	handler->addHistogram(risovdxy_poselectrons);
	handler->addHistogram(risovdxy_negelectrons);

	SignatureTH1F_N* n_muonsNINP = new SignatureTH1F_N("n_muonsNINP","muonsNINP");
	SignatureTH1F_N* n_muonsINP = new SignatureTH1F_N("n_muonsINP","muonsINP");
	SignatureTH1F_N* n_muonsNIP = new SignatureTH1F_N("n_muonsNIP","muonsNIP");
	SignatureTH1F_N* n_muonsIP = new SignatureTH1F_N("n_muonsIP","muonsIP");
	SignatureTH2F_RelIsoVsDxy* risovdxy_muons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_muons","basicMuons");
	SignatureTH2F_RelIsoVsDxy* risovdxy_posmuons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_posMuons","basicMuonsPos");
	SignatureTH2F_RelIsoVsDxy* risovdxy_negmuons = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_negMuons","basicMuonsNeg");

	handler->addHistogram(n_muonsNINP);
	handler->addHistogram(n_muonsINP);
	handler->addHistogram(n_muonsNIP);
	handler->addHistogram(n_muonsIP);
	handler->addHistogram(risovdxy_muons);
	handler->addHistogram(risovdxy_posmuons);
	handler->addHistogram(risovdxy_negmuons);

	SignatureTH1F_N* n_tracksNINP = new SignatureTH1F_N("n_tracksNINP","tracksNINP");
	SignatureTH1F_N* n_tracksINP = new SignatureTH1F_N("n_tracksINP","tracksINP");
	SignatureTH1F_N* n_tracksNIP = new SignatureTH1F_N("n_tracksNIP","tracksNIP");
	SignatureTH1F_N* n_tracksIP = new SignatureTH1F_N("n_tracksIP","tracksIP");
	SignatureTH2F_RelIsoVsDxy* risovdxy_tracks = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_tracks","basicTracks");
	SignatureTH2F_RelIsoVsDxy* risovdxy_postracks = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_posTracks","basicTracksPos");
	SignatureTH2F_RelIsoVsDxy* risovdxy_negtracks = new SignatureTH2F_RelIsoVsDxy("RelIsoVsDxy_negTracks","basicTracksNeg");

	handler->addHistogram(n_tracksNINP);
	handler->addHistogram(n_tracksINP);
	handler->addHistogram(n_tracksNIP);
	handler->addHistogram(n_tracksIP);
	handler->addHistogram(risovdxy_tracks);
	handler->addHistogram(risovdxy_postracks);
	handler->addHistogram(risovdxy_negtracks);

	// Histograms for Ftfsb
	std::vector<int> sumBins;
	sumBins.push_back(0);
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
		
/*		name = TString::Format("tauIsoLead%dto%d", edgeLow, edgeHigh);
		dummy = new SignatureTH1F_TauIso(name.Data(), "basicTaus", edgeLow, edgeHigh, "LEAD");
		handler->addHistogram(dummy, "Seed");
*/		
		name = TString::Format("tauIsoHT%dto%d", edgeLow, edgeHigh);
		dummy = new SignatureTH1F_TauIso(name.Data(), "basicTaus", edgeLow, edgeHigh, "HT");
		handler->addHistogram(dummy, "Seed");
	}
	name = TString::Format("tauIsoHT%dto%d", 180, 200);
	dummy = new SignatureTH1F_TauIso(name.Data(), "basicTaus", 180, 200, "HT");
	handler->addHistogram(dummy, "Seed");
	name = TString::Format("tauIsoHT%dto%d", 200, 220);
	dummy = new SignatureTH1F_TauIso(name.Data(), "basicTaus", 200, 220, "HT");
	handler->addHistogram(dummy, "Seed");

	name = "tauIso";
	dummy = new SignatureTH1F_TauIso(name.Data(), "basicTaus", -1, -1, "SUM");
	handler->addHistogram(dummy);
	name = "goodTauIso";
	dummy = new SignatureTH1F_TauIso(name.Data(), "goodTaus", -1, -1, "SUM");
	handler->addHistogram(dummy);
	
	name = "HTvsWSumPt";
	SignatureTH2F_HTvsWSumPt* dummy2 = new SignatureTH2F_HTvsWSumPt(name.Data());
	handler->addHistogram(dummy2);
	
	name = "TauIsovsHT";
	SignatureTH2F_TauIsovsHT* dummy3 = new SignatureTH2F_TauIsovsHT(name.Data(), "basicTaus");
	handler->addHistogram(dummy3, "Seed");
	
	name = "TauIsovsWSumPt";
	SignatureTH2F_TauIsovsWSumPt* dummy4 = new SignatureTH2F_TauIsovsWSumPt(name.Data(), "basicTaus");
	handler->addHistogram(dummy4);
}
