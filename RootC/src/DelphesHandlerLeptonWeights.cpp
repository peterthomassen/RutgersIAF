#include "RutgersIAF/RootC/interface/DelphesHandler.h"
#include <math.h>

using namespace std;

double DelphesHandler::getMuonIsolationCorrection(double pt)
{

  double effinf = 0.9987;
  double effc = 0.878;
  double sigma = 11.2652;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);

}
double DelphesHandler::getMuonIdentificationCorrection(double pt)
{

  return 0.9932;

}
double DelphesHandler::getElectronIsolationCorrection(double pt)
{
  double effinf = 0.999;
  double effc = 0.9;
  double sigma = 15.33;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);
}
double DelphesHandler::getElectronIdentificationCorrection(double pt)
{

  double effinf = 1.014;
  double effc = 0.7835;
  double sigma = 11.57;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);
}
