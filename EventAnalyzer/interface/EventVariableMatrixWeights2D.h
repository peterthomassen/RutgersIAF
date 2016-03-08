#ifndef EventVariableMatrixWeights2D_h
#define EventVariableMatrixWeights2D_h

#include <vector>
#include "TLorentzVector.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableMatrixWeights2D : public EventVariable{
 public:
 EventVariableMatrixWeights2D(TString name, TString productname, TString suffix, TString loosename, TString tightname) : EventVariable(name), m_suffix(suffix), m_loosename(loosename), m_tightname(tightname) {m_productnames.push_back(productname);}


  void addProduct(TString);

  bool calculate(BaseHandler*);

  void ResetFakePromptRates();
  void ResetLooseTight();
  void SetFakePromptRates(TLorentzVector, TLorentzVector, int array[2], TString);
  void setVariablesToZero(BaseHandler*);

  double mP( double, double, double, TString );
  double mF( double, double, double, TString );
  double eP( double, double, double, TString );
  double eF( double, double, double, TString );
  double tP( double, double, double, TString );
  double tF( double, double, double, TString );

  double p1, p2;
  double f1, f2;

  double nLL;
  double nLT;
  double nTL;
  double nTT;

  //double fake
  double Wff();
  //single fake
  double Wfp();
  double Wpf();
  //zero fake
  double Wpp();

  double WfakeBckg();

  ClassDef(EventVariableMatrixWeights2D,1);

 private:
  TString m_suffix;
  TString m_loosename;
  TString m_tightname;
  std::vector<TString> m_productnames;


};

#endif
