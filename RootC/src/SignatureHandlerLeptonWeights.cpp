#include "RutgersIAF/RootC/interface/SignatureHandler.h"
#include <math.h>

using namespace std;

double SignatureHandler::getMuonIsolationCorrection(double pt)
{

  double effinf = 0.9905 + getMode("muonUncertainty") * 0.002;
  double effc = 0.8584 + getMode("muonUncertainty") * 0.1;
  double sigma = 10.9019 + getMode("muonUncertainty") * 2.5;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);

}
double SignatureHandler::getMuonIdentificationCorrection(double pt)
{

  return 0.9901 + getMode("muonUncertainty") * 0.0022;

}
double SignatureHandler::getElectronIsolationCorrection(double pt)
{
  double effinf = 1.0055 + getMode("electronUncertainty") * 0.001;
  double effc = 0.8999 + getMode("electronUncertainty") * 0.016;
  double sigma = 39.9999 + getMode("electronUncertainty") * 3.0;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);
}
double SignatureHandler::getElectronIdentificationCorrection(double pt)
{

  double effinf = 1.0074 + getMode("electronUncertainty") * 0.01 ;
  double effc = 0.7614 + getMode("electronUncertainty") * 0.128;
  double sigma = 11.8286 + getMode("electronUncertainty") * 9.6;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);
}
