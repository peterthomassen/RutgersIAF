#ifndef SignatureBeamSpot_h
#define SignatureBeamSpot_h
#include <TVector3.h>

class SignatureBeamSpot : public TVector3 {
 public:
  SignatureBeamSpot(double x=0,double y=0,double z=0);
  SignatureBeamSpot(TVector3 v);
  ~SignatureBeamSpot(){/* no-op */}

  void setNtrack(int c){m_ntrack = c;}
  void setEx(double c){m_ex = c;}
  void setEy(double c){m_ey = c;}
  void setEz(double c){m_ez = c;}
  void setSigmaz(double c){m_sigmaz = c;}
  void setDxdz(double c){m_dxdz = c;}
  void setWidth(double c){m_width = c;}

  int getNtrack(){return m_ntrack;}
  double getEx(){return m_ex;}
  double getEy(){return m_ey;}
  double getEz(){return m_ez;}
  double getSigmaz(){return m_sigmaz;}
  double getDxdz(){return m_dxdz;}
  double getWidth(){return m_width;}

 private:
  int m_ntrack;
  double m_ex;
  double m_ey;
  double m_ez;
  double m_sigmaz;
  double m_dxdz;
  double m_width;


  ClassDef(SignatureBeamSpot,1);

};

inline SignatureBeamSpot::SignatureBeamSpot(double _x, double _y, double _z) : TVector3(_x,_y,_z){
  m_ntrack = -1;
  m_ex = -1;
  m_ey = -1;
  m_ez = -1;
  m_sigmaz = -1;
  m_dxdz = -1;
  m_width = -1;

}
inline SignatureBeamSpot::SignatureBeamSpot(TVector3 v):TVector3(v){
  m_ntrack = -1;
  m_ex = -1;
  m_ey = -1;
  m_ez = -1;
  m_sigmaz = -1;
  m_dxdz = -1;
  m_width = -1;

}
#endif
