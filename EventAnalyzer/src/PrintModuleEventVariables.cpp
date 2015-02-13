#include "RutgersIAF/EventAnalyzer/interface/PrintModuleEventVariables.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

ClassImp(PrintModuleEventVariables)

  using namespace std;

void PrintModuleEventVariables::addVariable(TString varname, int var)
{
  if(find(m_variables_int.begin(),m_variables_int.end(),varname) == m_variables_int.end())m_variables_int.push_back(varname);
}

void PrintModuleEventVariables::addVariable(TString varname, double var)
{
  if(find(m_variables_double.begin(),m_variables_double.end(),varname) == m_variables_double.end())m_variables_double.push_back(varname);
}

void PrintModuleEventVariables::addVariable(TString varname, TString var)
{
  if(find(m_variables_TString.begin(),m_variables_TString.end(),varname) == m_variables_TString.end())m_variables_TString.push_back(varname);
}

void PrintModuleEventVariables::addVariable(TString varname, bool var)
{
  if(find(m_variables_bool.begin(),m_variables_bool.end(),varname) == m_variables_bool.end())m_variables_bool.push_back(varname);
}

void PrintModuleEventVariables::print(BaseHandler* handler)
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

  cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event;
  for(int k = 0; k < (int)m_variables_int.size(); k++){
    int val = 0;
    bool isSet = handler->getVariable(m_variables_int[k],val);
    cout<<" "<<m_variables_int[k]<<"(i): ";
    if(isSet){
      cout<<val;
    }else{
      cout<<"-";
    }
  }
  for(int k = 0; k < (int)m_variables_double.size(); k++){
    double val = 0;
    bool isSet = handler->getVariable(m_variables_double[k],val);
    cout<<" "<<m_variables_double[k]<<"(d): ";
    if(isSet){
      cout<<val;
    }else{
          cout<<"-";
    }
  }
  for(int k = 0; k < (int)m_variables_TString.size(); k++){
    TString val = "";
    bool isSet = handler->getVariable(m_variables_TString[k],val);
    cout<<" "<<m_variables_TString[k]<<"(S): ";
    if(isSet){
      cout<<val;
    }else{
      cout<<"-";
    }
  }
  for(int k = 0; k < (int)m_variables_bool.size(); k++){
    bool val = false;
    bool isSet = handler->getVariable(m_variables_bool[k],val);
    cout<<" "<<m_variables_bool[k]<<"(b): ";
    if(isSet){
      cout<<val;
    }else{
      cout<<"-";
    }
  }
  cout<<endl;
}
