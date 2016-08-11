#!/usr/bin/env python
from ROOT import *
from array import *
import plotSettings

inputFileName="/tmp/hsaka/results_EAtest.root"
#
tagHLTName="HLT_IsoMu22_v"
tagPathName="hltL3crIsoL1sMu20L1f0L2f10QL3f22QL3trkIsoFiltered0p09"
#tagHLTName="HLT_Mu50_v"
#tagPathName="hltL3fL1sMu22Or25L1f0L2f10QL3Filtered50Q"
#
probeHLTName="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"
probePathName="hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter"
probePathName2="hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8"

#
#tagPtCut=55
tagPtCut=25
#probePtFit=25
probePtFit=10
HLTDRcut=0.3
#
#isMatchTag=True; matchTag="True"
isMatchTag=False; matchTag="False"

# Assume Muon is tag, Electron is probe
#
# SingleMu PD
#  'hltL3fL1sMu1lqL1f0L2f10L3Filtered17TkIsoFiltered0p4',   #HLT_Mu17_TrkIsoVVL_v3
#  'hltL3fL1sMu22Or25L1f0L2f10QL3Filtered50Q',              #HLT_Mu50_v3,v4
#  'hltL3fL1sMu16orMu25L1f0L2f10QL3Filtered50Q',            #HLT_Mu50_v2
#  'hltL3fL1sMu25f0TkFiltered50Q',                          #HLT_TkMu50_v1,v2,v3
#  'hltL3fL1sMu1lqL1f0L2f10L3Filtered17TkIsoFiltered0p4',   #HLT_Mu17_TrkIsoVVL_v2,v3
#  'hltL3fL1sMu5L1f0L2f5L3Filtered8TkIsoFiltered0p4',       #HLT_Mu8_TrkIsoVVL_v3,v4
#  'hltL3crIsoL1sMu20L1f0L2f10QL3f22QL3trkIsoFiltered0p09', #HLT_IsoMu22_v2,v3
#  'hltL3fL1sMu20L1f0Tkf22QL3trkIsoFiltered0p09',           #HLT_IsoTkMu22_v2,v3,v4

# MuonEG PD (pairs of filters correspond to muon and electron legs separately)
#  'hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23', 'hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter', #HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3,v4,v5,v6
#  'hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23',  'hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter',  #HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v1,v2,v3,v4
#  'hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8',   'hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter',  #HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3,v4,v5,v6

print "debug0"
inFile = TFile(inputFileName,"READ")
tr=inFile.Get("treeR")
print "debug0B"
#
tr.SetAlias(  "tagPt",        "PTGOODMUONS[0]")
tr.SetAlias("probePt",        "PTGOODELECTRONS[0]")
tr.SetAlias(  "tagEta",       "ETAGOODMUONS[0]")
tr.SetAlias("probeEta",       "ETAGOODELECTRONS[0]")
tr.SetAlias(  "tagPhi",       "PHIGOODMUONS[0]")
tr.SetAlias("probePhi",       "PHIGOODELECTRONS[0]")
tr.SetAlias(  "tagIsMatrix",  "ISTIGHTMATRIXMUON[0]")
tr.SetAlias("probeIsMatrix",  "ISTIGHTMATRIXELECTRON[0]")
tr.SetAlias(  "tagIsTightID", "ISTIGHTIDGOODMUONS[0]")
tr.SetAlias("probeIsTightID", "ISCUTTIGHTIDGOODELECTRONS[0]")
tr.SetAlias(  "tagRelIso",    "RELISODBDR0p4GOODMUONS[0]")
tr.SetAlias("probeRelIso",    "RELISOCUTIDGOODELECTRONS[0]")
tr.SetAlias(  "tagDrHLT",     "goodMuonsDR"+tagPathName+"[0]")
tr.SetAlias(  "tagDrHLT2",    "goodMuonsDR"+probePathName2+"[0]")
tr.SetAlias("probeDrHLT",     "goodElectronsDR"+probePathName+"[0]")
#
gROOT.ProcessLineSync('.L customFunctions.C')
#
tr.SetAlias("tagHLT",    "Alt$(N"+tagHLTName+"1[0],0)+"+"Alt$(N"+tagHLTName+"2[0],0)+"+"Alt$(N"+tagHLTName+"3[0],0)+"+"Alt$(N"+tagHLTName+"4[0],0)+"+"Alt$(N"+tagHLTName+"5[0],0)")
tr.SetAlias("probeHLT",  "Alt$(N"+probeHLTName+"1[0],0)+"+"Alt$(N"+probeHLTName+"2[0],0)+"+"Alt$(N"+probeHLTName+"3[0],0)+"+"Alt$(N"+probeHLTName+"4[0],0)+"+"Alt$(N"+probeHLTName+"5[0],0)")

if isMatchTag :
    tr.Draw(">>skim","NGOODMUONS[0]==1&&NGOODELECTRONS[0]==1&&QGOODMUONS[0]+QGOODELECTRONS[0]==0&&tagHLT>0&&tagPt>"+str(tagPtCut)+"&&tagIsMatrix+probeIsMatrix==2&&tagDrHLT<"+str(HLTDRcut)+"&&DR(ETAGOODMUONS[0],PHIGOODMUONS[0],ETAGOODELECTRONS[0],PHIGOODELECTRONS[0])>0.8&&tagIsTightID>0&&tagRelIso<0.1&&tagDrHLT2<"+str(HLTDRcut),"entrylist");
else :
    tr.Draw(">>skim","NGOODMUONS[0]==1&&NGOODELECTRONS[0]==1&&QGOODMUONS[0]+QGOODELECTRONS[0]==0&&tagHLT>0&&tagPt>"+str(tagPtCut)+"&&tagIsMatrix+probeIsMatrix==2&&tagDrHLT<"+str(HLTDRcut)+"&&DR(ETAGOODMUONS[0],PHIGOODMUONS[0],ETAGOODELECTRONS[0],PHIGOODELECTRONS[0])>0.8&&tagIsTightID>0&&tagRelIso<0.1","entrylist");


skim = gDirectory.Get("skim");
tr.SetEntryList(skim);


PTallh   = TH1D("PTallh",  "",40,0,100)
PTpassh  = TH1D("PTpassh", "",40,0,100)
ETAallh  = TH1D("ETAallh", "",10,-3,3)
ETApassh = TH1D("ETApassh","",10,-3,3)
DRallh   = TH1D("DRallh",  "",25,0,5)
DRpassh  = TH1D("DRpassh", "",25,0,5)
#
tr.Draw("probePt>>PTallh")
tr.Draw("probePt>>PTpassh", "probeDrHLT<"+str(HLTDRcut))
#
tr.Draw("probeEta>>ETAallh",  "probePt>"+str(probePtFit))
tr.Draw("probeEta>>ETApassh", "probeDrHLT<"+str(HLTDRcut)+"&&probePt>"+str(probePtFit))
#
tr.Draw("DR(ETAGOODMUONS[0],PHIGOODMUONS[0],ETAGOODELECTRONS[0],PHIGOODELECTRONS[0])>>DRallh",  "probePt>"+str(probePtFit))
tr.Draw("DR(ETAGOODMUONS[0],PHIGOODMUONS[0],ETAGOODELECTRONS[0],PHIGOODELECTRONS[0])>>DRpassh", "probeDrHLT<"+str(HLTDRcut)+"&&probePt>"+str(probePtFit))
#

print " PT  bins: ",PTallh.GetNbinsX()
print "  PT  all: ",PTallh.GetEntries()
print "  PT pass: ",PTpassh.GetEntries()
print " ETA  all: ",ETAallh.GetEntries()
print " ETA pass: ",ETApassh.GetEntries()
print "  DR  all: ",DRallh.GetEntries()
print "  DR pass: ",DRpassh.GetEntries()


can=plotSettings.CreateCanvas1D("can")



can.SetLogx(0); can.SetLogy(0); can.cd()
frame=PTallh.Clone(); frame.Reset("MICES"); 
plotSettings.SetHistoStyle(frame); frame.Draw("HIST")
frame.GetYaxis().SetTitle("Efficiency")
frame.GetYaxis().SetRangeUser(0,1)
frame.GetXaxis().SetTitle("Electron pT")
PTtrigEffh = TGraphAsymmErrors(PTallh.GetNbinsX())
PTtrigEffh.Divide(PTpassh,PTallh,"cp")
PTtrigEffh.SetMarkerStyle(9)
PTtrigEffh.Draw("Psame")
f1 = TF1("f1", "pol0", probePtFit, 100);
PTtrigEffh.Fit("f1","R")
f1.Draw("Same")
f1.SetLineColor(2)
can.Print("TriggerEfficiencyPlotter_TagTrigger_"+tagHLTName+"_matchTag_"+matchTag+"_ProbeTrigger_"+probeHLTName+"_ProbePath_"+probePathName+".pdf(")

can.SetLogx(0); can.SetLogy(0); can.cd()
frame=ETAallh.Clone(); frame.Reset("MICES"); 
plotSettings.SetHistoStyle(frame); frame.Draw("HIST")
frame.GetYaxis().SetTitle("Efficiency")
frame.GetYaxis().SetRangeUser(0,1)
frame.GetXaxis().SetTitle("Electron Eta")
ETAtrigEffh = TGraphAsymmErrors(ETAallh.GetNbinsX())
ETAtrigEffh.Divide(ETApassh,ETAallh,"cp")
ETAtrigEffh.SetMarkerStyle(9)
ETAtrigEffh.Draw("Psame")
can.Print("TriggerEfficiencyPlotter_TagTrigger_"+tagHLTName+"_matchTag_"+matchTag+"_ProbeTrigger_"+probeHLTName+"_ProbePath_"+probePathName+".pdf")

can.SetLogx(0); can.SetLogy(0); can.cd()
frame=DRallh.Clone(); frame.Reset("MICES");
plotSettings.SetHistoStyle(frame); frame.Draw("HIST")
frame.GetYaxis().SetTitle("Efficiency")
frame.GetYaxis().SetRangeUser(0,1)
frame.GetXaxis().SetTitle("DR(Tag Muon, Probe Electron)")
DRtrigEffh = TGraphAsymmErrors(DRallh.GetNbinsX())
DRtrigEffh.Divide(DRpassh,DRallh,"cp")
DRtrigEffh.SetMarkerStyle(9)
DRtrigEffh.Draw("Psame")
can.Print("TriggerEfficiencyPlotter_TagTrigger_"+tagHLTName+"_matchTag_"+matchTag+"_ProbeTrigger_"+probeHLTName+"_ProbePath_"+probePathName+".pdf)")
