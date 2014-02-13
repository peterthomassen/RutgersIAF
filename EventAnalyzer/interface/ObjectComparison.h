#ifndef ObjectComparison_h
#define ObjectComparison_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>

class SignatureObject;

class ObjectComparison : public TObject{
 public:
  ObjectComparison(TString name):m_name(name){}
  virtual ~ObjectComparison() {}

  virtual bool passCut(SignatureObject*,SignatureObject*) const = 0;
  virtual bool operator()(SignatureObject*,SignatureObject*) const = 0;
  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;

  ClassDef(ObjectComparison,1);
};

#endif
