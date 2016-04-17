#!/usr/bin/env python
from ROOT import *
import os
import sys
from array import array
import numpy as np
from decimal import Decimal

def CreateCanvas( canName ) :
    can=TCanvas(canName,canName,0,0,650,650)
    can.cd()
    can.SetLogy(1)
    gStyle.SetOptStat(0)
    can.SetLeftMargin(0.16)
    can.SetRightMargin(0.05)
    can.SetTopMargin(0.05)
    can.SetBottomMargin(0.13)
    can.SetTickx(1)
    can.SetTicky(1)
    return can

def SetgStyle():
    gStyle.SetOptStat(111110)
    gStyle.SetStatFontSize(0.04)
    gStyle.SetStatY(0.915)
    gStyle.SetStatX(0.93)
    gStyle.SetStatW(0.23)
    gStyle.SetStatH(0.25)

def SetHistoStyle( histo ) :
    histo.SetLineColor(2)
    histo.SetMarkerColor(1)
    histo.GetXaxis().SetTitleFont(42);
    histo.GetYaxis().SetTitleFont(42);
    histo.GetXaxis().SetTitleSize(0.05);
    histo.GetYaxis().SetTitleSize(0.05);
    histo.GetXaxis().SetTitleFont(42)
    histo.GetYaxis().SetTitleFont(42)
    histo.GetXaxis().SetLabelFont(42)
    histo.GetYaxis().SetLabelFont(42)
    histo.GetXaxis().SetTitleSize(0.055)
    histo.GetYaxis().SetTitleSize(0.055)
    histo.GetXaxis().SetTitleOffset(1.1)
    histo.GetYaxis().SetTitleOffset(1.25)
    histo.GetXaxis().SetLabelOffset(0.011)
    histo.GetYaxis().SetLabelOffset(0.011)
    histo.GetXaxis().SetLabelSize(0.045)
    histo.GetYaxis().SetLabelSize(0.045)
    histo.SetMarkerStyle(9)
    histo.SetMarkerColor(1)
    histo.SetFillColor(2)
    histo.SetFillStyle(0)
    histo.SetTitle("")
    histo.GetYaxis().SetTitle("Count")
    histo.GetYaxis().CenterTitle()
    histo.GetXaxis().CenterTitle()
    maxbin=histo.GetMaximumBin()
    maxheight=histo.GetBinContent(maxbin)
    histo.GetYaxis().SetRangeUser(0.2,maxheight*25)

def SetLegendStyle( legend ) :
    legend.SetFillColor(0)
    legend.SetLineColor(0)
    legend.SetFillColor(0)
    legend.SetTextSize(0.045)
    legend.SetTextFont(42)

# --------------------------------------------------------------------------------
#promptfake="Prompt"
promptfake="Fake"

#leptonType="Electron"
leptonType="Muon"
#leptonType="Tau"

inputsample="DYJetsToLL_M-50"
#inputsample="TTJets_DiLept"
inputsample2="TTJets_DiLept"
indir1="/home/shchauha/t3store/220316_matrix_method/useConeCorrPt/CMSSW_7_6_3_patch2/src/RutgersIAF/AnalysisPresenter/test/MatrixMacros/DYJets/"
indir2="/home/shchauha/t3store/220316_matrix_method/useConeCorrPt/CMSSW_7_6_3_patch2/src/RutgersIAF/AnalysisPresenter/test/MatrixMacros/TTbar/"

maxPt=200

# --------------------------------------------------------------------------------
para = ['PT', 'ETA', 'JETNOOFCONST', 'CONENDR04TO08', 'CONESUMETDR04TO08']
#para = ['PT']
for i in range(0, 5):
    par = para[i]

    if(i==0): PTbin = array('d',[0,10,20,40,80,200])
    if(i==1): PTbin = array('d',[-2.5,-1.5,0,1.5,2.5])
    if(i==2 or i==3): PTbin = array('d',[0,5,10,20,40,80])
    if(i==4): PTbin = array('d',[0,10,20,40,80,200])

#nlep_iter = np.arange(3)
    for nlep in range(0, 3):
        # Extract the loose and tight histograms
        looseFile = TFile(indir1+"Rates"+"/"+"Loose"+leptonType+"s"+par+repr(nlep)+promptfake+".root","READ")
        tightFile = TFile(indir1+"Rates"+"/"+"Tight"+leptonType+"s"+par+repr(nlep)+promptfake+".root","READ")
        
        looseFile2 = TFile(indir2+"Rates"+"/"+"Loose"+leptonType+"s"+par+repr(nlep)+promptfake+".root","READ")
        tightFile2 = TFile(indir2+"Rates"+"/"+"Tight"+leptonType+"s"+par+repr(nlep)+promptfake+".root","READ")    
        looseFile.ls()
        tightFile.ls()        
        looseFile2.ls()
        tightFile2.ls()
        
        looseHisto=looseFile.Get(inputsample)
        tightHisto=tightFile.Get(inputsample)    
        looseHisto2=looseFile2.Get(inputsample2)
        tightHisto2=tightFile2.Get(inputsample2)
                
        print "Sanity Check"
        print "looseHisto: ",looseHisto.GetEntries()
        print "tightHisto: ",tightHisto.GetEntries()
        print "looseHisto2: ",looseHisto2.GetEntries()
        print "tightHisto2: ",tightHisto2.GetEntries()   
        if par=="PT":
            looseHisto.SetBinContent(1,0)#zero out first bin
            looseHisto2.SetBinContent(1,0)#zero out first bin     
            tightHisto.SetBinContent(1,0)#zero out first bin
            tightHisto2.SetBinContent(1,0)#zero out first bin
        
        #looseHisto.SetDirectory(0)
        looseHistoR=looseHisto.Rebin(len(PTbin)-1,"looseHistoR",PTbin)
        looseHisto2R=looseHisto2.Rebin(len(PTbin)-1,"looseHisto2R",PTbin)
        tightHistoR=tightHisto.Rebin(len(PTbin)-1,"tightHistoR",PTbin)
        tightHisto2R=tightHisto2.Rebin(len(PTbin)-1,"tightHisto2R",PTbin)
        
#        l1.GetEntries()
        looseHisto=looseHistoR.Clone()
        looseHisto2=looseHisto2R.Clone()
        tightHisto=tightHistoR.Clone()
        tightHisto2=tightHisto2R.Clone()
        MuonRatio=TGraphAsymmErrors()
        MuonRatio.Divide(tightHisto,looseHisto,"b(1,1),mode")         
        MuonRatio2=TGraphAsymmErrors()
        MuonRatio2.Divide(tightHisto2,looseHisto2,"b(1,1),mode") 
#https://root.cern.ch/doc/master/classTEfficiency.html#a3a14f2babaaecc09e0a8e96cbc3c2913
        
        can1 = CreateCanvas("can1")
        maxbin1=looseHisto.GetMaximum()
        maxbin2=looseHisto2.GetMaximum()
        
        ymax=max(maxbin1,maxbin2)
        printy = 'ymax is '+ repr(ymax)+ 'and maxbin1 is '+ repr(maxbin1) + ' and maxbin2 is '+ repr(maxbin2)
#print printy
        Frame = looseHisto.Clone()
        Frame.Reset("MICES")
#Frame2 = looseHisto2.Clone(); Frame2.Reset("MICES")
        
    
        can1.Clear(); can1.cd()
        SetgStyle(); can1.SetLogx(0); can1.SetLogy(1); gStyle.SetOptStat(0); can1.SetTickx(1); can1.SetTicky(1)
        SetHistoStyle(Frame)
        Frame.Draw("HIST")
        Frame.GetXaxis().SetTitle(par)
        Frame.GetYaxis().SetTitle("Count")
        Frame.GetXaxis().SetRangeUser(0,maxPt)
        if "ETA" in par : Frame.GetXaxis().SetRangeUser(-3,3)
        Frame.GetYaxis().SetRangeUser(0.1,1.5*ymax)
    
        SetHistoStyle(looseHisto)
        looseHisto.SetLineColor(1)
        looseHisto.SetLineWidth(2)
        looseHisto.Draw("HISTsame")
        SetHistoStyle(tightHisto)
        tightHisto.SetLineColor(2)
        tightHisto.SetLineWidth(2)
        tightHisto.Draw("HISTsame")
        
        SetHistoStyle(looseHisto2)
        looseHisto2.SetLineColor(3)
        looseHisto2.SetLineWidth(2)
        looseHisto2.Draw("HISTsame")
        SetHistoStyle(tightHisto2)
        tightHisto2.SetLineColor(4)
        tightHisto2.SetLineWidth(2)
        tightHisto2.Draw("HISTsame")
        
        
        leg = TLegend(.73,.32,.97,.53)
        leg.SetBorderSize(0)
        leg.SetFillColor(0)
        leg.SetFillStyle(0)
        leg.SetTextFont(42)
        leg.SetTextSize(0.035)
        
        leg.AddEntry(looseHisto,"DY_Loose","L")
        leg.AddEntry(looseHisto2,"TT_Loose","L")
        
        leg.AddEntry(tightHisto,"DY_Tight","L")
        leg.AddEntry(tightHisto2,"TT_Tight","L")
        
        leg.Draw()
        
        can1.RedrawAxis()
        can1.Print(leptonType+"_"+promptfake+par+repr(nlep)+"num_den.png")
        can1.Print("MCRatePlotter_"+leptonType+"_"+promptfake+par+repr(nlep)+".pdf(")
        
        
        
        can1.Clear(); can1.cd()
        SetgStyle(); can1.SetLogx(0); can1.SetLogy(0); gStyle.SetOptStat(0); can1.SetTickx(1); can1.SetTicky(1); can1.SetGridx(1); can1.SetGridy(1)
        if "Fake" in promptfake : can1.SetLogy(1)
        SetHistoStyle(Frame)
        Frame.Draw("HIST")
        Frame.GetXaxis().SetTitle(par)
        Frame.GetYaxis().SetTitle("Tight/Loose Ratio")
        Frame.GetXaxis().SetRangeUser(0,maxPt)
        if "ETA" in par : Frame.GetXaxis().SetRangeUser(-3,3)
        Frame.GetYaxis().SetRangeUser(0,1.05)
        if "Fake" in promptfake: Frame.GetYaxis().SetRangeUser(0.005,1)
        MuonRatio.SetMarkerStyle(9)
        MuonRatio.SetMarkerSize(0.8)
        MuonRatio.SetMarkerColor(2)
        MuonRatio.SetLineColor(2)
        MuonRatio.SetLineWidth(2)
        MuonRatio.Draw("Psame")
        MuonRatio2.SetMarkerStyle(10)
        MuonRatio2.SetMarkerSize(1)
        MuonRatio2.SetMarkerColor(4)
        MuonRatio2.SetLineColor(4)
        MuonRatio2.SetLineWidth(2)
        MuonRatio2.Draw("Psame")
        
        leg = TLegend(.73,.32,.97,.53)
        leg.SetBorderSize(0)
        leg.SetFillColor(0)
        leg.SetFillStyle(0)
        leg.SetTextFont(42)
        leg.SetTextSize(0.035)
        
        leg.AddEntry(MuonRatio,"DY","L")
        leg.AddEntry(MuonRatio2,"TT","L")
        leg.Draw()
        
        can1.RedrawAxis()
        can1.Print(leptonType+"_"+promptfake+par+repr(nlep)+"Rates.png")
        can1.Print("MCRatePlotter_"+leptonType+"_"+promptfake+par+repr(nlep)+".pdf)")
        
    
