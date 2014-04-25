///////////////////////////////////////////////////////////////////////
//
//   This Class produces a TTree from an LHE file
//
//   Written by: Emmanuel Contreras-Campana
//
//   Date: 04-25-2013
//
///////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>
#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include "lheReader.h"


void lheReader::ntuplizer(TString output)
{
  std::string lheline;
  std::string beginevent = "<event>";
  std::string endevent = "</event>";

  TFile *fileoutput = new TFile(output,"RECREATE","Demo root file with trees");

  TTree *LHETree = new TTree("LHETree","Events in LHE File");

  Int_t i = 0; // array index
  Int_t event_count = 0;

  bool eventswitch = false;
  bool debug = false;

  LHETree->Branch("run",&run,"run/I");
  LHETree->Branch("event",&event,"event/I");
  LHETree->Branch("lumi",lumi,"lumi/I");
  LHETree->Branch("particle_n",&mc_particle_n,"mc_particle_n/I");
  LHETree->Branch("pdgID",&mc_particle_pdgID,"mc_particle_pdgID[mc_particle_n]/I");
  LHETree->Branch("state",&mc_particle_state,"mc_particle_state[mc_particle_n]/I");
  LHETree->Branch("mother1",&mc_particle_mother1,"mc_particle_mother1[mc_particle_n]/I");
  LHETree->Branch("mother2",&mc_particle_mother2,"mc_particle_mother2[mc_particle_n]/I");
  LHETree->Branch("color",&mc_particle_color,"mc_particle_color[mc_particle_n]/I");
  LHETree->Branch("anticolor",&mc_particle_anticolor,"mc_particle_anticolor[mc_particle_n]/I");
  LHETree->Branch("Px",&mc_particle_Px,"mc_particle_Px[mc_particle_n]/F");
  LHETree->Branch("Py",&mc_particle_Py,"mc_particle_Py[mc_particle_n]/F");
  LHETree->Branch("Pz",&mc_particle_Pz,"mc_particle_Pz[mc_particle_n]/F");
  LHETree->Branch("E",&mc_particle_E,"mc_particle_E[mc_particle_n]/F");
  LHETree->Branch("mass",&mc_particle_mass,"mc_particle_mass[mc_particle_n]/F");
  LHETree->Branch("ctau",&mc_particle_ctau,"mc_particle_ctau[mc_particle_n]/D");
  LHETree->Branch("spincosine",&mc_particle_spincosine,"mc_particle_spincosine[mc_particle_n]/D");
  LHETree->Branch("pt",&mc_particle_pt,"mc_particle_pt[mc_particle_n]/F");
  LHETree->Branch("eta",&mc_particle_eta,"mc_particle_eta[mc_particle_n]/F");
  LHETree->Branch("phi",&mc_particle_phi,"mc_particle_phi[mc_particle_n]/F");
  LHETree->Branch("energy",&mc_particle_energy,"mc_particle_energy[mc_particle_n]/F");

  if (fileinput.is_open()) {

    if (debug) {
      std::cout << "File is open!!" << std::endl;
    }

    while (getline(fileinput, lheline)) {

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

        if (debug) {
          std::cout << "lheline " << lheline << std::endl;
          std::cout << "lheline.length " << lheline.length() << std::endl;
        }

        // 66 characters in Madgraph and 68 characters in Pythia
        if (lheline.length() > 65 && lheline.length() < 69) {

          std::stringstream ss(lheline);
          ss >> mc_particle_n;

          if (debug) {
            std::cout << "mc_particle_n = " << mc_particle_n << std::endl;
          }
        }

        else if (lheline != "</event>") {

          std::stringstream ss(lheline);

          ss >> pdgID >> state >> mother1 >> mother2 >> color >> anticolor
             >> Px >> Py >> Pz >> E >> Mass >> ctau >> spincosine;

          if (debug) {
            std::cout << lheline << std::endl;
            std::cout << pdgID << "    " << state << "    " << mother1 << "    " << mother2 << "  " 
                      << color << "    " << anticolor << "  " << Px << " " << Py << "  " << Pz << "  " 
                      << E << "  " << Mass << " " << ctau << " " << spincosine << std::endl;
          }

          mc_particle_pdgID[i] = pdgID;
          mc_particle_state[i] = state;
          mc_particle_mother1[i] = mother1;
          mc_particle_mother2[i] = mother2;
          mc_particle_color[i] = color;
          mc_particle_anticolor[i] = anticolor;
          mc_particle_Px[i] = Px;
          mc_particle_Py[i] = Py;
          mc_particle_Pz[i] = Pz;
          mc_particle_E[i] = E;
          mc_particle_mass[i] = Mass;
          mc_particle_ctau[i] = ctau;
          mc_particle_spincosine[i] = spincosine;

          TLorentzVector temp;
          temp.SetPxPyPzE(Px, Py, Pz , E);

          mc_particle_pt[i] = temp.Pt();

          // Supress large eta value warnings by setting it to a large value by hand
          if (temp.Pt() == 0.0 && temp.Pz() > 0.0) {
            mc_particle_eta[i] = 10e10;
          }

          else if (temp.Pt() == 0.0 && temp.Pz() < 0.0) {
            mc_particle_eta[i] = -10e10;
          }

          else {
            mc_particle_eta[i] = temp.Eta();
          }

          mc_particle_phi[i] = temp.Phi();
          mc_particle_energy[i] = temp.E();

          ++i;

          if (debug) {
            std::cout << "mc_particle_pdgID = " << pdgID << std::endl;
          }
        } // end length 136 loop

        else if (lheline == endevent) {
          i = 0;
          eventswitch = false;

          LHETree->Fill();

          if (debug) {
            std::cout << "Found end of event!! " << eventswitch << std::endl;
          }
        }
      }

      // This else-statement is intended to skip over header information
      // from either MadGraph or Pythia LHE files
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

void lheReader::lhefile(TString lhefilename)
{
  fileinput.open(lhefilename);
}

Int_t lheReader::getRun(void)
{
  return run_number;
}

void lheReader::setRun(Int_t r)
{
  run_number = r;
}

Int_t lheReader::getEvent(void)
{
  return event_number;
}

void lheReader::setEvent(Int_t e)
{
  event_number = e;
}

Int_t lheReader::getLumi(void)
{
  return lumi_number;
}
 
void lheReader::setLumi(Int_t l)
{
  lumi_number = l;
}

lheReader::lheReader()
{
  setRun(1);
  setEvent(1);
  setLumi(1);
}

lheReader::~lheReader()
{

}

int main(int argc, char **argv)
{
  lheReader *handler = new lheReader();

  //"/cms/emmanuel/2012/coNLSP/store/lhe/delta0/coNLSP_chargino1400_gluino1700_delta0.lhe"
  //"coNLSP_chargino1400_gluino1700_delta0.root"

  if (argc < 1) {
    std::cout << "Please specify the LHE filename!" << std::endl;
  }

  handler->lhefile(argv[1]);
  handler->ntuplizer(argv[2]);

  delete handler;
  return 0;
}
