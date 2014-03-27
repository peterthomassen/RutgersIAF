#ifndef ObjectVariableLorentzVectorInRange_h
#define ObjectVariableLorentzVectorInRange_h

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

typedef double (TLorentzVector::*SOfunction) ();

class ObjectVariableLorentzVectorInRange : public ObjectVariable {
 public:
  ObjectVariableLorentzVectorInRange(SOfunction func, double low=0, double high=100000,TString name="variableinrangecut") : ObjectVariable(name),m_low(low),m_high(high){m_function = func;}
    
  virtual ~ObjectVariableLorentzVectorInRange(){}

  bool calculate(SignatureObject* sigObj)
  {
    double value = ((TLorentzVector*)sigObj->*m_function)();
    bool retval = true;
    if(value < m_low)retval = false;
    if(value > m_high)retval = false;
    sigObj->setVariable(getName(),retval);
    return retval;
  }

 private:
  SOfunction m_function;
  double m_low;
  double m_high;

  ClassDef(ObjectVariableLorentzVectorInRange,1);

};

#endif
