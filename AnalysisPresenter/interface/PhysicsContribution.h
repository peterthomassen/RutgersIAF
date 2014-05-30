#ifndef PhysicsContribution_h
#define PhysicsContribution_h

#include <vector>
#include <map>

#include "THnBase.h"
#include "TROOT.h"

class PhysicsContribution : public TObject {

public:
	PhysicsContribution(TString, double, TString = "");
	virtual ~PhysicsContribution();
	
	THnBase* fillTHn(const THnBase*, std::string, std::string);
	double getLumi() const;
	THnBase* getTHn();

	void setRange(const char*, double, double, bool = true);
	void setRange(const char*, double);
	void setRange(const char*);

private:
	TString m_filename;
	double m_lumi;
	TString m_name;
	
	THnBase* m_hn = 0;
	
	ClassDef(PhysicsContribution,1);
};

#endif
