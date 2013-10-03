#ifndef SignatureCutTrigger_h
#define SignatureCutTrigger_h

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
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"
#include "RutgersIAF2012/RootC/interface/SignatureTrigger.h"

class SignatureCutTrigger : public SignatureCut {
 public:
  SignatureCutTrigger(bool usePrescaled=false,const char* name="sigcuttrigger") : SignatureCut(name),m_usePrescaled(usePrescaled){ /* no-op */}
    //SignatureCutTrigger(double nlow = 0, double nhigh=-1):SignatureCutTrigger("sigcutn",nlow,nhigh) { /*no-op */ }
  virtual ~SignatureCutTrigger(){ /* no-op */ }

  virtual void addCut(TString name, SignatureCut* s);
  virtual void addVetoTrigger(TString name, int c);
  virtual void addAcceptTrigger(TString name, int c);
  virtual void addVetoTrigger(TString name, TString c);
  virtual void addAcceptTrigger(TString name, TString c);
  virtual bool passCut(BaseHandler* handler) const ;
  virtual bool operator()(BaseHandler*) const;

 private:
  bool m_usePrescaled;
  std::map<TString,SignatureCut*> m_map_cuts;
  std::map<TString,std::vector<int> > m_veto_int;
  std::map<TString,std::vector<int> > m_accept_int;
  std::map<TString,std::vector<TString> > m_veto_TString;
  std::map<TString,std::vector<TString> > m_accept_TString;

  ClassDef(SignatureCutTrigger,1);

};

inline bool SignatureCutTrigger::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
