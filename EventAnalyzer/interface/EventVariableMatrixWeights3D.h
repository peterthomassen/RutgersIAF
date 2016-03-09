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
  void SetFakePromptRates(TLorentzVector, TLorentzVector, TLorentzVector, int array[3], TString);
  void setVariablesToZero(BaseHandler*);

  float mP( float, float, float, TString );
  float mF( float, float, float, TString );
  float eP( float, float, float, TString );
  float eF( float, float, float, TString );
  float tP( float, float, float, TString );
  float tF( float, float, float, TString );

  float p1, p2, p3;
  float f1, f2, f3;

  float nLLL;
  float nLLT, nLTL, nTLL;
  float nLTT, nTLT, nTTL;
  float nTTT;

  //triple fake
  float Wfff();
  //double fake
  float Wffp();
  float Wfpf();
  float Wpff();
  //single fake
  float Wfpp();
  float Wpfp();
  float Wppf();
  //zero fake
  float Wppp();

  float WfakeBckg();

  ClassDef(EventVariableMatrixWeights3D,1);

 private:
  TString m_suffix;
  TString m_loosename;
  TString m_tightname;
  std::vector<TString> m_productnames;


};

#endif
