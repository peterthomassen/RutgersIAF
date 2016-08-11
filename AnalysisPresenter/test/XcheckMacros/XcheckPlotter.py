#!/usr/bin/env python
from ROOT import *
from array import *
import plotSettings

inputFileName="/cms/multilepton/mheindl/2016/AnalysisTrees/Data/output/DoubleMuon_2016B_274241-274443_0__062916_044052/362711_results_461_data.root"
inFile = TFile(inputFileName,"READ")
tr=inFile.Get("treeR")
varexp = []
#
#Object
varexp.append("NGOODMUONS[0]")
varexp.append("NGOODELECTRONS[0]")
varexp.append("NGOODTAUS[0]")
varexp.append("NGOODJETS[0]")
varexp.append("MOSSF[0]")
varexp.append("MET[0]")
varexp.append("HT[0]")
varexp.append("LT[0]")
varexp.append("ST[0]")
#
#Triggers
varexp.append("NDiMuHLT[0]")
varexp.append("NIsoDiMuHLT[0]")
varexp.append("NIsoDiEleHLT[0]")
varexp.append("NIsoMuEleHLT[0]")
#
can=plotSettings.CreateCanvas1D("can")
for i in xrange(len(varexp)):
    print varexp[i]," plot"
    #
    can.SetLogx(0); can.SetLogy(1); can.cd()
    tr.Draw(varexp[i]+">>"+varexp[i])
    hist = gDirectory.Get(varexp[i]);
    plotSettings.SetHistoStyle(hist);
    hist.Draw("HIST")
    hist.GetXaxis().SetTitle(varexp[i])
    hist.SetTitle("No. of Events: "+str((int)(hist.GetEntries())))
    #
    if               i==0 : can.Print("XcheckPlotter.pdf(")
    elif i==len(varexp)-1 : can.Print("XcheckPlotter.pdf)")
    else                  : can.Print("XcheckPlotter.pdf")
exit(0)



#    if i==0 : can.Print("XcheckPlotter.pdf(")
#    else if i==len(varexp) : can.Print("XcheckPlotter.pdf)")
#else :


#tr.Draw("NIsoDiMuHLT[0]")
#tr.Draw("NDiMuHLT[0]")
#tr.Draw("NIsoDiEleHLT[0]")
#tr.Draw("NIsoMuEleHLT[0]")



#can.SetLogx(0); can.SetLogy(0); can.cd()














tagHLTName="HLT_IsoMu22_v"
tagPathName="hltL3crIsoL1sMu20L1f0L2f10QL3f22QL3trkIsoFiltered0p09"
#tagHLTName="HLT_Mu50_v"
#tagPathName="hltL3fL1sMu22Or25L1f0L2f10QL3Filtered50Q"
#
#probeHLTName="HLT_IsoMu22_v"
#probePathName="hltL3crIsoL1sMu20L1f0L2f10QL3f22QL3trkIsoFiltered0p09"
#probeHLTName="HLT_IsoTkMu22_v"
#probePathName="hltL3fL1sMu20L1f0Tkf22QL3trkIsoFiltered0p09"
#probeHLTName="HLT_Mu50_v"
#probePathName="hltL3fL1sMu22Or25L1f0L2f10QL3Filtered50Q" #v3,v4
#
#probeHLTName="HLT_Mu30_TkMu11_v"
#probePathName="hltDiMuonGlbFiltered30TrkFiltered11"
#probeHLTName="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"
#probePathName="hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4"
#probeHLTName="HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"
#probePathName="hltDiMuonGlb17Trk8RelTrkIsoFiltered0p4"
#probeHLTName="HLT_Mu17_TrkIsoVVL_v"
#probePathName="hltL3fL1sMu1lqL1f0L2f10L3Filtered17TkIsoFiltered0p4"
#probeHLTName="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v"
#probePathName="hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter"
#
#tagPtCut=55
tagPtCut=35
#probePtFit=25
probePtFit=10
HLTDRcut=0.3
#isMatchTag=True; matchTag="True"
isMatchTag=False; matchTag="False"

# Assume (+)ve charge is tag, (-)ve charge is probe
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

# DoubleMu PD
#  'hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4',              #HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v2,v3,v4  (also good for pre-DZ step of the filter below)
#  'hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4DzFiltered0p2', #HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2,v3
#  'hltDiMuonGlb17Trk8RelTrkIsoFiltered0p4',              #HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v2,v3   (also good for pre-DZ step of the filter below)
#  'hltDiMuonGlb17Trk8RelTrkIsoFiltered0p4DzFiltered0p2', #HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2,v3,v4
#  'hltDiMuonGlb17Glb8DzFiltered0p2SameSign',             #HLT_Mu17_Mu8_SameSign_DZ_v1,v2,v3
#  'hltDiMuonGlb17Glb8DzFiltered0p2',                     #HLT_Mu17_Mu8_SameSign_DZ_v1,v2,v3  (DZ filter)
#  'hltL3pfL1sDoubleMu114L1f0L2pf0L3PreFiltered8',        #HLT_Mu17_Mu8_SameSign_DZ_v1,v2,v3  (pre DZ filter)
#  'hltL3fL1sDoubleMu114L1f0L2f10OneMuL3Filtered17',      #HLT_Mu17_Mu8_SameSign_DZ_v1,v2,v3  (pre DZ filter)
#  'hltDiMuonGlb30Trk11DzFiltered0p2',                    #HLT_Mu30_TkMu11_v2,v3
#  'hltDiMuonGlbFiltered30TrkFiltered11',                 #HLT_Mu30_TkMu11_v2,v3 (pre DZ filter)

# MuonEG PD (pairs of filters correspond to muon and electron legs separately)
#  'hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23', 'hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter', #HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3,v4,v5,v6
#  'hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23',  'hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter',  #HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v1,v2,v3,v4
#  'hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8',   'hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter',  #HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3,v4,v5,v6

print "debug0"
inFile = TFile(inputFileName,"READ")
tr=inFile.Get("treeR")
print "debug0B"
#
tr.SetAlias(  "tagMuonPt",        "((QGOODMUONS[0]-1==0)*PTGOODMUONS[0]+(QGOODMUONS[1]-1==0)*PTGOODMUONS[1])")
tr.SetAlias("probeMuonPt",        "((QGOODMUONS[0]+1==0)*PTGOODMUONS[0]+(QGOODMUONS[1]+1==0)*PTGOODMUONS[1])")
tr.SetAlias(  "tagMuonEta",       "((QGOODMUONS[0]-1==0)*ETAGOODMUONS[0]+(QGOODMUONS[1]-1==0)*ETAGOODMUONS[1])")
tr.SetAlias("probeMuonEta",       "((QGOODMUONS[0]+1==0)*ETAGOODMUONS[0]+(QGOODMUONS[1]+1==0)*ETAGOODMUONS[1])")
tr.SetAlias(  "tagMuonPhi",       "((QGOODMUONS[0]-1==0)*PHIGOODMUONS[0]+(QGOODMUONS[1]-1==0)*PHIGOODMUONS[1])")
tr.SetAlias("probeMuonPhi",       "((QGOODMUONS[0]+1==0)*PHIGOODMUONS[0]+(QGOODMUONS[1]+1==0)*PHIGOODMUONS[1])")
tr.SetAlias(  "tagMuonIsMatrix",  "((QGOODMUONS[0]-1==0)*ISTIGHTMATRIXMUON[0]+(QGOODMUONS[1]-1==0)*ISTIGHTMATRIXMUON[1])")
tr.SetAlias("probeMuonIsMatrix",  "((QGOODMUONS[0]+1==0)*ISTIGHTMATRIXMUON[0]+(QGOODMUONS[1]+1==0)*ISTIGHTMATRIXMUON[1])")
tr.SetAlias(  "tagMuonIsTightID", "((QGOODMUONS[0]-1==0)*ISTIGHTIDGOODMUONS[0]+(QGOODMUONS[1]-1==0)*ISTIGHTIDGOODMUONS[1])")
tr.SetAlias("probeMuonIsTightID", "((QGOODMUONS[0]+1==0)*ISTIGHTIDGOODMUONS[0]+(QGOODMUONS[1]+1==0)*ISTIGHTIDGOODMUONS[1])")
tr.SetAlias(  "tagMuonRelIsoDB",  "((QGOODMUONS[0]-1==0)*RELISODBDR0p4GOODMUONS[0]+(QGOODMUONS[1]-1==0)*RELISODBDR0p4GOODMUONS[1])")
tr.SetAlias("probeMuonRelIsoDB",  "((QGOODMUONS[0]+1==0)*RELISODBDR0p4GOODMUONS[0]+(QGOODMUONS[1]+1==0)*RELISODBDR0p4GOODMUONS[1])")
tr.SetAlias(  "tagMuonDrHLT",     "((QGOODMUONS[0]-1==0)*goodMuonsDR"+tagPathName+"[0]+(QGOODMUONS[1]-1==0)*goodMuonsDR"+tagPathName+"[1])")
tr.SetAlias(  "tagMuonDrHLT2",    "((QGOODMUONS[0]-1==0)*goodMuonsDR"+probePathName+"[0]+(QGOODMUONS[1]-1==0)*goodMuonsDR"+probePathName+"[1])")
tr.SetAlias("probeMuonDrHLT",     "((QGOODMUONS[0]+1==0)*goodMuonsDR"+probePathName+"[0]+(QGOODMUONS[1]+1==0)*goodMuonsDR"+probePathName+"[1])")
#
gROOT.ProcessLineSync('.L customFunctions.C')
#
tr.SetAlias("tagHLT",    "Alt$(N"+tagHLTName+"1[0],0)+"+"Alt$(N"+tagHLTName+"2[0],0)+"+"Alt$(N"+tagHLTName+"3[0],0)+"+"Alt$(N"+tagHLTName+"4[0],0)+"+"Alt$(N"+tagHLTName+"5[0],0)")
tr.SetAlias("probeHLT",  "Alt$(N"+probeHLTName+"1[0],0)+"+"Alt$(N"+probeHLTName+"2[0],0)+"+"Alt$(N"+probeHLTName+"3[0],0)+"+"Alt$(N"+probeHLTName+"4[0],0)+"+"Alt$(N"+probeHLTName+"5[0],0)")

if isMatchTag :
    tr.Draw(">>skim","NGOODMUONS[0]==2&&QGOODMUONS[0]+QGOODMUONS[1]==0&&tagHLT>0&&tagMuonPt>"+str(tagPtCut)+"&&tagMuonIsMatrix+probeMuonIsMatrix==2&&tagMuonDrHLT<"+str(HLTDRcut)+"&&DR(ETAGOODMUONS[0],PHIGOODMUONS[0],ETAGOODMUONS[1],PHIGOODMUONS[1])>0.8&&tagMuonIsTightID>0&&tagMuonRelIsoDB<0.1&&tagMuonDrHLT2<"+str(HLTDRcut),"entrylist");
else :
    tr.Draw(">>skim","NGOODMUONS[0]==2&&QGOODMUONS[0]+QGOODMUONS[1]==0&&tagHLT>0&&tagMuonPt>"+str(tagPtCut)+"&&tagMuonIsMatrix+probeMuonIsMatrix==2&&tagMuonDrHLT<"+str(HLTDRcut)+"&&DR(ETAGOODMUONS[0],PHIGOODMUONS[0],ETAGOODMUONS[1],PHIGOODMUONS[1])>0.8&&tagMuonIsTightID>0&&tagMuonRelIsoDB<0.1","entrylist");

skim = gDirectory.Get("skim");
tr.SetEntryList(skim);


PTallh   = TH1D("PTallh",  "",40,0,100)
PTpassh  = TH1D("PTpassh", "",40,0,100)
ETAallh  = TH1D("ETAallh", "",10,-3,3)
ETApassh = TH1D("ETApassh","",10,-3,3)
DRallh   = TH1D("DRallh",  "",25,0,5)
DRpassh  = TH1D("DRpassh", "",25,0,5)
#
tr.Draw("probeMuonPt>>PTallh")
tr.Draw("probeMuonPt>>PTpassh", "probeMuonDrHLT<"+str(HLTDRcut))
#
tr.Draw("probeMuonEta>>ETAallh",  "probeMuonPt>"+str(probePtFit))
tr.Draw("probeMuonEta>>ETApassh", "probeMuonDrHLT<"+str(HLTDRcut)+"&&probeMuonPt>"+str(probePtFit))
#
tr.Draw("DR(ETAGOODMUONS[0],PHIGOODMUONS[0],ETAGOODMUONS[1],PHIGOODMUONS[1])>>DRallh",  "probeMuonPt>"+str(probePtFit))
tr.Draw("DR(ETAGOODMUONS[0],PHIGOODMUONS[0],ETAGOODMUONS[1],PHIGOODMUONS[1])>>DRpassh", "probeMuonDrHLT<"+str(HLTDRcut)+"&&probeMuonPt>"+str(probePtFit))
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
frame.GetXaxis().SetTitle("Muon pT")
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
frame.GetXaxis().SetTitle("Muon Eta")
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
frame.GetXaxis().SetTitle("DR(Tag Muon, Probe Muon)")
DRtrigEffh = TGraphAsymmErrors(DRallh.GetNbinsX())
DRtrigEffh.Divide(DRpassh,DRallh,"cp")
DRtrigEffh.SetMarkerStyle(9)
DRtrigEffh.Draw("Psame")
can.Print("TriggerEfficiencyPlotter_TagTrigger_"+tagHLTName+"_matchTag_"+matchTag+"_ProbeTrigger_"+probeHLTName+"_ProbePath_"+probePathName+".pdf)")
