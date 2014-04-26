//////////////////////////////////////////////////////
//                                                  //
//   This Class produces a TTree from an LHE file   //
//                                                  //
//   Written by: Emmanuel Contreras-Campana and     //
//               Christian Contreras-Campana        //
//                                                  //
//   Date: 04-25-2013                               //
//                                                  //
//////////////////////////////////////////////////////

#include <string>
#include <sstream>
#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include "lheReader.h"

//
// constructors and destructor
//

lheReader::lheReader()
{
  setRun("1");
  setEvent("1");
  setLumi("1");

  debug = false;
}

lheReader::~lheReader()
{

}

//
// member functions
//

bool lheReader::getDebug()
{
  return debug;
}

void lheReader::setDebug(const char *db)
{
  std::stringstream ss(db);
  ss >> std::boolalpha >> debug;
}

void lheReader::lhefile(TString lhefilename)
{
  fileinput.open(lhefilename);
}

void lheReader::ntuplizer(TString output)
{
  std::string lheline;
  std::string beginevent = "<event>";
  std::string endevent = "</event>";

  Int_t i = 0; // array index
  Int_t event_count = 0;
  Int_t event_line_count = 0;

  bool eventswitch = false;

  TFile *fileoutput = new TFile(output,"RECREATE","Demo root file with trees");

  TTree *LHETree = new TTree("LHETree","Events in LHE File");

  LHETree->Branch("run",&run,"run/I");
  LHETree->Branch("event",&event,"event/I");
  LHETree->Branch("lumi",&lumi,"lumi/I");
  LHETree->Branch("particle_n",&particle_n,"particle_n/I");
  LHETree->Branch("process_ID",&process_ID,"process_ID/I");
  LHETree->Branch("event_weight",&event_weight,"event_weight/F");
  LHETree->Branch("factorization_scale",&factorization_scale,"factorization_scale/F");
  LHETree->Branch("alpha_em",&alpha_em,"alpha_em/F");
  LHETree->Branch("alpha_s",&alpha_s,"alpha_s/F");
  LHETree->Branch("pdgID","std::vector<Int_t>",&particle_pdgID);
  LHETree->Branch("state","std::vector<Int_t>",&particle_state);
  LHETree->Branch("mother1","std::vector<Int_t>",&particle_mother1);
  LHETree->Branch("mother2","std::vector<Int_t>",&particle_mother2);
  LHETree->Branch("color","std::vector<Int_t>",&particle_color);
  LHETree->Branch("anticolor","std::vector<Int_t>",&particle_anticolor);
  LHETree->Branch("Px","std::vector<Double_t>",&particle_Px);
  LHETree->Branch("Py","std::vector<Double_t>",&particle_Py);
  LHETree->Branch("Pz","std::vector<Double_t>",&particle_Pz);
  LHETree->Branch("E","std::vector<Double_t>",&particle_E);
  LHETree->Branch("mass","std::vector<Double_t>",&particle_mass);
  LHETree->Branch("ctau","std::vector<Double_t>",&particle_ctau);
  LHETree->Branch("spincosine","std::vector<Double_t>",&particle_spincosine);
  LHETree->Branch("pt","std::vector<Double_t>",&particle_pt);
  LHETree->Branch("eta","std::vector<Double_t>",&particle_eta);
  LHETree->Branch("phi","std::vector<Double_t>",&particle_phi);
  LHETree->Branch("energy","std::vector<Double_t>",&particle_energy);

  if (fileinput.is_open()) {

    if (debug) {
      std::cout << "File is open!!" << std::endl;
    }

    while (getline(fileinput, lheline)) {

      // Find begining of event
      if (lheline == beginevent) {
        eventswitch = true;

        if (debug) {
          std::cout << "Found begining of event!! " << eventswitch << std::endl;
          std::cout << "Inside event!!" << std::endl;
        }

        ++event_count;

        run = getRun();
        event = event_count + getEvent() - 1;
        lumi = getLumi();

        continue;
      }

      if (eventswitch) {

        ++event_line_count;

        // Find line with event level information
        if (event_line_count == 1) {

          std::stringstream ss(lheline);
          ss >> particle_n >> process_ID >> event_weight >> factorization_scale >> alpha_em >> alpha_s;

          if (debug) {
            std::cout << lheline << std::endl;
            std::cout << "particle_n = " << particle_n << std::endl;
            std::cout << "process_ID = " << process_ID << std::endl;
            std::cout << "event_weight = " << event_weight << std::endl;
            std::cout << "factorization_scale = " << factorization_scale << std::endl;
            std::cout << "alpha_em = " << alpha_em << std::endl;
            std::cout << "alpha_s = " << alpha_s << std::endl;
          }
        }

        // Find line with particle level information
        else if (event_line_count > 1 && lheline != "</event>") {

          std::stringstream ss(lheline);

          ss >> pdgID >> state >> mother1 >> mother2 >> color >> anticolor
             >> Px >> Py >> Pz >> E >> Mass >> ctau >> spincosine;

          particle_pdgID->push_back(pdgID);
          particle_state->push_back(state);
          particle_mother1->push_back(mother1);
          particle_mother2->push_back(mother2);
          particle_color->push_back(color);
          particle_anticolor->push_back(anticolor);
          particle_Px->push_back(Px);
          particle_Py->push_back(Py);
          particle_Pz->push_back(Pz);
          particle_E->push_back(E);
          particle_mass->push_back(Mass);
          particle_ctau->push_back(ctau);
          particle_spincosine->push_back(spincosine);

          TLorentzVector temp;
          temp.SetPxPyPzE(Px, Py, Pz , E);

          particle_pt->push_back(temp.Pt());

          // Supress large eta value warnings by setting it to a large value by hand
          if (temp.Pt() == 0.0 && temp.Pz() > 0.0) {
            particle_eta->push_back(10e10);
          }

          else if (temp.Pt() == 0.0 && temp.Pz() < 0.0) {
            particle_eta->push_back(-10e10);
          }

          else {
            particle_eta->push_back(temp.Eta());
          }

          particle_phi->push_back(temp.Phi());
          particle_energy->push_back(temp.E());

          ++i;

          if (debug) {
            std::cout << lheline << std::endl;
            std::cout << pdgID << "    " << state << "    " << mother1 << "    " << mother2 << "  " 
                      << color << "    " << anticolor << "  " << Px << " " << Py << "  " << Pz << "  " 
                      << E << "  " << Mass << " " << ctau << " " << spincosine << std::endl;
          }
        }

        // Find end of event
        else if (lheline == endevent) {
          i = 0;
          eventswitch = false;
          event_line_count = 0;

          LHETree->Fill();

          particle_pdgID->clear();
          particle_state->clear();
          particle_mother1->clear();
          particle_mother2->clear();
          particle_color->clear();
          particle_anticolor->clear();
          particle_Px->clear();
          particle_Py->clear();
          particle_Pz->clear();
          particle_E->clear();
          particle_mass->clear();
          particle_ctau->clear();
          particle_spincosine->clear();
          particle_pt->clear();
          particle_eta->clear();
          particle_phi->clear();
          particle_energy->clear();

          if (debug) {
            std::cout << "Found end of event!! " << eventswitch << std::endl;
          }
        }
      }

      // Find header file information and skip over it
      else {
        if (debug) {
          std::cout << "Line skipped!!" << std::endl;
        }

        continue;
      }
    }  // end while still lines in file loop
  } // end if file open

  LHETree->Print();
  LHETree->Write();

  fileoutput->Close();
}

Int_t lheReader::getRun(void)
{
  return run_number;
}

void lheReader::setRun(const char *r)
{
  std::stringstream ss(r);
  ss >> run_number;
}

Int_t lheReader::getEvent(void)
{
  return event_number;
}

void lheReader::setEvent(const char *e)
{
  std::stringstream ss(e);
  ss >> event_number;
}

Int_t lheReader::getLumi(void)
{
  return lumi_number;
}
 
void lheReader::setLumi(const char *l)
{
  std::stringstream ss(l);
  ss >> lumi_number;
}

int main(int argc, char **argv)
{
  lheReader *handler = new lheReader();

  if (argc < 2) {
    std::cout << "Please specify the LHE filename!" << std::endl;
  }

  else if (argc == 4) {
    handler->setRun(argv[3]);
  }

  else if (argc == 5) {
    handler->setRun(argv[3]);
    handler->setEvent(argv[4]);
  }

  else if (argc == 6) {
    handler->setRun(argv[3]);
    handler->setEvent(argv[4]);
    handler->setLumi(argv[5]);
  }

  else if (argc == 7) {
    handler->setRun(argv[3]);
    handler->setEvent(argv[4]);
    handler->setLumi(argv[5]);
    handler->setDebug(argv[6]);
  }

  else {
    std::cout << "You have specified too many arguments!" << std::endl;
  }

  handler->lhefile(argv[1]);
  handler->ntuplizer(argv[2]);

  delete handler;

  return 0;
}
