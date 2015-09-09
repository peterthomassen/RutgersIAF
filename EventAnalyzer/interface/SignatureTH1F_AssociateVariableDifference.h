#ifndef SignatureTH1F_AssociateVariableDifference_h
#define SignatureTH1F_AssociateVariableDifference_h

#include <TH1F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class SignatureTH1F_AssociateVariableDifference : public SignatureTH1F {
public:
  
 SignatureTH1F_AssociateVariableDifference(const char* name, TString varname, TString productname, TString associatename, int doFractionalMode=0,const char* title = "N Distribution", int nbins = 20, double xmin = -0.5, double xmax = 19.5):SignatureTH1F(name,title,nbins,xmin,xmax),m_varname(varname),m_associatename(associatename),m_doFractionalMode(doFractionalMode){ m_productnames.push_back(productname);}
    
  SignatureTH1F_AssociateVariableDifference(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_AssociateVariableDifference():SignatureTH1F() {}
	
  void addProduct(TString pname)
  {
    if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
  }


  using TH1F::Fill;
  Int_t Fill(BaseHandler* handler)
  {
    Int_t dummy = -1;
    
    for(int i = 0; i < (int)m_productnames.size(); i++){
      std::vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
      for(int j = 0; j < (int)v.size(); j++){
	SignatureObject* associate = v[j]->getAssociate(m_associatename);
	if(!associate)continue;
	T valueAssociate = 0;
	bool isSetAssociate = associate->getVariable(m_varname,valueAssociate);
	T valueObject = 0;
	bool isSetObject = v[j]->getVariable(m_varname,valueObject);
	if(isSetAssociate && isSetObject){
	  switch (m_doFractionalMode){
	  case 0:
	    dummy = TH1F::Fill(valueObject-valueAssociate,handler->getPhysicsWeight());
	    break;
	  case 1:
	    if(valueAssociate != 0){
	      dummy = TH1F::Fill((valueObject-valueAssociate)/valueAssociate,handler->getPhysicsWeight());
	    }
	    break;
	  case 2:
	    if(valueObject != 0){
	      dummy = TH1F::Fill((valueObject-valueAssociate)/valueObject,handler->getPhysicsWeight());
	    }
	    break;
	  default:
	    break;
	  }
	}
      }
    }
    return dummy;
  }

  virtual void Copy(TObject& hnew) const
  {
    TH1F::Copy(hnew);
    ((SignatureTH1F_AssociateVariableDifference<T>&)hnew).m_varname = m_varname;
    ((SignatureTH1F_AssociateVariableDifference<T>&)hnew).m_associatename = m_associatename;
    ((SignatureTH1F_AssociateVariableDifference<T>&)hnew).m_doFractionalMode = m_doFractionalMode;
    ((SignatureTH1F_AssociateVariableDifference<T>&)hnew).m_productnames = m_productnames;

  }

  ClassDef(SignatureTH1F_AssociateVariableDifference,1);

 protected:
  TString m_varname;
  TString m_associatename;
  int m_doFractionalMode; //0 = no fractional, 1 = associate denom, 2 = object denom
  std::vector<TString> m_productnames;
};

#endif
