/* This example macro reads the validation variables from the output of exampleValidation.C 
 * for the WZto3LNu background from 2015 MC data and creates a PDF with plots
 * for all the validation variables.

 * Some instructions:
 * - Change the input-file (line 23; Important: Use exampleValidation.C + necessary helper-files when creating AnalysisTree!).
 * - Change the name and the collision energy for your sample (line 29f).
 * - You can switch a template sample on and off, with scaling between input and template on and off and change the template file (line 24ff & 31). 
     With template on, every plot has the input and the template sample distribution.
 * - You can also set log-scale for the y-axis on and off (line 27).
 * - When you want to plot your own variables, just create them in the same way as the others (Important: These variables have to be added to helperValidation.C/helperMiniAOD.C before!).
 * - You can also change the range for the x-axis. You have an upper and lower limit (see example line 678ff).
 * - You can write some comments on the first page via TPaveText (line 717).
*/

#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <iostream>

using namespace std;

void ValidationPlotMacro(TString inputFile = "/cms/data21/heindl/validation_package/AnalysisTree/WZto3LNu_all.simulation.root"
	, Bool_t temp = false
	, Bool_t scaling = false
	, TString templateFile = "/cms/data21/heindl/validation_package/AnalysisTree/WZto3LNu_all.simulation.root"
	, Bool_t logScale = false
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
	std::vector<double> rangeXup;
	std::vector<double> rangeXdown;
	
	//electrons
	variables.push_back("MCELECTRONSPT");	
	titles.push_back("Generator Electrons PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("PTGOODELECTRONS");	
	titles.push_back("Reconstructed Electrons PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSPhi");
	titles.push_back("Generator Electrons Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("PHIGOODELECTRONS");
	titles.push_back("Reconstructed Electrons Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSEta");
	titles.push_back("Generator Electrons Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ETAGOODELECTRONS");
	titles.push_back("Reconstructed Electrons Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSN");
	titles.push_back("Number of Generator Electrons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("NGOODELECTRONS");
	titles.push_back("Number of Reconstructed Electrons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSM");
	titles.push_back("Generator Electrons Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MGOODELECTRONS");
	titles.push_back("Reconstructed Electrons Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Mother_MCELECTRONS");
	titles.push_back("Mother PDG-ID of Generator Electrons");
	lableX.push_back("PDG-ID");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);	
	
	variables.push_back("MatchingElectronsPT");	
	titles.push_back("Matching Electrons PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingElectronsPhi");
	titles.push_back("Matching Electrons Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingElectronsEta");
	titles.push_back("Matching Electrons Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingElectronsN");
	titles.push_back("Number of Matching Electrons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingElectronsM");
	titles.push_back("Matching Electrons Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MCELECTRONSFROMZPT");	
	titles.push_back("Electrons from Z PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSFROMZPhi");
	titles.push_back("Electrons from Z Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSFROMZEta");
	titles.push_back("Electrons from Z Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSFROMZN");
	titles.push_back("Number of Electrons from Z");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSFROMZM");
	titles.push_back("Electrons from Z Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MCELECTRONSFROMWPT");	
	titles.push_back("Electrons from W PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSFROMWPhi");
	titles.push_back("Electrons from W Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSFROMWEta");
	titles.push_back("Electrons from W Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSFROMWN");
	titles.push_back("Number of Electrons from W");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCELECTRONSFROMWM");
	titles.push_back("Electrons from W Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//muons
	variables.push_back("MCMUONSPT");	
	titles.push_back("Generator Muons PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("PTGOODMUONS");	
	titles.push_back("Reconstructed Muons PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSPhi");
	titles.push_back("Generator Muons Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("PHIGOODMUONS");
	titles.push_back("Reconstructed Muons Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSEta");
	titles.push_back("Generator Muons Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ETAGOODMUONS");
	titles.push_back("Reconstructed Muons Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSN");
	titles.push_back("Number of Generator Muons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("NGOODMUONS");
	titles.push_back("Number of Reconstructed Muons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSM");
	titles.push_back("Generator Muons Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MGOODMUONS");
	titles.push_back("Reconstructed Muons Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Mother_MCMUONS");
	titles.push_back("Mother PDG-ID of Generator Muons");
	lableX.push_back("PDG-ID");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);	
	
	variables.push_back("MatchingMuonsPT");	
	titles.push_back("Matching Muons PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingMuonsPhi");
	titles.push_back("Matching Muons Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingMuonsEta");
	titles.push_back("Matching Muons Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingMuonsN");
	titles.push_back("Number of Matching Muons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingMuonsM");
	titles.push_back("Matching Muons Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MCMUONSFROMZPT");	
	titles.push_back("Muons from Z PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSFROMZPhi");
	titles.push_back("Muons from Z Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSFROMZEta");
	titles.push_back("Muons from Z Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSFROMZN");
	titles.push_back("Number of Muons from Z");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSFROMZM");
	titles.push_back("Muons from Z Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MCMUONSFROMWPT");	
	titles.push_back("Muons from W PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSFROMWPhi");
	titles.push_back("Muons from W Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSFROMWEta");
	titles.push_back("Muons from W Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSFROMWN");
	titles.push_back("Number of Muons from W");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCMUONSFROMWM");
	titles.push_back("Muons from W Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//taus
	variables.push_back("MCTAUSPT");	
	titles.push_back("Generator Taus PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("PTGOODTAUS");	
	titles.push_back("Reconstructed Taus PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSPhi");
	titles.push_back("Generator Taus Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("PHIGOODTAUS");
	titles.push_back("Reconstructed Taus Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSEta");
	titles.push_back("Generator Taus Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ETAGOODTAUS");
	titles.push_back("Reconstructed Taus Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSN");
	titles.push_back("Number of Generator Taus");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("NGOODTAUS");
	titles.push_back("Number of Reconstructed Taus");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSM");
	titles.push_back("Generator Taus Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MGOODTAUS");
	titles.push_back("Reconstructed Taus Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Mother_MCTAUS");
	titles.push_back("Mother PDG-ID of Generator Taus");
	lableX.push_back("PDG-ID");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);	
	
	variables.push_back("MatchingTausPT");	
	titles.push_back("Matching Taus PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingTausPhi");
	titles.push_back("Matching Taus Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingTausEta");
	titles.push_back("Matching Taus Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingTausN");
	titles.push_back("Number of Matching Taus");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MatchingTausM");
	titles.push_back("Matching Taus Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MCTAUSFROMZPT");	
	titles.push_back("Taus from Z PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSFROMZPhi");
	titles.push_back("Taus from Z Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSFROMZEta");
	titles.push_back("Taus from Z Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSFROMZN");
	titles.push_back("Number of Taus from Z");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSFROMZM");
	titles.push_back("Taus from Z Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MCTAUSFROMWPT");	
	titles.push_back("Taus from W PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSFROMWPhi");
	titles.push_back("Taus from W Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSFROMWEta");
	titles.push_back("Taus from W Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSFROMWN");
	titles.push_back("Number of Taus from W");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTAUSFROMWM");
	titles.push_back("Taus from W Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);

	//dz and dxy
	variables.push_back("ElectronsDz");
	titles.push_back("Electrons dz");		
	lableX.push_back("dz");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);	
	variables.push_back("ElectronsDxy");
	titles.push_back("Electrons dxy");		
	lableX.push_back("dxy");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MuonsDz");
	titles.push_back("Muons dz");		
	lableX.push_back("dz");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);	
	variables.push_back("MuonsDxy");
	titles.push_back("Muons dxy");		
	lableX.push_back("dxy");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("TausDz");
	titles.push_back("Taus dz");		
	lableX.push_back("dz");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);	
	
	variables.push_back("MAXGENDXY");
	titles.push_back("MAXGENDXY");		
	lableX.push_back("dxy");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//top and bottom; Jets
	variables.push_back("MCTopPT");
	titles.push_back("Top-Quark PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTopPhi");
	titles.push_back("Top-Quark Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTopEta");
	titles.push_back("Top-Quark Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTopN");
	titles.push_back("Number of Top-Quarks");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCTopM");
	titles.push_back("Top-Quark Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MCBottomPT");
	titles.push_back("Bottom-Quark PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCBottomPhi");
	titles.push_back("Bottom-Quark Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCBottomEta");
	titles.push_back("Bottom-Quark Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCBottomN");
	titles.push_back("Number of Bottom-Quarks");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("MCBottomM");
	titles.push_back("Bottom-Quark Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("NGOODJETS");
	titles.push_back("Number of Jets");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("PTGOODJETS");
	titles.push_back("Jet PT");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("ETAGOODJETS");
	titles.push_back("Jet Eta");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("NBJETSCSVM");
	titles.push_back("Number of B-Jets (CSVM)");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("NBJETSCSVL");
	titles.push_back("Number of B-Jets (CSVL)");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//Bosons: Z, W, Higgs
	variables.push_back("Z_BOSONPT");
	titles.push_back("Z-Boson PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Z_BOSONPhi");
	titles.push_back("Z-Boson Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Z_BOSONEta");
	titles.push_back("Z-Boson Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Z_BOSONN");
	titles.push_back("Number of Z-Bosons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Z_BOSONM");
	titles.push_back("Z-Boson Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("W_BOSONPT");
	titles.push_back("W-Boson PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("W_BOSONPhi");
	titles.push_back("W-Boson Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("W_BOSONEta");
	titles.push_back("W-Boson Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("W_BOSONN");
	titles.push_back("Number of W-Bosons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("W_BOSONM");
	titles.push_back("W-Boson Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("Higgs_BOSONPT");
	titles.push_back("Higgs-Boson PT");		
	lableX.push_back("PT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Higgs_BOSONPhi");
	titles.push_back("Higgs-Boson Phi");		
	lableX.push_back("Phi");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Higgs_BOSONEta");
	titles.push_back("Higgs-Boson Eta");		
	lableX.push_back("Eta");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Higgs_BOSONN");
	titles.push_back("Number of Higgs-Bosons");		
	lableX.push_back("N");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	variables.push_back("Higgs_BOSONM");
	titles.push_back("Higgs-Boson Mass");		
	lableX.push_back("M");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	//ST, LT, HT, MET, MT
	variables.push_back("LT");
	titles.push_back("LT");		
	lableX.push_back("LT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("HT");
	titles.push_back("HT");		
	lableX.push_back("HT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MET");
	titles.push_back("MET");		
	lableX.push_back("MET");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("MT");
	titles.push_back("MT");		
	lableX.push_back("MT");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);
	
	variables.push_back("ST");
	titles.push_back("ST");		
	lableX.push_back("ST");
	rangeXup.push_back(0);
	rangeXdown.push_back(0);

	//your own plots, e.g:
	//X-axis range:
	/*variables.push_back("MCMUONSPhi");
	titles.push_back("Generator Electrons Phi (Zoom)");		
	lableX.push_back("Phi");
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
	if (logScale) {gStyle->SetOptLogy(1);}
	
	//Draw histograms in one pdf; identify 1D, 2D or 3D plots	
	TCanvas* canvas = new TCanvas("canvas");
	
	TPaveText *FirstPage1=new TPaveText(.05,.7,.95,.9,"NDC");
	FirstPage1->AddText("MC validation of " + sample + " (" + energy + ")");
	FirstPage1->Draw();
	TPaveText *FirstPage2=new TPaveText(.05,.1,.95,.4,"NDC");
	FirstPage2->AddText("Comments:");	
	FirstPage2->AddText("...");
	if (temp && !scaling) {FirstPage2->AddText("Template Sample: " + templateSample);}
	if (temp && scaling) {FirstPage2->AddText("Template Sample: " + templateSample + " (scaled)");}
	if (temp) {FirstPage2->AddText(sample + ": blue; " + templateSample + ": red");}
	FirstPage2->Draw();
	canvas->Print("validation_" + sample + ".pdf(");
	canvas->Clear();
	
	canvas->Divide(2,2);
	int n_plot = 0;
	
	std::vector<TString> variablesFiltered;
	std::vector<TString> titlesFiltered;
	std::vector<TString> lableXFiltered;
	std::vector<double> rangeXupFiltered;
	std::vector<double> rangeXdownFiltered;
	
	cout << "Filtering histograms with no entries..." << endl;
	for(size_t k = 0; k < variables.size(); k++) {
		if (treeR->GetEntries(variables[k])==0) {cout << "Histogram with no entries (" << variables[k] << ") -> not drawn" << endl; continue;}
		variablesFiltered.push_back(variables[k]);
		titlesFiltered.push_back(titles[k]);
		lableXFiltered.push_back(lableX[k]);
		rangeXupFiltered.push_back(rangeXup[k]);
		rangeXdownFiltered.push_back(rangeXdown[k]);				
	}
	
	int fullPages = variablesFiltered.size()/4;
	if (variablesFiltered.size()%4==0) {fullPages--;}

	char colon = ':';
	int i_colon = colon;	
	
	for(size_t i = 0; i < variablesFiltered.size(); ++i) {
		int n_dim = variablesFiltered[i].CountChar(i_colon);
		
		cout << "Histogram " << i+1 << "/" << variablesFiltered.size() << endl;
		if (n_dim!=0) {cout << "*** Hist " << variablesFiltered[i] << " error: not a 1D histogram ***" << endl; break;}
		
		double rangeX = rangeXupFiltered[i]-rangeXdownFiltered[i];
		TString Draw1 = TString::Format("%s>>htemp",variablesFiltered[i].Data());
		TString Draw2 = TString::Format("%s>>htemp(100,%f,%f)",variablesFiltered[i].Data(),rangeXdownFiltered[i],rangeXupFiltered[i]);
		TString DrawT1 = TString::Format("%s>>htempT",variablesFiltered[i].Data());
		TString DrawT2 = TString::Format("%s>>htempT(100,%f,%f)",variablesFiltered[i].Data(),rangeXdownFiltered[i],rangeXupFiltered[i]);
		
		//mid of pdf
		if (i<4*fullPages) {
			n_plot++;
			canvas->cd(n_plot);
			THStack *tempStack = new THStack("tempStack",titlesFiltered[i]);
			if(rangeX == 0) {treeR->Draw(Draw1);}
			else {treeR->Draw(Draw2);}
			TH1D *htemp = (TH1D*)gPad->GetPrimitive("htemp");
			htemp->SetLineColor(4);
			if(htemp) {
				tempStack->Add(htemp);
				TH1D *htempT = 0;
				if (temp && treeT->GetEntries(variablesFiltered[i]) != 0) {
					if(rangeX == 0) {treeT->Draw(DrawT1);}
					else {treeT->Draw(DrawT2);}
					htempT = (TH1D*)gPad->GetPrimitive("htempT");
					htempT->SetLineColor(46);
					if (scaling) {htempT->Scale(htemp->GetEntries()/htempT->GetEntries());}
					tempStack->Add(htempT);
				}
				tempStack->Draw("nostack");
				tempStack->GetXaxis()->SetTitle(lableXFiltered[i]);
				
				TLegend* legend = new TLegend(0.775,0.8,1,1,"CMS Simulation (" + energy + ")","NDC");
				legend->SetNColumns(2);
				legend->AddEntry(htemp, sample, "l");
				legend->AddEntry((TObject*)0, "", "");
				TString Entries = TString::Format("Entries: %.0f", htemp->GetEntries());
				legend->AddEntry((TObject*)0, Entries, "");
				TString Mean = TString::Format("Mean: %.2f", htemp->GetMean());
				legend->AddEntry((TObject*)0, Mean, "");
				if (temp) {
					legend->AddEntry(htempT, templateSample, "l");
					if (scaling) {
						TString ScaleFactor = TString::Format("scale factor: %.2f",htemp->GetEntries()/htempT->GetEntries());
						legend->AddEntry((TObject*)0, ScaleFactor, "");
					}
					if (!scaling) {legend->AddEntry((TObject*)0, "", "");}
					TString EntriesT = TString::Format("Entries: %.0f", htempT->GetEntries());
					legend->AddEntry((TObject*)0, EntriesT, "");
					TString MeanT = TString::Format("Mean: %.2f", htempT->GetMean());
					legend->AddEntry((TObject*)0, MeanT, "");				
				}
				legend->Draw();
					
				if (n_plot==4) {
					canvas->Print("validation_" + sample + ".pdf"); 
					n_plot=0;
					canvas->Clear("D");
				}
			} 
		}
		
		//end pdf
		if (i>=fullPages*4) {
			n_plot++;
			canvas->cd(n_plot);
			THStack *tempStack = new THStack("tempStack",titlesFiltered[i]);
			if(rangeX == 0) {treeR->Draw(Draw1);}
			else {treeR->Draw(Draw2);}
			TH1D *htemp = (TH1D*)gPad->GetPrimitive("htemp");
			htemp->SetLineColor(4);
			if(htemp) {
				tempStack->Add(htemp);
				TH1D *htempT = 0;
				if (temp && treeT->GetEntries(variablesFiltered[i]) != 0) {
					if(rangeX == 0) {treeT->Draw(DrawT1);}
					else {treeT->Draw(DrawT2);}
					htempT = (TH1D*)gPad->GetPrimitive("htempT");
					htempT->SetLineColor(46);
					if (scaling) {htempT->Scale(htemp->GetEntries()/htempT->GetEntries());}
					tempStack->Add(htempT);
				}
				tempStack->Draw("nostack");
				tempStack->GetXaxis()->SetTitle(lableXFiltered[i]);
				
				TLegend* legend = new TLegend(0.775,0.8,1,1,"CMS Simulation (" + energy + ")","NDC");
				legend->SetNColumns(2);
				legend->AddEntry(htemp, sample, "l");
				legend->AddEntry((TObject*)0, "", "");
				TString Entries = TString::Format("Entries: %.0f", htemp->GetEntries());
				legend->AddEntry((TObject*)0, Entries, "");
				TString Mean = TString::Format("Mean: %.2f", htemp->GetMean());
				legend->AddEntry((TObject*)0, Mean, "");
				if (temp) {
					legend->AddEntry(htempT, templateSample, "l");
					if (scaling) {
						TString ScaleFactor = TString::Format("scale factor: %.2f",htemp->GetEntries()/htempT->GetEntries());
						legend->AddEntry((TObject*)0, ScaleFactor, "");
					}
					if (!scaling) {legend->AddEntry((TObject*)0, "", "");}
					TString EntriesT = TString::Format("Entries: %.0f", htempT->GetEntries());
					legend->AddEntry((TObject*)0, EntriesT, "");
					TString MeanT = TString::Format("Mean: %.2f", htempT->GetMean());
					legend->AddEntry((TObject*)0, MeanT, "");				
				}
				legend->Draw();
					
				if (i==variablesFiltered.size()-1) {
					canvas->Print("validation_" + sample + ".pdf)");
					canvas->Clear("D");
				}
			} 
		}
	}
	delete treeR;
	delete treeT;
	ValFile->Close();
	TemplateFile->Close();
}