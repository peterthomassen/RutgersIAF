#ifndef SignatureCutFilter_h
#define SignatureCutFilter_h

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

class SignatureCutFilter : public SignatureCut {
 public:
  SignatureCutFilter(TString filterName,bool passFilter=true, const char* name="filtercut") : SignatureCut(name),m_filterName(filterName),m_passFilter(passFilter){ /*no-op*/}
    //SignatureCutFilter(double ptlow = 8.,double pthigh = -1):SignatureCutFilter("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~SignatureCutFilter(){}

  bool passCut(BaseHandler* sigObj) const
  {
    return (((SignatureHandler*)sigObj)->passFilter(m_filterName) == m_passFilter);
  }
  bool operator()(BaseHandler*) const;

 private:
  TString m_filterName;
  bool m_passFilter;

  ClassDef(SignatureCutFilter,1);

};

inline bool SignatureCutFilter::operator()(BaseHandler* sigobj) const
{
  return passCut(sigobj);
}
#endif
