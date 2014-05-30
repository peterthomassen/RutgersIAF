#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

#include <assert.h>

#include "TAxis.h"
#include "TFile.h"
#include "THnBase.h"
#include "TTree.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(PhysicsContribution)

PhysicsContribution::PhysicsContribution(TString filename, double lumi, TString name) : m_filename(filename), m_lumi(lumi), m_name(name) {
}

PhysicsContribution::~PhysicsContribution() {
	delete m_hn;
}

THnBase* PhysicsContribution::fillTHn(const THnBase* hn, std::string varexp, std::string selection) {
	delete m_hn;
	
	m_hn = (THnBase*)hn->Clone();
	
	cout << "Running " << m_filename << " (lumi=" << m_lumi << "/pb) ";
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
		if(k % (10 * step) == 9 * step) {
			cout << (int)(10*k/treeR->GetEntries()) << flush;
		} else {
			cout << '.' << flush;
		}
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
	
	cout << endl;
	
	return m_hn;
}

double PhysicsContribution::getLumi() const {
	return m_lumi;
}

THnBase* PhysicsContribution::getTHn() {
	return m_hn;
}

void PhysicsContribution::setRange(const char* name, double lo, double hi, bool includeLast) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "Could not find axis " << name << endl;
		exit(1);
	}
	
	Int_t first = axis->FindFixBin(lo);
	Int_t last  = axis->FindFixBin(hi);
	if(!includeLast) {
		--last;
	}
	
	axis->SetRange(first, last);
}

void PhysicsContribution::setRange(const char* name, double lo) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "Could not find axis " << name << endl;
		exit(1);
	}
	axis->SetRange();
	Int_t first = axis->FindFixBin(lo);
	Int_t last  = axis->GetLast() + 1;
	axis->SetRange(first, last);
}

void PhysicsContribution::setRange(const char* name) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "Could not find axis " << name << endl;
		exit(1);
	}
	axis->SetRange();
}
