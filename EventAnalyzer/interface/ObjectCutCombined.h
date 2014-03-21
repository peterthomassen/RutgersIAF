#ifndef ObjectCutCombined_h
#define ObjectCutCombined_h

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

using namespace std;

class ObjectCutCombined : public ObjectCut {
 public:
  ObjectCutCombined(TString cut1, TString cut2, bool doAnd=false, const char* name="combinedcut") : ObjectCut(name),m_and(doAnd){
    m_cuts.push_back(cut1);
    m_cuts.push_back(cut2);
  }
    //ObjectCutCombined(double ptlow = 8.,double pthigh = -1):ObjectCutCombined("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectCutCombined(){}

  void addCut(TString cut){m_cuts.push_back(cut);}

  bool passCut(SignatureObject* sigObj)
  {
    bool retval = m_and;
    for(int i = 0; i < (int)m_cuts.size(); i++){
      bool passVal = false;
      bool isSet = sigObj->getVariable(m_cuts[i],passVal);
      if(m_and)retval = retval && passVal && isSet;
      else retval = retval || (passVal && isSet);
      //cout<<"    "<<m_cuts[i]->getName()<<" "<<(int)passVal<<endl;
    }
    sigObj->setVariable(getName(),retval);
    return retval;
  }
  bool operator()(SignatureObject*);

 private:
  std::vector<TString> m_cuts;
  bool m_and;//true = satisfy and, false = satisfy or

  ClassDef(ObjectCutCombined,1);

};

inline bool ObjectCutCombined::operator()(SignatureObject* sigobj)
{
  return passCut(sigobj);
}
#endif
