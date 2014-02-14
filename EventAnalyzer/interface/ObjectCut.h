#ifndef ObjectCut_h
#define ObjectCut_h

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

class ObjectCut : public TObject {
 public:
  ObjectCut(TString name):m_name(name){}
  virtual ~ObjectCut() {}

  virtual bool passCut(SignatureObject*) const = 0;
  virtual bool operator()(SignatureObject*) const = 0;
  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;


  ClassDef(ObjectCut,1);

};

#endif
