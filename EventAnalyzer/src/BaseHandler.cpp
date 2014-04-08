#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include <algorithm>
#include <TFile.h>
#include "TPRegexp.h"
#include <string>
#include <fstream>
#include "RutgersIAF2012/EventAnalyzer/interface/Signature.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureWithBjets.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH2F.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH3F.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_CountWeight.h"

#include <assert.h>

using namespace std;

ClassImp(BaseHandler)

BaseHandler::BaseHandler(TString ofname, BaseTreeReader* reader)
{
  m_doRunLumiCheck = false;
  m_doRunLumiCheckFromJSON = false;
  m_checkedRun = -1;
  m_checkedLumi = -1;
  m_isRunLumiGood = true;

  m_isMC = false;
  m_physicsWeight = 1.0;

  m_lastEntryPrepared = -1;
  m_currentEntry = -1;
  m_outFileName = ofname;
  m_outFile = new TFile(m_outFileName.Data(),"RECREATE");
  m_noCutSignature = new Signature("noCutSignature","");

  m_writer = 0;

  m_reader = reader;  
}


BaseHandler::~BaseHandler()
{
  delete m_noCutSignature;
}

//-----------------------------------------
int BaseHandler::getMode(std::string name) {
        std::map<std::string, int>::iterator it = m_mode.find(name);
        return (it != m_mode.end())
                ? it->second
                : 0;
}
//----------------------------------------
void BaseHandler::printSignature(Signature* sig)
{
  int run = 0, lumiBlock = 0;
  long event = 0;
  bool hasRun = m_reader->getVariable("RUN",run);
  bool hasLumi = m_reader->getVariable("LUMI",lumiBlock);
  bool hasEvent = m_reader->getVariable("EVENT",event);
  if(hasRun && hasLumi && hasEvent)
    cout<<sig->getName()<<" "<<run<<" "<<lumiBlock<<" "<<event<<endl;
}
//-----------------------------------------
Signature* BaseHandler::addSignature(const char* name, const char* option)
{
  Signature* sig = new Signature(name,option);
  sig->setHandler(this);
  addSignature(sig);
  return sig;
}

//-----------------------------------------
void BaseHandler::addPreCutSignature(const char* name, const char* option)
{
  Signature* sig = new Signature(name,option);
  addPreCutSignature(sig);
}
//-----------------------------------------
void BaseHandler::initSignatures()
{

  gDirectory->pwd();
  int nSig = (int)m_Signatures.size()+(int)m_preHandlerCutSignatures.size()+(int)m_bjetSignatures.size();
  m_signatureCorrelationHisto = new TH2F("signatureCorrelationHisto","",nSig,-0.5,(float)nSig-0.5,nSig,-0.5,(float)nSig-0.5);

  addHistogram(new SignatureTH1F_CountWeight("COUNT"));

  m_noCutSignature->init();
  unsigned int s = 0,u=0;
  for(s = 0; s < m_Signatures.size(); s++){
    m_signatureCorrelationHisto->GetXaxis()->SetBinLabel(s+1,m_Signatures[s]->getName());
    m_signatureCorrelationHisto->GetYaxis()->SetBinLabel(s+1,m_Signatures[s]->getName());
    m_Signatures[s]->init();
    m_Signatures[s]->setHandler(this);

  }
  for(u = 0; u < m_bjetSignatures.size(); u++){
    m_signatureCorrelationHisto->GetXaxis()->SetBinLabel(s+u+1,m_bjetSignatures[u]->getName());
    m_signatureCorrelationHisto->GetYaxis()->SetBinLabel(s+u+1,m_bjetSignatures[u]->getName());
    m_bjetSignatures[u]->init();
    m_bjetSignatures[s]->setHandler(this);
  }
  for(unsigned int t = 0; t < m_preHandlerCutSignatures.size(); t++){
    m_signatureCorrelationHisto->GetXaxis()->SetBinLabel(s+u+t+1,m_preHandlerCutSignatures[t]->getName());
    m_signatureCorrelationHisto->GetYaxis()->SetBinLabel(s+u+t+1,m_preHandlerCutSignatures[t]->getName());
    m_preHandlerCutSignatures[t]->init();
    m_preHandlerCutSignatures[s]->setHandler(this);
  }
  m_noCutSignature->setHandler(this);

}

//-----------------------------------------
void BaseHandler::finishSignatures()
{

  m_outFile->cd();
  m_signatureCorrelationHisto->Write();
  m_noCutSignature->finish();
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    m_Signatures[s]->finish();
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    m_preHandlerCutSignatures[s]->finish();
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    m_bjetSignatures[s]->finish();
  }
  if(m_writer)m_writer->finish();
  m_outFile->Close();
}

//-----------------------------------------
void BaseHandler::eventLoop()
{
        eventLoop(-1, 0);
}
void BaseHandler::eventLoop(int onlyRun, long int onlyEvent)
{
  int nevents = m_reader->GetEntries();
  int nEntryLow = getMode("nEntryLow");
  int nEntryHigh = getMode("nEntryHigh");
  if(nEntryHigh == 0 || nEntryHigh > nevents) nEntryHigh = nevents;
  
  for(m_currentEntry = nEntryLow; m_currentEntry < nEntryHigh; m_currentEntry++){

    m_reader->GetEntry(m_currentEntry);
    if (m_currentEntry % 100000 == 0)cout<<"Processing event "<<m_currentEntry<<" of "<<nevents<<endl;

    int run = 0, lumiBlock = 0;
    long event = 0;
    bool hasRun = m_reader->getVariable("RUN",run);
    bool hasLumi = m_reader->getVariable("LUMI",lumiBlock);
    bool hasEvent = m_reader->getVariable("EVENT",event);

    if(!hasRun || !hasLumi || !hasEvent)continue;

    if(onlyRun >= 0 && (run != onlyRun || event != onlyEvent)) continue;
    

    if(m_dumpList.find(run) != m_dumpList.end() && m_dumpList[run].find(lumiBlock) != m_dumpList[run].end() && find(m_dumpList[run][lumiBlock].begin(),m_dumpList[run][lumiBlock].end(),event) != m_dumpList[run][lumiBlock].end())dumpEventInfo();
    if(m_doRunLumiCheck || m_doRunLumiCheckFromJSON){
      if(run != m_checkedRun || lumiBlock != m_checkedLumi){
        m_isRunLumiGood = ((m_doRunLumiCheck && checkRunLumi(run,lumiBlock)) || (m_doRunLumiCheckFromJSON && checkRunLumiFromJSON(run,lumiBlock)));
        m_checkedRun = run;
        m_checkedLumi = lumiBlock;
        
                if(!m_isRunLumiGood) {
                        if(getDebugMode()) std::cout << "JSON: Decided against running over run " << run << ", ls " << lumiBlock << std::endl;
                } else {
                        if(getDebugMode()) std::cout << "JSON: Will run over run " << run << ", ls " << lumiBlock << std::endl;
                }
      }
      if(!m_isRunLumiGood) {
                  continue;
          }
    }

    prepareEvent();
    analyzeEvent();

  }//End of event loop
}

//-----------------------------------------
void BaseHandler::addHistogram(SignatureTH1F* h) {
        addHistogram(h, "");
}
//-----------------------------------------
void BaseHandler::addHistogram(SignatureTH2F* h) {
        addHistogram(h, "");
}
//-----------------------------------------
void BaseHandler::addHistogram(SignatureTH3F* h) {
        addHistogram(h, "");
}
//-----------------------------------------
void BaseHandler::addHistogram(SignatureTH1F* h, TString signatureRegExp) {
  TString nname = m_noCutSignature->GetName();
  nname += "_";
  nname += h->GetName();
  SignatureTH1F* nh = (SignatureTH1F*)h->Clone(nname.Data());
  m_noCutSignature->addHistogram(nh);
  
  TPMERegexp re(signatureRegExp);
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    nname = m_Signatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH1F* nh2 = (SignatureTH1F*)h->Clone(nname.Data());
    m_Signatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    nname = m_preHandlerCutSignatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH1F* nh2 = (SignatureTH1F*)h->Clone(nname.Data());
    m_preHandlerCutSignatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    nname = m_bjetSignatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH1F* nh2 = (SignatureTH1F*)h->Clone(nname.Data());
    m_bjetSignatures[s]->addHistogram(nh2);
  }
}
//-----------------------------------------
void BaseHandler::addHistogram(SignatureTH2F* h, TString signatureRegExp) {
  TString nname = m_noCutSignature->GetName();
  nname += "_";
  nname += h->GetName();
  SignatureTH2F* nh = (SignatureTH2F*)h->Clone(nname.Data());
  m_noCutSignature->addHistogram(nh);
  
  TPMERegexp re(signatureRegExp);
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    nname = m_Signatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH2F* nh2 = (SignatureTH2F*)h->Clone(nname.Data());
    m_Signatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    nname = m_preHandlerCutSignatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH2F* nh2 = (SignatureTH2F*)h->Clone(nname.Data());
    m_preHandlerCutSignatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    nname = m_bjetSignatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH2F* nh2 = (SignatureTH2F*)h->Clone(nname.Data());
    m_bjetSignatures[s]->addHistogram(nh2);
  }
}
//-----------------------------------------
void BaseHandler::addHistogram(SignatureTH3F* h, TString signatureRegExp) {
  TString nname = m_noCutSignature->GetName();
  nname += "_";
  nname += h->GetName();
  SignatureTH3F* nh = (SignatureTH3F*)h->Clone(nname.Data());
  m_noCutSignature->addHistogram(nh);
  
  TPMERegexp re(signatureRegExp);
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    nname = m_Signatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH3F* nh2 = (SignatureTH3F*)h->Clone(nname.Data());
    m_Signatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    nname = m_preHandlerCutSignatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH3F* nh2 = (SignatureTH3F*)h->Clone(nname.Data());
    m_preHandlerCutSignatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    nname = m_bjetSignatures[s]->GetName();
    if(!re.Match(nname)) {
                continue;
        }
    nname += "_";
    nname += h->GetName();
    SignatureTH3F* nh2 = (SignatureTH3F*)h->Clone(nname.Data());
    m_bjetSignatures[s]->addHistogram(nh2);
  }
}
bool BaseHandler::applyHandlerCuts()
{
  for(int i = 0; i < (int)m_handlerCuts.size(); i++){
    bool passed = false;
    bool isset = getVariable(m_handlerCuts[i],passed);
    if(getDebugMode()) cout<<"handler "<<m_handlerCuts[i]<<" "<<isset<<" "<<passed<<endl;
    if(!isset || !passed){
      return false;
    }
  }
  return true;
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::addProduct(TString productName,TString productSource)
{
  if(find(m_product_names.begin(),m_product_names.end(),productName) != m_product_names.end()){
    cerr<<"Product with name "<<productName<<" is already in list, skipping"<<endl;
    return;
  }
  m_product_names.push_back(productName);
  m_product_sources[productName] = productSource;
  vector<SignatureObject*> a;
  m_products[productName] = a;
  vector<TString> b;
  m_product_cuts[productName] = b;
}
//-----------------------------------------
void BaseHandler::addProductCut(TString productName, TString cut)
{
  if(m_product_cuts.find(productName) == m_product_cuts.end()){
    cerr<<"Product "<<productName<<" not found"<<endl;
    return;
  }
  m_product_cuts[productName].push_back(cut);
}
//-----------------------------------------
//-----------------------------------------
vector<SignatureObject*> BaseHandler::getProduct(TString productName)
{
  //if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  vector<SignatureObject*> retvec;
  map<TString,vector<SignatureObject*> >::const_iterator pIter = m_products.find(productName);
  if(pIter == m_products.end()){
    cerr<<"Product "<<productName<<" not found"<<endl;
    return retvec;
  }

  retvec = (*pIter).second;
  return retvec;
}
//-----------------------------------------
bool BaseHandler::isProductPresent(TString prodName)
{
  if(m_products.find(prodName) == m_products.end())return false;
  return true;
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::createProducts()
{

  //calculate all of the variables and cuts
  map<TString,vector<SignatureObject*> >::iterator iIter;
  for(iIter = m_products.begin(); iIter != m_products.end(); iIter++){
    TString sname = (*iIter).first;
    vector<SignatureObject*> product = (*iIter).second;
    for(int j = 0; j < (int)product.size(); j++){
      SignatureObject* object = product[j];
      for(int k = 0; k < (int)m_object_variable_list.size(); k++){
	TString varname = m_object_variable_list[k];
	m_object_variables[varname]->calculate(object);
      }
    }
  }

  for(int i = 0; i < (int)m_product_names.size(); i++){
    TString pname = m_product_names[i];
    TString sname = m_product_sources[pname];
    vector<SignatureObject*> source;
    vector<SignatureObject*> product;

    map<TString,vector<SignatureObject*> >::const_iterator pIter = m_products.find(sname);
    if(pIter != m_products.end()){
      source = (*pIter).second;
    }else{
      cerr<<"Warning attempt to make product "<<pname<<" from non-existent source "<<sname<<endl;
      continue;
    }

    //////////////////////////////////////////////////////
    //First apply cuts on source to create base products//
    //////////////////////////////////////////////////////
    //cout<<pname<<" "<<sname<<" "<<source.size()<<endl;

    for(int k = 0; k < (int)source.size(); k++){
      int passed = 1;
      vector<TString> cutnames;
      if(m_product_cuts.find(pname) != m_product_cuts.end()){
	cutnames = m_product_cuts[pname];
      }
      for(int icut = 0; icut < (int)cutnames.size() && passed == 1; icut++){
	bool check = false;
	bool isset = source[k]->getVariable(cutnames[icut],check);
	if(!isset || !check)passed = 0;
      }
      if(passed == 1)product.push_back(source[k]);
    }
    m_products[pname] = product;

    ///////////////////////////////////////////////////////
    ////////////////apply self separation//////////////////
    ///////////////////////////////////////////////////////
    map<TString,std::pair<ObjectComparison*,bool> >::const_iterator findSelf = m_product_selfcomparisons.find(pname);
    if(findSelf != m_product_selfcomparisons.end()){
      vector<SignatureObject*> i_product = m_products[pname];
      vector<SignatureObject*> f_product;
      ObjectComparison* comparison = (*findSelf).second.first;
      bool doAnd = (*findSelf).second.second;
      for(int k = 0; k < (int)i_product.size(); k++){
	  bool passed = doAnd;
	  for(int j = 0; j < k && passed != doAnd; j++){
	    bool pass = comparison->passCut(i_product[k],i_product[j]);
	    if(doAnd) passed = pass && passed;
	    else passed = pass || passed;
	  }
	  if(passed)f_product.push_back(i_product[k]);
      }
      m_products[pname] = f_product;
      i_product.clear();
      f_product.clear();
    }

    ///////////////////////////////////////////////////////
    //////////apply separation to other objects////////////
    ///////////////////////////////////////////////////////

    map<TString, map<TString,pair<ObjectComparison*,bool> > >::iterator pcIter = m_product_comparisons.find(pname);
    if(pcIter != m_product_comparisons.end()){
      map<TString,pair<ObjectComparison*,bool> > pcMap = (*pcIter).second;
      map<TString,pair<ObjectComparison*,bool> >::iterator sIter;
      for(sIter = pcMap.begin(); sIter != pcMap.end(); sIter++){
	TString cname = (*sIter).first;
	ObjectComparison* comparison = (*sIter).second.first;
	bool doAnd = (*sIter).second.second;
	vector<SignatureObject*> i_product = m_products[pname];
	vector<SignatureObject*> comp_product = getProduct(cname);
	vector<SignatureObject*> f_product;
	for(int j = 0; j < (int)i_product.size(); j++){
	  bool passed = doAnd;
	  for(int k = 0; k < (int)comp_product.size() && passed == doAnd; k++){
	    bool pass = comparison->passCut(i_product[j],comp_product[k]);
	    if(doAnd) passed = pass && passed;
	    else passed = pass || passed;
	  }
	  if(passed)f_product.push_back(i_product[j]);
	}
	i_product.clear();
	m_products[pname] = f_product;
	f_product.clear();
      }
    }
  }
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::resetProducts()
{
  for(int i = 0; i < (int)m_product_names.size(); i++){
    m_products[m_product_names[i]].clear();
  }
}
//-----------------------------------------
void BaseHandler::calcPhysicsWeight()
{
	m_physicsWeight = 1.0;
	if(getMode("debugPhysicsWeights")) {
		cout << "Weights:";
	}
	for(int i = 0; i < (int)m_weight_variables.size(); i++){
		TString weightname = m_weight_variables[i];
		double weight;
		bool success = getVariable(weightname, weight);
		assert(success);
		m_physicsWeight *= weight;
		if(getMode("debugPhysicsWeights")) {
			cout << " " << weightname << "=" << weight;
		}
	}
	if(getMode("debugPhysicsWeights")) {
		cout << "\n";
	}
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::prepareEvent()
{

  if(m_currentEntry == m_lastEntryPrepared)return;
  resetProducts();
  resetVariables();

  m_products = m_reader->getProducts();

  m_variable_map_double = m_reader->m_variable_mapdouble;
  m_variable_map_int = m_reader->m_variable_mapint;
  m_variable_map_long = m_reader->m_variable_maplong;
  m_variable_map_TString = m_reader->m_variable_mapTString;
  m_variable_map_bool = m_reader->m_variable_mapbool;

  createProducts();

  calculateVariables();

  m_lastEntryPrepared = m_currentEntry;

  calcPhysicsWeight();

  return;
}
//------------------------------------------
//------------------------------------------
//------------------------------------------
//------------------------------------------
//------------------------------------------
void BaseHandler::addDumpEvent(int run, int lumi, long event)
{
  if(m_dumpList.find(run) == m_dumpList.end()){
    map<int,vector<long> > amap;
    m_dumpList[run] = amap;
  }
  if(m_dumpList[run].find(lumi) == m_dumpList[run].end()){
    vector<long> avec;
    m_dumpList[run][lumi] = avec;
  }
  m_dumpList[run][lumi].push_back(event);
}
//-----------------------------------------
//-----------------------------------------
bool BaseHandler::passCut(TString cutName)
{
  bool check = false;
  bool isset = getVariable(cutName,check);
  if(!isset)return false;
  return check;
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::dumpEventInfo()
{

}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::calculateVariables()
{

  map<TString,EventVariable*>::iterator iter;
  for(int i = 0; i < (int)m_event_variable_list.size(); i++){
    iter = m_variable_map.find(m_event_variable_list[i]);
    if(iter == m_variable_map.end())continue;
    EventVariable* variable = (*iter).second;
    variable->calculate(this);
  }
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::resetVariables()
{
  m_variable_map_double.clear();
  m_variable_map_int.clear();
  m_variable_map_long.clear();
  m_variable_map_bool.clear();
  m_variable_map_TString.clear();
}
//-----------------------------------------
//-----------------------------------------
//---------------------------------------

void BaseHandler::readGoodRunLumi(TString c)
{
  
  ifstream infile(c.Data());
  
  int rrr,lll;
  
  while(1){
    infile >> rrr >> lll;
    if(!infile.good())break;
    if(m_goodRunLumi.find(rrr) == m_goodRunLumi.end()){
      vector<int> lvec;
      m_goodRunLumi[rrr] = lvec;
    }
    
    if(find(m_goodRunLumi[rrr].begin(),m_goodRunLumi[rrr].end(),lll) == m_goodRunLumi[rrr].end())m_goodRunLumi[rrr].push_back(lll);
  }
  
  if(m_goodRunLumi.size() > 0)m_doRunLumiCheck = true;
  
}

//-------------------------------------
bool BaseHandler::checkRunLumi(int r, int l)
{
  if(m_goodRunLumi.find(r) == m_goodRunLumi.end())return false;
  if(find(m_goodRunLumi[r].begin(),m_goodRunLumi[r].end(),l) == m_goodRunLumi[r].end())return false;
  return true;

}
//-----------------------------------------
//-----------------------------------------
//--------------------------------------

void BaseHandler::readGoodRunLumiFromJSON(TString JSONFile, bool debug)
{
  ifstream inputfile;
  inputfile.open(JSONFile);

  bool beginJson = false;
  bool beginRun = false;
  bool beginLumiSet = false;
  bool beginLumiRange = false;
  
  bool firstLumiNumberEnd = false;
  bool secondLumiNumberEnd = false;
  
  Int_t Run = -999;

  std::pair<Int_t, Int_t> LumiRange;
  LumiRange.first = -999;
  LumiRange.second = -999;
  std::vector<std::pair<Int_t, Int_t> > Lumis;

  if (!inputfile.is_open()) {
    std::cout << "The JSON file you are using does not exist!!!" << std::endl;
    std::cout << "JSON File: " << JSONFile << std::endl;
  }else {
    std::cout << "The JSON file you are using is: " << JSONFile << std::endl;

    while (!inputfile.eof()) {
      char c = inputfile.get();
      char p = inputfile.peek();

      // Find beginning of JSON file
      if (c == '{' && beginJson == false && beginRun == false && beginLumiSet ==false && beginLumiRange == false) {
	beginJson = true;
	if (debug == true) {
	  std::cout << "Found beginning of JSON file: " << c << std::endl;
	}
      }

      // Find beginning of Run and fill it
      if (c == '"' && beginJson == true && beginRun == false && beginLumiSet == false && beginLumiRange == false) {
	beginRun = true;

	inputfile >> Run;
	if (debug == true) {
	  std::cout << "Found beginning of Run: " << c << Run << std::endl;
	}
      }

      // Find ending of Run
      if (c == ':' && beginJson == true && beginRun == true && beginLumiSet == false && beginLumiRange == false) {
	beginRun = false;
	if (debug == true) {
	  std::cout << "Found ending of Run: " << c << std::endl;
	}
      }

      // Find beginning of Lumi Set
      if (c == '[' && beginJson == true && beginRun == false && beginLumiSet == false && beginLumiRange == false) {
	beginLumiSet = true;
	if (debug == true) {
	  std::cout << "Found beginning of LumiSet: " << c << std::endl;
	}
      }

      // Find begining of Lumi Range and fill it
      if (p == '[' && beginJson == true && beginRun == false && beginLumiSet == true && beginLumiRange == false) {
	beginLumiRange = true;
	c = inputfile.get();
	inputfile >> LumiRange.first;
	LumiRange.second = -999; // Set to -999 in the case that a second value does not exist for the pair
	if (debug == true) {
	  std::cout << "Found beginning of LumiRange: " << c << LumiRange.first << std::endl;
	}
      }

      // Find middle of Lumi Range and fill it
      if (c == ',' && beginJson == true && beginRun == false && beginLumiSet == true && beginLumiRange == true && firstLumiNumberEnd == false && secondLumiNumberEnd == false) {
	firstLumiNumberEnd = true;

	inputfile >> LumiRange.second;

	secondLumiNumberEnd = true;
      }

      // Find ending of Lumi Range
      if (c == ']' && beginJson == true && beginRun == false && beginLumiSet == true && beginLumiRange == true) {
	beginLumiRange = false;
	if (debug == true) {
	  std::cout << "Found ending of LumiRange: " << c << std::endl;
	}

	firstLumiNumberEnd = false;
	secondLumiNumberEnd = false;
	Lumis.push_back(LumiRange);
      }

      // Find ending of Lumi Set
      if (p == ']' && beginJson == true && beginRun == false && beginLumiSet == true && beginLumiRange == false) {
	beginLumiSet = false;
	if (debug == true) {
	  std::cout << "Found ending of LumiSet: " << c << std::endl;
	}
      }

      // Initialize json multimap
      if (p == ']' && beginJson == true && beginRun == false && beginLumiSet == false && beginLumiRange == false) {
	m_json.insert(std::pair<Int_t, std::vector<std::pair<Int_t, Int_t> > >(Run, Lumis));
	Run = -999;
	LumiRange.first = -999;
	LumiRange.second = -999;
	Lumis.clear();
      }

      // Find ending of JSON file
      if (c == '}' && beginJson == true && beginRun == false && beginLumiSet == false && beginLumiRange == false) {
	beginJson = false;
	if (debug == true) {
	  std::cout << "Found ending of JSON file: " << c << std::endl;
	}
      }
    }
  }

  inputfile.close();

  if (m_json.size() > 0) {
    m_doRunLumiCheckFromJSON = true;
  }
}
//--------------------------------------
void BaseHandler::printRunLumiJSON()
{
  std::multimap<Int_t, std::vector<std::pair<Int_t, Int_t> > >::iterator store_iter;

  std::cout << "The Run and Lumi numbers stored in memory were: " << std::endl;

  std::cout << "{";

  for (std::multimap<Int_t, std::vector<std::pair<Int_t, Int_t> > >::iterator json_iter = m_json.begin(); json_iter != m_json.end(); json_iter++) {
    store_iter = json_iter;
    std::cout << "\"" << json_iter->first << "\": [";
    for (std::vector<std::pair<Int_t, Int_t> >::const_iterator lumi_iter = (json_iter->second).begin(); lumi_iter != (json_iter->second).end(); lumi_iter++) {

      // First Run of Json file and Run has only one Lumi Range
      if (json_iter == m_json.begin() && std::distance((json_iter->second).begin(),(json_iter->second).end()) == 1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]], ";
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "]], ";
	}
      }

      // First Run of Json file and all Lumi Ranges, except last one, of Run and Run has more than one Lumi Range
      if (json_iter == m_json.begin() && std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && lumi_iter != (json_iter->second).end()-1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "], ";
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "], ";
	}
      }

      // First Run of Json file and last Lumi Range of Run and Run has more than one Lumi Range
      if (json_iter == m_json.begin() && std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && lumi_iter == (json_iter->second).end()-1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]], ";
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "]]";
	}
      }

      // Middle Runs of Json file and if Run has only one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter != m_json.end() && std::distance((json_iter->second).begin(),(json_iter->second).end()) == 1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]], ";
	  store_iter = json_iter;
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "]], ";
	  store_iter = json_iter;
	}
      }else {
	store_iter = json_iter;
      }
      // Middle Runs of Json file and all Lumi Ranges, except last one, of Runs and if Runs have more than one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter != m_json.end() && std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && lumi_iter != (json_iter->second).end()-1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "], ";
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "], ";
	}
      }else {
	store_iter = json_iter;
      }

      // Middle Runs of Json file and last Lumi Range of Runs and Runs have more than one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter != m_json.end() && std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && lumi_iter == (json_iter->second).end()-1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]], ";
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "], ";
	}
      }else {
	store_iter = json_iter;
      }

      // Last Run of Json file and Run has only one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter == m_json.end() && std::distance((json_iter->second).begin(),(json_iter->second).end()) == 1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]]";
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "]]";
	}
      }else {
	store_iter = json_iter;
      }

      // Last Run of Json file and all Lumi Ranges, except last one, of Run and Run has more than one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter == m_json.end() && std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && lumi_iter != (json_iter->second).end()-1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "], ";
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "]], ";
	}
      }else {
	store_iter = json_iter;
      }

      // Last Run of Json file and last Lumi Range of Run and Run has more than one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter == m_json.end() && std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && lumi_iter == (json_iter->second).end()-1) {
	if (lumi_iter->second != -999) {
	  std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]]";
	}else if (lumi_iter->second == -999) {
	  std::cout << "[" << lumi_iter->first << "]], ";
	}
      }else {
	store_iter = json_iter;
      }
    }
  }
  std::cout << "}" << std::endl;
}

//--------------------------------------
bool BaseHandler::checkRunLumiFromJSON(int RunNumber, int LumiNumber, bool debug)
{
  bool foundRun = false;
  bool foundLumi = false;

  if( m_json.size()==0 )
    {
      return true; //If you didn't specify a JSON file, then just pass everything
    }
  
  std::multimap<int, std::vector<std::pair<int, int> > >::iterator json_iter = m_json.find(RunNumber);
  
  if (debug == true) {
    std::cout << "Run: " << RunNumber << " Lumi: " << LumiNumber << std::endl;
  }
  
  // Check whether Run number is found in JSON file
  if (json_iter != m_json.end()) {
    foundRun = true;
  }
  
  // Check whether Lumi number is found in the list of Lumis for the given Run number in the JSON file
  if (foundRun == true) {
    std::vector<std::pair<int, int> > lumis = json_iter->second;
    
    for (std::vector<std::pair<int, int> >::iterator lumis_iter = lumis.begin();
         lumis_iter != lumis.end(); ++lumis_iter) {
      
      if (debug == true) {
        if (lumis_iter->second != -999) {
          std::cout << "Lumi: [" << lumis_iter->first << ", " << lumis_iter->second << "]" << std::endl;
        }
        
        else if (lumis_iter->second == -999){
          std::cout << "Lumi: [" << lumis_iter->first << "]" << std::endl;
        }
      }
      
      if (LumiNumber >= lumis_iter->first && LumiNumber <= lumis_iter->second) {
        if (debug == true) {
          std::cout << "Run: " << RunNumber << " and Lumi: " << LumiNumber << " was found!" << std::endl;
        }
        
        foundLumi = true;
      }
      
      else if (LumiNumber == lumis_iter->first && lumis_iter->second == -999) {
        if (debug == true) {
          std::cout << "Run: " << RunNumber << " and Lumi: " << LumiNumber << " was found!" << std::endl;
        }
        
        foundLumi = true;
      }
      
      else {
        continue;
      }
    }
  }
  
  else {
    if (debug == true) {
      std::cout << "Did not find Run: " << RunNumber << " and Lumi: " << LumiNumber << std::endl;
    }
  }

  return (foundRun && foundLumi);
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::addProductComparison(TString pname1,TString pname2, ObjectComparison* comparison, bool requireAnd)
{
  map<TString,map<TString,pair<ObjectComparison*,bool> > >::const_iterator iter1 = m_product_comparisons.find(pname1);
  if(iter1 == m_product_comparisons.end()){
    map<TString,pair<ObjectComparison*,bool> > nmap;
    nmap[pname2] = make_pair(comparison,requireAnd);
    m_product_comparisons[pname1] = nmap;
  }else{
    pair<ObjectComparison*,bool> np = pair<ObjectComparison*,bool>(comparison,requireAnd);
    m_product_comparisons[pname1].insert(map<TString,pair<ObjectComparison*,bool> >::value_type(pname2,np));
  }
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::addProductSelfComparison(TString pname, ObjectComparison* comparison, bool requireAnd)
{
  m_product_selfcomparisons[pname] = make_pair(comparison,requireAnd);
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::addHandlerCut(TString cutname)
{
  m_handlerCuts.push_back(cutname);
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::addEventVariable(TString varname, EventVariable* var, bool rename)
{
  map<TString,EventVariable*>::iterator iter = m_variable_map.find(varname);
  if(iter == m_variable_map.end()){
    m_event_variable_list.push_back(varname);
  }else{
    cerr << "WARNING: Replacing variable with name "<<varname<<endl;
  }
  if(rename)var->setName(varname);
  m_variable_map[varname] = var;
}
//-----------------------------------------
//-----------------------------------------
EventVariable* BaseHandler::getEventVariable(TString varname)
{
  map<TString,EventVariable*>::iterator iter = m_variable_map.find(varname);
  if(iter != m_variable_map.end()){
    return (*iter).second;
  }
  return 0;
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::addWeightVariable(TString varname)
{
  vector<TString>::iterator iter = find(m_weight_variables.begin(),m_weight_variables.end(),varname);
  if(iter != m_weight_variables.end()){
    cerr<<"WARNING: weight variable with name: "<<varname<<" is already in list!"<<endl;
  }
  m_weight_variables.push_back(varname);
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::setVariable(TString varname, double c)
{
  map<TString,double>::iterator iter = m_variable_map_double.find(varname);
  if(iter != m_variable_map_double.end()){
    cerr << "WARNING: resetting variable with name: "<<varname<<" from "<<(*iter).second<<" to "<<c<<endl;
  }
  m_variable_map_double[varname] = c;
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::setVariable(TString varname, int c)
{
  map<TString,int>::iterator iter = m_variable_map_int.find(varname);
  if(iter != m_variable_map_int.end()){
    cerr << "WARNING: resetting variable with name: "<<varname<<" from "<<(*iter).second<<" to "<<c<<endl;
  }
  m_variable_map_int[varname] = c;
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::setVariable(TString varname, long c)
{
  map<TString,long>::iterator iter = m_variable_map_long.find(varname);
  if(iter != m_variable_map_long.end()){
    cerr << "WARNING: resetting variable with name: "<<varname<<" from "<<(*iter).second<<" to "<<c<<endl;
  }
  m_variable_map_long[varname] = c;
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::setVariable(TString varname, TString c)
{
  map<TString,TString>::iterator iter = m_variable_map_TString.find(varname);
  if(iter != m_variable_map_TString.end()){
    cerr << "WARNING: resetting variable with name: "<<varname<<" from "<<(*iter).second<<" to "<<c<<endl;
  }
  m_variable_map_TString[varname] = c;
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::setVariable(TString varname, bool c)
{
  map<TString,bool>::iterator iter = m_variable_map_bool.find(varname);
  if(iter != m_variable_map_bool.end()){
    cerr << "WARNING: resetting variable with name: "<<varname<<" from "<<(*iter).second<<" to "<<c<<endl;
  }
  m_variable_map_bool[varname] = c;
}
//-----------------------------------------
//-----------------------------------------
bool BaseHandler::getVariable(TString varname, double& c)
{
  map<TString,double>::iterator iter = m_variable_map_double.find(varname);
  if(iter == m_variable_map_double.end()){
    c = 0;
    return false;
  }else{
    c = (*iter).second;
    return true;
  }
}
//-----------------------------------------
//-----------------------------------------
bool BaseHandler::getVariable(TString varname, int& c)
{
  map<TString,int>::iterator iter = m_variable_map_int.find(varname);
  if(iter == m_variable_map_int.end()){
    c = 0;
    return false;
  }else{
    c = (*iter).second;
    return true;
  }
}
//-----------------------------------------
//-----------------------------------------
bool BaseHandler::getVariable(TString varname, long& c)
{
  map<TString,long>::iterator iter = m_variable_map_long.find(varname);
  if(iter == m_variable_map_long.end()){
    c = 0;
    return false;
  }else{
    c = (*iter).second;
    return true;
  }
}
//-----------------------------------------
//-----------------------------------------
bool BaseHandler::getVariable(TString varname, TString& c)
{
  map<TString,TString>::iterator iter = m_variable_map_TString.find(varname);
  if(iter == m_variable_map_TString.end()){
    c = "";
    return false;
  }else{
    c = (*iter).second;
    return true;
  }
}
//-----------------------------------------
//-----------------------------------------
bool BaseHandler::getVariable(TString varname, bool& c)
{
  map<TString,bool>::iterator iter = m_variable_map_bool.find(varname);
  if(iter == m_variable_map_bool.end()){
    c = false;
    return false;
  }else{
    c = (*iter).second;
    return true;
  }
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::addObjectVariable(TString varname, ObjectVariable* objvar,bool rename)
{
  map<TString,ObjectVariable*>::iterator iter = m_object_variables.find(varname);
  if(iter == m_object_variables.end()){
    m_object_variable_list.push_back(varname);
  }else{
    cerr<<"WARNING: setting ObjectVariable with name "<<varname<<" to new value"<<endl;
  }
  if(rename)objvar->setName(varname);
  m_object_variables[varname] = objvar;
}
//-----------------------------------------
//-----------------------------------------
ObjectVariable* BaseHandler::getObjectVariable(TString varname)
{
  map<TString,ObjectVariable*>::iterator iter = m_object_variables.find(varname);
  if(iter == m_object_variables.end()){
    return 0;
  }else{
    return (*iter).second;
  }
}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::analyzeEvent()
{

    ////////////////////////////////////////////////////////////////
    //Get all Physics objects and calculate all Physics quantities//
    ////////////////////////////////////////////////////////////////

    m_noCutSignature->fillHistograms();

    if(m_debugMode)printDebugInfo();

    unsigned int nSig = m_Signatures.size();
    unsigned int nBjetSig = m_bjetSignatures.size();
    unsigned int nPreSig = m_preHandlerCutSignatures.size();
    vector<int> isSigVec(nSig + nBjetSig + nPreSig,0);
    for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
      if(m_preHandlerCutSignatures[s]->isSignature()){
        printSignature(m_preHandlerCutSignatures[s]);
        m_preHandlerCutSignatures[s]->fillHistograms();
        isSigVec[s+nSig+nBjetSig]=1;
	setVariable(m_preHandlerCutSignatures[s]->getName(),true);
      }
    }
    ////////////////////////////
    //Check handler level cuts//
    ////////////////////////////
    if(applyHandlerCuts()){


    ////////////////////////////////////////////////////////////
    //Check if it is part of the signature and fill histograms//
    ////////////////////////////////////////////////////////////
      for(unsigned int s = 0; s < m_Signatures.size(); s++){
        if(m_Signatures[s]->isSignature()){
          printSignature(m_Signatures[s]);
          m_Signatures[s]->fillHistograms();
          isSigVec[s]=1;
	  setVariable(m_Signatures[s]->getName(),true);
          if(m_doPriorityList)break;
        }
      }
      double baseweight = m_physicsWeight;
      for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
        if(m_bjetSignatures[s]->isSignature()){
	  setVariable(m_bjetSignatures[s]->getName(),true);
          if(m_bTagged >= m_bjetSignatures[s]->getLow() && m_bTagged <= m_bjetSignatures[s]->getHigh()){
            printSignature(m_bjetSignatures[s]);
            isSigVec[s + nSig] = 1;
            if(!m_isMC)m_bjetSignatures[s]->fillHistograms();
          }
          if(m_isMC){
            double bweight = 0.0;
            for(int b = m_bjetSignatures[s]->getLow(); b <= m_bjetSignatures[s]->getHigh() && b < 3; b++){
              bweight += m_btagWeights[b];
            }
            m_physicsWeight = baseweight * bweight;

            if(m_physicsWeight != 0.0)m_bjetSignatures[s]->fillHistograms();
          }
        }

      }
      m_physicsWeight = baseweight;
    }
    ////////////////////////////////////
    //Check correlations of signatures//
    ////////////////////////////////////
    for(unsigned int s = 0; s < isSigVec.size(); s++){
      if(isSigVec[s]){
        m_signatureCorrelationHisto->Fill(s,s);
      }
      //dumpEventInfo();
      for(unsigned int t = s+1; t < isSigVec.size();t++){
        if(isSigVec[s] && isSigVec[t]){
          m_signatureCorrelationHisto->Fill(s,t);
          m_signatureCorrelationHisto->Fill(t,s);
        }
      }
    }
    bool saveEvent = false;
    bool isSet = getVariable("WRITEEVENT",saveEvent);
    if(m_writer && isSet && saveEvent)m_writer->fillTree();

}
//-----------------------------------------
//-----------------------------------------
void BaseHandler::printDebugInfo()
{
  for(map<TString,double>::iterator iter = m_variable_map_double.begin(); iter != m_variable_map_double.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  for(map<TString,int>::iterator iter = m_variable_map_int.begin(); iter != m_variable_map_int.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  for(map<TString,long>::iterator iter = m_variable_map_long.begin(); iter != m_variable_map_long.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  for(map<TString,TString>::iterator iter = m_variable_map_TString.begin(); iter != m_variable_map_TString.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  for(map<TString,bool>::iterator iter = m_variable_map_bool.begin(); iter != m_variable_map_bool.end();iter++){
    cout<<(*iter).first<<" "<<(*iter).second<<endl;
  }
  std::map<TString,std::vector<SignatureObject*> >::iterator pIter;
  for(pIter = m_products.begin(); pIter != m_products.end(); pIter++){
    cout<<"product "<<(*pIter).first<<" "<<(*pIter).second.size()<<endl;
    vector<SignatureObject*> v = (*pIter).second;
    /*
    for(int i = 0; i < (int)v.size(); i++){
      cout<<"  "<<*v[i]<<endl;
    }
    */
  }
}
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
