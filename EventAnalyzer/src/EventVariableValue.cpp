#include "RutgersIAF/EventAnalyzer/interface/EventVariableValue.h"

ClassImp(EventVariableValue<int>)
ClassImp(EventVariableValue<long>)
ClassImp(EventVariableValue<double>)
ClassImp(EventVariableValue<TString>)
ClassImp(EventVariableValue<bool>)

template class EventVariableValue<int>;
template class EventVariableValue<long>;
template class EventVariableValue<double>;
template class EventVariableValue<TString>;
template class EventVariableValue<bool>;
