#ifndef SignatureCutEvent_h
#define SignatureCutEvent_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <assert.h>
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureObject.h"

class SignatureCutEvent : public SignatureCut {
 public:
	SignatureCutEvent(std::vector<int> runList, std::vector<long int> eventList, const char* name="sigcutevent") : SignatureCut(name),m_runList(runList),m_eventList(eventList) {
		assert(runList.size() == eventList.size());
	}
	virtual ~SignatureCutEvent(){ /* no-op */ }
	
	virtual bool passCut(BaseHandler* handler) const 
	{
		int run = handler->getRun();
		long int event = handler->getEvent();
		
		for(unsigned int i = 0; i < m_runList.size(); ++i) {
			if(m_runList[i] == run && m_eventList[i] == event) {
				return true;
			}
		}
		return false;
	}
	virtual bool operator()(BaseHandler*) const;

 protected:
	std::vector<int> m_runList;
	std::vector<long int> m_eventList;
	
 private:
	
	ClassDef(SignatureCutEvent,1);

};

inline bool SignatureCutEvent::operator()(BaseHandler* handler)const
{
	return passCut(handler);
}

#endif
