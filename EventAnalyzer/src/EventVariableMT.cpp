#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableMT.h"
#include <algorithm>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include <assert.h>

using namespace std;

ClassImp(EventVariableMT)

bool EventVariableMT::calculate(BaseHandler* handler) {
  std::vector<SignatureObject*> el  = handler->getProduct(m_productEl);
  std::vector<SignatureObject*> mu  = handler->getProduct(m_productMu);
  std::vector<SignatureObject*> tau = handler->getProduct(m_productTau);
  
  int n = el.size() + mu.size() + tau.size();
  if(n < 1) return false;
  
  double MT = 0;
  double MLL = 0;
  
  TLorentzVector ll;
  TLorentzVector wl;
  
  TLorentzVector metv = *(TLorentzVector*)(handler->getProduct(m_productMET)[0]);
  std::vector<double> chargeEl(el.size());
  for(size_t i = 0; i < el.size(); ++i) {
    double charge;
    assert(el[i]->getVariable("CHARGE",charge));
    chargeEl[i] = charge;
  }
  
  std::vector<double> chargeMu(mu.size());
  for(size_t i = 0; i < mu.size(); ++i) {
    double charge;
    assert(mu[i]->getVariable("CHARGE",charge));
    chargeMu[i] = charge;
  }
  
  std::vector<double> chargeTau(tau.size());
  for(size_t i = 0; i < tau.size(); ++i) {
    double charge;
    assert(tau[i]->getVariable("CHARGE",charge));
    chargeTau[i] = charge;
  }


  if(n == 1){
    if(el.size() == 1){
      wl = *el[0];
    }else if(mu.size() == 1){
      wl = *mu[0];
    }else if(tau.size() == 1){
      wl = *tau[0];
    }
  }else if(n == 2){
    if(tau.size() > 1) return false;

    double maxMT = 0;
    TLorentzVector dummy;

    if(el.size() == 2){
      if(chargeEl[0]*chargeEl[0] < 0) ll = *el[0] + *el[1];
    }else if(mu.size() == 2){
      if(chargeMu[0]*chargeMu[0] < 0) ll = *mu[0] + *mu[1];
    }

    for(int j = 0; j < (int)el.size(); j++){
      dummy = *el[j];
      double mt = sqrt(2*metv.Pt() * dummy.Pt() * ( 1 - cos(dummy.DeltaPhi(metv))));
      if(mt > maxMT)wl = dummy;
    }

    for(int j = 0; j < (int)mu.size(); j++){
      dummy = *mu[j];
      double mt = sqrt(2*metv.Pt() * dummy.Pt() * ( 1 - cos(dummy.DeltaPhi(metv))));
      if(mt > maxMT)wl = dummy;
    }

    for(int j = 0; j < (int)tau.size(); j++){
      dummy = *tau[j];
      double mt = sqrt(2*metv.Pt() * dummy.Pt() * ( 1 - cos(dummy.DeltaPhi(metv))));
      if(mt > maxMT)wl = dummy;
    }

  }else if(n == 3){
    if(tau.size() > 1) return false;    
    
    // Loop over the two flavors that the dilepton pair from Z can contain (including 1e1tau and 1m1tau)
    for(int iFlavor = 0; iFlavor <= 1; ++iFlavor) {
      std::vector<SignatureObject*> lepFl1, lepFl2;
      std::vector<double> chargeFl1, chargeFl2;
      if(iFlavor == 0) {
	lepFl1 = el;
	lepFl2 = mu;
	chargeFl1 = chargeEl;
	chargeFl2 = chargeMu;
      } else if(iFlavor == 1) {
	lepFl1 = mu;
	lepFl2 = el;
	chargeFl1 = chargeMu;
	chargeFl2 = chargeEl;
      } else {
	assert(false);
      }
      
      if(ll.M() == 0 && lepFl1.size() == 3) {
	double bestMll = 1e6;
	int worstIndex = -1;
	for(int i = 0; i < (int)lepFl1.size(); i++) {
	  for(int j = i+1; j < (int)lepFl1.size(); j++){
	    if(chargeFl1[i] * chargeFl1[j] > 0) {
	      continue;
	    }
	    double badMll = (*lepFl1[i] + *lepFl1[j]).M();
	    if(fabs(badMll - m_mZ) < fabs(bestMll - m_mZ)) {
	      bestMll = badMll;
	      ll = *lepFl1[i] + *lepFl1[j];
	      worstIndex = 3 - i - j;
	      wl = *lepFl1[worstIndex];
	    }
	  }
	}
      }
      if(ll.M() == 0 && lepFl1.size() == 2 && lepFl2.size() == 1){
	if(chargeFl1[0] * chargeFl1[1] < 0){
	  ll = *lepFl1[0] + *lepFl1[1];
	  wl = *lepFl2[0];
	}else if(chargeFl1[0] * chargeFl2[0] < 0) {
	  double badMll0 = (*lepFl1[0] + *lepFl2[0]).M();
	  double badMll1 = (*lepFl1[1] + *lepFl2[0]).M();
	  if(fabs(badMll0 - 50) < fabs(badMll1 - 50)) {
	    ll = *lepFl1[0] + *lepFl2[0];
	    wl = *lepFl1[1];
	  } else {
	    ll = *lepFl1[1] + *lepFl2[0];
	    wl = *lepFl1[0];
	  }
	} else {
	  return false;
	}
      }
      if(ll.M() == 0 && lepFl1.size() == 2 && tau.size() == 1){
	if(chargeFl1[0] * chargeFl1[1] < 0){
	  ll = *lepFl1[0] + *lepFl1[1];
	  wl = *tau[0];
	}else if(chargeFl1[0] * chargeTau[0] < 0){
	  double badMll0 = (*lepFl1[0] + *tau[0]).M();
	  double badMll1 = (*lepFl1[1] + *tau[0]).M();
	  if(fabs(badMll0 - 60) < fabs(badMll1 - 60)) {
	    ll = *lepFl1[0] + *tau[0];
	    wl = *lepFl1[1];
	  } else {
	    ll = *lepFl1[1] + *tau[0];
	    wl = *lepFl1[0];
	  }
	} else {
	  return false;
	}
      }
    }
    
    if(ll.M() == 0 && mu.size() == 1 && el.size() == 1 && tau.size() == 1){
      double em = 999999;
      double et = 999999;
      double mt = 999999;
      if(chargeEl[0] * chargeMu[0] < 0){
	em = fabs(TLorentzVector(*el[0] + *mu[0]).M() - 50);
      }
      if(chargeEl[0] * chargeTau[0] < 0){
	et = fabs(TLorentzVector(*el[0] + *tau[0]).M() - 60);
      }
      if(chargeMu[0] * chargeTau[0] < 0){
	mt = fabs(TLorentzVector(*mu[0] + *tau[0]).M() - 60);
      }
      if( em < et && em < mt){
	ll = *el[0] + *mu[0];
	wl = *tau[0];
      }else if(et < em && et < mt){
	ll = *el[0] + *tau[0];
	wl = *mu[0];
      }else if(mt < em && mt < et){
	ll = *tau[0] + *mu[0];
	wl = *el[0];
      }
    }
  }else{
    return false;
  }


  MLL = ll.M();
  MT = sqrt(2*metv.Pt() * wl.Pt() * ( 1 - cos(wl.DeltaPhi(metv))));
  
  handler->setVariable(TString::Format("%sMT",  m_prefix.Data()), MT);
  handler->setVariable(TString::Format("%sMLL", m_prefix.Data()), MLL);
  return true;
  }
