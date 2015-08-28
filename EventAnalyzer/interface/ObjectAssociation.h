#ifndef ObjectAssociation_h
#define ObjectAssociation_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include <utility>

class SignatureObject;

class ObjectAssociation : public TObject{
 public:
  ObjectAssociation(TString name):m_name(name){}
  virtual ~ObjectAssociation() {}

  virtual std::pair<bool,double> passCut(SignatureObject*,SignatureObject*) const = 0;
  virtual std::pair<bool,double> operator()(SignatureObject*,SignatureObject*) const = 0;
  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;

  ClassDef(ObjectAssociation,1);
};

#endif
