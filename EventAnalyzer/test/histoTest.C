void histoTest()
{
  gSystem->Load("libRutgersIAFEventAnalyzer.so");
  SignatureTH1F_TEST<double>* hd0 = new SignatureTH1F_TEST<double>("hd0","PT","goodJets","PT",100,0,100);
  hd0->addProduct("goodElectrons");

  SignatureTH1F_TEST<double>* hd1 = hd0->Clone("hd1");

  cout<<hd0->GetName()<<" "<<hd0->m_varname<<" "<<hd0->m_productnames.size()<<endl;
  cout<<hd1->GetName()<<" "<<hd1->m_varname<<" "<<hd1->m_productnames.size()<<endl;

  TClass::GetClass("SignatureTH1F_TEST<double>")->GetStreamerInfos()->ls();
  TClass::GetClass("SignatureObject")->GetStreamerInfos()->ls();
}
