#ifndef kfactorReader_h
#define kfactorReader_h

#include <string>
#include <vector>
#include <fstream>

#include <TString.h>

//
// class declaration
//
class kfactorReader {

  public:
    // default constructor
    kfactorReader(void);
 
    // virtual destructor
    ~kfactorReader();

    // lheReader ifstream
    std::vector<std::ifstream* > inputfiles;

    bool m_debug;

    // kfactorReader data members
    Int_t    processID;
    Float_t  event_weight;    

    // kfactorReader methods
    bool getDebug(void);
    void setDebug(const char *);

    void kfactorReaderfile(std::vector<std::string>);
    void makeHistograms(TString);

    void initialize(struct commandLineParameters *);

  private:
    std::string kfactorline;
    std::string factorization_scale;

    TString labelString;
    TObjString label;

  protected:

};

#endif
