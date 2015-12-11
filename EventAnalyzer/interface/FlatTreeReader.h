//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#ifndef FlatTreeReader_h
#define FlatTreeReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "TRandom.h"
#include "TRandom3.h"
#include "TClonesArray.h"
#include "TObjArray.h"

#include "RutgersIAF/EventAnalyzer/interface/BaseTreeReader.h"

class BaseHandler;

class FlatTreeReader : public BaseTreeReader {

  friend class BaseHandler;
public :
   Int_t           fCurrent; //!current Tree number in a TChain

   FlatTreeReader(TTree *tree);
   virtual ~FlatTreeReader();
   virtual void     Init(TTree *tree);
   void dumpEventInfo();

 protected:
   void makeProducts();
   void clearProducts();
   void createVariables();

   long event_;
   int run_;
   int lumi_;

   std::vector<std::string>* p_variable_map_double_keys;
   std::vector<std::string>* p_variable_map_long_keys;
   std::vector<std::string>* p_variable_map_int_keys;
   std::vector<std::string>* p_variable_map_TString_keys;
   std::vector<std::string>* p_variable_map_bool_keys;
   
   std::vector<double>* p_variable_map_double_values;
   std::vector<long>* p_variable_map_long_values;
   std::vector<int>* p_variable_map_int_values;
   std::vector<std::string>* p_variable_map_TString_values;
   std::vector<bool>* p_variable_map_bool_values;

   TObjArray* clonesarray_;

   ClassDef(FlatTreeReader,1);
};

#endif

