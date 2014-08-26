#ifndef ObjectCutMCStatus_h
#define ObjectCutMCStatus_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMCPart.h"

class ObjectCutMCStatus : public ObjectCut {
 public:
  ObjectCutMCStatus(int status, const char* name="mcstatuscut") : ObjectCut(name),m_status(status){ /*no-op*/}
    //ObjectCutMCStatus(double etamax) : ObjectCutMCStatus("etacut",etamax){ /* no-op */ }
    
  virtual ~ObjectCutMCStatus(){}
  bool passCut(SignatureObject* sigObj) const {return passCut((SignatureObjectMCPart*)sigObj);}
  bool operator()(SignatureObject* sigObj) const {return passCut((SignatureObjectMCPart*)sigObj);}

  bool passCut(SignatureObjectMCPart* sigObj) const
  {
    if(sigObj->getStatus() != m_status) return false;
    return true;
  }
  bool operator()(SignatureObjectMCPart*) const;

 private:
  double m_status;


  ClassDef(ObjectCutMCStatus,1);

};

inline bool ObjectCutMCStatus::operator()(SignatureObjectMCPart* sigobj) const
{
  return passCut(sigobj);
}
#endif
