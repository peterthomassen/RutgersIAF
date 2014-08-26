#ifndef SignatureTreeWriter_h
#define SignatureTreeWriter_h

#include <TROOT.h>
#include "RutgersIAF/EventAnalyzer/interface/BaseTreeWriter.h"
#include <map>

class TTree;
class TString;
class TFile;
class BaseHandler;
class TClonesArray;

class SignatureTreeWriter : public BaseTreeWriter{
 public:
  SignatureTreeWriter(BaseHandler*,TString);
  virtual ~SignatureTreeWriter();

  virtual void finish();
  virtual void fillTree();

 private:
  TClonesArray* m_clonesarray;
  std::map<TString,double> m_variable_map_double;
  std::map<TString,int> m_variable_map_int;
  std::map<TString,long> m_variable_map_long;
  std::map<TString,TString> m_variable_map_TString;
  std::map<TString,bool> m_variable_map_bool;

  ClassDef(SignatureTreeWriter,1);

};


#endif
