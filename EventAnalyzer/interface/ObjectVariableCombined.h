#ifndef ObjectVariableCombined_h
#define ObjectVariableCombined_h

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

using namespace std;

class ObjectVariableCombined : public ObjectVariable {
 public:
  ObjectVariableCombined(TString cut1, TString cut2, bool doAnd=false, const char* name="combinedcut") : ObjectVariable(name),m_and(doAnd){
    m_cuts.push_back(cut1);
    m_cuts.push_back(cut2);
  }
    //ObjectVariableCombined(double ptlow = 8.,double pthigh = -1):ObjectVariableCombined("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectVariableCombined(){}

  void addVariable(TString cut){m_cuts.push_back(cut);}

  bool calculate(SignatureObject* sigObj)
  {
    bool retval = m_and;
    for(int i = 0; i < (int)m_cuts.size(); i++){
      bool passVal = false;
      bool isSet = sigObj->getVariable(m_cuts[i],passVal);
      if(m_and)retval = retval && passVal && isSet;
      else retval = retval || (passVal && isSet);
      //cout<<"    "<<m_cuts[i]<<" "<<(int)passVal<<endl;
    }
    sigObj->setVariable(getName(),retval);
    return retval;
  }

 private:
  std::vector<TString> m_cuts;
  bool m_and;//true = satisfy and, false = satisfy or

  ClassDef(ObjectVariableCombined,1);

};

#endif
