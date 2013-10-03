#ifndef SignatureCutST_h
#define SignatureCutST_h

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

class SignatureCutST : public SignatureCut {
 public:
  SignatureCutST(double stlow = 0, double sthigh=-1,const char* name="sigcutST") : SignatureCut(name),m_SThigh(sthigh),m_STlow(stlow){ /* no-op */}
    //SignatureCutST(double stlow = 0, double sthigh=-1):SignatureCutST("sigcutST",stlow,sthigh) { /*no-op */ }
  virtual ~SignatureCutST(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const 
  {
    if(m_STlow > 0 && handler->getST() < m_STlow) return false;
    if(m_SThigh > 0 && handler->getST() > m_SThigh) return false;
    return true;
  }
  virtual bool operator()(BaseHandler*) const;

 private:
  double m_SThigh;
  double m_STlow;

  ClassDef(SignatureCutST,1);

};

inline bool SignatureCutST::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
