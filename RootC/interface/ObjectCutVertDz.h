#ifndef ObjectCutVertDz_h
#define ObjectCutVertDz_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutVertDz : public ObjectCut {
 public:
  ObjectCutVertDz(double dzmax=1.0, const char* name="dzcut") : ObjectCut(name),m_dzmax(dzmax){ /*no-op*/}
    //ObjectCutVertDz(double dzmax = 1.0) : ObjectCutVertDz("dzcut",dzmax) {/* no-op */ }
    
  virtual ~ObjectCutVertDz(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
	//std::cout<<m_dzmax<<" "<<sigObj->getVert_dz()<<" "<<(int)(fabs(sigObj->getVert_dz()) > m_dzmax)<<std::endl;
    if(m_dzmax > 0 && fabs(sigObj->getVert_dz()) > m_dzmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_dzmax;

  ClassDef(ObjectCutVertDz,1);

};

inline bool ObjectCutVertDz::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
