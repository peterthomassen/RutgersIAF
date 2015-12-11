#ifndef Channel_h
#define Channel_h

#include <set>
#include <vector>

#include "TROOT.h"

#include "RutgersIAF/AnalysisPresenter/interface/AssemblerProjection.h"

class Assembler;
class TString;

class Channel : public AssemblerProjection {

public:
	Channel();
	Channel(Assembler* assembler, TString name);
	Channel(const Channel* parent, Bundle* bundle, TString missingName);
	virtual ~Channel();
	
	Channel* bundle(Bundle* bundle, TString missingName = "") const;
	
	void datacard(TString datacardName = "", bool isData = true, double statFactor = 1.00, double systFactor = 1.00);
	
	double get(TString type) const;
	double get(TString type, TString bundleName) const;
	TString getName() const;
	double getStat(TString type) const;
	double getStat(TString type, TString bundleName) const;
	double getSyst(TString type) const;
	double getSyst(TString type, TString name) const;
	double getSyst(TString type, TString name, TString bundleName) const;
	
	AssemblerProjection* project(const char*, const bool binForOverflow);

protected:

private:
	
	ClassDef(Channel,1);
};

#endif
