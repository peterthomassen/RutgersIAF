#ifndef PeterTreeWriter_h
#define PeterTreeWriter_h

#include <TROOT.h>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeWriter.h"
#include <map>

class BaseHandler;
class TTree;
class TString;
class TFile;
//class TClonesArray;
class TBranch;

class PeterTreeWriter : public BaseTreeWriter{
public:
	PeterTreeWriter(BaseHandler*,TString);
	virtual ~PeterTreeWriter();
	
	virtual void finish();
	virtual void fillTree();

private:
	//TClonesArray* m_clonesarray;
	
	bool m_false;
	bool m_true;
	
	unsigned short m_fBits; // This tells us how many muckets in m_bits we need. It will usually be around m_nBits/8
	unsigned short m_nBits; // Number of bits in the event
	unsigned char m_bits[(1 << (sizeof(m_nBits)*8)) / sizeof(unsigned char)]; // This gives 2^(sizeof(nbits)*8) / sizeof(*m_bits) = 2^16 / 8 = 8192 buckets à 8 bit = 65536 bits
	
	std::map<TString, std::pair<TBranch*, TBranch*> > m_branches;
	std::map<TString, UInt_t> m_boolIndex;
	
	virtual void processVariable(TString, void*, TString);
	
	ClassDef(PeterTreeWriter,1);
};


#endif
