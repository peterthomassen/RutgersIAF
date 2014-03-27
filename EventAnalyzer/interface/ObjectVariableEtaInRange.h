#ifndef ObjectVariableEtaInRange_h
#define ObjectVariableEtaInRange_h

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


class ObjectVariableEtaInRange : public ObjectVariable {
 public:
  ObjectVariableEtaInRange(double low=-2.5, double high=2.5,TString name="ptinrangecut") : ObjectVariable(name),m_low(low),m_high(high){/*no-op*/}
    
  virtual ~ObjectVariableEtaInRange(){}

  bool calculate(SignatureObject* sigObj)
  {
    double value = sigObj->Eta();
    bool retval = true;
    if(value < m_low)retval = false;
    if(value > m_high)retval = false;
    sigObj->setVariable(getName(),retval);
    return retval;
  }

 private:
  double m_low;
  double m_high;

  ClassDef(ObjectVariableEtaInRange,1);

};

#endif
