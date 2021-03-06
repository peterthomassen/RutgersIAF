#ifndef BundleProjection_h
#define BundleProjection_h

#include "RutgersIAF/AnalysisPresenter/interface/BaseBundleProjection.h"

#include "TROOT.h"

class Bundle;

class BundleProjection : public BaseBundleProjection {

public:
	BundleProjection();
	BundleProjection(const Bundle*, std::vector<std::string> varNames);
	virtual ~BundleProjection();

protected:

private:

	ClassDef(BundleProjection,1);
};

#endif
