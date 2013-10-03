#ifndef Signature_h
#define Signature_h

#include <string>
#include <iostream>
#include <sstream>
#include <TObject.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH3F.h"

class SignatureCut;
class BaseHandler;
class SignatureTH1F;
class SignatureTH2F;
class SignatureTH3F;

class Signature : public TObject {

 public:

  //functions
  Signature(const char*,const char*); //constructor
  Signature(const Signature&);//copy constructor
  virtual ~Signature(); //destructor
  TString getName() const {return m_name; }
  using TObject::GetName;
  const char* GetName() {return m_name.Data();}
  void setName(TString name){m_name = name;}

  //////////////////////////////////
  //Manage Definition of Signature//
  //////////////////////////////////
  void parseOptions();
  void addCut(SignatureCut* cut){m_Cuts.push_back(cut);}
  std::vector<SignatureCut*> getCuts() const{return m_Cuts;}
  
  /////////////////////////////////////
  //Manage communication with Handler//
  /////////////////////////////////////
  void setHandler(BaseHandler* sigHandler) {m_handler = sigHandler;}
  bool isSignature(BaseHandler*);
  bool isSignature();

  /////////////////////
  //Manage Histograms//
  /////////////////////
  void fillHistograms();
  virtual void init(); //initialize
  virtual void finish();
  void addBasicHistograms();
  void addChargeSignHistograms();
  void addFakeStudyHistograms();
  void addHistogram(SignatureTH1F* c){m_1dhistograms.push_back(c);}
  void addHistogram(SignatureTH2F* c){m_2dhistograms.push_back(c);}
  void addHistogram(SignatureTH3F* c){m_3dhistograms.push_back(c);}
  void setDoEventDump(bool c = true){m_doEventDump = c;}

 protected:



 private:
  BaseHandler* m_handler;
  std::vector<SignatureCut*> m_Cuts;
  int m_isInit,m_isFinish;
  TString m_name;
  TString m_options;

  bool m_doEventDump;

  std::vector<SignatureTH1F*> m_1dhistograms;
  std::vector<SignatureTH2F*> m_2dhistograms;
  std::vector<SignatureTH3F*> m_3dhistograms;

  ClassDef(Signature,1);

};


#endif
