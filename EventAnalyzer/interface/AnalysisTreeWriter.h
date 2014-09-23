#ifndef AnalysisTreeWriter_h
#define AnalysisTreeWriter_h

#include "RutgersIAF/EventAnalyzer/interface/BaseTreeWriter.h"
#include <assert.h>
#include <iostream>
#include <map>
#include <TBranchElement.h>

class BaseHandler;
class TBranch;
class TFile;
class TString;
class TTree;

class AnalysisTreeWriter : public BaseTreeWriter{
public:
	AnalysisTreeWriter(BaseHandler*,TString = "treeR");
	virtual ~AnalysisTreeWriter();
	
	virtual void finish();
	virtual void fillTree();

private:
	std::map<TString, TBranch*> m_branchesD;
	std::map<TString, TBranch*> m_branchesI;
	std::map<TString, TBranch*> m_branchesL;
	std::map<TString, TBranch*> m_branchesTString;
	
	std::map<TString, UInt_t> m_boolIndex;
	std::vector<unsigned char> m_bits; // 8 bits per element
	
	template<typename T>
	void processVariable(std::map<TString, std::vector<T>>, TString);
	
	ClassDef(AnalysisTreeWriter,1);
};

template<typename T>
void AnalysisTreeWriter::processVariable(std::map<TString, std::vector<T>> varMap, TString type) {
	std::map<TString, TBranch*>* branches = 0;
	if(type == "D") {
		branches = &m_branchesD;
	} else if(type == "I") {
		branches = &m_branchesI;
	} else if(type == "L") {
		branches = &m_branchesL;
	} else if(type == "TString") {
		branches = &m_branchesTString;
	} else {
		assert(false);
	}
	
	for(std::map<TString, TBranch*>::iterator it = branches->begin(); it != branches->end(); ++it) {
		reinterpret_cast<std::vector<T>*>(((TBranchElement*)(it->second))->GetObject())->clear();
	}
	
	for(auto it = varMap.begin(); it != varMap.end(); ++it) {
		typename std::map<TString, TBranch*>::iterator branchIt = branches->find(it->first);
		if(branchIt == branches->end()) {
			std::cout << "Adding new branch " << it->first << "[" << type << "]" << '\n';
			
			TBranch* branch = m_tree->Branch(it->first, new std::vector<T>, 32000, 0);
			
			for(Long64_t i = 0; i < m_tree->GetEntries(); ++i) {
				branch->Fill();
			}
			
			std::pair<std::map<TString, TBranch*>::iterator, bool> insPair = branches->insert(std::make_pair(it->first, branch));
			branchIt = insPair.first;
		}
		
		for(T value : it->second) {
			reinterpret_cast<std::vector<T>*>(((TBranchElement*)(branchIt->second))->GetObject())->push_back(value);
		}
	}
}

#endif
