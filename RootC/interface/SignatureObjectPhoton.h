#ifndef SignatureObjectPhoton_h
#define SignatureObjectPhoton_h

#include <vector>
#include "RutgersIAF2012/RootC/interface/SignatureObjectWithIso.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class SignatureObjectPhoton : public SignatureObjectWithIso {
 public:
  SignatureObjectPhoton(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectPhoton(TLorentzVector v);
  virtual ~SignatureObjectPhoton() {/* no-op */}
  double getRelIso();
  double getTotalIso();

  double getPhotonIso(){return m_photonIso;}
  int getGenPhoton_pdgID(){return m_genPhoton_pdgID;}
  int getEndcap(){return m_endcap;}
  int getTrack_nSolidR03(){return m_track_nSolidR03;}
  double getNeutralHadronIso(){return m_neutralHadronIso;}
  int getIsLoose(){return m_isLoose;}
  double getHcalDepth2TowerEtR04(){return m_hcalDepth2TowerEtR04;}
  double getChargedHadronIso(){return m_chargedHadronIso;}
  float getEOut(){return m_EOut;}
  std::vector<int> getTrigger_objectType(){return m_trigger_objectType;}
  int getTrigger_objectTypeAt(int i){return m_trigger_objectType[i];}
  double getScEt(){return m_scEt;}
  double getEcalRecHitEtR04(){return m_ecalRecHitEtR04;}
  double getEcalRecHitEtR03(){return m_ecalRecHitEtR03;}
  int getConversionSafeElectronVeto(){return m_conversionSafeElectronVeto;}
  int getGenPhoton_ntID(){return m_genPhoton_ntID;}
  SignatureObjectMCPart* getGenPhoton(){return m_genPhoton;}
  double getTrackSumPtSolidR04(){return m_trackSumPtSolidR04;}
  double getHadTowOverEm(){return m_hadTowOverEm;}
  double getSigmaIetaIeta(){return m_sigmaIetaIeta;}
  double getPFPhotonRes(){return m_PFPhotonRes;}
  double getMVAGlobalCorrEError(){return m_MVAGlobalCorrEError;}
  double getHcalTowerEtR04(){return m_hcalTowerEtR04;}
  double getHcalDepth1TowerEtR03(){return m_hcalDepth1TowerEtR03;}
  float getMustacheEt(){return m_mustacheEt;}
  double getHcalDepth1TowerEtR04(){return m_hcalDepth1TowerEtR04;}
  double getHcalTowerEtR03(){return m_hcalTowerEtR03;}
  int getTrack_nHollowR03(){return m_track_nHollowR03;}
  int getTrack_nHollowR04(){return m_track_nHollowR04;}
  int getTrack_nSolidR04(){return m_track_nSolidR04;}
  int getIsTight(){return m_isTight;}
  float getMVAGlobalCorrE(){return m_MVAGlobalCorrE;}
  double getHadOverEm(){return m_hadOverEm;}
  std::vector<int> getTrigger_objectID(){return m_trigger_objectID;}
  int getTrigger_objectIDAt(int i){return m_trigger_objectID[i];}
  double getR9(){return m_r9;}
  int getTrigger_nfilter(){return m_trigger_nfilter;}
  double getTrackSumPtHollowR04(){return m_trackSumPtHollowR04;}
  int getBarrel(){return m_barrel;}
  double getTrackSumPtSolidR03(){return m_trackSumPtSolidR03;}
  double getHcalDepth2TowerEtR03(){return m_hcalDepth2TowerEtR03;}
  double getTrackSumPtHollowR03(){return m_trackSumPtHollowR03;}

  void setPhotonIso(double c){m_photonIso = c;}
  void setGenPhoton_pdgID(int c){m_genPhoton_pdgID = c;}
  void setEndcap(int c){m_endcap = c;}
  void setTrack_nSolidR03(int c){m_track_nSolidR03 = c;}
  void setNeutralHadronIso(double c){m_neutralHadronIso = c;}
  void setIsLoose(int c){m_isLoose = c;}
  void setHcalDepth2TowerEtR04(double c){m_hcalDepth2TowerEtR04 = c;}
  void setChargedHadronIso(double c){m_chargedHadronIso = c;}
  void setEOut(float c){m_EOut = c;}
  void addTrigger_objectType(int c){m_trigger_objectType.push_back(c);}
  void setScEt(double c){m_scEt = c;}
  void setEcalRecHitEtR04(double c){m_ecalRecHitEtR04 = c;}
  void setEcalRecHitEtR03(double c){m_ecalRecHitEtR03 = c;}
  void setConversionSafeElectronVeto(int c){m_conversionSafeElectronVeto = c;}
  void setGenPhoton_ntID(int c){m_genPhoton_ntID = c;}
  void setGenPhoton(SignatureObjectMCPart* genPhoton){m_genPhoton = genPhoton;}
  void setTrackSumPtSolidR04(double c){m_trackSumPtSolidR04 = c;}
  void setHadTowOverEm(double c){m_hadTowOverEm = c;}
  void setSigmaIetaIeta(double c){m_sigmaIetaIeta = c;}
  void setPFPhotonRes(double c){m_PFPhotonRes = c;}
  void setMVAGlobalCorrEError(double c){m_MVAGlobalCorrEError = c;}
  void setHcalTowerEtR04(double c){m_hcalTowerEtR04 = c;}
  void setHcalDepth1TowerEtR03(double c){m_hcalDepth1TowerEtR03 = c;}
  void setMustacheEt(float c){m_mustacheEt = c;}
  void setHcalDepth1TowerEtR04(double c){m_hcalDepth1TowerEtR04 = c;}
  void setHcalTowerEtR03(double c){m_hcalTowerEtR03 = c;}
  void setTrack_nHollowR03(int c){m_track_nHollowR03 = c;}
  void setTrack_nHollowR04(int c){m_track_nHollowR04 = c;}
  void setTrack_nSolidR04(int c){m_track_nSolidR04 = c;}
  void setIsTight(int c){m_isTight = c;}
  void setMVAGlobalCorrE(float c){m_MVAGlobalCorrE = c;}
  void setHadOverEm(double c){m_hadOverEm = c;}
  void addTrigger_objectID(int c){m_trigger_objectID.push_back(c);}
  void setR9(double c){m_r9 = c;}
  void setTrigger_nfilter(int c){m_trigger_nfilter = c;}
  void setTrackSumPtHollowR04(double c){m_trackSumPtHollowR04 = c;}
  void setBarrel(int c){m_barrel = c;}
  void setTrackSumPtSolidR03(double c){m_trackSumPtSolidR03 = c;}
  void setHcalDepth2TowerEtR03(double c){m_hcalDepth2TowerEtR03 = c;}
  void setTrackSumPtHollowR03(double c){m_trackSumPtHollowR03 = c;}

 private:
  double m_photonIso;
  int m_genPhoton_pdgID;
  int m_endcap;
  int m_track_nSolidR03;
  double m_neutralHadronIso;
  int m_isLoose;
  double m_hcalDepth2TowerEtR04;
  double m_chargedHadronIso;
  float m_EOut;
  std::vector<int> m_trigger_objectType;
  double m_scEt;
  double m_ecalRecHitEtR04;
  double m_ecalRecHitEtR03;
  int m_conversionSafeElectronVeto;
  int m_genPhoton_ntID;
  SignatureObjectMCPart* m_genPhoton;
  double m_trackSumPtSolidR04;
  double m_hadTowOverEm;
  double m_sigmaIetaIeta;
  double m_PFPhotonRes;
  double m_MVAGlobalCorrEError;
  double m_hcalTowerEtR04;
  double m_hcalDepth1TowerEtR03;
  float m_mustacheEt;
  double m_hcalDepth1TowerEtR04;
  double m_hcalTowerEtR03;
  int m_track_nHollowR03;
  int m_track_nHollowR04;
  int m_track_nSolidR04;
  int m_isTight;
  float m_MVAGlobalCorrE;
  double m_hadOverEm;
  std::vector<int> m_trigger_objectID;
  double m_r9;
  int m_trigger_nfilter;
  double m_trackSumPtHollowR04;
  int m_barrel;
  double m_trackSumPtSolidR03;
  double m_hcalDepth2TowerEtR03;
  double m_trackSumPtHollowR03;

  ClassDef(SignatureObjectPhoton,1);

};

inline SignatureObjectPhoton::SignatureObjectPhoton(double x,double y, double z, double t):SignatureObjectWithIso(x,y,z,t){
  m_pdgid = 22;

  m_photonIso = -10000;
  m_genPhoton_pdgID = -10000;
  m_endcap = -10000;
  m_track_nSolidR03 = -10000;
  m_neutralHadronIso = -10000;
  m_isLoose = -10000;
  m_hcalDepth2TowerEtR04 = -10000;
  m_chargedHadronIso = -10000;
  m_EOut = -10000;
  m_scEt = -10000;
  m_ecalRecHitEtR04 = -10000;
  m_ecalRecHitEtR03 = -10000;
  m_conversionSafeElectronVeto = -10000;
  m_genPhoton_ntID = -10000;
  m_genPhoton = 0;
  m_trackSumPtSolidR04 = -10000;
  m_hadTowOverEm = -10000;
  m_sigmaIetaIeta = -10000;
  m_PFPhotonRes = -10000;
  m_MVAGlobalCorrEError = -10000;
  m_hcalTowerEtR04 = -10000;
  m_hcalDepth1TowerEtR03 = -10000;
  m_mustacheEt = -10000;
  m_hcalDepth1TowerEtR04 = -10000;
  m_hcalTowerEtR03 = -10000;
  m_track_nHollowR03 = -10000;
  m_track_nHollowR04 = -10000;
  m_track_nSolidR04 = -10000;
  m_isTight = -10000;
  m_MVAGlobalCorrE = -10000;
  m_hadOverEm = -10000;
  m_r9 = -10000;
  m_trigger_nfilter = -10000;
  m_trackSumPtHollowR04 = -10000;
  m_barrel = -10000;
  m_trackSumPtSolidR03 = -10000;
  m_hcalDepth2TowerEtR03 = -10000;
  m_trackSumPtHollowR03 = -10000;

}

inline SignatureObjectPhoton::SignatureObjectPhoton(TLorentzVector v):SignatureObjectWithIso(v){
  m_pdgid = 22;
  m_photonIso = -10000;
  m_genPhoton_pdgID = -10000;
  m_endcap = -10000;
  m_track_nSolidR03 = -10000;
  m_neutralHadronIso = -10000;
  m_isLoose = -10000;
  m_hcalDepth2TowerEtR04 = -10000;
  m_chargedHadronIso = -10000;
  m_EOut = -10000;
  m_scEt = -10000;
  m_ecalRecHitEtR04 = -10000;
  m_ecalRecHitEtR03 = -10000;
  m_conversionSafeElectronVeto = -10000;
  m_genPhoton_ntID = -10000;
  m_genPhoton = 0;
  m_trackSumPtSolidR04 = -10000;
  m_hadTowOverEm = -10000;
  m_sigmaIetaIeta = -10000;
  m_PFPhotonRes = -10000;
  m_MVAGlobalCorrEError = -10000;
  m_hcalTowerEtR04 = -10000;
  m_hcalDepth1TowerEtR03 = -10000;
  m_mustacheEt = -10000;
  m_hcalDepth1TowerEtR04 = -10000;
  m_hcalTowerEtR03 = -10000;
  m_track_nHollowR03 = -10000;
  m_track_nHollowR04 = -10000;
  m_track_nSolidR04 = -10000;
  m_isTight = -10000;
  m_MVAGlobalCorrE = -10000;
  m_hadOverEm = -10000;
  m_r9 = -10000;
  m_trigger_nfilter = -10000;
  m_trackSumPtHollowR04 = -10000;
  m_barrel = -10000;
  m_trackSumPtSolidR03 = -10000;
  m_hcalDepth2TowerEtR03 = -10000;
  m_trackSumPtHollowR03 = -10000;

}

inline double SignatureObjectPhoton::getRelIso(){
  if (Pt() < 0) return 9999999.9;
  return getTotalIso()/Pt();
}
inline double SignatureObjectPhoton::getTotalIso(){
  return getRhoCorrectedPFChargedHadronIsolation() + getRhoCorrectedPFNeutralHadronIsolation() + getRhoCorrectedPFPhotonIsolation();
}
#endif
