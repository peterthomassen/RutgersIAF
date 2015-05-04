#ifndef PhysicsContributionProjection_h
#define PhysicsContributionProjection_h

#include "RutgersIAF/AnalysisPresenter/interface/BaseBundleProjection.h"

#include <map>

#include "TROOT.h"

class PhysicsContribution;
class THnBase;

class PhysicsContributionProjection : public BaseBundleProjection {

public:
	PhysicsContributionProjection();
	PhysicsContributionProjection(const PhysicsContribution*, const char* varName, const std::map<TString, THnBase*>* uncertaintyMap = 0, const double zerostat = 0.);
	virtual ~PhysicsContributionProjection();
	
	void scale(const double scale);

protected:

private:

	ClassDef(PhysicsContributionProjection,1);
};

#endif
