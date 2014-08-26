#include "RutgersIAF/EventAnalyzer/interface/BaseTreeReader.h"
#include <TTree.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(BaseTreeReader)

using namespace std;

BaseTreeReader::BaseTreeReader(TTree* tree) : m_inTree(tree)
{

}

BaseTreeReader::~BaseTreeReader()
{
  clearProducts();
}

int BaseTreeReader::GetEntries()
{
  if(m_inTree)return m_inTree->GetEntries();
  return 0;
}

int BaseTreeReader::GetEntry(int entry)
{
  clearProducts();
  int rval = m_inTree->GetEntry(entry);
  makeProducts();
  return rval;
}

map<TString,vector<SignatureObject*> > BaseTreeReader::getProducts()
{
  return m_productmap;
}

void BaseTreeReader::clearProducts()
{
  map<TString,vector<SignatureObject*> >::iterator iter;
  while(!m_productmap.empty()){
    iter = m_productmap.begin();
    vector<SignatureObject*> product = (*iter).second;
    while(!product.empty()){
      delete product.back();
      product.pop_back();
    }
    m_productmap.erase(iter);
  }

  m_variable_mapint.clear();
  m_variable_maplong.clear();
  m_variable_mapdouble.clear();
  m_variable_mapTString.clear();
  m_variable_mapbool.clear();
}

bool BaseTreeReader::getVariable(TString name,int &value)
{
  map<TString,int>::iterator iter = m_variable_mapint.find(name);
  if(iter == m_variable_mapint.end())return false;
  value = (*iter).second;
  return true;
}
bool BaseTreeReader::getVariable(TString name,long &value)
{
  map<TString,long>::iterator iter = m_variable_maplong.find(name);
  if(iter == m_variable_maplong.end())return false;
  value = (*iter).second;
  return true;
}
bool BaseTreeReader::getVariable(TString name,double &value)
{
  map<TString,double>::iterator iter = m_variable_mapdouble.find(name);
  if(iter == m_variable_mapdouble.end())return false;
  value = (*iter).second;
  return true;
}
bool BaseTreeReader::getVariable(TString name,TString &value)
{
  map<TString,TString>::iterator iter = m_variable_mapTString.find(name);
  if(iter == m_variable_mapTString.end())return false;
  value = (*iter).second;
  return true;
}
bool BaseTreeReader::getVariable(TString name,bool &value)
{
  map<TString,bool>::iterator iter = m_variable_mapbool.find(name);
  if(iter == m_variable_mapbool.end())return false;
  value = (*iter).second;
  return true;
}

vector<SignatureObject*> BaseTreeReader::getProduct(TString productName)
{
  vector<SignatureObject*> retvec;
  map<TString,vector<SignatureObject*> >::const_iterator pIter = m_productmap.find(productName);
  if(pIter == m_productmap.end()){
    cerr<<"Product "<<productName<<" not found"<<endl;
    return retvec;
  }

  retvec = (*pIter).second;
  return retvec;
}

void BaseTreeReader::setVariable(TString varname, int val)
{
  m_variable_mapint[varname] = val;
}

void BaseTreeReader::setVariable(TString varname, long val)
{
  m_variable_maplong[varname] = val;
}

void BaseTreeReader::setVariable(TString varname, double val)
{
  m_variable_mapdouble[varname] = val;
}

void BaseTreeReader::setVariable(TString varname, TString val)
{
  m_variable_mapTString[varname] = val;
}

void BaseTreeReader::setVariable(TString varname, bool val)
{
  m_variable_mapbool[varname] = val;
}
