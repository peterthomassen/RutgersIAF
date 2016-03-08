#include "RutgersIAF/EventAnalyzer/interface/EventVariableLeptonLTChecker.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableLeptonLTChecker)

void EventVariableLeptonLTChecker::addProduct(TString pname) {
	if(find(m_productnames.begin(), m_productnames.end(), pname) == m_productnames.end()) {
		m_productnames.push_back(pname);
	}
}

bool EventVariableLeptonLTChecker::calculate(BaseHandler* handler) {

  bool isdebug=false;

  //debugging
  if(isdebug){
    std::cout<<std::endl;
    std::cout<<"-----------"<<std::endl;
    for(int i = 0; i < (int)m_productnames.size(); i++) {//loop over all product names added
      vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);// get all objects of a given product name
      for(int j = 0; j < (int)v.size(); j++){//loop over all objects of a given product name
	std::cout<<"m_productname: "<<m_productnames[i]<<"   pT: "<<v[j]->Pt()<<std::endl;
      }
    }
  }//end-debugging



  // Store Tight Leptons
  // (Partial) name of tight collection: m_tightname
  vector<double> PtVectorTight;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find(m_loosename) != std::string::npos ) continue;
    for(int j = 0; j < (int)v.size(); j++){
      PtVectorTight.push_back( v[j]->Pt() );
    }
  }


  // Store Loose Leptons
  // (Partial) name of loose collection: m_loosename
  vector<double> PtVectorLoose;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find(m_tightname) != std::string::npos ) continue;
    for(int j = 0; j < (int)v.size(); j++){
      PtVectorLoose.push_back( v[j]->Pt() );
    }
  }

  // Check if Loose Leptons are Tight
  vector<int> isLooseTightVector;
  for(auto it=begin(PtVectorLoose); it!=end(PtVectorLoose); ++it){
    int isMatched=0;
    if(std::find(PtVectorTight.begin(), PtVectorTight.end(), *it) != PtVectorTight.end()) isMatched=1;
    isLooseTightVector.push_back(isMatched);
  }


  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find(m_tightname) != std::string::npos ) continue;// only use loose lepton collection for the final tagging
    for(int j = 0; j < (int)v.size(); j++){
      v[j]->setVariable("IsTight", (int)(isLooseTightVector.at(j)));
    }
  }

  return true;

}
