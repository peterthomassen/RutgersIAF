#ifndef AssemblerProjection_h
#define AssemblerProjection_h

#include <map>
#include <set>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TF1.h"
#include "THStack.h"
#include "TROOT.h"

#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

class Assembler;
class Bundle;
class PhysicsContributionProjection;

class AssemblerProjection : public TObject {

public:
	AssemblerProjection();
	AssemblerProjection(Assembler* assembler, std::vector<std::string> varNames, bool binForOverflow);
	AssemblerProjection(const AssemblerProjection* parent, Bundle* bundle, TString missingName);
	virtual ~AssemblerProjection();

	AssemblerProjection* bundle(Bundle* bundle, TString missingName = "") const;
	
	double getBin(TString type, int i) const;
	double getBin(TString type, int i, TString bundleName) const;
	double getBinStat(TString type, int i) const;
	double getBinStat(TString type, int i, TString bundleName) const;
	double getBinSyst(TString type, int i) const;
	double getBinSyst(TString type, int i, TString name) const;
	double getBinSyst(TString type, int i, TString name, TString bundleName) const;
	std::vector<TString> getBundleNames(TString type) const;
	int getDimensionality() const;
	TH1* getHistogram(TString type) const;
	std::vector<TH1*> getHistograms(TString type) const;
	std::set<PhysicsContribution::metadata_t> getMeta(TString type = "data") const;
	double getMoment(TString type, int k = 1, bool center = false) const;
	std::vector<std::pair<int, int>> getRanges() const;
	std::set<TString> getUncertaintyNames() const;
	std::vector<std::string> getVarNames() const;
	
	bool has(TString type) const;
	bool has(TString type, TString bundleName) const;
	bool hasOverflowIncluded() const;
	bool isDistribution() const;
	
	TCanvas* plot(bool log = true, TF1* f1 = 0, double xminFit = 0, double xmaxFit = 0);
	
	void print() const;
	TString printRA7table() const;
	void printMeta(TString type = "data") const;
	
	void datacard(TString datacardName, bool isData = true, double statFactor = 1.00, double systFactor = 1.00);

protected:
	Assembler* m_assembler;
	bool m_binForOverflow;
	Bundle* m_bundle = 0;
	const AssemblerProjection* m_parent = 0;
	std::vector<std::pair<int, int>> m_ranges;
	TString m_name;
	std::vector<std::string> m_varNames;
	
	std::map<TString, std::vector<BaseBundleProjection*>> m_typeProjections;
	
	double extractStackBin(THStack* stack, int i, TString name) const;
	double addStackBinInQuadrature(THStack* stack, int i) const;
	double getMoment(TH1* h, int k = 1, bool center = false) const;

private:
	TCanvas* m_canvas = 0;
	
	std::map<TString, std::pair<THStack*, THStack*>> m_stacks; // like m_stacks["background"], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	std::map<TString, std::map<TString, std::pair<THStack*, THStack*>>> m_bundles; // like m_bundles["background"]["rare"], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	
	void prepareStacks();


	ClassDef(AssemblerProjection,1);
};

#endif
