#include "RutgersIAF/EventAnalyzer/interface/FlatTreeReader.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObjectFlat.h"

ClassImp(FlatTreeReader)

using namespace std;

FlatTreeReader::FlatTreeReader(TTree* tree) : BaseTreeReader(tree)
{
  //clonesarray_ = new TClonesArray("SignatureObjectFlat",500);
  clonesarray_ = new TObjArray();
  p_variable_map_double_values = 0;
  p_variable_map_long_values = 0;
  p_variable_map_int_values = 0;
  p_variable_map_TString_values = 0;
  p_variable_map_bool_values = 0;
   
  p_variable_map_double_keys = 0;
  p_variable_map_long_keys = 0;
  p_variable_map_int_keys = 0;
  p_variable_map_TString_keys = 0;
  p_variable_map_bool_keys = 0;

  Init(tree);
}

FlatTreeReader::~FlatTreeReader()
{
  clonesarray_->Delete();
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
   m_inTree->SetBranchAddress("VariableDoubleValues",&p_variable_map_double_values);
   m_inTree->SetBranchAddress("VariableIntValues",&p_variable_map_int_values);
   m_inTree->SetBranchAddress("VariableLongValues",&p_variable_map_long_values);
   m_inTree->SetBranchAddress("VariableTStringValues",&p_variable_map_TString_values);
   m_inTree->SetBranchAddress("VariableBoolValues",&p_variable_map_bool_values);
   m_inTree->SetBranchAddress("VariableDoubleKeys",&p_variable_map_double_keys);
   m_inTree->SetBranchAddress("VariableIntKeys",&p_variable_map_int_keys);
   m_inTree->SetBranchAddress("VariableLongKeys",&p_variable_map_long_keys);
   m_inTree->SetBranchAddress("VariableTStringKeys",&p_variable_map_TString_keys);
   m_inTree->SetBranchAddress("VariableBoolKeys",&p_variable_map_bool_keys);

}

void FlatTreeReader::makeProducts()
{

  createVariables();

  int nObjects = clonesarray_->GetEntries();
  vector<SignatureObject*> v;
  vector<SignatureObject*> mc;
  for(int i = 0; i < nObjects; i++){
    SignatureObjectFlat* sof = (SignatureObjectFlat*)clonesarray_->At(i);
    //sof->Print();
    SignatureObject* so = new SignatureObject(*sof);
    v.push_back(so);
    TString inputtype = "UNKNOWN";
    bool hasInputtype = so->getVariable("INPUTTYPE",inputtype);
    if(!hasInputtype)continue;
    if(inputtype == "mc")mc.push_back(so);
  }
  m_productmap["ALL"] = v;
  m_productmap["allmc"] = mc;
  clonesarray_->Delete();

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
    setVariable((*p_variable_map_TString_keys)[i],TString((*p_variable_map_TString_values)[i]));
  }
  for(int i = 0; i < (int)p_variable_map_bool_keys->size(); i++){
    setVariable((*p_variable_map_bool_keys)[i],(*p_variable_map_bool_values)[i]);
  }

}

void FlatTreeReader::dumpEventInfo()
{

}

void FlatTreeReader::clearProducts()
{
  map<TString,vector<SignatureObject*> >::iterator iter;
  while(!m_productmap.empty()){
    iter = m_productmap.begin();
    vector<SignatureObject*> product = (*iter).second;
    if((*iter).first == "ALL"){
      while(!product.empty()){
        delete product.back();
        product.pop_back();
      }
    }
    m_productmap.erase(iter);
  }

  m_variable_mapint.clear();
  m_variable_maplong.clear();
  m_variable_mapdouble.clear();
  m_variable_mapTString.clear();
  m_variable_mapbool.clear();
}

