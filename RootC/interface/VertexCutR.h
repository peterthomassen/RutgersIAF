#ifndef VertexCutR_h
#define VertexCutR_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include "RutgersIAF/RootC/interface/VertexCut.h"
#include "RutgersIAF/RootC/interface/SignatureRecoVertex.h"

class VertexCutR : public VertexCut {
 public:
  VertexCutR(double rmax = 2, const char* name="vertrcut") : VertexCut(name), m_rmax(rmax){/* no-op */}
    //VertexCutR(double rmax = 2) : VertexCutR("vertrcut",rmax) { /* no-op */ }
    virtual ~VertexCutR(){ /* no-op */ }

  bool passCut(SignatureRecoVertex* vert) const
  {
    if(m_rmax > 0 && fabs(vert->Pt()) > m_rmax) return false;
    return true;
  }
  bool operator()(SignatureRecoVertex*) const;

 private:
  double m_rmax;

  ClassDef(VertexCutR,1);

};

inline bool VertexCutR::operator()(SignatureRecoVertex* vert) const
{
  return passCut(vert);
}
#endif
