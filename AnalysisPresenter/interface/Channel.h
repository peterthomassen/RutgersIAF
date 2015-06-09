#ifndef Channel_h
#define Channel_h

#include <set>
#include <vector>

#include "TROOT.h"

#include "RutgersIAF/AnalysisPresenter/interface/AssemblerProjection.h"

class Assembler;
class TString;
class Bundle;

class Channel : public AssemblerProjection {

public:
	Channel();
	Channel(Assembler* assembler, TString name);
	virtual ~Channel();

	double get(TString type) const;
	double get(TString type, TString bundleName) const;
	TString getName() const;
	double getStat(TString type) const;
	double getStat(TString type, TString bundleName) const;
	double getSyst(TString type) const;
	double getSyst(TString type, TString name) const;
	double getSyst(TString type, TString name, TString bundleName) const;
	
	bool ChannelHas(TString type) const;
	bool ChannelHas(TString type, TString bundleName) const;
	
	std::set<TString> getChannelUncertainties() const;
	std::vector<TString> getChannelBundleNames(TString type) const;
	
	AssemblerProjection* project(const char*, const bool binForOverflow);

protected:
	
	std::map<TString, std::vector<BaseBundleProjection*>> m_typeProjections;
	

private:

	std::map<TString, std::map<TString, std::pair<THStack*, THStack*>>> m_bundles; // like m_bundles["background"]["rare"], where .first is the content (with stat uncertainties), and .second are syst
	
	ClassDef(Channel,1);
};

#endif
