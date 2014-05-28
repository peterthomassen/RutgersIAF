#ifndef TheoryTreeWriter_h
#define TheoryTreeWriter_h

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeWriter.h"

class BaseHandler;

class TheoryTreeWriter : public BaseTreeWriter {

  public:

    TheoryTreeWriter(BaseHandler*,TString); //Constructor
    virtual ~TheoryTreeWriter(); //destructor

    virtual void finish();
    virtual void fillTree();

    virtual void addObject(TLorentzVector fourvec, double type, double btag, double dum1, double dum2, double dum3, double dum4, double dum5, double dum6, double dum7, double dum8);
    virtual void addObject(TLorentzVector fourvec, double type, double btag, double dum1, double dum2, double dum3, double dum4, double dum5, double dum6, double dum7, double dum8, double scalar);
    virtual void addObject(TLorentzVector fourvec, double type, double btag);
    virtual void addMET(double type, double pt, double phi);
    virtual void addScalar(double type, double value);
    virtual void addEvtNum(double run, double evt, double lumi);

    int m_debug;
    int m_nobject;

    double m_weight;

    std::vector<double>* m_object_type;
    std::vector<double>* m_object_btag;
    std::vector<double>* m_object_dum1;
    std::vector<double>* m_object_dum2;
    std::vector<double>* m_object_dum3;
    std::vector<double>* m_object_dum4;
    std::vector<double>* m_object_dum5;
    std::vector<double>* m_object_dum6;
    std::vector<double>* m_object_dum7;
    std::vector<double>* m_object_dum8;
    std::vector<double>* m_object_scalar;
    std::vector<double>* m_evtnum;

    TClonesArray *m_object;

    Double_t m_theoryID_photon;
    Double_t m_theoryID_electron;
    Double_t m_theoryID_muon;
    Double_t m_theoryID_tau_isotrack;
    Double_t m_theoryID_tau_1prongpi0s;
    Double_t m_theoryID_jet;
    Double_t m_theoryID_pfmet;
    Double_t m_theoryID_tcmet;
    Double_t m_theoryID_calomet;
    Double_t m_theoryID_st;
    Double_t m_theoryID_lt;
    Double_t m_theoryID_ht;
    Double_t m_theoryID_dymass;
    Double_t m_theoryID_wtmass;

  private:

    ClassDef(TheoryTreeWriter,1);
};

#endif
