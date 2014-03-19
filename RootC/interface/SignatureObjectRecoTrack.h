#ifndef SignatureObjectRecoTrack_h
#define SignatureObjectRecoTrack_h

#include <vector>
#include "RutgersIAF2012/RootC/interface/SignatureObjectWithIso.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class SignatureObjectRecoTrack : public SignatureObjectWithIso {
 public:
  SignatureObjectRecoTrack(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectRecoTrack(TLorentzVector v);
  virtual ~SignatureObjectRecoTrack() {/* no-op */}
  
  virtual bool isElectron() { return false; }
  virtual bool isMuon() { return false; }
  virtual bool isTau() { return false; }
  bool isTrack() { return !(isElectron() || isMuon() || isTau()); }
  
  double getDz(){return m_dz;}
  int getGenParticle_ntID(){return m_genParticle_ntID;}
  SignatureObjectMCPart* getGenParticle(){return m_genParticle;}
  double getCaloIso9(){return m_caloIso9;}
  double getDxy(){return m_dxy;}
  int getNValidMuonHits(){return m_nValidMuonHits;}
  double getCaloIso2(){return m_caloIso2;}
  double getVert_dxy(){return m_vert_dxy;}
  double getCharge(){return m_charge;}
  double getCaloIso1(){return m_caloIso1;}
  int getIsGlobal(){return m_isGlobal;}
  double getBeam_dsz(){return m_beam_dsz;}
  int getNLostPixelHits(){return m_nLostPixelHits;}
  int getNpixelLayersWM(){return m_npixelLayersWM;}
  double getVx(){return m_vx;}
  double getVy(){return m_vy;}
  double getLambdaError(){return m_lambdaError;}
  double getPF_chargedHadronIso(){return m_PF_chargedHadronIso;}
  int getNValidPixelHits(){return m_nValidPixelHits;}
  double getVz(){return m_vz;}
  double getD0(){return m_d0;}
  int getGenParticle_mother_ntID(){return m_genParticle_mother_ntID;}
  double getDsz(){return m_dsz;}
  int getNValidTrackerHits(){return m_nValidTrackerHits;}
  int getNBadMuonHitsInFirstStation(){return m_nBadMuonHitsInFirstStation;}
  double getThetaError(){return m_thetaError;}
  double getVert_dz(){return m_vert_dz;}
  double getPF_photonIso(){return m_PF_photonIso;}
  int getOutermostMuonStationWithValidHits(){return m_outermostMuonStationWithValidHits;}
  double getPhiError(){return m_phiError;}
  int getNAnyMuonHitsInFirstStation(){return m_nAnyMuonHitsInFirstStation;}
  double getTrackIso6(){return m_trackIso6;}
  int getNtrackerLayersWM(){return m_ntrackerLayersWM;}
  double getTrackIso2(){return m_trackIso2;}
  double getTheta(){return m_theta;}
  int getNLostTrackerHits(){return m_nLostTrackerHits;}
  int getIsMuon(){return m_isMuon;}
  double getTrackIso9(){return m_trackIso9;}
  double getD0Error(){return m_d0Error;}
  double getTrackIso1(){return m_trackIso1;}
  int getNBadMuonHits(){return m_nBadMuonHits;}
  double getChi2(){return m_chi2;}
  double getCaloIso6(){return m_caloIso6;}
  double getEtaError(){return m_etaError;}
  double getTrackIso12(){return m_trackIso12;}
  double getNdof(){return m_ndof;}
  int getNstripLayersWM(){return m_nstripLayersWM;}
  double getBeam_dz(){return m_beam_dz;}
  int getIsTracker(){return m_isTracker;}
  int getNValidHits(){return m_nValidHits;}
  double getDzError(){return m_dzError;}
  int getNValidMuonHitsInFirstStation(){return m_nValidMuonHitsInFirstStation;}
  double getDxyError(){return m_dxyError;}
  int getGenParticle_mother_pdgID(){return m_genParticle_mother_pdgID;}
  double getGenParticle_dR(){return m_genParticle_dR;}
  double getPF_neutralHadronIso(){return m_PF_neutralHadronIso;}
  int getNLostMuonHitsInFirstStation(){return m_nLostMuonHitsInFirstStation;}
  int getGenParticle_pdgID(){return m_genParticle_pdgID;}
  double getBeam_dxy(){return m_beam_dxy;}
  double getCaloIso12(){return m_caloIso12;}
  int getMuonStationsWAH(){return m_muonStationsWAH;}
  int getNLostMuonHits(){return m_nLostMuonHits;}
  int getNLostHits(){return m_nLostHits;}
  int getMuonStationsWVH(){return m_muonStationsWVH;}
  double getBeam_d0(){return m_beam_d0;}
  double getVertWeight(){return m_vertWeight;}
  double getRelIso();
  double getTotalIso();

  void setDz(double c){m_dz = c;}
  void setGenParticle_ntID(int c){m_genParticle_ntID = c;}
  void setGenParticle(SignatureObjectMCPart* genParticle){m_genParticle = genParticle;}
  void setCaloIso9(double c){m_caloIso9 = c;}
  void setDxy(double c){m_dxy = c;}
  void setNValidMuonHits(int c){m_nValidMuonHits = c;}
  void setCaloIso2(double c){m_caloIso2 = c;}
  void setVert_dxy(double c){m_vert_dxy = c;}
  void setCharge(double c){m_charge = c;}
  void setCaloIso1(double c){m_caloIso1 = c;}
  void setIsGlobal(int c){m_isGlobal = c;}
  void setBeam_dsz(double c){m_beam_dsz = c;}
  void setNLostPixelHits(int c){m_nLostPixelHits = c;}
  void setNpixelLayersWM(int c){m_npixelLayersWM = c;}
  void setVx(double c){m_vx = c;}
  void setVy(double c){m_vy = c;}
  void setLambdaError(double c){m_lambdaError = c;}
  void setPF_chargedHadronIso(double c){m_PF_chargedHadronIso = c;}
  void setNValidPixelHits(int c){m_nValidPixelHits = c;}
  void setVz(double c){m_vz = c;}
  void setD0(double c){m_d0 = c;}
  void setGenParticle_mother_ntID(int c){m_genParticle_mother_ntID = c;}
  void setDsz(double c){m_dsz = c;}
  void setNValidTrackerHits(int c){m_nValidTrackerHits = c;}
  void setNBadMuonHitsInFirstStation(int c){m_nBadMuonHitsInFirstStation = c;}
  void setThetaError(double c){m_thetaError = c;}
  void setVert_dz(double c){m_vert_dz = c;}
  void setPF_photonIso(double c){m_PF_photonIso = c;}
  void setOutermostMuonStationWithValidHits(int c){m_outermostMuonStationWithValidHits = c;}
  void setPhiError(double c){m_phiError = c;}
  void setNAnyMuonHitsInFirstStation(int c){m_nAnyMuonHitsInFirstStation = c;}
  void setTrackIso6(double c){m_trackIso6 = c;}
  void setNtrackerLayersWM(int c){m_ntrackerLayersWM = c;}
  void setTrackIso2(double c){m_trackIso2 = c;}
  void setTheta(double c){m_theta = c;}
  void setNLostTrackerHits(int c){m_nLostTrackerHits = c;}
  void setIsMuon(int c){m_isMuon = c;}
  void setTrackIso9(double c){m_trackIso9 = c;}
  void setD0Error(double c){m_d0Error = c;}
  void setTrackIso1(double c){m_trackIso1 = c;}
  void setNBadMuonHits(int c){m_nBadMuonHits = c;}
  void setChi2(double c){m_chi2 = c;}
  void setCaloIso6(double c){m_caloIso6 = c;}
  void setEtaError(double c){m_etaError = c;}
  void setTrackIso12(double c){m_trackIso12 = c;}
  void setNdof(double c){m_ndof = c;}
  void setNstripLayersWM(int c){m_nstripLayersWM = c;}
  void setBeam_dz(double c){m_beam_dz = c;}
  void setIsTracker(int c){m_isTracker = c;}
  void setNValidHits(int c){m_nValidHits = c;}
  void setDzError(double c){m_dzError = c;}
  void setNValidMuonHitsInFirstStation(int c){m_nValidMuonHitsInFirstStation = c;}
  void setDxyError(double c){m_dxyError = c;}
  void setGenParticle_mother_pdgID(int c){m_genParticle_mother_pdgID = c;}
  void setGenParticle_dR(double c){m_genParticle_dR = c;}
  void setPF_neutralHadronIso(double c){m_PF_neutralHadronIso = c;}
  void setNLostMuonHitsInFirstStation(int c){m_nLostMuonHitsInFirstStation = c;}
  void setGenParticle_pdgID(int c){m_genParticle_pdgID = c;}
  void setBeam_dxy(double c){m_beam_dxy = c;}
  void setCaloIso12(double c){m_caloIso12 = c;}
  void setMuonStationsWAH(int c){m_muonStationsWAH = c;}
  void setNLostMuonHits(int c){m_nLostMuonHits = c;}
  void setNLostHits(int c){m_nLostHits = c;}
  void setMuonStationsWVH(int c){m_muonStationsWVH = c;}
  void setBeam_d0(double c){m_beam_d0 = c;}
  void setVertWeight(double c){m_vertWeight = c;}

 private:
  double m_dz;
  int m_genParticle_ntID;
  SignatureObjectMCPart* m_genParticle;
  double m_caloIso9;
  double m_dxy;
  int m_nValidMuonHits;
  double m_caloIso2;
  double m_vert_dxy;
  double m_charge;
  double m_caloIso1;
  int m_isGlobal;
  double m_beam_dsz;
  int m_nLostPixelHits;
  int m_npixelLayersWM;
  double m_vx;
  double m_vy;
  double m_lambdaError;
  double m_PF_chargedHadronIso;
  int m_nValidPixelHits;
  double m_vz;
  double m_d0;
  int m_genParticle_mother_ntID;
  double m_dsz;
  int m_nValidTrackerHits;
  int m_nBadMuonHitsInFirstStation;
  double m_thetaError;
  double m_vert_dz;
  double m_PF_photonIso;
  int m_outermostMuonStationWithValidHits;
  double m_phiError;
  int m_nAnyMuonHitsInFirstStation;
  double m_trackIso6;
  int m_ntrackerLayersWM;
  double m_trackIso2;
  double m_theta;
  int m_nLostTrackerHits;
  int m_isMuon;
  double m_trackIso9;
  double m_d0Error;
  double m_trackIso1;
  int m_nBadMuonHits;
  double m_chi2;
  double m_caloIso6;
  double m_etaError;
  double m_trackIso12;
  double m_ndof;
  int m_nstripLayersWM;
  double m_beam_dz;
  int m_isTracker;
  int m_nValidHits;
  double m_dzError;
  int m_nValidMuonHitsInFirstStation;
  double m_dxyError;
  int m_genParticle_mother_pdgID;
  double m_genParticle_dR;
  double m_PF_neutralHadronIso;
  int m_nLostMuonHitsInFirstStation;
  int m_genParticle_pdgID;
  double m_beam_dxy;
  double m_caloIso12;
  int m_muonStationsWAH;
  int m_nLostMuonHits;
  int m_nLostHits;
  int m_muonStationsWVH;
  double m_beam_d0;
  double m_vertWeight;


  ClassDef(SignatureObjectRecoTrack,1);

};

inline SignatureObjectRecoTrack::SignatureObjectRecoTrack(double x,double y, double z, double t):SignatureObjectWithIso(x,y,z,t){
  m_dz = -10000;
  m_genParticle_ntID = -10000;
  m_genParticle = 0;
  m_caloIso9 = -10000;
  m_dxy = -10000;
  m_nValidMuonHits = -10000;
  m_caloIso2 = -10000;
  m_vert_dxy = -10000;
  m_charge = -10000;
  m_caloIso1 = -10000;
  m_isGlobal = -10000;
  m_beam_dsz = -10000;
  m_nLostPixelHits = -10000;
  m_npixelLayersWM = -10000;
  m_vx = -10000;
  m_vy = -10000;
  m_lambdaError = -10000;
  m_PF_chargedHadronIso = -10000;
  m_nValidPixelHits = -10000;
  m_vz = -10000;
  m_d0 = -10000;
  m_genParticle_mother_ntID = -10000;
  m_dsz = -10000;
  m_nValidTrackerHits = -10000;
  m_nBadMuonHitsInFirstStation = -10000;
  m_thetaError = -10000;
  m_vert_dz = -10000;
  m_PF_photonIso = -10000;
  m_outermostMuonStationWithValidHits = -10000;
  m_phiError = -10000;
  m_nAnyMuonHitsInFirstStation = -10000;
  m_trackIso6 = -10000;
  m_ntrackerLayersWM = -10000;
  m_trackIso2 = -10000;
  m_theta = -10000;
  m_nLostTrackerHits = -10000;
  m_isMuon = -10000;
  m_trackIso9 = -10000;
  m_d0Error = -10000;
  m_trackIso1 = -10000;
  m_nBadMuonHits = -10000;
  m_chi2 = -10000;
  m_caloIso6 = -10000;
  m_etaError = -10000;
  m_trackIso12 = -10000;
  m_ndof = -10000;
  m_nstripLayersWM = -10000;
  m_beam_dz = -10000;
  m_isTracker = -10000;
  m_nValidHits = -10000;
  m_dzError = -10000;
  m_nValidMuonHitsInFirstStation = -10000;
  m_dxyError = -10000;
  m_genParticle_mother_pdgID = -10000;
  m_genParticle_dR = -10000;
  m_PF_neutralHadronIso = -10000;
  m_nLostMuonHitsInFirstStation = -10000;
  m_genParticle_pdgID = -10000;
  m_beam_dxy = -10000;
  m_caloIso12 = -10000;
  m_muonStationsWAH = -10000;
  m_nLostMuonHits = -10000;
  m_nLostHits = -10000;
  m_muonStationsWVH = -10000;
  m_beam_d0 = -10000;
  m_vertWeight = -10000;
}

inline SignatureObjectRecoTrack::SignatureObjectRecoTrack(TLorentzVector v):SignatureObjectWithIso(v){
  m_dz = -10000;
  m_genParticle_ntID = -10000;
  m_genParticle = 0;
  m_caloIso9 = -10000;
  m_dxy = -10000;
  m_nValidMuonHits = -10000;
  m_caloIso2 = -10000;
  m_vert_dxy = -10000;
  m_charge = -10000;
  m_caloIso1 = -10000;
  m_isGlobal = -10000;
  m_beam_dsz = -10000;
  m_nLostPixelHits = -10000;
  m_npixelLayersWM = -10000;
  m_vx = -10000;
  m_vy = -10000;
  m_lambdaError = -10000;
  m_PF_chargedHadronIso = -10000;
  m_nValidPixelHits = -10000;
  m_vz = -10000;
  m_d0 = -10000;
  m_genParticle_mother_ntID = -10000;
  m_dsz = -10000;
  m_nValidTrackerHits = -10000;
  m_nBadMuonHitsInFirstStation = -10000;
  m_thetaError = -10000;
  m_vert_dz = -10000;
  m_PF_photonIso = -10000;
  m_outermostMuonStationWithValidHits = -10000;
  m_phiError = -10000;
  m_nAnyMuonHitsInFirstStation = -10000;
  m_trackIso6 = -10000;
  m_ntrackerLayersWM = -10000;
  m_trackIso2 = -10000;
  m_theta = -10000;
  m_nLostTrackerHits = -10000;
  m_isMuon = -10000;
  m_trackIso9 = -10000;
  m_d0Error = -10000;
  m_trackIso1 = -10000;
  m_nBadMuonHits = -10000;
  m_chi2 = -10000;
  m_caloIso6 = -10000;
  m_etaError = -10000;
  m_trackIso12 = -10000;
  m_ndof = -10000;
  m_nstripLayersWM = -10000;
  m_beam_dz = -10000;
  m_isTracker = -10000;
  m_nValidHits = -10000;
  m_dzError = -10000;
  m_nValidMuonHitsInFirstStation = -10000;
  m_dxyError = -10000;
  m_genParticle_mother_pdgID = -10000;
  m_genParticle_dR = -10000;
  m_PF_neutralHadronIso = -10000;
  m_nLostMuonHitsInFirstStation = -10000;
  m_genParticle_pdgID = -10000;
  m_beam_dxy = -10000;
  m_caloIso12 = -10000;
  m_muonStationsWAH = -10000;
  m_nLostMuonHits = -10000;
  m_nLostHits = -10000;
  m_muonStationsWVH = -10000;
  m_beam_d0 = -10000;
  m_vertWeight = -10000;
}
inline double SignatureObjectRecoTrack::getRelIso()
{
  if(Pt() < 0)return 9999999999.0;
  return getTotalIso()/Pt();
}
inline double SignatureObjectRecoTrack::getTotalIso()
{
	if(getPF_photonIso() < 0 || getPF_neutralHadronIso() < 0 || getPF_chargedHadronIso() < 0) {
		return 1e6;
	}
	return std::max(getPF_photonIso()+getPF_neutralHadronIso()-getRho() * getPhotonPlusNeutralHadronEffectiveArea(),0.0)+getPF_chargedHadronIso();
}
#endif
