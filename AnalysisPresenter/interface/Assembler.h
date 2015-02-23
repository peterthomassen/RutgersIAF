#ifndef Assembler_h
#define Assembler_h

#include <map>
#include <set>
#include <string>
#include <vector>

#include "TROOT.h"

class TFile;
class AssemblerProjection;
class PhysicsContribution;
class PhysicsContributionProjection;

class Assembler : public TObject {

friend class AssemblerProjection;

public:
	Assembler(TString = "", Option_t* options = "CREATE");
	virtual ~Assembler();
	
	void addContribution(PhysicsContribution*);
	std::set<TString> getCorrelationClasses(TString type);
	
	std::vector<PhysicsContribution*> getContributions(TString type) const;
	double getLumi() const;
	TString getVarExp() const;
	TString getVarName(TString name) const;
	TString getSelection() const;
	
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

public:
	std::vector<std::pair<int, int>> getRanges() const;
	void setRanges(std::vector<std::pair<int, int>> ranges);

private:
	TFile* m_outfile = 0;
	
	std::map<TString, std::vector<PhysicsContribution*>> m_contributions;
	
	AssemblerProjection* m_projection = 0;
	
	TString m_varexp;
	std::map<TString, TString> m_vars;
	TString m_selection;
	
	ClassDef(Assembler,1);
};

#endif
