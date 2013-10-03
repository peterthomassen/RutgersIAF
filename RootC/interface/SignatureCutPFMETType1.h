#ifndef SignatureCutPFMETType1_h
#define SignatureCutPFMETType1_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"

class SignatureCutPFMETType1 : public SignatureCut {
 public:
  SignatureCutPFMETType1(double metlow = 0, double methigh=-1,const char* name="sigcutPFMETType1") : SignatureCut(name),m_METhigh(methigh),m_METlow(metlow){ /* no-op */}
    //SignatureCutPFMETType1(double metlow = 0, double methigh=-1):SignatureCutPFMETType1("sigcutPFMETType1",metlow,methigh) { /*no-op */ }
    virtual ~SignatureCutPFMETType1(){/* no-op*/}

  bool passCut(SignatureHandler* handler) const 
  {
    if(m_METlow > 0 && handler->pf_met_type1_pt < m_METlow) return false;
    if(m_METhigh > 0 && handler->pf_met_type1_pt > m_METhigh) return false;
    return true;
  }
  bool operator()(SignatureHandler*) const;

 private:
  double m_METhigh;
  double m_METlow;

  ClassDef(SignatureCutPFMETType1,1);

};

inline bool SignatureCutPFMETType1::operator()(SignatureHandler* handler)const
{
  return passCut(handler);
}
#endif
