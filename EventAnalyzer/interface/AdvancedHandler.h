#ifndef AdvancedHandler_h
#define AdvancedHandler_h


#include <iostream>
#include <TROOT.h>
#include <vector>
#include <map>
#include <TObject.h>
#include <string>
#include "BaseHandler.h"
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
class ProductMaker;
class ObjectAssociation;

class AdvancedHandler :  public BaseHandler {
 public:
  //default constructor
  AdvancedHandler(TString,BaseTreeReader*);
  //virtual destructor
  virtual ~AdvancedHandler();

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

  /////////////////////////////
  //Access physics quantities//
  /////////////////////////////


  void setWriter(BaseTreeWriter* writer, TString fakeCombination = "");

  //////////////////////
  //Product Management//
  //////////////////////
  virtual void addProduct(TString,ProductMaker*);
  virtual void addProduct(TString,TString);
  virtual void addProductCut(TString,TString);

  virtual void addProductComparison(TString,TString,ObjectComparison*,bool doAnd=true);
  virtual void addProductSelfComparison(TString,ObjectComparison*,bool doAnd=true);
  virtual void addProductAssociation(TString,TString,ObjectAssociation*);
  virtual void addAssociateVariable(TString,TString,ObjectVariable*,bool rename=true);

 protected:
  virtual bool createProducts();
  virtual bool prepareEvent();
  virtual void analyzeEvent();

  std::map<TString,ProductMaker*> m_product_maker_map;    
  ////////////
  //Products//
  ////////////
  
  
 protected:

  ClassDef(AdvancedHandler,1);

};

#endif //#ifdef AdvancedHandler_cxx
