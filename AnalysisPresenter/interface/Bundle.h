#ifndef Bundle_h
#define Bundle_h

#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"

#include <map>
#include <set>
#include <vector>

#include "TROOT.h"

class BundleProjection;

class Bundle : public TObject {

public:
	Bundle();
	Bundle(TString type, TString name, bool allowNegative = false, Int_t fillColor = -1);
	virtual ~Bundle();
	
	bool getAllowNegative() const;
	Int_t getFillColor() const;
	TString getName() const;
	TString getType(const bool detailed = false) const;
	
	bool isBackground() const;
	bool isData() const;
	bool isSignal() const;
	
	void setFillColor(const Int_t fillColor);

protected:
	bool m_allowNegative;
	Int_t m_fillColor = -1;
	TString m_name;
	TString m_type;

private:

	ClassDef(Bundle,1);
};

#endif
