#include "RutgersIAF/EventAnalyzer/interface/PrintModuleEverything.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include <vector>
#include <map>
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(PrintModuleEverything)

using namespace std;

void PrintModuleEverything::print(BaseHandler* handler)
{
  for(map<TString,double>::iterator iter = handler->m_variable_map_double.begin(); iter != handler->m_variable_map_double.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  for(map<TString,int>::iterator iter = handler->m_variable_map_int.begin(); iter != handler->m_variable_map_int.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  for(map<TString,long>::iterator iter = handler->m_variable_map_long.begin(); iter != handler->m_variable_map_long.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  for(map<TString,TString>::iterator iter = handler->m_variable_map_TString.begin(); iter != handler->m_variable_map_TString.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  for(map<TString,bool>::iterator iter = handler->m_variable_map_bool.begin(); iter != handler->m_variable_map_bool.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  std::map<TString,std::vector<SignatureObject*> >::iterator pIter;
  for(pIter = handler->m_products.begin(); pIter != handler->m_products.end(); pIter++){
    cout<<"product "<<(*pIter).first<<" "<<(*pIter).second.size()<<endl;
    vector<SignatureObject*> v = (*pIter).second;
    for(int i = 0; i < (int)v.size(); i++){
      cout<<"  "<<*v[i]<<endl;
    }
  }


}
