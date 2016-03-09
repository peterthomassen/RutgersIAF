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

  float mP( float, float, float, TString );
  float mF( float, float, float, TString );
  float eP( float, float, float, TString );
  float eF( float, float, float, TString );
  float tP( float, float, float, TString );
  float tF( float, float, float, TString );

  float p1, p2;
  float f1, f2;

  float nLL;
  float nLT;
  float nTL;
  float nTT;

  //double fake
  float Wff();
  //single fake
  float Wfp();
  float Wpf();
  //zero fake
  float Wpp();

  float WfakeBckg();

  ClassDef(EventVariableMatrixWeights2D,1);

 private:
  TString m_suffix;
  TString m_loosename;
  TString m_tightname;
  std::vector<TString> m_productnames;


};

#endif
