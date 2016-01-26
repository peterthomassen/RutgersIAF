#ifndef EventVariableMatrixLeptons_h
#define EventVariableMatrixLeptons_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableMatrixLeptons : public EventVariable{
 public:
 EventVariableMatrixLeptons(TString name, TString productname, TString prefix="") : EventVariable(name), m_prefix(prefix) {m_productnames.push_back(productname);}


  void addProduct(TString);

  bool calculate(BaseHandler*);

  void ResetFakePromptRates();
  void ResetLooseTight();
  void SetFakePromptRates(double pt1, double pt2, double pt3, int array[3]);

  double mP( double pt, double jetNconst );
  double mF( double pt, double jetNconst );
  double eP( double pt, double jetNconst );
  double eF( double pt, double jetNconst );

  double p1, p2, p3;
  double f1, f2, f3;

  double nLLL;
  double nLLT, nLTL, nTLL;
  double nLTT, nTLT, nTTL;
  double nTTT;

  //triple fake
  double Wfff();
  //double fake
  double Wffp();
  double Wfpf();
  double Wpff();
  //single fake
  double Wfpp();
  double Wpfp();
  double Wppf();
  //zero fake
  double Wppp();

  double WfakeBckg();

  ClassDef(EventVariableMatrixLeptons,1);

 private:
  TString m_prefix;
  double m_zmass;
  double m_zwidth;
  std::vector<TString> m_productnames;
  bool m_includeFakes;


};

#endif
