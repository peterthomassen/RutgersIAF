#include "RutgersIAF2012/RootC/interface/SignatureTH2F_METvsMll.h"

ClassImp(SignatureTH2F_METvsMll)
using namespace std;

Int_t SignatureTH2F_METvsMll::Fill(BaseHandler* handler)
{
  return TH2F::Fill(handler->getMLL(),handler->getPFMET(),handler->getPhysicsWeight());

}
