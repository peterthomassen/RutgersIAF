#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"
#include <math.h>

using namespace std;

double SignatureHandler::getMuonIsolationCorrection(double pt)
{

  double effinf = 0.9905 + m_muonUncertaintyMode * 0.002;
  double effc = 0.8584 + m_muonUncertaintyMode * 0.1;
  double sigma = 10.9019 + m_muonUncertaintyMode * 2.5;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);

}
double SignatureHandler::getMuonIdentificationCorrection(double pt)
{

  return 0.9901 + m_muonUncertaintyMode * 0.0022;

}
double SignatureHandler::getElectronIsolationCorrection(double pt)
{
  double effinf = 1.0055 + m_electronUncertaintyMode * 0.001;
  double effc = 0.8999 + m_electronUncertaintyMode * 0.016;
  double sigma = 39.9999 + m_electronUncertaintyMode * 3.0;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);
}
double SignatureHandler::getElectronIdentificationCorrection(double pt)
{

  double effinf = 1.0074 + m_electronUncertaintyMode * 0.01 ;
  double effc = 0.7614 + m_electronUncertaintyMode * 0.128;
  double sigma = 11.8286 + m_electronUncertaintyMode * 9.6;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);
}
