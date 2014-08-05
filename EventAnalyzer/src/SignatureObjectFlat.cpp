#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObjectFlat.h"

ClassImp(SignatureObjectFlat)

using namespace std;

SignatureObjectFlat::SignatureObjectFlat(SignatureObjectFlat &sigObj) : TObject()
{
  px_ = sigObj.px_;
  py_ = sigObj.py_;
  pz_ = sigObj.pz_;
  e_ = sigObj.e_;
  
  m_variableMapDoubleKeys = sigObj.m_variableMapDoubleKeys;
  m_variableMapDoubleValues = sigObj.m_variableMapDoubleValues;
  m_variableMapIntKeys = sigObj.m_variableMapIntKeys;
  m_variableMapIntValues = sigObj.m_variableMapIntValues;
  m_variableMapTStringKeys = sigObj.m_variableMapTStringKeys;
  m_variableMapTStringValues = sigObj.m_variableMapTStringValues;
  m_variableMapBoolKeys = sigObj.m_variableMapBoolKeys;
  m_variableMapBoolValues = sigObj.m_variableMapBoolValues;

  m_associationKeys = sigObj.m_associationKeys;
  m_associationValues = sigObj.m_associationValues;
  
}

SignatureObjectFlat::~SignatureObjectFlat()
{
   
  m_variableMapDoubleKeys.clear();
  m_variableMapDoubleValues.clear();
  m_variableMapIntKeys.clear();
  m_variableMapIntValues.clear();
  m_variableMapTStringKeys.clear();
  m_variableMapTStringValues.clear();
  m_variableMapTStringKeys.clear();
  m_variableMapTStringValues.clear();

  m_associationKeys.clear();
  m_associationValues.clear();
  /*  

  delete[] m_variableMapDoubleKeys;
  delete[] m_variableMapIntKeys;
  delete[] m_variableMapBoolKeys;
  delete[] m_variableMapTStringKeys;
  //delete[] m_associationKeys;

  delete[] m_variableMapDoubleValues;
  delete[] m_variableMapIntValues;
  delete[] m_variableMapBoolValues;
  delete[] m_variableMapTStringValues;
  //delete[] m_associationValues;


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
  */

}

SignatureObjectFlat::SignatureObjectFlat(SignatureObject& sigObj)
{
  px_ = sigObj.X();
  py_ = sigObj.Y();
  pz_ = sigObj.Z();
  e_ = sigObj.T();

  nDouble_ = sigObj.m_variableMapDouble.size();
  nInt_ = sigObj.m_variableMapInt.size();
  nTString_ = sigObj.m_variableMapTString.size();
  nBool_ = sigObj.m_variableMapBool.size();
  nAssociation_ = sigObj.m_association_map.size();
  iAssociation_ = 0;
  /*
  //cout<<" "<<nDouble_<<" "<<nInt_<<" "<<nTString_<<" "<<nBool_<<endl;
  if(nDouble_ > 0){
    m_variableMapDoubleKeys = new string[nDouble_];
    m_variableMapDoubleValues = new double[nDouble_];
  }else{
    nDouble_ = 1;
    m_variableMapDoubleKeys = new string[nDouble_];
    m_variableMapDoubleValues = new double[nDouble_];
    m_variableMapDoubleKeys[0] = "empty";
    m_variableMapDoubleValues[0] = 0.0;
  }
  if(nInt_ > 0){
    m_variableMapIntKeys = new string[nInt_];
    m_variableMapIntValues = new int[nInt_];
  }else{
    nInt_ = 1;
    m_variableMapIntKeys = new string[nInt_];
    m_variableMapIntValues = new int[nInt_];
    m_variableMapIntKeys[0] = "empty";
    m_variableMapIntValues[0] = 0;
  }
  if(nTString_ > 0){
    m_variableMapTStringValues = new string[nTString_];
    m_variableMapTStringKeys = new string[nTString_];
  }else{
    nTString_ = 1;
    m_variableMapTStringValues = new string[nTString_];
    m_variableMapTStringKeys = new string[nTString_];
    m_variableMapTStringValues[0] = "empty";
    m_variableMapTStringKeys[0] = "empty";
  }
  if(nBool_ > 0){
    m_variableMapBoolKeys = new string[nBool_];
    m_variableMapBoolValues = new bool[nBool_];
  }else{
    nBool_ = 1;
    m_variableMapBoolKeys = new string[nBool_];
    m_variableMapBoolValues = new bool[nBool_];
    m_variableMapBoolKeys[0] = "empty";
    m_variableMapBoolValues[0] = false;
  }
  //m_associationKeys = new string[nAssociation_];
  //m_associationValues = new SignatureObjectFlat*[nAssociation_];


  int i = 0;
  for(map<TString,double>::iterator iter=sigObj.m_variableMapDouble.begin(); iter != sigObj.m_variableMapDouble.end(); iter++){
    m_variableMapDoubleKeys[i] = string((*iter).first);
    m_variableMapDoubleValues[i] = (*iter).second;
    i++;
  }
  i = 0;
  for(map<TString,int>::iterator iter=sigObj.m_variableMapInt.begin(); iter != sigObj.m_variableMapInt.end(); iter++){
    m_variableMapIntKeys[i] = string((*iter).first);
    m_variableMapIntValues[i] = (*iter).second;
    i++;
  }
  i = 0;
  for(map<TString,TString>::iterator iter=sigObj.m_variableMapTString.begin(); iter != sigObj.m_variableMapTString.end(); iter++){
    m_variableMapTStringKeys[i] = string((*iter).first);
    m_variableMapTStringValues[i] = string((*iter).second);
    i++;
  }
  i = 0;
  for(map<TString,bool>::iterator iter=sigObj.m_variableMapBool.begin(); iter != sigObj.m_variableMapBool.end(); iter++){
    m_variableMapBoolKeys[i] = string((*iter).first);
    m_variableMapBoolValues[i] = (*iter).second;
    i++;
  }
  */
  
  for(map<TString,double>::iterator iter=sigObj.m_variableMapDouble.begin(); iter != sigObj.m_variableMapDouble.end(); iter++){
    m_variableMapDoubleKeys.push_back(string((*iter).first));
    m_variableMapDoubleValues.push_back((*iter).second);
  }
  for(map<TString,int>::iterator iter=sigObj.m_variableMapInt.begin(); iter != sigObj.m_variableMapInt.end(); iter++){
    m_variableMapIntKeys.push_back(string((*iter).first));
    m_variableMapIntValues.push_back((*iter).second);
  }
  for(map<TString,TString>::iterator iter=sigObj.m_variableMapTString.begin(); iter != sigObj.m_variableMapTString.end(); iter++){
    m_variableMapTStringKeys.push_back(string((*iter).first));
    m_variableMapTStringValues.push_back(string((*iter).second));
  }
  for(map<TString,bool>::iterator iter=sigObj.m_variableMapBool.begin(); iter != sigObj.m_variableMapBool.end(); iter++){
    m_variableMapBoolKeys.push_back(string((*iter).first));
    m_variableMapBoolValues.push_back((*iter).second);
  }
  
}

void SignatureObjectFlat::addAssociate(string name,SignatureObjectFlat* ptr)
{
  /*
  if(iAssociation_ == nAssociation_)return;
  m_associationKeys[iAssociation_] = name;
  m_associationValues[iAssociation_] = ptr;
  iAssociation_++;
  */
  if(find(m_associationValues.begin(),m_associationValues.end(),ptr) != m_associationValues.end())return;
  m_associationKeys.push_back(name);
  m_associationValues.push_back(ptr);

}

void SignatureObjectFlat::Print()
{
  if(nDouble_ > 0)
    cout<<"  d "<<nDouble_<<" "<<m_variableMapDoubleKeys[nDouble_-1]<<" "<<m_variableMapDoubleValues[nDouble_-1];
  if(nInt_ > 0)
    cout<<" i "<<nInt_<<" "<<m_variableMapIntKeys[nInt_-1]<<" "<<m_variableMapIntValues[nInt_-1];
  if(nTString_ > 0)
    cout<<" ts "<<nTString_<<" "<<m_variableMapTStringKeys[nTString_-1]<<" "<<m_variableMapTStringValues[nTString_-1];
  if(nBool_ > 0)
    cout<<" b "<<nBool_<<" "<<m_variableMapBoolKeys[nBool_-1]<<" "<<m_variableMapBoolValues[nBool_-1];
  cout<<endl;
}
