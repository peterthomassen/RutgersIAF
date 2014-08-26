#include "RutgersIAF/RootC/interface/SignatureTH2F_METxy.h"

ClassImp(SignatureTH2F_METxy)

Int_t SignatureTH2F_METxy::Fill(BaseHandler* handler)
{
  return Fill(dynamic_cast<SignatureHandler*>(handler));

}
Int_t SignatureTH2F_METxy::Fill(SignatureHandler* handler)
{
  return TH2F::Fill(handler->getPFMET()*cos(handler->pf_met_phi),handler->getPFMET()*sin(handler->pf_met_phi),handler->getPhysicsWeight());

}
