#include "RutgersIAF/EventAnalyzer/interface/EventVariableConst.h"

ClassImp(EventVariableConst<int>)
ClassImp(EventVariableConst<long>)
ClassImp(EventVariableConst<double>)
ClassImp(EventVariableConst<TString>)
ClassImp(EventVariableConst<bool>)

template class EventVariableConst<int>;
template class EventVariableConst<long>;
template class EventVariableConst<double>;
template class EventVariableConst<TString>;
template class EventVariableConst<bool>;
