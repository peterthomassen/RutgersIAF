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

Assembler::Assembler(TString outfileName, Option_t* options) {
	if(outfileName.Length()) {
		m_outfile = new TFile(outfileName.Data(), options);
		if(!m_outfile->IsOpen()) {
			throw std::runtime_error("Could not open output file");
		}
	}
}

Assembler::~Assembler() {
	cout << "Running Assembler destructor ...";
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

std::pair<double, std::pair<double, double>> Assembler::getBin(TString type, int i) {
	std::pair<double, std::pair<double, double>> value;
	if(m_hsProjections[type].first) {
		TH1D* h = (TH1D*)m_hsProjections[type].first->GetStack()->Last();
		value.first = h->GetBinContent(i);
		value.second.first = h->GetBinError(i);
		if(m_hsProjections[type].second->GetStack()) {
			value.second.second = ((TH1D*)m_hsProjections[type].second->GetStack()->Last())->GetBinContent(i);
		}
	}
	return value;
}

double Assembler::getLumi() const {
	double lumi = 0;
	for(const auto &contribution : m_data) {
		lumi += contribution->getLumi();
	}
	return lumi;
}

void Assembler::print(const char* name, const bool binForOverflow) {
	project(name, binForOverflow);
	
	double sumData = 0;
	double sumBackground = 0;
	double sumBackgroundStat2 = 0;
	double sumBackgroundSyst = 0;
	double sumSignal = 0;
	double sumSignalStat2 = 0;
	double sumSignalSyst = 0;
	//cout << "data entries: " << m_hProjections["data"].begin()->first->GetEntries() << endl;
	//cout << "data integral: " << m_hProjections["data"].begin()->first->Integral() << endl;
	//cout << "data integral w/ overflow: " << m_hProjections["data"].begin()->first->Integral(0, m_hProjections["data"].begin()->first->GetNbinsX() + 1) << endl;
	for(int i = 1; i <= m_hProjections["data"].begin()->first->GetNbinsX(); ++i) {
		double lo = m_hProjections["data"].begin()->first->GetXaxis()->GetBinLowEdge(i);
		double hi = m_hProjections["data"].begin()->first->GetXaxis()->GetBinUpEdge(i);
		
		double contentData = getBin("data", i).first;
		sumData += contentData;
		
		auto background = getBin("background", i);
		double contentBackground = background.first;
		double contentBackgroundStat = background.second.first;
		double contentBackgroundSyst = background.second.second;
		sumBackground += contentBackground;
		sumBackgroundStat2 += contentBackgroundStat*contentBackgroundStat;
		sumBackgroundSyst += contentBackgroundSyst;
		
		if(i < m_hProjections["data"].begin()->first->GetNbinsX() || !binForOverflow) {
			cout << name << " " << (int)lo << "-" << (int)hi;
		} else {
			cout << name << " " << (int)lo << "-" << "inf";
		}
		if(contentBackground > 5) {
			printf("	%.0f : %.2f ± %.2f ± %.2f ± %.2f", contentData, contentBackground, sqrt(contentBackground), contentBackgroundStat, contentBackgroundSyst);
		} else {
			printf("	%.0f : %.2f ± n/a ± %.2f ± %.2f", contentData, contentBackground, contentBackgroundStat, contentBackgroundSyst);
		}
		
		if(m_hsProjections["signal"].first) {
			auto signal = getBin("signal", i);
			double contentSignal = signal.first;
			double contentSignalStat = signal.second.first;
			double contentSignalSyst = signal.second.second;
			sumSignal += contentSignal;
			sumSignalStat2 += contentSignalStat*contentSignalStat;
			sumSignalSyst += contentSignalSyst;
			
			printf(" : %.2f ± %.2f ± %.2f", contentSignal, contentSignalStat, contentSignalSyst);
		}
		cout << endl;
	}
	if(sumBackground > 5) {
		printf("Sum:		%.0f : %.2f ± %.2f ± %.2f ± %.2f", sumData, sumBackground, sqrt(sumBackground), sqrt(sumBackgroundStat2), sumBackgroundSyst);
	} else {
		printf("Sum:		%.0f : %.2f ± n/a ± %.2f ± %.2f", sumData, sumBackground, sqrt(sumBackgroundStat2), sumBackgroundSyst);
	}
	if(m_hsProjections["signal"].first) {
		printf(" : %.2f ± %.2f ± %.2f", sumSignal, sqrt(sumSignalStat2), sumSignalSyst);
	}
	cout << endl;
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
		contribution->fillContent(hs, varexp, selection);
	}
	delete hs;
}

void Assembler::project(const char* name, const bool binForOverflow) {
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
	
	for(auto &hs : m_hsProjections) {
		delete hs.second.first;
		delete hs.second.second;
	}
	m_hsProjections.clear();
	
	// Project event counts and uncertainty histograms
	auto contributionsModel = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsModel)) {
		if(m_hProjections.find(contribution->getType()) == m_hProjections.end()) {
			m_hProjections.insert(make_pair(contribution->getType(), std::map<TH1D*, std::map<TString, TH1D*> >()));
		}
		
		double scale = contribution->isData() ? 1 : (getLumi() / contribution->getLumi());
		m_hProjections[contribution->getType()].insert(contribution->project(dim, scale, binForOverflow));
	}
	
	// Prepare projections for output
	std::map<TString, std::vector<std::pair<TH1D*, double>>> vh;
	for(const auto &typeProjection : m_hProjections) {
		// Prepare vector of contributions for sorting, and take care of error correlations
		std::vector<std::pair<TH1D*, double>> vh;
		THStack* hsUncertainties = new THStack("hsUncertainties", m_varexp + TString(" {") + m_selection + TString("}"));
		for(const auto &contribution : typeProjection.second) {
			vh.push_back(make_pair(contribution.first, contribution.first->Integral()));
			
			for(const auto &uncertainty : contribution.second) {
				TH1D* hUncertainty = (TH1D*)hsUncertainties->FindObject(uncertainty.first);
				if(hUncertainty) {
					for(int i = 1; i <= hUncertainty->GetNbinsX(); ++i) {
						double value = hUncertainty->GetBinContent(i);
						value = sqrt(value*value + pow(uncertainty.second->GetBinContent(i), 2));
						hUncertainty->SetBinContent(i, value);
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
		
		THStack* hs = new THStack("hs", m_varexp + TString(" {") + m_selection + TString("}"));
		for(const auto &contribution : vh) {
			hs->Add(contribution.first);
		}
		
		m_hsProjections.insert(make_pair(typeProjection.first, make_pair(hs, hsUncertainties)));
	}
}

void Assembler::save() {
	m_outfile->cd();
	cerr << "Currently only saving THn of first data file" << endl;
	m_data[0]->getContent()->Write("data");
	m_outfile->Flush();
}

void Assembler::save(const char* name, const bool binForOverflow) {
	project(name, binForOverflow);
	
	m_outfile->cd();
	if(m_hsProjections["data"].first) {
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
	m_outfile->Flush();
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
