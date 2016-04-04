#ifndef ObjectComparisonDisplacedVertex_h
#define ObjectComparisonDisplacedVertex_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectComparisonDisplacedVertex : public ObjectComparison {
 public:
 ObjectComparisonDisplacedVertex(double maxR, TString xname="VtxX", TString yname="VtxY", TString zname="VtxZ",TString name="objectcomparisondisplacedvertex"): ObjectComparison(name),m_maxR(maxR),m_xname(xname),m_yname(yname),m_zname(zname){}
  virtual ~ObjectComparisonDisplacedVertex() {}

  virtual bool passCut(SignatureObject* a,SignatureObject* b) const {
    double a_x = 0,a_y = 0, a_z = 0;
    double b_x = 0,b_y = 0, b_z = 0;
    bool isSet_ax = a->getVariable(m_xname,a_x);
    bool isSet_ay = a->getVariable(m_yname,a_y);
    bool isSet_az = a->getVariable(m_zname,a_z);
    bool isSet_bx = b->getVariable(m_xname,b_x);
    bool isSet_by = b->getVariable(m_yname,b_y);
    bool isSet_bz = b->getVariable(m_zname,b_z);
    if(isSet_ax && isSet_ay && isSet_az && isSet_bx && isSet_by && isSet_bz){
      double rrr = sqrt(pow(a_x-b_x,2) + pow(a_y-b_y,2) + pow(a_z-b_z,2));
      if(rrr < m_maxR) return false;
    }
    return true;
  }
  virtual bool operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_maxR;
  TString m_xname;
  TString m_yname;
  TString m_zname;

  ClassDef(ObjectComparisonDisplacedVertex,1);
};

#endif
