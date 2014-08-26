#ifndef SignatureCutReversed_h
#define SignatureCutReversed_h

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

class SignatureCutReversed : public SignatureCut {
 public:
  SignatureCutReversed(SignatureCut* cut1, const char* name="reversedcut") : SignatureCut(name),m_cut1(cut1){ /*no-op*/}
    //SignatureCutReversed(double ptlow = 8.,double pthigh = -1):SignatureCutReversed("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~SignatureCutReversed(){}

  bool passCut(BaseHandler* sigObj) const
  {
    return !(m_cut1->passCut(sigObj));
  }
  bool operator()(BaseHandler*) const;

 private:
  SignatureCut* m_cut1;

  ClassDef(SignatureCutReversed,1);

};

inline bool SignatureCutReversed::operator()(BaseHandler* sigobj) const
{
  return passCut(sigobj);
}
#endif
