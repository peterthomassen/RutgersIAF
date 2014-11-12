#ifndef PhysicsContribution_h
#define PhysicsContribution_h

#include <map>
#include <vector>

#include "THnBase.h"
#include "TROOT.h"

class PhysicsContributionProjection;

class PhysicsContribution : public TObject {

public:
	PhysicsContribution();
	PhysicsContribution(TString type, TString filename, double lumi, TString name, Int_t fillColor = -1, bool unordered = true, bool forceData = false);
	virtual ~PhysicsContribution();
	
	void addFlatUncertainty(TString, double);
	void addWeight(TString, TString = "");
	THnBase* fillContent(const THnBase*, std::string, TString, double scale = 1.0, const double minScale = 0.01);
	int findBinFromLowEdge(TAxis* axis, double x);
	THnBase* getContent() const;
	TString getCorrelationClass() const;
	std::map<PhysicsContribution*, std::map<TString, TString>> getEnsembleFakeRateParams() const;
	Int_t getFillColor() const;
	double getLumi() const;
	TString getName() const;
	TString getType(const bool detailed = false) const;
	double getWeight();
	
	bool isBackground() const;
	bool isData() const;
	bool isMC() const;
	bool isSignal() const;
	
	PhysicsContributionProjection* project(const char* varName, const bool binForOverflow = false, const bool plain = false) const;
	
	bool setDebug(bool);
	void setCorrelationClass(TString correlationClass);
	void setEnsembleFakeRateParam(PhysicsContribution*, TString varName, TString formula);
	void setFakeRate(TString, TString);
	void setFillColor(const Int_t fillColor);
	bool setRange(const char*, double, double, bool = true);
	bool setRange(const char*, double);
	bool setRange(const char*);
	bool setRange();

protected:
	void applyRelativeUncertainty(THnBase*, TString);
	void applyUncertainty(TString, THnBase*);

private:
	TString m_correlationClass = "";
	bool m_debug = false;
	TString m_filename;
	Int_t m_fillColor = -1;
	double m_lumi;
	bool m_MC = false;
	TString m_name;
	double m_scale = 0;
	TString m_selection;
	TString m_type;
	bool m_unordered;
	double m_weight = 0;
	
	THnBase* m_hn = 0;
	std::map<TString, THnBase*> m_hProjectionUncertainties;
	
	std::map<PhysicsContribution*, std::map<TString, TString>> m_ensembleFakeRateParams;
	std::map<TString, TString> m_fakerateMap;
	std::map<TString, double> m_flatUncertaintyMap;
	std::map<TString, TString> m_rangeStrings;
	std::map<TString, THnBase*> m_uncertaintyMap;
	std::vector<TString> m_weights;
	
	ClassDef(PhysicsContribution,1);
};

#endif
