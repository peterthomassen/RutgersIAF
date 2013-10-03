#ifndef SignatureObjectWithIso_h
#define SignatureObjectWithIso_h

#include <algorithm>
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"

class SignatureObjectWithIso : public SignatureObject {
 public:
  SignatureObjectWithIso(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectWithIso(TLorentzVector v);
  virtual ~SignatureObjectWithIso(){/* no-op*/}
  void setRho(double c){m_rho = c;}
  double getRho(){return m_rho;}
  void setRhoNeutral(double c){m_rho_neutral = c;}
  double getRhoNeutral(){return m_rho_neutral;}

  void setCaloIso(double iso){m_caloIso = iso;}
  void setEcaloIso(double iso){m_ecaloIso = iso;}
  void setHcaloIso(double iso){m_hcaloIso = iso;}
  void setTrackIso(double iso){m_trackIso = iso;}
  void setAllTrackIso(double iso){m_allTrackIso = iso;}
  void setVertTrackIso(double iso){m_vertTrackIso = iso;}
  void setEcalIsoDep(double iso){m_ecalIsoDep = iso;}
  void setHcalIsoDep(double iso){m_hcalIsoDep = iso;}

  double getCaloIso(){return m_caloIso;}
  double getEcaloIso(){return m_ecaloIso;}
  double getHcaloIso(){return m_hcaloIso;}
  double getTrackIso(){return m_trackIso;}
  double getAllTrackIso(){return m_allTrackIso;}
  double getVertTrackIso(){return m_vertTrackIso;}
  double getEcalIsoDep(){return m_ecalIsoDep;}
  double getHcalIsoDep(){return m_hcalIsoDep;}

  virtual double getPhotonIso(){return m_photonIso;}
  virtual double getChargedHadronIso(){return m_chargedHadronIso;}
  virtual double getNeutralHadronIso(){return m_neutralHadronIso;}

  virtual void setPhotonIso(double c){m_photonIso = c;}
  virtual void setChargedHadronIso(double c){m_chargedHadronIso = c;}
  virtual void setNeutralHadronIso(double c){m_neutralHadronIso = c;}


  virtual double getRelIso();
  virtual double getTotalIso();
  virtual double getRhoCorrectedPFChargedHadronIsolation();
  virtual double getRhoCorrectedPFNeutralHadronIsolation();
  virtual double getRhoCorrectedPFPhotonIsolation();

 private:
  double m_caloIso,m_ecaloIso,m_hcaloIso,m_trackIso,m_allTrackIso,m_vertTrackIso,m_ecalIsoDep,m_hcalIsoDep,m_rho,m_rho_neutral;
  double m_photonIso,m_chargedHadronIso,m_neutralHadronIso;

  ClassDef(SignatureObjectWithIso,1);

};

inline SignatureObjectWithIso::SignatureObjectWithIso(double x,double y, double z, double t):SignatureObject(x,y,z,t){
  m_rho = -1.;
  m_rho_neutral = -1.;

  m_photonIso = -1.;
  m_chargedHadronIso = -1.;
  m_neutralHadronIso = -1.;
  m_caloIso = -1.;
  m_ecaloIso = -1.;
  m_hcaloIso = -1.;
  m_trackIso = -1.;
  m_allTrackIso = -1.;
  m_vertTrackIso = -1.;
  m_ecalIsoDep = -1.;
  m_hcalIsoDep = -1.;

}
inline SignatureObjectWithIso::SignatureObjectWithIso(TLorentzVector v):SignatureObject(v){
  m_rho = -1.;
  m_rho_neutral = -1.;

  m_photonIso = -1.;
  m_chargedHadronIso = -1.;
  m_neutralHadronIso = -1.;
  m_caloIso = -1.;
  m_ecaloIso = -1.;
  m_hcaloIso = -1.;
  m_trackIso = -1.;
  m_allTrackIso = -1.;
  m_vertTrackIso = -1.;
  m_ecalIsoDep = -1.;
  m_hcalIsoDep = -1.;

}

inline double SignatureObjectWithIso::getRelIso(){
  if (Pt() < 0) return 999999999.0;
  return getTotalIso()/Pt();
}

inline double SignatureObjectWithIso::getTotalIso(){
  if(m_caloIso < 0)return 9999999999.0;
  if(m_trackIso < 0)return 9999999999.0;
  return (m_caloIso + m_trackIso);
}

inline double SignatureObjectWithIso::getRhoCorrectedPFChargedHadronIsolation()
{
  if(getChargedHadronIso() < 0)return 999999999.0;
  return std::max(getChargedHadronIso() - getRho()*getChargedHadronEffectiveArea(),0.);
}
inline double SignatureObjectWithIso::getRhoCorrectedPFNeutralHadronIsolation()
{
  if(getNeutralHadronIso() < 0)return 999999999.0;
  return std::max(getNeutralHadronIso() - getRho()*getNeutralHadronEffectiveArea(),0.);
}
inline double SignatureObjectWithIso::getRhoCorrectedPFPhotonIsolation()
{
  if(getPhotonIso() < 0)return 999999999.0;
  return std::max(getPhotonIso() - getRho()*getPhotonEffectiveArea(),0.);
}

#endif
