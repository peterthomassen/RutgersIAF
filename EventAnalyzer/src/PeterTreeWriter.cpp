#include "RutgersIAF2012/EventAnalyzer/interface/PeterTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include <TTree.h>
#include <TFile.h>

using namespace std;

ClassImp(PeterTreeWriter)

PeterTreeWriter::PeterTreeWriter(BaseHandler* handler,TString treename)
: BaseTreeWriter(handler,treename) {
	m_tree->Branch("bits", &m_bits);
}

PeterTreeWriter::~PeterTreeWriter() { }

void PeterTreeWriter::finish() {
	m_handler->getOutFile()->cd();
	m_tree->Write();
}

void PeterTreeWriter::fillTree() {
	// Prepare branches for non-bool event variables
	processVariable(m_handler->m_variable_map_int, "I");
	processVariable(m_handler->m_variable_map_double, "D");
	processVariable(m_handler->m_variable_map_long, "L");
	processVariable(m_handler->m_variable_map_TString, "TString");
	// Prepares m_boolIndex
	processVariable(m_handler->m_variable_map_bool, "O");
	
	size_t nBits = m_boolIndex.size();
	m_bits.resize((nBits + sizeof(unsigned char)*8 - 1) / (sizeof(unsigned char)*8));
	for(std::map<TString, bool>::iterator it = m_handler->m_variable_map_bool.begin(); it != m_handler->m_variable_map_bool.end(); ++it) {
		int idx = m_boolIndex[it->first] / (sizeof(unsigned char) * 8);
		int off = m_boolIndex[it->first] % (sizeof(unsigned char) * 8);
		m_tree->SetAlias(it->first, TString::Format("(bits[%d] & (1 << %d)) > 0", idx, off));
		if(it->second) {
			m_bits[idx] |= 1 << off;
		}
	}
	
/*	for(size_t i = 0; i < nBits; ++i) {
		bool humanReadable = true;
		size_t j = humanReadable ? (nBits - i - 1) 	: i;
		cout << (bool)(m_bits[j/8] & (1 << (j%8)));
	}
	cout << '\n';*/
	
	m_tree->Fill();
}
