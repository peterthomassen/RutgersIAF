#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariablePtInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableEtaInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableLorentzVectorInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableValueInList.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableThreshold.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_CountNoWeight.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_CountWeight.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableRelIso.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableElectronTotalIso.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableMuonTotalIso.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableObjectWeightPtTF1.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableTH1.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableTF1.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparisonDeltaR.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SkimTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableValue.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableReversed.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableCombined.h"
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
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/Signature.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableReversed.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableCombined.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableValue.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableInRange.h"

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;
#pragma link C++ class EventVariable+;
#pragma link C++ class SignatureObject+;
#pragma link C++ class ObjectVariableInRange<int>+;
#pragma link C++ class ObjectVariableInRange<double>+;
#pragma link C++ class ObjectVariableValue<int>+;
#pragma link C++ class ObjectVariableValue<bool>+;
#pragma link C++ class ObjectVariableValue<TString>+;
#pragma link C++ class ObjectVariableValue<double>+;
#pragma link C++ class ObjectVariableCombined+;
#pragma link C++ class ObjectVariableReversed+;
#pragma link C++ class Signature+;
#pragma link C++ class BaseHandler+;
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
#pragma link C++ class EventVariableCombined+;
#pragma link C++ class EventVariableReversed+;
#pragma link C++ class EventVariableInRange<int>+;
#pragma link C++ class EventVariableInRange<long>+;
#pragma link C++ class EventVariableInRange<double>+;
#pragma link C++ class EventVariableValue<int>+;
#pragma link C++ class EventVariableValue<long>+;
#pragma link C++ class EventVariableValue<double>+;
#pragma link C++ class EventVariableValue<TString>+;
#pragma link C++ class EventVariableValue<bool>+;
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
#pragma link C++ class ObjectVariableMuonTotalIso+;
#pragma link C++ class ObjectVariableElectronTotalIso+;
#pragma link C++ class ObjectVariableRelIso+;
#pragma link C++ class SignatureTH1F_CountWeight+;
#pragma link C++ class SignatureTH1F_CountNoWeight+;
#pragma link C++ class EventVariableThreshold+;
#pragma link C++ class EventVariableValueInList<int>+;
#pragma link C++ class EventVariableValueInList<long>+;
#pragma link C++ class EventVariableValueInList<double>+;
#pragma link C++ class EventVariableValueInList<TString>+;
#pragma link C++ class EventVariableValueInList<bool>+;
#pragma link C++ class ObjectVariableValueInList<int>+;
#pragma link C++ class ObjectVariableValueInList<double>+;
#pragma link C++ class ObjectVariableValueInList<TString>+;
#pragma link C++ class ObjectVariableValueInList<bool>+;
#pragma link C++ class ObjectVariableLorentzVectorInRange+;
#pragma link C++ class ObjectVariableEtaInRange+;
#pragma link C++ class ObjectVariablePtInRange+;
#endif
