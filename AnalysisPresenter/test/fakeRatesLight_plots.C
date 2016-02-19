#include <sys/stat.h>
#include <unistd.h>

#include <vector>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter.C"

void fakeRatesLight_plots() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For fake rate measurement
	std::string varexp1 = "(NGOODELECTRONS[0]%2){0,2}:(NGOODMUONS[0]%2){0,2}:NGOODMUONS[0]{0,4}:NGOODELECTRONS[0]{0,4}:NOSSF[0]{0,2}:ONZ{0,2}:NBJETSCSVM[0]{0,4}:HT[0]{0,450,45}:ST[0]{0,600,60}:MET[0]{0,100,10}:MT[0]{0,100,10}:NGOODJETS[0]{0,10}:NPROMPTINCLUSIVETRACKS7[0]{0,25}:NPROMPTNONISOTRACKS[0]{0,15}:NPROMPTNONISOTRACKS7[0]{0,15}:NISONONPROMPTTRACKS[0]{0,15}:NISONONPROMPTTRACKS7[0]{0,15}";
	varexp1 += ":NPROMPTINCLUSIVETRACKS[0]{0,15}";
	varexp1 += ":NPROMPTNONISOINCLUSIVETRACKS7[0]{0,15,1}";
	varexp1 += ":Max$(PTGOODJETS){-10,430,11,\"maxJetPT\"}";
	
	varexp1 += ":NISONONPROMPTINCLUSIVETRACKS7[0]{0,15}";
	//varexp1 += ":Max$(BDISCCSVGOODJETS){0,1,20,\"maxBDISCCSVGOODJETS\"}";
	
	//std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,500,10}:MET{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{6,100,1}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	//std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,500,10}:MET{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{4,6,1}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	//std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,500,10}:MET{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{0,4,1}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	//std::string varexp1 = "(NGOODELECTRONS%2){0,1}:(NGOODMUONS%2){0,1}:NGOODMUONS{0,3}:NGOODELECTRONS{0,3}:NPOSGOODMUONS{0,3}:NPOSGOODELECTRONS{0,3}:NNEGGOODMUONS{0,3}:NNEGGOODELECTRONS{0,3}:NOSSF{0,2}:ONZ{0,1}:NBJETSCSVM{0,2}:HT{0,500,10}:MET{0,100,10}:NGOODJETS{0,10}:NPROMPTINCLUSIVETRACKS7{0,100,1}:NPROMPTNONISOTRACKS{0,15}:NPROMPTNONISOTRACKS7{0,15}:NISONONPROMPTTRACKS{0,15}:NISONONPROMPTTRACKS7{0,15}";
	std::string varexp2 = varexp1 + std::string(":nTrackFakeElectrons[0]{0,3}:nTrackFakeMuons[0]{0,3}:nTrackFakePosElectrons[0]{0,3}:nTrackFakePosMuons[0]{0,3}:nTrackFakeNegElectrons[0]{0,3}:nTrackFakeNegMuons[0]{0,3}");
	
	// Global cuts, if desired
	TString selection1 = "NLIGHTLEPTONS[0] == 3 && PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10"; // && NGOODTAUS[0] == 0";
	//selection1 += " && abs(OSSFCLOSEMLL - 91) < 10";
	//selection1 += " && !(MLEPTONS > 81 && MLEPTONS < 101)";
//	selection1 += " && MT < 50 && HT < 100";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler1 = new Assembler;
	init(assembler1);
	setupData(assembler1);
	setupBackgroundMC(assembler1);
	//setupBackgroundMC(assembler1);
	//setupBackgroundDD(assembler1, "noTracks");
	setupBackgroundDD(assembler1, "justPhotons"); // tracks are not a background here
	setupFakeRates(assembler1);
	assembler1->setFakeRate("nTrackFakeMuons", "0"); // avoid ttbar MC subtraction
	assembler1->setFakeRate("nTrackFakeElectrons", "0"); // avoid ttbar MC subtraction
	assembler1->setDebug(true);
	prepare(assembler1);
	assembler1->process(varexp1, selection1);
	
	Assembler* assembler2 = new Assembler;
	init(assembler2);
	setupData(assembler2, true, 1);
	//setupBackgroundMC(assembler2, false, true, true);
	assembler2->setDebug(true);
	TString selection2 = selection1;
	selection2 += " && nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 0"; // + nTauFakeTaus[0] == 0";
	selection2 += " && nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1"; // + nTauFakeTaus[0] == 0";
	prepare(assembler2);
	assembler2->process(varexp2, selection2);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("fakeRatesLight_plots", 0755);
	chdir("fakeRatesLight_plots");
	
	std::vector<Assembler*> assemblers;
	assemblers.push_back(assembler1);
	assemblers.push_back(assembler2);
	
	std::vector<TString> cuts;
	cuts.push_back("");
	//cuts.push_back("assembler->setRange(\"HT[0]\", 0, 200, false);");
	//cuts.push_back("assembler->setRange(\"HT[0]\", 200);");
	
	//TString varName = "HT[0]";
	//TString varName = "NGOODJETS[0]";
	//TString varName = "NBJETSCSVM[0]";
	//TString varName = "NPROMPTNONISOTRACKS[0]";
	//TString varName = "NPROMPTNONISOTRACKS7[0]";
	//TString varName = "NISONONPROMPTTRACKS[0]";
	//TString varName = "NISONONPROMPTTRACKS7[0]";
	//TString varName = "(NPROMPTNONISOTRACKS[0]+NGOODTRACKS[0])";
	//TString varName = "(NPROMPTNONISOTRACKS7[0]+NGOODTRACKS[0])";
	//TString varName = "NBASICTRACKS7[0]";
//	TString varName = "NPROMPTINCLUSIVETRACKS[0]"; // considerung to use
	//TString varName = "NPROMPTINCLUSIVETRACKS7[0]"; // this is what we use
	//varName = "maxJetPT";

	TString varName = "NPROMPTNONISOINCLUSIVETRACKS7[0]";

//	TString varName = "NISONONPROMPTINCLUSIVETRACKS7[0]";
//	TString varName = "maxBDISCCSVGOODJETS";

	//TString varName = "NISONONPROMPTINCLUSIVETRACKS7[0]";
	//TString varName = "NISOINCLUSIVETRACKS7[0]";
	//TString varName = "NINCLUSIVETRACKS7[0]";
	//TString varName = "(NPROMPTINCLUSIVETRACKS7[0]-NPROMPTNONISOINCLUSIVETRACKS7[0])";
	
	assemblers[0]->setRange(varName);
	TCanvas* c1 = new TCanvas();
	c1->cd();
	TH1* hTemplate = (TH1*)assemblers[0]->project(varName, false)->getHistogram("data")->Clone("mu");
	hTemplate->Reset();
	hTemplate->SetLineColor(2);
	hTemplate->SetTitle("fake rate");
	std::vector<TH1*> hV;
	gStyle->SetOptFit(1111);
	
	// Measure light lepton fake rates
	for(int nMuons = 0; nMuons < 4; ++nMuons) {
		std::string fakeName = (nMuons % 2) ? "muon" : "electron";
//		for(int charge : {-1, +1}) {
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
						//assembler->setRange("(NGOODMUONS[0]%2)", nMuons, nMuons);
						assembler->setRange("NGOODMUONS[0]", nMuons, nMuons);
						if(i == 2) {
							assembler->setRange("nTrackFakeMuons[0]", (nMuons % 2), (nMuons % 2));
							assembler->setRange("nTrackFakeElectrons[0]", !(nMuons % 2), !(nMuons % 2));
						}
						
						//assembler->setRange("HT[0]", 0, 200, false);
						//assembler->setRange("HT[0]", 200);
						assembler->setRange("ONZ", 1);
						assembler->setRange("MET[0]", 0, 50, false); // 30?
						
						// Z+b
						//assembler->setRange("ONZ", 1, 1);
						//assembler->setRange("MET[0]", 0, 30, false);
						//assembler->setRange("HT[0]", 0, 100, false);
						//assembler->setRange("NBJETSCSVM[0]", 1, 1);
						
						// ttbar
						//assembler->setRange("ONZ", 0, 0);
						//assembler->setRange("ST[0]", 200);
						//assembler->setRange("NBJETSCSVM[0]", 1, 1);
						
						//assembler->setRange("MT[0]", 0, 50, false);
						//assembler->setRange("ONZ", 1, 1);
			//			assembler->setRange("NBJETSCSVM[0]", 0, 0);
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
							//fakeMC = projection->getHistogram("background")->IntegralAndError(k, k, fakeMCerr);
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
					double fakeRateErr = sqrt( (dataErr*dataErr + mcErr*mcErr) / pow(fake - fakeMC, 2) + ( (fakeErr*fakeErr + fakeMCerr*fakeMCerr) * pow(data - mc, 2) ) / pow(fake - fakeMC, 4) );
					printf("fake rate: %.4f ± %.4f (%.0f%%)\n", fakeRate, fakeRateErr, fakeRateErr / fakeRate * 100);
					h->SetBinContent(k, fakeRate);
					h->SetBinError(k, fakeRateErr);
				}
				h->SetMinimum(-0.10); h->SetMaximum(+0.30);
				h->Draw();
				h->Fit("pol0", "", "SAME");
				c1->SaveAs(TString::Format("sum_%s_%s_%dmu.pdf", varName.Data(), fakeName.c_str(), nMuons));
				//c1->SaveAs(TString::Format("sum_%s_%s_%s.pdf", varName.Data(), fakeName.c_str(), (nMuons == 0) ? "electronFake" : "muonFake"));
				//c1->SaveAs(TString::Format("sum_%s_%s_%s.pdf", varName.Data(), "lepon", "allFlavor"));
			}
//		}
	}
	
	delete assembler1;
	delete assembler2;
}
