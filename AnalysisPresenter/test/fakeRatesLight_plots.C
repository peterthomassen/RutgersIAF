#include <unistd.h>

#include <vector>

void fakeRatesLight_plots() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For fake rate measurement
	std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,4}:HT{0,450,15}:MET{0,100,10}:MT{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{0,25}:NISONONPROMPTINCLUSIVETRACKS7{0,25}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	varexp1 += ":NPROMPTINCLUSIVETRACKS{0,15}";
	varexp1 += ":NPROMPTNONISOINCLUSIVETRACKS7{0,15}";
	varexp1 += ":Max$(PTGOODJETS){-10,430,11,\"maxJetPT\"}";
	//std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,500,10}:MET{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{6,100,1}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	//std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,500,10}:MET{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{4,6,1}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	//std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,500,10}:MET{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{0,4,1}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	//std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,500,10}:MET{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{0,100,1}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	std::string varexp2 = varexp1 + std::string(":nTrackFakeElectrons{0,3}:nTrackFakeMuons{0,3}:nTrackFakePosElectrons{0,3}:nTrackFakePosMuons{0,3}:nTrackFakeNegElectrons{0,3}:nTrackFakeNegMuons{0,3}");
	
	// Global cuts, if desired
	TString selection1 = "NOTTRILEPTONONZ";
	selection1 += " && NLEPTONS == 3 && NGOODTAUS == 0";
	//selection1 += " && abs(OSSFCLOSEMLL - 91) < 10";
	//selection1 += " && !(MLEPTONS > 81 && MLEPTONS < 101)";
//	selection1 += " && MT < 50 && HT < 100";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler1 = new Assembler;
	init(assembler1);
	setupData(assembler1);
	//setupBackgroundMC(assembler1, false, false);
	setupBackgroundMC(assembler1);
	//setupBackgroundDD(assembler1, "noTracks");
	setupBackgroundDD(assembler1, "justPhotons"); // tracks are not a background here; taus can be skipped (NGOODTAUS == 0 in selection1)
/*	assembler1->setFakeRate("nTrackFakeMuons", "(NGOODMUONS[0]==1)*(0.01384 + -0.0003956*NPROMPTNONISOINCLUSIVETRACKS7[0]) + (NGOODMUONS[0]==3)*(0.01697 + -0.0001669*NPROMPTNONISOINCLUSIVETRACKS7[0])");
	assembler1->setFakeRate("nTrackFakeElectrons", "(NGOODELECTRONS[0]==1)*(0.0139 + 0.01388*NPROMPTNONISOINCLUSIVETRACKS7[0]) + (NGOODELECTRONS[0]==3)*(0.01751 + 0.00594*NPROMPTNONISOINCLUSIVETRACKS7[0])");
	assembler1->setFakeRate("nPhotonFakeMuons", "0");
	assembler1->setFakeRate("nPhotonFakeElectrons", "0");
	assembler1->setFakeRate("nSidebandFakeTaus", "0");
*/	setupFakeRates(assembler1);
	assembler1->setDebug(true);
	assembler1->process(varexp1, selection1);
	
	Assembler* assembler2 = new Assembler;
	init(assembler2);
	setupData(assembler2, true);
	setupBackgroundMC(assembler2, false, true, true);
	assembler2->setDebug(true);
	TString selection2 = selection1;
	selection2 += " && nPhotonFakeElectrons + nPhotonFakeMuons + nSidebandFakeTaus == 0";
	assembler2->process(varexp2, selection2);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("fakeRatesLight_plots", 0755);
	chdir("fakeRatesLight_plots");
	
	std::vector<Assembler*> assemblers;
	assemblers.push_back(assembler1);
	assemblers.push_back(assembler2);
	
	std::vector<char*> cuts;
	cuts.push_back("");
	//cuts.push_back("assembler->setRange(\"HT\", 0, 200, false);");
	//cuts.push_back("assembler->setRange(\"HT\", 200);");
	
	//char* varName = "HT";
	//char* varName = "NGOODJETS";
	//char* varName = "NBJETSCSVM";
	//char* varName = "NPROMPTNONISOTRACKS";
	//char* varName = "NPROMPTNONISOTRACKS7";
	//char* varName = "NISONONPROMPTTRACKS";
	//char* varName = "NISONONPROMPTTRACKS7";
	//char* varName = "(NPROMPTNONISOTRACKS+NGOODTRACKS)";
	//char* varName = "(NPROMPTNONISOTRACKS7+NGOODTRACKS)";
	//char* varName = "NBASICTRACKS7";
//	char* varName = "NPROMPTINCLUSIVETRACKS"; // considerung to use
	//char* varName = "NPROMPTINCLUSIVETRACKS7"; // this is what we use
	//varName = "maxJetPT";
	char* varName = "NPROMPTNONISOINCLUSIVETRACKS7";
	//char* varName = "NISONONPROMPTINCLUSIVETRACKS7";
	//char* varName = "NISOINCLUSIVETRACKS7";
	//char* varName = "NINCLUSIVETRACKS7";
	//char* varName = "(NPROMPTINCLUSIVETRACKS7-NPROMPTNONISOINCLUSIVETRACKS7)";
	
	assemblers[0]->setRange(varName);
	TH1* hTemplate = (TH1*)assemblers[0]->project(varName, false)->getHistogram("data")->Clone("mu");
	hTemplate->Reset();
	hTemplate->SetLineColor(2);
	hTemplate->SetTitle("fake rate");
	std::vector<TH1*> hV;
	gStyle->SetOptFit(1111);
	
	// Measure light lepton fake rates
	for(int nMuons = 0; nMuons < 4; ++nMuons) {
		std::string fakeName = (nMuons % 2) ? "muon" : "electron";
		for(int charge = -1; charge <= -1; charge += 2) {
			for(size_t j = 0; j < cuts.size(); ++j) {
				TH1* h = (TH1*)hTemplate->Clone(TString::Format("%s fake in %d mu region", fakeName.c_str(), nMuons));
				for(int k = 1; k <= h->GetXaxis()->GetNbins(); ++k) {
					double lo = h->GetBinLowEdge(k);
					double width = h->GetBinWidth(k);
					cout << endl;
					cout << "=== Now computing " << fakeName << " fake rate for: " << varName << " = " << lo << ".." << (lo+width) << ", cut: " << cuts[j] << endl;
					double data = 0, dataErr = 0, mc = 0, mcErr = 0, fake = 0, fakeErr = 0, fakeMC = 0, fakeMCerr = 0;
					for(size_t i = 1; i <= 2; ++i) {
						Assembler* assembler = assemblers[i-1];
						assembler->setRange();
						assembler->setRange("NGOODMUONS", nMuons, nMuons);
						//assembler->setRange("(NGOODMUONS%2)", (nMuons % 2), (nMuons % 2));
						if(i == 2) {
							assembler->setRange("nTrackFakeMuons", (nMuons % 2), (nMuons % 2));
							assembler->setRange("nTrackFakeElectrons", !(nMuons % 2), !(nMuons % 2));
						}
						
						//assembler->setRange("HT", 0, 200, false);
						//assembler->setRange("HT", 200);
						assembler->setRange("MET", 0, 50, false); // 30?
						//assembler->setRange("MET", 0, 30, false);
						//assembler->setRange("MT", 0, 50, false);
						assembler->setRange("ONZ", 1, 1);
						assembler->setRange("NBJETSCSVM", 0, 0);
						gROOT->ProcessLineFast(cuts[j]);
						cout << "bins stuff: " << lo << " " << (lo + width) << endl;
						AssemblerProjection* projection = assembler->project(varName, true);
						if(i == 1) {
							data = projection->getHistogram("data")->IntegralAndError(k, k, dataErr);
							if(data == 0) dataErr = 1;
							mc = projection->getHistogram("background")->IntegralAndError(k, k, mcErr);
							cout << assembler->project("ONZ", true)->getHistogram("data")->GetTitle() << endl;
						}
						if(i == 2) {
							fake = projection->getHistogram("data")->IntegralAndError(k, k, fakeErr);
							if(fake == 0) fakeErr = 1;
							fakeMC = projection->getHistogram("background")->IntegralAndError(k, k, fakeMCerr);
							if(fakeMC == 0) fakeMCerr = 1;
						}
					}
					//cout << "setting subtraction to 0" << endl;
					//mc = 0; mcErr = 0; fakeMC = 0; fakeMCerr = 0;
					cout << data << "/" << dataErr << endl;
					cout << mc << "/" << mcErr << endl;
					cout << fake << "/" << fakeErr << endl;
					cout << fakeMC << "/" << fakeMCerr << endl;
					if(fake == 0) continue;
					double fakeRate = (data - mc) / (fake - fakeMC);
					//double fakeRateErr = sqrt(dataErr*dataErr + pow(fakeErr*(data-mc)/fake, 2) + mcErr*mcErr) / fake;
					double fakeRateErr = sqrt( (dataErr*dataErr + mcErr*mcErr) / pow(fake - fakeMC, 2) + ( (fakeErr*fakeErr + fakeMCerr*fakeMCerr) * pow(data - mc, 2) ) / pow(fake - fakeMC, 4) );
					printf("fake rate: %.4f ± %.4f (%.0f%%)\n", fakeRate, fakeRateErr, fakeRateErr / fakeRate * 100);
					h->SetBinContent(k, fakeRate);
					h->SetBinError(k, fakeRateErr);
				}
				h->SetMinimum(-0.10); h->SetMaximum(+0.30);
				h->Draw();
				h->Fit("pol1", "", "SAME");
				//c1->SaveAs(TString::Format("%d/sum_%s_%s_%dmu.pdf", j, varName, fakeName.c_str(), nMuons));
				c1->SaveAs(TString::Format("sum_%s_%s_%dmu.pdf", varName, fakeName.c_str(), nMuons));
			}
		}
	}
/*	
	TLegend* leg = 0;
	TH1* h1 = 0;
	TH1* h2 = 0;
	
	h1 = mu;
	h1->SetMinimum(-0.20); h1->SetMaximum(+0.20);
	h2 = el;
	h1->Draw();
	h2->Draw("SAME");
	leg = new TLegend(0.1,0.8,0.3,0.9);
	leg->AddEntry(h1);
	leg->AddEntry(h2);
	leg->Draw();
	gStyle->SetOptFit(1111);
	cout << "mu" << endl;
	h1->Fit("pol0", "", "SAME");
	h1->Fit("pol1", "", "SAME");
//	h1->Fit("pol2", "", "SAME");
	cout << "el" << endl;
	h2->Fit("pol0", "", "SAME");
	h2->Fit("pol1", "", "SAME");
//	h2->Fit("pol2", "", "SAME");
	c1->SaveAs(TString::Format("sum_%s.pdf", varName));
*/	
	delete assembler1;
	delete assembler2;
}
