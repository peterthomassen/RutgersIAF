#ifndef EventVariableMatrixWeights3D_h
#define EventVariableMatrixWeights3D_h

#include <vector>
#include "TLorentzVector.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableMatrixWeights3D : public EventVariable{
 public:
 EventVariableMatrixWeights3D(TString name, TString productname, TString suffix, TString loosename, TString tightname) : EventVariable(name), m_suffix(suffix), m_loosename(loosename), m_tightname(tightname) {m_productnames.push_back(productname);}


  void addProduct(TString);

  bool calculate(BaseHandler*);

  void ResetFakePromptRates();
  void ResetLooseTight();
  //void SetFakePromptRates(double pt1, double pt2, double pt3, int array[3]);
  void SetFakePromptRates(TLorentzVector, TLorentzVector, TLorentzVector, int array[3]);

  double mP( double pt, double eta, double jetNconst );
  double mF( double pt, double eta, double jetNconst );
  double eP( double pt, double eta, double jetNconst );
  double eF( double pt, double eta, double jetNconst );

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

  ClassDef(EventVariableMatrixWeights3D,1);

 private:
  TString m_suffix;
  TString m_loosename;
  TString m_tightname;
  std::vector<TString> m_productnames;


};

#endif
