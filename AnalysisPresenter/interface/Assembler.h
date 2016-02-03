#ifndef Assembler_h
#define Assembler_h

#include <map>
#include <set>
#include <string>
#include <vector>

#include "TROOT.h"

class TFile;
class TH1D;

class AssemblerProjection;
class Bundle;
class Channel;
class PhysicsContribution;
class PhysicsContributionProjection;

class Assembler : public TObject {

friend class AssemblerProjection;
friend class Channel;

public:
	Assembler(TString = "", Option_t* options = "CREATE");
	virtual ~Assembler();
	
	void addContribution(PhysicsContribution* contribution);
	void addBundle(Bundle* bundle);
	Channel* channel(const char* name, Bundle* bundle = 0);
	
	Bundle* getBundle(TString name) const;
	Bundle* getDefaultBundle() const;
	double getLumi() const;
	bool getMode(TString name) const;
	std::vector<PhysicsContribution*> getPhysicsContributions(TString type) const;
	std::vector<std::pair<int, int>> getRanges() const;
	TString getVarExp() const;
	TString getVarName(TString name) const;
	TString getSelection() const;
	
	void process(std::string, TString, bool ApplyMCNormalizationWeights=true);
	AssemblerProjection* project(const char* name, const bool binForOverflow, Bundle* bundle = 0);
	void save();
	void save(const char*, const bool binForOverflow = true);
	
	void setDebug(bool);
	Bundle* setDefaultBundle(Bundle* bundle);
	void setFakeRate(TString, TString);
	bool setMode(TString name, bool value = true);
	void setPileupHistogram(TH1D* hPileup, TH1D* hPileupUnc = 0);
	void setRange(const char*, double, double, bool = true);
	void setRange(const char*, double);
	void setRange(const char*);
	void setRange();
	void setRanges(std::vector<std::pair<int, int>> ranges);

protected:

private:
	TFile* m_outfile = 0;
	
	std::map<TString, std::vector<PhysicsContribution*>> m_contributions;
	std::map<TString, Bundle*> m_bundles;
	std::pair<TH1D*, TH1D*> m_hPileup;
	std::map<TString, bool> m_modes;
	
	Bundle* m_defaultBundle = 0;
	AssemblerProjection* m_projection = 0;
	
	TString m_varexp;
	std::map<TString, TString> m_vars;
	TString m_selection;
	
	ClassDef(Assembler,1);
};

#endif
