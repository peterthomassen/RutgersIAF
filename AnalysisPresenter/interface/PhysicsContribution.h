#ifndef PhysicsContribution_h
#define PhysicsContribution_h

#include <vector>
#include <map>

#include "THnBase.h"
#include "TROOT.h"

class PhysicsContribution : public TObject {

public:
	PhysicsContribution(TString, TString, double, TString = "");
	virtual ~PhysicsContribution();
	
	void addCorrelatedUncertainty(TString, THnBase*);
	void addFlatUncertainty(TString, double);
	void addWeight(TString, TString = "");
	void applyRelativeUncertainty(THnBase*, TString);
	THnBase* fillContent(const THnBase*, std::string, TString);
	THnBase* getContent();
	double getLumi() const;
	TString getName() const;
	TString getType(const bool detailed = false) const;
	
	bool isBackground() const;
	bool isData() const;
	bool isSignal() const;
	
	std::pair<TH1D*, std::map<TString, TH1D*> > project(const int dim, const double scale = 1.0) const;
	
	bool setDebug(bool);
	void setFakeRate(TString, double);
	void setRange(const char*, double, double, bool = true);
	void setRange(const char*, double);
	void setRange(const char*);

private:
	bool m_debug = false;
	TString m_filename;
	double m_lumi;
	TString m_name;
	TString m_type;
	
	THnBase* m_hn = 0;
	std::map<TString, THnBase*> m_hProjectionUncertainties;
	
	std::map<TString, double> m_fakerateMap;
	std::map<TString, double> m_flatUncertaintyMap;
	std::map<TString, THnBase*> m_systematicUncertaintyMap;
	std::vector<TString> m_weights;
	
	ClassDef(PhysicsContribution,1);
};

#endif
