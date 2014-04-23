#ifndef Signature_h
#define Signature_h

#include <iostream>
#include <TObject.h>
#include <TROOT.h>
#include <vector>
#include <map>
#include <algorithm>

class TString;
class BaseHandler;
class SignatureTH1F;
class SignatureTH2F;
class SignatureTH3F;

class Signature : public TObject {

 public:

  //functions
  Signature(TString,TString options=""); //constructor
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
  Signature* addCut(TString);
  std::vector<TString> getCuts() const{return m_Cuts;}
  
  /////////////////////////////////////
  //Manage communication with Handler//
  /////////////////////////////////////
  void setHandler(BaseHandler* sigHandler) {m_handler = sigHandler;}
  bool isSignature();

  /////////////////////
  //Manage Histograms//
  /////////////////////
  void fillHistograms();
  virtual void init(); //initialize
  virtual void finish();
  Signature* addHistogram(SignatureTH1F* c){m_1dhistograms.push_back(c); return this;}
  Signature* addHistogram(SignatureTH2F* c){m_2dhistograms.push_back(c); return this;}
  Signature* addHistogram(SignatureTH3F* c){m_3dhistograms.push_back(c); return this;}
  void setDoEventDump(bool c = true){m_doEventDump = c;}

 protected:



 private:
  BaseHandler* m_handler;
  std::vector<TString> m_Cuts;
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
