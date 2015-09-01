#ifndef ObjectAssociationVariableMatch_h
#define ObjectAssociationVariableMatch_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociation.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class ObjectAssociationVariableMatch : public ObjectAssociation {
 public:
 ObjectAssociationVariableMatch(TString varname, TString assocvarname="", TString name="objectcomparisonmatchdeltar"): ObjectAssociation(name),m_varName(varname),m_assocVarName(assocvarname)
  {
    if(m_assocVarName == ""){
      m_assocVarName = m_varName;
    }
  }
  virtual ~ObjectAssociationVariableMatch() {}

  virtual std::pair<bool,double> passCut(SignatureObject* a,SignatureObject* b) const {
    T aa;
    T bb;
    bool a_isSet = a->getVariable(m_varName,aa);
    bool b_isSet = b->getVariable(m_assocVarName,bb);
    if(!a_isSet || !b_isSet)return std::make_pair(false,1e6);
    if(aa == bb)return std::make_pair(true,0);
    return std::make_pair(false,1e6);
  }
  virtual std::pair<bool,double> operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  TString m_varName;
  TString m_assocVarName;

  ClassDef(ObjectAssociationVariableMatch,1);
};

#endif
