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
	
	void addBackground(PhysicsContribution*);
	void addData(PhysicsContribution*);
	void addSignal(PhysicsContribution*);
	
	void process(std::string, std::string);
	
	void setRange(const char*, double, double, bool = true);
	void setRange(const char*, double);
	void setRange(const char*);
	
	void write(const char*);

private:
	TString m_ofname;
	
	std::vector<PhysicsContribution*> m_data;
	std::vector<PhysicsContribution*> m_background;
	std::vector<PhysicsContribution*> m_signal;
	
	ClassDef(Assembler,1);
};

#endif
