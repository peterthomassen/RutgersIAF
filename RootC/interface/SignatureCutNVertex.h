#ifndef SignatureCutNVertex_h
#define SignatureCutNVertex_h

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

class SignatureCutNVertex : public SignatureCutN {
 public:
  SignatureCutNVertex(double nvertexlow = 0, double nvertexhigh=-1,const char* name="sigcutnvertex") : SignatureCutN("",nvertexlow,nvertexhigh,name){ /* no-op */}
    //SignatureCutNVertex(double nvertexlow = 0, double nvertexhigh=-1):SignatureCutNVertex("sigcutnvertex",nvertexlow,nvertexhigh) { /*no-op */ }
  virtual ~SignatureCutNVertex(){ /* no-op */ }

  int getN(BaseHandler*) const;


 private:

  ClassDef(SignatureCutNVertex,1);

};

inline int SignatureCutNVertex::getN(BaseHandler* handler) const
{
  //std::cout<<handler->getGoodRecoVertices().size()<<std::endl;
  return (int)handler->getGoodRecoVertices().size();
}

#endif
