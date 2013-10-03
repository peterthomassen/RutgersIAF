#ifndef SignatureCut_h
#define SignatureCut_h

#include <string>
#include <iostream>
#include <sstream>
#include <TObject.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
//#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"

class BaseHandler;

class SignatureCut : public TObject {
 public:
  SignatureCut(const char*);
  virtual ~SignatureCut();

  virtual bool passCut(BaseHandler*) const = 0;
  virtual bool operator()(BaseHandler*) const = 0;
  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;

  ClassDef(SignatureCut,1);

};

#endif
