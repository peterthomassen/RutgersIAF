#ifndef ObjectVariableRename_h
#define ObjectVariableRename_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class ObjectVariableRename : public ObjectVariable {
 public:
  ObjectVariableRename(TString cut1, const char* name="renamevar") : ObjectVariable(name),m_cut1(cut1){ /*no-op*/}
    //ObjectVariableRename(double ptlow = 8.,double pthigh = -1):ObjectVariableRename("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectVariableRename(){}

  bool calculate(SignatureObject* sigObj)
  {
    T retval;
    bool isSet = sigObj->getVariable(m_cut1,retval);
    if(isSet){
      sigObj->setVariable(getName(),retval);
      return true;
    }else{
      return false;
    }
  }

 private:
  TString m_cut1;

  ClassDef(ObjectVariableRename,1);

};

#endif
