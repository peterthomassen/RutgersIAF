#ifndef SignatureRecoVertex_h
#define SignatureRecoVertex_h
#include <TVector3.h>

class SignatureRecoVertex : public TVector3 {
 public:
  SignatureRecoVertex(double x=0,double y=0,double z=0);
  SignatureRecoVertex(TVector3 v);
  ~SignatureRecoVertex(){/* no-op */}

  void setNtrack(int c){m_ntrack = c;}
  void setEx(double c){m_ex = c;}
  void setEy(double c){m_ey = c;}
  void setEz(double c){m_ez = c;}
  void setNdof(double c){m_ndof = c;}
  void setChi2(double c){m_chi2 = c;}
  void setWSumPt(double c){m_wSumPt = c;}

  int getNtrack(){return m_ntrack;}
  double getEx(){return m_ex;}
  double getEy(){return m_ey;}
  double getEz(){return m_ez;}
  double getNdof(){return m_ndof;}
  double getChi2(){return m_chi2;}
  double getWSumPt(){return m_wSumPt;}

 private:
  int m_ntrack;
  double m_ex;
  double m_ey;
  double m_ez;
  double m_ndof;
  double m_chi2;
  double m_wSumPt;


  ClassDef(SignatureRecoVertex,1);

};

inline SignatureRecoVertex::SignatureRecoVertex(double _x, double _y, double _z) : TVector3(_x,_y,_z){
  m_ntrack = -1;
  m_ex = -1;
  m_ey = -1;
  m_ez = -1;
  m_ndof = -1;
  m_chi2 = -1;
  m_wSumPt = -1;

}
inline SignatureRecoVertex::SignatureRecoVertex(TVector3 v):TVector3(v){
  m_ntrack = -1;
  m_ex = -1;
  m_ey = -1;
  m_ez = -1;
  m_ndof = -1;
  m_chi2 = -1;
  m_wSumPt = -1;

}
#endif
