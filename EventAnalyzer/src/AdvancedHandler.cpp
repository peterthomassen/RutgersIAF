#include "RutgersIAF/EventAnalyzer/interface/AdvancedHandler.h"
#include <algorithm>
#include <TFile.h>
#include "TPRegexp.h"
#include <string>
#include <fstream>
#include "RutgersIAF/EventAnalyzer/interface/Signature.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureWithBjets.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH3F.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseTreeWriter.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_CountWeight.h"
#include "RutgersIAF/EventAnalyzer/interface/PrintModule.h"
#include "RutgersIAF/EventAnalyzer/interface/ProductMaker.h"

#include <assert.h>

using namespace std;

ClassImp(AdvancedHandler)

AdvancedHandler::AdvancedHandler(TString ofname, BaseTreeReader* reader) : BaseHandler(ofname,reader)
{

}


AdvancedHandler::~AdvancedHandler()
{

}

//-----------------------------------------
//-----------------------------------------
void AdvancedHandler::eventLoop()
{
        eventLoop(-1, 0);
}
//-----------------------------------------
void AdvancedHandler::eventLoop(int onlyRun, long int onlyEvent)
{
	int nevents = m_reader->GetEntries();
	int nEntryLow = getMode("nEntryLow");
	int nEntryHigh = getMode("nEntryHigh");
	bool done = false;
	if(nEntryHigh == 0 || nEntryHigh > nevents) {
		nEntryHigh = nevents;
	}
	if(m_writers.size() > 0) {
		m_n = nEntryHigh - nEntryLow;
	}
	for(m_currentEntry = nEntryLow; m_currentEntry < nEntryHigh; m_currentEntry++){
		if(done) break;
		if (m_currentEntry % 100000 == 0) {
			cout<<"Processing event "<<m_currentEntry<<" of "<<nevents<<endl;
		}
		
		m_trackFakeCombination = 0;
		m_photonFakeCombination = 0;
		m_tauFakeCombination = 0;
		for(m_trackFakeCombinationIndex = 0; m_trackFakeCombinationIndex <= m_trackFakeCombination; ++m_trackFakeCombinationIndex) {
			for(m_photonFakeCombinationIndex = 0; m_photonFakeCombinationIndex <= m_photonFakeCombination; ++m_photonFakeCombinationIndex) {
				for(m_tauFakeCombinationIndex = 0; m_tauFakeCombinationIndex <= m_tauFakeCombination; ++m_tauFakeCombinationIndex) {
					m_reader->GetEntry(m_currentEntry);
					int run = 0, lumiBlock = 0;
					long event = 0;
					bool hasRun = m_reader->getVariable("RUN",run);
					bool hasLumi = m_reader->getVariable("LUMI",lumiBlock);
					bool hasEvent = m_reader->getVariable("EVENT",event);
					
					if(!hasRun || !hasLumi || !hasEvent)continue;
					
					if(onlyRun >= 0) {
						if(run != onlyRun || event != onlyEvent) {
							continue;
						}
						if(m_trackFakeCombinationIndex + m_photonFakeCombinationIndex + m_tauFakeCombinationIndex == 0) {
							cout << "This is entry " << m_currentEntry << endl;
						}
						done = true;
					}
					
					if(onlyRun >= 0 && m_trackFakeCombinationIndex + m_photonFakeCombinationIndex + m_tauFakeCombinationIndex == 0 && getDebugMode()) {
						m_reader->dumpEventInfo();
					}
					
					m_writer = getWriter();
					if(getMode("trackFakeCombination") || getMode("photonFakeCombination") || getMode("tauFakeCombination")) {
						cout << "E=" << event;
						if((bool)m_trackFakeCombinationIndex + (bool)m_photonFakeCombinationIndex + (bool)m_tauFakeCombinationIndex > 1) {
							cout << ", skipping (multiple fake proxy flavors)" << '\n';
							continue;
						}
						if(getMode("trackFakeCombination")) {
							cout << " trackIt=" << m_trackFakeCombinationIndex;
							if(m_trackFakeCombinationIndex) m_writer = getWriter("trackFakeCombination");
						}
						if(getMode("photonFakeCombination")) {
							cout << " photonIt=" << m_photonFakeCombinationIndex;
							if(m_photonFakeCombinationIndex) m_writer = getWriter("photonFakeCombination");
						}
						if(getMode("tauFakeCombination")) {
							cout << " tauIt=" << m_tauFakeCombinationIndex;
							if(m_tauFakeCombinationIndex) m_writer = getWriter("tauFakeCombination");
						}
						cout << '\n';
					}
					
					if(m_dumpList.find(run) != m_dumpList.end() && m_dumpList[run].find(lumiBlock) != m_dumpList[run].end() && find(m_dumpList[run][lumiBlock].begin(),m_dumpList[run][lumiBlock].end(),event) != m_dumpList[run][lumiBlock].end()) {
						dumpEventInfo();
					}
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
					
					int incarnation = m_trackFakeCombinationIndex
						+ m_trackFakeCombination + m_photonFakeCombinationIndex
						+ m_trackFakeCombination + m_photonFakeCombination + m_tauFakeCombinationIndex;
					
					bool wellPrepared = prepareEvent();
					if(!wellPrepared) {
						continue;
					}
					
					if(m_hookFunction && applyHandlerCuts()) {
						if(!(*m_hookFunction)(this, incarnation)) {
							continue;
						}
					}
					
					setVariable("fakeIncarnation", incarnation);
					if(incarnation == 0) {
						analyzeEvent();
					}

					if(applyHandlerCuts()){
					  bool saveEvent = false;
					  bool isSet = getVariable("WRITEEVENT",saveEvent);
					  if(m_writer && isSet && saveEvent) {
						  m_writer->fillTree();
					  }
					}
				}
			}
		}
	}//End of event loop
}

//-----------------------------------------
//-----------------------------------------
bool AdvancedHandler::createProducts()
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
    m_products[m_product_names[i]] = m_product_maker_map[m_product_names[i]]->makeProduct(this);
  }
  
  return true;
}
//-----------------------------------------
//-----------------------------------------
bool AdvancedHandler::prepareEvent()
{
  if(m_currentEntry == m_lastEntryPrepared && !(getMode("trackFakeCombination") || getMode("photonFakeCombination") || getMode("tauFakeCombination"))) {
	  return true;
  }
  resetProducts();
  resetVariables();

  m_products = m_reader->getProducts();

  m_variable_map_double = m_reader->m_variable_mapdouble;
  m_variable_map_int = m_reader->m_variable_mapint;
  m_variable_map_long = m_reader->m_variable_maplong;
  m_variable_map_TString = m_reader->m_variable_mapTString;
  m_variable_map_bool = m_reader->m_variable_mapbool;

  bool wellPrepared = createProducts();
  if(!wellPrepared) {
	  return false;
  }

  calculateVariables();

  m_lastEntryPrepared = m_currentEntry;

  calcPhysicsWeight();

  return true;
}
//------------------------------------------
//------------------------------------------
//-----------------------------------------
void AdvancedHandler::addProductComparison(TString pname1,TString pname2, ObjectComparison* comparison, bool requireAnd)
{
  map<TString,ProductMaker*>::iterator iter = m_product_maker_map.find(pname1);
  if(iter == m_product_maker_map.end()){
    cerr<<"WARNING attempting to add product comparison to unknown product: "<<pname1<<endl;
    return;
  }
  if(!requireAnd){
    cerr<<"WARNING not doing match/association through comparison anymore, skipping comparison between "<<pname1<<" and "<<pname2<<endl;
    return;
  }
  (*iter).second->addComparison(pname2,comparison);
  
}
//-----------------------------------------
//-----------------------------------------
void AdvancedHandler::addProductSelfComparison(TString pname, ObjectComparison* comparison, bool requireAnd)
{
  map<TString,ProductMaker*>::iterator iter = m_product_maker_map.find(pname);
  if(iter == m_product_maker_map.end()){
    cerr<<"WARNING attempting to add self comparison to unknown product: "<<pname<<endl;
    return;
  }
  if(!requireAnd){
    cerr<<"WARNING not doing match/association through comparison anymore, skipping self comparison for "<<pname<<endl;
    return;
  }
  (*iter).second->addSelfComparison(comparison);

}
//-----------------------------------------
//-----------------------------------------
void AdvancedHandler::analyzeEvent()
{
	unsigned int nSig = m_Signatures.size();
	unsigned int nBjetSig = m_bjetSignatures.size();
	unsigned int nPreSig = m_preHandlerCutSignatures.size();
	vector<int> isSigVec(nSig + nBjetSig + nPreSig,0);

	m_noCutSignature->fillHistograms();

	if(m_debugMode)
	  printDebugInfo();

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

}
//-----------------------------------------
//-----------------------------------------
void AdvancedHandler::addProduct(TString pname, ProductMaker* pm)
{
  map<TString,ProductMaker*>::iterator iter = m_product_maker_map.find(pname);
  if(iter == m_product_maker_map.end()){
    cerr<<"WARNING replacing product maker for product: "<<pname<<endl;
  }
  m_product_maker_map[pname] = pm;
}
//-----------------------------------------
//-----------------------------------------
void AdvancedHandler::addProduct(TString pname, TString sname)
{
  ProductMaker* pm = new ProductMaker(sname,pname);
  addProduct(pname,pm);
}
//-----------------------------------------
//-----------------------------------------
void AdvancedHandler::addProductCut(TString pname, TString cut)
{
  map<TString,ProductMaker*>::iterator iter = m_product_maker_map.find(pname);
  if(iter == m_product_maker_map.end()){
    cerr<<"WARNING unable to find product: "<<pname<<endl;
    return;
  }
  (*iter).second->addCut(cut);
}
//-----------------------------------------
//-----------------------------------------
void AdvancedHandler::addProductAssociation(TString pname1,TString pname2, ObjectAssociation* association)
{
  map<TString,ProductMaker*>::iterator iter = m_product_maker_map.find(pname1);
  if(iter == m_product_maker_map.end()){
    cerr<<"WARNING attempting to add product association to unknown product: "<<pname1<<endl;
    return;
  }
  (*iter).second->addAssociation(pname2,association);
}
//-----------------------------------------
//-----------------------------------------
void AdvancedHandler::addAssociateVariable(TString pname, TString oname, ObjectVariable* objvar, bool rename)
{
  map<TString,ProductMaker*>::iterator iter = m_product_maker_map.find(pname);
  if(iter == m_product_maker_map.end()){
    cerr<<"WARNING attempting to add associate variable to unknown product: "<<pname<<endl;
    return;
  }
  (*iter).second->addAssociateVariable(oname,objvar,rename);
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
