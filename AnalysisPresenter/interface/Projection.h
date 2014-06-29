#ifndef Projection_h
#define Projection_h

#include <map>
#include <string>
#include <vector>

#include "THStack.h"
#include "TROOT.h"

class Projection : public TObject {

public:
	Projection();
	Projection(TString, bool);
	virtual ~Projection();

	void add(TString type, THStack* content, THStack* contentSyst);
	
	double getBin(TString type, int i) const;
	double getBinStat(TString type, int i) const;
	double getBinSyst(TString type, int i) const;
	
	bool has(TString type) const;
	bool hasOverflowIncluded() const;

private:
	bool m_binForOverflow;
	TString m_name;
	
	std::map<TString, std::pair<THStack*, THStack*>> m_components; // like m_components["background"], where .first is the content (with stat uncertainties), and .second are syst uncertainties
	
	ClassDef(Projection,1);
};

#endif
