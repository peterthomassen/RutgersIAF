#ifndef SignatureObjectMuon_h
#define SignatureObjectMuon_h

#include <vector>
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class SignatureObjectMuon : public SignatureObjectRecoTrack {
 public:
  SignatureObjectMuon(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectMuon(TLorentzVector v);
  virtual ~SignatureObjectMuon() {/* no-op */}
  double getRelIso();
  double getTotalIso();

  int getIsGlobalMuon(){return m_isGlobalMuon;}
  int getGlobalTrackID(){return m_globalTrackID;}
  double getDRmin10(){return m_dRmin10;}
  int getTrackID(){return m_trackID;}
  double getPF_chargedHadronIso_04(){return m_PF_chargedHadronIso_04;}
  int getPFMatchPdgId(){return m_PFMatchPdgId;}
  int getIsTMLastStationAngTight(){return m_isTMLastStationAngTight;}
  double getPF_neutralHadronIso_04(){return m_PF_neutralHadronIso_04;}
  double getPFPAT_dq(){return m_PFPAT_dq;}
  int getIsPF(){return m_isPF;}
  double getPFPAT_deta(){return m_PFPAT_deta;}
  int getDirection(){return m_Direction;}
  int getIsGlobalMuonPromptTight(){return m_isGlobalMuonPromptTight;}
  double getDRmin(){return m_dRmin;}
  std::vector<int> getTrigger_objectType(){return m_trigger_objectType;}
  int getTrigger_objectTypeAt(int i){return m_trigger_objectType[i];}
  double getCalEnergyHad(){return m_calEnergyHad;}
  float getCaloCompatibility(){return m_caloCompatibility;}
  int getDRmin_track_ntID(){return m_dRmin_track_ntID;}
  float getSegmentCompatibility(){return m_segmentCompatibility;}
  float getOverlapCompatibility(){return m_overlapCompatibility;}
  int getIsCaloMuon(){return m_isCaloMuon;}
  float getCosmicCompatibility(){return m_cosmicCompatibility;}
  int getIsTMLastStationTight(){return m_isTMLastStationTight;}
  int getIsCaloCompatibilityValid(){return m_isCaloCompatibilityValid;}
  int getNumberOfMatches(){return m_numberOfMatches;}
  double getPFPAT_dpt(){return m_PFPAT_dpt;}
  int getGenLepton_pdgID(){return m_genLepton_pdgID;}
  double getCalEnergyEM(){return m_calEnergyEM;}
  int getDRmin05_track_ntID(){return m_dRmin05_track_ntID;}
  double getDRmin05(){return m_dRmin05;}
  double getGenLepton_dR(){return m_genLepton_dR;}
  int getMuonTrackID(){return m_muonTrackID;}
  int getIsTrackerMuon(){return m_isTrackerMuon;}
  float getBackToBackCompatibility(){return m_backToBackCompatibility;}
  std::vector<int> getTrigger_objectID(){return m_trigger_objectID;}
  int getTrigger_objectIDAt(int i){return m_trigger_objectID[i];}
  double getPF_photonIso_04(){return m_PF_photonIso_04;}
  double getPFPAT_dphi(){return m_PFPAT_dphi;}
  int getIsStandAloneMuon(){return m_isStandAloneMuon;}
  int getDRmin10_track_ntID(){return m_dRmin10_track_ntID;}
  int getGenLepton_mother_ntID(){return m_genLepton_mother_ntID;}
  int getTrigger_nfilter(){return m_trigger_nfilter;}
  float getTimeCompatibility(){return m_timeCompatibility;}
  int getGenLepton_mother_pdgID(){return m_genLepton_mother_pdgID;}
  int getGenLepton_ntID(){return m_genLepton_ntID;}
  SignatureObjectMCPart* getGenLepton(){return m_genLepton;}
  double getBeta(){return m_beta;}
  float getInnerVertDxy(){return m_innerVertDxy;}
  int getInnerNumberOfValidPixelHits(){return m_innerNumberOfValidPixelHits;}
  float getInnerVertDz(){return m_innerVertDz;}
  float getNormalizedChi2(){return m_normalizedChi2;}

  void setIsGlobalMuon(int c){m_isGlobalMuon = c;}
  void setGlobalTrackID(int c){m_globalTrackID = c;}
  void setDRmin10(double c){m_dRmin10 = c;}
  void setTrackID(int c){m_trackID = c;}
  void setPF_chargedHadronIso_04(double c){m_PF_chargedHadronIso_04 = c;}
  void setPFMatchPdgId(int c){m_PFMatchPdgId = c;}
  void setIsTMLastStationAngTight(int c){m_isTMLastStationAngTight = c;}
  void setPF_neutralHadronIso_04(double c){m_PF_neutralHadronIso_04 = c;}
  void setPFPAT_dq(double c){m_PFPAT_dq = c;}
  void setIsPF(int c){m_isPF = c;}
  void setPFPAT_deta(double c){m_PFPAT_deta = c;}
  void setDirection(int c){m_Direction = c;}
  void setIsGlobalMuonPromptTight(int c){m_isGlobalMuonPromptTight = c;}
  void setDRmin(double c){m_dRmin = c;}
  void addTrigger_objectType(int c){m_trigger_objectType.push_back(c);}
  void setCalEnergyHad(double c){m_calEnergyHad = c;}
  void setCaloCompatibility(float c){m_caloCompatibility = c;}
  void setDRmin_track_ntID(int c){m_dRmin_track_ntID = c;}
  void setSegmentCompatibility(float c){m_segmentCompatibility = c;}
  void setOverlapCompatibility(float c){m_overlapCompatibility = c;}
  void setIsCaloMuon(int c){m_isCaloMuon = c;}
  void setCosmicCompatibility(float c){m_cosmicCompatibility = c;}
  void setIsTMLastStationTight(int c){m_isTMLastStationTight = c;}
  void setIsCaloCompatibilityValid(int c){m_isCaloCompatibilityValid = c;}
  void setNumberOfMatches(int c){m_numberOfMatches = c;}
  void setPFPAT_dpt(double c){m_PFPAT_dpt = c;}
  void setGenLepton_pdgID(int c){m_genLepton_pdgID = c;}
  void setCalEnergyEM(double c){m_calEnergyEM = c;}
  void setDRmin05_track_ntID(int c){m_dRmin05_track_ntID = c;}
  void setDRmin05(double c){m_dRmin05 = c;}
  void setGenLepton_dR(double c){m_genLepton_dR = c;}
  void setMuonTrackID(int c){m_muonTrackID = c;}
  void setIsTrackerMuon(int c){m_isTrackerMuon = c;}
  void setBackToBackCompatibility(float c){m_backToBackCompatibility = c;}
  void addTrigger_objectID(int c){m_trigger_objectID.push_back(c);}
  void setPF_photonIso_04(double c){m_PF_photonIso_04 = c;}
  void setPFPAT_dphi(double c){m_PFPAT_dphi = c;}
  void setIsStandAloneMuon(int c){m_isStandAloneMuon = c;}
  void setDRmin10_track_ntID(int c){m_dRmin10_track_ntID = c;}
  void setGenLepton_mother_ntID(int c){m_genLepton_mother_ntID = c;}
  void setTrigger_nfilter(int c){m_trigger_nfilter = c;}
  void setTimeCompatibility(float c){m_timeCompatibility = c;}
  void setGenLepton_mother_pdgID(int c){m_genLepton_mother_pdgID = c;}
  void setGenLepton_ntID(int c){m_genLepton_ntID = c;}
  void setGenLepton(SignatureObjectMCPart* genLepton){m_genLepton = genLepton;}
  void setBeta(double c){m_beta = c;}
  void setInnerVertDxy(float c){m_innerVertDxy = c;}
  void setInnerNumberOfValidPixelHits(int c){m_innerNumberOfValidPixelHits = c;}
  void setInnerVertDz(float c){m_innerVertDz = c;}
  void setNormalizedChi2(float c){m_normalizedChi2 = c;}

 private:
  int m_isGlobalMuon;
  int m_globalTrackID;
  double m_dRmin10;
  int m_trackID;
  double m_PF_chargedHadronIso_04;
  int m_PFMatchPdgId;
  int m_isTMLastStationAngTight;
  double m_PF_neutralHadronIso_04;
  double m_PFPAT_dq;
  int m_isPF;
  double m_PFPAT_deta;
  int m_Direction;
  int m_isGlobalMuonPromptTight;
  double m_dRmin;
  std::vector<int> m_trigger_objectType;
  double m_calEnergyHad;
  float m_caloCompatibility;
  int m_dRmin_track_ntID;
  float m_segmentCompatibility;
  float m_overlapCompatibility;
  int m_isCaloMuon;
  float m_cosmicCompatibility;
  int m_isTMLastStationTight;
  int m_isCaloCompatibilityValid;
  int m_numberOfMatches;
  double m_PFPAT_dpt;
  int m_genLepton_pdgID;
  double m_calEnergyEM;
  int m_dRmin05_track_ntID;
  double m_dRmin05;
  double m_genLepton_dR;
  int m_muonTrackID;
  int m_isTrackerMuon;
  float m_backToBackCompatibility;
  std::vector<int> m_trigger_objectID;
  double m_PF_photonIso_04;
  double m_PFPAT_dphi;
  int m_isStandAloneMuon;
  int m_dRmin10_track_ntID;
  int m_genLepton_mother_ntID;
  int m_trigger_nfilter;
  float m_timeCompatibility;
  int m_genLepton_mother_pdgID;
  int m_genLepton_ntID;
  SignatureObjectMCPart* m_genLepton;
  double m_beta;
  float m_innerVertDxy;
  int m_innerNumberOfValidPixelHits;
  float m_innerVertDz;
  float m_normalizedChi2;


  ClassDef(SignatureObjectMuon,1);

};

inline SignatureObjectMuon::SignatureObjectMuon(double x,double y, double z, double t):SignatureObjectRecoTrack(x,y,z,t){
  m_pdgid = 13;

  m_isGlobalMuon = -10000;
  m_globalTrackID = -10000;
  m_dRmin10 = -10000;
  m_trackID = -10000;
  m_PF_chargedHadronIso_04 = -10000;
  m_PFMatchPdgId = -10000;
  m_isTMLastStationAngTight = -10000;
  m_PF_neutralHadronIso_04 = -10000;
  m_PFPAT_dq = -10000;
  m_isPF = -10000;
  m_PFPAT_deta = -10000;
  m_Direction = -10000;
  m_isGlobalMuonPromptTight = -10000;
  m_dRmin = -10000;
  m_calEnergyHad = -10000;
  m_caloCompatibility = -10000;
  m_dRmin_track_ntID = -10000;
  m_segmentCompatibility = -10000;
  m_overlapCompatibility = -10000;
  m_isCaloMuon = -10000;
  m_cosmicCompatibility = -10000;
  m_isTMLastStationTight = -10000;
  m_isCaloCompatibilityValid = -10000;
  m_numberOfMatches = -10000;
  m_PFPAT_dpt = -10000;
  m_genLepton_pdgID = -10000;
  m_calEnergyEM = -10000;
  m_dRmin05_track_ntID = -10000;
  m_dRmin05 = -10000;
  m_genLepton_dR = -10000;
  m_muonTrackID = -10000;
  m_isTrackerMuon = -10000;
  m_backToBackCompatibility = -10000;
  m_PF_photonIso_04 = -10000;
  m_PFPAT_dphi = -10000;
  m_isStandAloneMuon = -10000;
  m_dRmin10_track_ntID = -10000;
  m_genLepton_mother_ntID = -10000;
  m_trigger_nfilter = -10000;
  m_timeCompatibility = -10000;
  m_genLepton_mother_pdgID = -10000;
  m_genLepton_ntID = -10000;
  m_genLepton = 0;
  m_beta = -10000;
  m_innerVertDxy = -10000;
  m_innerNumberOfValidPixelHits = -10000;
  m_innerVertDz = -10000;
  m_normalizedChi2 = -10000;

}

inline SignatureObjectMuon::SignatureObjectMuon(TLorentzVector v):SignatureObjectRecoTrack(v){
  m_pdgid = 13;

  m_isGlobalMuon = -10000;
  m_globalTrackID = -10000;
  m_dRmin10 = -10000;
  m_trackID = -10000;
  m_PF_chargedHadronIso_04 = -10000;
  m_PFMatchPdgId = -10000;
  m_isTMLastStationAngTight = -10000;
  m_PF_neutralHadronIso_04 = -10000;
  m_PFPAT_dq = -10000;
  m_isPF = -10000;
  m_PFPAT_deta = -10000;
  m_Direction = -10000;
  m_isGlobalMuonPromptTight = -10000;
  m_dRmin = -10000;
  m_calEnergyHad = -10000;
  m_caloCompatibility = -10000;
  m_dRmin_track_ntID = -10000;
  m_segmentCompatibility = -10000;
  m_overlapCompatibility = -10000;
  m_isCaloMuon = -10000;
  m_cosmicCompatibility = -10000;
  m_isTMLastStationTight = -10000;
  m_isCaloCompatibilityValid = -10000;
  m_numberOfMatches = -10000;
  m_PFPAT_dpt = -10000;
  m_genLepton_pdgID = -10000;
  m_calEnergyEM = -10000;
  m_dRmin05_track_ntID = -10000;
  m_dRmin05 = -10000;
  m_genLepton_dR = -10000;
  m_muonTrackID = -10000;
  m_isTrackerMuon = -10000;
  m_backToBackCompatibility = -10000;
  m_PF_photonIso_04 = -10000;
  m_PFPAT_dphi = -10000;
  m_isStandAloneMuon = -10000;
  m_dRmin10_track_ntID = -10000;
  m_genLepton_mother_ntID = -10000;
  m_trigger_nfilter = -10000;
  m_timeCompatibility = -10000;
  m_genLepton_mother_pdgID = -10000;
  m_genLepton_ntID = -10000;
  m_genLepton = 0;
  m_beta = -10000;
  m_innerVertDxy = -10000;
  m_innerNumberOfValidPixelHits = -10000;
  m_innerVertDz = -10000;
  m_normalizedChi2 = -10000;

}
inline double SignatureObjectMuon::getRelIso(){
  if(Pt() < 0) return 9999999.0;
  return getTotalIso()/Pt();
}

inline double SignatureObjectMuon::getTotalIso(){
  return getPF_chargedHadronIso() + std::max(0.0,getPF_neutralHadronIso() + getPF_photonIso() - 0.5*getBeta());
}
#endif
