#include <assert.h>

#include "TAxis.h"
#include "TFile.h"
#include "TH1D.h"
#include "THnBase.h"
#include "THnSparse.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TPRegexp.h"

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/range/join.hpp>
#include <boost/tokenizer.hpp>
#include <exception>

#include "RutgersIAF2012/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(Assembler)

Assembler::Assembler() {
	/* no-op */
}

Assembler::Assembler(TString outfileName, Option_t* options) {
	if(outfileName.Length()) {
		m_outfile = new TFile(outfileName.Data(), options);
		if(!m_outfile->IsOpen()) {
			throw std::runtime_error("Could not open output file");
		}
	}
}

Assembler::~Assembler() {
	cout << "Saving output file ...";
	if(m_outfile) {
		m_outfile->Close();
		delete m_outfile;
	}
	cout << " done." << endl;
}

void Assembler::addContribution(PhysicsContribution* contribution) {
	if(contribution->isData()) {
		m_data.push_back(contribution);
	} else if(contribution->isBackground()) {
		m_background.push_back(contribution);
	} else if(contribution->isSignal()) {
		m_signal.push_back(contribution);
	} else {
		throw std::runtime_error("Unable to handle contribution");
	}
}

void Assembler::addWeight(TString varexp, TString type) {
	for(auto &contribution : boost::join(m_background, m_signal)) {
		contribution->addWeight(varexp, type);
	}
}

double Assembler::getLumi() const {
	double lumi = 0;
	for(const auto &contribution : m_data) {
		lumi += contribution->getLumi();
	}
	return lumi;
}

void Assembler::process(std::string varexp, TString selection) {
	std::vector<TString> varNames;
	std::vector<double> rangeMin, rangeMax;
	std::vector<int> nbins;
	
	cout << varexp << endl;
	boost::char_separator<char> sep(":");
	boost::tokenizer<boost::char_separator<char> > tokens(varexp, sep);
	BOOST_FOREACH(const string& t, tokens) {
		TObjArray* matches = TPRegexp("^([^{}]+)\\{ *([0-9]+(\\.[0-9]+)?) *, *([0-9]+(\\.[0-9]+)?) *(, *([0-9]+) *)?\\}").MatchS(t.c_str());
		if(matches->GetLast() < 0) {
			cerr << "Invalid variable specification: " << t << endl;
			return;
		}
		TString var = ((TObjString*)matches->At(1))->GetString();
		Double_t min = ((TObjString*)matches->At(2))->GetString().Atof();
		Double_t max = ((TObjString*)matches->At(4))->GetString().Atof();
		Int_t bins = (matches->GetLast() == 7)
			? ((TObjString *)matches->At(7))->GetString().Atoi()
			: (max - min);
		varNames.push_back(var);
		rangeMin.push_back(min);
		rangeMax.push_back(max);
		nbins.push_back(bins);
		delete matches;
	}
	varexp = varNames[0];
	for(size_t i = 1; i < varNames.size(); ++i) {
		varexp += ":" + varNames[i];
	}
	cout << varexp << endl;
	
	m_varexp = varexp;
	m_selection = selection;
	
	THnSparse* hs = new THnSparseD("hSparse", varexp.c_str(), varNames.size(), &nbins[0], &rangeMin[0], &rangeMax[0]);
	hs->Sumw2();
	for(size_t i = 0; i < varNames.size(); ++i) {
		hs->GetAxis(i)->SetName(varNames[i]);
		hs->GetAxis(i)->SetTitle(varNames[i]);
	}
	
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		double scale = contribution->isData() ? 1 : (getLumi() / contribution->getLumi());
		contribution->fillContent(hs, varexp, selection, scale);
	}
	delete hs;
}

Projection* Assembler::project(const char* name, const bool binForOverflow) {
	TAxis* axis = (TAxis*)m_data[0]->getContent()->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "Could not find axis " << name << endl;
		throw std::runtime_error("");
	}
	int dim = m_data[0]->getContent()->GetListOfAxes()->IndexOf(axis);
	
	// Clean up from earlier projections
	for(auto &h : m_hProjections) {
		for(auto &h2 : h.second) {
			delete h2.first;
			for(auto &h3 : h2.second) {
				delete h3.second;
			}
			h2.second.clear();
		}
		h.second.clear();
	}
	m_hProjections.clear();
	
	delete m_projection;
	
	// Project event counts and uncertainty histograms
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		if(m_hProjections.find(contribution->getType()) == m_hProjections.end()) {
			m_hProjections.insert(make_pair(contribution->getType(), std::vector<std::pair<TH1D*, std::map<TString, TH1D*>>>()));
		}
		
		m_hProjections[contribution->getType()].push_back(contribution->project(dim, binForOverflow));
	}
	
	// Prepare projection for output: Combine correlated uncertainties and assemble contributions into histogram stack
	m_projection = new Projection(name, binForOverflow);
	std::map<TString, std::vector<std::pair<TH1D*, double>>> vh;
	for(const auto &typeProjection : m_hProjections) {
		// Prepare vector of contributions for sorting, and take care of error correlations
		std::vector<std::pair<TH1D*, double>> vh;
		unsigned int i = 2;
		THStack* hsUncertainties = new THStack("hsUncertainties", m_varexp + TString(" {") + m_selection + TString("}"));
		for(const auto &contribution : typeProjection.second) {
			contribution.first->SetFillColor(i);
			++i;
			vh.push_back(make_pair(contribution.first, contribution.first->Integral()));
			
			for(const auto &uncertainty : contribution.second) {
				TH1D* hUncertainty = (TH1D*)hsUncertainties->FindObject(uncertainty.first);
				if(hUncertainty) {
					for(int j = 1; j <= hUncertainty->GetNbinsX(); ++j) {
						double value = hUncertainty->GetBinContent(j);
						value = sqrt(value*value + pow(uncertainty.second->GetBinContent(j), 2));
						hUncertainty->SetBinContent(j, value);
					}
				} else {
					hsUncertainties->Add(uncertainty.second);
				}
			}
		}
		
		// Sort by amount of contribution
		std::sort(vh.begin()
			, vh.end()
			, boost::bind(&std::pair<TH1D*, double>::second, _1) < boost::bind(&std::pair<TH1D*, double>::second, _2)
		);
		
		// Prepare stack
		THStack* hs = new THStack("hs", m_varexp + TString(" {") + m_selection + TString("}"));
		for(const auto &contribution : vh) {
			hs->Add(contribution.first);
		}
		
		m_projection->add(typeProjection.first, hs, hsUncertainties);
	}
	
	return m_projection;
}

void Assembler::save() {
	m_outfile->cd();
	cerr << "Currently only saving THn of first data file" << endl;
	m_data[0]->getContent()->Write("data");
	this->Write("assembler");
	m_outfile->Flush();
}

void Assembler::save(const char* name, const bool binForOverflow) {
	project(name, binForOverflow);
	
	m_outfile->cd();
/*	if(m_hsProjections["data"].first) {
		m_hsProjections["data"].first->Write(TString(name) + TString("_data"));
		m_hsProjections["data"].second->Write(TString(name) + TString("_dataSyst"));
	}
	if(m_hsProjections["background"].first) {
		m_hsProjections["background"].first->Write(TString(name) + TString("_background"));
		m_hsProjections["background"].second->Write(TString(name) + TString("_backgroundSyst"));
	}
	if(m_hsProjections["signal"].first) {
		m_hsProjections["signal"].first->Write(TString(name) + TString("_signal"));
		m_hsProjections["signal"].second->Write(TString(name) + TString("_signalSyst"));
	}
*/	m_outfile->Flush();
}

void Assembler::setDebug(bool debug) {
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		contribution->setDebug(debug);
	}
}

void Assembler::setFakeRate(TString name, TString f) {
	for(auto &contribution : m_background) {
		contribution->setFakeRate(name, f);
	}
	// Declare fake rate so that PhysicsContribution::fillContent() knows how to skip events that have fake proxies
	for(auto &contribution : boost::join(m_data, m_signal)) {
		contribution->setFakeRate(name, "0");
	}
}

void Assembler::setRange(const char* name, double lo, double hi, bool includeLast) {
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		contribution->setRange(name, lo, hi, includeLast);
	}
}

void Assembler::setRange(const char* name, double lo) {
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		contribution->setRange(name, lo);
	}
}

void Assembler::setRange(const char* name) {
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		contribution->setRange(name);
	}
}

void Assembler::setRange() {
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		contribution->setRange();
	}
}
