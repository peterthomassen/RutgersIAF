#ifndef ObjectVariable_h
#define ObjectVariable_h

#include <string>
#include <iostream>
#include <sstream>
#include <TObject.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>

class SignatureObject;

class ObjectVariable : public TObject {
 public:
  ObjectVariable(TString name):m_name(name){}
  virtual ~ObjectVariable() {}

  virtual bool calculate(SignatureObject*) = 0;
  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;


  ClassDef(ObjectVariable,1);

};

#endif
