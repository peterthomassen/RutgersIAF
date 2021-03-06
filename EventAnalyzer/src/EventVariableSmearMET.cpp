#include "RutgersIAF/EventAnalyzer/interface/EventVariableSmearMET.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
using namespace std;

ClassImp(EventVariableSmearMET)

bool EventVariableSmearMET::calculate(BaseHandler* handler)
{
  int nv = 0;
  double ht = 0;

  if(!handler->getVariable(m_htname,ht))return false;
  if(!handler->getVariable(m_nvname,nv))return false;

  double smearSigma = sqrt( max(pow(m_data_sigma0,2) - pow(m_mc_sigma0,2),0.0) + max(pow(m_data_sigmaHT,2) - pow(m_mc_sigmaHT,2),0.0) * ht/30.0 + max(pow(m_data_sigmaNV,2) - pow(m_mc_sigmaNV,2),0.0) * double(nv));

  double ptsum = 0;
  double pxsum = 0,pysum = 0;
  vector<SignatureObject*> v = handler->getProduct(m_productname);
  for(int j = 0; j < (int)v.size(); j++){
    double px = v[j]->X();
    double py = v[j]->Y();
    px += m_random.Gaus(0,smearSigma);
    py += m_random.Gaus(0,smearSigma);
    pxsum += px;
    pysum += py;
    ptsum += pow(px,2)+pow(py,2);
    v[j]->SetX(px);
    v[j]->SetY(py);
  }
  handler->setVariable(getName(),sqrt(ptsum));
  handler->setVariable(getName()+"SMEAREDPX",pxsum);
  handler->setVariable(getName()+"SMEAREDPY",pysum);
  return true;
}
