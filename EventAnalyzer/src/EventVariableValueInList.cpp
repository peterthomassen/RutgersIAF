#include "RutgersIAF/EventAnalyzer/interface/EventVariableValueInList.h"

ClassImp(EventVariableValueInList<int>)
ClassImp(EventVariableValueInList<long>)
ClassImp(EventVariableValueInList<double>)
ClassImp(EventVariableValueInList<TString>)
ClassImp(EventVariableValueInList<bool>)

template class EventVariableValueInList<int>;
template class EventVariableValueInList<long>;
template class EventVariableValueInList<double>;
template class EventVariableValueInList<TString>;
template class EventVariableValueInList<bool>;
