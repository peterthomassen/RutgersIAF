#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutCombined.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutChi2Ndof.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutDxy.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutDz.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutVertDz.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutBeamDxy.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutBeamD0.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronConversionDCotTheta.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronConversionDistance.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronDeltaEta.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronDeltaPhi.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronHadOverEm.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronMissingHits.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronSigmaIetaIeta.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutEta.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutGlobalMuonPromptTight.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIrel.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIrel010to030.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutPhotonIsTight.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutPt.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTauIsPF.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTrackerMuon.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutValidTrackerHits.h"
#include "RutgersIAF2012/RootC/interface/Signature.h"
#include "RutgersIAF2012/RootC/interface/SignatureBeamSpot.h"
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutHT.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNBjetTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNDYPairs.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNDYPairsT.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNElectron.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNJet.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNMuon.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNPhoton.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNTau.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutST.h"
#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectJet.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectPhoton.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectWithIso.h"
#include "RutgersIAF2012/RootC/interface/SignatureRecoVertex.h"
#include "RutgersIAF2012/RootC/interface/SkimTreeBase.h"
#include "RutgersIAF2012/RootC/interface/VertexCut.h"
#include "RutgersIAF2012/RootC/interface/VertexCutNdof.h"
#include "RutgersIAF2012/RootC/interface/VertexCutR.h"
#include "RutgersIAF2012/RootC/interface/VertexCutZ.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNVertexAllReco.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_LJJMvsPiT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_LJJMvsEta.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH3F_LJJDalitz.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH3F.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_LJJMvsPT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_NVertex.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetBeta.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_QuadJetAvgM.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_TauIso.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutTauZ.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutTTZSelection.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutPFMETType1.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutHcalIso.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutEcalIso.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMissingPixelHits.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronMVA.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_ZpT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_TopTagChi2.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutMass.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutFourJetTopTag.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutAllMass.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_NvN.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_METxy.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_METvsMll.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_METvsMT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_METvsAllMass.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutPairMass.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutMll.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutMT.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutFilter.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronVertDz.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronVertDxy.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutReversed.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTauCharge.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetChargedMultiplicity.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetChargedHadronFraction.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetChargedEMFraction.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_RelIsoVsDxy.h"
#include "RutgersIAF2012/RootC/interface/SignatureWithBjets.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutCharge.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_PU.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutValidMuonHits.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronSuperClusterEta.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMuonNormalizedChi2.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMuonInnerVertDz.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMuonInnerVertDxy.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMuonInnerNumberOfValidPixelHits.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetNumberConstituents.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetNeutralEMFraction.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetNeutralHadronFraction.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronIsConversion.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronVertexFitProbability.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIrelPhoton.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIrelNeutralHadron.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIrelChargedHadron.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMT.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetBDiscPositive.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetBDiscNegative.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronChargeConsistent.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronEminusP.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutVertDxy.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMuonGlobal.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutValidPixelHits.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTrackLayersWithMeasurement.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMuonMatches.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIsPF.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_M.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutBeamDz.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutNdof.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMCStatus.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMCPdgID.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutMCMotherPdgID.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutJetGenParticle.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTauGenLepton.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutElectronExpectedInnerHits.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutPtTauLeadingTrack.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutEtaTauLeadingTrack.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutReversed.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutNdofTauLeadingTrack.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutBeamD0TauLeadingTrack.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutValidTrackerHitsTauLeadingTrack.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTauChargeMatch.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_METvsSumPt.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTauDiscriminants.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutAllLeptonMass.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutBDiscriminant.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_LeadPtVsM.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutQ.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_RelIsoVsPt.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_PhiVsEta.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_PT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_TCMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_LT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_HT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_N.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_LJMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_PFMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_MT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_ST.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"
#include "RutgersIAF2012/RootC/interface/SignatureTrigger.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutEvent.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutTrigger.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutSameSignMuEl.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNTauTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNMuEl.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNVertex.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutAbsRel010to030Tau.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutAbsRelTau.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutAbsRelEcalOffset.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutAbsRel010to030.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutAbsRel.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutThresholdMuon.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutThresholdElectron.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutThreshold.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutN.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutCombined.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIrelTau.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIrel010to030Tau.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTrackIsTracker.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTrackIsMuon.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutTrackIsGlobal.h"
#include "RutgersIAF2012/RootC/interface/ObjectCutIrelEcalOffset.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutTTZ4L.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include "RutgersIAF2012/RootC/interface/SortableObject.h"
#include "RutgersIAF2012/RootC/interface/DelphesClasses.h"
#include "RutgersIAF2012/RootC/interface/DelphesHandler.h"
#include "RutgersIAF2012/RootC/interface/DelphesTreeBase.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_HTvsWSumPt.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_TauIsovsHT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_TauIsovsWSumPt.h"


#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;
#pragma link C++ class ObjectCut+;
#pragma link C++ class ObjectCutCombined+;
#pragma link C++ class ObjectCutChi2Ndof+;
#pragma link C++ class ObjectCutDxy+;
#pragma link C++ class ObjectCutDz+;
#pragma link C++ class ObjectCutVertDz+;
#pragma link C++ class ObjectCutBeamDxy+;
#pragma link C++ class ObjectCutBeamD0+;
#pragma link C++ class ObjectCutElectronConversionDCotTheta+;
#pragma link C++ class ObjectCutElectronConversionDistance+;
#pragma link C++ class ObjectCutElectronDeltaEta+;
#pragma link C++ class ObjectCutElectronDeltaPhi+;
#pragma link C++ class ObjectCutElectronHadOverEm+;
#pragma link C++ class ObjectCutElectronMissingHits+;
#pragma link C++ class ObjectCutElectronSigmaIetaIeta+;
#pragma link C++ class ObjectCutEta+;
#pragma link C++ class ObjectCutGlobalMuonPromptTight+;
#pragma link C++ class ObjectCutIrel+;
#pragma link C++ class ObjectCutIrel010to030+;
#pragma link C++ class ObjectCutPhotonIsTight+;
#pragma link C++ class ObjectCutPt+;
#pragma link C++ class ObjectCutTauIsPF+;
#pragma link C++ class ObjectCutTrackerMuon+;
#pragma link C++ class ObjectCutValidTrackerHits+;
#pragma link C++ class Signature+;
#pragma link C++ class SignatureBeamSpot+;
#pragma link C++ class SignatureCut+;
#pragma link C++ class SignatureCutHT+;
#pragma link C++ class SignatureCutMET+;
#pragma link C++ class SignatureCutNBjetTrack+;
#pragma link C++ class SignatureCutNDYPairs+;
#pragma link C++ class SignatureCutNDYPairsT+;
#pragma link C++ class SignatureCutNElectron+;
#pragma link C++ class SignatureCutNJet+;
#pragma link C++ class SignatureCutNMuon+;
#pragma link C++ class SignatureCutNPhoton+;
#pragma link C++ class SignatureCutNTau+;
#pragma link C++ class SignatureCutST+;
#pragma link C++ class SignatureHandler+;
#pragma link C++ class SignatureObject+;
#pragma link C++ class SignatureObjectElectron+;
#pragma link C++ class SignatureObjectJet+;
#pragma link C++ class SignatureObjectMCPart+;
#pragma link C++ class SignatureObjectMET+;
#pragma link C++ class SignatureObjectMuon+;
#pragma link C++ class SignatureObjectPhoton+;
#pragma link C++ class SignatureObjectRecoTrack+;
#pragma link C++ class SignatureObjectTau+;
#pragma link C++ class SignatureObjectWithIso+;
#pragma link C++ class SignatureRecoVertex+;
#pragma link C++ class SkimTreeBase+;
#pragma link C++ class VertexCut+;
#pragma link C++ class VertexCutNdof+;
#pragma link C++ class VertexCutR+;
#pragma link C++ class VertexCutZ+;
#pragma link C++ class ObjectCutIrelEcalOffset+;
#pragma link C++ class ObjectCutTrackIsGlobal+;
#pragma link C++ class ObjectCutTrackIsMuon+;
#pragma link C++ class ObjectCutTrackIsTracker+;
#pragma link C++ class ObjectCutIrel010to030Tau+;
#pragma link C++ class ObjectCutIrelTau+;
#pragma link C++ class SignatureCutCombined+;
#pragma link C++ class SignatureCutN+;
#pragma link C++ class SignatureCutThreshold+;
#pragma link C++ class SignatureCutThresholdElectron+;
#pragma link C++ class SignatureCutThresholdMuon+;
#pragma link C++ class ObjectCutAbsRel+;
#pragma link C++ class ObjectCutAbsRel010to030+;
#pragma link C++ class ObjectCutAbsRelEcalOffset+;
#pragma link C++ class ObjectCutAbsRelTau+;
#pragma link C++ class ObjectCutAbsRel010to030Tau+;
#pragma link C++ class SignatureCutNVertex+;
#pragma link C++ class SignatureCutNMuEl+;
#pragma link C++ class SignatureCutNTrack+;
#pragma link C++ class SignatureCutNTauTrack+;
#pragma link C++ class SignatureCutSameSignMuEl+;
#pragma link C++ class SignatureCutTrigger+;
#pragma link C++ class SignatureCutEvent+;
#pragma link C++ class SignatureTrigger+;
#pragma link C++ class SignatureTH1F+;
#pragma link C++ class SignatureTH1F_HT+;
#pragma link C++ class SignatureTH1F_ST+;
#pragma link C++ class SignatureTH1F_N+;
#pragma link C++ class SignatureTH1F_PFMET+;
#pragma link C++ class SignatureTH1F_MT+;
#pragma link C++ class SignatureTH1F_LJMET+;
#pragma link C++ class SignatureTH1F_LT+;
#pragma link C++ class SignatureTH1F_TCMET+;
#pragma link C++ class SignatureTH1F_PT+;
#pragma link C++ class SignatureTH2F+;
#pragma link C++ class SignatureTH2F_PhiVsEta+;
#pragma link C++ class SignatureTH2F_RelIsoVsPt+;
#pragma link C++ class SignatureCutQ+;
#pragma link C++ class SignatureTH2F_LeadPtVsM+;
#pragma link C++ class SignatureCutBDiscriminant+;
#pragma link C++ class SignatureCutAllLeptonMass+;
#pragma link C++ class ObjectCutTauDiscriminants+;
#pragma link C++ class SignatureTH2F_METvsSumPt+;
#pragma link C++ class ObjectCutTauChargeMatch+;
#pragma link C++ class ObjectCutValidTrackerHitsTauLeadingTrack+;
#pragma link C++ class ObjectCutBeamD0TauLeadingTrack+;
#pragma link C++ class ObjectCutNdofTauLeadingTrack+;
#pragma link C++ class ObjectCutReversed+;
#pragma link C++ class ObjectCutEtaTauLeadingTrack+;
#pragma link C++ class ObjectCutPtTauLeadingTrack+;
#pragma link C++ class ObjectCutElectronExpectedInnerHits+;
#pragma link C++ class ObjectCutMCMotherPdgID+;
#pragma link C++ class ObjectCutJetGenParticle+;
#pragma link C++ class ObjectCutTauGenLepton+;
#pragma link C++ class ObjectCutMCPdgID+;
#pragma link C++ class ObjectCutMCStatus+;
#pragma link C++ class ObjectCutNdof+;
#pragma link C++ class ObjectCutBeamDz+;
#pragma link C++ class SignatureTH1F_M+;
#pragma link C++ class ObjectCutIsPF+;
#pragma link C++ class ObjectCutMuonMatches+;
#pragma link C++ class ObjectCutTrackLayersWithMeasurement+;
#pragma link C++ class ObjectCutValidPixelHits+;
#pragma link C++ class ObjectCutMuonGlobal+;
#pragma link C++ class ObjectCutVertDxy+;
#pragma link C++ class ObjectCutElectronEminusP+;
#pragma link C++ class ObjectCutElectronChargeConsistent+;
#pragma link C++ class ObjectCutJetBDiscNegative+;
#pragma link C++ class ObjectCutJetBDiscPositive+;
#pragma link C++ class ObjectCutMT+;
#pragma link C++ class ObjectCutIrelChargedHadron+;
#pragma link C++ class ObjectCutIrelNeutralHadron+;
#pragma link C++ class ObjectCutIrelPhoton+;
#pragma link C++ class ObjectCutElectronVertexFitProbability+;
#pragma link C++ class ObjectCutElectronIsConversion+;
#pragma link C++ class ObjectCutJetNeutralHadronFraction+;
#pragma link C++ class ObjectCutJetNeutralEMFraction+;
#pragma link C++ class ObjectCutJetNumberConstituents+;
#pragma link C++ class ObjectCutMuonInnerNumberOfValidPixelHits+;
#pragma link C++ class ObjectCutMuonInnerVertDxy+;
#pragma link C++ class ObjectCutMuonInnerVertDz+;
#pragma link C++ class ObjectCutMuonNormalizedChi2+;
#pragma link C++ class ObjectCutElectronSuperClusterEta+;
#pragma link C++ class ObjectCutValidMuonHits+;
#pragma link C++ class SignatureTH1F_PU+;
#pragma link C++ class ObjectCutCharge+;
#pragma link C++ class SignatureWithBjets+;
#pragma link C++ class SignatureTH2F_RelIsoVsDxy+;
#pragma link C++ class ObjectCutJetChargedEMFraction+;
#pragma link C++ class ObjectCutJetChargedHadronFraction+;
#pragma link C++ class ObjectCutJetChargedMultiplicity+;
#pragma link C++ class ObjectCutTauCharge+;
#pragma link C++ class SignatureCutReversed+;
#pragma link C++ class ObjectCutElectronVertDxy+;
#pragma link C++ class ObjectCutElectronVertDz+;
#pragma link C++ class SignatureCutFilter+;
#pragma link C++ class SignatureCutMT+;
#pragma link C++ class SignatureCutMll+;
#pragma link C++ class SignatureCutPairMass+;
#pragma link C++ class SignatureTH2F_METvsMll+;
#pragma link C++ class SignatureTH2F_METvsMT+;
#pragma link C++ class SignatureTH2F_METvsAllMass+;
#pragma link C++ class SignatureTH2F_METxy+;
#pragma link C++ class SignatureTH2F_NvN+;
#pragma link C++ class SignatureCutAllMass+;
#pragma link C++ class SignatureCutFourJetTopTag+;
#pragma link C++ class SignatureCutMass+;
#pragma link C++ class SignatureTH1F_TopTagChi2+;
#pragma link C++ class SignatureTH1F_ZpT+;
#pragma link C++ class ObjectCutElectronMVA+;
#pragma link C++ class ObjectCutMissingPixelHits+;
#pragma link C++ class ObjectCutEcalIso+;
#pragma link C++ class ObjectCutHcalIso+;
#pragma link C++ class SignatureCutPFMETType1+;
#pragma link C++ class SignatureCutTTZSelection+;
#pragma link C++ class SignatureCutTauZ+;
#pragma link C++ class SignatureTH1F_TauIso+;
#pragma link C++ class SignatureTH1F_QuadJetAvgM+;
#pragma link C++ class ObjectCutJetBeta+;
#pragma link C++ class SignatureTH1F_NVertex+;
#pragma link C++ class SignatureTH2F_LJJMvsPT+;
#pragma link C++ class SignatureTH3F+;
#pragma link C++ class SignatureTH3F_LJJDalitz+;
#pragma link C++ class SignatureTH2F_LJJMvsEta+;
#pragma link C++ class SignatureTH2F_LJJMvsPiT+;
#pragma link C++ class SignatureCutTTZ4L+;
#pragma link C++ class BaseHandler+;
#pragma link C++ class SortableObject+;
#pragma link C++ class Event+;
#pragma link C++ class LHCOEvent+;
#pragma link C++ class LHEFEvent+;
#pragma link C++ class HepMCEvent+;
#pragma link C++ class GenParticle+;
#pragma link C++ class MissingET+;
#pragma link C++ class ScalarHT+;
#pragma link C++ class Photon+;
#pragma link C++ class Electron+;
#pragma link C++ class Muon+;
#pragma link C++ class Jet+;
#pragma link C++ class Track+;
#pragma link C++ class Tower+;
#pragma link C++ class Candidate+;
#pragma link C++ class DelphesTreeBase+;
#pragma link C++ class DelphesHandler+;
#pragma link C++ class SignatureTH2F_HTvsWSumPt+;
#pragma link C++ class SignatureTH2F_TauIsovsHT+;
#pragma link C++ class SignatureTH2F_TauIsovsWSumPt+;
#pragma link C++ class SignatureCutNVertexAllReco+;
#endif
