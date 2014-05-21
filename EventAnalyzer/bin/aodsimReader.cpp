#include <cstdlib>
#include <sstream>
#include <iostream>

int main(int argc, char **argv)
{
  std::string arguments;

  std::string command = "cmsRun";
  std::string configurationFile = "particleTreeDrawer_cfg.py";
  std::string filePath = std::string(std::getenv("CMSSW_BASE"))+"/src/RutgersIAF2012/EventAnalyzer/bin";

  // command line arguments
  for (int i = 1; i < argc; ++i) {
    std::stringstream ss(argv[i]);
    arguments += ss.str()+" ";
    ss.clear();
  }

  std::system(std::string(command+" "+filePath+"/"+configurationFile+" "+arguments).c_str());

  return 0;
}
