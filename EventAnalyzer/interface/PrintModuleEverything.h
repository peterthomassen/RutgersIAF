#ifndef PrintModuleEverything_h
#define PrintModuleEverything_h

#include <TObject.h>
#include <TROOT.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/PrintModule.h"

class BaseHandler;

class PrintModuleEverything : public PrintModule {
 public:
  PrintModuleEverything(TString name):PrintModule(name){ }
  virtual ~PrintModuleEverything(){}

  virtual void print(BaseHandler*);

 private:

  ClassDef(PrintModuleEverything,1);

};


#endif
