#include "RutgersIAF2012/EventAnalyzer/interface/FlatTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObjectFlat.h"

ClassImp(FlatTreeReader)

using namespace std;

FlatTreeReader::FlatTreeReader(TTree* tree) : BaseTreeReader(tree)
{
  //clonesarray_ = new TClonesArray("SignatureObjectFlat",500);
  clonesarray_ = new TObjArray();
  p_variable_map_double_keys = 0;
  p_variable_map_long_keys = 0;
  p_variable_map_int_keys = 0;
  p_variable_map_TString_keys = 0;
  p_variable_map_bool_keys = 0;
   
  p_variable_map_double_values = 0;
  p_variable_map_long_values = 0;
  p_variable_map_int_values = 0;
  p_variable_map_TString_values = 0;
  p_variable_map_bool_values = 0;

  Init(tree);
}

FlatTreeReader::~FlatTreeReader()
{
   if (!m_inTree) return;
   delete m_inTree->GetCurrentFile();

}

void FlatTreeReader::Init(TTree* tree)
{
  if (!tree) return;
  m_inTree = tree;

   m_inTree->SetBranchAddress("SignatureObjectFlats",&clonesarray_);
   m_inTree->SetBranchAddress("event",&event_);
   m_inTree->SetBranchAddress("run",&run_);
   m_inTree->SetBranchAddress("lumi",&lumi_);
   m_inTree->Branch("VariableDoubleValues",&p_variable_map_double_values);
   m_inTree->Branch("VariableIntValues",&p_variable_map_int_values);
   m_inTree->Branch("VariableLongValues",&p_variable_map_long_values);
   m_inTree->Branch("VariableTStringValues",&p_variable_map_TString_values);
   m_inTree->Branch("VariableBoolValues",&p_variable_map_bool_values);
   m_inTree->Branch("VariableDoubleKeys",&p_variable_map_double_keys);
   m_inTree->Branch("VariableIntKeys",&p_variable_map_int_keys);
   m_inTree->Branch("VariableLongKeys",&p_variable_map_long_keys);
   m_inTree->Branch("VariableTStringKeys",&p_variable_map_TString_keys);
   m_inTree->Branch("VariableBoolKeys",&p_variable_map_bool_keys);

}

void FlatTreeReader::makeProducts()
{

  createVariables();

  int nObjects = clonesarray_->GetEntries();
  vector<SignatureObject*> v;
  for(int i = 0; i < nObjects; i++){
    SignatureObjectFlat* sof = (SignatureObjectFlat*)clonesarray_->At(i);
    //sof->Print();
    SignatureObject* so = new SignatureObject(*sof);
    v.push_back(so);
  }
  m_productmap["ALL"] = v;

}
void FlatTreeReader::createVariables()
{
  setVariable("RUN",run_);
  setVariable("EVENT",event_);
  setVariable("LUMI",lumi_);

  for(int i = 0; i < (int)p_variable_map_double_keys->size(); i++){
    setVariable((*p_variable_map_double_keys)[i],(*p_variable_map_double_values)[i]);
  }
  for(int i = 0; i < (int)p_variable_map_int_keys->size(); i++){
    setVariable((*p_variable_map_int_keys)[i],(*p_variable_map_int_values)[i]);
  }
  for(int i = 0; i < (int)p_variable_map_long_keys->size(); i++){
    setVariable((*p_variable_map_long_keys)[i],(*p_variable_map_long_values)[i]);
  }
  for(int i = 0; i < (int)p_variable_map_TString_keys->size(); i++){
    setVariable((*p_variable_map_TString_keys)[i],(*p_variable_map_TString_values)[i]);
  }
  for(int i = 0; i < (int)p_variable_map_bool_keys->size(); i++){
    setVariable((*p_variable_map_bool_keys)[i],(*p_variable_map_bool_values)[i]);
  }

}

void FlatTreeReader::dumpEventInfo()
{

}
