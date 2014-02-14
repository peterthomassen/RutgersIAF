#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCutVariableValue.h"

ClassImp(SignatureCutVariableValue<int>)
ClassImp(SignatureCutVariableValue<long>)
ClassImp(SignatureCutVariableValue<double>)
ClassImp(SignatureCutVariableValue<TString>)
ClassImp(SignatureCutVariableValue<bool>)

template class SignatureCutVariableValue<int>;
template class SignatureCutVariableValue<long>;
template class SignatureCutVariableValue<double>;
template class SignatureCutVariableValue<TString>;
template class SignatureCutVariableValue<bool>;
