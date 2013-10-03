#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"
#include <math.h>

using namespace std;

double SignatureHandler::getMuonIsolationCorrection(double pt)
{

  double effinf = 0.9985 + m_muonUncertaintyMode * 0.002;
  double effc = 0.932 + m_muonUncertaintyMode * 0.1;
  double sigma = 11.636 + m_muonUncertaintyMode * 2.5;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);

}
double SignatureHandler::getMuonIdentificationCorrection(double pt)
{

  return 0.9925 + m_muonUncertaintyMode * 0.0022;

}
double SignatureHandler::getElectronIsolationCorrection(double pt)
{
  double effinf = 0.998 + m_electronUncertaintyMode * 0.001;
  double effc = 0.93 + m_electronUncertaintyMode * 0.016;
  double sigma = 16.4 + m_electronUncertaintyMode * 3.0;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);
}
double SignatureHandler::getElectronIdentificationCorrection(double pt)
{

  double effinf = 1.012 + m_electronUncertaintyMode * 0.01 ;
  double effc = 0.7513 + m_electronUncertaintyMode * 0.128;
  double sigma = 10.623 + m_electronUncertaintyMode * 9.6;
  double c = 8;

  double erfval = erf((pt-c)/sigma);

  return effinf * erfval + effc * (1 - erfval);
}
