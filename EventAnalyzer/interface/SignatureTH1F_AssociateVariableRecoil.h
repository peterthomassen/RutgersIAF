#ifndef SignatureTH1F_AssociateVariableRecoil_h
#define SignatureTH1F_AssociateVariableRecoil_h

#include <TH1F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class SignatureTH1F_AssociateVariableRecoil : public SignatureTH1F {
public:
  
 SignatureTH1F_AssociateVariableRecoil(const char* name, TString productname, TString associatename, const char* title = "N Distribution", int nbins = 20, double xmin = -0.5, double xmax = 19.5):SignatureTH1F(name,title,nbins,xmin,xmax),m_associatename(associatename){ m_productnames.push_back(productname);}
    
  SignatureTH1F_AssociateVariableRecoil(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_AssociateVariableRecoil():SignatureTH1F() {}
	
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
	TVector3 p = TLorentzVector(*v[j]).Vect(); //Product 3-Vector
	TVector3 a = TLorentzVector(*associate).Vect(); //Associate 3-Vector
        double value;
        value = (a - p*((p*a)/(p*p))).Mag();
        dummy = TH1F::Fill(value,handler->getPhysicsWeight());
      }
    }
    return dummy;
  }

  virtual void Copy(TObject& hnew) const
  {
    TH1F::Copy(hnew);
    ((SignatureTH1F_AssociateVariableRecoil&)hnew).m_associatename = m_associatename;
    ((SignatureTH1F_AssociateVariableRecoil&)hnew).m_productnames = m_productnames;

  }

  ClassDef(SignatureTH1F_AssociateVariableRecoil,1);

 protected:
  TString m_associatename;
  std::vector<TString> m_productnames;
};

#endif
