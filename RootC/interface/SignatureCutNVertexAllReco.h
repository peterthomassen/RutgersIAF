#ifndef SignatureCutNVertexAllReco_h
#define SignatureCutNVertexAllReco_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/SignatureCutN.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"

class SignatureCutNVertexAllReco : public SignatureCutN {
 public:
  SignatureCutNVertexAllReco(double nvertexlow = 0, double nvertexhigh=-1,const char* name="sigCutNVertexAllReco") : SignatureCutN("",nvertexlow,nvertexhigh,name){ /* no-op */}
    //SignatureCutNVertex(double nvertexlow = 0, double nvertexhigh=-1):SignatureCutNVertex("sigcutnvertex",nvertexlow,nvertexhigh) { /*no-op */ }
  virtual ~SignatureCutNVertexAllReco(){ /* no-op */ }

  int getN(BaseHandler*) const;


 private:

  ClassDef(SignatureCutNVertexAllReco,1);

};

inline int SignatureCutNVertexAllReco::getN(BaseHandler* handler) const
{
  //std::cout<<handler->getGoodRecoVertices().size()<<std::endl;
  return (int)handler->getAllRecoVertices().size();
}

#endif
