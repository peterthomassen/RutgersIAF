#ifndef BaseBundle_h
#define BaseBundle_h

#include <map>
#include <set>
#include <vector>

#include "TROOT.h"

class BaseBundleProjection;

class BaseBundle : public TObject {

public:
	BaseBundle();
	BaseBundle(TString type, TString name, bool allowNegative = false, Int_t fillColor = -1);
	virtual ~BaseBundle() = 0;
	
	bool getAllowNegative() const;
	Int_t getFillColor() const;
	TString getName() const;
	TString getType(const bool detailed = false) const;
	
	bool isBackground() const;
	bool isData() const;
	bool isSignal() const;
	
	virtual void print(int level = 0) const = 0;
	virtual BaseBundleProjection* project(std::vector<std::string> varNames, const bool binForOverflow = false) const = 0;
	void setFillColor(const Int_t fillColor);

protected:
	bool m_allowNegative;
	Int_t m_fillColor = -1;
	TString m_name;
	TString m_type;

private:

	ClassDef(BaseBundle,1);
};

#endif
