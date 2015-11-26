/* This example macro reads the validation variables from the output of exampleValidation.C 
 * for the WZto3LNu background from 2015 MC data and creates a PDF with plots
 * for all the validation variables.

 * Some instructions:
 * - Change the Input-file (line 21; Important: Use exampleValidation.C when creating AnalysisTree!).
 * - Change the name and the collision energy for your sample (line 26f).
 * - You can swith a template sample on and off, swith scaling between input and template on and off and change the template file (line 23f & 29). With template-on, every 1D plot has the input and the template sample distribution.
 * - When you want to plot your own variables (1D, 2D, 3D), just create them in the same way as the others (see 2D & 3D example line 874ff).
 * - You can also change the range for the X-axis in 1D histograms. You have an upper and lower limit (see example line 891ff).
*/


#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <iostream>


using namespace std;

void ValidationPlotMacro (TString inputFile = "/cms/data21/heindl/validation_package/AnalysisTree/WZto3LNu_all.simulation.root"
	, Bool_t temp = false
	, Bool_t scaling = false
	, TString templateFile = "/cms/data21/heindl/validation_package/AnalysisTree/WZto3LNu_all.simulation.root"
) {
	
	TString sample = "WZto3LNu";
	TString energy = "13 TeV";
	TString templateSample = "WZto3LNu";

	
	TH1::AddDirectory(false);
	TFile *ValFile = TFile::Open(inputFile);
	TTree* treeR = (TTree*)ValFile->Get("treeR");
	treeR->SetWeight();
	TFile *TemplateFile = TFile::Open(templateFile);
	TTree* treeT = (TTree*)TemplateFile->Get("treeR");
	treeT->SetWeight();
	
	//Set variables and titles
	std::vector<TString> variables;
	std::vector<TString> titles;
	std::vector<TString> lableX;
	std::vector<TString> lableY;
	std::vector<TString> lableZ;
	std::vector<double> rangeXup;
	std::vector<double> rangeXdown;
	
	//electrons
	variables.push_back("ValMCELECTRONSPT");	
	titles.push_back("Generator Electrons PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecElectronsPT");	
	titles.push_back("Reconstructed Electrons PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSPhi");
	titles.push_back("Generator Electrons Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecElectronsPhi");
	titles.push_back("Reconstructed Electrons Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSEta");
	titles.push_back("Generator Electrons Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecElectronsEta");
	titles.push_back("Reconstructed Electrons Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSN");
	titles.push_back("Number of Generator Electrons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecElectronsN");
	titles.push_back("Number of Reconstructed Electrons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSM");
	titles.push_back("Generator Electrons Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecElectronsM");
	titles.push_back("Reconstructed Electrons Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMatchingElectronsPT");	
	titles.push_back("Matching Electrons PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingElectronsPhi");
	titles.push_back("Matching Electrons Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingElectronsEta");
	titles.push_back("Matching Electrons Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingElectronsN");
	titles.push_back("Number of Matching Electrons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingElectronsM");
	titles.push_back("Matching Electrons Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMCELECTRONSFromZPT");	
	titles.push_back("Electrons from Z PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSFromZPhi");
	titles.push_back("Electrons from Z Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSFromZEta");
	titles.push_back("Electrons from Z Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSFromZN");
	titles.push_back("Number of Electrons from Z");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSFromZM");
	titles.push_back("Electrons from Z Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMCELECTRONSFromWPT");	
	titles.push_back("Electrons from W PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSFromWPhi");
	titles.push_back("Electrons from W Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSFromWEta");
	titles.push_back("Electrons from W Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSFromWN");
	titles.push_back("Number of Electrons from W");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCELECTRONSFromWM");
	titles.push_back("Electrons from W Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);

	//muons
	variables.push_back("ValMCMUONSPT");	
	titles.push_back("Generator Muons PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecMuonsPT");	
	titles.push_back("Reconstructed Muons PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSPhi");
	titles.push_back("Generator Muons Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecMuonsPhi");
	titles.push_back("Reconstructed Muons Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSEta");
	titles.push_back("Generator Muons Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecMuonsEta");
	titles.push_back("Reconstructed Muons Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSN");
	titles.push_back("Number of Generator Muons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecMuonsN");
	titles.push_back("Number of Reconstructed Muons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSM");
	titles.push_back("Generator Muons Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecMuonsM");
	titles.push_back("Reconstructed Muons Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMatchingMuonsPT");	
	titles.push_back("Matching Muons PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingMuonsPhi");
	titles.push_back("Matching Muons Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingMuonsEta");
	titles.push_back("Matching Muons Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingMuonsN");
	titles.push_back("Number of Matching Muons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingMuonsM");
	titles.push_back("Matching Muons Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMCMUONSFromZPT");	
	titles.push_back("Muons from Z PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSFromZPhi");
	titles.push_back("Muons from Z Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSFromZEta");
	titles.push_back("Muons from Z Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSFromZN");
	titles.push_back("Number of Muons from Z");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSFromZM");
	titles.push_back("Muons from Z Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMCMUONSFromWPT");	
	titles.push_back("Muons from W PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSFromWPhi");
	titles.push_back("Muons from W Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSFromWEta");
	titles.push_back("Muons from W Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSFromWN");
	titles.push_back("Number of Muons from W");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCMUONSFromWM");
	titles.push_back("Muons from W Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//taus
	variables.push_back("ValMCTAUSPT");	
	titles.push_back("Generator Taus PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecTausPT");	
	titles.push_back("Reconstructed Taus PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSPhi");
	titles.push_back("Generator Taus Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecTausPhi");
	titles.push_back("Reconstructed Taus Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSEta");
	titles.push_back("Generator Taus Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecTausEta");
	titles.push_back("Reconstructed Taus Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSN");
	titles.push_back("Number of Generator Taus");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecTausN");
	titles.push_back("Number of Reconstructed Taus");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSM");
	titles.push_back("Generator Taus Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValRecTausM");
	titles.push_back("Reconstructed Taus Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMatchingTausPT");	
	titles.push_back("Matching Taus PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingTausPhi");
	titles.push_back("Matching Taus Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingTausEta");
	titles.push_back("Matching Taus Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingTausN");
	titles.push_back("Number of Matching Taus");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMatchingTausM");
	titles.push_back("Matching Taus Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMCTAUSFromZPT");	
	titles.push_back("Taus from Z PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSFromZPhi");
	titles.push_back("Taus from Z Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSFromZEta");
	titles.push_back("Taus from Z Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSFromZN");
	titles.push_back("Number of Taus from Z");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSFromZM");
	titles.push_back("Taus from Z Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValMCTAUSFromWPT");	
	titles.push_back("Taus from W PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSFromWPhi");
	titles.push_back("Taus from W Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSFromWEta");
	titles.push_back("Taus from W Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSFromWN");
	titles.push_back("Number of Taus from W");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValMCTAUSFromWM");
	titles.push_back("Taus from W Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//dz and dxy
	variables.push_back("ValMuonsDz");
	titles.push_back("Muons dz");		
	lableX.push_back("dz");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);	
	variables.push_back("ValMuonsDxy");
	titles.push_back("Muons dxy");		
	lableX.push_back("dxy");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValElectronsDz");
	titles.push_back("Electrons dz");		
	lableX.push_back("dz");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);	
	variables.push_back("ValElectronsDxy");
	titles.push_back("Electrons dxy");		
	lableX.push_back("dxy");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MAXGENDXY");
	titles.push_back("MAXGENDXY");		
	lableX.push_back("dxy");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//top and bottom; Jets
	variables.push_back("ValTopPT");
	titles.push_back("Top-Quark PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValTopPhi");
	titles.push_back("Top-Quark Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValTopEta");
	titles.push_back("Top-Quark Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValTopN");
	titles.push_back("Number of Top-Quarks");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValTopM");
	titles.push_back("Top-Quark Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValBottomPT");
	titles.push_back("Bottom-Quark PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValBottomPhi");
	titles.push_back("Bottom-Quark Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValBottomEta");
	titles.push_back("Bottom-Quark Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValBottomN");
	titles.push_back("Number of Bottom-Quarks");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValBottomM");
	titles.push_back("Bottom-Quark Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValNGOODJETS");
	titles.push_back("Number of Jets");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("NBJETSCSVM");
	titles.push_back("Number of B-Jets (CSVM)");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("NBJETSCSVL");
	titles.push_back("Number of B-Jets (CSVL)");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//Bosons: Z, W, Higgs
	variables.push_back("ValZPT");
	titles.push_back("Z-Boson PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValZPhi");
	titles.push_back("Z-Boson Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValZEta");
	titles.push_back("Z-Boson Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValZN");
	titles.push_back("Number of Z-Bosons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValZM");
	titles.push_back("Z-Boson Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValWPT");
	titles.push_back("W-Boson PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValWPhi");
	titles.push_back("W-Boson Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValWEta");
	titles.push_back("W-Boson Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValWN");
	titles.push_back("Number of W-Bosons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValWM");
	titles.push_back("W-Boson Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ValHiggsPT");
	titles.push_back("Higgs-Boson PT");		
	lableX.push_back("PT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValHiggsPhi");
	titles.push_back("Higgs-Boson Phi");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValHiggsEta");
	titles.push_back("Higgs-Boson Eta");		
	lableX.push_back("Eta");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValHiggsN");
	titles.push_back("Number of Higgs-Bosons");		
	lableX.push_back("N");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ValHiggsM");
	titles.push_back("Higgs-Boson Mass");		
	lableX.push_back("M");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//ST, LT, HT, MET, MT
	variables.push_back("LT");
	titles.push_back("LT");		
	lableX.push_back("LT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("HT");
	titles.push_back("HT");		
	lableX.push_back("HT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MET");
	titles.push_back("MET");		
	lableX.push_back("MET");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MT");
	titles.push_back("MT");		
	lableX.push_back("MT");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ST");
	titles.push_back("ST");		
	lableX.push_back("ST");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);

	//your own plots, e.g:
	//2D:
	/*variables.push_back("ValMCTAUSEta:ValMCTAUSPhi");
	titles.push_back("Generator Taus Eta vs Phi");		
	lableX.push_back("Phi");
	lableY.push_back("Eta");
	lableZ.push_back("");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	//3D:
	variables.push_back("ValMCTAUSPT:ValMCTAUSEta:ValMCTAUSPhi");
	titles.push_back("Generator Taus PT vs Eta vs Phi");		
	lableX.push_back("Phi");
	lableY.push_back("Eta");
	lableZ.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	//X-axis range:
	variables.push_back("ValMCELECTRONSPhi");
	titles.push_back("Generator Electrons Phi (Zoom)");		
	lableX.push_back("Phi");
	lableY.push_back("");
	lableZ.push_back("");
	rangeXup.push_back(2);
	rangeXdown.push_back(-1);*/
	
	//Nice plots layout	
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetFillColor(0);
	gStyle->SetTextFont(42);
	gStyle->SetTextSize(0.04);
	gStyle->SetLabelFont(42,"x");
	gStyle->SetLabelFont(42,"y");
	gStyle->SetLabelFont(42,"z");
	gStyle->SetLabelSize(0.04,"x");
	gStyle->SetTitleSize(0.04,"x");
	gStyle->SetLabelSize(0.04,"y");
	gStyle->SetTitleSize(0.04,"y");
	gStyle->SetLabelSize(0.04,"z");
	gStyle->SetTitleSize(0.04,"z");
	gStyle->SetOptTitle(1);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	
	//Draw histograms in one pdf; identify 1D, 2D or 3D plots	
	TCanvas* canvas = new TCanvas("canvas");
	canvas->Divide(2,2);
	int n_plot = 0;
	
	std::vector<TString> variablesFiltered;
	std::vector<TString> titlesFiltered;
	std::vector<TString> lableXFiltered;
	std::vector<TString> lableYFiltered;
	std::vector<TString> lableZFiltered;
	std::vector<double> rangeXupFiltered;
	std::vector<double> rangeXdownFiltered;
	
	cout << "Filtering histograms with no entries..." << endl;
	for(size_t k = 0; k < variables.size(); k++) {
		if (treeR->GetEntries(variables[k])==0) {cout << "Histogram with no entries (" << variables[k] << ") -> not drawn" << endl; continue;}
		variablesFiltered.push_back(variables[k]);
		titlesFiltered.push_back(titles[k]);
		lableXFiltered.push_back(lableX[k]);
		lableYFiltered.push_back(lableY[k]);
		lableZFiltered.push_back(lableZ[k]);
		rangeXupFiltered.push_back(rangeXup[k]);
		rangeXdownFiltered.push_back(rangeXdown[k]);				
	}
	
	int fullPages = variablesFiltered.size()/4;
	if (variablesFiltered.size()%4==0) {fullPages--;}

	char colon = ':';
	int i_colon = colon;	
	
	for(size_t i = 0; i < variablesFiltered.size(); ++i) {
		int n_dim = variablesFiltered[i].CountChar(i_colon);
		
		double rangeX = rangeXupFiltered[i]-rangeXdownFiltered[i];
		TString Draw1 = TString::Format("%s>>htemp",variablesFiltered[i].Data());
		TString Draw2 = TString::Format("%s>>htemp(100,%f,%f)",variablesFiltered[i].Data(),rangeXdownFiltered[i],rangeXupFiltered[i]);
		TString DrawT1 = TString::Format("%s>>htempT",variablesFiltered[i].Data());
		TString DrawT2 = TString::Format("%s>>htempT(100,%f,%f)",variablesFiltered[i].Data(),rangeXdownFiltered[i],rangeXupFiltered[i]);
		
		cout << "Histogram " << i+1 << "/" << variablesFiltered.size() << endl;
		if (n_dim<0 || n_dim>2) {cout << "*** Hist " << variablesFiltered[i] << " error: wrong dimensions for Hist ***" << endl; break;}
		
		//begin pdf
		if (i<4) {
			if (n_dim==0) {
				n_plot++;
				canvas->cd(n_plot);
				THStack *tempStack = new THStack("tempStack",titlesFiltered[i]);
				if(rangeX == 0) {treeR->Draw(Draw1);}
				else {treeR->Draw(Draw2);}
				TH1D *htemp1 = (TH1D*)gPad->GetPrimitive("htemp");
				if(htemp1) {
					tempStack->Add(htemp1);
					if (temp && treeT->GetEntries(variablesFiltered[i]) != 0) {
						if(rangeX == 0) {treeT->Draw(DrawT1);}
						else {treeT->Draw(DrawT2);}
						TH1D *htemp1T = (TH1D*)gPad->GetPrimitive("htempT");
						htemp1T->SetLineColor(34);
						if (scaling) {htemp1T->Scale(htemp1->GetEntries()/htemp1T->GetEntries());}
						tempStack->Add(htemp1T);
					}
					tempStack->Draw("nostack");
					tempStack->GetYaxis()->SetTitle(lableYFiltered[i]);
					tempStack->GetXaxis()->SetTitle(lableXFiltered[i]);
					
					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText(sample + " (" + energy + ")");
					Info->AddText("CMS Simulation");
					if (temp) {Info->AddText("Template: " + templateSample);}
					Info->Draw();
					
					if (n_plot==4) {
						canvas->Print("validation_" + sample + ".pdf("); n_plot=0;
						canvas->Clear("D");
					}
				} 
				else {cout << "*** htemp1 error: " << variablesFiltered[i] << " ***" << endl;}
			}
			if (n_dim==1) {
				n_plot++;
				canvas->cd(n_plot);
				treeR->Draw(variablesFiltered[i],"","COLZ"); 
				TH2D *htemp2 = (TH2D*)gPad->GetPrimitive("htemp");
				if(htemp2) {
					htemp2->Draw("COLZ");
					htemp2->SetTitle(titlesFiltered[i]);
					htemp2->GetXaxis()->SetTitle(lableXFiltered[i]);
					htemp2->GetYaxis()->SetTitle(lableYFiltered[i]);
					htemp2->GetZaxis()->SetTitle(lableZFiltered[i]);
					
					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText("CMS Simulation");
					Info->AddText(sample + " (" + energy + ")");
					Info->Draw();
					
					if (n_plot==4) {
						canvas->Print("validation_" + sample + ".pdf("); n_plot=0;
						canvas->Clear("D");
					}
				} 
				else {cout << "*** htemp2 error: " << variablesFiltered[i] << " ***" << endl;}
			}
			if (n_dim==2) {
				n_plot++;
				canvas->cd(n_plot);
				treeR->Draw(variablesFiltered[i],"","ISO"); 
				TH3D *htemp3 = (TH3D*)gPad->GetPrimitive("htemp");
				if(htemp3) {
					htemp3->Draw("ISO");
					htemp3->SetTitle(titlesFiltered[i]);
					htemp3->GetXaxis()->SetTitle(lableXFiltered[i]);
					htemp3->GetYaxis()->SetTitle(lableYFiltered[i]);
					htemp3->GetZaxis()->SetTitle(lableZFiltered[i]);
					
					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText("CMS Simulation");
					Info->AddText(sample + " (" + energy + ")");
					Info->Draw();
					
					if (n_plot==4) {
						canvas->Print("validation_" + sample + ".pdf("); n_plot=0;
						canvas->Clear("D");
					}
				} 
				else {cout << "*** htemp3 error: " << variablesFiltered[i] << " ***" << endl;}
			}
		}
		
		//mid of pdf
		if (i>3 && i<4*fullPages) {
			if (n_dim==0) {
				n_plot++;
				canvas->cd(n_plot);
				THStack *tempStack = new THStack("tempStack",titlesFiltered[i]);
				if(rangeX == 0) {treeR->Draw(Draw1);}
				else {treeR->Draw(Draw2);}
				TH1D *htemp1 = (TH1D*)gPad->GetPrimitive("htemp");
				if(htemp1) {
					tempStack->Add(htemp1);
					if (temp && treeT->GetEntries(variablesFiltered[i]) != 0) {
						if(rangeX == 0) {treeT->Draw(DrawT1);}
						else {treeT->Draw(DrawT2);}
						TH1D *htemp1T = (TH1D*)gPad->GetPrimitive("htempT");
						htemp1T->SetLineColor(34);
						if (scaling) {htemp1T->Scale(htemp1->GetEntries()/htemp1T->GetEntries());}
						tempStack->Add(htemp1T);
					}
					tempStack->Draw("nostack");
					tempStack->GetYaxis()->SetTitle(lableYFiltered[i]);
					tempStack->GetXaxis()->SetTitle(lableXFiltered[i]);

					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText("CMS Simulation");
					Info->AddText(sample + " (" + energy + ")");
					if (temp) {Info->AddText("Template: " + templateSample);}
					Info->Draw();
					
					if (n_plot==4) {
						canvas->Print("validation_" + sample + ".pdf"); n_plot=0;
						canvas->Clear("D");
					}
				} 
				else {cout << "*** htemp1 error: " << variablesFiltered[i] << " ***" << endl;}
			}
			if (n_dim==1) {
				n_plot++;
				canvas->cd(n_plot);
				treeR->Draw(variablesFiltered[i],"","COLZ"); 
				TH2D *htemp2 = (TH2D*)gPad->GetPrimitive("htemp");
				if(htemp2) {
					htemp2->Draw("COLZ");
					htemp2->SetTitle(titlesFiltered[i]);
					htemp2->GetXaxis()->SetTitle(lableXFiltered[i]);
					htemp2->GetYaxis()->SetTitle(lableYFiltered[i]);
					htemp2->GetZaxis()->SetTitle(lableZFiltered[i]);
	
					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText("CMS Simulation");
					Info->AddText(sample + " (" + energy + ")");
					Info->Draw();
					
					if (n_plot==4) {
						canvas->Print("validation_" + sample + ".pdf"); n_plot=0;
						canvas->Clear("D");
					}
				} 
				else {cout << "*** htemp2 error: " << variablesFiltered[i] << " ***" << endl;}
			}
			if (n_dim==2) {
				n_plot++;
				canvas->cd(n_plot);
				treeR->Draw(variablesFiltered[i],"","ISO"); 
				TH3D *htemp3 = (TH3D*)gPad->GetPrimitive("htemp");
				if(htemp3) {
					htemp3->Draw("ISO");
					htemp3->SetTitle(titlesFiltered[i]);
					htemp3->GetXaxis()->SetTitle(lableXFiltered[i]);
					htemp3->GetYaxis()->SetTitle(lableYFiltered[i]);
					htemp3->GetZaxis()->SetTitle(lableZFiltered[i]);

					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText("CMS Simulation");
					Info->AddText(sample + " (" + energy + ")");
					Info->Draw();
					
					if (n_plot==4) {
						canvas->Print("validation_" + sample + ".pdf"); n_plot=0;
						canvas->Clear("D");
					}
				} 
				else {cout << "*** htemp3 error: " << variablesFiltered[i] << " ***" << endl;}
			}
		}
		
		//end pdf
		if (i>=fullPages*4) {
			if (n_dim==0) {
				n_plot++;
				canvas->cd(n_plot);
				THStack *tempStack = new THStack("tempStack",titlesFiltered[i]);
				if(rangeX == 0) {treeR->Draw(Draw1);}
				else {treeR->Draw(Draw2);}
				TH1D *htemp1 = (TH1D*)gPad->GetPrimitive("htemp");
				if(htemp1) {
					tempStack->Add(htemp1);
					if (temp && treeT->GetEntries(variablesFiltered[i]) != 0) {
						if(rangeX == 0) {treeT->Draw(DrawT1);}
						else {treeT->Draw(DrawT2);}
						TH1D *htemp1T = (TH1D*)gPad->GetPrimitive("htempT");
						htemp1T->SetLineColor(34);
						if (scaling) {htemp1T->Scale(htemp1->GetEntries()/htemp1T->GetEntries());}
						tempStack->Add(htemp1T);
					}
					tempStack->Draw("nostack");
					tempStack->GetYaxis()->SetTitle(lableYFiltered[i]);
					tempStack->GetXaxis()->SetTitle(lableXFiltered[i]);
	
					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText("CMS Simulation");
					Info->AddText(sample + " (" + energy + ")");
					if (temp) {Info->AddText("Template: " + templateSample);}
					Info->Draw();
					
					if (i==variablesFiltered.size()-1) {
						canvas->Print("validation_" + sample + ".pdf)");
						canvas->Clear("D");
					}
				} 
				else {cout << "*** htemp1 error: " << variablesFiltered[i] << " ***" << endl;}
			}
			if (n_dim==1) {
				n_plot++;
				canvas->cd(n_plot);
				treeR->Draw(variablesFiltered[i],"","COLZ"); 
				TH2D *htemp2 = (TH2D*)gPad->GetPrimitive("htemp");
				if(htemp2) {
					htemp2->Draw("COLZ");
					htemp2->SetTitle(titlesFiltered[i]);
					htemp2->GetXaxis()->SetTitle(lableXFiltered[i]);
					htemp2->GetYaxis()->SetTitle(lableYFiltered[i]);
					htemp2->GetZaxis()->SetTitle(lableZFiltered[i]);

					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText("CMS Simulation");
					Info->AddText(sample + " (" + energy + ")");
					Info->Draw();
					
					if (i==variablesFiltered.size()-1) {
						canvas->Print("validation_" + sample + ".pdf)");
						canvas->Clear("D");
						}
				} 
				else {cout << "*** htemp2 error: " << variablesFiltered[i] << " ***" << endl;}
			}
			if (n_dim==2) {
				n_plot++;
				canvas->cd(n_plot);
				treeR->Draw(variablesFiltered[i],"","ISO"); 
				TH3D *htemp3 = (TH3D*)gPad->GetPrimitive("htemp");
				if(htemp3) {
					htemp3->Draw("ISO");
					htemp3->SetTitle(titlesFiltered[i]);
					htemp3->GetXaxis()->SetTitle(lableXFiltered[i]);
					htemp3->GetYaxis()->SetTitle(lableYFiltered[i]);
					htemp3->GetZaxis()->SetTitle(lableZFiltered[i]);

					TPaveText *Info=new TPaveText(0.8,0.8,1,1,"NDC");
					Info->AddText("CMS Simulation");
					Info->AddText(sample + " (" + energy + ")");
					Info->Draw();
					
					if (i==variablesFiltered.size()-1) {
						canvas->Print("validation_" + sample + ".pdf)");
						canvas->Clear("D");
					}
				} 
				else {cout << "*** htemp3 error: " << variablesFiltered[i] << " ***" << endl;}
			}
		}
		
	}
	delete treeR;
	delete treeT;
	ValFile->Close();
	TemplateFile->Close();
}