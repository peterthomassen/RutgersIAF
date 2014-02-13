#ifndef EventVariable_h
#define EventVariable_h

#include <TObject.h>
#include <TROOT.h>
#include <TString.h>

class BaseHandler;

class EventVariable : public TObject {
 public:
  EventVariable(TString);
  virtual ~EventVariable(){}

  virtual bool calculate(BaseHandler*) = 0;

  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;

  ClassDef(EventVariable,1);

};


#endif
