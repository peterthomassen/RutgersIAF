#include <assert.h>

#include "TAxis.h"
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

#include "RutgersIAF2012/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(Assembler)

Assembler::Assembler(TString ofname) {
	m_ofname = ofname;
}

Assembler::~Assembler() {
	/* no-op */
}

void Assembler::addContribution(PhysicsContribution* contribution) {
	if(contribution->isData()) {
		if(m_data.size() > 0) {
			throw std::runtime_error("More than one data input file not supported.");
		}
		m_data.push_back(contribution);
	} else if(contribution->isBackground()) {
		m_background.push_back(contribution);
	} else if(contribution->isSignal()) {
		m_signal.push_back(contribution);
	} else {
		throw std::runtime_error("Unable to handle contribution");
	}
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
	
	THnSparse* hs = new THnSparseD("hSparse", varexp.c_str(), varNames.size(), &nbins[0], &rangeMin[0], &rangeMax[0]);
	hs->Sumw2();
	for(size_t i = 0; i < varNames.size(); ++i) {
		hs->GetAxis(i)->SetName(varNames[i]);
		hs->GetAxis(i)->SetTitle(varNames[i]);
	}
	
	auto contributionsMC = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsMC)) {
		contribution->fillTHn(hs, varexp, selection);
	}
	delete hs;
}

void Assembler::setFakeRate(TString name, double f) {
	for(auto &contribution : m_data) {
		contribution->setFakeRate(name, 0);
	}
	for(auto &contribution : m_background) {
		contribution->setFakeRate(name, f);
	}
}

void Assembler::setRange(const char* name, double lo, double hi, bool includeLast) {
	auto contributionsMC = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsMC)) {
		contribution->setRange(name, lo, hi, includeLast);
	}
}

void Assembler::setRange(const char* name, double lo) {
	auto contributionsMC = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsMC)) {
		contribution->setRange(name, lo);
	}
}

void Assembler::setRange(const char* name) {
	auto contributionsMC = boost::join(m_background, m_signal);
	for(auto &contribution : boost::join(m_data, contributionsMC)) {
		contribution->setRange(name);
	}
}

void Assembler::write(const char* name) {
	TAxis* axis = (TAxis*)m_data[0]->getTHn()->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "Could not find axis " << name << endl;
		exit(1);
	}
	
	int dim = m_data[0]->getTHn()->GetListOfAxes()->IndexOf(axis);
	TH1D* hData = m_data[0]->getTHn()->Projection(dim, "E");
	//hData->Draw();
	
	TH1D* hBackground = (TH1D*)hData->Clone();
	hBackground->Reset();
	for(auto &contribution : m_background) {
		TH1D* hContribution = contribution->getTHn()->Projection(dim, "E");
		double scale = m_data[0]->getLumi() / contribution->getLumi();
		hBackground->Add(hContribution, scale);
	}
	
	double sumData = 0;
	double sumBackground = 0;
	double sumBackgroundUnc2 = 0;
	for(int i = 1; i <= hData->GetNbinsX(); ++i) {
		double contentData = hData->GetBinContent(i);
		double contentBackground = hBackground->GetBinContent(i);
		double uncBackground = hBackground->GetBinError(i);
		double lo = hData->GetXaxis()->GetBinLowEdge(i);
		double hi = hData->GetXaxis()->GetBinUpEdge(i);
		if(i < hData->GetNbinsX()) {
			printf("%s %d-%d	%d : %.2f ± %.2f\n", name, (int)lo, (int)hi, (int)contentData, contentBackground, uncBackground);
		} else {
			contentData += hData->GetBinContent(i + 1);
			contentBackground += hBackground->GetBinContent(i + 1);
			printf("%s %d-inf	%d : %.2f ± %.2f\n", name, (int)lo, (int)contentData, contentBackground, uncBackground);
		}
		sumData += contentData;
		sumBackground += contentBackground;
		sumBackgroundUnc2 += uncBackground * uncBackground;
	}
	printf("Sum: %.2f : %.2f ± %.2f\n", sumData, sumBackground, sqrt(sumBackgroundUnc2));
	
	delete hData;
}
