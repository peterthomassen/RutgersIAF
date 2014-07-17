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

PhysicsContribution::PhysicsContribution(TString type, TString filename, double lumi, TString name, bool unordered) : m_filename(filename), m_lumi(lumi), m_name(name), m_type(type), m_unordered(unordered) {
	if(!(m_type == "data"  || m_type == "backgroundMC" || m_type == "backgroundDD" || m_type == "signal")) {
		throw std::runtime_error("invalid contribution type");
	}
}

PhysicsContribution::~PhysicsContribution() {
	delete m_hn;
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
		h->SetBinContent(i, m_flatUncertaintyMap[name] * h->GetBinContent(i));
		h->SetBinError(i, 0);
	}
	
	applyUncertainty(name, h);
}

void PhysicsContribution::applyUncertainty(TString name, THnBase* h) {
	if(!h || !m_hn) {
		throw std::runtime_error("Histograms not ready");
	}
	if(h->GetNbins() != m_hn->GetNbins()) {
		throw std::runtime_error("Number of bins in uncertainty histogram does not match");
	}
	
	if(m_uncertaintyMap.find(name) != m_uncertaintyMap.end()) {
		cout << "Warning: Overwriting histogram for uncertainty " << name << endl;
		m_uncertaintyMap[name] = h;
	} else {
		m_uncertaintyMap.insert(make_pair(name, h));
	}
}

THnBase* PhysicsContribution::fillContent(const THnBase* hn, std::string varexp, TString selection, double scale, const double minScale) {
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
		selection += TString(" * (") + weight + TString(")");
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
	int n = treeR->GetEntries();
	// Limit reading of MC such that the scale factor is no less than minScale (default: 0.01) if the sample is randomly distributed (as given by m_unordered).
	// This means that we are skipping MC events beyond 100 times the data luminosity.
	if(!isData() && m_unordered && scale < minScale) {
		n /= minScale / scale;
		cout << "Reading only the first " << n << " of " << treeR->GetEntries() << " events, changing scale = " << scale << " --> " << minScale << endl;
		scale = minScale;
	}
	m_scale = scale;
	cout << "scale: " << m_scale << endl;
	Double_t x[m_hn->GetNdimensions()];
	for(int k = 0; k < n; k += step) {
		if(k % (10 * step) == 9 * step) {
			cout << (int)(10*k/treeR->GetEntries()) << flush;
		} else {
			cout << '.' << flush;
		}
		if(k + step > n) {
			step = n - k;
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

Int_t PhysicsContribution::getFillColor() const {
	return m_fillColor;
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

std::pair<TH1D*, std::map<TString, TH1D*> > PhysicsContribution::project(const int dim, const bool binForOverflow) const {
	TH1D* projection = m_hn->Projection(dim, "E");
	if(isData()) {
		projection->SetName(m_name);
		TString title = m_selection;
		for(const auto &rangeString : m_rangeStrings) {
			title += TString(" && ") + rangeString.second;
		}
		projection->SetTitle(title);
	} else {
		projection->SetName(m_name);
		projection->SetTitle(m_name);
	}
	
	// Zerostat uncertainty for background and signal samples
	if(!isData()) {
		for(int i = 0; i <= projection->GetXaxis()->GetNbins() + 1; ++i) {
			if(projection->GetBinContent(i) == 0) {
				double zerostat = 1;
				if(m_type == "backgroundDD" && i > 0) {
					zerostat = 0.051*1.25; // largest fake rate + uncertainty
					cerr << "Estimating zerostat uncertainty for " << m_name << " data-driven background in bin " << i << " as " << zerostat << " events" << endl;
				}
				projection->SetBinError(i, zerostat);
			}
		}
	}
	if(binForOverflow) {
		incorporateOverflow(projection);
	}
	projection->Scale(m_scale);
	if(m_fillColor >= 0) {
		projection->SetFillColor(m_fillColor);
	}
	
	std::map<TString, TH1D*> uncertainties;
	for(auto &uncertainty : m_uncertaintyMap) {
		TH1D* hUncertainty = uncertainty.second->Projection(dim, "E");
		if(binForOverflow) {
			incorporateOverflow(hUncertainty);
		}
		hUncertainty->Scale(m_scale);
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

void PhysicsContribution::setFillColor(const Int_t fillColor) {
	m_fillColor = fillColor;
}

bool PhysicsContribution::setRange(const char* name, double lo, double hi, bool includeLast) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "setRange: Could not find axis " << name << endl;
		return false;
	}
	
	Int_t first = axis->FindFixBin(lo);
	Int_t last  = axis->FindFixBin(hi);
	if(!includeLast) {
		--last;
	}
	
	axis->SetRange(first, last);
	for(auto &uncertainty : m_uncertaintyMap) {
		((TAxis*)uncertainty.second->GetListOfAxes()->FindObject(name))->SetRange(first, last);
	}
	
	if(lo == hi) {
		m_rangeStrings[name] = TString::Format("%s == %.0f", name, lo);
	} else if(includeLast) {
		m_rangeStrings[name] = TString::Format("%s >= %.0f && %s <= %.0f", name, lo, name, hi);
	} else {
		m_rangeStrings[name] = TString::Format("%s >= %.0f && %s < %.0f", name, lo, name, hi);
	}
	
	return true;
}

bool PhysicsContribution::setRange(const char* name, double lo) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "setRange: Could not find axis " << name << endl;
		return false;
	}
	axis->SetRange();
	Int_t first = axis->FindFixBin(lo);
	Int_t last  = axis->GetLast() + 1;
	axis->SetRange(first, last);
	for(auto &uncertainty : m_uncertaintyMap) {
		((TAxis*)uncertainty.second->GetListOfAxes()->FindObject(name))->SetRange(first, last);
	}
	
	m_rangeStrings[name] = TString::Format("%s >= %.0f", name, lo);
	
	return true;
}

bool PhysicsContribution::setRange(const char* name) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "setRange: Could not find axis " << name << endl;
		return false;
	}
	axis->SetRange();
	for(auto &uncertainty : m_uncertaintyMap) {
		((TAxis*)uncertainty.second->GetListOfAxes()->FindObject(name))->SetRange();
	}
	
	m_rangeStrings.erase(name);
	
	return true;
}

bool PhysicsContribution::setRange() {
	m_hn->GetListOfAxes()->R__FOR_EACH(TAxis, SetRange)();
	for(auto &uncertainty : m_uncertaintyMap) {
		uncertainty.second->GetListOfAxes()->R__FOR_EACH(TAxis, SetRange)();
	}
	
	m_rangeStrings.clear();
	
	return true;
}
