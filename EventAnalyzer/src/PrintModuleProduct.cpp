#include "RutgersIAF/EventAnalyzer/interface/PrintModuleProduct.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include <algorithm>

ClassImp(PrintModuleProduct)

  using namespace std;

void PrintModuleProduct::addProduct(TString product)
{
  if(find(m_products.begin(),m_products.end(),product) == m_products.end())m_products.push_back(product);
}

void PrintModuleProduct::addVariable(TString varname, int var)
{
  if(find(m_variables_int.begin(),m_variables_int.end(),varname) == m_variables_int.end())m_variables_int.push_back(varname);
}

void PrintModuleProduct::addVariable(TString varname, double var)
{
  if(find(m_variables_double.begin(),m_variables_double.end(),varname) == m_variables_double.end())m_variables_double.push_back(varname);
}

void PrintModuleProduct::addVariable(TString varname, TString var)
{
  if(find(m_variables_TString.begin(),m_variables_TString.end(),varname) == m_variables_TString.end())m_variables_TString.push_back(varname);
}

void PrintModuleProduct::addVariable(TString varname, bool var)
{
  if(find(m_variables_bool.begin(),m_variables_bool.end(),varname) == m_variables_bool.end())m_variables_bool.push_back(varname);
}

void PrintModuleProduct::print(BaseHandler* handler)
{
  int run = 0;
  int lumi = 0;
  long event = 0;

  bool runSet = handler->getVariable("RUN",run);
  bool lumiSet = handler->getVariable("LUMI",lumi);
  bool eventSet = handler->getVariable("EVENT",event);

  if(!runSet || !lumiSet || !eventSet){
    cerr<<"Missing run/lumi/event information, will not be set properly in this module"<<endl;
  }

  for(int i = 0; i < (int)m_products.size(); i++){
    vector<SignatureObject*> v = handler->getProduct(m_products[i]);
    for(int j = 0; j < (int)v.size(); j++){
      cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<" pT: "<<v[j]->Pt()<<" eta: "<<v[j]->Eta()<<" phi: "<<v[j]->Phi()<<" m: "<<v[j]->M();
      for(int k = 0; k < (int)m_variables_int.size(); k++){
	int val = 0;
	bool isSet = v[j]->getVariable(m_variables_int[k],val);
	cout<<" "<<m_variables_int[k]<<": ";
	if(isSet){
	  cout<<val;
	}else{
	  cout<<"-";
	}
      }
      for(int k = 0; k < (int)m_variables_double.size(); k++){
	double val = 0;
	bool isSet = v[j]->getVariable(m_variables_double[k],val);
	cout<<" "<<m_variables_double[k]<<": ";
	if(isSet){
	  cout<<val;
	}else{
	  cout<<"-";
	}
      }
      for(int k = 0; k < (int)m_variables_TString.size(); k++){
	TString val = "";
	bool isSet = v[j]->getVariable(m_variables_TString[k],val);
	cout<<" "<<m_variables_TString[k]<<": ";
	if(isSet){
	  cout<<val;
	}else{
	  cout<<"-";
	}
      }
      for(int k = 0; k < (int)m_variables_bool.size(); k++){
	bool val = false;
	bool isSet = v[j]->getVariable(m_variables_bool[k],val);
	cout<<" "<<m_variables_bool[k]<<": ";
	if(isSet){
	  cout<<val;
	}else{
	  cout<<"-";
	}
      }
      cout<<endl;
    }
  }
}
