#ifndef PrintModuleEventVariables_h
#define PrintModuleEventVariables_h

#include <TObject.h>
#include <TROOT.h>
#include <TString.h>
#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/PrintModule.h"

class BaseHandler;

class PrintModuleEventVariables : public PrintModule {
 public:
  PrintModuleEventVariables(TString name="printProduct"):PrintModule(name){ }
  virtual ~PrintModuleEventVariables(){}

  void addVariable(TString,int);
  void addVariable(TString,double);
  void addVariable(TString,TString);
  void addVariable(TString,bool);

  virtual void print(BaseHandler*);

 private:
  std::vector<TString> m_variables_int;
  std::vector<TString> m_variables_double;
  std::vector<TString> m_variables_TString;
  std::vector<TString> m_variables_bool;
  ClassDef(PrintModuleEventVariables,1);

};


#endif
