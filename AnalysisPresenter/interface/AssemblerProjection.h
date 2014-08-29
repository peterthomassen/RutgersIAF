#ifndef AssemblerProjection_h
#define AssemblerProjection_h

#include <map>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "THStack.h"
#include "TROOT.h"

class AssemblerProjection : public TObject {

public:
	AssemblerProjection();
	AssemblerProjection(TString name, TString title, bool binForOverflow);
	virtual ~AssemblerProjection();

	void add(TString type, THStack* content, THStack* contentSyst);
	
	double getBin(TString type, int i) const;
	double getBinStat(TString type, int i) const;
	double getBinSyst(TString type, int i) const;
	TH1* getHistogram(TString type) const;
	
	bool has(TString type) const;
	bool hasOverflowIncluded() const;
	
	TCanvas* plot(bool log = true, bool sqrtError = false, double xminFit = 0, double xmaxFit = 0);
	void print() const;

private:
	bool m_binForOverflow;
	TCanvas* m_canvas = 0;
	TString m_name;
	TString m_title;
	
	std::map<TString, std::pair<THStack*, THStack*>> m_components; // like m_components["background"], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	
	ClassDef(AssemblerProjection,1);
};

#endif
