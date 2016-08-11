#include "TLorentzVector.h"

double DR( double eta1=0, double phi1=0, double eta2=0, double phi2=0 )
{
  TLorentzVector* vec1 = new TLorentzVector();
  TLorentzVector* vec2 = new TLorentzVector();
  vec1->SetPtEtaPhiM(1, eta1, phi1, 0);
  vec2->SetPtEtaPhiM(1, eta2, phi2, 0);
  return fabs(vec1->DeltaR(*vec2));
}

double DPhi( double phi1=0, double phi2=0 )
{
  TLorentzVector* vec1 = new TLorentzVector();
  TLorentzVector* vec2 = new TLorentzVector();
  vec1->SetPtEtaPhiM(1, 0, phi1, 0);
  vec2->SetPtEtaPhiM(1, 0, phi2, 0);
  return fabs(vec1->DeltaPhi(*vec2));
}
