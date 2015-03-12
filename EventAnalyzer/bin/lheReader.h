#ifndef lheReader_h
#define lheReader_h

#include <vector>
#include <fstream>

#include <TString.h>
#include <memory>

//
// class declaration
//
class lheReader {

  public:
    // default constructor
    lheReader(void);
 
    // virtual destructor
    ~lheReader();

    // lheReader ifstream
    std::map<std::string, std::ifstream *> *inputfiles;

    bool m_debug;

    // lheReader data members
    Int_t    run;
    Int_t    event;
    Int_t    lumi;
    Int_t    particle_n;
    Int_t    processID;

    Float_t  event_weight;
    Float_t  factorization_scale;
    Float_t  alpha_em;
    Float_t  alpha_s;

    std::vector<Int_t>     *m_pdgID;
    std::vector<Int_t>     *m_state;
    std::vector<Int_t>     *m_mother1;
    std::vector<Int_t>     *m_mother2;
    std::vector<Int_t>     *m_color;
    std::vector<Int_t>     *m_anticolor;
    std::vector<Double_t>  *m_Px;
    std::vector<Double_t>  *m_Py;
    std::vector<Double_t>  *m_Pz;
    std::vector<Double_t>  *m_E;
    std::vector<Double_t>  *m_mass;
    std::vector<Double_t>  *m_ctau;
    std::vector<Double_t>  *m_spincosine;
    std::vector<Double_t>  *m_pt;
    std::vector<Double_t>  *m_eta;
    std::vector<Double_t>  *m_phi;
    std::vector<Double_t>  *m_energy;

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
    Float_t  ctau;
    Float_t  spincosine;

    // lheReader methods
    bool getDebug(void);
    void setDebug(const char *);

    void lhefile(std::vector<std::string>);
    void ntuplizer(TString);

    Int_t getRun(void);
    void setRun(const char *);

    Int_t getEvent(void);
    void setEvent(const char *);

    Int_t getLumi(void);
    void setLumi(const char *);

    void initialize(struct commandLineParameters *);

  private:
    Int_t    run_number;
    Int_t    event_number;
    Int_t    lumi_number;

    TString labelString;
    TObjString label;

  protected:

};

#endif

