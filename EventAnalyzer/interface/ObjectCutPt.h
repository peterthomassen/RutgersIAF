#ifndef ObjectCutPt_h
#define ObjectCutPt_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectCut.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

class ObjectCutPt : public ObjectCut {
 public:
  ObjectCutPt(double low=0, double high=100000,TString name="ptcut") : ObjectCut(name),m_low(low),m_high(high){ /*no-op*/}
    
  virtual ~ObjectCutPt(){}

  bool passCut(SignatureObject* sigObj)
  {
    double value = sigObj->Pt();
    if(value < m_low){
      sigObj->setVariable(getName(),false);
      return false;
    }
    if(value > m_high){
      sigObj->setVariable(getName(),false);
      return false;
    }
    sigObj->setVariable(getName(),true);
    return true;
  }
  bool operator()(SignatureObject* sigObj)
  {
    return passCut(sigObj);
  }

 private:
  double m_low;
  double m_high;

  ClassDef(ObjectCutPt,1);

};

#endif
