#include "RutgersIAF2012/RootC/interface/SignatureTH2F_METxy.h"

ClassImp(SignatureTH2F_METxy)

Int_t SignatureTH2F_METxy::Fill(SignatureHandler* handler)
{
  return TH2F::Fill(handler->getPFMET()*cos(handler->pf_met_phi),handler->getPFMET()*sin(handler->pf_met_phi),handler->getPhysicsWeight());

}
