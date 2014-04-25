#ifndef lheReader_h
#define lheReader_h

#include <fstream>

#include <TString.h>

class lheReader {

  public:
    // Default constructor
      lheReader(void);
 
    // Virtual destructor
      ~lheReader();

    // lheReader ifstream
      ifstream fileinput;

    // lheReader Arrays and Variables
      static const Int_t  MAXMCPART = 1000;

      Int_t    run;
      Int_t    event;
      Int_t    lumi;
      Int_t    mc_particle_n;
      Int_t    mc_particle_pdgID[MAXMCPART];
      Int_t    mc_particle_state[MAXMCPART];
      Int_t    mc_particle_mother1[MAXMCPART];
      Int_t    mc_particle_mother2[MAXMCPART];
      Int_t    mc_particle_color[MAXMCPART];
      Int_t    mc_particle_anticolor[MAXMCPART];
      Float_t  mc_particle_Px[MAXMCPART];
      Float_t  mc_particle_Py[MAXMCPART];
      Float_t  mc_particle_Pz[MAXMCPART];
      Float_t  mc_particle_E[MAXMCPART];
      Float_t  mc_particle_mass[MAXMCPART];
      Double_t mc_particle_ctau[MAXMCPART];
      Double_t mc_particle_spincosine[MAXMCPART];

      Float_t  mc_particle_pt[MAXMCPART];
      Float_t  mc_particle_eta[MAXMCPART];
      Float_t  mc_particle_phi[MAXMCPART];
      Float_t  mc_particle_energy[MAXMCPART];

      Int_t    n;
      Int_t    pdgID;
      Int_t    state;
      Int_t    mother1;
      Int_t    mother2;
      Int_t    color;
      Int_t    anticolor;
      Float_t  Px;
      Float_t  Py;
      Float_t  Pz;
      Float_t  E;
      Float_t  Mass;
      Double_t ctau;
      Double_t spincosine;

    // lheReader Methods
      void lhefile(TString);
      void ntuplizer(TString);

      Int_t getRun(void);
      void setRun(Int_t);

      Int_t getEvent(void);
      void setEvent(Int_t);

      Int_t getLumi(void);
      void setLumi(Int_t);

  private:
      Int_t    run_number;
      Int_t    event_number;
      Int_t    lumi_number;

  protected:

};

#endif
