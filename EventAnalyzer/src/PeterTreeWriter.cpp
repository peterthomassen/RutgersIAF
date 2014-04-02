#include "RutgersIAF2012/EventAnalyzer/interface/PeterTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include <vector>
#include <TClonesArray.h>
#include <TTree.h>
#include <TFile.h>
#include <assert.h>

using namespace std;

ClassImp(PeterTreeWriter)

PeterTreeWriter::PeterTreeWriter(BaseHandler* handler,TString treename): BaseTreeWriter(handler,treename)
{
  //m_clonesarray = new TClonesArray("SignatureObject",1000);
  //m_tree->Branch("SignatureObjects",m_clonesarray);
  m_tree->Branch("VariablesDouble",&m_variable_map_double);
  m_tree->Branch("VariablesInt",&m_variable_map_int);
  m_tree->Branch("VariablesLong",&m_variable_map_long);
  m_tree->Branch("VariablesTString",&m_variable_map_TString);
  m_tree->Branch("VariablesBool",&m_variable_map_bool);
  
  m_tree->Branch("MET", &m_met);
  m_tree->Branch("HT", &m_ht);
  m_tree->Branch("ST", &m_st);
  m_tree->Branch("NOSSF", &m_NOSSF);
}
PeterTreeWriter::~PeterTreeWriter()
{
//  delete m_clonesarray;
}
void PeterTreeWriter::finish()
{
  m_handler->getOutFile()->cd();
  m_tree->Write();
}

void PeterTreeWriter::fillTree()
{
//  m_clonesarray->Clear();

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

  int flag = true;
  flag &= (int)m_handler->getVariable("MET",   m_met);
  flag &= (int)m_handler->getVariable("HT",    m_ht);
  flag &= (int)m_handler->getVariable("ST",    m_st);
  flag &= (int)m_handler->getVariable("NOSSF", m_NOSSF);
  assert(flag);

  m_tree->Fill();
}
