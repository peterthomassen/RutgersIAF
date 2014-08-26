#ifndef SignatureObjectJet_h
#define SignatureObjectJet_h

#include "RutgersIAF/RootC/interface/SignatureObject.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMCPart.h"

class SignatureObjectJet : public SignatureObject {
 public:
  SignatureObjectJet(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectJet(TLorentzVector v);
  virtual ~SignatureObjectJet(){/* no-op*/}

  int getCorrLevel(){return m_corrLevel;}
  double getBDiscriminator_combined(){return m_bDiscriminator_combined;}
  double getChargedHadronFraction(){return m_chargedHadronFraction;}
  int getGenParton_ntID(){return m_genParton_ntID;}
  SignatureObjectMCPart* getGenParton(){return m_genParton;}
  std::vector<int> getTrigger_objectType(){return m_trigger_objectType;}
  int getTrigger_objectTypeAt(int i){return m_trigger_objectType[i];}
  std::vector<double> getBDiscPositive(){return m_bDiscPositive;}
  double getBDiscPositiveAt(int i){return m_bDiscPositive[i];}
  double getEtaetaMoment(){return m_etaetaMoment;}
  double getRaw_pt(){return m_raw_pt;}
  double getBDiscriminator_trackCount(){return m_bDiscriminator_trackCount;}
  double getNeutralEMFraction(){return m_neutralEMFraction;}
  double getChargedEMFraction(){return m_chargedEMFraction;}
  std::vector<double> getBDiscNegative(){return m_bDiscNegative;}
  double getBDiscNegativeAt(int i){return m_bDiscNegative[i];}
  int getTrigger_nfilter(){return m_trigger_nfilter;}
  double getNeutralHadronFraction(){return m_neutralHadronFraction;}
  int getIsCalo(){return m_isCalo;}
  double getEhf(){return m_ehf;}
  double getBDiscriminator_ssVertexPure(){return m_bDiscriminator_ssVertexPure;}
  double getBDiscriminator(){return m_bDiscriminator;}
  double getPhiphiMoment(){return m_phiphiMoment;}
  int getGenParton_pdgID(){return m_genParton_pdgID;}
  double getSumTrackPt(){return m_sumTrackPt;}
  std::vector<double> getCorr_uds(){return m_corr_uds;}
  double getCorr_udsAt(int i){return m_corr_uds[i];}
  int getTight_PFjetID(){return m_tight_PFjetID;}
  std::vector<int> getTrkIDs(){return m_trkIDs;}
  int getTrkIDsAt(int i){return m_trkIDs[i];}
  int getChargedHadronMultiplicity(){return m_chargedHadronMultiplicity;}
  std::vector<double> getCorr_c(){return m_corr_c;}
  double getCorr_cAt(int i){return m_corr_c[i];}
  std::vector<double> getCorr_b(){return m_corr_b;}
  double getCorr_bAt(int i){return m_corr_b[i];}
  double getBDiscriminator_trackCountPure(){return m_bDiscriminator_trackCountPure;}
  int getIsPF(){return m_isPF;}
  double getEmf(){return m_emf;}
  std::vector<int> getTrigger_objectID(){return m_trigger_objectID;}
  int getTrigger_objectIDAt(int i){return m_trigger_objectID[i];}
  double getUncertainty(){return m_uncertainty;}
  int getNtracks(){return m_ntracks;}
  double getRaw_et(){return m_raw_et;}
  double getEtaphiMoment(){return m_etaphiMoment;}
  double getMass(){return m_mass;}
  int getLoose_PFjetID(){return m_loose_PFjetID;}
  int getMedium_PFjetID(){return m_medium_PFjetID;}
  std::vector<double> getCorr_glue(){return m_corr_glue;}
  double getCorr_glueAt(int i){return m_corr_glue[i];}
  int getNumberConstituents(){return m_numberConstituents;}
  double getBDiscriminator_ssVertex(){return m_bDiscriminator_ssVertex;}
  double getBeta(){return m_beta;}

  void setBeta(double c){m_beta = c;}
  void setCorrLevel(int c){m_corrLevel = c;}
  void setBDiscriminator_combined(double c){m_bDiscriminator_combined = c;}
  void setChargedHadronFraction(double c){m_chargedHadronFraction = c;}
  void setGenParton_ntID(int c){m_genParton_ntID = c;}
  void setGenParton(SignatureObjectMCPart* genParton){m_genParton = genParton;}
  void addTrigger_objectType(int c){m_trigger_objectType.push_back(c);}
  void addBDiscPositive(double c){m_bDiscPositive.push_back(c);}
  void setEtaetaMoment(double c){m_etaetaMoment = c;}
  void setRaw_pt(double c){m_raw_pt = c;}
  void setBDiscriminator_trackCount(double c){m_bDiscriminator_trackCount = c;}
  void setNeutralEMFraction(double c){m_neutralEMFraction = c;}
  void setChargedEMFraction(double c){m_chargedEMFraction = c;}
  void addBDiscNegative(double c){m_bDiscNegative.push_back(c);}
  void setTrigger_nfilter(int c){m_trigger_nfilter = c;}
  void setNeutralHadronFraction(double c){m_neutralHadronFraction = c;}
  void setIsCalo(int c){m_isCalo = c;}
  void setEhf(double c){m_ehf = c;}
  void setBDiscriminator_ssVertexPure(double c){m_bDiscriminator_ssVertexPure = c;}
  void setBDiscriminator(double c){m_bDiscriminator = c;}
  void setPhiphiMoment(double c){m_phiphiMoment = c;}
  void setGenParton_pdgID(int c){m_genParton_pdgID = c;}
  void setSumTrackPt(double c){m_sumTrackPt = c;}
  void addCorr_uds(double c){m_corr_uds.push_back(c);}
  void setTight_PFjetID(int c){m_tight_PFjetID = c;}
  void addTrkIDs(int c){m_trkIDs.push_back(c);}
  void setChargedHadronMultiplicity(int c){m_chargedHadronMultiplicity = c;}
  void addCorr_c(double c){m_corr_c.push_back(c);}
  void addCorr_b(double c){m_corr_b.push_back(c);}
  void setBDiscriminator_trackCountPure(double c){m_bDiscriminator_trackCountPure = c;}
  void setIsPF(int c){m_isPF = c;}
  void setEmf(double c){m_emf = c;}
  void addTrigger_objectID(int c){m_trigger_objectID.push_back(c);}
  void setUncertainty(double c){m_uncertainty = c;}
  void setNtracks(int c){m_ntracks = c;}
  void setRaw_et(double c){m_raw_et = c;}
  void setEtaphiMoment(double c){m_etaphiMoment = c;}
  void setMass(double c){m_mass = c;}
  void setLoose_PFjetID(int c){m_loose_PFjetID = c;}
  void setMedium_PFjetID(int c){m_medium_PFjetID = c;}
  void addCorr_glue(double c){m_corr_glue.push_back(c);}
  void setNumberConstituents(int c){m_numberConstituents = c;}
  void setBDiscriminator_ssVertex(double c){m_bDiscriminator_ssVertex = c;}

 private:
  double m_beta;
  int m_corrLevel;
  double m_bDiscriminator_combined;
  double m_chargedHadronFraction;
  int m_genParton_ntID;
  SignatureObjectMCPart* m_genParton;
  std::vector<int> m_trigger_objectType;
  std::vector<double> m_bDiscPositive;
  double m_etaetaMoment;
  double m_raw_pt;
  double m_bDiscriminator_trackCount;
  double m_neutralEMFraction;
  double m_chargedEMFraction;
  std::vector<double> m_bDiscNegative;
  int m_trigger_nfilter;
  double m_neutralHadronFraction;
  int m_isCalo;
  double m_ehf;
  double m_bDiscriminator_ssVertexPure;
  double m_bDiscriminator;
  double m_phiphiMoment;
  int m_genParton_pdgID;
  double m_sumTrackPt;
  std::vector<double> m_corr_uds;
  int m_tight_PFjetID;
  std::vector<int> m_trkIDs;
  int m_chargedHadronMultiplicity;
  std::vector<double> m_corr_c;
  std::vector<double> m_corr_b;
  double m_bDiscriminator_trackCountPure;
  int m_isPF;
  double m_emf;
  std::vector<int> m_trigger_objectID;
  double m_uncertainty;
  int m_ntracks;
  double m_raw_et;
  double m_etaphiMoment;
  double m_mass;
  int m_loose_PFjetID;
  int m_medium_PFjetID;
  std::vector<double> m_corr_glue;
  int m_numberConstituents;
  double m_bDiscriminator_ssVertex;


  ClassDef(SignatureObjectJet,1);

};

inline SignatureObjectJet::SignatureObjectJet(double x,double y, double z, double t):SignatureObject(x,y,z,t){
  m_corrLevel = -10000;
  m_bDiscriminator_combined = -10000;
  m_chargedHadronFraction = -10000;
  m_genParton_ntID = -10000;
  m_genParton = 0;
  m_etaetaMoment = -10000;
  m_raw_pt = -10000;
  m_bDiscriminator_trackCount = -10000;
  m_neutralEMFraction = -10000;
  m_chargedEMFraction = -10000;
  m_trigger_nfilter = -10000;
  m_neutralHadronFraction = -10000;
  m_isCalo = -10000;
  m_ehf = -10000;
  m_bDiscriminator_ssVertexPure = -10000;
  m_bDiscriminator = -10000;
  m_phiphiMoment = -10000;
  m_genParton_pdgID = -10000;
  m_sumTrackPt = -10000;
  m_tight_PFjetID = -10000;
  m_chargedHadronMultiplicity = -10000;
  m_bDiscriminator_trackCountPure = -10000;
  m_isPF = -10000;
  m_emf = -10000;
  m_uncertainty = -10000;
  m_ntracks = -10000;
  m_raw_et = -10000;
  m_etaphiMoment = -10000;
  m_mass = -10000;
  m_loose_PFjetID = -10000;
  m_medium_PFjetID = -10000;
  m_numberConstituents = -10000;
  m_bDiscriminator_ssVertex = -10000;
  m_beta = -1000000;

}
inline SignatureObjectJet::SignatureObjectJet(TLorentzVector v):SignatureObject(v){
  m_corrLevel = -10000;
  m_bDiscriminator_combined = -10000;
  m_chargedHadronFraction = -10000;
  m_genParton_ntID = -10000;
  m_genParton = 0;
  m_etaetaMoment = -10000;
  m_raw_pt = -10000;
  m_bDiscriminator_trackCount = -10000;
  m_neutralEMFraction = -10000;
  m_chargedEMFraction = -10000;
  m_trigger_nfilter = -10000;
  m_neutralHadronFraction = -10000;
  m_isCalo = -10000;
  m_ehf = -10000;
  m_bDiscriminator_ssVertexPure = -10000;
  m_bDiscriminator = -10000;
  m_phiphiMoment = -10000;
  m_genParton_pdgID = -10000;
  m_sumTrackPt = -10000;
  m_tight_PFjetID = -10000;
  m_chargedHadronMultiplicity = -10000;
  m_bDiscriminator_trackCountPure = -10000;
  m_isPF = -10000;
  m_emf = -10000;
  m_uncertainty = -10000;
  m_ntracks = -10000;
  m_raw_et = -10000;
  m_etaphiMoment = -10000;
  m_mass = -10000;
  m_loose_PFjetID = -10000;
  m_medium_PFjetID = -10000;
  m_numberConstituents = -10000;
  m_bDiscriminator_ssVertex = -10000;
  m_beta = -10000;
}
#endif
