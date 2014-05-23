void exampleMacro(TString ofname = "test.root") {
	gSystem->Load("libRutgersIAF2012AnalysisPresenter.so");
	//gROOT->ProcessLine(".L helperChannelHandler.C");
	
	Assembler* assembler = new Assembler(ofname);
	assembler->addData(new PhysicsContribution("/cms/thomassen/2014/Analysis/data/histograms/20140522_data.3L.root", 19500));
	
	std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,200,4}";
	
	std::string selection = "!(NLEPTONS == 3 && MLEPTONS > 76 && MLEPTONS < 106)";
	selection += " && nFakeMuons + nFakeElectrons == 0";
//	selection += " && (LOWDYOSMINMLL > 12)";
	
	THnBase* hn = assembler->process(varexp, selection);
	cout << hn->GetEntries() << endl;
	
	assembler->writeTablePT(hn);
	
	delete hn;
}
