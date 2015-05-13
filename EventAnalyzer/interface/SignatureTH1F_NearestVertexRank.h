#ifndef SignatureTH1F_NearestVertexRank_h
#define SignatureTH1F_NearestVertexRank_h

#include <TH1F.h>
#include <TString.h>
#include <vector>
#include <TVector3.h>
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class SignatureTH1F_NearestVertexRank : public SignatureTH1F {
public:
  
  SignatureTH1F_NearestVertexRank(const char* name, TString otherProductName, TString vertexProductName="ALLVERTICES"):SignatureTH1F(name,"Nearest Vertex Rank",20,-0.5,19.5),m_vertexProductName(vertexProductName),m_otherProductName(otherProductName){ }
    
  SignatureTH1F_NearestVertexRank(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_NearestVertexRank():SignatureTH1F() {}
	
  using TH1F::Fill;
  Int_t Fill(BaseHandler* handler)
  {    
    std::vector<SignatureObject*> vertices = handler->getProduct(m_vertexProductName);
    if(vertices.size() < 1)return -1;
    std::vector<SignatureObject*> others = handler->getProduct(m_otherProductName);
    if(others.size() < 1) return -1;
    double vx = -99999;
    double vy = -99999;
    double vz = -999999;
    if(!others[0]->getVariable("vx",vx) || !others[0]->getVariable("vy",vy) || !others[0]->getVariable("vz",vz)) return -1;
    TVector3 otherV(vx,vy,vz);
    double minR3 = 100000;
    int rank = 1000;
    for(int i = 0; i < (int)vertices.size(); i++){
      double x = -999999;
      double y = -999999;
      double z = -999999;
      if(!vertices[i]->getVariable("x",x) || !vertices[i]->getVariable("y",y) || !vertices[i]->getVariable("z",z)) continue;
      TVector3 thisV(x,y,z);
      if((otherV-thisV).Mag() < minR3){
	minR3 = (otherV-thisV).Mag();
	rank = i;
      }
    }

    return TH1F::Fill(rank,handler->getPhysicsWeight());
  }

  virtual void Copy(TObject& hnew) const
  {
    TH1F::Copy(hnew);
    ((SignatureTH1F_NearestVertexRank&)hnew).m_vertexProductName = m_vertexProductName;
    ((SignatureTH1F_NearestVertexRank&)hnew).m_otherProductName = m_otherProductName;
  }

  ClassDef(SignatureTH1F_NearestVertexRank,1);

 protected:
  TString m_vertexProductName;
  TString m_otherProductName;
};

#endif
