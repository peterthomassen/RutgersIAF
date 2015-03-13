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
#include <TObject.h>
#include <TLorentzVector.h>
#include <TPRegexp.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h> 
#include <ctype.h>
#include <getopt.h>

#include "lheReader.h"

//
// constructors and destructor
//

struct commandLineParameters
{
  std::vector<std::string> infile;      // -i
  std::string outfile;                  // -o
  std::string Run;                      // -r 
  std::string Event;                    // -e
  std::string Lumi;                     // -l 
  std::string Debug;                    // -d

  std::string input;

  commandLineParameters(void) :
    outfile("defaultOutPutFileName.root"),
    Run("1"),              
    Event("1"),            
    Lumi("1"),          
    Debug("false")      
  {}
  
  void parseCommandLine(int argc, char **argv);

private:

  template <typename T> void getArg(T& pRetVal, char* arg) {

    if (arg != '\0') {
      std::istringstream(arg) >> pRetVal;
    }
  }
};

void commandLineParameters::parseCommandLine(int argc, char **argv)
{
  int opt;
  
  while ((opt = getopt(argc, argv, "o:i:r:e:l:d:h")) != -1) {

    switch(opt) {

    case 'i':
      getArg(input, optarg);
      infile.push_back(input);      

      while (optind < argc && *argv[optind] != '-'){

	if (TPRegexp("(\\.lhe)+").MatchB(argv[optind])) {
	  infile.push_back(argv[optind++]);
	}
	else
	  continue;
      }
      break;
    case 'o':     
      getArg(outfile, optarg);
      break;
    case 'r':
      getArg(Run, optarg);
      break;      
    case 'e':
      getArg(Event, optarg);
      break;
    case 'l':
      getArg(Lumi, optarg);
      break;
    case 'd':
      getArg(Debug, optarg);
      break;           
    case 'h':
      std::cout << "synopsis: lheReader -i <input lhe file> -o <target output file>\n"
		<< "-r [run number] -e [event number] -l [lumi number] -d [debug mode]" << std::endl;
      exit(1);
      break;      
    case ':':
      // missing option argument
      fprintf(stderr, "%s: option '-%c' requires an argument\n", argv[0], optopt);
      exit(1);
      break;
    case '?':
    default:
      // invalid option
      fprintf(stderr, "%s: option '-%c' is invalid: ignored\nUse -h for a list of options.\n", argv[0], optopt);
      exit(1);
      break;      
    }
  }
}

void lheReader::initialize(struct commandLineParameters* args) {

  this->setDebug(args->Debug.c_str());
  this->lhefile(args->infile);
  this->setRun(args->Run.c_str());
  this->setEvent(args->Event.c_str());
  this->setLumi(args->Lumi.c_str());
  this->ntuplizer(args->outfile.c_str());
}

lheReader::lheReader()
{
  setRun("1");
  setEvent("1");
  setLumi("1");

  m_debug = false;
}

lheReader::~lheReader()
{

}

//
// member functions
//

bool lheReader::getDebug()
{
  return m_debug;
}

void lheReader::setDebug(const char *db)
{
  std::stringstream ss(db);
  ss >> std::boolalpha >> m_debug;
}

void lheReader::lhefile(std::vector<std::string> lhefilename)
{
  inputfiles  = new std::map<std::string, std::ifstream*>;

  for (int i = 0; i < (int)lhefilename.size(); ++i) {
    inputfiles->insert(std::pair<std::string, std::ifstream*>(lhefilename[i], new std::ifstream));
    (*inputfiles)[lhefilename[i]]->open(lhefilename[i], std::ifstream::in);
  }
}

void lheReader::ntuplizer(TString output)
{

  std::string lheline;
  std::string beginevent = "<event>";
  std::string endevent = "</event>";

  Int_t event_count = 0;
  Int_t event_line_count = 0;

  bool eventswitch = false;

  TFile *fileoutput = new TFile(output,"RECREATE","Demo root file with trees");

  TTree *LHETree = new TTree("LHETree","Events in LHE File");

  LHETree->Branch("run",&run,"run/I");
  LHETree->Branch("event",&event,"event/I");
  LHETree->Branch("lumi",&lumi,"lumi/I");
  LHETree->Branch("particle_n",&particle_n,"particle_n/I");
  LHETree->Branch("processID",&processID,"processID/I");
  LHETree->Branch("event_weight",&event_weight,"event_weight/F");
  LHETree->Branch("factorization_scale",&factorization_scale,"factorization_scale/F");
  LHETree->Branch("alpha_em",&alpha_em,"alpha_em/F");
  LHETree->Branch("alpha_s",&alpha_s,"alpha_s/F");
  LHETree->Branch("pdgID","std::vector<Int_t>",&m_pdgID);
  LHETree->Branch("state","std::vector<Int_t>",&m_state);
  LHETree->Branch("mother1","std::vector<Int_t>",&m_mother1);
  LHETree->Branch("mother2","std::vector<Int_t>",&m_mother2);
  LHETree->Branch("color","std::vector<Int_t>",&m_color);
  LHETree->Branch("anticolor","std::vector<Int_t>",&m_anticolor);
  LHETree->Branch("Px","std::vector<Double_t>",&m_Px);
  LHETree->Branch("Py","std::vector<Double_t>",&m_Py);
  LHETree->Branch("Pz","std::vector<Double_t>",&m_Pz);
  LHETree->Branch("E","std::vector<Double_t>",&m_E);
  LHETree->Branch("mass","std::vector<Double_t>",&m_mass);
  LHETree->Branch("ctau","std::vector<Double_t>",&m_ctau);
  LHETree->Branch("spincosine","std::vector<Double_t>",&m_spincosine);
  LHETree->Branch("pt","std::vector<Double_t>",&m_pt);
  LHETree->Branch("eta","std::vector<Double_t>",&m_eta);
  LHETree->Branch("phi","std::vector<Double_t>",&m_phi);
  LHETree->Branch("energy","std::vector<Double_t>",&m_energy);

  if (!inputfiles->empty()) {

    std::map<std::string, std::ifstream*>::const_iterator fileinput;
    
    for (fileinput = inputfiles->begin(); fileinput != inputfiles->end(); ++fileinput) {
      
      if ((fileinput->second)->is_open()) { 
	
	// Store name of input file
	labelString += "\n" + fileinput->first;

	if (m_debug) {
	  std::cout << "File is open!!" << std::endl;
	}
	
	while (getline(*fileinput->second, lheline)) { 

	  // Ignore #-tag comments, especially needed for LHE files with jet matching and model information within the event block
	  if (TPRegexp("^#+").MatchB(lheline))
	    continue;

	  // Find begining of event
	  if (lheline == beginevent) {
	    eventswitch = true;

	    if (m_debug) {
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
	      ss >> particle_n >> processID >> event_weight >> factorization_scale >> alpha_em >> alpha_s;

	      if (m_debug) {
		std::cout << lheline << std::endl;
		std::cout << "particle_n = " << particle_n << std::endl;
		std::cout << "processID = " << processID << std::endl;
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

	      m_pdgID->push_back(pdgID);
	      m_state->push_back(state);
	      m_mother1->push_back(mother1);
	      m_mother2->push_back(mother2);
	      m_color->push_back(color);
	      m_anticolor->push_back(anticolor);
	      m_Px->push_back(Px);
	      m_Py->push_back(Py);
	      m_Pz->push_back(Pz);
	      m_E->push_back(E);
	      m_mass->push_back(Mass);
	      m_ctau->push_back(ctau);
	      m_spincosine->push_back(spincosine);

	      TLorentzVector temp;
	      temp.SetPxPyPzE(Px, Py, Pz , E);
	      
	      m_pt->push_back(temp.Pt());
	      
	      // Supress large eta value warnings by setting it to a large value by hand
	      if (temp.Pt() < 1e-10 && temp.Pz() > 0.0) {
		m_eta->push_back(10e10);
	      }
	      
	      else if (temp.Pt() < 1e-10 && temp.Pz() < 0.0) {
		m_eta->push_back(-10e10);
	      }
	      
	      else {
		m_eta->push_back(temp.Eta());
	      }
	      
	      m_phi->push_back(temp.Phi());
	      m_energy->push_back(temp.E());
	      
	      if (m_debug) {
		std::cout << lheline << std::endl;
		std::cout << pdgID << "    " << state << "    " << mother1 << "    " << mother2 << "  " 
			  << color << "    " << anticolor << "  " << Px << " " << Py << "  " << Pz << "  " 
			  << E << "  " << Mass << " " << ctau << " " << spincosine << std::endl;
	      }
	    }

	    // Find end of event
	    else if (lheline == endevent) {

	      eventswitch = false;
	      event_line_count = 0;
	      
	      LHETree->Fill();

	      m_pdgID->clear();
	      m_state->clear();
	      m_mother1->clear();
	      m_mother2->clear();
	      m_color->clear();
	      m_anticolor->clear();
	      m_Px->clear();
	      m_Py->clear();
	      m_Pz->clear();
	      m_E->clear();
	      m_mass->clear();
	      m_ctau->clear();
	      m_spincosine->clear();
	      m_pt->clear();
	      m_eta->clear();
	      m_phi->clear();
	      m_energy->clear();
	      
	      if (m_debug) {
		std::cout << "Found end of event!! " << eventswitch << std::endl;
	      }
	    }
	  }

	  // Find header file information and skip over it
	  else {
	    if (m_debug) {
	      std::cout << "Line skipped!!" << std::endl;
	    }
	    
	    continue;
	  }
	} // end while still lines in file loop
      } // end if file open
      else {
	std::cout << "The following file failed to open: " << fileinput->first  << std::endl;
      }
    } // end for input fils loop
  } // end of if input file is not empty

  // output file contains information of input files used
  label = labelString.Data();
  label.Write("listOfLHEFilesUsed", TObject::kOverwrite);
  
  LHETree->Print();
  LHETree->Write("",TObject::kOverwrite);

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
  commandLineParameters *args = new commandLineParameters();

  lheReader *handler = new lheReader();
  
  if (argc < 2) {  
    std::cout << "Usage: " << argv[0] << " -i <input.lhe> -o <output.root> -r [run] -e [event] -l [lumi] -d [debug flag]" << std::endl;
    return 1;
  }
    
  args->parseCommandLine(argc, argv);

  handler->initialize(args);
  
  delete handler;
  delete args;

  handler = NULL;
  args = NULL;
  
  return 0;
}

