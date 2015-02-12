#ifndef PhysicsContribution_h
#define PhysicsContribution_h

#include <map>
#include <set>
#include <vector>

#include "THnBase.h"
#include "TROOT.h"

class PhysicsContributionProjection;

class PhysicsContribution : public TObject {

public:
	struct metadata_t {
		long event;
		int run;
		int lumi;
		int fakeIncarnation;
	};
	
	PhysicsContribution();
	PhysicsContribution(TString type, TString filename, double lumi, TString name, Int_t fillColor = -1, bool unordered = true, bool forceData = false);
	virtual ~PhysicsContribution();
	
	void addFlatUncertainty(TString, double);
	void addWeight(TString weight, double normalization = 1.0);
	THnBase* fillContent(const THnBase*, std::string, TString, double scale = 1.0, const double minScale = 0.01);
	int findBinFromLowEdge(TAxis* axis, double x);
	std::set<Long64_t> getBins() const; // std::unordered_set doesn't work with slc5_amd64_gcc481
	THnBase* getContent() const;
	TString getCorrelationClass() const;
	std::map<PhysicsContribution*, std::map<TString, TString>> getEnsembleFakeRateParams() const;
	Int_t getFillColor() const;
	double getLumi() const;
	std::set<PhysicsContribution::metadata_t> getMeta() const;
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
	std::vector<std::vector<metadata_t>> m_metadata;
	
	std::map<PhysicsContribution*, std::map<TString, TString>> m_ensembleFakeRateParams;
	std::map<TString, TString> m_fakerateMap;
	std::map<TString, double> m_flatUncertaintyMap;
	std::map<TString, TString> m_rangeStrings;
	std::map<TString, THnBase*> m_uncertaintyMap;
	std::vector<TString> m_weights;
	
	ClassDef(PhysicsContribution,1);
};

inline bool operator<(const PhysicsContribution::metadata_t& x, const PhysicsContribution::metadata_t& y) {
	// std::tie does not work with slc5_amd64_gcc481
	//return std::tie(x.event, x.run, x.lumi, x.fakeIncarnation) < std::tie(y.event, y.run, y.lumi, y.fakeIncarnation);
	return (x.event < y.event)
		? true
		: ((x.run < y.run)
			? true
			: ((x.lumi < y.lumi)
				? true
				: (x.fakeIncarnation < y.fakeIncarnation)
			)
		);
}

#endif
