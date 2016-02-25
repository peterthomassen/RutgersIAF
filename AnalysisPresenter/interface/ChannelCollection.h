#ifndef ChannelCollection_h
#define ChannelCollection_h

#include <map>
#include <set>
#include <string>
#include <vector>

#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

class Channel;

class ChannelCollection : public TObject {

public:
	ChannelCollection();
	ChannelCollection(TString name);
	virtual ~ChannelCollection();
	
	bool addChannel(Channel* channel, bool allowDuplicates = false);
	void datacard(TString datacardName, bool isData = true, double statFactor = 1.00, double systFactor = 1.00, double signalXsecUncertainty = 0.00);
	
	std::vector<Channel*> getChannels() const;
	std::set<TString> getUncertaintyNames() const;
	std::vector<TString> getBundleNames(TString type) const;
	std::set<PhysicsContribution::metadata_t> getMeta(TString type = "data") const;
	TString getName() const;
	
	bool has(TString type) const;
	bool has(TString type, TString bundleName) const;
	
	void printMeta(TString type = "data") const;

protected:
	
private:
	std::vector<Channel*> m_channels;
	std::map<TString, std::set<PhysicsContribution::metadata_t>> m_meta;
	TString m_name;
	
	ClassDef(ChannelCollection,1);
};

#endif
