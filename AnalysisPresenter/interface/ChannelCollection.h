#ifndef ChannelCollection_h
#define ChannelCollection_h

#include <set>
#include <vector>

#include "TROOT.h"

#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

class Channel;

class ChannelCollection : public TObject {

public:
	ChannelCollection();
	ChannelCollection(TString name);
	virtual ~ChannelCollection();
	
	bool addChannel(Channel* channel);
	void datacard(TString filename) const;
	std::set<Channel*> getChannels() const;
	std::set<PhysicsContribution::metadata_t> getMeta(TString type = "data") const;
	TString getName() const;
	void printMeta(TString type = "data") const;

protected:

private:
	std::set<Channel*> m_channels;
	std::map<TString, std::set<PhysicsContribution::metadata_t>> m_meta;
	TString m_name;
	
	ClassDef(ChannelCollection,1);
};

#endif
