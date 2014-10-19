////////////////////////////////////////////////////////////////////////
//                                                                    //
//   This Class produces a TH1D hisogram from an kfactorReader file   //
//                                                                    //
//   Written by: Christian Contreras-Campana and                      //
//               Emmanuel Contreras-Campana                           //
//                                                           	      //
//   Date: 10-15-2014                                        	      //
//                                                           	      //
////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>

#include "kfactorReader.h"

//
// constructors and destructor
//

struct commandLineParameters 
{
public:
  // default constructor
  commandLineParameters(void) : Debug("false") {}
  
  // commandLineParameters methods
  void parseCommandLine(int argc, char **argv);

  // commandLineParameters data members
  std::vector<std::string> infile;      // -i                                                                     
  std::string outfile;                  // -o                                                                     
  std::string Debug;                    // -d                                                                    

  std::string input;
  Int_t opt;

private:
  // private commandLineParameters methods
  template <typename T> void getArg(T& pRetVal, char* arg) {

    if (arg != '\0') {
      std::istringstream(arg) >> pRetVal;
    }
  }
};

void commandLineParameters::parseCommandLine(int argc, char **argv)
{
  while ((opt = getopt(argc, argv, "o:i:d:h")) != -1) {

    switch(opt) {

    case 'i':
      getArg(input, optarg);
      infile.push_back(input);      
 
     while (optind < argc && *argv[optind] != '-'){
	getArg(input, optarg);
	infile.push_back(input);
	optind++;
      }
      break;
    case 'o':
      getArg(outfile, optarg);
      break;
    case 'd':
      getArg(Debug, optarg); 
      break;           
    case 'h':
      std::cout << "synopsis: kfactorReader -i <input kfactorReader file> -o <target output file>\n"
		<< "-d [debug mode]" << std::endl;
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

void kfactorReader::initialize(struct commandLineParameters* args)
{
  this->setDebug(args->Debug.c_str());
  this->kfactorReaderfile(args->infile);
  this->makeHistograms(args->outfile.c_str());
}

kfactorReader::kfactorReader()
{
  m_debug = false;
}

kfactorReader::~kfactorReader()
{
  // delete dynamically allocated objects                                                                                                                               
  for (Int_t i = 0; i < (Int_t)inputfiles.size(); ++i) {
    delete inputfiles[i];
  }
}

//
// member functions
//

bool kfactorReader::getDebug()
{
  return m_debug;
}

void kfactorReader::setDebug(const char *db)
{
  std::stringstream ss(db);
  ss >> std::boolalpha >> m_debug;
}

void kfactorReader::kfactorReaderfile(std::vector<std::string> kfactorfilenames)
{
  for(Int_t i = 0; i < (Int_t)kfactorfilenames.size(); ++i) {
 
   inputfiles.push_back(new std::ifstream);
   inputfiles[i]->open(kfactorfilenames[i]);    

  }
}

void kfactorReader::makeHistograms(TString output)
{
  TFile *fileoutput = new TFile(output,"RECREATE","k-factor root file");
  
  TH1D *h_nominal_kfactor = new TH1D("nominal_kfactor", "Nominal k-factor", 1000, 0, 1000);
  TH1D *h_half_nominal_kfactor = new TH1D("half_nominal_kfactor", "Half nominal k-factor", 1000, 0, 1000);
  TH1D *h_twice_nominal_kfactor = new TH1D("twice_nominal_kfactor", "Twice nominal k-factor", 1000, 0, 1000);

  if(!inputfiles.empty()) {
    
    for (Int_t i = 0; i < (Int_t)inputfiles.size(); ++i) {

      if (inputfiles[i]->is_open()) {

	if (m_debug) {
	  std::cout << "File is open!!" << std::endl;
	}
	

	while (getline(*(inputfiles[i]), kfactorline)) {

	  std::stringstream ss(kfactorline);	 
	  ss >> processID >> event_weight >> factorization_scale;

	  labelString  += "\n" + kfactorline;
	    
	  if (m_debug) {
	    std::cout << "k-factor line = " << kfactorline << std::endl;
	    std::cout << "processID = " << processID << std::endl;
	    std::cout << "event_weight = " << event_weight << std::endl;
	    std::cout << "factorization_scale = " << factorization_scale << std::endl;
	  }
	  
	  if (factorization_scale == "nominal") {
	    h_nominal_kfactor->Fill(processID, event_weight);
	  }

	  else if (factorization_scale == "halfnominal") {
            h_half_nominal_kfactor->Fill(processID, event_weight);
          }

	  else if (factorization_scale == "twicenominal") {
            h_twice_nominal_kfactor->Fill(processID, event_weight);
          }
	} // end of while getline
      } // end of is open
    } // end for input files loop  
  } // end of if input file is not empty 

  label = labelString.Data();

  h_nominal_kfactor->Write("", TObject::kOverwrite);
  h_half_nominal_kfactor->Write("", TObject::kOverwrite);
  h_twice_nominal_kfactor->Write("", TObject::kOverwrite);

  label.Write("label", TObject::kOverwrite);
  fileoutput->Close();
}


int main(int argc, char **argv)
{
  kfactorReader *handler = new kfactorReader();

  commandLineParameters *args = new commandLineParameters();
  
  if (argc < 2) {  
    std::cout << "Usage: " << argv[0] << " -i <input.txt> -o <output.root>" << std::endl;
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
