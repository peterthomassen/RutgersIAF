#include <assert.h>

#include "TAxis.h"
#include "TFile.h"
#include "TFormula.h"
#include "TH1D.h"
#include "THnBase.h"
#include "THnSparse.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TPRegexp.h"

#include <boost/foreach.hpp>
#include <boost/range/join.hpp>
#include <boost/tokenizer.hpp>
#include <exception>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/AssemblerProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "RutgersIAF/debug.h"

using namespace std;

ClassImp(Assembler)

Assembler::Assembler(TString outfileName, Option_t* options) {
	if(outfileName.Length()) {
		m_outfile = new TFile(outfileName.Data(), options);
		if(!m_outfile->IsOpen()) {
			throw std::runtime_error("Could not open output file");
		}
	}
}

Assembler::~Assembler() {
	if(m_outfile) {
		cout << "Saving output file ...";
		m_outfile->Close();
		delete m_outfile;
		cout << " done." << endl;
	}
}

void Assembler::addContribution(PhysicsContribution* contribution) {
	if(contribution->isData()) {
		if(std::find(m_contributions["data"].begin(), m_contributions["data"].end(), contribution) != m_contributions["data"].end()) {
			cerr << "Cannot add " << contribution->getType() << " contribution " << contribution->getName() << " twice" << endl;
			throw std::runtime_error("Unable to handle contribution");
		}
		m_contributions["data"].push_back(contribution);
	} else if(contribution->isBackground()) {
		if(std::find(m_contributions["background"].begin(), m_contributions["background"].end(), contribution) != m_contributions["background"].end()) {
			cerr << "Cannot add " << contribution->getType() << " contribution " << contribution->getName() << " twice" << endl;
			throw std::runtime_error("Unable to handle contribution");
		}
		if(contribution->getFillColor() < 0) {
			contribution->setFillColor(2 + m_contributions["background"].size());
		}
		m_contributions["background"].push_back(contribution);
	} else if(contribution->isSignal()) {
		if(std::find(m_contributions["signal"].begin(), m_contributions["signal"].end(), contribution) != m_contributions["signal"].end()) {
			cerr << "Cannot add " << contribution->getType() << " contribution " << contribution->getName() << " twice" << endl;
			throw std::runtime_error("Unable to handle contribution");
		}
		m_contributions["signal"].push_back(contribution);
	} else {
		throw std::runtime_error("Unable to handle contribution");
	}
}

void Assembler::addBundle(Bundle* bundle) {
	if(m_bundles.find(bundle->getName()) != m_bundles.end()) {
		cerr << "There is already a bundle with name " << bundle->getName() << " declared to the assembler" << endl;
		throw std::runtime_error("Unable to handle bundle");
	}
	m_bundles.insert(make_pair(bundle->getName(), bundle));
}

Channel* Assembler::channel(const char* name) {
	return new Channel(this, name);
}

Bundle* Assembler::getBundle(TString name) const {
	return (m_bundles.find(name) != m_bundles.end())
		? m_bundles.at(name)
		: 0;
}

Bundle* Assembler::getDefaultBundle() const {
	return m_defaultBundle;
}

std::vector<PhysicsContribution*> Assembler::getPhysicsContributions(TString type) const {
	return m_contributions.at(type);
}

double Assembler::getLumi() const {
	double lumi = 0;
	for(const auto &contribution : m_contributions.at("data")) {
		lumi += contribution->getLumi();
	}
	return lumi;
}

std::vector<std::pair<int, int>> Assembler::getRanges() const {
	return m_contributions.at("data")[0]->getRanges();
}

TString Assembler::getVarExp() const {
	return m_varexp;
}

TString Assembler::getVarName(TString name) const {
	auto pair = m_vars.find(name);
	if(pair == m_vars.end()) {
		cout << "invalid variable name " << name << endl;
		throw std::runtime_error("");
	}
	return pair->second;
}

TString Assembler::getSelection() const {
	return m_selection;
}

void Assembler::process(std::string varexp, TString selection) {
	std::vector<TString> variables;
	std::vector<TString> names;
	std::vector<double> rangeMin, rangeMax;
	std::vector<int> nbins;
	
	cout << varexp << endl;
	m_vars.clear();
	
	// Add axis "_" with just one bin for everything. This is to allow integration 
	// while respecting cuts (setRange()) by means of projection on this axis.
	// Used by the channel code.
	varexp += ":0{-0.5,0.5,1,\"_\"}";
	boost::char_separator<char> sep(":");
	boost::tokenizer<boost::char_separator<char> > tokens(varexp, sep);
	BOOST_FOREACH(const string& t, tokens) {
		TObjArray* matches = TPRegexp("^([^{}]+)\\{ *(-?[0-9]+(\\.[0-9]+)?) *, *(-?[0-9]+(\\.[0-9]+)?) *(, *([0-9]+) *)? *(, *\"([^\"]+)\" *)?\\}").MatchS(t.c_str());
		if(matches->GetLast() < 0) {
			cerr << "was processing " << t << endl;
			throw std::runtime_error("invalid variable specification");
		}
		TString var = ((TObjString*)matches->At(1))->GetString();
		Double_t min = ((TObjString*)matches->At(2))->GetString().Atof();
		Double_t max = ((TObjString*)matches->At(4))->GetString().Atof();
		Int_t bins = (matches->GetLast() >= 7 && ((TObjString*)matches->At(7))->GetString().Length() > 0)
			? ((TObjString*)matches->At(7))->GetString().Atoi()
			: (max - min);
		TString name = (matches->GetLast() >= 9)
			? ((TObjString*)matches->At(9))->GetString()
			: var;
		if(m_vars.find(name) == m_vars.end()) {
			m_vars.insert(make_pair(name, var));
		} else {
			cout << "was processing " << t << endl;
			throw std::runtime_error("duplicate variable name");
		}
		variables.push_back(var);
		names.push_back(name);
		rangeMin.push_back(min);
		rangeMax.push_back(max);
		nbins.push_back(bins);
		delete matches;
	}
	varexp = variables[0];
	for(size_t i = 1; i < variables.size(); ++i) {
		varexp += ":" + variables[i];
	}
	cout << varexp << endl;
	
	m_varexp = varexp;
	m_selection = selection;
	
	THnSparse* hs = new THnSparseD("hSparse", varexp.c_str(), variables.size(), &nbins[0], &rangeMin[0], &rangeMax[0]);
	hs->Sumw2();
	for(size_t i = 0; i < variables.size(); ++i) {
		hs->GetAxis(i)->SetName(names[i]);
		hs->GetAxis(i)->SetTitle(variables[i]);
	}
	
	auto contributionsModel = boost::join(m_contributions["background"], m_contributions["signal"]);
	for(auto &contribution : boost::join(m_contributions["data"], contributionsModel)) {
		double scale = contribution->isData() ? 1 : (getLumi() / contribution->getLumi());
		contribution->fillContent(hs, varexp, selection, scale);
	}
	delete hs;
}

AssemblerProjection* Assembler::project(const char* name, const bool binForOverflow) {
	AssemblerProjection* projection = new AssemblerProjection(this, name, binForOverflow);
	if(getDefaultBundle()) {
		projection = projection->bundle(getDefaultBundle());
	}
	return projection;
}

void Assembler::save() {
	m_outfile->cd();
	cerr << "Currently only saving THn of first data file" << endl;
	m_contributions["data"][0]->getContent()->Write("data");
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
	auto contributionsModel = boost::join(m_contributions["background"], m_contributions["signal"]);
	for(auto &contribution : boost::join(m_contributions["data"], contributionsModel)) {
		contribution->setDebug(debug);
	}
}

Bundle* Assembler::setDefaultBundle(Bundle* bundle) {
	Bundle* prev = getDefaultBundle();
	m_defaultBundle = bundle;
	return prev;
}

void Assembler::setFakeRate(TString name, TString f) {
	for(auto &contribution : m_contributions["background"]) {
		contribution->setFakeRate(name, f);
	}
	// Declare fake rate so that PhysicsContribution::fillContent() knows how to skip events that have fake proxies
	for(auto &contribution : boost::join(m_contributions["data"], m_contributions["signal"])) {
		contribution->setFakeRate(name, "0");
	}
}

void Assembler::setRange(const char* name, double lo, double hi, bool includeLast) {
	auto contributionsModel = boost::join(m_contributions["background"], m_contributions["signal"]);
	for(auto &contribution : boost::join(m_contributions["data"], contributionsModel)) {
		contribution->setRange(name, lo, hi, includeLast);
	}
}

void Assembler::setRange(const char* name, double lo) {
	auto contributionsModel = boost::join(m_contributions["background"], m_contributions["signal"]);
	for(auto &contribution : boost::join(m_contributions["data"], contributionsModel)) {
		contribution->setRange(name, lo);
	}
}

void Assembler::setRange(const char* name) {
	auto contributionsModel = boost::join(m_contributions["background"], m_contributions["signal"]);
	for(auto &contribution : boost::join(m_contributions["data"], contributionsModel)) {
		contribution->setRange(name);
	}
}

void Assembler::setRange() {
	auto contributionsModel = boost::join(m_contributions["background"], m_contributions["signal"]);
	for(auto &contribution : boost::join(m_contributions["data"], contributionsModel)) {
		contribution->setRange();
	}
}

void Assembler::setRanges(std::vector<std::pair<int, int>> ranges) {
	auto contributionsModel = boost::join(m_contributions["background"], m_contributions["signal"]);
	for(auto &contribution : boost::join(m_contributions["data"], contributionsModel)) {
		contribution->setRanges(ranges);
	}
}
