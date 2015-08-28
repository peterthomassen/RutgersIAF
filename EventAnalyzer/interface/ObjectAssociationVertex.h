#ifndef ObjectAssociationVertex_h
#define ObjectAssociationVertex_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociation.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectAssociationVertex : public ObjectAssociation {
 public:
 ObjectAssociationVertex(double deltar, TString vxname, TString vyname, TString vzname, TString name="objectcomparisonmatchdeltar"): ObjectAssociation(name),m_deltaR(deltar),m_vxName(vxname),m_vyName(vyname),m_vzName(vzname){}
  virtual ~ObjectAssociationVertex() {}

  virtual std::pair<bool,double> passCut(SignatureObject* a,SignatureObject* b) const {
    double a_vx,a_vy,a_vz;
    double b_vx,b_vy,b_vz;
    bool ax_isSet = a->getVariable(m_vxName,a_vx);
    bool ay_isSet = a->getVariable(m_vyName,a_vy);
    bool az_isSet = a->getVariable(m_vzName,a_vz);
    bool bx_isSet = b->getVariable(m_vxName,b_vx);
    bool by_isSet = b->getVariable(m_vyName,b_vy);
    bool bz_isSet = b->getVariable(m_vzName,b_vz);
    if(!ax_isSet || !ay_isSet || !az_isSet || !bx_isSet || !by_isSet || !bz_isSet)return std::make_pair(false,1e6);
    double dr = sqrt(pow(a_vx-b_vx,2)+pow(a_vy-b_vy,2)+pow(a_vz-b_vz,2));
    if(dr < m_deltaR){
      return std::make_pair(true,dr);
    }
    return std::make_pair(false,1e6);
  }
  virtual std::pair<bool,double> operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltaR;
  TString m_vxName;
  TString m_vyName;
  TString m_vzName;

  ClassDef(ObjectAssociationVertex,1);
};

#endif
