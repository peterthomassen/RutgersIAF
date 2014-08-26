#ifndef SignatureWithBjets_h
#define SignatureWithBjets_h

#include "RutgersIAF/RootC/interface/Signature.h"

class SignatureWithBjets : public Signature {

 public:

  //functions
  SignatureWithBjets(const char*,const char*,int,int); //constructor
  SignatureWithBjets(const Signature&,int,int);
  SignatureWithBjets(const SignatureWithBjets&);//copy constructor
  virtual ~SignatureWithBjets(){/* no-op */} //destructor

  int getLow(){return m_low;}
  int getHigh(){return m_high;}
  void setLow(int c){m_low = c;}
  void setHigh(int c){m_high = c;}

  void init();
  void finish();

 protected:



 private:
  int m_low,m_high;
  ClassDef(SignatureWithBjets,1);

};


#endif
