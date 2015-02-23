#ifndef Channel_h
#define Channel_h

#include <set>
#include <vector>

#include "TROOT.h"

#include "RutgersIAF/AnalysisPresenter/interface/AssemblerProjection.h"

class Assembler;

class Channel : public AssemblerProjection {

public:
	Channel();
	Channel(Assembler* assembler, TString name = "");
	virtual ~Channel();

	double getStat(TString type) const;
	double getStat(TString type, TString correlationClass) const;
	double getSyst(TString type) const;
	double getSyst(TString type, TString name) const;
	double getSyst(TString type, TString name, TString correlationClass) const;

protected:

private:
	
	ClassDef(Channel,1);
};

#endif
