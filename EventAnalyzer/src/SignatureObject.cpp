#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObjectFlat.h"

ClassImp(SignatureObject)

using namespace std;

SignatureObject::SignatureObject(SignatureObject& sigObj) : TLorentzVector(TLorentzVector(sigObj))
{
  m_variableMapDouble = sigObj.m_variableMapDouble;
  m_variableMapInt = sigObj.m_variableMapInt;
  m_variableMapTString = sigObj.m_variableMapTString;
  m_variableMapBool = sigObj.m_variableMapBool;
  m_association_map = sigObj.m_association_map;
}

SignatureObject::SignatureObject(SignatureObjectFlat& sigObj) : TLorentzVector(sigObj.px_,sigObj.py_,sigObj.pz_,sigObj.e_){

  for(int i = 0; i < sigObj.nDouble_; i++){
    setVariable(TString(sigObj.m_variableMapDoubleKeys[i]),sigObj.m_variableMapDoubleValues[i]);
  }
  for(int i = 0; i < sigObj.nInt_; i++){
    setVariable(sigObj.m_variableMapIntKeys[i],sigObj.m_variableMapIntValues[i]);
  }
  for(int i = 0; i < sigObj.nBool_; i++){
    setVariable(sigObj.m_variableMapBoolKeys[i],sigObj.m_variableMapBoolValues[i]);
  }
  for(int i = 0; i < sigObj.nTString_; i++){
    setVariable(sigObj.m_variableMapTStringKeys[i],sigObj.m_variableMapTStringValues[i]);
  }

}

SignatureObject::~SignatureObject()
{
  m_variableMapDouble.clear();
  m_variableMapInt.clear();
  m_variableMapTString.clear();
  m_variableMapBool.clear();
  m_association_map.clear();
}

bool SignatureObjectComparison(SignatureObject* a, SignatureObject* b)
{
  return a->Pt() < b->Pt();
}

ostream& operator<<(ostream& os, const SignatureObject& so)
{
  os <<"   pt : "<<so.Pt()<<" eta: "<<so.Eta()<<" phi: "<<so.Phi()<<" m: "<<so.M()<<endl;
  map<TString,double>::const_iterator iterD;
  for(iterD = so.m_variableMapDouble.begin(); iterD != so.m_variableMapDouble.end(); iterD++){
    os << (*iterD).first << " " << (*iterD).second <<" ";
  }
  os << endl;

  map<TString,int>::const_iterator iterI;
  for(iterI = so.m_variableMapInt.begin(); iterI != so.m_variableMapInt.end(); iterI++){
    os << (*iterI).first << " " << (*iterI).second <<" ";
  }
  os << endl;

  map<TString,TString>::const_iterator iterT;
  for(iterT = so.m_variableMapTString.begin(); iterT != so.m_variableMapTString.end(); iterT++){
    os << (*iterT).first << " " << (*iterT).second <<" ";
  }
  os << endl;

  map<TString,bool>::const_iterator iterB;
  for(iterB = so.m_variableMapBool.begin(); iterB != so.m_variableMapBool.end(); iterB++){
    os << (*iterB).first << " " << (*iterB).second <<" ";
  }
  os << endl;

  return os;
}
