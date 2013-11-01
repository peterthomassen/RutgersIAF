#ifndef SignatureObjectTau_h
#define SignatureObjectTau_h

#include <vector>
#include <iostream>
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class SignatureObjectTau : public SignatureObjectRecoTrack {
 public:
  SignatureObjectTau(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectTau(TLorentzVector v);
  virtual ~SignatureObjectTau() {/* no-op */}
  double getRelIso();
  double getTotalIso();
  void setLeadingTrack(SignatureObjectRecoTrack* c){m_leadingTrack = c;}
  SignatureObjectRecoTrack* getLeadingTrack(){return m_leadingTrack;}


  double getPF_neutralHadronIso05(){return m_PF_neutralHadronIso05;}
  double getPF_isoGammaEtSum(){return m_PF_isoGammaEtSum;}
  int getPF_NsigGamma(){return m_PF_NsigGamma;}
  std::vector<int> getIsoTracks_ntIDs(){return m_isoTracks_ntIDs;}
  int getIsoTracks_ntIDsAt(int i){return m_isoTracks_ntIDs[i];}
  int getIsPF(){return m_isPF;}
  int getIsCalo(){return m_isCalo;}
  double getEmFraction(){return m_emFraction;}
  double getPF_againstMuon(){return m_PF_againstMuon;}
  std::vector<int> getSignalTracks_ntIDs(){return m_signalTracks_ntIDs;}
  int getSignalTracks_ntIDsAt(int i){return m_signalTracks_ntIDs[i];}
  double getPF_neutralHadronIso03(){return m_PF_neutralHadronIso03;}
  double getCalo_leadTracksignedSipt(){return m_calo_leadTracksignedSipt;}
  std::vector<int> getTrigger_objectType(){return m_trigger_objectType;}
  int getTrigger_objectTypeAt(int i){return m_trigger_objectType[i];}
  int getPF_NsigCharged(){return m_PF_NsigCharged;}
  double getPF_isoKlongCandMaxPt(){return m_PF_isoKlongCandMaxPt;}
  double getPF_photonIso05(){return m_PF_photonIso05;}
  double getPF_againstElectron(){return m_PF_againstElectron;}
  double getPF_photonIso03(){return m_PF_photonIso03;}
  int getIsoTracks_n(){return m_isoTracks_n;}
  int getLeadTrack_ntID(){return m_leadTrack_ntID;}
  double getCalo_isoECALEtSum(){return m_calo_isoECALEtSum;}
  double getPF_signalMass(){return m_PF_signalMass;}
  int getGenLepton_pdgID(){return m_genLepton_pdgID;}
  double getPF_isoChargedPtSum(){return m_PF_isoChargedPtSum;}
  int getGenLepton_ntID(){return m_genLepton_ntID;}
  SignatureObjectMCPart* getGenLepton(){return m_genLepton;}
  std::vector<double> getPF_Discriminants(){return m_PF_Discriminants;}
  double getPF_DiscriminantsAt(int i){return m_PF_Discriminants[i];}
  double getPF_leadTracksignedSipt(){return m_PF_leadTracksignedSipt;}
  double getPF_isoChargedCandMaxPt(){return m_PF_isoChargedCandMaxPt;}
  double getPF_isoSumPt(){return m_PF_isoSumPt;}
  double getPF_maxHCALhitEt(){return m_PF_maxHCALhitEt;}
  double getCalo_maxHCALhitEt(){return m_calo_maxHCALhitEt;}
  double getPF_isoGammaCandMaxPt(){return m_PF_isoGammaCandMaxPt;}
  double getCalo_isoChargedPtSum(){return m_calo_isoChargedPtSum;}
  int getTrigger_nfilter(){return m_trigger_nfilter;}
  int getSignalTracks_n(){return m_signalTracks_n;}
  double getSignalTracksInvMass(){return m_signalTracksInvMass;}
  std::vector<int> getTrigger_objectID(){return m_trigger_objectID;}
  int getTrigger_objectIDAt(int i){return m_trigger_objectID[i];}
  double getPF_signalCharge(){return m_PF_signalCharge;}
  double getPF_chargedHadronIso05(){return m_PF_chargedHadronIso05;}
  double getPF_chargedHadronIso03(){return m_PF_chargedHadronIso03;}

  void setPF_neutralHadronIso05(double c){m_PF_neutralHadronIso05 = c;}
  void setPF_isoGammaEtSum(double c){m_PF_isoGammaEtSum = c;}
  void setPF_NsigGamma(int c){m_PF_NsigGamma = c;}
  void addIsoTracks_ntIDs(int c){m_isoTracks_ntIDs.push_back(c);}
  void setIsPF(int c){m_isPF = c;}
  void setIsCalo(int c){m_isCalo = c;}
  void setEmFraction(double c){m_emFraction = c;}
  void setPF_againstMuon(double c){m_PF_againstMuon = c;}
  void addSignalTracks_ntIDs(int c){m_signalTracks_ntIDs.push_back(c);}
  void setPF_neutralHadronIso03(double c){m_PF_neutralHadronIso03 = c;}
  void setCalo_leadTracksignedSipt(double c){m_calo_leadTracksignedSipt = c;}
  void addTrigger_objectType(int c){m_trigger_objectType.push_back(c);}
  void setPF_NsigCharged(int c){m_PF_NsigCharged = c;}
  void setPF_isoKlongCandMaxPt(double c){m_PF_isoKlongCandMaxPt = c;}
  void setPF_photonIso05(double c){m_PF_photonIso05 = c;}
  void setPF_againstElectron(double c){m_PF_againstElectron = c;}
  void setPF_photonIso03(double c){m_PF_photonIso03 = c;}
  void setIsoTracks_n(int c){m_isoTracks_n = c;}
  void setLeadTrack_ntID(int c){m_leadTrack_ntID = c;}
  void setCalo_isoECALEtSum(double c){m_calo_isoECALEtSum = c;}
  void setPF_signalMass(double c){m_PF_signalMass = c;}
  void setGenLepton_pdgID(int c){m_genLepton_pdgID = c;}
  void setPF_isoChargedPtSum(double c){m_PF_isoChargedPtSum = c;}
  void setGenLepton_ntID(int c){m_genLepton_ntID = c;}
  void setGenLepton(SignatureObjectMCPart* genLepton){m_genLepton = genLepton;}
  void addPF_Discriminants(double c){m_PF_Discriminants.push_back(c);}
  void setPF_leadTracksignedSipt(double c){m_PF_leadTracksignedSipt = c;}
  void setPF_isoChargedCandMaxPt(double c){m_PF_isoChargedCandMaxPt = c;}
  void setPF_isoSumPt(double c){m_PF_isoSumPt = c;}
  void setPF_maxHCALhitEt(double c){m_PF_maxHCALhitEt = c;}
  void setCalo_maxHCALhitEt(double c){m_calo_maxHCALhitEt = c;}
  void setPF_isoGammaCandMaxPt(double c){m_PF_isoGammaCandMaxPt = c;}
  void setCalo_isoChargedPtSum(double c){m_calo_isoChargedPtSum = c;}
  void setTrigger_nfilter(int c){m_trigger_nfilter = c;}
  void setSignalTracks_n(int c){m_signalTracks_n = c;}
  void setSignalTracksInvMass(double c){m_signalTracksInvMass = c;}
  void addTrigger_objectID(int c){m_trigger_objectID.push_back(c);}
  void setPF_signalCharge(double c){m_PF_signalCharge = c;}
  void setPF_chargedHadronIso05(double c){m_PF_chargedHadronIso05 = c;}
  void setPF_chargedHadronIso03(double c){m_PF_chargedHadronIso03 = c;}

 private:
  double m_PF_neutralHadronIso05;
  double m_PF_isoGammaEtSum;
  int m_PF_NsigGamma;
  std::vector<int> m_isoTracks_ntIDs;
  int m_isPF;
  int m_isCalo;
  double m_emFraction;
  double m_PF_againstMuon;
  std::vector<int> m_signalTracks_ntIDs;
  double m_PF_neutralHadronIso03;
  double m_calo_leadTracksignedSipt;
  std::vector<int> m_trigger_objectType;
  int m_PF_NsigCharged;
  double m_PF_isoKlongCandMaxPt;
  double m_PF_photonIso05;
  double m_PF_againstElectron;
  double m_PF_photonIso03;
  int m_isoTracks_n;
  int m_leadTrack_ntID;
  double m_calo_isoECALEtSum;
  double m_PF_signalMass;
  int m_genLepton_pdgID;
  double m_PF_isoChargedPtSum;
  int m_genLepton_ntID;
  SignatureObjectMCPart* m_genLepton;
  std::vector<double> m_PF_Discriminants;
  double m_PF_leadTracksignedSipt;
  double m_PF_isoChargedCandMaxPt;
  double m_PF_isoSumPt;
  double m_PF_maxHCALhitEt;
  double m_calo_maxHCALhitEt;
  double m_PF_isoGammaCandMaxPt;
  double m_calo_isoChargedPtSum;
  int m_trigger_nfilter;
  int m_signalTracks_n;
  double m_signalTracksInvMass;
  std::vector<int> m_trigger_objectID;
  double m_PF_signalCharge;
  double m_PF_chargedHadronIso05;
  double m_PF_chargedHadronIso03;
  
  SignatureObjectRecoTrack* m_leadingTrack;
  ClassDef(SignatureObjectTau,1);

};

inline SignatureObjectTau::SignatureObjectTau(double x,double y, double z, double t):SignatureObjectRecoTrack(x,y,z,t){
  m_pdgid = 15;
  m_leadingTrack = 0;

  m_PF_neutralHadronIso05 = -10000;
  m_PF_isoGammaEtSum = -10000;
  m_PF_NsigGamma = -10000;
  m_isPF = -10000;
  m_isCalo = -10000;
  m_emFraction = -10000;
  m_PF_againstMuon = -10000;
  m_PF_neutralHadronIso03 = -10000;
  m_calo_leadTracksignedSipt = -10000;
  m_PF_NsigCharged = -10000;
  m_PF_isoKlongCandMaxPt = -10000;
  m_PF_photonIso05 = -10000;
  m_PF_againstElectron = -10000;
  m_PF_photonIso03 = -10000;
  m_isoTracks_n = -10000;
  m_leadTrack_ntID = -10000;
  m_calo_isoECALEtSum = -10000;
  m_PF_signalMass = -10000;
  m_genLepton_pdgID = -10000;
  m_PF_isoChargedPtSum = -10000;
  m_genLepton_ntID = -10000;
  m_genLepton = 0;
  m_PF_leadTracksignedSipt = -10000;
  m_PF_isoChargedCandMaxPt = -10000;
  m_PF_isoSumPt = -10000;
  m_PF_maxHCALhitEt = -10000;
  m_calo_maxHCALhitEt = -10000;
  m_PF_isoGammaCandMaxPt = -10000;
  m_calo_isoChargedPtSum = -10000;
  m_trigger_nfilter = -10000;
  m_signalTracks_n = -10000;
  m_signalTracksInvMass = -10000;
  m_PF_signalCharge = -10000;
  m_PF_chargedHadronIso05 = -10000;
  m_PF_chargedHadronIso03 = -10000;

}

inline SignatureObjectTau::SignatureObjectTau(TLorentzVector v):SignatureObjectRecoTrack(v){
  m_pdgid = 15;
  m_leadingTrack = 0;

  m_PF_neutralHadronIso05 = -10000;
  m_PF_isoGammaEtSum = -10000;
  m_PF_NsigGamma = -10000;
  m_isPF = -10000;
  m_isCalo = -10000;
  m_emFraction = -10000;
  m_PF_againstMuon = -10000;
  m_PF_neutralHadronIso03 = -10000;
  m_calo_leadTracksignedSipt = -10000;
  m_PF_NsigCharged = -10000;
  m_PF_isoKlongCandMaxPt = -10000;
  m_PF_photonIso05 = -10000;
  m_PF_againstElectron = -10000;
  m_PF_photonIso03 = -10000;
  m_isoTracks_n = -10000;
  m_leadTrack_ntID = -10000;
  m_calo_isoECALEtSum = -10000;
  m_PF_signalMass = -10000;
  m_genLepton_pdgID = -10000;
  m_PF_isoChargedPtSum = -10000;
  m_genLepton_ntID = -10000;
  m_genLepton = 0;
  m_PF_leadTracksignedSipt = -10000;
  m_PF_isoChargedCandMaxPt = -10000;
  m_PF_isoSumPt = -10000;
  m_PF_maxHCALhitEt = -10000;
  m_calo_maxHCALhitEt = -10000;
  m_PF_isoGammaCandMaxPt = -10000;
  m_calo_isoChargedPtSum = -10000;
  m_trigger_nfilter = -10000;
  m_signalTracks_n = -10000;
  m_signalTracksInvMass = -10000;
  m_PF_signalCharge = -10000;
  m_PF_chargedHadronIso05 = -10000;
  m_PF_chargedHadronIso03 = -10000;

}

inline double SignatureObjectTau::getRelIso(){
  if (Pt() < 0) return 9999999.9;
  return getTotalIso()/Pt();
}
inline double SignatureObjectTau::getTotalIso(){
	//if (getCaloIso() < 0)return 9999999.9;
	//if (getTrackIso() < 0)return 9999999.9;
	//return (std::max(getPF_photonIso05(),0.0) + std::max(getPF_chargedHadronIso05(),0.0))
	return (bool)getPF_DiscriminantsAt(26)
		? 0
		: (std::max(getPF_photonIso05(),0.0) + std::max(getPF_chargedHadronIso05(),0.0));
}
#endif
