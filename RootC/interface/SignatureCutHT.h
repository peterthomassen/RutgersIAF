#ifndef SignatureCutHT_h
#define SignatureCutHT_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"

class SignatureCutHT : public SignatureCut {
 public:
  SignatureCutHT(double htlow = 0, double hthigh=-1,const char* name="sigcutHT") : SignatureCut(name),m_HThigh(hthigh),m_HTlow(htlow){ /* no-op */}
    //SignatureCutHT(double htlow = 0, double hthigh=-1):SignatureCutHT("sigcutHT",htlow,hthigh) { /*no-op */ }
  virtual ~SignatureCutHT(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const 
  {
    if(m_HTlow > 0 && handler->getHT() < m_HTlow) return false;
    if(m_HThigh > 0 && handler->getHT() > m_HThigh) return false;
    return true;
  }
  virtual bool operator()(BaseHandler*) const;

 private:
  double m_HThigh;
  double m_HTlow;

  ClassDef(SignatureCutHT,1);

};

inline bool SignatureCutHT::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
