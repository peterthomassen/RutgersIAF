#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

#include <assert.h>
#include <exception>

#include "TAxis.h"
#include "TFile.h"
#include "TH1D.h"
#include "THnBase.h"
#include "TTree.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(PhysicsContribution)

PhysicsContribution::PhysicsContribution() {
	/* no-op */
}

PhysicsContribution::PhysicsContribution(TString type, TString filename, double lumi, TString name) : m_filename(filename), m_lumi(lumi), m_name(name), m_type(type) {
	if(!(m_type == "data"  || m_type == "backgroundMC" || m_type == "backgroundDD" || m_type == "signal")) {
		throw std::runtime_error("invalid contribution type");
	}
}

PhysicsContribution::~PhysicsContribution() {
	delete m_hn;
}

void PhysicsContribution::addCorrelatedUncertainty(TString name, THnBase* h) {
	if(!h || !m_hn) {
		throw std::runtime_error("Histograms not ready");
	}
	if(h->GetNbins() != m_hn->GetNbins()) {
		throw std::runtime_error("Number of bins in uncertainty histogram does not match");
	}
	
	if(m_systematicUncertaintyMap.find(name) != m_systematicUncertaintyMap.end()) {
		cout << "Warning: Overwriting histogram for uncertainty " << name << endl;
		m_systematicUncertaintyMap[name] = h;
	} else {
		m_systematicUncertaintyMap.insert(make_pair(name, h));
	}
}

void PhysicsContribution::addFlatUncertainty(TString name, double relErr) {
	if(isData()) {
		return;
	}
	
	if(m_flatUncertaintyMap.find(name) != m_flatUncertaintyMap.end()) {
		cout << "Warning: Changing flat uncertainty " << name << " from " << m_flatUncertaintyMap[name] << " to " << relErr << endl;
		m_flatUncertaintyMap[name] = relErr;
	} else {
		m_flatUncertaintyMap.insert(make_pair(name, relErr));
	}
}

void PhysicsContribution::addWeight(TString varexp, TString type) {
	if(type != "" && m_type != type) {
		return;
	}
	
	if(isData()) {
		cerr << "Warning: Applying " << m_weights.size() << " weight(s) to data" << endl;
	}
	
	if(std::find(m_weights.begin(), m_weights.end(), varexp) != m_weights.end()) {
		cout << "Warning: Adding weight " << varexp << " repeatedly" << endl;
	}
	m_weights.push_back(varexp);
}

void PhysicsContribution::applyRelativeUncertainty(THnBase* hIn, TString name) {
	if(!hIn) {
		throw std::runtime_error("Null histogram given");
	}
	
	if(m_flatUncertaintyMap.find(name) == m_flatUncertaintyMap.end()) {
		throw std::runtime_error("Could not find requested flat uncertainty");
	}
	
	THnBase* h = (THnBase*)hIn->Clone(name);
	h->CalculateErrors(false);
	for(int i = 0; i <= h->GetNbins() + 1; ++i) {
		if(h->GetBinContent(i) == 0) {
			continue;
		}
		h->SetBinContent(i, m_flatUncertaintyMap[name] * h->GetBinContent(i));
	}
	
	addCorrelatedUncertainty(name, h);
}

THnBase* PhysicsContribution::fillContent(const THnBase* hn, std::string varexp, TString selection) {
	delete m_hn;
	
	m_hn = (THnBase*)hn->Clone();
	
	cout << "Running " << m_filename << " (" << m_type << ", lumi=" << m_lumi << "/pb) ";
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
	m_selection = selection;
	
	if(isData() || isSignal()) {
		for(auto &fakerate : m_fakerateMap) {
			if(!treeR->GetListOfBranches()->FindObject(fakerate.first)) {
				continue;
			}
			selection += TString::Format(" && %s == 0", fakerate.first.Data());
		}
	}
	
	selection = TString("(") + selection + TString(")");
	
	for(auto &weight : m_weights) {
		selection += TString(" * ") + weight;
	}
	
	// I suppose the following could be entirely in the weights mechanism. But now we have this already.
	if(m_fakerateMap.size() > 0) {
		// Apply fake rate
		if(isBackground()) {
			TString sum;
			for(auto &fakerate : m_fakerateMap) {
				if(!treeR->GetListOfBranches()->FindObject(fakerate.first)) {
					if(m_type == "backgroundDD") {
						cerr << "could not find branch for fake rate variable " << fakerate.first << endl;
						throw std::runtime_error("");
					}
					continue;
				}
				
				if(sum.Length() == 0) {
					sum = fakerate.first;
				} else {
					sum += TString(" + ") + fakerate.first;
				}
				
				selection += TString::Format(" * pow(%s, %s)", fakerate.second.Data(), fakerate.first.Data());
			}
			
			// Prune MC
			if(m_type == "backgroundMC") {
				if(sum.Length() > 0) {
					selection += TString::Format(" * pow(-1, %s > 0)", sum.Data());
				}
			} else
			// Only take fake events from backgroundDD input
			if(m_type == "backgroundDD") {
				selection += TString::Format(" * (%s > 0)", sum.Data());
			} else
			//
			{
				cerr << "background type: " << m_type << endl;
				throw std::runtime_error("Unknown background type");
			}
		}
		
		// Signal
		if(isSignal()) {
			cout << endl << "Notice: Fake rates are being ignored in signal treatment";
		}
	}
	
	if(m_debug) cout << endl << selection << endl;
	
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
	
	for(auto &flatUncertainty : m_flatUncertaintyMap) {
		applyRelativeUncertainty(m_hn, flatUncertainty.first);
	}
	
	return m_hn;
}

THnBase* PhysicsContribution::getContent() const {
	return m_hn;
}

double PhysicsContribution::getLumi() const {
	return m_lumi;
}

TString PhysicsContribution::getName() const {
	return m_name;
}

TString PhysicsContribution::getType(const bool detailed) const {
	if(detailed) {
		return m_type;
	}
	
	if(isData()) return "data";
	if(isBackground()) return "background";
	if(isSignal()) return "signal";
	
	throw std::runtime_error("should never make it here");
}

void PhysicsContribution::incorporateOverflow(TH1D* &h) {
	// Adapted from http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=6764
	UInt_t nx = h->GetNbinsX() + 1;
	Double_t* xbins = new Double_t[nx + 1];
	for (UInt_t i = 0; i < nx; ++i) {
		xbins[i] = h->GetBinLowEdge(i+1);
	}
	xbins[nx] = xbins[nx - 1] + h->GetBinWidth(nx);
	TH1D* htmp = new TH1D(h->GetName(), h->GetTitle(), nx, xbins);
	htmp->SetXTitle(h->GetXaxis()->GetTitle());
	htmp->SetYTitle(h->GetYaxis()->GetTitle());
	for (UInt_t i = 0; i <= nx; ++i) {
		htmp->SetBinContent(i, h->GetBinContent(i));
		htmp->SetBinError(i, h->GetBinError(i));
	}
	htmp->SetEntries(h->GetEntries());
	delete h;
	h = htmp;
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

std::pair<TH1D*, std::map<TString, TH1D*> > PhysicsContribution::project(const int dim, const double scale, const bool binForOverflow) const {
	TH1D* projection = m_hn->Projection(dim, "E");
	if(isData()) {
		projection->SetName(m_name);
		TString title = m_selection;
		for(const auto &rangeString : m_rangeStrings) {
			title += TString(" && ") + rangeString.second;
		}
		projection->SetTitle(title);
	} else {
		projection->SetTitle(m_name);
	}
	// Zerostat uncertainty for background and signal samples
	if(!isData()) {
		for(int i = 0; i <= projection->GetXaxis()->GetNbins() + 1; ++i) {
			if(projection->GetBinContent(i) == 0) {
				if(m_type == "backgroundDD" && i > 0) {
					cerr << "Overestimating zerostat uncertainty for " << m_name << " data-driven background in bin " << i << " -- need to multiply by fake rate" << endl;
				}
				projection->SetBinError(i, 1);
			}
		}
	}
	projection->Scale(scale);
	
	if(binForOverflow) {
		incorporateOverflow(projection);
	}
	
	std::map<TString, TH1D*> uncertainties;
	for(auto &uncertainty : m_systematicUncertaintyMap) {
		TH1D* hUncertainty = uncertainty.second->Projection(dim, "E");
		hUncertainty->Scale(scale);
		if(binForOverflow) {
			incorporateOverflow(hUncertainty);
		}
		uncertainties.insert(make_pair(uncertainty.first, hUncertainty));
	}
	
	return std::make_pair(projection, uncertainties);
}

bool PhysicsContribution::setDebug(bool debug) {
	bool oldDebug = m_debug;
	m_debug = debug;
	return oldDebug;
}

void PhysicsContribution::setFakeRate(TString name, TString f) {
	if(isData() && f != "0") {
		cerr << "Warning: Ignoring request to apply fake rate to data sample\n";
		f = "0";
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
	for(auto &correlatedUncertainty : m_systematicUncertaintyMap) {
		((TAxis*)correlatedUncertainty.second->GetListOfAxes()->FindObject(name))->SetRange(first, last);
	}
	
	if(lo == hi) {
		m_rangeStrings[name] = TString::Format("%s == %.0f", name, lo);
	} else if(includeLast) {
		m_rangeStrings[name] = TString::Format("%s >= %.0f && %s <= %.0f", name, lo, name, hi);
	} else {
		m_rangeStrings[name] = TString::Format("%s >= %.0f && %s < %.0f", name, lo, name, hi);
	}
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
	for(auto &correlatedUncertainty : m_systematicUncertaintyMap) {
		((TAxis*)correlatedUncertainty.second->GetListOfAxes()->FindObject(name))->SetRange(first, last);
	}
	
	m_rangeStrings[name] = TString::Format("%s >= %.0f", name, lo);
}

void PhysicsContribution::setRange(const char* name) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "Could not find axis " << name << endl;
		exit(1);
	}
	axis->SetRange();
	for(auto &correlatedUncertainty : m_systematicUncertaintyMap) {
		((TAxis*)correlatedUncertainty.second->GetListOfAxes()->FindObject(name))->SetRange();
	}
	
	m_rangeStrings.erase(name);
}

void PhysicsContribution::setRange() {
	m_hn->GetListOfAxes()->R__FOR_EACH(TAxis,SetRange)();
	
	m_rangeStrings.clear();
}
