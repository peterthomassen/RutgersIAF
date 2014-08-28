#ifndef PrintModule_h
#define PrintModule_h

#include <TObject.h>
#include <TROOT.h>
#include <TString.h>

class BaseHandler;

class PrintModule : public TObject {
 public:
  PrintModule(TString);
  virtual ~PrintModule(){}

  virtual void print(BaseHandler*) = 0;

  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;

  ClassDef(PrintModule,1);

};


#endif
