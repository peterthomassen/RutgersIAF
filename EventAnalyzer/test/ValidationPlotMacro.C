#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <iostream>


using namespace std;

void ValidationPlotMacro (TString inputFile = "/cms/data21/heindl/Validation/ttbarS/validation_ttbarS.root") {
	
	TFile *ValFile = TFile::Open(inputFile);
	TTree* treeR = (TTree*)ValFile->Get("treeR");
	treeR->SetWeight();
	
	//set all variables
	std::vector<TString> variables;
	
	//electrons
	variables.push_back("ValMCelectronsPT");
	variables.push_back("ValMCelectronsPhi");
	variables.push_back("ValMCelectronsEta");
	variables.push_back("ValMCelectronsN");
	variables.push_back("ValMCelectronsM");
	
	variables.push_back("ValRecElectronsPT");
	variables.push_back("ValRecElectronsPhi");
	variables.push_back("ValRecElectronsEta");
	variables.push_back("ValRecElectronsN");
	variables.push_back("ValRecElectronsM");
	
	variables.push_back("ValMatchingElectronsPT");
	variables.push_back("ValMatchingElectronsPhi");
	variables.push_back("ValMatchingElectronsEta");
	variables.push_back("ValMatchingElectronsN");
	variables.push_back("ValMatchingElectronsM");
	
	variables.push_back("ValMCelectronsFromZPT");
	variables.push_back("ValMCelectronsFromZPhi");
	variables.push_back("ValMCelectronsFromZEta");
	variables.push_back("ValMCelectronsFromZN");
	variables.push_back("ValMCelectronsFromZM");

	//muons
	variables.push_back("ValMCmuonsPT");
	variables.push_back("ValMCmuonsPhi");
	variables.push_back("ValMCmuonsEta");
	variables.push_back("ValMCmuonsN");
	variables.push_back("ValMCmuonsM");
	
	variables.push_back("ValRecMuonsPT");
	variables.push_back("ValRecMuonsPhi");
	variables.push_back("ValRecMuonsEta");
	variables.push_back("ValRecMuonsN");
	variables.push_back("ValRecMuonsM");
	
	variables.push_back("ValMatchingMuonsPT");
	variables.push_back("ValMatchingMuonsPhi");
	variables.push_back("ValMatchingMuonsEta");
	variables.push_back("ValMatchingMuonsN");
	variables.push_back("ValMatchingMuonsM");
	
	variables.push_back("ValMCmuonsFromZPT");
	variables.push_back("ValMCmuonsFromZPhi");
	variables.push_back("ValMCmuonsFromZEta");
	variables.push_back("ValMCmuonsFromZN");
	variables.push_back("ValMCmuonsFromZM");
	
	//taus
	variables.push_back("ValMCtausPT");
	variables.push_back("ValMCtausPhi");
	variables.push_back("ValMCtausEta");
	variables.push_back("ValMCtausN");
	variables.push_back("ValMCtausM");
	
	variables.push_back("ValRecTausPT");
	variables.push_back("ValRecTausPhi");
	variables.push_back("ValRecTausEta");
	variables.push_back("ValRecTausN");
	variables.push_back("ValRecTausM");
	
	variables.push_back("ValMatchingTausPT");
	variables.push_back("ValMatchingTausPhi");
	variables.push_back("ValMatchingTausEta");
	variables.push_back("ValMatchingTausN");
	variables.push_back("ValMatchingTausM");
	
	variables.push_back("ValMCtausFromZPT");
	variables.push_back("ValMCtausFromZPhi");
	variables.push_back("ValMCtausFromZEta");
	variables.push_back("ValMCtausFromZN");
	variables.push_back("ValMCtausFromZM");
	
	//top and bottom; Jets
	variables.push_back("ValTopPT");
	variables.push_back("ValTopPhi");
	variables.push_back("ValTopEta");
	variables.push_back("ValTopN");
	variables.push_back("ValTopM");
	
	variables.push_back("ValBottomPT");
	variables.push_back("ValBottomPhi");
	variables.push_back("ValBottomEta");
	variables.push_back("ValBottomN");
	variables.push_back("ValBottomM");
	
	variables.push_back("ValJetsN");
	variables.push_back("ValBJetsCSVMN");
	variables.push_back("ValBJetsCSVLN");
	
	//Bosons: Z, W, Higgs
	variables.push_back("ValZPT");
	variables.push_back("ValZPhi");
	variables.push_back("ValZEta");
	variables.push_back("ValZN");
	variables.push_back("ValZM");
	
	variables.push_back("ValWPT");
	variables.push_back("ValWPhi");
	variables.push_back("ValWEta");
	variables.push_back("ValWN");
	variables.push_back("ValWM");
	
	variables.push_back("ValHiggsPT");
	variables.push_back("ValHiggsPhi");
	variables.push_back("ValHiggsEta");
	variables.push_back("ValHiggsN");
	variables.push_back("ValHiggsM");
	
	//ST, LT, HT, MET, MT
	variables.push_back("ValST");
	variables.push_back("ValLT");
	variables.push_back("ValHT");
	variables.push_back("ValMET");
	variables.push_back("ValMT");
	
	//Space for your own plots (1D,2D,3D)
	//e.g.: variables.push_back("ValMCelectronsEta:ValMCelectronsPhi>>htemp(100,-5,5,100,-5,5)","ValMCelectronsPT>20","COLZ");

	
	//Draw histograms in one pdf; identify 1D, 2D or 3D plots
	
	for(size_t i = 0; i < variables.size(); ++i) {
		char colon = ':';
		int i_colon = colon;
		int n_dim = variables[i].CountChar(i_colon);
		
		cout << "Histogram " << i+1 << "/" << variables.size() << endl;
		if (n_dim<0 || n_dim>2) {cout << "*** Hist " << variables[i] << " error: wrong dimensions for Hist ***" << endl; continue;}
		if (treeR->GetEntries(variables[i])==0) {cout << "Histogram with no entries (" << variables[i] << ") -> not drawn..." << endl; continue;}
		
		//begin pdf
		if (i==0 && i!=variables.size()-1) {
			if (n_dim==0) {
				treeR->Draw(variables[i]); 
				TH1D *htemp1 = (TH1D*)gPad->GetPrimitive("htemp");
				if(htemp1) {
					htemp1->Draw();
					
					c1->Print("validation_ttbarS.pdf(");
				} 
				else {cout << "*** htemp1 error: " << variables[i] << " ***" << endl;}
			}
			if (n_dim==1) {
				treeR->Draw(variables[i],"","COLZ"); 
				TH2D *htemp2 = (TH2D*)gPad->GetPrimitive("htemp");
				if(htemp2) {
					htemp2->Draw("COLZ");
					
					c1->Print("validation_ttbarS.pdf(");
				} 
				else {cout << "*** htemp2 error: " << variables[i] << " ***" << endl;}
			}
			if (n_dim==2) {
				treeR->Draw(variables[i],"","ISO"); 
				TH3D *htemp3 = (TH3D*)gPad->GetPrimitive("htemp");
				if(htemp3) {
					htemp3->Draw("ISO");
					
					c1->Print("validation_ttbarS.pdf(");
				} 
				else {cout << "*** htemp3 error: " << variables[i] << " ***" << endl;}
			}
		}
		
		//end pdf
		if (i!=0 && i==variables.size()-1) {
			if (n_dim==0) {
				treeR->Draw(variables[i]); 
				TH1D *htemp1 = (TH1D*)gPad->GetPrimitive("htemp");
				if(htemp1) {
					htemp1->Draw();
					
					c1->Print("validation_ttbarS.pdf)");
				} 
				else {cout << "*** htemp1 error: " << variables[i] << " ***" << endl;}
			}
			if (n_dim==1) {
				treeR->Draw(variables[i],"","COLZ"); 
				TH2D *htemp2 = (TH2D*)gPad->GetPrimitive("htemp");
				if(htemp2) {
					htemp2->Draw("COLZ");
					
					c1->Print("validation_ttbarS.pdf)");
				} 
				else {cout << "*** htemp2 error: " << variables[i] << " ***" << endl;}
			}
			if (n_dim==2) {
				treeR->Draw(variables[i],"","ISO"); 
				TH3D *htemp3 = (TH3D*)gPad->GetPrimitive("htemp");
				if(htemp3) {
					htemp3->Draw("ISO");
					
					c1->Print("validation_ttbarS.pdf)");
				} 
				else {cout << "*** htemp3 error: " << variables[i] << " ***" << endl;}
			}
		}
		
		//rest of pdf
		if(i!=0 && i!=variables.size()-1) {
			if (n_dim==0) {
				treeR->Draw(variables[i]); 
				TH1D *htemp1 = (TH1D*)gPad->GetPrimitive("htemp");
				if(htemp1) {
					htemp1->Draw();
					
					c1->Print("validation_ttbarS.pdf");
				} 
				else {cout << "*** htemp1 error: " << variables[i] << " ***" << endl;}
			}
			if (n_dim==1) {
				treeR->Draw(variables[i],"","COLZ"); 
				TH2D *htemp2 = (TH2D*)gPad->GetPrimitive("htemp");
				if(htemp2) {
					htemp2->Draw("COLZ");
					
					c1->Print("validation_ttbarS.pdf");
				} 
				else {cout << "*** htemp2 error: " << variables[i] << " ***" << endl;}
			}
			if (n_dim==2) {
				treeR->Draw(variables[i],"","ISO"); 
				TH3D *htemp3 = (TH3D*)gPad->GetPrimitive("htemp");
				if(htemp3) {
					htemp3->Draw("ISO");
					
					c1->Print("validation_ttbarS.pdf");
				} 
				else {cout << "*** htemp3 error: " << variables[i] << " ***" << endl;}
			}
		}
	}
	delete treeR;
	ValFile->Close();
}




