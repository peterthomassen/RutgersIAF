#ifndef SignatureCutMET_h
#define SignatureCutMET_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"

class SignatureCutMET : public SignatureCut {
 public:
  SignatureCutMET(double metlow = 0, double methigh=-1,const char* name="sigcutMET") : SignatureCut(name),m_METhigh(methigh),m_METlow(metlow){ /* no-op */}
    //SignatureCutMET(double metlow = 0, double methigh=-1):SignatureCutMET("sigcutMET",metlow,methigh) { /*no-op */ }
    virtual ~SignatureCutMET(){/* no-op*/}

  bool passCut(BaseHandler* handler) const 
  {
    if(m_METlow > 0 && handler->getPFMET() < m_METlow) return false;
    if(m_METhigh > 0 && handler->getPFMET() > m_METhigh) return false;
    return true;
  }
  bool operator()(BaseHandler*) const;

 private:
  double m_METhigh;
  double m_METlow;

  ClassDef(SignatureCutMET,1);

};

inline bool SignatureCutMET::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
