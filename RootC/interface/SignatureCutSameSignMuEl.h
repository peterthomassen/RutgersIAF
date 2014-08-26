#ifndef SignatureCutSameSignMuEl_h
#define SignatureCutSameSignMuEl_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF/RootC/interface/SignatureObjectElectron.h"

class SignatureCutSameSignMuEl : public SignatureCut {
 public:
  SignatureCutSameSignMuEl(const char* name="sigcutSameSignMuEl") : SignatureCut(name){ /* no-op */}
    //SignatureCutSameSignMuEl(double stlow = 0, double sthigh=-1):SignatureCutSameSignMuEl("sigcutSameSignMuEl",stlow,sthigh) { /*no-op */ }
  virtual ~SignatureCutSameSignMuEl(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const 
  {
    double firstcharge = 0;
    if(handler->getGoodElectrons().size() > 0){
      SignatureObjectElectron* e = (SignatureObjectElectron*)(handler->getGoodElectrons())[0];
      firstcharge = e->getCharge();
    }else if(handler->getGoodMuons().size() > 0){
      SignatureObjectMuon* e = (SignatureObjectMuon*)(handler->getGoodMuons())[0];
      firstcharge = e->getCharge();
    }else{
      return false;
    }
    for(int i = 0; i < (int)handler->getGoodElectrons().size(); i++){
      SignatureObjectElectron* e = (SignatureObjectElectron*)handler->getGoodElectrons()[i];
      if(firstcharge * e->getCharge() <= 0)return false;
    }
    for(int i = 0; i < (int)handler->getGoodMuons().size(); i++){
      SignatureObjectMuon* e = (SignatureObjectMuon*)handler->getGoodMuons()[i];
      if(firstcharge * e->getCharge() <= 0)return false;
    }
    return true;
  }
  virtual bool operator()(BaseHandler*) const;

 private:

  ClassDef(SignatureCutSameSignMuEl,1);

};

inline bool SignatureCutSameSignMuEl::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
