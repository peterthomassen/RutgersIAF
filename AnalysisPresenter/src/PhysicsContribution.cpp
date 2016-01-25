#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include <assert.h>
#include <exception>
#include <iostream>

#include "TAxis.h"
#include "TFile.h"
#include "TH1D.h"
#include "THnBase.h"
#include "TLeaf.h"
#include "TTree.h"

#include "RutgersIAF/AnalysisPresenter/interface/BaseBundleProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContributionProjection.h"

using namespace std;

ClassImp(PhysicsContribution)

PhysicsContribution::PhysicsContribution() {
	/* no-op */
}

PhysicsContribution::PhysicsContribution(TString type, TString filename, double lumiOrXsec, TString name, bool allowNegative, TString treeRname, Int_t fillColor, double minScale, bool unordered) : BaseBundle(type, name, allowNegative, fillColor), m_filename(filename), m_treeRname(treeRname), m_minScale(minScale), m_unordered(unordered) {
	if(!(m_type == "data"  || m_type == "backgroundMC" || m_type == "backgroundDD" || m_type == "signal")) {
		throw std::runtime_error("invalid contribution type");
	}
	
	TFile f(m_filename);
	if(f.IsZombie()) {
		cout << "was processing " << m_filename << endl;
		throw std::runtime_error("could not open contribution root file");
	}
	TTree* treeR = (TTree*)f.Get(m_treeRname);
	if(!treeR) {
		cout << "was processing " << m_filename << ", looking for Rutgers tree " << m_treeRname << endl;
		throw std::runtime_error("contribution root file does not contain treeR");
	}
	//m_MC = treeR->GetBranch("WEIGHT");
	m_MC = (type != "data" && type != "backgroundDD");
	m_lumi = isMC()
		? (1. / lumiOrXsec / treeR->GetWeight())
		: lumiOrXsec;
	delete treeR;
	f.Close();
	
	if(m_MC && (m_type == "data" || m_type == "backgroundDD")) {
		cout << "Warning: " << m_filename << "#" << m_treeRname << " has WEIGHT branch, but is being used as " << m_type << endl;
	}
	if(!m_MC && (m_type == "signal" || m_type == "backgroundMC")) {
		cout << "was processing " << m_filename << "#" << m_treeRname << endl;
		throw std::runtime_error("MC tree does not have a WEIGHT branch");
	}
}

PhysicsContribution::~PhysicsContribution() {
	delete m_hn;
	delete m_hnAbs;
	
	for(auto &uncertainty : m_uncertaintyMap) {
		delete uncertainty.second.second;
	}
}

void PhysicsContribution::addFlatUncertainty(TString name, double relErr) {
	if(isData()) {
		return;
	}
	
	assert(m_uncertaintyMap.find(name) == m_uncertaintyMap.end());
	assert(m_variationMap.find(name) == m_variationMap.end());
	
	if(m_flatUncertaintyMap.find(name) != m_flatUncertaintyMap.end()) {
		cout << "Warning: Changing flat uncertainty " << name << " from " << m_flatUncertaintyMap[name] << " to " << relErr << endl;
		m_flatUncertaintyMap[name] = relErr;
	} else {
		m_flatUncertaintyMap.insert(make_pair(name, relErr));
	}
}

void PhysicsContribution::addRelativeUncertainty(TString name, TString uncertaintyExpression) {
	if(isData()) {
		return;
	}
	
	assert(m_flatUncertaintyMap.find(name) == m_flatUncertaintyMap.end());
	assert(m_variationMap.find(name) == m_variationMap.end());
	
	auto pair = make_pair(uncertaintyExpression, (THnBase*)(0));
	
	if(m_uncertaintyMap.find(name) != m_uncertaintyMap.end()) {
		cout << "Warning: Changing uncertainty " << name << " from " << m_uncertaintyMap[name].first << " to " << pair.first << endl;
		m_uncertaintyMap[name] = pair;
	} else {
		m_uncertaintyMap.insert(make_pair(name, pair));
	}
}

void PhysicsContribution::addVariation(TString name, std::pair<TString, TString> mapping) {
	if(isData()) {
		return;
	}
	
	assert(m_flatUncertaintyMap.find(name) == m_flatUncertaintyMap.end());
	assert(m_uncertaintyMap.find(name) == m_uncertaintyMap.end() || m_uncertaintyMap[name].first == "");
	
	assert((m_uncertaintyMap.find(name) != m_uncertaintyMap.end()) == (m_variationMap.find(name) != m_variationMap.end()));
	
	auto pair = make_pair("", (THnBase*)(0));
	
	if(m_uncertaintyMap.find(name) != m_uncertaintyMap.end()) {
		cout << "Warning: Changing variation " << name << endl;
		m_variationMap[name] = mapping;
		m_uncertaintyMap[name] = pair;
	} else {
		m_variationMap.insert(make_pair(name, mapping));
		m_uncertaintyMap.insert(make_pair(name, pair));
	}
}

void PhysicsContribution::addWeight(TString weight, double normalization) {
	if(normalization != 1.0) {
		weight = TString::Format("(%s) * %f", weight.Data(), normalization);
	}
	
	if(isData()) {
		cerr << "Notice: Applying weight " << weight << " to data" << endl;
	}
	
	if(std::find(m_weights.begin(), m_weights.end(), weight) != m_weights.end()) {
		cout << "Warning: Adding weight " << weight << " repeatedly" << endl;
	}
	m_weights.push_back(weight);
}

bool PhysicsContribution::addVetoEvent(std::string vetoString) {
	auto result = m_vetoEvents.insert(vetoString);
	return result.second;
}

void PhysicsContribution::applyFlatUncertainty(TString name) {
	if(!m_hn) {
		throw std::runtime_error("Null histogram given");
	}
	
	if(m_flatUncertaintyMap.find(name) == m_flatUncertaintyMap.end()) {
		throw std::runtime_error("Could not find requested flat uncertainty");
	}
	
	if(m_hn->GetEntries() == 0) {
		return;
	}
	
	THnBase* h = (THnBase*)m_hn->Clone(name);
	h->CalculateErrors(false);
	h->Scale(m_flatUncertaintyMap[name]);
	
	if(m_uncertaintyMap.find(name) != m_uncertaintyMap.end()) {
		cout << "Warning: Overwriting histogram for uncertainty " << name << endl;
		m_uncertaintyMap[name].second = h;
	} else {
		m_uncertaintyMap.insert(make_pair(name, make_pair("", h)));
	}
}

THnBase* PhysicsContribution::fillContent(const THnBase* hn, std::string varexp, TString selection, double scale, TH1D* hPileup) {
	delete m_hn;
	delete m_hnAbs;
	
	m_hn = (THnBase*)hn->Clone();
	if(m_nominalWeight.Length() > 0) {
		m_hnAbs = (THnBase*)hn->Clone();
		m_hnAbs->Reset();
	}
	
	for(auto &uncertainty : m_uncertaintyMap) {
		delete uncertainty.second.second;
		uncertainty.second.second = (THnBase*)hn->Clone(uncertainty.first);
		uncertainty.second.second->Reset();
		uncertainty.second.second->CalculateErrors(false);
	}
	
	TFile f(m_filename);
	if(f.IsZombie()) {
		throw std::runtime_error("couldn't open contribution file");
	}
	TTree* treeR = (TTree*)f.Get(m_treeRname);
	treeR->SetWeight(1);
	
	TH1D* hPileupWeights = 0;
	TH1D* hPileupMC = (TH1D*)f.Get("noCutSignature_TrueNumInteractions");
	if(isMC() && hPileup && hPileupMC) {
		hPileupWeights = (TH1D*)hPileup->Clone();
		hPileupWeights->Scale(1./hPileupWeights->Integral());
		hPileupMC->Scale(1./hPileupMC->Integral());
		hPileupWeights->Divide(hPileupMC);
	}
	
	cout << "Running " << m_filename << "#" << m_treeRname << " (" << m_type << ", lumi=" << m_lumi << "/pb)" << endl;
	fillContentVariation(treeR, m_hn, varexp, selection, scale, hPileupWeights);
	
	for(auto &pair : m_variationMap) {
		TString orgBranchName = pair.second.first;
		TString tmpBranchName = TString("_") + orgBranchName;
		TString variationExpr = pair.second.second;
		
		cout << "Running " << m_filename << "#" << m_treeRname << " (" << m_type << ", lumi=" << m_lumi << "/pb), " << pair.first << " variation (" << orgBranchName << " --> " << variationExpr << ")" << endl;
		
		assert(treeR->GetBranch(orgBranchName));
		
		treeR->GetBranch(orgBranchName)->SetTitle(tmpBranchName);
		treeR->GetBranch(orgBranchName)->SetName(tmpBranchName);
		treeR->GetLeaf(orgBranchName)->SetTitle(tmpBranchName);
		treeR->GetLeaf(orgBranchName)->SetName(tmpBranchName);
		treeR->SetAlias(orgBranchName, variationExpr);
		
		fillContentVariation(treeR, m_uncertaintyMap[pair.first].second, varexp, selection, scale, hPileupWeights);
		
		treeR->GetListOfAliases()->Remove(treeR->GetListOfAliases()->FindObject(orgBranchName));
		treeR->GetBranch(tmpBranchName)->SetTitle(orgBranchName);
		treeR->GetBranch(tmpBranchName)->SetName(orgBranchName);
		treeR->GetLeaf(tmpBranchName)->SetTitle(orgBranchName);
		treeR->GetLeaf(tmpBranchName)->SetName(orgBranchName);
	}
	
	delete hPileupWeights;
	delete hPileupMC;
	delete treeR;
	f.Close();
	
	for(auto &flatUncertainty : m_flatUncertaintyMap) {
		applyFlatUncertainty(flatUncertainty.first);
	}
	
	for(auto &uncertainty : m_uncertaintyMap) {
		auto h = uncertainty.second.second;
		if(!h->GetNbins()) {
			continue;
		}
		for(int i = 0; i <= h->GetNbins() + 1; ++i) {
			h->SetBinError(i, 0);
		}
	}
	
	return m_hn;
}

THnBase* PhysicsContribution::fillContentVariation(TTree* treeR, THnBase* hn, std::string varexp, TString selection, double scale, TH1D* hPileupWeights) {
	assert(treeR);
	
	bool variation = (hn != m_hn);
	
	if(selection == "") {
		selection = "1";
	}
	m_selection = selection;
	
	if(isData() || isSignal()) {
		for(auto &fakerate : m_fakerateMap) {
			if(!treeR->GetListOfBranches()->FindObject(fakerate.first)) {
				continue;
			}
			selection += TString::Format(" && %s[0] == 0", fakerate.first.Data());
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
					sum = fakerate.first + TString("[0]");
				} else {
					sum += TString(" + ") + fakerate.first + TString("[0]");
				}
				
				selection += TString::Format(" * pow(%s, %s[0])", fakerate.second.Data(), fakerate.first.Data());
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
			cout << "Notice: Fake rates are being ignored in signal treatment" << endl;
		}
	}
	
	if(m_debug) cout << selection << endl;
	
	int step = 10000;
	int n = treeR->GetEntries();
	
	// Limit reading of MC such that the scale factor is no less than m_minScale if the sample is randomly distributed (as given by m_unordered).
	// This means that we are skipping MC events beyond 100 times the data luminosity.
	if(!isData() && m_unordered && scale < m_minScale && n > 0) {
		int nOld = n;
		double scaleOld = scale;
		n /= m_minScale / scale;
		scale *= (float)nOld / n;
		cout << "Reading only the first " << n << " of " << treeR->GetEntries() << " events, changing scale = " << scaleOld << " --> " << scale << " (target scale: " << m_minScale << ")" << endl;
	}
	m_scale = scale;
	cout << "scale: " << m_scale << endl;
	
	Double_t x[hn->GetNdimensions()];
	std::string varexpIncarnation = treeR->GetListOfBranches()->FindObject("fakeIncarnation")
		? "fakeIncarnation[0]"
		: ((m_type == "backgroundDD") ? "Entry$" : "0");
	
	TString varexpFull = TString::Format("%s:EVENT[0]:RUN[0]:LUMI[0]:%s:Entry$", varexp.c_str(), varexpIncarnation.c_str());
	
	varexpFull += (m_hnAbs)
		? TString(":") + m_nominalWeight
		: TString(":1");
	
	if(hPileupWeights) {
		varexpFull += ":TrueNumInteractions[0]";
	}
	
	int uncertaintyOffset = 0;
	std::vector<TString> uncertaintyNames;
	if(!variation) {
		uncertaintyOffset = hn->GetNdimensions() + 6 + (bool)hPileupWeights;
		
		for(const auto &uncertainty : m_uncertaintyMap) {
			if(uncertainty.second.first == "") {
				continue;
			}
			uncertaintyNames.push_back(uncertainty.first);
		}
		
		for(const auto uncertaintyName : uncertaintyNames) {
			varexpFull += TString(":") + m_uncertaintyMap[uncertaintyName].first;
		}
	}
	
	if(m_vetoEvents.size() > 0) {
		cout << "Notice: " << m_vetoEvents.size() << " events in veto list" << endl;
	}
	
	long entryPrev = 0;
	
	for(int k = 0; k < n; k += step) {
		if(k % (10 * step) == 9 * step) {
			cout << (int)(10*k/n) << flush;
		} else {
			cout << '.' << flush;
		}
		if(k + step > n) {
			step = n - k;
		}
		
		// PT 20141009: I checked that step refers to TTree entries, not entry instances. So we're good even when looping over collections, and always get full events counted properly.
		long nSelected = treeR->Draw(varexpFull.Data(), selection.Data(), "goff candle", step, k);
		if(nSelected < 0) {
			throw std::runtime_error("error selecting events");
		}
		
		for(int i = 0; i < nSelected; ++i) {
			// Extract metadata
			long event = treeR->GetVal(hn->GetNdimensions() + 0)[i] + 0.5;
			int run = treeR->GetVal(hn->GetNdimensions() + 1)[i] + 0.5;
			int lumi = treeR->GetVal(hn->GetNdimensions() + 2)[i] + 0.5;
			int fakeIncarnation = treeR->GetVal(hn->GetNdimensions() + 3)[i] + 0.5;
			long entry = treeR->GetVal(hn->GetNdimensions() + 4)[i] + 0.5;
			
			// Skip vetoed events
			std::string vetoString = TString::Format("%ld:%d:%d", event, run, lumi).Data();
			if(m_vetoEvents.find(vetoString) != m_vetoEvents.end()) {
				cout << "Skipping vetoed event e=" << event << " r=" << run << " l=" << lumi << endl;
				continue;
			}
			
			// Get variable values and weight
			for(Int_t j = 0; j < hn->GetNdimensions(); ++j) {
				x[j] = treeR->GetVal(j)[i];
			} 
			double weight = treeR->GetW()[i];
			
			if(hPileupWeights) {
				int trueNumInteractions = (int)(treeR->GetVal(hn->GetNdimensions() + 6)[i]); // don't add 0.5 because we have integer bin boundaries
				weight *= hPileupWeights->GetBinContent(trueNumInteractions + 1); // 1st bin contains ((int)trueNumInteractions == 0)
			}
			
			// Fill histograms
			if(m_hnAbs) {
				if(!variation) {
					m_hnAbs->Fill(x, weight);
				}
				
				// This is the sgn function
				weight *= (treeR->GetVal(hn->GetNdimensions() + 5)[i] > 0) - (treeR->GetVal(hn->GetNdimensions() + 5)[i] < 0);
			}
			Long64_t bin = hn->Fill(x, weight);
			
			if(!variation) {
				// Fill uncertainties
				for(size_t l = 0; l < uncertaintyNames.size(); ++l) {
					double uncertainty = treeR->GetVal(uncertaintyOffset + l)[i];
					m_uncertaintyMap[uncertaintyNames[l]].second->Fill(x, weight * uncertainty);
				}
				
				// Write down event and run number, lumi section and fake incartion
				if(bin >= (Long64_t)m_metadata.size()) {
					m_metadata.push_back(std::vector<metadata_t>());
				}
				if(entry != entryPrev || (k == 0 && i == 0)) {
					m_metadata[bin].push_back({event, run, lumi, fakeIncarnation});
				}
			}
			entryPrev = entry;
		}
	}
	
	cout << endl;
	
	if(variation) {
		hn->Add(m_hn, -1);
	}
	
	return hn;
}

int PhysicsContribution::findBinFromLowEdge(TAxis* axis, double x) {
	int bin = axis->FindFixBin(x);
	double width = axis->GetBinWidth(bin);
	double lo = axis->GetBinLowEdge(bin);
	double hi = axis->GetBinUpEdge(bin);
	if(x < lo) {
		cerr << "Error: " << x << " seems to be in the underflow bin of " << axis->GetName() << " axis; please rebin" << endl;
		throw std::runtime_error("binning error");
	} else if(x > lo + width / 100 && x < hi - width / 100) {
		cerr << "Error: " << x << " is not a bin boundary for " << axis->GetName() << " axis (considered boundaries: " << lo << " and " << hi << ")" << endl;
		throw std::runtime_error("binning error");
	}
	return bin;
}

std::set<Long64_t> PhysicsContribution::getBins() const {
	std::set<Long64_t> bins;
	THnIter iter(m_hn, true);
	Long64_t bin;
	while((bin = iter.Next()) >= 0) {
		auto ins = bins.insert(bin);
		assert(ins.second);
	}
	return bins;
}

THnBase* PhysicsContribution::getContent(bool absoluteWeights) const {
	return absoluteWeights ? m_hnAbs : m_hn;
}

std::map<PhysicsContribution*, std::map<TString, TString>> PhysicsContribution::getEnsembleFakeRateParams() const {
	return m_ensembleFakeRateParams;
}

double PhysicsContribution::getLumi() const {
	return m_lumi;
}

std::set<PhysicsContribution::metadata_t> PhysicsContribution::getMeta() const {
	std::set<PhysicsContribution::metadata_t> s;
	unsigned int nDuplicates = 0;
	
	for(const auto &bin : getBins()) {
		for(auto &metadata : m_metadata[bin]) {
			auto ins = s.insert(metadata);
			if(!ins.second) {
				if(nDuplicates < 10) {
					cout << "Notice: duplicate entry in " << getName() << ": " << metadata.event << " " << metadata.run << " " << metadata.lumi << " " << metadata.fakeIncarnation << endl;
				}
				++nDuplicates;
			}
		}
	}
	
	if(nDuplicates > 0) {
		cout << "Notice: " << nDuplicates << " duplicate entries in " << getName() << " (showing no more than 10)" << endl;
	}
	
	//assert(nDuplicates == 0);
	/*if(nDuplicates > 0) {
		cout << "Press any key to continue" << flush;
		system("read");
	}*/
	
	return s;
}

std::vector<std::pair<int, int>> PhysicsContribution::getRanges() const {
	std::vector<std::pair<int, int>> ranges;
	for(int i = 0; i <= m_hn->GetListOfAxes()->GetLast(); ++i) {
		TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->At(i);
		bool kAxisRange = axis->TestBit(TAxis::kAxisRange);
		ranges.emplace_back(kAxisRange ? axis->GetFirst() : 0, kAxisRange ? axis->GetLast() : -1);
	}
	return ranges;
}

TString PhysicsContribution::getSelectionString() const {
	TString rangeString;
	
	auto ranges = getRanges();
	for(size_t i = 0; i < ranges.size(); ++i) {
		TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->At(i);
		auto lo = ranges[i].first;
		auto hi = ranges[i].second;
		
		auto edgeLo = axis->GetBinLowEdge(lo);
		auto edgeHi = axis->GetBinUpEdge(hi);
		
		// Check whether we have integer bins and unity width selection
		bool oneBin = (edgeHi - edgeLo == 1 && fabs(floor(edgeHi + 0.5) - edgeHi) < 1e-6);
		
		const char* title = axis->GetTitle();
		
		if(hi < lo) {
			continue;
		}
		
		if(rangeString.Length()) {
			rangeString += " && ";
		}
		
		if(hi == axis->GetNbins() + 1) {
			rangeString += TString::Format("%s >= %.0f", title, axis->GetBinLowEdge(lo));
		} else if(oneBin) {
			rangeString += TString::Format("%s == %.0f", title, axis->GetBinLowEdge(lo));
		} else {
			rangeString += TString::Format("(%s >= %.0f && %s < %.0f)", title, edgeLo, title, edgeHi);
		}
	}
	
	if(rangeString.Length() == 0) {
		return m_selection;
	} else if(m_selection.Length() == 0) {
		return rangeString;
	}
	
	return "(" + m_selection + ") * (" + rangeString + ")";
}

std::map<TString, std::pair<TString, THnBase*>> PhysicsContribution::getUncertaintyMap() const {
	return m_uncertaintyMap;
}

bool PhysicsContribution::isMC() const {
	return m_MC;
}

void PhysicsContribution::print(int level) const {
	std::string prefix = std::string(2 * level, ' ');
	cout << prefix << getName() << " (" << m_filename << ", " << m_treeRname << ")" << endl;
}

BaseBundleProjection* PhysicsContribution::project(const char* varName, const bool binForOverflow) const {
	double zerostat = (m_type == "backgroundDD") ? 0.05 : 1;
	
	PhysicsContributionProjection* projection = new PhysicsContributionProjection(this, varName, zerostat);
	
	if(binForOverflow) {
		projection->incorporateOverflow();
	}
	
	projection->scale(m_scale);
	
	if(m_fillColor >= 0) {
		projection->getHistogram()->SetFillColor(m_fillColor);
	}
	
	return projection;
}

bool PhysicsContribution::setDebug(bool debug) {
	bool oldDebug = m_debug;
	m_debug = debug;
	return oldDebug;
}

void PhysicsContribution::setEnsembleFakeRateParam(PhysicsContribution* contribution, TString varName, TString formula) {
	if(getType(true) != "backgroundDD") {
		throw std::runtime_error("ensemble fake rates are meant for data-driven backgrounds only");
	}
	
	if(m_ensembleFakeRateParams.find(contribution) == m_ensembleFakeRateParams.end()) {
		m_ensembleFakeRateParams.insert(make_pair(contribution, std::map<TString, TString>()));
	}
	
	if(m_ensembleFakeRateParams[contribution].find(varName) != m_ensembleFakeRateParams[contribution].end()) {
		cout << "Warning: Overwriting ensemble fake rate parametrization for variable " << varName << endl;
	}
	m_ensembleFakeRateParams[contribution].insert(make_pair(varName, formula));
}

void PhysicsContribution::setFakeRate(TString name, TString f) {
	if(isData() && f != "0") {
		cerr << "Notice: Ignoring request to apply fake rate to data sample\n";
		f = "0";
	}
	
	if(m_fakerateMap.find(name) != m_fakerateMap.end()) {
		cout << "Warning: Changing fake rate " << name << " from " << m_fakerateMap[name] << " to " << f << endl;
		m_fakerateMap[name] = f;
	} else {
		m_fakerateMap.insert(make_pair(name, f));
	}
}

void PhysicsContribution::setNominalWeight(TString nominalWeight) {
	if(!isMC()) {
		throw std::runtime_error("Nominal weight branch can only be set for MC contributions");
	}
	
	m_nominalWeight = nominalWeight;
}

bool PhysicsContribution::setRange(const char* name, double lo, double hi, bool includeLast) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "setRange: Could not find axis " << name << endl;
		return false;
	}
	
	Int_t first = findBinFromLowEdge(axis, lo);
	Int_t last  = findBinFromLowEdge(axis, hi);
	if(!includeLast) {
		--last;
	}
	
	if(last > axis->GetNbins()) {
		cerr << "Error: attempt to set " << name << " upper boundary to overflow bin. If intended, omit upper boundary." << endl;
		throw std::runtime_error("invalid axis range");
	}
	
	if(first > last) {
		cerr << "Error: attempt to set " << name << " upper boundary below lower boundary." << endl;
		throw std::runtime_error("invalid axis range");
	}
	
	axis->SetRange(first, last);
	if(m_hnAbs) {
		((TAxis*)m_hnAbs->GetListOfAxes()->FindObject(name))->SetRange(first, last);
	}
	for(auto &uncertainty : m_uncertaintyMap) {
		((TAxis*)uncertainty.second.second->GetListOfAxes()->FindObject(name))->SetRange(first, last);
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
	Int_t first = findBinFromLowEdge(axis, lo);
	Int_t last  = axis->GetNbins() + 1;
	
	axis->SetRange(first, last);
	if(m_hnAbs) {
		((TAxis*)m_hnAbs->GetListOfAxes()->FindObject(name))->SetRange(first, last);
	}
	for(auto &uncertainty : m_uncertaintyMap) {
		((TAxis*)uncertainty.second.second->GetListOfAxes()->FindObject(name))->SetRange(first, last);
	}
	
	return true;
}

bool PhysicsContribution::setRange(const char* name) {
	TAxis* axis = (TAxis*)m_hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "setRange: Could not find axis " << name << endl;
		return false;
	}
	
	axis->SetRange();
	if(m_hnAbs) {
		((TAxis*)m_hnAbs->GetListOfAxes()->FindObject(name))->SetRange();
	}
	for(auto &uncertainty : m_uncertaintyMap) {
		((TAxis*)uncertainty.second.second->GetListOfAxes()->FindObject(name))->SetRange();
	}
	
	return true;
}

bool PhysicsContribution::setRange() {
	m_hn->GetListOfAxes()->R__FOR_EACH(TAxis, SetRange)();
	if(m_hnAbs) {
		m_hnAbs->GetListOfAxes()->R__FOR_EACH(TAxis, SetRange)();
	}
	for(auto &uncertainty : m_uncertaintyMap) {
		uncertainty.second.second->GetListOfAxes()->R__FOR_EACH(TAxis, SetRange)();
	}
	
	return true;
}

void PhysicsContribution::setRanges(std::vector<std::pair<int, int>> ranges) {
	for(auto &hn : {m_hn, m_hnAbs}) {
		if(!hn) {
			continue;
		}
		assert((int)ranges.size() == hn->GetListOfAxes()->GetLast() + 1);
		for(size_t i = 0; i < ranges.size(); ++i) {
			TAxis* axis = (TAxis*)hn->GetListOfAxes()->At(i);
			axis->SetRange(ranges[i].first, ranges[i].second);
			for(auto &uncertainty : m_uncertaintyMap) {
				axis = (TAxis*)uncertainty.second.second->GetListOfAxes()->At(i);
				axis->SetRange(ranges[i].first, ranges[i].second);
			}
		}
	}
}
