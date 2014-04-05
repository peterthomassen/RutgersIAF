#include "RutgersIAF2012/EventAnalyzer/interface/PeterTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include <TClonesArray.h>
#include <TTree.h>
#include <TFile.h>
#include <limits>
#include <assert.h>

using namespace std;

ClassImp(PeterTreeWriter)

PeterTreeWriter::PeterTreeWriter(BaseHandler* handler,TString treename)
: BaseTreeWriter(handler,treename), m_false(false), m_true(true) {
	//m_clonesarray = new TClonesArray("SignatureObject",1000);
	//m_tree->Branch("SignatureObjects",m_clonesarray);
	
	m_tree->Branch("nBits", &m_nBits);
	m_tree->Branch("fBits", &m_fBits);
	m_tree->Branch("bits", m_bits, "bits[fBits]/b");
}

PeterTreeWriter::~PeterTreeWriter() {
//  delete m_clonesarray;
}

void PeterTreeWriter::finish() {
	m_handler->getOutFile()->cd();
	m_tree->Write();
}

void PeterTreeWriter::processVariable(TString varName, void* address, TString type) {
	std::map<TString, std::pair<TBranch*,TBranch*> >::iterator branchIt = m_branches.find(varName);
	if(branchIt == m_branches.end()) {
//		cout << "Adding new branch " << varName << "[" << type << "]" << '\n';
		
		if(type == "O") {
			m_boolIndex.insert(make_pair(varName, m_boolIndex.size()));
			return;
		}
		
		TString fName = TString("f") + varName;
		TBranch* fBranch = m_tree->Branch(fName, &m_false);
		
		TBranch* branch = 0;
		
		if(type == "I" || type == "D" || type == "L" || type == "O") {
			TString leaflist = TString::Format("%s[f%s]/%s", varName.Data(), varName.Data(), type.Data());
			branch = m_tree->Branch(varName, address, leaflist);
		} else if(type == "TString") {
			TString* addr = new TString(*(TString*)address);
			branch = m_tree->Branch(varName, &addr);
		} else {
			assert(false);
		}
		
		for(Long64_t i = 0; i < m_tree->GetEntries(); ++i) {
			fBranch->Fill();
			branch->Fill();
		}
		
		fBranch->SetAddress(&m_true);
		m_branches.insert(make_pair(varName, make_pair(fBranch, branch)));
	} else {
		branchIt->second.first->SetAddress(&m_true);
		
		if(type == "I" || type == "D" || type == "L" || type == "O") {
			branchIt->second.second->SetAddress(address);
		} else if(type == "TString") {
			TString* addr = new TString(*(TString*)address);
			branchIt->second.second->SetAddress(&addr);
		} else {
			assert(false);
		}
	}
}

void PeterTreeWriter::fillTree() {
	std::fill(m_bits, m_bits + (1 << (sizeof(m_nBits)*8)) / sizeof(*m_bits), 0);
	
//  m_clonesarray->Clear();
	//cout << ">>> call " << m_tree->GetEntries() << endl;
	
	for(std::map<TString, std::pair<TBranch*,TBranch*> >::iterator it = m_branches.begin(); it != m_branches.end(); ++it) {
		it->second.first->SetAddress(&m_false);
	}
	
	for(std::map<TString, int>::iterator it = m_handler->m_variable_map_int.begin(); it != m_handler->m_variable_map_int.end(); ++it) {
		processVariable(it->first, &(it->second), "I");
	}
	
	for(std::map<TString, double>::iterator it = m_handler->m_variable_map_double.begin(); it != m_handler->m_variable_map_double.end(); ++it) {
		processVariable(it->first, &(it->second), "D");
	}
	
	for(std::map<TString, long>::iterator it = m_handler->m_variable_map_long.begin(); it != m_handler->m_variable_map_long.end(); ++it) {
		processVariable(it->first, &(it->second), "L");
	}
	
	for(std::map<TString, bool>::iterator it = m_handler->m_variable_map_bool.begin(); it != m_handler->m_variable_map_bool.end(); ++it) {
		processVariable(it->first, &(it->second), "O");
	}
	
	//m_handler->m_variable_map_TString.insert(make_pair("test", TString::Format("testval%d", (int)(m_tree->GetEntries()))));
	
	for(std::map<TString, TString>::iterator it = m_handler->m_variable_map_TString.begin(); it != m_handler->m_variable_map_TString.end(); ++it) {
		processVariable(it->first, &(it->second), "TString");
	}
	
	assert(m_boolIndex.size() < std::numeric_limits<unsigned short>::max() - sizeof(*m_bits)*8);
	m_nBits = m_boolIndex.size();
	m_fBits = (m_nBits + sizeof(*m_bits)*8 - 1) / (sizeof(*m_bits)*8);
	for(std::map<TString, bool>::iterator it = m_handler->m_variable_map_bool.begin(); it != m_handler->m_variable_map_bool.end(); ++it) {
		int idx = m_boolIndex[it->first] / (sizeof(*m_bits) * 8);
		int off = m_boolIndex[it->first] % (sizeof(*m_bits) * 8);
		m_tree->SetAlias(it->first, TString::Format("(bits[%d] & (1 << %d)) > 0", idx, off));
		if(it->second) {
			m_bits[idx] |= 1 << off;
		}
	}
	
/*	for(int i = 0; i < m_nBits; ++i) {
		bool humanReadable = true;
		int j = humanReadable
			? m_nBits - i - 1
			: i;
		cout << (bool)(m_bits[j/8] & (1 << (j%8)));
	}
	cout << '\n';
*/	
	m_tree->Fill();
}
