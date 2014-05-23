#include <assert.h>

#include "TAxis.h"
#include "TH1D.h"
#include "THnBase.h"
#include "THnSparse.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TPRegexp.h"

#ifndef __CINT__
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#endif

#include "RutgersIAF2012/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(Assembler)

Assembler::Assembler(TString ofname) {
	m_ofname = ofname;
}

Assembler::~Assembler() {
	/* no-op atm*/
}

bool Assembler::addData(PhysicsContribution* pc) {
	m_data.push_back(pc);
	return true;
}

THnBase* Assembler::process(std::string varexp, std::string selection) {
	std::vector<TString> varNames;
	std::vector<double> rangeMin, rangeMax;
	std::vector<int> nbins;
	
#ifndef __CINT__
	cout << varexp << endl;
	boost::char_separator<char> sep(":");
	boost::tokenizer<boost::char_separator<char> > tokens(varexp, sep);
	BOOST_FOREACH(const string& t, tokens) {
		TObjArray* matches = TPRegexp("^([^{}]+)\\{ *([0-9]+(\\.[0-9]+)?) *, *([0-9]+(\\.[0-9]+)?) *(, *([0-9]+) *)?\\}").MatchS(t.c_str());
		if(matches->GetLast() < 0) {
			cerr << "Invalid variable specification: " << t << endl;
			return 0;
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
#endif
	
	THnSparse* hs = new THnSparseD("hSparse", varexp.c_str(), varNames.size(), &nbins[0], &rangeMin[0], &rangeMax[0]);
	hs->Sumw2();
	for(size_t i = 0; i < varNames.size(); ++i) {
		hs->GetAxis(i)->SetName(varNames[i]);
		hs->GetAxis(i)->SetTitle(varNames[i]);
	}
	
	return m_data[0]->fillTHn(hs, varexp, selection);
}

void Assembler::writeTablePT(THnBase* hs) {
	// So far, now taus and no b-jets
	setAxisRange(hs, "NGOODTAUS", 0, 0);
	setAxisRange(hs, "NBJETSCSVM", 0, 0);
	
	// Low HT first
	setAxisRange(hs, "HT", 0, 200, false);
	cout << "\n\n==== HT < 200" << endl;
	
	// DY0, no requirements on ONZ
	cout << "\nDY0" << endl;
	setAxisRange(hs, "NOSSF", 0, 0);
	setAxisRange(hs, "ONZ");
	writeMET(hs);
	
	// DYz1
	cout << "\nDYz1" << endl;
	setAxisRange(hs, "NOSSF", 1, 1);
	setAxisRange(hs, "ONZ", 1, 1);
	writeMET(hs);
	
	// DYl1
	cout << "\nDYl1" << endl;
	setAxisRange(hs, "NOSSF", 1, 1);
	setAxisRange(hs, "ONZ", 0, 0);
	setAxisRange(hs, "MOSSF", 0, 76, false);
	writeMET(hs);
	
	// DYh1
	cout << "\nDYh1" << endl;
	setAxisRange(hs, "NOSSF", 1, 1);
	setAxisRange(hs, "ONZ", 0, 0);
	setAxisRange(hs, "MOSSF", 106);
	writeMET(hs);
	
	// DYo1
	cout << "\nDYo1" << endl;
	setAxisRange(hs, "NOSSF", 1, 1);
	setAxisRange(hs, "ONZ", 0, 0);
	setAxisRange(hs, "MOSSF");
	writeMET(hs);
}

void Assembler::writeMET(THnBase* hn) {
	TH1D* h = hn->Projection(7, "E");
	//h->Draw();
	
	double sum = 0;
	for(int i = 1; i <= h->GetNbinsX(); ++i) {
		double content = h->GetBinContent(i);
		double lo = h->GetXaxis()->GetBinLowEdge(i);
		double hi = h->GetXaxis()->GetBinUpEdge(i);
		if(i < h->GetNbinsX()) {
			printf("%d-%d	%d\n", (int)lo, (int)hi, (int)content);
		} else {
			content += h->GetBinContent(i + 1);
			printf("%d-inf	%d\n", (int)lo, (int)content);
		}
		sum += content;
	}
	delete h;
}

bool Assembler::setAxisRange(THnBase* hn, const char* name, double lo, double hi, bool includeLast) {
	TAxis* axis = (TAxis*)hn->GetListOfAxes()->FindObject(name);
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
	
	return true;
}

bool Assembler::setAxisRange(THnBase* hn, const char* name, double lo) {
	TAxis* axis = (TAxis*)hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "Could not find axis " << name << endl;
		exit(1);
	}
	axis->SetRange();
	Int_t first = axis->FindFixBin(lo);
	Int_t last  = axis->GetLast() + 1;
	axis->SetRange(first, last);
	return true;
}

bool Assembler::setAxisRange(THnBase* hn, const char* name) {
	TAxis* axis = (TAxis*)hn->GetListOfAxes()->FindObject(name);
	if(!axis) {
		cerr << "Could not find axis " << name << endl;
		exit(1);
	}
	axis->SetRange();
	return true;
}
