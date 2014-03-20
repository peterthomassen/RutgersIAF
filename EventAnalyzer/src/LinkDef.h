#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableObjectWeightPtTF1.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableTH1.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableTF1.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparisonDeltaR.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SkimTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCutVariableValue.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCutVariableInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCutReversed.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCutCombined.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableOSSF.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableN.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableSumPT.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_N.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureWithBjets.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH3F.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH2F.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCut.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/Signature.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectCutReversed.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectCutCombined.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectCutVariableValue.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectCutVariableInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectCut.h"

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;
#pragma link C++ class EventVariable+;
#pragma link C++ class SignatureObject+;
#pragma link C++ class ObjectCut+;
#pragma link C++ class ObjectCutVariableInRange<int>+;
#pragma link C++ class ObjectCutVariableInRange<double>+;
#pragma link C++ class ObjectCutVariableValue<int>+;
#pragma link C++ class ObjectCutVariableValue<bool>+;
#pragma link C++ class ObjectCutVariableValue<TString>+;
#pragma link C++ class ObjectCutVariableValue<double>+;
#pragma link C++ class ObjectCutCombined+;
#pragma link C++ class ObjectCutReversed+;
#pragma link C++ class Signature+;
#pragma link C++ class BaseHandler+;
#pragma link C++ class SignatureCut+;
#pragma link C++ class BaseTreeReader+;
#pragma link C++ class SignatureTH1F+;
#pragma link C++ class SignatureTH2F+;
#pragma link C++ class SignatureTH3F+;
#pragma link C++ class SignatureWithBjets+;
#pragma link C++ class ObjectComparison+;
#pragma link C++ class ObjectVariable+;
#pragma link C++ class SignatureTH1F_N+;
#pragma link C++ class EventVariableSumPT+;
#pragma link C++ class EventVariableN+;
#pragma link C++ class EventVariableOSSF+;
#pragma link C++ class SignatureCutCombined+;
#pragma link C++ class SignatureCutReversed+;
#pragma link C++ class SignatureCutVariableInRange<int>+;
#pragma link C++ class SignatureCutVariableInRange<long>+;
#pragma link C++ class SignatureCutVariableInRange<double>+;
#pragma link C++ class SignatureCutVariableValue<int>+;
#pragma link C++ class SignatureCutVariableValue<long>+;
#pragma link C++ class SignatureCutVariableValue<double>+;
#pragma link C++ class SignatureCutVariableValue<TString>+;
#pragma link C++ class SignatureCutVariableValue<bool>+;
#pragma link C++ class SignatureTH1F_EventVariable<int>+;
#pragma link C++ class SignatureTH1F_EventVariable<double>+;
#pragma link C++ class SignatureTH1F_ObjectVariable<int>+;
#pragma link C++ class SignatureTH1F_ObjectVariable<double>+;
#pragma link C++ class BaseTreeWriter+;
#pragma link C++ class SignatureTreeWriter+;
#pragma link C++ class SkimTreeReader+;
#pragma link C++ class ObjectComparisonDeltaR+;
#pragma link C++ class EventVariableTF1<int>+;
#pragma link C++ class EventVariableTF1<long>+;
#pragma link C++ class EventVariableTF1<double>+;
#pragma link C++ class EventVariableTH1<int>+;
#pragma link C++ class EventVariableTH1<long>+;
#pragma link C++ class EventVariableTH1<double>+;
#pragma link C++ class EventVariableObjectWeightPtTF1+;
#endif
