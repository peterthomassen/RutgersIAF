#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include <vector>
#include <TClonesArray.h>
#include <TTree.h>
#include <TFile.h>

using namespace std;

ClassImp(SignatureTreeWriter)

SignatureTreeWriter::SignatureTreeWriter(BaseHandler* handler,TString treename): BaseTreeWriter(handler,treename)
{
  m_clonesarray = new TClonesArray("SignatureObject",1000);
  m_tree->Branch("SignatureObjects",m_clonesarray);
  m_tree->Branch("VariablesDouble",&m_variable_map_double);
  m_tree->Branch("VariablesInt",&m_variable_map_int);
  m_tree->Branch("VariablesLong",&m_variable_map_long);
  m_tree->Branch("VariablesTString",&m_variable_map_TString);
  m_tree->Branch("VariablesBool",&m_variable_map_bool);
}
SignatureTreeWriter::~SignatureTreeWriter()
{
  delete m_clonesarray;
}
void SignatureTreeWriter::finish()
{
  m_handler->getOutFile()->cd();
  m_tree->Write();
}

void SignatureTreeWriter::fillTree()
{
  m_clonesarray->Clear();

  m_variable_map_double.clear();
  m_variable_map_int.clear();
  m_variable_map_long.clear();
  m_variable_map_TString.clear();
  m_variable_map_bool.clear();

  m_variable_map_double = m_handler->m_variable_map_double;
  m_variable_map_int = m_handler->m_variable_map_int;
  m_variable_map_long = m_handler->m_variable_map_long;
  m_variable_map_TString = m_handler->m_variable_map_TString;
  m_variable_map_bool = m_handler->m_variable_map_bool;

  map<TString,vector<SignatureObject*> > products = m_handler->getReader()->getProducts();
  map<TString,vector<SignatureObject*> >::const_iterator iter;
  map<SignatureObject*,SignatureObject*> oldToNew;
  map<SignatureObject*,SignatureObject*> newToOld;
  int i = 0;
  for(iter = products.begin(); iter != products.end(); iter++){
    TString productname = (*iter).first;
    vector<SignatureObject*> v = (*iter).second;
    for(int j = 0; j < (int)v.size();j++){
      bool check = false;
      bool isset = v[j]->getVariable("WRITEOBJECT",check);
      if(!isset || !check)continue;
      new((*m_clonesarray)[i]) SignatureObject(*v[j]);
      ((SignatureObject*)m_clonesarray->At(i))->setVariable("PRODUCTNAME",productname);
      oldToNew[v[j]] = (SignatureObject*)m_clonesarray->At(i);
      newToOld[(SignatureObject*)m_clonesarray->At(i)] = v[j];
      i++;
    }
  }
  //Fix associations
  int n = m_clonesarray->GetEntries();
  for(int j = 0; j < n; j++){
    SignatureObject* newObject = (SignatureObject*)m_clonesarray->At(j);
    map<SignatureObject*,SignatureObject*>::iterator iterNew = newToOld.find(newObject);
    if(iterNew == newToOld.end())continue;
    map<TString,SignatureObject*> oldAssociates = newObject->getAssociates();
    map<TString,SignatureObject*> newAssociates;
    map<TString,SignatureObject*>::iterator associateIter;
    for(associateIter = oldAssociates.begin(); associateIter != oldAssociates.end(); associateIter++){
      TString associateName = (*associateIter).first;
      SignatureObject* oldAssociate = (*associateIter).second;
      map<SignatureObject*,SignatureObject*>::const_iterator iterOld = oldToNew.find(oldAssociate);
      if(iterOld == oldToNew.end())continue;
      newAssociates[associateName] = (*iterOld).second;
    }
    newObject->setAssociates(newAssociates);
  }


  m_tree->Fill();
}
