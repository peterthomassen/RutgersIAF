#ifndef PhysicsContribution_h
#define PhysicsContribution_h

#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"

#include <map>
#include <set>
#include <vector>

#include "THnBase.h"
#include "TROOT.h"

class PhysicsContributionProjection;

class PhysicsContribution : public Bundle {

friend class Assembler;

public:
	struct metadata_t {
		long event;
		int run;
		int lumi;
		int fakeIncarnation;
	};
	
	PhysicsContribution();
	PhysicsContribution(TString type, TString filename, double lumi, TString name, TString treeRname = "treeR", Int_t fillColor = -1, bool unordered = true);
	virtual ~PhysicsContribution();
	
	void addFlatUncertainty(TString, double);
	void addWeight(TString weight, double normalization = 1.0);
	THnBase* fillContent(const THnBase*, std::string, TString, double scale = 1.0, const double minScale = 0.01);
	int findBinFromLowEdge(TAxis* axis, double x);
	std::set<Long64_t> getBins() const; // std::unordered_set doesn't work with slc5_amd64_gcc481
	THnBase* getContent() const;
	TString getCorrelationClass() const;
	std::map<PhysicsContribution*, std::map<TString, TString>> getEnsembleFakeRateParams() const;
	double getLumi() const;
	std::set<PhysicsContribution::metadata_t> getMeta() const;
	TString getSelectionString() const;
	double getWeight();
	
	bool isMC() const;
	
	PhysicsContributionProjection* project(const char* varName, const bool binForOverflow = false, const bool plain = false) const;
	
	bool setDebug(bool);
	void setCorrelationClass(TString correlationClass);
	void setEnsembleFakeRateParam(PhysicsContribution*, TString varName, TString formula);
	void setFakeRate(TString, TString);

protected:
	void applyRelativeUncertainty(THnBase*, TString);
	void applyUncertainty(TString, THnBase*);
	
	bool setRange(const char*, double, double, bool = true);
	bool setRange(const char*, double);
	bool setRange(const char*);
	bool setRange();
	
	std::vector<std::pair<int, int>> getRanges() const;
	void setRanges(std::vector<std::pair<int, int>> ranges);


private:
	TString m_correlationClass = "";
	bool m_debug = false;
	TString m_filename;
	double m_lumi;
	bool m_MC = false;
	double m_scale = 0;
	TString m_selection;
	TString m_treeRname;
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
	//return std::tie(x.run, x.lumi, x.event, x.fakeIncarnation) < std::tie(y.run, y.lumi, y.event, y.fakeIncarnation);
	return (x.run < y.run)
		? true
		: ((x.run == y.run && x.lumi < y.lumi)
			? true
			: ((x.run == y.run && x.lumi == y.lumi && x.event < y.event)
				? true
				: (x.run == y.run && x.lumi == y.lumi && x.event == y.event && x.fakeIncarnation < y.fakeIncarnation)
			)
		);
}

#endif
