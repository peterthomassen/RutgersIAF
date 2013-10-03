#ifndef SignatureCutCombined_h
#define SignatureCutCombined_h

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

class SignatureCutCombined : public SignatureCut {
 public:
  SignatureCutCombined(SignatureCut* cut1, SignatureCut* cut2, bool doAnd=false, const char* name="combinedcut") : SignatureCut(name),m_cut1(cut1),m_cut2(cut2),m_and(doAnd){ /*no-op*/}
    //SignatureCutCombined(double ptlow = 8.,double pthigh = -1):SignatureCutCombined("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~SignatureCutCombined(){}

  bool passCut(BaseHandler* sigObj) const
  {
    if(m_and)return (m_cut1->passCut(sigObj) && m_cut2->passCut(sigObj));
    if(!m_and)return (m_cut1->passCut(sigObj) || m_cut2->passCut(sigObj));
    return true;
  }
  bool operator()(BaseHandler*) const;

 private:
  SignatureCut* m_cut1;
  SignatureCut* m_cut2;
  bool m_and;//true = satisfy and, false = satisfy or

  ClassDef(SignatureCutCombined,1);

};

inline bool SignatureCutCombined::operator()(BaseHandler* sigobj) const
{
  return passCut(sigobj);
}
#endif
