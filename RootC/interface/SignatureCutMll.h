#ifndef SignatureCutMll_h
#define SignatureCutMll_h

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

class SignatureCutMll : public SignatureCut {
 public:
  SignatureCutMll(double metlow = 12, double methigh=-1,const char* name="sigcutMll") : SignatureCut(name),m_Mllhigh(methigh),m_Mlllow(metlow){ /* no-op */}
    //SignatureCutMll(double metlow = 0, double methigh=-1):SignatureCutMll("sigcutMll",metlow,methigh) { /*no-op */ }
    virtual ~SignatureCutMll(){/* no-op*/}

  bool passCut(BaseHandler* handler) const 
  {
    if(m_Mlllow > 0 && handler->getMLL() < m_Mlllow) return false;
    if(m_Mllhigh > 0 && handler->getMLL() > m_Mllhigh) return false;
    return true;
  }
  bool operator()(BaseHandler*) const;

 private:
  double m_Mllhigh;
  double m_Mlllow;

  ClassDef(SignatureCutMll,1);

};

inline bool SignatureCutMll::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
