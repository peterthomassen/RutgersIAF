#ifndef SignatureObjectElectron_h
#define SignatureObjectElectron_h

#include <vector>
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class SignatureObjectElectron : public SignatureObjectRecoTrack {
 public:
  SignatureObjectElectron(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectElectron(TLorentzVector v);
  virtual ~SignatureObjectElectron() {/* no-op */}
  double getRelIso();
  double getTotalIso();

  double getMvaTrig(){return m_mvaTrig;}
  double getMvaNoTrig(){return m_mvaNoTrig;}
  double getFbrem(){return m_fbrem;}
  int getTrackID(){return m_trackID;}
  double getPF_chargedHadronIso_04(){return m_PF_chargedHadronIso_04;}
  double getConversionDCotTheta(){return m_ConversionDCotTheta;}
  double getFMVAVar_detacalo(){return m_fMVAVar_detacalo;}
  double getFMVAVar_eta(){return m_fMVAVar_eta;}
  double getFMVAVar_dphicalo(){return m_fMVAVar_dphicalo;}
  double getSwissCross(){return m_swissCross;}
  double getFMVAVar_PreShowerOverRaw(){return m_fMVAVar_PreShowerOverRaw;}
  int getFMVAVar_kfhits(){return m_fMVAVar_kfhits;}
  int getEidTight(){return m_eidTight;}
  int getGenLepton_ntID(){return m_genLepton_ntID;}
  SignatureObjectMCPart* getGenLepton(){return m_genLepton;}
  double getFMVAVar_kfchi2(){return m_fMVAVar_kfchi2;}
  double getHadOverEm(){return m_hadOverEm;}
  double getFMVAVar_IoEmIoP(){return m_fMVAVar_IoEmIoP;}
  double getFMVAVar_pt(){return m_fMVAVar_pt;}
  int getTrigger_nfilter(){return m_trigger_nfilter;}
  double getFMVAVar_phiwidth(){return m_fMVAVar_phiwidth;}
  double getFMVAVar_EoP(){return m_fMVAVar_EoP;}
  double getPFPAT_dphi(){return m_PFPAT_dphi;}
  int getGsfScPixChargeConsistent(){return m_GsfScPixChargeConsistent;}
  double getFMVAVar_eleEoPout(){return m_fMVAVar_eleEoPout;}
  int getPFMatchPdgId(){return m_PFMatchPdgId;}
  double getPF_neutralHadronIso_04(){return m_PF_neutralHadronIso_04;}
  int getEidRobustLoose(){return m_eidRobustLoose;}
  int getIsPF(){return m_isPF;}
  double getFMVAVar_etawidth(){return m_fMVAVar_etawidth;}
  double getDeltaEta(){return m_deltaEta;}
  double getDRmin(){return m_dRmin;}
  double getESeedClusterOverPout(){return m_eSeedClusterOverPout;}
  int getDRmin_track_ntID(){return m_dRmin_track_ntID;}
  double getSigmaIetaIeta(){return m_sigmaIetaIeta;}
  double getFMVAVar_d0(){return m_fMVAVar_d0;}
  double getFMVAVar_dz(){return m_fMVAVar_dz;}
  int getFMVAVar_nbrems(){return m_fMVAVar_nbrems;}
  double getFMVAVar_see(){return m_fMVAVar_see;}
  double getCaloEnergy(){return m_caloEnergy;}
  double getFMVAVar_fbrem(){return m_fMVAVar_fbrem;}
  int getClassification(){return m_classification;}
  double getE2x5Max(){return m_e2x5Max;}
  double getPFPAT_dq(){return m_PFPAT_dq;}
  double getPFPAT_deta(){return m_PFPAT_deta;}
  double getDeltaPhi(){return m_deltaPhi;}
  std::vector<int> getTrigger_objectType(){return m_trigger_objectType;}
  int getTrigger_objectTypeAt(int i){return m_trigger_objectType[i];}
  int getNumberOfLostInnerHits(){return m_NumberOfLostInnerHits;}
  double getConversionDist(){return m_ConversionDist;}
  double getPFPAT_dpt(){return m_PFPAT_dpt;}
  int getGenLepton_pdgID(){return m_genLepton_pdgID;}
  double getFMVAVar_gsfchi2(){return m_fMVAVar_gsfchi2;}
  double getEOverPin(){return m_eOverPin;}
  double getFMVAVar_HoE(){return m_fMVAVar_HoE;}
  int getIsConversion(){return m_IsConversion;}
  int getEcalDriven(){return m_ecalDriven;}
  int getGsfCtfChargeConsistent(){return m_GsfCtfChargeConsistent;}
  double getFMVAVar_spp(){return m_fMVAVar_spp;}
  double getFMVAVar_dphi(){return m_fMVAVar_dphi;}
  double getFMVAVar_e1x5e5x5(){return m_fMVAVar_e1x5e5x5;}
  double getE1x5(){return m_e1x5;}
  int getEidRobustHighEnergy(){return m_eidRobustHighEnergy;}
  double getEMax(){return m_eMax;}
  double getSigmaEtaEta(){return m_sigmaEtaEta;}
  double getConv_vtxProb(){return m_conv_vtxProb;}
  int getStatus(){return m_status;}
  double getE5x5(){return m_e5x5;}
  double getFMVAVar_R9(){return m_fMVAVar_R9;}
  int getEidRobustTight(){return m_eidRobustTight;}
  double getFMVAVar_deta(){return m_fMVAVar_deta;}
  std::vector<int> getTrigger_objectID(){return m_trigger_objectID;}
  int getTrigger_objectIDAt(int i){return m_trigger_objectID[i];}
  double getPF_photonIso_04(){return m_PF_photonIso_04;}
  int getEidLoose(){return m_eidLoose;}
  int getGsfCtfScPixChargeConsistent(){return m_GsfCtfScPixChargeConsistent;}
  int getNumberOfExpectedInnerHits(){return m_NumberOfExpectedInnerHits;}

  void setMvaTrig(double c){m_mvaTrig = c;}
  void setMvaNoTrig(double c){m_mvaNoTrig = c;}
  void setFbrem(double c){m_fbrem = c;}
  void setTrackID(int c){m_trackID = c;}
  void setPF_chargedHadronIso_04(double c){m_PF_chargedHadronIso_04 = c;}
  void setConversionDCotTheta(double c){m_ConversionDCotTheta = c;}
  void setFMVAVar_detacalo(double c){m_fMVAVar_detacalo = c;}
  void setFMVAVar_eta(double c){m_fMVAVar_eta = c;}
  void setFMVAVar_dphicalo(double c){m_fMVAVar_dphicalo = c;}
  void setSwissCross(double c){m_swissCross = c;}
  void setFMVAVar_PreShowerOverRaw(double c){m_fMVAVar_PreShowerOverRaw = c;}
  void setFMVAVar_kfhits(int c){m_fMVAVar_kfhits = c;}
  void setEidTight(int c){m_eidTight = c;}
  void setGenLepton_ntID(int c){m_genLepton_ntID = c;}
  void setGenLepton(SignatureObjectMCPart* genLepton){m_genLepton = genLepton;}
  void setFMVAVar_kfchi2(double c){m_fMVAVar_kfchi2 = c;}
  void setHadOverEm(double c){m_hadOverEm = c;}
  void setFMVAVar_IoEmIoP(double c){m_fMVAVar_IoEmIoP = c;}
  void setFMVAVar_pt(double c){m_fMVAVar_pt = c;}
  void setTrigger_nfilter(int c){m_trigger_nfilter = c;}
  void setFMVAVar_phiwidth(double c){m_fMVAVar_phiwidth = c;}
  void setFMVAVar_EoP(double c){m_fMVAVar_EoP = c;}
  void setPFPAT_dphi(double c){m_PFPAT_dphi = c;}
  void setGsfScPixChargeConsistent(int c){m_GsfScPixChargeConsistent = c;}
  void setFMVAVar_eleEoPout(double c){m_fMVAVar_eleEoPout = c;}
  void setPFMatchPdgId(int c){m_PFMatchPdgId = c;}
  void setPF_neutralHadronIso_04(double c){m_PF_neutralHadronIso_04 = c;}
  void setEidRobustLoose(int c){m_eidRobustLoose = c;}
  void setIsPF(int c){m_isPF = c;}
  void setFMVAVar_etawidth(double c){m_fMVAVar_etawidth = c;}
  void setDeltaEta(double c){m_deltaEta = c;}
  void setDRmin(double c){m_dRmin = c;}
  void setESeedClusterOverPout(double c){m_eSeedClusterOverPout = c;}
  void setDRmin_track_ntID(int c){m_dRmin_track_ntID = c;}
  void setSigmaIetaIeta(double c){m_sigmaIetaIeta = c;}
  void setFMVAVar_d0(double c){m_fMVAVar_d0 = c;}
  void setFMVAVar_dz(double c){m_fMVAVar_dz = c;}
  void setFMVAVar_nbrems(int c){m_fMVAVar_nbrems = c;}
  void setFMVAVar_see(double c){m_fMVAVar_see = c;}
  void setCaloEnergy(double c){m_caloEnergy = c;}
  void setFMVAVar_fbrem(double c){m_fMVAVar_fbrem = c;}
  void setClassification(int c){m_classification = c;}
  void setE2x5Max(double c){m_e2x5Max = c;}
  void setPFPAT_dq(double c){m_PFPAT_dq = c;}
  void setPFPAT_deta(double c){m_PFPAT_deta = c;}
  void setDeltaPhi(double c){m_deltaPhi = c;}
  void addTrigger_objectType(int c){m_trigger_objectType.push_back(c);}
  void setNumberOfLostInnerHits(int c){m_NumberOfLostInnerHits = c;}
  void setConversionDist(double c){m_ConversionDist = c;}
  void setPFPAT_dpt(double c){m_PFPAT_dpt = c;}
  void setGenLepton_pdgID(int c){m_genLepton_pdgID = c;}
  void setFMVAVar_gsfchi2(double c){m_fMVAVar_gsfchi2 = c;}
  void setEOverPin(double c){m_eOverPin = c;}
  void setFMVAVar_HoE(double c){m_fMVAVar_HoE = c;}
  void setIsConversion(int c){m_IsConversion = c;}
  void setEcalDriven(int c){m_ecalDriven = c;}
  void setGsfCtfChargeConsistent(int c){m_GsfCtfChargeConsistent = c;}
  void setFMVAVar_spp(double c){m_fMVAVar_spp = c;}
  void setFMVAVar_dphi(double c){m_fMVAVar_dphi = c;}
  void setFMVAVar_e1x5e5x5(double c){m_fMVAVar_e1x5e5x5 = c;}
  void setE1x5(double c){m_e1x5 = c;}
  void setEidRobustHighEnergy(int c){m_eidRobustHighEnergy = c;}
  void setEMax(double c){m_eMax = c;}
  void setSigmaEtaEta(double c){m_sigmaEtaEta = c;}
  void setConv_vtxProb(double c){m_conv_vtxProb = c;}
  void setStatus(int c){m_status = c;}
  void setE5x5(double c){m_e5x5 = c;}
  void setFMVAVar_R9(double c){m_fMVAVar_R9 = c;}
  void setEidRobustTight(int c){m_eidRobustTight = c;}
  void setFMVAVar_deta(double c){m_fMVAVar_deta = c;}
  void addTrigger_objectID(int c){m_trigger_objectID.push_back(c);}
  void setPF_photonIso_04(double c){m_PF_photonIso_04 = c;}
  void setEidLoose(int c){m_eidLoose = c;}
  void setGsfCtfScPixChargeConsistent(int c){m_GsfCtfScPixChargeConsistent = c;}
  void setNumberOfExpectedInnerHits(int c){m_NumberOfExpectedInnerHits = c;}

 private:

  double m_mvaTrig;
  double m_mvaNoTrig;
  double m_fbrem;
  int m_trackID;
  double m_PF_chargedHadronIso_04;
  double m_ConversionDCotTheta;
  double m_fMVAVar_detacalo;
  double m_fMVAVar_eta;
  double m_fMVAVar_dphicalo;
  double m_swissCross;
  double m_fMVAVar_PreShowerOverRaw;
  int m_fMVAVar_kfhits;
  int m_eidTight;
  int m_genLepton_ntID;
  SignatureObjectMCPart* m_genLepton;
  double m_fMVAVar_kfchi2;
  double m_hadOverEm;
  double m_fMVAVar_IoEmIoP;
  double m_fMVAVar_pt;
  int m_trigger_nfilter;
  double m_fMVAVar_phiwidth;
  double m_fMVAVar_EoP;
  double m_PFPAT_dphi;
  int m_GsfScPixChargeConsistent;
  double m_fMVAVar_eleEoPout;
  int m_PFMatchPdgId;
  double m_PF_neutralHadronIso_04;
  int m_eidRobustLoose;
  int m_isPF;
  double m_fMVAVar_etawidth;
  double m_deltaEta;
  double m_dRmin;
  double m_eSeedClusterOverPout;
  int m_dRmin_track_ntID;
  double m_sigmaIetaIeta;
  double m_fMVAVar_d0;
  double m_fMVAVar_dz;
  int m_fMVAVar_nbrems;
  double m_fMVAVar_see;
  double m_caloEnergy;
  double m_fMVAVar_fbrem;
  int m_classification;
  double m_e2x5Max;
  double m_PFPAT_dq;
  double m_PFPAT_deta;
  double m_deltaPhi;
  std::vector<int> m_trigger_objectType;
  int m_NumberOfLostInnerHits;
  double m_ConversionDist;
  double m_PFPAT_dpt;
  int m_genLepton_pdgID;
  double m_fMVAVar_gsfchi2;
  double m_eOverPin;
  double m_fMVAVar_HoE;
  int m_IsConversion;
  int m_ecalDriven;
  int m_GsfCtfChargeConsistent;
  double m_fMVAVar_spp;
  double m_fMVAVar_dphi;
  double m_fMVAVar_e1x5e5x5;
  double m_e1x5;
  int m_eidRobustHighEnergy;
  double m_eMax;
  double m_sigmaEtaEta;
  double m_conv_vtxProb;
  int m_status;
  double m_e5x5;
  double m_fMVAVar_R9;
  int m_eidRobustTight;
  double m_fMVAVar_deta;
  std::vector<int> m_trigger_objectID;
  double m_PF_photonIso_04;
  int m_eidLoose;
  int m_GsfCtfScPixChargeConsistent;
  int m_NumberOfExpectedInnerHits;

  ClassDef(SignatureObjectElectron,1);

};

inline SignatureObjectElectron::SignatureObjectElectron(double x,double y, double z, double t):SignatureObjectRecoTrack(x,y,z,t){
  m_pdgid = 11;

  m_fbrem = -10000;
  m_trackID = -10000;
  m_PF_chargedHadronIso_04 = -10000;
  m_ConversionDCotTheta = -10000;
  m_fMVAVar_detacalo = -10000;
  m_fMVAVar_eta = -10000;
  m_fMVAVar_dphicalo = -10000;
  m_swissCross = -10000;
  m_fMVAVar_PreShowerOverRaw = -10000;
  m_fMVAVar_kfhits = -10000;
  m_eidTight = -10000;
  m_genLepton_ntID = -10000;
  m_genLepton = 0;
  m_fMVAVar_kfchi2 = -10000;
  m_hadOverEm = -10000;
  m_fMVAVar_IoEmIoP = -10000;
  m_fMVAVar_pt = -10000;
  m_trigger_nfilter = -10000;
  m_fMVAVar_phiwidth = -10000;
  m_fMVAVar_EoP = -10000;
  m_PFPAT_dphi = -10000;
  m_GsfScPixChargeConsistent = -10000;
  m_fMVAVar_eleEoPout = -10000;
  m_PFMatchPdgId = -10000;
  m_PF_neutralHadronIso_04 = -10000;
  m_eidRobustLoose = -10000;
  m_isPF = -10000;
  m_fMVAVar_etawidth = -10000;
  m_deltaEta = -10000;
  m_dRmin = -10000;
  m_eSeedClusterOverPout = -10000;
  m_dRmin_track_ntID = -10000;
  m_sigmaIetaIeta = -10000;
  m_fMVAVar_d0 = -10000;
  m_fMVAVar_dz = -10000;
  m_fMVAVar_nbrems = -10000;
  m_fMVAVar_see = -10000;
  m_caloEnergy = -10000;
  m_fMVAVar_fbrem = -10000;
  m_classification = -10000;
  m_e2x5Max = -10000;
  m_PFPAT_dq = -10000;
  m_PFPAT_deta = -10000;
  m_deltaPhi = -10000;
  m_NumberOfLostInnerHits = -10000;
  m_ConversionDist = -10000;
  m_PFPAT_dpt = -10000;
  m_genLepton_pdgID = -10000;
  m_fMVAVar_gsfchi2 = -10000;
  m_eOverPin = -10000;
  m_fMVAVar_HoE = -10000;
  m_IsConversion = -10000;
  m_ecalDriven = -10000;
  m_GsfCtfChargeConsistent = -10000;
  m_fMVAVar_spp = -10000;
  m_fMVAVar_dphi = -10000;
  m_fMVAVar_e1x5e5x5 = -10000;
  m_e1x5 = -10000;
  m_eidRobustHighEnergy = -10000;
  m_eMax = -10000;
  m_sigmaEtaEta = -10000;
  m_conv_vtxProb = -10000;
  m_status = -10000;
  m_e5x5 = -10000;
  m_fMVAVar_R9 = -10000;
  m_eidRobustTight = -10000;
  m_fMVAVar_deta = -10000;
  m_PF_photonIso_04 = -10000;
  m_eidLoose = -10000;
  m_GsfCtfScPixChargeConsistent = -10000;
  m_NumberOfExpectedInnerHits = -10000;
}

inline SignatureObjectElectron::SignatureObjectElectron(TLorentzVector v):SignatureObjectRecoTrack(v){
  m_pdgid = 11;
  m_fbrem = -10000;
  m_trackID = -10000;
  m_PF_chargedHadronIso_04 = -10000;
  m_ConversionDCotTheta = -10000;
  m_fMVAVar_detacalo = -10000;
  m_fMVAVar_eta = -10000;
  m_fMVAVar_dphicalo = -10000;
  m_swissCross = -10000;
  m_fMVAVar_PreShowerOverRaw = -10000;
  m_fMVAVar_kfhits = -10000;
  m_eidTight = -10000;
  m_genLepton_ntID = -10000;
  m_genLepton = 0;
  m_fMVAVar_kfchi2 = -10000;
  m_hadOverEm = -10000;
  m_fMVAVar_IoEmIoP = -10000;
  m_fMVAVar_pt = -10000;
  m_trigger_nfilter = -10000;
  m_fMVAVar_phiwidth = -10000;
  m_fMVAVar_EoP = -10000;
  m_PFPAT_dphi = -10000;
  m_GsfScPixChargeConsistent = -10000;
  m_fMVAVar_eleEoPout = -10000;
  m_PFMatchPdgId = -10000;
  m_PF_neutralHadronIso_04 = -10000;
  m_eidRobustLoose = -10000;
  m_isPF = -10000;
  m_fMVAVar_etawidth = -10000;
  m_deltaEta = -10000;
  m_dRmin = -10000;
  m_eSeedClusterOverPout = -10000;
  m_dRmin_track_ntID = -10000;
  m_sigmaIetaIeta = -10000;
  m_fMVAVar_d0 = -10000;
  m_fMVAVar_dz = -10000;
  m_fMVAVar_nbrems = -10000;
  m_fMVAVar_see = -10000;
  m_caloEnergy = -10000;
  m_fMVAVar_fbrem = -10000;
  m_classification = -10000;
  m_e2x5Max = -10000;
  m_PFPAT_dq = -10000;
  m_PFPAT_deta = -10000;
  m_deltaPhi = -10000;
  m_NumberOfLostInnerHits = -10000;
  m_ConversionDist = -10000;
  m_PFPAT_dpt = -10000;
  m_genLepton_pdgID = -10000;
  m_fMVAVar_gsfchi2 = -10000;
  m_eOverPin = -10000;
  m_fMVAVar_HoE = -10000;
  m_IsConversion = -10000;
  m_ecalDriven = -10000;
  m_GsfCtfChargeConsistent = -10000;
  m_fMVAVar_spp = -10000;
  m_fMVAVar_dphi = -10000;
  m_fMVAVar_e1x5e5x5 = -10000;
  m_e1x5 = -10000;
  m_eidRobustHighEnergy = -10000;
  m_eMax = -10000;
  m_sigmaEtaEta = -10000;
  m_conv_vtxProb = -10000;
  m_status = -10000;
  m_e5x5 = -10000;
  m_fMVAVar_R9 = -10000;
  m_eidRobustTight = -10000;
  m_fMVAVar_deta = -10000;
  m_PF_photonIso_04 = -10000;
  m_eidLoose = -10000;
  m_GsfCtfScPixChargeConsistent = -10000;
  m_NumberOfExpectedInnerHits = -10000;

}

inline double SignatureObjectElectron::getRelIso(){
  if(Pt() < 0) return 9999999.0;
  return getTotalIso()/Pt();
}

inline double SignatureObjectElectron::getTotalIso(){
  return getChargedHadronIso() + std::max(0.0,getPhotonIso() + getNeutralHadronIso() - getRho() * getPhotonPlusNeutralHadronEffectiveArea());
}
#endif
