#ifndef PhysicsContribution_h
#define PhysicsContribution_h

#include "RutgersIAF/AnalysisPresenter/interface/BaseBundle.h"

#include <map>
#include <set>
#include <unordered_set>
#include <vector>

#include "THnBase.h"
#include "TROOT.h"

class PhysicsContributionProjection;
class TTree;

class PhysicsContribution : public BaseBundle {

friend class Assembler;

public:
	struct metadata_t {
		long event;
		int run;
		int lumi;
		int fakeIncarnation;
	};
	
	PhysicsContribution();
	PhysicsContribution(TString type, TString filename, double lumi, TString name, bool allowNegative = false, TString treeRname = "treeR", Int_t fillColor = -1, double minScale = 0.01, bool unordered = true);
	virtual ~PhysicsContribution();
	
	void addFlatUncertainty(TString, double);
	void addRelativeUncertainty(TString, TString);
	void addVariation(TString, std::pair<TString, TString>);
	void addWeight(TString weight, double normalization = 1.0);
	bool addVetoEvent(std::string vetoString);
	THnBase* fillContent(const THnBase*, std::string, TString, double scale = 1.0, TH1D* hPileup = 0, TH1D* hPileupUnc = 0);
	int findBinFromLowEdge(TAxis* axis, double x);
	std::set<Long64_t> getBins() const; // std::unordered_set doesn't work with slc5_amd64_gcc481
	THnBase* getContent(bool absoluteWeights = false) const;
	double getLumi() const;
	std::set<PhysicsContribution::metadata_t> getMeta() const;
	TString getSelectionString() const;
	std::map<TString, std::pair<TString, THnBase*>> getUncertaintyMap() const;
	void setAlias(TString, TString);
	
	bool isMC() const;
	
	void print(int level = 0) const;
	BaseBundleProjection* project(std::vector<std::string> varNames, const bool binForOverflow = false) const;
	
	bool setDebug(bool);
	void setFakeRate(TString, TString);
	void setNominalWeight(TString);

protected:
	void applyFlatUncertainty(TString);
	
	bool setRange(const char*, double, double, bool = true);
	bool setRange(const char*, double);
	bool setRange(const char*);
	bool setRange();
	
	std::vector<std::pair<int, int>> getRanges() const;
	void setRanges(std::vector<std::pair<int, int>> ranges);


private:
	bool m_debug = false;
	TString m_filename;
	double m_lumi;
	bool m_MC = false;
	double m_scale = 0;
	TString m_selection;
	TString m_treeRname;
	double m_minScale;
	bool m_unordered;
	
	TString m_nominalWeight;
	
	THnBase* m_hn = 0;
	THnBase* m_hnAbs = 0;
	std::map<TString, THnBase*> m_hProjectionUncertainties;
	std::vector<std::vector<metadata_t>> m_metadata;
	
	std::map<TString, TString> m_fakerateMap;
	std::map<TString, double> m_flatUncertaintyMap;
	std::map<TString, TString> m_rangeStrings;
	std::map<TString, std::pair<TString, THnBase*>> m_uncertaintyMap;
	std::map<TString, std::pair<TString, TString>> m_variationMap;
	std::vector<TString> m_weights;
	std::unordered_set<std::string> m_vetoEvents;
	std::map<TString,TString> m_aliases;

	
	THnBase* fillContentVariation(TTree*, THnBase*, std::string, TString, double scale = 1.0, TH1D* hPileupWeights = 0);
	
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
