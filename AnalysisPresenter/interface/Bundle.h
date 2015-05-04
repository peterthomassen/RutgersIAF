#ifndef Bundle_h
#define Bundle_h

#include "RutgersIAF/AnalysisPresenter/interface/BaseBundle.h"

#include <vector>

#include "TROOT.h"

class BundleProjection;

class Bundle : public BaseBundle {

public:
	Bundle();
	Bundle(TString type, TString name, bool allowNegative = false, Int_t fillColor = -1);
	virtual ~Bundle();
	
	bool addComponent(BaseBundle* component);
	std::vector<BaseBundle*> getComponents() const;
	
	void print(int level = 0) const;
	BaseBundleProjection* project(const char* varName, const bool binForOverflow = false) const;

protected:

private:
	std::vector<BaseBundle*> m_components;

	ClassDef(Bundle,1);
};

#endif
