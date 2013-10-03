#include "RutgersIAF2012/RootC/interface/SignatureTH1F_QuadJetAvgM.h"
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"

using namespace std;

ClassImp(SignatureTH1F_QuadJetAvgM)

Int_t  SignatureTH1F_QuadJetAvgM::Fill(BaseHandler* handler)
{

  vector<SignatureObject*> product = handler->getProduct(m_product);

  if(product.size() < 4)return -1;

  int dummy = -1;

  TLorentzVector j1,j2,j3,j4;
  j1 = *(product[0]);
  j2 = *(product[1]);
  j3 = *(product[2]);
  j4 = *(product[3]);
  double m12 = (j1+j2).M();
  double m13 = (j1+j3).M();
  double m14 = (j1+j4).M();
  double m23 = (j2+j3).M();
  double m24 = (j2+j4).M();
  double m34 = (j3+j4).M();

  double chi2a,chi2b,chi2c;
  chi2a = 2.0*fabs(m12-m34)/(m12+m34);
  chi2b = 2.0*fabs(m13-m24)/(m13+m24);
  chi2c = 2.0*fabs(m14-m23)/(m14+m23);
  double minRes = min(chi2a,min(chi2b,chi2c));
  if(minRes > m_maxMassRes)return dummy;
  double delta1 = 0;
  double delta2 = 0;
  double avgM = 0;
  if(minRes == chi2a){
    delta1 = j1.Pt()+j2.Pt()-m12;
    delta2 = j3.Pt()+j4.Pt()-m34;
    avgM = (m12+m34)/2.0;
  }else if(minRes == chi2b){
    delta1 = j1.Pt()+j3.Pt()-m13;
    delta2 = j2.Pt()+j4.Pt()-m24;
    avgM = (m13+m24)/2.0;
  }else if(minRes == chi2c){
    delta1 = j1.Pt()+j4.Pt()-m14;
    delta2 = j3.Pt()+j2.Pt()-m23;
    avgM = (m14+m23)/2.0;
  }
  if(delta1 < m_minDelta)return dummy;
  if(delta2 < m_minDelta)return dummy;

  dummy = TH1F::Fill(avgM,handler->getPhysicsWeight());

  return dummy;

}
