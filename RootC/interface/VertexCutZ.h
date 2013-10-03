#ifndef VertexCutZ_h
#define VertexCutZ_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include <cmath>
#include "RutgersIAF2012/RootC/interface/VertexCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureRecoVertex.h"

class VertexCutZ : public VertexCut {
 public:
  VertexCutZ(double zmax = 24,const char* name="vertzcut") : VertexCut(name), m_zmax(zmax){/* no-op */}
    //VertexCutZ(double zmax = 24) : VertexCutZ("vertzcut",zmax) { /* no-op */}
  virtual ~VertexCutZ(){ /* no-op */ }

  bool passCut(SignatureRecoVertex* vert) const
  {
    if(m_zmax > 0 && fabs(vert->Z()) > m_zmax) return false;
    return true;
  }
  bool operator()(SignatureRecoVertex*) const;

 private:
  double m_zmax;

  ClassDef(VertexCutZ,1);

};

inline bool VertexCutZ::operator()(SignatureRecoVertex* vert)const
{
  return passCut(vert);
}
#endif
