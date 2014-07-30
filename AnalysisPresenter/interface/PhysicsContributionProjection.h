#ifndef PhysicsContributionProjection_h
#define PhysicsContributionProjection_h

#include <vector>
#include <map>

#include "TH1D.h"
#include "THnBase.h"
#include "TROOT.h"

class PhysicsContribution;

class PhysicsContributionProjection : public TObject {

public:
	PhysicsContributionProjection();
	PhysicsContributionProjection(const TString name, const TString title, const PhysicsContribution*, const char* varName, const std::map<TString, THnBase*>* uncertaintyMap = 0, const double zerostat = 0.);
	virtual ~PhysicsContributionProjection();
	
	TH1D* getHistogram() const;
	const PhysicsContribution* getPhysicsContribution() const;
	std::map<TString, TH1D*> getUncertainties() const;
	void incorporateOverflow();
	static void incorporateOverflow(TH1D* &);
	void scale(const double scale);

protected:

private:
	const PhysicsContribution* m_contribution = 0;
	TH1D* m_histogram = 0;
	TString m_name;
	TString m_title;
	std::map<TString, TH1D*> m_uncertainties;
	
	ClassDef(PhysicsContributionProjection,1);
};

#endif
