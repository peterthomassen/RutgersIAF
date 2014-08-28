#ifndef PrintModuleProduct_h
#define PrintModuleProduct_h

#include <TObject.h>
#include <TROOT.h>
#include <TString.h>
#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/PrintModule.h"

class BaseHandler;

class PrintModuleProduct : public PrintModule {
 public:
  PrintModuleProduct(TString product, TString name="printProduct"):PrintModule(name){m_products.push_back(product); }
  virtual ~PrintModuleProduct(){}

  void addProduct(TString);
  void addVariable(TString,int);
  void addVariable(TString,double);
  void addVariable(TString,TString);
  void addVariable(TString,bool);

  virtual void print(BaseHandler*);

 private:
  std::vector<TString> m_products;
  std::vector<TString> m_variables_int;
  std::vector<TString> m_variables_double;
  std::vector<TString> m_variables_TString;
  std::vector<TString> m_variables_bool;
  ClassDef(PrintModuleProduct,1);

};


#endif
