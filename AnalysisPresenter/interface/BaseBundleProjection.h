#ifndef BaseBundleProjection_h
#define BaseBundleProjection_h

#include <map>
#include <set>

#include "TH1.h"
#include "THnBase.h"
#include "TROOT.h"

class BaseBundle;
class PhysicsContribution;

class BaseBundleProjection : public TObject {

public:
	BaseBundleProjection();
	BaseBundleProjection(const BaseBundle*, const char* varName);
	virtual ~BaseBundleProjection();
	
	TH1* getHistogram() const;
	std::set<const PhysicsContribution*> getPhysicsContributions() const;
	const BaseBundle* getSource() const;
	std::map<TString, TH1*> getUncertainties() const;
	void incorporateOverflow();

protected:
	TH1* m_histogram = 0;
	const BaseBundle* m_source = 0;
	
	std::set<const PhysicsContribution*> m_contributions;
	std::map<TString, TH1*> m_uncertainties;
	
	static void incorporateOverflow(TH1* &);

private:

	ClassDef(BaseBundleProjection,1);
};

#endif
