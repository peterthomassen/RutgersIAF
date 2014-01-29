#ifndef SignatureObject_h
#define SignatureObject_h
#include <TLorentzVector.h>

class SignatureObject : public TLorentzVector {
 public:
  SignatureObject(double x=0,double y=0, double z=0, double t=0);
  SignatureObject(TLorentzVector v);
  virtual ~SignatureObject(){/* no-op*/}
  int getPDGid(){return m_pdgid;}
  void setPDGid(int id){m_pdgid = id;}
  bool operator>(SignatureObject &s);
  bool operator<(SignatureObject &s);
  //virtual bool operator==(SignatureObject &s);
  double getChargedHadronEffectiveArea();
  double getNeutralHadronEffectiveArea();
  double getPhotonEffectiveArea();
  double getPhotonPlusNeutralHadronEffectiveArea();
  virtual double getCharge(){return m_charge;}
  virtual void setCharge(double c){m_charge = c;}

 protected:
  int m_pdgid;
  double m_charge;

  ClassDef(SignatureObject,1);

};

inline SignatureObject::SignatureObject(double x,double y, double z, double t):TLorentzVector(x,y,z,t){
  m_pdgid = 0;
  m_charge = 0;
}
inline SignatureObject::SignatureObject(TLorentzVector v):TLorentzVector(v){
  m_pdgid = 0;
  m_charge = 0;
}
inline bool SignatureObject::operator>(SignatureObject &s)
{
  return Pt() > s.Pt();
}
inline bool SignatureObject::operator<(SignatureObject &s)
{
  return Pt() < s.Pt();
}

inline double SignatureObject::getChargedHadronEffectiveArea()
{
  if(fabs(Eta()) < 1.0) return 0.002;
  else if(fabs(Eta()) > 1.0 && fabs(Eta()) < 1.479) return 0.003;
  else if(fabs(Eta()) > 1.479 && fabs(Eta()) < 2.0) return 0.004;
  else if(fabs(Eta()) > 2.0 && fabs(Eta()) < 2.2) return 0.006;
  else if(fabs(Eta()) > 2.2 && fabs(Eta()) < 2.3) return 0.006;
  else if(fabs(Eta()) > 2.3 && fabs(Eta()) < 2.4) return 0.004;
  else return 0.003;
}

inline double SignatureObject::getNeutralHadronEffectiveArea()
{
  if(fabs(Eta()) < 1.0) return 0.024;
  else if(fabs(Eta()) > 1.0 && fabs(Eta()) < 1.479) return 0.037;
  else if(fabs(Eta()) > 1.479 && fabs(Eta()) < 2.0) return 0.037;
  else if(fabs(Eta()) > 2.0 && fabs(Eta()) < 2.2) return 0.034;
  else if(fabs(Eta()) > 2.2 && fabs(Eta()) < 2.3) return 0.043;
  else if(fabs(Eta()) > 2.3 && fabs(Eta()) < 2.4) return 0.047;
  else return 0.066;
}

inline double SignatureObject::getPhotonEffectiveArea()
{
  if(fabs(Eta()) < 1.0) return 0.053;
  else if(fabs(Eta()) > 1.0 && fabs(Eta()) < 1.479) return 0.052;
  else if(fabs(Eta()) > 1.479 && fabs(Eta()) < 2.0) return 0.037;
  else if(fabs(Eta()) > 2.0 && fabs(Eta()) < 2.2) return 0.073;
  else if(fabs(Eta()) > 2.2 && fabs(Eta()) < 2.3) return 0.107;
  else if(fabs(Eta()) > 2.3 && fabs(Eta()) < 2.4) return 0.123;
  else return 0.133;
}

inline double SignatureObject::getPhotonPlusNeutralHadronEffectiveArea()
{
  if(fabs(Eta()) < 1.0) return 0.13;
  else if(fabs(Eta()) > 1.0 && fabs(Eta()) < 1.479) return 0.14;
  else if(fabs(Eta()) > 1.479 && fabs(Eta()) < 2.0) return 0.07;
  else if(fabs(Eta()) > 2.0 && fabs(Eta()) < 2.2) return 0.09;
  else if(fabs(Eta()) > 2.2 && fabs(Eta()) < 2.3) return 0.11;
  else if(fabs(Eta()) > 2.3 && fabs(Eta()) < 2.4) return 0.11;
  else return 0.14;
}

bool SignatureObjectComparison(SignatureObject*,SignatureObject*);

#endif
