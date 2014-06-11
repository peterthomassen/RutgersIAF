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
	std::map<TString, THnBase*> getCorrelatedUncertainties();
	double getLumi() const;
	TString getName() const;
	TString getType() const;
	
	bool isBackground() const;
	bool isData() const;
	bool isSignal() const;
	
	void setFakeRate(TString, double);
	
	void setRange(const char*, double, double, bool = true);
	void setRange(const char*, double);
	void setRange(const char*);

private:
	TString m_filename;
	double m_lumi;
	TString m_name;
	TString m_type;
	
	THnBase* m_hn = 0;
	
	std::map<TString, THnBase*> m_correlatedUncertaintyHistogramMap;
	std::map<TString, double> m_fakerateMap;
	std::map<TString, double> m_flatUncertaintyMap;
	std::vector<TString> m_weights;
	
	ClassDef(PhysicsContribution,1);
};

#endif
