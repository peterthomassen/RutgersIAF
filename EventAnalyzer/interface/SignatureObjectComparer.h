#ifndef SignatureObjectComparer_h
#define SignatureObjectComparer_h
#include <TROOT.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class SignatureObjectComparer {
 public:
 SignatureObjectComparer(TString varname) : m_varname(varname){}
  virtual ~SignatureObjectComparer(){}

  bool operator ()(const SignatureObject *a, SignatureObject *b)
  {
    T aval = 0;
    T bval = 0;
    bool a_isSet = a->getVariable(m_varname,aval);
    bool b_isSet = b->getVariable(m_varname,bval);
    
    if(a_isSet && b_isSet)return aval < bval;
    else if(!a_isSet && !b_isSet)return a->Pt() < b->Pt();
    else return b_isSet;
  }

 private:
  TString m_varname;

};


#endif
