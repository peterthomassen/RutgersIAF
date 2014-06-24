#ifndef Assembler_h
#define Assembler_h

#include <map>
#include <string>
#include <vector>

#include "THStack.h"
#include "TROOT.h"

#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

class Assembler : public TObject {

public:
	Assembler(TString);
	virtual ~Assembler();
	
	void addContribution(PhysicsContribution*);
	void addWeight(TString, TString = "");
	
	double getLumi() const;
	
	void process(std::string, TString);
	void project(const char*);
	
	void setDebug(bool);
	void setFakeRate(TString, double);
	void setRange(const char*, double, double, bool = true);
	void setRange(const char*, double);
	void setRange(const char*);
	
	void write(const char*);

private:
	TString m_ofname;
	
	std::vector<PhysicsContribution*> m_data;
	std::vector<PhysicsContribution*> m_background;
	std::vector<PhysicsContribution*> m_signal;
	
	std::map<TString, std::map<TH1D*, std::map<TString, TH1D*> > > m_hProjections; // Example: m_hProjections["backgroundDD"] is a map whose keys are pointers to data-driven background histograms, including statistical uncertainties. The value is a vector that contains systematic uncertainty histograms.
	std::map<TString, std::pair<THStack*, THStack*>> m_hsProjections; // Example: m_hsProjections["background"].first contains the stacked background histograms (with statistical uncertainties only), m_hsProjections["background"].second is a stack of the systematic uncertainty histograms for the sum of the background contributions (correlations taken into account)
	
	TString m_varexp;
	TString m_selection;
	
	ClassDef(Assembler,1);
};

#endif
