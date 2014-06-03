#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

#include <assert.h>
#include <exception>

#include "TAxis.h"
#include "TFile.h"
#include "THnBase.h"
#include "TTree.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(PhysicsContribution)

PhysicsContribution::PhysicsContribution(TString type, TString filename, double lumi, TString name) : m_filename(filename), m_lumi(lumi), m_name(name), m_type(type) {
	if(!(m_type == "data"  || m_type == "backgroundMC" || m_type == "backgroundDD" || m_type == "signal")) {
		throw std::runtime_error("invalid contribution type");
	}
}

PhysicsContribution::~PhysicsContribution() {
	delete m_hn;
}

THnBase* PhysicsContribution::fillTHn(const THnBase* hn, std::string varexp, TString selection) {
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
	
	if(selection == "") {
		selection = "1";
	}
	
	if(isData()) {
		for(auto &fakerate : m_fakerateMap) {
			selection += TString::Format(" && %s == 0", fakerate.first.Data());
		}
	}
	
	selection = TString("(") + selection + TString(")");
	
	for(auto &fakerate : m_fakerateMap) {
		if(isBackground()) {
			selection += TString::Format(" * pow(%f, %s)", fakerate.second, fakerate.first.Data());
		}
		if(isSignal()) {
			cerr << "Warning: Fake rate treatment currently not implemented for signal\n" << endl;
		}
	}
	if(m_type == "backgroundMC" && m_fakerateMap.size() > 0) {
		TString sum;
		for(auto it = m_fakerateMap.begin(); it != m_fakerateMap.end(); ++it) {
			if(it == m_fakerateMap.begin()) {
				sum = it->first;
			} else {
				sum += TString(" + ") + it->first;
			}
		}
		selection += TString::Format(" * pow(-1, %s > 0) * ELIDISOWEIGHT * MUIDISOWEIGHT * PUWEIGHT * TRIGGERWEIGHT", sum.Data());
	}
	
	cout << endl << selection << endl;
	
	int step = 10000;
	Double_t x[m_hn->GetNdimensions()];
	for(int k = 0; k < treeR->GetEntries(); k += step) {
		if(k % (10 * step) == 9 * step) {
			cout << (int)(10*k/treeR->GetEntries()) << flush;
		} else {
			cout << '.' << flush;
		}
		treeR->Draw(varexp.c_str(), selection.Data(), "goff candle", step, k);
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

TString PhysicsContribution::getType() const {
	return m_type;
}

bool PhysicsContribution::isBackground() const {
	return m_type.BeginsWith("background");
}

bool PhysicsContribution::isData() const {
	return m_type.BeginsWith("data");
}

bool PhysicsContribution::isSignal() const {
	return m_type.BeginsWith("signal");
}

void PhysicsContribution::setFakeRate(TString name, double f) {
	if(isData() && f != 0) {
		cerr << "Warning: Ignoring request to apply fake rate to data sample\n";
		f = 0;
	}
	
	if(m_fakerateMap.find(name) != m_fakerateMap.end()) {
		cout << "Warning: Changing fake rate " << name << " from " << m_fakerateMap[name] << " to " << f << endl;
		m_fakerateMap[name] = f;
	} else {
		m_fakerateMap.insert(make_pair(name, f));
	}
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
