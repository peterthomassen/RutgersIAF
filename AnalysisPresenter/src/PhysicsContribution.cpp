#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

#include <assert.h>

#include "TFile.h"
#include "THnBase.h"
#include "TTree.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(PhysicsContribution)

PhysicsContribution::PhysicsContribution(TString filename, double lumi, TString name) : m_filename(filename), m_lumi(lumi), m_name(name) {
}

PhysicsContribution::~PhysicsContribution() {
	/* no-op atm*/
}

THnBase* PhysicsContribution::fillTHn(const THnBase* hn, std::string varexp, std::string selection) {
	if(m_hn) {
		delete m_hn;
	}
	m_hn = (THnBase*)hn->Clone();
	
	TFile f(m_filename);
	if(f.IsZombie()) {
		return 0;
	}
	TTree* treeR = (TTree*)f.Get("treeR");
	if(!treeR) {
		return 0;
	}
	
	int step = 10000;
	Double_t x[m_hn->GetNdimensions()];
	for(int k = 0; k < treeR->GetEntries(); k += step) {
		treeR->Draw(varexp.c_str(), selection.c_str(), "goff candle", step, k);
		for(int i = 0; i < treeR->GetSelectedRows(); ++i) {
			for(Int_t j = 0; j < m_hn->GetNdimensions(); ++j) {
				x[j] = treeR->GetVal(j)[i];
			}
			m_hn->Fill(x, treeR->GetW()[i]);
		}
	}
	
	delete treeR;
	f.Close();
	
	return m_hn;
}
