#include <THnSparse.h>
//#include <TArray.h>
//#include <THn.h>
//#include <TH1.h>
#include "THnBase.h"
#include "matrixLUTreader_Weights.C"

void matrixLUTreader(){
  cout<<"matrixLUTreader begin"<<endl;

  TFile* fi = new TFile("Mu3MatrixLUT.root","READ");

  fi->ls();

  THnSparseF* LUT = (THnSparseF*)(fi->Get("Mu3MatrixLUT"));

  printTHn(LUT);

  cout<<"matrixLUTreader end"<<endl;
}
