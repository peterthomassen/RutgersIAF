#ifndef PhysicsContribution_h
#define PhysicsContribution_h

#include <vector>
#include <map>

#include "THnBase.h"
#include "TROOT.h"

class PhysicsContribution : public TObject {

public:
	PhysicsContribution();
	PhysicsContribution(TString type, TString filename, double lumi, TString name, bool unordered = true);
	virtual ~PhysicsContribution();
	
	void addFlatUncertainty(TString, double);
	void addWeight(TString, TString = "");
	THnBase* fillContent(const THnBase*, std::string, TString, double scale = 1.0, const double minScale = 0.01);
	THnBase* getContent() const;
	Int_t getFillColor() const;
	double getLumi() const;
	TString getName() const;
	TString getType(const bool detailed = false) const;
	
	static void incorporateOverflow(TH1D* &);
	
	bool isBackground() const;
	bool isData() const;
	bool isSignal() const;
	
	std::pair<TH1D*, std::map<TString, TH1D*> > project(const int dim, const bool binForOverflow = false) const;
	
	bool setDebug(bool);
	void setFakeRate(TString, TString);
	void setFillColor(const Int_t fillColor);
	bool setRange(const char*, double, double, bool = true);
	bool setRange(const char*, double);
	bool setRange(const char*);
	bool setRange();

protected:
	void applyRelativeUncertainty(THnBase*, TString);
	void applyUncertainty(TString, THnBase*);

private:
	bool m_debug = false;
	TString m_filename;
	Int_t m_fillColor = -1;
	double m_lumi;
	TString m_name;
	TString m_selection;
	TString m_type;
	bool m_unordered;
	
	THnBase* m_hn = 0;
	std::map<TString, THnBase*> m_hProjectionUncertainties;
	
	std::map<TString, TString> m_fakerateMap;
	std::map<TString, double> m_flatUncertaintyMap;
	std::map<TString, TString> m_rangeStrings;
	std::map<TString, THnBase*> m_uncertaintyMap;
	std::vector<TString> m_weights;
	
	ClassDef(PhysicsContribution,1);
};

#endif
