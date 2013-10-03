#include "RutgersIAF2012/RootC/interface/ObjectCutElectronMVA.h"

ClassImp(ObjectCutElectronMVA)

using namespace std;

ObjectCutElectronMVA::ObjectCutElectronMVA(float nMVAmin, float nMVAmax,bool useTrig, const char* name ):ObjectCut(name),m_nMVAmin(nMVAmin),m_nMVAmax(nMVAmax),m_useTrig(useTrig)
{
}

bool ObjectCutElectronMVA::passCut(SignatureObjectElectron* sigObj)const
{
  double mvaVal = -999.;
  if(m_useTrig)mvaVal = sigObj->getMvaTrig();
  else mvaVal = sigObj->getMvaNoTrig();  
  //std::cout<<mvaVal<<std::endl;
  if(mvaVal < m_nMVAmin)return false;
  if(mvaVal > m_nMVAmax)return false;

  return true;
}

