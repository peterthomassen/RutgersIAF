#ifndef VertexCutNdof_h
#define VertexCutNdof_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/VertexCut.h"
#include "RutgersIAF/RootC/interface/SignatureRecoVertex.h"

class VertexCutNdof : public VertexCut {
 public:
  VertexCutNdof(double minNdof = 4,const char* name="ndofcut") : VertexCut(name), m_ndofmin(minNdof){/* no-op */}
    //VertexCutNdof(double minNdof = 4) : VertexCutNdof("ndofcut",minNdof){/* no-op */}
    virtual ~VertexCutNdof() {/* no-op */ }

  bool passCut(SignatureRecoVertex* vert) const
  {
    if(m_ndofmin > 0 && vert->getNdof() < m_ndofmin) return false;
    return true;
  }
  bool operator()(SignatureRecoVertex*) const;

 private:
  double m_ndofmin;

  ClassDef(VertexCutNdof,1);

};

inline bool VertexCutNdof::operator()(SignatureRecoVertex* vert)const
{
  return passCut(vert);
}
#endif
