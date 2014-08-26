#ifndef EventVariableSmearMET_h
#define EventVariableSmearMET_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include <TRandom3.h>

class EventVariableSmearMET : public EventVariable{
 public:
  EventVariableSmearMET(TString name, TString productname, TString htname="HT", TString nvname="NRECOVERTICES", double mc_sigma0 = 2.68, double mc_sigmaHT = 4.14, double mc_sigmaNV = 3.48, double data_sigma0 = 2.68, double data_sigmaHT = 5.10, double data_sigmaNV = 3.48) : EventVariable(name),m_productname(productname),m_htname(htname),m_nvname(nvname),m_data_sigma0(data_sigma0),m_data_sigmaHT(data_sigmaHT),m_data_sigmaNV(data_sigmaNV),m_mc_sigma0(mc_sigma0),m_mc_sigmaHT(mc_sigmaHT), m_mc_sigmaNV(mc_sigmaNV) {/* no-op */}

  void setSeed(int c){m_random.SetSeed(c);}
  bool calculate(BaseHandler*);

  ClassDef(EventVariableSmearMET,1);

 private:
  TString m_productname;
  TString m_htname;
  TString m_nvname;
  double m_data_sigma0;
  double m_data_sigmaHT;
  double m_data_sigmaNV;
  double m_mc_sigma0;
  double m_mc_sigmaHT;
  double m_mc_sigmaNV;
  TRandom3 m_random;


};

#endif
