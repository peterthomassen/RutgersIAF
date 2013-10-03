#ifndef SignatureObjectMCPart_h
#define SignatureObjectMCPart_h

#include "RutgersIAF2012/RootC/interface/SignatureObject.h"

class SignatureObjectMCPart : public SignatureObject {
 public:
  SignatureObjectMCPart(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectMCPart(TLorentzVector v);
  virtual ~SignatureObjectMCPart(){/* no-op*/}

  void setPdgID(int c){m_pdgID = c;}
  void setVx(double c){m_vx = c;}
  void setVy(double c){m_vy = c;}
  void setVz(double c){m_vz = c;}
  void setCharge(double c){m_charge = c;}
  void setStatus(int c){m_status = c;}
  void setBarcode(int c){m_barcode = c;}
  void setMother_pdgID(int c){m_mother_pdgID = c;}
  void setMother_ntID(int c){m_mother_ntID = c;}
  void setN_children(int c){m_n_children = c;}

  int getPdgID(){return m_pdgID;}
  double getVx(){return m_vx;}
  double getVy(){return m_vy;}
  double getVz(){return m_vz;}
  double getCharge(){return m_charge;}
  int getStatus(){return m_status;}
  int getBarcode(){return m_barcode;}
  int getMother_pdgID(){return m_mother_pdgID;}
  int getMother_ntID(){return m_mother_ntID;}
  int getN_children(){return m_n_children;}


 private:
  int m_pdgID;
  double m_vx;
  double m_vy;
  double m_vz;
  double m_charge;
  int m_status;
  int m_barcode;
  int m_mother_pdgID;
  int m_mother_ntID;
  int m_n_children;



  ClassDef(SignatureObjectMCPart,1);

};

inline SignatureObjectMCPart::SignatureObjectMCPart(double x,double y, double z, double t):SignatureObject(x,y,z,t){
  m_pdgID = 0;
  m_vx = -10000;
  m_vy = -10000;
  m_vz = -10000;
  m_charge = 0;
  m_status = -1;
  m_barcode = -1;
  m_mother_pdgID = 0;
  m_mother_ntID = -1;
  m_n_children = -1;

}
inline SignatureObjectMCPart::SignatureObjectMCPart(TLorentzVector v):SignatureObject(v){
  m_pdgID = 0;
  m_vx = -10000;
  m_vy = -10000;
  m_vz = -10000;
  m_charge = 0;
  m_status = -1;
  m_barcode = -1;
  m_mother_pdgID = 0;
  m_mother_ntID = -1;
  m_n_children = -1;

}
#endif
