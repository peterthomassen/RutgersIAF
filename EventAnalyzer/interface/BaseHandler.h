#ifndef BaseHandler_h
#define BaseHandler_h


#include <iostream>
#include <TROOT.h>
#include <vector>
#include <map>
#include <TObject.h>
#include <string>

#include "Signature.h"

class SignatureWithBjets;
class SignatureTH1F;
class SignatureTH2F;
class SignatureTH3F;
class SignatureObject;
class SignatureBeamSpot;
class SignatureRecoVertex;
class SignatureTrigger;
class TFile;
class BaseTreeReader;
class BaseTreeWriter;
class SignatureTreeWriter;
class ObjectComparison;
class EventVariable;
class TH2F;
class ObjectVariable;

class BaseHandler : virtual public TObject {
 public:
  //default constructor
  BaseHandler(TString,BaseTreeReader*);
  //virtual destructor
  virtual ~BaseHandler();

  friend class SignatureTreeWriter;
  friend class PeterTreeWriter;

  ////////////////    
  //Manage Event//
  ////////////////
  virtual void eventLoop();
  void eventLoop(int runOnly, long int eventOnly);

  /////////////////////
  //Manage Signatures//
  /////////////////////


  virtual void initSignatures();
  virtual void finishSignatures();
  virtual void addHistogram(SignatureTH1F*);
  virtual void addHistogram(SignatureTH2F*);
  virtual void addHistogram(SignatureTH3F*);
  void addHistogram(SignatureTH1F*, TString signatureRegExp);
  void addHistogram(SignatureTH2F*, TString signatureRegExp);
  void addHistogram(SignatureTH3F*, TString signatureRegExp);

  virtual double getPhysicsWeight(){return m_physicsWeight;}
  virtual Signature* addSignature(const char* name, const char* option="");
  void addSignature(Signature* sig) {m_Signatures.push_back(sig);}
  void addPreCutSignature(const char*, const char*);
  void addPreCutSignature(Signature* sig){m_preHandlerCutSignatures.push_back(sig);}

  virtual bool passCut(TString);

  void addHandlerCut(TString);

  /////////////////////////////
  //Access physics quantities//
  /////////////////////////////
  virtual bool getDebugMode(){return m_debugMode;}
  virtual void setDebugMode(bool c=true){m_debugMode = c;}
  virtual void dumpEventInfo();
  virtual void printDebugInfo();

  virtual void addEventVariable(TString,EventVariable*,bool rename=true);
  EventVariable* getEventVariable(TString);

  virtual void addObjectVariable(TString,ObjectVariable*,bool rename=true);
  ObjectVariable* getObjectVariable(TString);

  virtual void setVariable(TString,double);
  virtual void setVariable(TString,int);
  virtual void setVariable(TString,long);
  virtual void setVariable(TString,TString);
  virtual void setVariable(TString,bool);

  virtual bool getVariable(TString,double&);
  virtual bool getVariable(TString,int&);
  virtual bool getVariable(TString,long&);
  virtual bool getVariable(TString,TString&);
  virtual bool getVariable(TString,bool&);

  virtual void addWeightVariable(TString);

  BaseTreeReader* getReader(){return m_reader;}
  BaseTreeWriter* getWriter(){return m_writer;}
  void setWriter(BaseTreeWriter* c){m_writer = c;}
  TFile* getOutFile(){return m_outFile;}

  void addDumpEvent(int,int,long);

  void setMode(std::string name, int mode = 1){m_mode[name] = mode;}
  int getMode(std::string name);

  void readGoodRunLumi(TString c);
  void readGoodRunLumiFromJSON(TString JSONFile, bool debug = false);
  void printRunLumiJSON();
  //////////////////////
  //Product Management//
  //////////////////////
  virtual std::vector<SignatureObject*> getProduct(TString);
  virtual bool isProductPresent(TString);
  void addProduct(TString,TString);
  void addProductCut(TString,TString);

  void addProductComparison(TString,TString,ObjectComparison*,bool doAnd=true);
  void addProductSelfComparison(TString,ObjectComparison*,bool doAnd=true);

 protected:
  virtual void createProducts();
  virtual void resetProducts();
  virtual void prepareEvent();
  virtual void calculateVariables();
  virtual void resetVariables();
  virtual void calcPhysicsWeight();
  bool applyHandlerCuts();
  virtual void analyzeEvent();

  virtual void printSignature(Signature*);

  std::map<int, std::map<int,std::vector<long> > > m_dumpList;

  bool m_doPriorityList;

  bool m_debugMode;

  bool m_isMC;
  TString m_MCtype;

  TString m_outFileName;
  
  double m_physicsWeight;

  int m_lastEntryPrepared;
  int m_currentEntry;
    
  std::map<int, std::vector<int> > m_goodRunLumi;
  bool m_doRunLumiCheck;
  std::multimap<int, std::vector<std::pair<int, int> > > m_json;
  bool m_doRunLumiCheckFromJSON;
  int m_checkedRun;
  int m_checkedLumi;
  bool m_isRunLumiGood;
  bool checkRunLumi(int r, int l);
  bool checkRunLumiFromJSON(int RunNumber, int LumiNumber, bool debug = false);
  
  std::map<std::string, int> m_mode;
  ////////////
  //Products//
  ////////////
  std::vector<TString> m_product_names;
  std::map<TString,TString> m_product_sources;
  std::map<TString,std::vector<SignatureObject*> > m_products;
  std::vector<TString> m_object_cut_list;
  std::vector<TString> m_signature_cut_list;
  std::vector<TString> m_handlerCuts;

  std::vector<TString> m_object_variable_list;
  std::map<TString,ObjectVariable*> m_object_variables;
  
  std::map<TString,std::vector<TString> > m_product_cuts;

  std::map<TString,std::map<TString,std::pair<ObjectComparison*,bool> > > m_product_comparisons;
  std::map<TString,std::pair<ObjectComparison*,bool> > m_product_selfcomparisons;

  TH2F* m_signatureCorrelationHisto;

  std::vector<TString> m_event_variable_list;
  std::map<TString,EventVariable*> m_variable_map;
  std::vector<TString> m_weight_variables;

  std::map<TString,double> m_variable_map_double;
  std::map<TString,int> m_variable_map_int;
  std::map<TString,long> m_variable_map_long;
  std::map<TString,TString> m_variable_map_TString;
  std::map<TString,bool> m_variable_map_bool;

  double m_btagWeights[3];
  int m_bTagged;
  
  
 protected:
  std::vector<Signature*> m_preHandlerCutSignatures;
  std::vector<Signature*> m_Signatures;
  std::vector<SignatureWithBjets*> m_bjetSignatures;
  Signature* m_noCutSignature;
  TFile* m_outFile;  
  BaseTreeReader* m_reader;  
  BaseTreeWriter* m_writer;

  ClassDef(BaseHandler,1);

};

#endif //#ifdef BaseHandler_cxx
