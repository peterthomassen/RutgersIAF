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
class PrintModule;
class PrintModuleEverything;

typedef bool (*boolFunction)(BaseHandler*, int);

class BaseHandler : virtual public TObject {
 public:
  //default constructor
  BaseHandler(TString,BaseTreeReader*);
  //virtual destructor
  virtual ~BaseHandler();

  friend class AnalysisTreeWriter;
  friend class SignatureTreeWriter;
  friend class PrintModuleEverything;

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
  virtual void addHistogram(SignatureTH1F*, TString signatureRegExp);
  virtual void addHistogram(SignatureTH2F*, TString signatureRegExp);
  virtual void addHistogram(SignatureTH3F*, TString signatureRegExp);

  virtual double getPhysicsWeight(){return m_physicsWeight;}
  virtual Signature* addSignature(const char* name, const char* option="");
  virtual void addSignature(Signature* sig) {m_Signatures.push_back(sig);}
  virtual void addPreCutSignature(const char*, const char*);
  virtual void addPreCutSignature(Signature* sig){m_preHandlerCutSignatures.push_back(sig);}

  virtual bool passCut(TString);

  virtual void addHandlerCut(TString);

  /////////////////////////////
  //Access physics quantities//
  /////////////////////////////
  virtual bool getDebugMode(){return m_debugMode;}
  virtual void setDebugMode(bool c=true){m_debugMode = c;}
  virtual void dumpEventInfo();
  virtual void printDebugInfo();

  virtual void addPrintModule(PrintModule*);

  virtual void addEventVariable(TString,EventVariable*,bool rename=true);
  EventVariable* getEventVariable(TString);

  virtual void addObjectVariable(TString,ObjectVariable*,bool rename=true);
  ObjectVariable* getObjectVariable(TString);

  boolFunction setHookFunction(boolFunction hookFunction);
  virtual void setVariable(TString,double);
  virtual void setVariable(TString,int);
  virtual void setVariable(TString,long);
  virtual void setVariable(TString,TString);
  virtual void setVariable(TString,bool);
  virtual void setVector(TString,std::vector<double>);
  virtual void setVector(TString,std::vector<int>);
  virtual void setVector(TString,std::vector<long>);
  virtual void setVector(TString,std::vector<TString>);

  virtual bool getVariable(TString,double&);
  virtual bool getVariable(TString,int&);
  virtual bool getVariable(TString,long&);
  virtual bool getVariable(TString,TString&);
  virtual bool getVariable(TString,bool&);
  virtual bool getVector(TString,std::vector<double>&);
  virtual bool getVector(TString,std::vector<int>&);
  virtual bool getVector(TString,std::vector<long>&);
  virtual bool getVector(TString,std::vector<TString>&);

  virtual void addWeightVariable(TString);

  BaseTreeReader* getReader(){return m_reader;}
  BaseTreeWriter* getWriter(TString fakeCombination = "") const;
  void setWriter(BaseTreeWriter* writer, TString fakeCombination = "");
  TFile* getOutFile(){return m_outFile;}

  void addDumpEvent(int,int,long);

  void setMode(std::string name, int mode = 1){m_mode[name] = mode;}
  int getMode(std::string name) const;
  int getN() const { return m_n; }
  int getM() const { return m_m; }

  void readGoodRunLumi(TString c);
  void readGoodRunLumiFromJSON(TString JSONFile, bool debug = false);
  void printRunLumiJSON();
  //////////////////////
  //Product Management//
  //////////////////////
  virtual std::vector<SignatureObject*> getProduct(TString);
  virtual bool isProductListed(TString);
  virtual bool isProductPresent(TString);
  virtual void addProduct(TString,TString);
  virtual void addProductCut(TString,TString);

  virtual void addProductComparison(TString,TString,ObjectComparison*,bool doAnd=true);
  virtual void addProductSelfComparison(TString,ObjectComparison*,bool doAnd=true);
  
  // set default for single product
  virtual void setDefaultObjectVariable(TString,TString,double,bool);
  virtual void setDefaultObjectVariable(TString,TString,int,bool);
  virtual void setDefaultObjectVariable(TString,TString,TString,bool);
  virtual void setDefaultObjectVariable(TString,TString,bool,bool);
  
  // set default for all products
  virtual void setDefaultObjectVariable(TString,double,bool);
  virtual void setDefaultObjectVariable(TString,int,bool);
  virtual void setDefaultObjectVariable(TString,TString,bool);
  virtual void setDefaultObjectVariable(TString,bool,bool);
  
  virtual bool getDefaultObjectVariable(TString,TString,double&) const;
  virtual bool getDefaultObjectVariable(TString,TString,int&) const;
  virtual bool getDefaultObjectVariable(TString,TString,TString&) const;
  virtual bool getDefaultObjectVariable(TString,TString,bool&) const;

 protected:
  virtual bool createProducts();
  virtual void resetProducts();
  virtual bool prepareEvent();
  virtual void calculateVariables();
  virtual void resetVariables();
  virtual void calcPhysicsWeight();
  virtual bool applyHandlerCuts();
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
  
  bool m_passedHandlerCuts = false;
    
  std::map<int, std::vector<int> > m_goodRunLumi;
  bool m_doRunLumiCheck;
  std::multimap<int, std::vector<std::pair<int, int> > > m_json;
  bool m_doRunLumiCheckFromJSON;
  int m_checkedRun;
  int m_checkedLumi;
  int m_n = -1;
  int m_m = -1;
  unsigned m_trackFakeCombination;
  unsigned m_trackFakeCombinationIndex;
  unsigned m_photonFakeCombination;
  unsigned m_photonFakeCombinationIndex;
  unsigned m_tauFakeCombination;
  unsigned m_tauFakeCombinationIndex;
  bool m_isRunLumiGood;
  bool checkRunLumi(int r, int l);
  bool checkRunLumiFromJSON(int RunNumber, int LumiNumber, bool debug = false);
  
  int power(int, int);
  
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

  std::map<TString,std::vector<double>> m_variable_map_double;
  std::map<TString,std::vector<int>> m_variable_map_int;
  std::map<TString,std::vector<long>> m_variable_map_long;
  std::map<TString,std::vector<TString>> m_variable_map_TString;
  std::map<TString,bool> m_variable_map_bool;
  std::vector<PrintModule*> m_print_modules;

  std::map<std::pair<TString,TString>,double> m_defaultMapDouble;
  std::map<std::pair<TString,TString>,int> m_defaultMapInt;
  std::map<std::pair<TString,TString>,TString> m_defaultMapTString;
  std::map<std::pair<TString,TString>,bool> m_defaultMapBool;

  double m_btagWeights[3];
  int m_bTagged;
  
  boolFunction m_hookFunction = 0;
  
  
 protected:
  std::vector<Signature*> m_preHandlerCutSignatures;
  std::vector<Signature*> m_Signatures;
  std::vector<SignatureWithBjets*> m_bjetSignatures;
  Signature* m_noCutSignature;
  TFile* m_outFile;  
  BaseTreeReader* m_reader;
  BaseTreeWriter* m_writer = 0;
  std::map<TString, BaseTreeWriter*> m_writers;

  ClassDef(BaseHandler,1);

};

#endif //#ifdef BaseHandler_cxx
