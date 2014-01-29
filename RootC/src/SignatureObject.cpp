#include "RutgersIAF2012/RootC/interface/SignatureObject.h"

ClassImp(SignatureObject)

bool SignatureObjectComparison(SignatureObject* a, SignatureObject* b)
{
  return a->Pt() < b->Pt();
}
