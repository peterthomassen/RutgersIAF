#include "RutgersIAF/EventAnalyzer/interface/EventVariableRename.h"

ClassImp(EventVariableRename<int>)
ClassImp(EventVariableRename<double>)
ClassImp(EventVariableRename<TString>)
ClassImp(EventVariableRename<bool>)

template class EventVariableRename<int>;
template class EventVariableRename<double>;
template class EventVariableRename<TString>;
template class EventVariableRename<bool>;
