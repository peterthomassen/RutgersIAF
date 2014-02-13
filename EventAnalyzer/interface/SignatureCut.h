#ifndef SignatureCut_h
#define SignatureCut_h

#include <TObject.h>
#include <TROOT.h>

class TString;
class BaseHandler;

class SignatureCut : public TObject {
 public:
  SignatureCut(TString);
  virtual ~SignatureCut();

  virtual bool passCut(BaseHandler*) const = 0;
  virtual bool operator()(BaseHandler*) const = 0;
  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}

 private:
  TString m_name;

  ClassDef(SignatureCut,1);

};

#endif
