#ifndef ObjectVariablePtInRange_h
#define ObjectVariablePtInRange_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"


class ObjectVariablePtInRange : public ObjectVariable {
 public:
  ObjectVariablePtInRange(double low=0, double high=100000,TString name="ptinrangecut") : ObjectVariable(name),m_low(low),m_high(high){/*no-op*/}
    
  virtual ~ObjectVariablePtInRange(){}

  bool calculate(SignatureObject* sigObj)
  {
    double value = sigObj->Pt();
    bool retval = true;
    if(value < m_low)retval = false;
    if(value > m_high)retval = false;
    sigObj->setVariable(getName(),retval);
    return retval;
  }

 private:
  double m_low;
  double m_high;

  ClassDef(ObjectVariablePtInRange,1);

};

#endif
