#ifndef SignatureObjectFlat_h
#define SignatureObjectFlat_h
#include <TObject.h>
#include <TROOT.h>
#include <string>
#include <map>
#include <iostream>
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

class SignatureObjectFlat : public TObject {
 public:
  SignatureObjectFlat(double x=0,double y=0, double z=0, double t=0);
  SignatureObjectFlat(SignatureObjectFlat&);
  SignatureObjectFlat(SignatureObject&);
  virtual ~SignatureObjectFlat();

  void addAssociate(std::string,SignatureObjectFlat*);
  void Print();

 protected:

  Int_t nDouble_;
  Int_t nInt_;
  Int_t nTString_;
  Int_t nBool_;
  Int_t nAssociation_;
  Int_t iAssociation_;

  std::string* m_variableMapDoubleKeys; //[nDouble_]
  std::string* m_variableMapIntKeys; //[nInt_]
  std::string* m_variableMapTStringKeys; //[nTString_]
  std::string* m_variableMapBoolKeys; //[nBool_]
  //std::string* m_associationKeys; //[nAssociation_]

  double* m_variableMapDoubleValues; //[nDouble_]
  int* m_variableMapIntValues; //[nInt_]
  std::string* m_variableMapTStringValues; //[nTString_]
  bool* m_variableMapBoolValues; //[nBool_]
  //SignatureObjectFlat** m_associationValues; //[nAssociation_]

  /*
  std::vector<std::string> m_variableMapDoubleKeys;
  std::vector<double> m_variableMapDoubleValues;
  std::vector<std::string> m_variableMapIntKeys;
  std::vector<int> m_variableMapIntValues;
  std::vector<std::string> m_variableMapTStringKeys;
  std::vector<std::string> m_variableMapTStringValues;
  std::vector<std::string> m_variableMapBoolKeys;
  std::vector<bool> m_variableMapBoolValues;
  */
  std::vector<std::string> m_associationKeys;
  std::vector<SignatureObjectFlat*> m_associationValues;

  double px_;
  double py_;
  double pz_;
  double e_;

  ClassDef(SignatureObjectFlat,1);

};

inline SignatureObjectFlat::SignatureObjectFlat(double x,double y, double z, double t):TObject(),px_(x),py_(y),pz_(z),e_(t){
  nDouble_ = 0;
  nInt_ = 0;
  nTString_ = 0;
  nBool_ = 0;
  nAssociation_ = 0;
  iAssociation_ = 0;

  m_variableMapDoubleKeys = NULL;
  m_variableMapIntKeys = NULL;
  m_variableMapTStringKeys = NULL;
  m_variableMapBoolKeys = NULL;
  //m_associationKeys = NULL;

  m_variableMapDoubleValues = NULL;
  m_variableMapIntValues = NULL;
  m_variableMapTStringValues = NULL;
  m_variableMapBoolValues = NULL;
  //m_associationValues = NULL;
}

#endif
