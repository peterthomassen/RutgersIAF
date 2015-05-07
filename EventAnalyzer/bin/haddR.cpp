/*
  2014-04-11
  Peter Thomassen <peter.thomassen@cern.ch>
  
  This program will add histograms and Trees from a list of root files and write them to a target 
  root file (like hadd). It has special treatment for trees created by the Rutgers EventAnalyer.
  This software is based on the ROOT hadd tool.
*/

#include "RConfig.h"
#include <string>
#include "TFile.h"
#include "THashList.h"
#include "TKey.h"
#include "TObjString.h"
#include "Riostream.h"
#include "TClass.h"
#include "TSystem.h"
#include <stdlib.h>

#include "TFileMerger.h"

#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "TBranch.h"
#include "TBranchElement.h"
#include "TPRegexp.h"
#include "TString.h"
#include "TTree.h"

using namespace std;

Bool_t mergeTreeR(TString targetname, std::vector<TString> inputFiles, const char* treeName) {
	cout << "Now adding Rutgers tree " << treeName << " ";
	TFile* outfile = new TFile(targetname, "UPDATE");
	
	outfile->cd();
	TTree* outTree = new TTree(treeName, "");
	
	std::unordered_map<std::string, std::vector<double>* >  mapD;
	std::unordered_map<std::string, std::vector<int>* >     mapI;
	std::unordered_map<std::string, std::vector<long>* >    mapL;
	std::unordered_map<std::string, std::vector<TString>* > mapTString;
	
	std::unordered_map<std::string, UInt_t> boolIndex;
	std::vector<std::string> outAliases;
	std::vector<unsigned char> outBits;
	
	double n = 0;
	bool success = true;
	bool weights = false;
	
	for(size_t i = 0; i < inputFiles.size(); ++i) {
		cout << ((i % 10 == 9) ? '|' : '.') << flush;
		
		TFile* f = new TFile(inputFiles[i]);
		TTree* curTree = (TTree*)(f->Get(treeName));
		outfile->cd();
		
		if(i == 0) {
			outTree->SetTitle(curTree->GetTitle());
			weights = curTree->GetBranch("WEIGHT");
		}
		
		if(weights != (bool)(curTree->GetBranch("WEIGHT"))) {
			cerr << endl << "Can't add events with weights and events without, aborting" << endl;
			success = false;
			break;
		}
		
		if(weights) {
			n += 1./curTree->GetWeight();
		}
		
		std::vector<UInt_t> boolPositionMap;
		std::vector<unsigned char>* inBits = NULL;
		TBranchElement* branchElement;
		TIterator* it = curTree->GetListOfBranches()->MakeIterator();
		while( (branchElement = (TBranchElement*)it->Next()) ) {
			std::string branchName = branchElement->GetName();
			if(branchName == "bits") {
				if(!curTree->GetListOfAliases()) {
					throw std::logic_error("trouble reading aliases");
				}
				TIterator* jt = curTree->GetListOfAliases()->MakeIterator();
				TNamed* alias;
				while( (alias = (TNamed*)jt->Next()) ) {
					TObjArray *matches = TPRegexp("\\(bits\\[([0-9]+)\\] & \\(1 << ([0-9]+)\\)\\) > 0").MatchS(alias->GetTitle());
					if(matches->GetLast() > 0) {
						int idx = ((TObjString *)matches->At(1))->GetString().Atoi();
						int off = ((TObjString *)matches->At(2))->GetString().Atoi();
						if(idx * (sizeof(unsigned char) * 8) + off != boolPositionMap.size()) {
							throw std::logic_error("trouble reading aliases");
						}
						if(boolIndex.find(alias->GetName()) == boolIndex.end()) {
							outAliases.push_back(alias->GetName());
							boolIndex.insert(make_pair(alias->GetName(), boolIndex.size()));
						}
						boolPositionMap.push_back(boolIndex[alias->GetName()]);
					} else {
						if(!outTree->GetAlias(alias->GetName())) {
							outTree->SetAlias(alias->GetName(), alias->GetTitle());
						}
					}
				}
				
				if(!outTree->GetBranch("bits")) {
					TBranch* newBranch = outTree->Branch("bits", &outBits);
					for(Long64_t i = 0; i < outTree->GetEntries(); ++i) {
						newBranch->Fill();
					}
				}
				curTree->SetBranchAddress("bits", &inBits);
				continue;
			}
			
			TString className  = branchElement->GetClassName();
//			cout << branchElement->GetClassName() << " " << branchElement->GetName() << endl;
			TBranch* newBranch = NULL;
			if(className == "vector<double>") {
				if(mapD.find(branchName) == mapD.end()) {
//					cout << "Adding branch " << branchName << endl;
					auto insPair = mapD.insert(make_pair(branchName, new vector<double>));
					newBranch = outTree->Branch(branchName.c_str(), insPair.first->second, 32000, 0);
				}
			} else if(className == "vector<int>") {
				if(mapI.find(branchName) == mapI.end()) {
//					cout << "Adding branch " << branchName << endl;
					auto insPair = mapI.insert(make_pair(branchName, new vector<int>));
					newBranch = outTree->Branch(branchName.c_str(), insPair.first->second, 32000, 0);
				}
			} else if(className == "vector<long>") {
				if(mapL.find(branchName) == mapL.end()) {
//					cout << "Adding branch " << branchName << endl;
					auto insPair = mapL.insert(make_pair(branchName, new vector<long>));
					newBranch = outTree->Branch(branchName.c_str(), insPair.first->second, 32000, 0);
				}
			} else if(className == "vector<TString>") {
				if(mapTString.find(branchName) == mapTString.end()) {
//					cout << "Adding branch " << branchName << endl;
					auto insPair = mapTString.insert(make_pair(branchName, new vector<TString>));
					newBranch = outTree->Branch(branchName.c_str(), insPair.first->second, 32000, 0);
				}
			} else {
				throw std::runtime_error("unsupported branch type");
			}
			
			if(newBranch) {
//				cout << "Filling new branch, quantity " << outTree->GetEntries() << endl;
				for(Long64_t i = 0; i < outTree->GetEntries(); ++i) {
					newBranch->Fill();
				}
			}
		}
		
		for(auto &pair : mapD) {
			pair.second->clear();
			if(curTree->GetBranch(pair.first.c_str())) {
//				cout << "Setting address of branch " << pair.first << endl;
				curTree->SetBranchAddress(pair.first.c_str(), &pair.second);
			}
		}
		for(auto &pair : mapI) {
			pair.second->clear();
			if(curTree->GetBranch(pair.first.c_str())) {
//				cout << "Setting address of branch " << pair.first << endl;
				curTree->SetBranchAddress(pair.first.c_str(), &pair.second);
			}
		}
		for(auto &pair : mapL) {
			pair.second->clear();
			if(curTree->GetBranch(pair.first.c_str())) {
//				cout << "Setting address of branch " << pair.first << endl;
				curTree->SetBranchAddress(pair.first.c_str(), &pair.second);
			}
		}
		for(auto &pair : mapTString) {
			pair.second->clear();
			if(curTree->GetBranch(pair.first.c_str())) {
//				cout << "Setting address of branch " << pair.first << endl;
				curTree->SetBranchAddress(pair.first.c_str(), &pair.second);
			}
		}
		
		for(int j = 0; j < curTree->GetEntries(); ++j) {
			curTree->GetEntry(j);
			
			outBits.clear();
			if(inBits) {
				size_t nBits = boolIndex.size();
				outBits.resize((nBits + sizeof(unsigned char)*8 - 1) / (sizeof(unsigned char)*8));
				for(size_t k = 0; k < boolPositionMap.size(); ++k) {
					int inIdx = k / (sizeof(unsigned char) * 8);
					int inOff = k % (sizeof(unsigned char) * 8);
					int outIdx = boolPositionMap[k] / (sizeof(unsigned char) * 8);
					int outOff = boolPositionMap[k] % (sizeof(unsigned char) * 8);
					outBits[outIdx] |= (bool)((*inBits)[inIdx] & (1 << inOff)) << outOff;
				}
				// Truncate trailing bits if zero. This has no measurable impact on runtime.
				while(outBits.back() == 0) {
					outBits.pop_back();
				}
			}
			
			outTree->Fill();
		}
		
		delete curTree;
		f->Close();
		delete f;
	}
	
	if(success) {
		for(const auto &outAlias : outAliases) {
			auto aliasIt = boolIndex.find(outAlias);
			int idx = aliasIt->second / (sizeof(unsigned char) * 8);
			int off = aliasIt->second % (sizeof(unsigned char) * 8);
			outTree->SetAlias(outAlias.c_str(), TString::Format("(bits[%d] & (1 << %d)) > 0", idx, off));
		}
		
		if(weights) {
			outTree->SetWeight(1./n);
		}
	}
	
	outTree->Write();
	cout << " (" << outTree->GetEntries() << " entries";
	if(success && weights) {
		cout << ", 1./weight = " << (1./outTree->GetWeight()) << " [PRECUT_EVENT_COUNT]";
	}
	cout << ")" << endl;
	outfile->Close();
	
	delete outfile;
	return success;
}

//___________________________________________________________________________
int main( int argc, char **argv )
{

   if ( argc < 3 || "-h" == string(argv[1]) || "--help" == string(argv[1]) ) {
      cout << "This is a modified version of ROOT hadd that implements special treatment for trees with name treeR." << endl;
      cout << "Usage: " << argv[0] << " [-f[0-9]] [-k] [-T] [-O] [-n maxopenedfiles] [-t treeNamePrefix] [-v verbosity] targetfile source1 [source2 source3 ...]" << endl;
      cout << "This program will add histograms from a list of root files and write them" << endl;
      cout << "to a target root file. The target file is newly created and must not " << endl;
      cout << "exist, or if -f (\"force\") is given, must not be one of the source files." << endl;
      cout << "Supply at least two source files for this to make sense... ;-)" << endl;
      cout << "If the option -k is used, hadd will not exit on corrupt or non-existant input files but skip the offending files instead." << endl;
      cout << "If the option -T is used, Trees are not merged" <<endl;
      cout << "If the option -O is used, when merging TTree, the basket size is re-optimized" <<endl;
      cout << "If the option -v is used, explicitly set the verbosity level; 0 request no output, 99 is the default" <<endl;
      cout << "[unsupported] If the option -n is used, hadd will open at most 'maxopenedfiles' at once, use 0 to request to use the system maximum." << endl;
      cout << "If the option -t is used, the specified tree is used for the Rutgers AnalysisTree treatment (default: treeR)" << endl;
      cout << "When the -f option is specified, one can also specify the compression" <<endl;
      cout << "level of the target file. By default the compression level is 1, but" <<endl;
      cout << "if \"-f0\" is specified, the target file will not be compressed." <<endl;
      cout << "if \"-f6\" is specified, the compression level 6 will be used." <<endl;
      cout << "if Target and source files have different compression levels"<<endl;
      cout << " a slower method is used"<<endl;
      return 1;
   }

   Bool_t force = kFALSE;
   Bool_t skip_errors = kFALSE;
   Bool_t reoptimize = kFALSE;
   Bool_t noTrees = kFALSE;
   Int_t maxopenedfiles = 0;
   Int_t verbosity = 99;
   string treeNamePrefix = "treeR";

   int outputPlace = 0;
   int ffirst = 2;
   Int_t newcomp = 1;
   for( int a = 1; a < argc; ++a ) {
      if ( strcmp(argv[a],"-T") == 0 ) {
         noTrees = kTRUE;
         ++ffirst;
      } else if ( strcmp(argv[a],"-f") == 0 ) {
         force = kTRUE;
         ++ffirst;
      } else if ( strcmp(argv[a],"-k") == 0 ) {
         skip_errors = kTRUE;
         ++ffirst;
      } else if ( strcmp(argv[a],"-O") == 0 ) {
         reoptimize = kTRUE;
         ++ffirst;
      } else if ( strcmp(argv[a],"-n") == 0 ) {
         if (a+1 >= argc) {
            cerr << "Error: no maximum number of opened was provided after -n.\n";
         } else {
            throw std::runtime_error("unsupported option");
            long request = strtol(argv[a+1], 0, 10);
            if (request < kMaxLong && request >= 0) {
               maxopenedfiles = (Int_t)request;
               ++a;
               ++ffirst;
            } else {
               cerr << "Error: could not parse the max number of opened file passed after -n: " << argv[a+1] << ". We will use the system maximum.\n";
            }
         }
         ++ffirst;
      } else if ( strcmp(argv[a],"-v") == 0 ) {
         if (a+1 >= argc) {
            cerr << "Error: no verbosity level was provided after -v.\n";
         } else {
            long request = strtol(argv[a+1], 0, 10);
            if (request < kMaxLong && request >= 0) {
               verbosity = (Int_t)request;
               ++a;
               ++ffirst;
            } else {
               cerr << "Error: could not parse the verbosity level passed after -v: " << argv[a+1] << ". We will use the default value (99).\n";
            }
         }
         ++ffirst;
      } else if ( strcmp(argv[a],"-t") == 0 ) {
         if (a+1 >= argc) {
            cerr << "Error: no tree name was provided after -t.\n";
         } else {
            treeNamePrefix = argv[a+1];
	    ++a;
	    ++ffirst;
         }
         ++ffirst;
      } else if ( argv[a][0] == '-' ) {
         char ft[4];
         for( int j=0; j<=9; ++j ) {
            snprintf(ft,4,"-f%d",j);
            if (!strcmp(argv[a],ft)) {
               force = kTRUE;
               newcomp = j;
               ++ffirst;
               break;
            }
         }
         if (!force) {
            // Bad argument
            cerr << "Error: option " << argv[a] << " is not a supported option.\n";
            ++ffirst;
         }
      } else if (!outputPlace) {
         outputPlace = a;
      }
   }

   gSystem->Load("libTreePlayer");

   const char *targetname = 0;
   if (outputPlace) {
      targetname = argv[outputPlace];
   } else {
      targetname = argv[ffirst-1];
   }
      
   if (verbosity > 1) {
      cout << "hadd Target file: " << targetname << endl;
   }

   TFileMerger merger(kFALSE,kFALSE);
   merger.SetMsgPrefix("hadd");
   merger.SetPrintLevel(verbosity - 1);
   if (maxopenedfiles > 0) {
      merger.SetMaxOpenedFiles(maxopenedfiles);
   }
   if (!merger.OutputFile(targetname,force,newcomp) ) {
      cerr << "hadd error opening target file (does " << argv[ffirst-1] << " exist?)." << endl;
      cerr << "Pass \"-f\" argument to force re-creation of output file." << endl;
      exit(1);
   }

   std::vector<TString> vInputFiles;
   for ( int i = ffirst; i < argc; i++ ) {
      if (argv[i] && argv[i][0]=='@') {
         std::ifstream indirect_file(argv[i]+1);
         if( ! indirect_file.is_open() ) {
            std::cerr<< "hadd could not open indirect file " << (argv[i]+1) << std::endl;
            return 1;
         }
         while( indirect_file ){
            std::string line;
            std::getline(indirect_file, line);
            if( !merger.AddFile(line.c_str()) ) {
               return 1;
            }
            vInputFiles.push_back(TString(line.c_str()));
         }         
      } else if( ! merger.AddFile(argv[i]) ) {
         if ( skip_errors ) {
            cerr << "hadd skipping file with error: " << argv[i] << endl;
         } else {
            cerr << "hadd exiting due to error in " << argv[i] << endl;
            return 1;
         }
      } else {
		  vInputFiles.push_back(TString(argv[i]));
	  }
   }
   
   if(merger.GetMaxOpenedFies() < (int)vInputFiles.size() + 1) {
	   cout << "hadd too many input files. Consider going step by step." << endl;
	   return 1;
   }
   
   if (reoptimize) {
      merger.SetFastMethod(kFALSE);
   } else {
      if (merger.HasCompressionChange()) {
         // Don't warn if the user any request re-optimization.
         cout <<"hadd Sources and Target have different compression levels"<<endl;
         cout <<"hadd merging will be slower"<<endl;
      }
   }
   
   std::set<TString> treeRnames;
   TFile* f = new TFile(vInputFiles[0]);
   TIterator* fi = f->GetListOfKeys()->MakeIterator();
   TNamed* treeRname;
   while( (treeRname = (TNamed*)fi->Next()) ) {
      TString name = treeRname->GetName();
      if(!name.BeginsWith(treeNamePrefix)) {
         continue;
      }
      treeRnames.insert(treeRname->GetName());
   }
   delete treeRname;
   delete fi;
   f->Close();
   
   merger.SetNotrees(noTrees);
   for(auto &treeName : treeRnames) {
      merger.AddObjectNames(treeName.Data());
   }
   Bool_t status = merger.PartialMerge(TFileMerger::kAll | TFileMerger::kRegular | TFileMerger::kSkipListed);
   if(!noTrees) {
      for(auto &treeName : treeRnames) {
         status &= mergeTreeR(targetname, vInputFiles, treeName.Data());
      }
   }

   if (status) {
      if (verbosity == 1) {
         cout << "hadd merged " << merger.GetMergeList()->GetEntries() << " input files in " << targetname << ".\n";
      }
      return 0;
   } else {
      if (verbosity == 1) {
         cout << "hadd failure during the merge of " << merger.GetMergeList()->GetEntries() << " input files in " << targetname << ".\n";
      }
      return 1;
   }
}
