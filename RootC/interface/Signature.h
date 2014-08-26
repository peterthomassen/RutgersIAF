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
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF/RootC/interface/SignatureTH3F.h"

class SignatureCut;
class BaseHandler;
class SignatureTH1F;
class SignatureTH2F;
class SignatureTH3F;

class Signature : public TObject {

 public:

  //functions
  Signature(const char* name = "sig",const char* options = ""); //constructor
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
  Signature* addCut(SignatureCut* cut){m_Cuts.push_back(cut); return this;}
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
  Signature* addHistogram(SignatureTH1F* c){if(find(m_1dhistograms.begin(),m_1dhistograms.end(),c) == m_1dhistograms.end())m_1dhistograms.push_back(c); return this;}
  Signature* addHistogram(SignatureTH2F* c){if(find(m_2dhistograms.begin(),m_2dhistograms.end(),c) == m_2dhistograms.end())m_2dhistograms.push_back(c); return this;}
  Signature* addHistogram(SignatureTH3F* c){if(find(m_3dhistograms.begin(),m_3dhistograms.end(),c) == m_3dhistograms.end())m_3dhistograms.push_back(c); return this;}
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
