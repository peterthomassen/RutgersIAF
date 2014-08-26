#ifndef VertexCut_h
#define VertexCut_h

#include <string>
#include <iostream>
#include <sstream>
#include <TObject.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
//#include "RutgersIAF/RootC/interface/BaseHandler.h"

class SignatureRecoVertex;

class VertexCut : public TObject {
 public:
  VertexCut(const char*);
  virtual ~VertexCut();

  virtual bool passCut(SignatureRecoVertex*) const = 0;
  virtual bool operator()(SignatureRecoVertex*) const = 0;
  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;

  ClassDef(VertexCut,1);

};

#endif
