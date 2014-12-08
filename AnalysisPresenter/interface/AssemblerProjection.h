#ifndef AssemblerProjection_h
#define AssemblerProjection_h

#include <map>
#include <set>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "THStack.h"
#include "TROOT.h"

#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContributionProjection.h"

class AssemblerProjection : public TObject {

public:
	AssemblerProjection();
	AssemblerProjection(TString name, TString title, bool binForOverflow);
	virtual ~AssemblerProjection();

	void add(std::pair<TString, std::vector<PhysicsContributionProjection*>> typeProjection, TString varexp, TString selection);
	
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
	std::vector<std::pair<double, double>> getMeta(TString type = "data", const char* var1 = "RUN[0]", const char* var2 = "EVENT[0]");
	std::set<TString> getUncertainties() const;
	
	bool has(TString type) const;
	bool has(TString type, TString correlationClass) const;
	bool hasOverflowIncluded() const;
	
	TCanvas* plot(bool log = true, double xminFit = 0, double xmaxFit = 0, const char* fitFormula = "pol0");
	void print() const;
	
	void datacard(TString datacardName);

protected:
	bool m_binForOverflow;
	TString m_name;
	TString m_title;
	
	std::set<PhysicsContributionProjection*> m_projections;
	
	double extractStackBin(THStack* stack, int i, TString name) const;
	double addStackBinInQuadrature(THStack* stack, int i) const;

private:
	TCanvas* m_canvas = 0;
	
	std::map<TString, std::pair<THStack*, THStack*>> m_components; // like m_components["background"], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	std::map<TString, std::map<TString, std::pair<THStack*, THStack*>>> m_componentsByCorrelationClass; // like m_components["background"][""], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	std::map<TString, std::vector<PhysicsContributionProjection*>> m_typeProjections;
	
	
	ClassDef(AssemblerProjection,1);
};

#endif
