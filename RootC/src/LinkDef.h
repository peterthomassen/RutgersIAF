#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/ObjectCutCombined.h"
#include "RutgersIAF/RootC/interface/ObjectCutChi2Ndof.h"
#include "RutgersIAF/RootC/interface/ObjectCutDxy.h"
#include "RutgersIAF/RootC/interface/ObjectCutDz.h"
#include "RutgersIAF/RootC/interface/ObjectCutVertDz.h"
#include "RutgersIAF/RootC/interface/ObjectCutBeamDxy.h"
#include "RutgersIAF/RootC/interface/ObjectCutBeamD0.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronConversionDCotTheta.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronConversionDistance.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronDeltaEta.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronDeltaPhi.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronHadOverEm.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronMissingHits.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronSigmaIetaIeta.h"
#include "RutgersIAF/RootC/interface/ObjectCutEta.h"
#include "RutgersIAF/RootC/interface/ObjectCutGlobalMuonPromptTight.h"
#include "RutgersIAF/RootC/interface/ObjectCutIrel.h"
#include "RutgersIAF/RootC/interface/ObjectCutIrel010to030.h"
#include "RutgersIAF/RootC/interface/ObjectCutPhotonIsTight.h"
#include "RutgersIAF/RootC/interface/ObjectCutPt.h"
#include "RutgersIAF/RootC/interface/ObjectCutTauIsPF.h"
#include "RutgersIAF/RootC/interface/ObjectCutTrackerMuon.h"
#include "RutgersIAF/RootC/interface/ObjectCutValidTrackerHits.h"
#include "RutgersIAF/RootC/interface/Signature.h"
#include "RutgersIAF/RootC/interface/SignatureBeamSpot.h"
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/SignatureCutHT.h"
#include "RutgersIAF/RootC/interface/SignatureCutMET.h"
#include "RutgersIAF/RootC/interface/SignatureCutNBjetTrack.h"
#include "RutgersIAF/RootC/interface/SignatureCutNDYPairs.h"
#include "RutgersIAF/RootC/interface/SignatureCutNDYPairsT.h"
#include "RutgersIAF/RootC/interface/SignatureCutNElectron.h"
#include "RutgersIAF/RootC/interface/SignatureCutNJet.h"
#include "RutgersIAF/RootC/interface/SignatureCutNMuon.h"
#include "RutgersIAF/RootC/interface/SignatureCutNPhoton.h"
#include "RutgersIAF/RootC/interface/SignatureCutNTau.h"
#include "RutgersIAF/RootC/interface/SignatureCutST.h"
#include "RutgersIAF/RootC/interface/SignatureHandler.h"
#include "RutgersIAF/RootC/interface/SignatureObject.h"
#include "RutgersIAF/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF/RootC/interface/SignatureObjectJet.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMCPart.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMET.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF/RootC/interface/SignatureObjectPhoton.h"
#include "RutgersIAF/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF/RootC/interface/SignatureObjectWithIso.h"
#include "RutgersIAF/RootC/interface/SignatureRecoVertex.h"
#include "RutgersIAF/RootC/interface/SkimTreeBase.h"
#include "RutgersIAF/RootC/interface/VertexCut.h"
#include "RutgersIAF/RootC/interface/VertexCutNdof.h"
#include "RutgersIAF/RootC/interface/VertexCutR.h"
#include "RutgersIAF/RootC/interface/VertexCutZ.h"
#include "RutgersIAF/RootC/interface/SignatureCutNVertexAllReco.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_LJJMvsPiT.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_LJJMvsEta.h"
#include "RutgersIAF/RootC/interface/SignatureTH3F_LJJDalitz.h"
#include "RutgersIAF/RootC/interface/SignatureTH3F.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_LJJMvsPT.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_NVertex.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetBeta.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_QuadJetAvgM.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_TauIso.h"
#include "RutgersIAF/RootC/interface/SignatureCutTauZ.h"
#include "RutgersIAF/RootC/interface/SignatureCutTTZSelection.h"
#include "RutgersIAF/RootC/interface/SignatureCutPFMETType1.h"
#include "RutgersIAF/RootC/interface/ObjectCutHcalIso.h"
#include "RutgersIAF/RootC/interface/ObjectCutEcalIso.h"
#include "RutgersIAF/RootC/interface/ObjectCutMissingPixelHits.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronMVA.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_ZpT.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_TopTagChi2.h"
#include "RutgersIAF/RootC/interface/SignatureCutMass.h"
#include "RutgersIAF/RootC/interface/SignatureCutFourJetTopTag.h"
#include "RutgersIAF/RootC/interface/SignatureCutAllMass.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_NvN.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_METxy.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_METvsMll.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_METvsMT.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_METvsAllMass.h"
#include "RutgersIAF/RootC/interface/SignatureCutPairMass.h"
#include "RutgersIAF/RootC/interface/SignatureCutMll.h"
#include "RutgersIAF/RootC/interface/SignatureCutMT.h"
#include "RutgersIAF/RootC/interface/SignatureCutFilter.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronVertDz.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronVertDxy.h"
#include "RutgersIAF/RootC/interface/SignatureCutReversed.h"
#include "RutgersIAF/RootC/interface/ObjectCutTauCharge.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetChargedMultiplicity.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetChargedHadronFraction.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetChargedEMFraction.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_RelIsoVsDxy.h"
#include "RutgersIAF/RootC/interface/SignatureWithBjets.h"
#include "RutgersIAF/RootC/interface/ObjectCutCharge.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_PU.h"
#include "RutgersIAF/RootC/interface/ObjectCutValidMuonHits.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronSuperClusterEta.h"
#include "RutgersIAF/RootC/interface/ObjectCutMuonNormalizedChi2.h"
#include "RutgersIAF/RootC/interface/ObjectCutMuonInnerVertDz.h"
#include "RutgersIAF/RootC/interface/ObjectCutMuonInnerVertDxy.h"
#include "RutgersIAF/RootC/interface/ObjectCutMuonInnerNumberOfValidPixelHits.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetNumberConstituents.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetNeutralEMFraction.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetNeutralHadronFraction.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronIsConversion.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronVertexFitProbability.h"
#include "RutgersIAF/RootC/interface/ObjectCutIrelPhoton.h"
#include "RutgersIAF/RootC/interface/ObjectCutIrelNeutralHadron.h"
#include "RutgersIAF/RootC/interface/ObjectCutIrelChargedHadron.h"
#include "RutgersIAF/RootC/interface/ObjectCutMT.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetBDiscPositive.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetBDiscNegative.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronChargeConsistent.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronEminusP.h"
#include "RutgersIAF/RootC/interface/ObjectCutVertDxy.h"
#include "RutgersIAF/RootC/interface/ObjectCutMuonGlobal.h"
#include "RutgersIAF/RootC/interface/ObjectCutValidPixelHits.h"
#include "RutgersIAF/RootC/interface/ObjectCutTrackLayersWithMeasurement.h"
#include "RutgersIAF/RootC/interface/ObjectCutMuonMatches.h"
#include "RutgersIAF/RootC/interface/ObjectCutIsPF.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_M.h"
#include "RutgersIAF/RootC/interface/ObjectCutBeamDz.h"
#include "RutgersIAF/RootC/interface/ObjectCutNdof.h"
#include "RutgersIAF/RootC/interface/ObjectCutMCStatus.h"
#include "RutgersIAF/RootC/interface/ObjectCutMCPdgID.h"
#include "RutgersIAF/RootC/interface/ObjectCutMCMotherPdgID.h"
#include "RutgersIAF/RootC/interface/ObjectCutJetGenParticle.h"
#include "RutgersIAF/RootC/interface/ObjectCutTauGenLepton.h"
#include "RutgersIAF/RootC/interface/ObjectCutElectronExpectedInnerHits.h"
#include "RutgersIAF/RootC/interface/ObjectCutPtTauLeadingTrack.h"
#include "RutgersIAF/RootC/interface/ObjectCutEtaTauLeadingTrack.h"
#include "RutgersIAF/RootC/interface/ObjectCutReversed.h"
#include "RutgersIAF/RootC/interface/ObjectCutNdofTauLeadingTrack.h"
#include "RutgersIAF/RootC/interface/ObjectCutBeamD0TauLeadingTrack.h"
#include "RutgersIAF/RootC/interface/ObjectCutValidTrackerHitsTauLeadingTrack.h"
#include "RutgersIAF/RootC/interface/ObjectCutTauChargeMatch.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_METvsSumPt.h"
#include "RutgersIAF/RootC/interface/ObjectCutTauDiscriminants.h"
#include "RutgersIAF/RootC/interface/SignatureCutAllLeptonMass.h"
#include "RutgersIAF/RootC/interface/SignatureCutBDiscriminant.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_LeadPtVsM.h"
#include "RutgersIAF/RootC/interface/SignatureCutQ.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_RelIsoVsPt.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_PhiVsEta.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_PT.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_TCMET.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_LT.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_HT.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_N.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_LJMET.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_PFMET.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_MT.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F_ST.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"
#include "RutgersIAF/RootC/interface/SignatureTrigger.h"
#include "RutgersIAF/RootC/interface/SignatureCutEvent.h"
#include "RutgersIAF/RootC/interface/SignatureCutTrigger.h"
#include "RutgersIAF/RootC/interface/SignatureCutSameSignMuEl.h"
#include "RutgersIAF/RootC/interface/SignatureCutNTauTrack.h"
#include "RutgersIAF/RootC/interface/SignatureCutNTrack.h"
#include "RutgersIAF/RootC/interface/SignatureCutNMuEl.h"
#include "RutgersIAF/RootC/interface/SignatureCutNVertex.h"
#include "RutgersIAF/RootC/interface/ObjectCutAbsRel010to030Tau.h"
#include "RutgersIAF/RootC/interface/ObjectCutAbsRelTau.h"
#include "RutgersIAF/RootC/interface/ObjectCutAbsRelEcalOffset.h"
#include "RutgersIAF/RootC/interface/ObjectCutAbsRel010to030.h"
#include "RutgersIAF/RootC/interface/ObjectCutAbsRel.h"
#include "RutgersIAF/RootC/interface/SignatureCutThresholdMuon.h"
#include "RutgersIAF/RootC/interface/SignatureCutThresholdElectron.h"
#include "RutgersIAF/RootC/interface/SignatureCutThreshold.h"
#include "RutgersIAF/RootC/interface/SignatureCutN.h"
#include "RutgersIAF/RootC/interface/SignatureCutCombined.h"
#include "RutgersIAF/RootC/interface/ObjectCutIrelTau.h"
#include "RutgersIAF/RootC/interface/ObjectCutIrel010to030Tau.h"
#include "RutgersIAF/RootC/interface/ObjectCutTrackIsTracker.h"
#include "RutgersIAF/RootC/interface/ObjectCutTrackIsMuon.h"
#include "RutgersIAF/RootC/interface/ObjectCutTrackIsGlobal.h"
#include "RutgersIAF/RootC/interface/ObjectCutIrelEcalOffset.h"
#include "RutgersIAF/RootC/interface/SignatureCutTTZ4L.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SortableObject.h"
#include "RutgersIAF/RootC/interface/DelphesClasses.h"
#include "RutgersIAF/RootC/interface/DelphesHandler.h"
#include "RutgersIAF/RootC/interface/DelphesTreeBase.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_HTvsWSumPt.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_TauIsovsHT.h"
#include "RutgersIAF/RootC/interface/SignatureTH2F_TauIsovsWSumPt.h"


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
