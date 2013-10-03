#include "RutgersIAF2012/RootC/interface/ObjectCutAbsRelTau.h"

ClassImp(ObjectCutAbsRelTau)

double  ObjectCutAbsRelTau::calcAbsRel(SignatureObjectTau* tau) const
{
  double neutIso = tau->getPF_neutralHadronIso05();
  double charIso = tau->getPF_chargedHadronIso05();
  if (neutIso < 0)neutIso = 0;
  if(charIso< 0)charIso = 0;
  return neutIso + charIso;
}
