#include "RutgersIAF/RootC/interface/SignatureTH2F_METvsMT.h"

ClassImp(SignatureTH2F_METvsMT)
using namespace std;

Int_t SignatureTH2F_METvsMT::Fill(BaseHandler* handler)
{
  return TH2F::Fill(handler->getMT(),handler->getPFMET(),handler->getPhysicsWeight());

}
