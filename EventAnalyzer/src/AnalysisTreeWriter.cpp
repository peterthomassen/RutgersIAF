#include "RutgersIAF/EventAnalyzer/interface/AnalysisTreeWriter.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include <TTree.h>
#include <TFile.h>
#include <TObject.h>

using namespace std;

ClassImp(AnalysisTreeWriter)

AnalysisTreeWriter::AnalysisTreeWriter(BaseHandler* handler,TString treename)
: BaseTreeWriter(handler,treename) {
	m_tree->Branch("bits", &m_bits);
	m_tree->SetAlias("I", "Iteration$ == 0");
}

AnalysisTreeWriter::~AnalysisTreeWriter() { }

void AnalysisTreeWriter::finish() {
	if(m_handler->getN() > 0 && m_tree->GetBranch("WEIGHT")) {
		m_tree->SetWeight(1./m_handler->getN());
	}
	m_handler->getOutFile()->cd();
	m_tree->Write(0, TObject::kOverwrite);
}

void AnalysisTreeWriter::fillTree() {
	// Prepare branches for non-bool event variables
	processVariable(m_handler->m_variable_map_int, "I");
	processVariable(m_handler->m_variable_map_double, "D");
	processVariable(m_handler->m_variable_map_long, "L");
	processVariable(m_handler->m_variable_map_TString, "TString");
	
	// Prepare bits branch
	m_bits.clear();
	for(typename std::map<TString, bool>::iterator it = m_handler->m_variable_map_bool.begin(); it != m_handler->m_variable_map_bool.end(); ++it) {
		if(m_boolIndex.find(it->first) == m_boolIndex.end()) {
			std::cout << "Adding new branch " << it->first << "[O]" << '\n';
			m_boolIndex.insert(std::make_pair(it->first, m_boolIndex.size()));
		}
	}
	
	size_t nBits = m_boolIndex.size();
	m_bits.resize((nBits + sizeof(unsigned char)*8 - 1) / (sizeof(unsigned char)*8));
	for(std::map<TString, bool>::iterator it = m_handler->m_variable_map_bool.begin(); it != m_handler->m_variable_map_bool.end(); ++it) {
		int idx = m_boolIndex[it->first] / (sizeof(unsigned char) * 8);
		int off = m_boolIndex[it->first] % (sizeof(unsigned char) * 8);
		// Do not change this: haddR relies on how the alias is defined
		m_tree->SetAlias(it->first, TString::Format("(bits[%d] & (1 << %d)) > 0", idx, off));
		if(it->second) {
			m_bits[idx] |= 1 << off;
		}
	}
	
	// Fill entry
	m_tree->Fill();
}
