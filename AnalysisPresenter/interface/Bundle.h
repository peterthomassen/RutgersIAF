#ifndef Bundle_h
#define Bundle_h

#include "RutgersIAF/AnalysisPresenter/interface/BaseBundle.h"

#include <map>
#include <set>
#include <vector>

#include "TROOT.h"

class Bundle : public BaseBundle {

public:
	Bundle();
	Bundle(TString type, TString name, bool allowNegative = false, Int_t fillColor = -1);
	virtual ~Bundle();
	
	bool addComponent(BaseBundle* component);

protected:

private:
	std::vector<BaseBundle*> m_components;

	ClassDef(Bundle,1);
};

#endif
