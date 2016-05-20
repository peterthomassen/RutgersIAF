#include <THnSparse.h>
//#include <TArray.h>
//#include <THn.h>
//#include <TH1.h>
#include "THnBase.h"
#include "matrixLUTgenerator_PromptFakeRates.C"

void matrixLUTgenerator(){
  cout<<"matrixLUTgenerator begin"<<endl;

  // -------------------------------------------------
  // Define desired bins here
  /*
  // We dont use individual Muon and Electron bins but they are also defined here anyway for reference,
  float MuonPt_Bins[7]           = {   10,   20,     30,   50,  75, 100, 10000 };
  float MuonAbsEta_Bins[4]       = {    0,  0.9,    1.3,  2.7                  };
  float MuonJetchmult_Bins[3]    = { -0.5,  8.5,  100.5                        };
  float MuonIsTight_Bins[3]      = { -0.5,  0.5,    1.5                        };
  //
  float ElectronPt_Bins[6]           = {   10,   20,    40,    60,  100, 10000 };
  float ElectronAbsEta_Bins[4]       = {    0,  0.9,   1.3,   2.7              };
  float ElectronJetnoofconst_Bins[4] = { -0.5,  8.5,  15.5, 100.5              };
  float ElectronIsTight_Bins[3]      = { -0.5,  0.5,   1.5                     };
  */
  //
  // These are the bins to be used for LUTs. They have to be as fine as the finer of the muon and electron bins above.
  float Pt_Bins[9]      = {   10,   20,   30,    40,  50,  60,  75,  100, 10000 };
  float AbsEta_Bins[4]  = {    0,  0.9,  1.3,   2.7                             };
  float Aux_Bins[4]     = { -0.5,  8.5, 15.5, 100.5                             };
  float IsTight_Bins[3] = { -0.5,  0.5,  1.5                                    };
  // -------------------------------------------------
  // These define the equal-width bins to be used for the THnSparseF declarations below. 
  // The upper and lower edges, and the number of bins have to match to those defined above. 
  int    bins[4] = {     8,   3,     3,    2 };
  double xmin[4] = {    10,   0,  -0.5, -0.5 };
  double xmax[4] = { 10000, 2.7, 100.5,  1.5 };
  // ..............................Lepton-1...........................Lepton-2..........................Lepton-3............
  int    D3bins[12] = {  bins[0],bins[1],bins[2],bins[3],  bins[0],bins[1],bins[2],bins[3],  bins[0],bins[1],bins[2],bins[3]  };
  double D3xmin[12] = {  xmin[0],xmin[1],xmin[2],xmin[3],  xmin[0],xmin[1],xmin[2],xmin[3],  xmin[0],xmin[1],xmin[2],xmin[3]  };
  double D3xmax[12] = {  xmax[0],xmax[1],xmax[2],xmax[3],  xmax[0],xmax[1],xmax[2],xmax[3],  xmax[0],xmax[1],xmax[2],xmax[3]  };
  //
  THnSparseF* Mu3MatrixLUT    = new THnSparseF("Mu3MatrixLUT",    "Mu3MatrixLUT",    12, D3bins, D3xmin, D3xmax);
  THnSparseF* Mu2El1MatrixLUT = new THnSparseF("Mu2El1MatrixLUT", "Mu2El1MatrixLUT", 12, D3bins, D3xmin, D3xmax);
  THnSparseF* Mu1El2MatrixLUT = new THnSparseF("Mu1El2MatrixLUT", "Mu1El2MatrixLUT", 12, D3bins, D3xmin, D3xmax);
  THnSparseF* El3MatrixLUT    = new THnSparseF("El3MatrixLUT",    "El3MatrixLUT",    12, D3bins, D3xmin, D3xmax);
  // -------------------------------------------------
  // Here the true boundaries are set for each bin.
  // 3Mu:
  Mu3MatrixLUT->GetAxis( 0)->Set(8,Pt_Bins);
  Mu3MatrixLUT->GetAxis( 1)->Set(3,AbsEta_Bins);
  Mu3MatrixLUT->GetAxis( 2)->Set(3,Aux_Bins);
  Mu3MatrixLUT->GetAxis( 3)->Set(2,IsTight_Bins);
  Mu3MatrixLUT->GetAxis( 4)->Set(8,Pt_Bins);
  Mu3MatrixLUT->GetAxis( 5)->Set(3,AbsEta_Bins);
  Mu3MatrixLUT->GetAxis( 6)->Set(3,Aux_Bins);
  Mu3MatrixLUT->GetAxis( 7)->Set(2,IsTight_Bins);
  Mu3MatrixLUT->GetAxis( 8)->Set(8,Pt_Bins);
  Mu3MatrixLUT->GetAxis( 9)->Set(3,AbsEta_Bins);
  Mu3MatrixLUT->GetAxis(10)->Set(3,Aux_Bins);
  Mu3MatrixLUT->GetAxis(11)->Set(2,IsTight_Bins);
  //
  // 2Mu - 1El : MuMuEl (also works for MuElMu and ElMuMu)
  Mu2El1MatrixLUT->GetAxis( 0)->Set(8,Pt_Bins);
  Mu2El1MatrixLUT->GetAxis( 1)->Set(3,AbsEta_Bins);
  Mu2El1MatrixLUT->GetAxis( 2)->Set(3,Aux_Bins);
  Mu2El1MatrixLUT->GetAxis( 3)->Set(2,IsTight_Bins);
  Mu2El1MatrixLUT->GetAxis( 4)->Set(8,Pt_Bins);
  Mu2El1MatrixLUT->GetAxis( 5)->Set(3,AbsEta_Bins);
  Mu2El1MatrixLUT->GetAxis( 6)->Set(3,Aux_Bins);
  Mu2El1MatrixLUT->GetAxis( 7)->Set(2,IsTight_Bins);
  Mu2El1MatrixLUT->GetAxis( 8)->Set(8,Pt_Bins);
  Mu2El1MatrixLUT->GetAxis( 9)->Set(3,AbsEta_Bins);
  Mu2El1MatrixLUT->GetAxis(10)->Set(3,Aux_Bins);
  Mu2El1MatrixLUT->GetAxis(11)->Set(2,IsTight_Bins);
  //
  // 1Mu - 2El : MuElEl (also works for ElMuEl and ElElMu)
  Mu1El2MatrixLUT->GetAxis( 0)->Set(8,Pt_Bins);
  Mu1El2MatrixLUT->GetAxis( 1)->Set(3,AbsEta_Bins);
  Mu1El2MatrixLUT->GetAxis( 2)->Set(3,Aux_Bins);
  Mu1El2MatrixLUT->GetAxis( 3)->Set(2,IsTight_Bins);
  Mu1El2MatrixLUT->GetAxis( 4)->Set(8,Pt_Bins);
  Mu1El2MatrixLUT->GetAxis( 5)->Set(3,AbsEta_Bins);
  Mu1El2MatrixLUT->GetAxis( 6)->Set(3,Aux_Bins);
  Mu1El2MatrixLUT->GetAxis( 7)->Set(2,IsTight_Bins);
  Mu1El2MatrixLUT->GetAxis( 8)->Set(8,Pt_Bins);
  Mu1El2MatrixLUT->GetAxis( 9)->Set(3,AbsEta_Bins);
  Mu1El2MatrixLUT->GetAxis(10)->Set(3,Aux_Bins);
  Mu1El2MatrixLUT->GetAxis(11)->Set(2,IsTight_Bins);
  //
  // 3El:
  El3MatrixLUT->GetAxis( 0)->Set(8,Pt_Bins);
  El3MatrixLUT->GetAxis( 1)->Set(3,AbsEta_Bins);
  El3MatrixLUT->GetAxis( 2)->Set(3,Aux_Bins);
  El3MatrixLUT->GetAxis( 3)->Set(2,IsTight_Bins);
  El3MatrixLUT->GetAxis( 4)->Set(8,Pt_Bins);
  El3MatrixLUT->GetAxis( 5)->Set(3,AbsEta_Bins);
  El3MatrixLUT->GetAxis( 6)->Set(3,Aux_Bins);
  El3MatrixLUT->GetAxis( 7)->Set(2,IsTight_Bins);
  El3MatrixLUT->GetAxis( 8)->Set(8,Pt_Bins);
  El3MatrixLUT->GetAxis( 9)->Set(3,AbsEta_Bins);
  El3MatrixLUT->GetAxis(10)->Set(3,Aux_Bins);
  El3MatrixLUT->GetAxis(11)->Set(2,IsTight_Bins);
  // -------------------------------------------------
  // Fill all LUTs.
  fillTHn( (THnSparseF*)Mu3MatrixLUT,    222, false ); // bool is for isDebug; it prints all bins
  fillTHn( (THnSparseF*)Mu2El1MatrixLUT, 221, false );
  fillTHn( (THnSparseF*)Mu1El2MatrixLUT, 211, false );
  fillTHn( (THnSparseF*)El3MatrixLUT,    111, false );
  // -------------------------------------------------
  // Define output file here, save LUTs:
  TFile* fo = new TFile("outfile3.root","RECREATE");
  Mu3MatrixLUT->Write();
  Mu2El1MatrixLUT->Write();
  Mu1El2MatrixLUT->Write();
  El3MatrixLUT->Write();
  // -------------------------------------------------
  /*
  // Alternate save-output for different files:
  Mu3MatrixLUT->SaveAs("Mu3MatrixLUT.root");
  Mu2El1MatrixLUT->SaveAs("Mu2El1MatrixLUT.root");
  Mu1El2MatrixLUT->SaveAs("Mu1El2MatrixLUT.root");
  El3MatrixLUT->SaveAs("El3MatrixLUT.root");
  */
  
  cout<<"matrixLUTgenerator end"<<endl;
}
