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
		m_data.push_back(contribution);
	} else if(contribution->isBackground()) {
		if(contribution->getFillColor() < 0) {
			contribution->setFillColor(2 + m_background.size());
		}
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
	std::vector<TString> variables;
	std::vector<TString> names;
	std::vector<double> rangeMin, rangeMax;
	std::vector<int> nbins;
	
	cout << varexp << endl;
	m_vars.clear();
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
	
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		double scale = contribution->isData() ? 1 : (getLumi() / contribution->getLumi());
		contribution->fillContent(hs, varexp, selection, scale);
	}
	delete hs;
}

AssemblerProjection* Assembler::project(const char* name, const bool binForOverflow) {
	// Clean up from earlier projections
	for(auto &typeProjection : m_hProjections) {
		for(auto &projection : typeProjection.second) {
			delete projection;
		}
		typeProjection.second.clear();
	}
	m_hProjections.clear();
	delete m_projection;
	
	// Project event counts and uncertainty histograms
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		if(m_hProjections.find(contribution->getType()) == m_hProjections.end()) {
			m_hProjections.insert(make_pair(contribution->getType(), std::vector<PhysicsContributionProjection*>()));
		}
		
		m_hProjections[contribution->getType()].push_back(contribution->project(name, binForOverflow));
	}
	
	// Ensemble-based scaling of data-driven backgrounds
	for(auto &projectionDD : m_hProjections["background"]) {
		// Fetch the PhysicsContribution object from which this data-driven predition was computed
		const PhysicsContribution* contribution = projectionDD->getPhysicsContribution();
		if(contribution->getType(true) != "backgroundDD") {
			continue;
		}
		
		for(const auto &params : contribution->getEnsembleFakeRateParams()) {
			// Determine which variable to use
			// TODO Add support for looking at two different variables (à la Rdxy)
			for(const auto &params2 : params.second) {
				TString varName = params2.first;
				
				// Get counts from both contributions and compute scale factor
				// TODO one could use the integral, momentum, ... instead
				double x = contribution->project(varName, true, true)->getHistogram()->GetEntries();
				double par = params.first->project(varName, true, true)->getHistogram()->GetEntries();
				
				TFormula* f = new TFormula("", params2.second);
				f->SetParameter(0, par);
				double scale = f->Eval(x);
				if(scale < 0) {
					throw std::runtime_error("scale turns out negative; please fix your ensemble fake rate parameterization");
				}
				cout << "Scaling " << contribution->getName() << " by " << scale << " based on " << params.first->getName() << " " << varName << " [" << x << "/" << par << "=" << (x/par) << "]" << endl;
				projectionDD->scale(f->Eval(x));
				delete f;
			}
		}
	}
	
	// Prepare projection for output: Put projections together
	m_projection = new AssemblerProjection(name, m_vars[name], binForOverflow);
	for(const auto &typeProjection : m_hProjections) {
		m_projection->add(typeProjection, m_varexp, m_selection);
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
