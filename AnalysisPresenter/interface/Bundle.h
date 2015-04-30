#ifndef Bundle_h
#define Bundle_h

#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"

#include <map>
#include <set>
#include <vector>

#include "TROOT.h"

class BundleProjection;

class Bundle : public TObject {

friend class Assembler;

public:
	Bundle();
	Bundle(TString type, TString name, Int_t fillColor = -1);
	virtual ~Bundle();
	
	Int_t getFillColor() const;
	TString getName() const;
	TString getType(const bool detailed = false) const;
	
	bool isBackground() const;
	bool isData() const;
	bool isSignal() const;
	
	void setFillColor(const Int_t fillColor);

protected:
	Int_t m_fillColor = -1;
	TString m_name;
	TString m_type;

private:

	ClassDef(Bundle,1);
};

#endif
