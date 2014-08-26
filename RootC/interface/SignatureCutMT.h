#ifndef SignatureCutMT_h
#define SignatureCutMT_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"

class SignatureCutMT : public SignatureCut {
 public:
  SignatureCutMT(double metlow = 0, double methigh=-1,const char* name="sigcutMT") : SignatureCut(name),m_MThigh(methigh),m_MTlow(metlow){ /* no-op */}
    //SignatureCutMT(double metlow = 0, double methigh=-1):SignatureCutMT("sigcutMT",metlow,methigh) { /*no-op */ }
    virtual ~SignatureCutMT(){/* no-op*/}

  bool passCut(BaseHandler* handler) const 
  {
    if(m_MTlow > 0 && handler->getMT() < m_MTlow) return false;
    if(m_MThigh > 0 && handler->getMT() > m_MThigh) return false;
    return true;
  }
  bool operator()(BaseHandler*) const;

 private:
  double m_MThigh;
  double m_MTlow;

  ClassDef(SignatureCutMT,1);

};

inline bool SignatureCutMT::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
