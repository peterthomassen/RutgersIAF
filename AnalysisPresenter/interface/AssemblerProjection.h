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
class PhysicsContributionProjection;

class AssemblerProjection : public TObject {

public:
	AssemblerProjection();
	AssemblerProjection(Assembler* assembler, TString name, bool binForOverflow);
	virtual ~AssemblerProjection();

	double getBin(TString type, int i) const;
	double getBin(TString type, int i, TString correlationClass) const;
	double getBinStat(TString type, int i) const;
	double getBinStat(TString type, int i, TString correlationClass) const;
	double getBinSyst(TString type, int i) const;
	double getBinSyst(TString type, int i, TString name) const;
	double getBinSyst(TString type, int i, TString name, TString correlationClass) const;
	std::vector<TString> getCorrelationClasses(TString type);
	TH1* getHistogram(TString type) const;
	TH1* getHistogram(TString type, TString correlationClass) const;
	std::set<PhysicsContribution::metadata_t> getMeta(TString type = "data") const;
	double getMoment(TString type, int k = 1, bool center = false) const;
	std::vector<std::pair<int, int>> getRanges() const;
	std::set<TString> getUncertainties() const;
	bool isDistribution() const;
	void printMeta(TString type = "data") const;
	
	bool has(TString type) const;
	bool has(TString type, TString correlationClass) const;
	bool hasOverflowIncluded() const;
	
	TCanvas* plot(bool log = true, TF1* f1 = 0, double xminFit = 0, double xmaxFit = 0);
	void print() const;
	
	void datacard(TString datacardName, bool isData = true, double statFactor = 1.00, double systFactor = 1.00);

protected:
	Assembler* m_assembler;
	bool m_binForOverflow;
	TString m_name;
	TString m_title;
	
	std::set<PhysicsContributionProjection*> m_projections;
	std::vector<std::pair<int, int>> m_ranges;
	
	void add(std::pair<TString, std::vector<PhysicsContributionProjection*>> typeProjection, TString varexp, TString selection);
	double extractStackBin(THStack* stack, int i, TString name) const;
	double addStackBinInQuadrature(THStack* stack, int i) const;

private:
	TCanvas* m_canvas = 0;
	
	bool m_isDistribution;
	
	std::map<TString, std::pair<THStack*, THStack*>> m_components; // like m_components["background"], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	std::map<TString, std::map<TString, std::pair<THStack*, THStack*>>> m_componentsByCorrelationClass; // like m_components["background"][""], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	std::map<TString, std::vector<PhysicsContributionProjection*>> m_typeProjections;
	
	
	ClassDef(AssemblerProjection,1);
};

#endif
