#ifndef SignatureObjectMET_h
#define SignatureObjectMET_h

#include "RutgersIAF/RootC/interface/SignatureObject.h"

class SignatureObjectMET : public SignatureObject {
 public:
  SignatureObjectMET(double x=0,double y=0, double z=0);
  SignatureObjectMET(TLorentzVector v);
  virtual ~SignatureObjectMET(){/* no-op*/}
  void setTc_sumEt(double c){m_tc_sumEt = c;}
  void setTc_pt(double c){m_tc_pt = c;}
  void setTc_phi(double c){m_tc_phi = c;}
  double getTc_sumEt(){return m_tc_sumEt;}
  double getTc_pt(){return m_tc_pt;}
  double getTc_phi(){return m_tc_phi;}

  int getPat_trigger_nfilter(){return m_pat_trigger_nfilter;}
  double getPat_sumEt(){return m_pat_sumEt;}
  double getPf_pt(){return m_pf_pt;}
  double getPf_eta(){return m_pf_eta;}
  double getPat_phi(){return m_pat_phi;}
  double getPat_eta(){return m_pat_eta;}
  double getPf_phi(){return m_pf_phi;}
  double getPat_px(){return m_pat_px;}
  double getPat_py(){return m_pat_py;}
  double getPat_pz(){return m_pat_pz;}
  double getPat_pt(){return m_pat_pt;}
  double getPf_sumEt(){return m_pf_sumEt;}
  double getPat_gen_sumEt(){return m_pat_gen_sumEt;}
  std::vector<int> getPat_trigger_objectID(){return m_pat_trigger_objectID;}
  int getPat_trigger_objectIDAt(int i){return m_pat_trigger_objectID[i];}
  double getPat_mEtSig(){return m_pat_mEtSig;}
  std::vector<int> getPat_trigger_objectType(){return m_pat_trigger_objectType;}
  int getPat_trigger_objectTypeAt(int i){return m_pat_trigger_objectType[i];}

  void setPat_trigger_nfilter(int c){m_pat_trigger_nfilter = c;}
  void setPat_sumEt(double c){m_pat_sumEt = c;}
  void setPf_pt(double c){m_pf_pt = c;}
  void setPf_eta(double c){m_pf_eta = c;}
  void setPat_phi(double c){m_pat_phi = c;}
  void setPat_eta(double c){m_pat_eta = c;}
  void setPf_phi(double c){m_pf_phi = c;}
  void setPat_px(double c){m_pat_px = c;}
  void setPat_py(double c){m_pat_py = c;}
  void setPat_pz(double c){m_pat_pz = c;}
  void setPat_pt(double c){m_pat_pt = c;}
  void setPf_sumEt(double c){m_pf_sumEt = c;}
  void setPat_gen_sumEt(double c){m_pat_gen_sumEt = c;}
  void addPat_trigger_objectID(int c){m_pat_trigger_objectID.push_back(c);}
  void setPat_mEtSig(double c){m_pat_mEtSig = c;}
  void addPat_trigger_objectType(int c){m_pat_trigger_objectType.push_back(c);}

 private:
  int m_pat_trigger_nfilter;
  double m_pat_sumEt;
  double m_pf_pt;
  double m_pf_eta;
  double m_pat_phi;
  double m_pat_eta;
  double m_pf_phi;
  double m_pat_px;
  double m_pat_py;
  double m_pat_pz;
  double m_pat_pt;
  double m_pf_sumEt;
  double m_pat_gen_sumEt;
  double m_tc_sumEt;
  double m_tc_pt;
  double m_tc_phi;
  std::vector<int> m_pat_trigger_objectID;
  double m_pat_mEtSig;
  std::vector<int> m_pat_trigger_objectType;



  ClassDef(SignatureObjectMET,1);

};

inline SignatureObjectMET::SignatureObjectMET(double x,double y, double z) : SignatureObject(x,y,z,0){
  m_pat_trigger_nfilter = -10000;
  m_pat_sumEt = -10000;
  m_pf_pt = -10000;
  m_pf_eta = -10000;
  m_pat_phi = -10000;
  m_pat_eta = -10000;
  m_pf_phi = -10000;
  m_pat_px = -10000;
  m_pat_py = -10000;
  m_pat_pz = -10000;
  m_pat_pt = -10000;
  m_pf_sumEt = -10000;
  m_pat_gen_sumEt = -10000;
  m_pat_mEtSig = -10000;
}
inline SignatureObjectMET::SignatureObjectMET(TLorentzVector v) : SignatureObject(v){
  m_pat_trigger_nfilter = -10000;
  m_pat_sumEt = -10000;
  m_pf_pt = -10000;
  m_pf_eta = -10000;
  m_pat_phi = -10000;
  m_pat_eta = -10000;
  m_pf_phi = -10000;
  m_pat_px = -10000;
  m_pat_py = -10000;
  m_pat_pz = -10000;
  m_pat_pt = -10000;
  m_pf_sumEt = -10000;
  m_pat_gen_sumEt = -10000;
  m_pat_mEtSig = -10000;
}
#endif
