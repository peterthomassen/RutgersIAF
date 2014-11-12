#ifndef Assembler_h
#define Assembler_h

#include <map>
#include <set>
#include <string>
#include <vector>

#include "TROOT.h"

#include "RutgersIAF/AnalysisPresenter/interface/AssemblerProjection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContributionProjection.h"

class TFile;

class Assembler : public TObject {

public:
	Assembler(TString = "", Option_t* options = "CREATE");
	virtual ~Assembler();
	
	void addContribution(PhysicsContribution*);
	void addWeight(TString, TString = "");
	
	double getLumi() const;
	
	void process(std::string, TString);
	AssemblerProjection* project(const char*, const bool binForOverflow);
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
	
	std::map<TString, std::vector<PhysicsContributionProjection*>> m_hProjections; // Example: m_hProjections["backgroundDD"] is a map whose keys are pointers to data-driven background histograms, including statistical uncertainties. The value is a map that contains systematic uncertainty histograms.
	AssemblerProjection* m_projection = 0;
	
	TString m_varexp;
	std::map<TString, TString> m_vars;
	TString m_selection;
	
	ClassDef(Assembler,1);
};

#endif
