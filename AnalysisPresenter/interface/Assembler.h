#ifndef Assembler_h
#define Assembler_h

#include <map>
#include <string>
#include <vector>

#include "THStack.h"
#include "TROOT.h"

#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"
#include "RutgersIAF2012/AnalysisPresenter/interface/Projection.h"

class TFile;

class Assembler : public TObject {

public:
	Assembler();
	Assembler(TString, Option_t* options = "CREATE");
	virtual ~Assembler();
	
	void addContribution(PhysicsContribution*);
	void addWeight(TString, TString = "");
	
	double getLumi() const;
	
	void print(const char*, const bool binForOverflow = true);
	void process(std::string, TString);
	Projection* project(const char*, const bool binForOverflow);
	void save();
	void save(const char*, const bool binForOverflow = true);
	
	void setDebug(bool);
	void setFakeRate(TString, TString);
	void setRange(const char*, double, double, bool = true);
	void setRange(const char*, double);
	void setRange(const char*);
	void setRange();

private:
	TFile* m_outfile = 0;
	
	std::vector<PhysicsContribution*> m_data;
	std::vector<PhysicsContribution*> m_background;
	std::vector<PhysicsContribution*> m_signal;
	
	std::map<TString, std::map<TH1D*, std::map<TString, TH1D*> > > m_hProjections; // Example: m_hProjections["backgroundDD"] is a map whose keys are pointers to data-driven background histograms, including statistical uncertainties. The value is a vector that contains systematic uncertainty histograms.
	Projection* m_projection = 0;
	
	TString m_varexp;
	TString m_selection;
	
	ClassDef(Assembler,1);
};

#endif
