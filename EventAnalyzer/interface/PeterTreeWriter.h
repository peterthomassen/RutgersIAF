#ifndef PeterTreeWriter_h
#define PeterTreeWriter_h

#include <TROOT.h>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeWriter.h"
#include <map>

class TTree;
class TString;
class TFile;
class BaseHandler;
//class TClonesArray;

class PeterTreeWriter : public BaseTreeWriter{
 public:
  PeterTreeWriter(BaseHandler*,TString);
  virtual ~PeterTreeWriter();

  virtual void finish();
  virtual void fillTree();

 private:
  //TClonesArray* m_clonesarray;
  std::map<TString,double> m_variable_map_double;
  std::map<TString,int> m_variable_map_int;
  std::map<TString,long> m_variable_map_long;
  std::map<TString,TString> m_variable_map_TString;
  std::map<TString,bool> m_variable_map_bool;

  double m_met;
  double m_ht;
  double m_st;
  int m_NOSSF;

  ClassDef(PeterTreeWriter,1);

};


#endif
