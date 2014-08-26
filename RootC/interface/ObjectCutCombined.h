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
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObject.h"

using namespace std;

class ObjectCutCombined : public ObjectCut {
 public:
  ObjectCutCombined(ObjectCut* cut1, ObjectCut* cut2, bool doAnd=false, const char* name="combinedcut") : ObjectCut(name),m_and(doAnd){
    m_cuts.push_back(cut1);
    m_cuts.push_back(cut2);
  }
    //ObjectCutCombined(double ptlow = 8.,double pthigh = -1):ObjectCutCombined("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectCutCombined(){}

  void addCut(ObjectCut* cut){m_cuts.push_back(cut);}

  bool passCut(SignatureObject* sigObj) const
  {
    bool retval = m_and;
    for(int i = 0; i < (int)m_cuts.size(); i++){
      bool passVal = (m_cuts[i]->passCut(sigObj));
      if(m_and)retval = retval && passVal;
      else retval = retval || passVal;
      //cout<<"    "<<m_cuts[i]->getName()<<" "<<(int)passVal<<endl;
    }
    return retval;
  }
  bool operator()(SignatureObject*) const;

 private:
  std::vector<ObjectCut*> m_cuts;
  bool m_and;//true = satisfy and, false = satisfy or

  ClassDef(ObjectCutCombined,1);

};

inline bool ObjectCutCombined::operator()(SignatureObject* sigobj) const
{
  return passCut(sigobj);
}
#endif
