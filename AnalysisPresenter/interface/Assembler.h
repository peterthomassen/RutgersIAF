#ifndef Assembler_h
#define Assembler_h

#include <map>
#include <string>
#include <vector>

#include "TROOT.h"

#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

class Assembler : public TObject {

public:
	Assembler(TString);
	virtual ~Assembler();
	
	bool addData(PhysicsContribution*);
	
	THnBase* process(std::string, std::string);
	
	void writeTablePT(THnBase*);
	void writeMET(THnBase*);
	bool setAxisRange(THnBase*, const char*, double, double, bool = true);
	bool setAxisRange(THnBase*, const char*, double);
	bool setAxisRange(THnBase*, const char*);

private:
	TString m_ofname;
	
	std::vector<PhysicsContribution*> m_data;
	std::vector<PhysicsContribution*> m_background;
	std::vector<PhysicsContribution*> m_signal;
	
	ClassDef(Assembler,1);
};

#endif
