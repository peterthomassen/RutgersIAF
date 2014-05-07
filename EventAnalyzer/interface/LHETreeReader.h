//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#ifndef LHETreeReader_h
#define LHETreeReader_h

#include <string>
#include <iostream>
#include <sstream>
#include <TLorentzVector.h>
#include <vector>

#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"

class BaseHandler;
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class LHETreeReader : public BaseTreeReader {

  friend class BaseHandler;
public :


   LHETreeReader(TTree *tree);
   virtual ~LHETreeReader();

 protected:
   void makeProducts();

   void createMCParticles();
   void createVariables();

 private:
   Int_t run;
   Int_t event;
   Int_t lumi;
   Int_t particle_n;
   Int_t processID;
   
   Float_t event_weight;
   Float_t factorization_scale;
   Float_t alpha_em;
   Float_t alpha_s;
   
   std::vector<Int_t> *m_pdgID;
   std::vector<Int_t> *m_state;
   std::vector<Int_t> *m_mother1;
   std::vector<Int_t> *m_mother2;
   std::vector<Int_t> *m_color;
   std::vector<Int_t> *m_anticolor;
   std::vector<Double_t> *m_Px;
   std::vector<Double_t> *m_Py;
   std::vector<Double_t> *m_Pz;
   std::vector<Double_t> *m_E;
   std::vector<Double_t> *m_ctau;
   std::vector<Double_t> *m_spincosine;   
   
   ClassDef(LHETreeReader,1);
};

#endif

