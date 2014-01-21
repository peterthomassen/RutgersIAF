void addTutorialSignatures(SignatureHandler* handler)
{

  //create some signature Cuts
  SignatureCutN* twoGoodElectrons = new SignatureCutN("goodElectrons",2,2);
  SignatureCutN* threeGoodLeptonCut = new SignatureCutN("goodElectrons",3,3);
  threeGoodLeptonCut->addProduct("goodMuons");

  SignatureCutQ* positiveChargeCut = new SignatureCutQ("goodElectrons",0,1000);
  positiveChargeCut->addProduct("goodMuons");

  SignatureCutQ* negativeChargeCut = new SignatureCutQ("goodElectrons",-1000,0);
  negativeChargeCut->addProduct("goodMuons");

  SignatureCutQ* zeroChargeCut = new SignatureCutQ("goodElectrons",-0.1,0.1);

  SignatureCutST* stCut0to300 = new SignatureCutST(0,300);
  SignatureCutST* stCut300to600 = new SignatureCutST(300,600);
  SignatureCutST* stCut600to1000 = new SignatureCutST(600,1000);

  //create some signatures
  Signature* El2q0ST0to300 = new Signature("El2q0ST0to300","");
  El2q0ST0to300->addCut(stCut0to300)
    ->addCut(twoGoodElectrons)
    ->addCut(zeroChargeCut)
    ;

  Signature* L3posST0to300 = new Signature("L3posST0to300","");
  L3posST0to300->addCut(stCut0to300)
    ->addCut(threeGoodLeptonCut)
    ->addCut(positiveChargeCut)
    ;

  Signature* L3negST600to1000 = new Signature("L3negST600to1000","");
  L3negST600to1000->addCut(stCut600to1000)
    ->addCut(threeGoodLeptonCut)
    ->addCut(positiveChargeCut)
    ;

  //add the signatures to the handler
  handler->addSignature(El2q0ST0to300);
  handler->addSignature(L3posST0to300);
  handler->addSignature(L3negST600to1000);

}

void addTutorialHistograms(SignatureHandler* handler)
{
  SignatureTH1F_M* massHisto = new SignatureTH1F_M("MLL","goodElectrons");
  handler->addHistogram(massHisto);
}
