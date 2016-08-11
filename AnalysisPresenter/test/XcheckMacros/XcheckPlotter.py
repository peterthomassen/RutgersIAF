#!/usr/bin/env python
from ROOT import *
from array import *
import plotSettings

gROOT.SetBatch(True)

#inputFileName="/cms/multilepton/mheindl/2016/AnalysisTrees/Data/output/DoubleMuon_2016B_274241-274443_0__062916_044052/362711_results_461_data.root"
inputFileName="/tmp/hsaka/results_EAtest.root"
isMC=False
if "_simulation" in inputFileName : isMC=False
inFile = TFile(inputFileName,"READ")
tr=inFile.Get("treeR")
varexp = []
#
# Lepton-Jet Object
varexp.append("NGOODMUONS[0]")
varexp.append("NGOODELECTRONS[0]")
varexp.append("NGOODTAUS[0]")
varexp.append("NGOODJETS[0]")
varexp.append("NGOODBJETSCSVM[0]")
varexp.append("NLEPTONS[0]")
varexp.append("NLIGHTLEPTONS[0]")
varexp.append("PTGOODMUONS[0]")
varexp.append("ETAGOODMUONS[0]")
varexp.append("PHIGOODMUONS[0]")
varexp.append("PTGOODELECTRONS[0]")
varexp.append("ETAGOODELECTRONS[0]")
varexp.append("PHIGOODELECTRONS[0]")
varexp.append("PTGOODTAUS[0]")
varexp.append("ETAGOODTAUS[0]")
varexp.append("PHIGOODTAUS[0]")
varexp.append("PTGOODJETS[0]")
varexp.append("ETAGOODJETS[0]")
varexp.append("PHIGOODJETS[0]")
#
# Global per-event variables
varexp.append("MOSSF[0]")
varexp.append("MLIGHTLEPTONS[0]")
varexp.append("MET[0]")
varexp.append("HT[0]")
varexp.append("LT[0]")
varexp.append("ST[0]")
varexp.append("MT[0]")
varexp.append("NRECOVERTICES[0]")
#
# MatrixMethod Variables
if isMC: varexp.append("ISPROMPTMUON[0]")
if isMC: varexp.append("ISPROMPTELECTRON[0]")
if isMC: varexp.append("ISPROMPTTAU[0]")
varexp.append("ISTIGHTMATRIXMUON[0]")
varexp.append("ISTIGHTMATRIXELECTRON[0]")
varexp.append("ISTIGHTMATRIXTAU[0]")
varexp.append("LeptonTypeVal3DLA[0]")
varexp.append("LeptonTypeVal2DLA[0]")
varexp.append("LeptonTypeVal3D[0]")
varexp.append("LeptonTypeVal2D[0]")
varexp.append("HTLA[0]")
varexp.append("LTLA[0]")
varexp.append("LTLA2[0]")
varexp.append("LTLA3[0]")
varexp.append("LTLA4[0]")
varexp.append("LT[0]")
varexp.append("LT2[0]")
varexp.append("LT3[0]")
varexp.append("LT4[0]")
varexp.append("JETNOOFCONSTGOODMUONS[0]")
varexp.append("JETNOOFCONSTGOODELECTRONS[0]")
varexp.append("JETNOOFCONSTGOODTAUS[0]")
#
#Triggers
varexp.append("NDiMuHLT[0]")
varexp.append("NIsoDiMuHLT[0]")
varexp.append("NIsoDiEleHLT[0]")
varexp.append("NIsoMuEleHLT[0]")
for i in xrange(1,6):
    print i
    varexp.append("NHLT_Mu50_v"+str(i)+"[0]")
    varexp.append("NHLT_IsoMu22_v"+str(i)+"[0]")
    varexp.append("NHLT_Ele27_eta2p1_WPLoose_Gsf_v"+str(i)+"[0]")
    varexp.append("NHLT_Ele27_WPTight_Gsf_v"+str(i)+"[0]")
    #
    #varexp.append("NHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"+str(i)+"[0]")  
    #varexp.append("NHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"+str(i)+"[0]")
    varexp.append("NHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"+str(i)+"[0]")
    varexp.append("NHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"+str(i)+"[0]")
    varexp.append("NHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"+str(i)+"[0]")
    varexp.append("NHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"+str(i)+"[0]")
    varexp.append("NHLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v"+str(i)+"[0]")
    varexp.append("NHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v"+str(i)+"[0]")
#
#Triggers Objects
MuTrigFilters = []
ElTrigFilters = []
#"""
MuTrigFilters.append("hltL3fL1sMu22Or25L1f0L2f10QL3Filtered50Q")                           # HLT_Mu50_v3,v4  - filter has changed for this path    - T&P mu  
MuTrigFilters.append("hltL3fL1sMu16orMu25L1f0L2f10QL3Filtered50Q")                         # HLT_Mu50_v2     - filter has changed for this path    - T&P mu
MuTrigFilters.append("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23")    # HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v     - MAIN mu
ElTrigFilters.append("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter") # HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v     - MAIN e
MuTrigFilters.append("hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23")     # HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v      - MAIN mu
ElTrigFilters.append("hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter")  # HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v      - MAIN e
MuTrigFilters.append("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8")      # HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v      - MAIN mu
ElTrigFilters.append("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter")  # HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v      - MAIN e
MuTrigFilters.append("hltL3fL1sMu25f0TkFiltered50Q")                                       # HLT_TkMu50_v1,v2,v3                                   - T&P mu
MuTrigFilters.append("hltL3crIsoL1sMu20L1f0L2f10QL3f22QL3trkIsoFiltered0p09")              # HLT_IsoMu22_v                                         - T&P mu
MuTrigFilters.append("hltL3fL1sMu20L1f0Tkf22QL3trkIsoFiltered0p09")                        # HLT_IsoTkMu22_v2,v3,v4                                - T&P mu
MuTrigFilters.append("hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4")                             # HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v2,v3,v4             - MAIN mu
MuTrigFilters.append("hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4DzFiltered0p2")                # HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2,v3             - MAIN mu
MuTrigFilters.append("hltDiMuonGlb17Trk8RelTrkIsoFiltered0p4")                             # HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v2,v3              - MAIN mu
MuTrigFilters.append("hltDiMuonGlb17Trk8RelTrkIsoFiltered0p4DzFiltered0p2")                # HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2,v3,v4        - MAIN mu
ElTrigFilters.append("hltEle27WPTightGsfTrackIsoFilter")                                   # HLT_Ele27_WPTight_Gsf_v1,v2,v3,v4                     - T&P e
ElTrigFilters.append("hltEle27erWPLooseGsfTrackIsoFilter")                                 # HLT_Ele27_eta2p1_WPLoose_Gsf_v3,v4,v5 - filter change - T&P e
ElTrigFilters.append("hltEle27WPLooseGsfTrackIsoFilter")                                   # HLT_Ele27_eta2p1_WPLoose_Gsf_v2       - filter change - T&P e
ElTrigFilters.append("hltEle23Ele12CaloIdLTrackIdLIsoVLDZFilter")                          # HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3,v4,v5,v6                                          - MAIN e
ElTrigFilters.append("hltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg1Filter")                # HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3,v4,v5,v6 (same as above, prior to the DZ filter)  - MAIN e
ElTrigFilters.append("hltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg2Filter")                # HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3,v4,v5,v6 (same as above, prior to the DZ filter)  - MAIN e
#
MuTrigFilters.append("hltDiMu9Ele9CaloIdLTrackIdLMuonlegL3Filtered9")                      # HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v
ElTrigFilters.append("hltDiMu9Ele9CaloIdLTrackIdLElectronlegDphiFilter")                   # HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v
MuTrigFilters.append("hltL3fL1sMu22orMu25orMu20EG15orMu5EG20L1f0L2f10QL3Filtered30Q")      # HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v
ElTrigFilters.append("hltEle30CaloIdLGsfTrkIdVLDPhiUnseededFilter")                        # HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v
MuTrigFilters.append("hltMu8DiEle12CaloIdLTrackIdLMuonlegL3Filtered8")                     # HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v
ElTrigFilters.append("hltMu8DiEle12CaloIdLTrackIdLElectronlegDphiFilter")                  # HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v
MuTrigFilters.append("hltL3fL1sMu1lqL1f0L2f10L3Filtered17TkIsoFiltered0p4")                # HLT_Mu17_TrkIsoVVL_v3
MuTrigFilters.append("hltL3fL1sMu1lqL1f0L2f10L3Filtered17TkIsoFiltered0p4")                # HLT_Mu17_TrkIsoVVL_v2,v3
MuTrigFilters.append("hltL3fL1sMu5L1f0L2f5L3Filtered8TkIsoFiltered0p4")                    # HLT_Mu8_TrkIsoVVL_v3,v4
MuTrigFilters.append("hltL3pfL1sDoubleMu114L1f0L2pf0L3PreFiltered8")                       # HLT_Mu17_Mu8_SameSign_DZ_v1,v2,v3 (pre-DZ filter)
MuTrigFilters.append("hltL3fL1sDoubleMu114L1f0L2f10OneMuL3Filtered17")                     # HLT_Mu17_Mu8_SameSign_DZ_v1,v2,v3 (pre-DZ filter)
MuTrigFilters.append("hltDiMuonGlb17Glb8DzFiltered0p2")                                    # HLT_Mu17_Mu8_SameSign_DZ_v1,v2,v3 (DZ filter)
MuTrigFilters.append("hltDiMuonGlb17Glb8DzFiltered0p2SameSign")                            # HLT_Mu17_Mu8_SameSign_DZ_v1,v2,v3 (same-sign filter)
MuTrigFilters.append("hltDiMuonGlb30Trk11DzFiltered0p2")                                   # HLT_Mu30_TkMu11_v2,v3
MuTrigFilters.append("hltDiMuonGlbFiltered30TrkFiltered11")                                # HLT_Mu30_TkMu11_v2,v3 (pre-DZ filter) 
ElTrigFilters.append("hltEle12CaloIdLTrackIdLIsoVLTrackIsoFilter")                         # HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v3,v4,v5,v6
ElTrigFilters.append("hltEle17CaloIdLTrackIdLIsoVLTrackIsoFilter")                         # HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v2,v3,v4,v5
ElTrigFilters.append("hltEle23CaloIdLTrackIdLIsoVLTrackIsoFilter")                         # HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v3,v4,v5,v6
#"""
for i in xrange(len(MuTrigFilters)):
    varexp.append("goodMuonsDR"+MuTrigFilters[i]+"[0]")
    varexp.append("PT"+MuTrigFilters[i]+"[0]")
    varexp.append("ETA"+MuTrigFilters[i]+"[0]")
    varexp.append("PHI"+MuTrigFilters[i]+"[0]")
for i in xrange(len(ElTrigFilters)):
    varexp.append("goodElectronsDR"+ElTrigFilters[i]+"[0]")
    varexp.append("PT"+ElTrigFilters[i]+"[0]")
    varexp.append("ETA"+ElTrigFilters[i]+"[0]")
    varexp.append("PHI"+ElTrigFilters[i]+"[0]")

#-------------------------------------------------
# Produce plots..
can=plotSettings.CreateCanvas1D("can")
text=TLatex(0.1,0.5,inputFileName); text.SetNDC(); text.SetTextSize(0.015)
text.Draw();
can.Print("XcheckPlotter.pdf(")
for i in xrange(len(varexp)):
    print varexp[i]," plot"
    #
    can.SetLogx(0); can.SetLogy(1); can.cd()
    tr.Draw(varexp[i]+">>"+"hist"+str(i))
    hist = gDirectory.Get("hist"+str(i));
    plotSettings.SetHistoStyle(hist);
    if "HLT_"    in varexp[i] : hist.GetXaxis().SetTitleSize(0.037); hist.GetXaxis().SetTitleOffset(1.5);
    if "DRhlt"  in varexp[i] : hist.GetXaxis().SetTitleSize(0.037); hist.GetXaxis().SetTitleOffset(1.5);
    if "PThlt"  in varexp[i] : hist.GetXaxis().SetTitleSize(0.037); hist.GetXaxis().SetTitleOffset(1.5);
    if "ETAhlt" in varexp[i] : hist.GetXaxis().SetTitleSize(0.037); hist.GetXaxis().SetTitleOffset(1.5);
    if "PHIhlt" in varexp[i] : hist.GetXaxis().SetTitleSize(0.037); hist.GetXaxis().SetTitleOffset(1.5);
    hist.Draw("HIST")
    hist.GetXaxis().SetTitle(varexp[i])
    hist.SetTitle("No. of Events: "+str((int)(hist.GetEntries())))
    #
    if i==len(varexp)-1 : can.Print("XcheckPlotter.pdf)")
    else                : can.Print("XcheckPlotter.pdf")

exit(0)

