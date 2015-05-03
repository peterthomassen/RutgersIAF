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
	AssemblerProjection(Assembler* assembler, TString name, bool binForOverflow);
	AssemblerProjection(const AssemblerProjection* parent, Bundle* bundle, bool combineMissing);
	virtual ~AssemblerProjection();

	AssemblerProjection* bundle(Bundle* bundle, bool combineMissing = false) const;
	double getBin(TString type, int i) const;
	double getBinStat(TString type, int i) const;
	double getBinSyst(TString type, int i) const;
	double getBinSyst(TString type, int i, TString name) const;
	TH1* getHistogram(TString type) const;
	std::set<PhysicsContribution::metadata_t> getMeta(TString type = "data") const;
	double getMoment(TString type, int k = 1, bool center = false) const;
	std::vector<std::pair<int, int>> getRanges() const;
	std::set<TString> getUncertainties() const;
	bool isDistribution() const;
	void printMeta(TString type = "data") const;
	
	bool has(TString type) const;
	bool hasOverflowIncluded() const;
	
	TCanvas* plot(bool log = true, TF1* f1 = 0, double xminFit = 0, double xmaxFit = 0);
	void print() const;
	
	//void datacard(TString datacardName, bool isData = true, double statFactor = 1.00, double systFactor = 1.00);

protected:
	Assembler* m_assembler;
	bool m_binForOverflow;
	bool m_isDistribution;
	TString m_name;
	const AssemblerProjection* m_parent = 0;
	std::vector<std::pair<int, int>> m_ranges;
	TString m_title;
	
	std::map<TString, std::pair<THStack*, THStack*>> m_components; // like m_components["background"], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	std::map<TString, std::vector<PhysicsContributionProjection*>> m_typeProjections;
	
	double extractStackBin(THStack* stack, int i, TString name) const;
	double addStackBinInQuadrature(THStack* stack, int i) const;
	double getMoment(TH1* h, int k = 1, bool center = false) const;

private:
	TCanvas* m_canvas = 0;
	
	void add(TString type);


	ClassDef(AssemblerProjection,1);
};

#endif
