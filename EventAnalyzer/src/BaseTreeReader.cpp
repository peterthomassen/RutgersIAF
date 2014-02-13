#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"
#include <TTree.h>
#include <TString.h>
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

ClassImp(BaseTreeReader)

using namespace std;

BaseTreeReader::BaseTreeReader(TTree* tree) : m_tree(tree)
{

}

BaseTreeReader::~BaseTreeReader()
{
  clearProducts();
}

int BaseTreeReader::GetEntries()
{
  if(m_tree)return m_tree->GetEntries();
  return 0;
}

int BaseTreeReader::GetEntry(int entry)
{
  clearProducts();
  int rval = m_tree->GetEntry(entry);
  createProducts();
  return rval;
}

map<TString,vector<SignatureObject*> > BaseTreeReader::getProducts()
{
  return m_products;
}

void BaseTreeReader::clearProducts()
{
  map<TString,vector<SignatureObject*> >::iterator iter;
  while(!m_products.empty()){
    iter = m_products.begin();
    vector<SignatureObject*> product = (*iter).second;
    while(!product.empty()){
      delete product.back();
      product.pop_back();
    }
    m_products.erase(iter);
  }
}

bool BaseTreeReader::getVariable(TString name,int &value)
{
  map<TString,int>::iterator iter = m_variable_map_int.find(name);
  if(iter == m_variable_map_int.end())return false;
  value = (*iter).second;
  return true;
}
bool BaseTreeReader::getVariable(TString name,long &value)
{
  map<TString,long>::iterator iter = m_variable_map_long.find(name);
  if(iter == m_variable_map_long.end())return false;
  value = (*iter).second;
  return true;
}
bool BaseTreeReader::getVariable(TString name,double &value)
{
  map<TString,double>::iterator iter = m_variable_map_double.find(name);
  if(iter == m_variable_map_double.end())return false;
  value = (*iter).second;
  return true;
}
bool BaseTreeReader::getVariable(TString name,TString &value)
{
  map<TString,TString>::iterator iter = m_variable_map_TString.find(name);
  if(iter == m_variable_map_TString.end())return false;
  value = (*iter).second;
  return true;
}
bool BaseTreeReader::getVariable(TString name,bool &value)
{
  map<TString,bool>::iterator iter = m_variable_map_bool.find(name);
  if(iter == m_variable_map_bool.end())return false;
  value = (*iter).second;
  return true;
}

vector<SignatureObject*> BaseTreeReader::getProduct(TString productName)
{
  vector<SignatureObject*> retvec;
  map<TString,vector<SignatureObject*> >::const_iterator pIter = m_products.find(productName);
  if(pIter == m_products.end()){
    cerr<<"Product "<<productName<<" not found"<<endl;
    return retvec;
  }

  retvec = (*pIter).second;
  return retvec;
}

void BaseTreeReader::setVariable(TString varname, int val)
{
  m_variable_map_int[varname] = val;
}

void BaseTreeReader::setVariable(TString varname, long val)
{
  m_variable_map_long[varname] = val;
}

void BaseTreeReader::setVariable(TString varname, double val)
{
  m_variable_map_double[varname] = val;
}

void BaseTreeReader::setVariable(TString varname, TString val)
{
  m_variable_map_TString[varname] = val;
}

void BaseTreeReader::setVariable(TString varname, bool val)
{
  m_variable_map_bool[varname] = val;
}
