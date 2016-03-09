#!/usr/bin/env python
from ROOT import *
import os
import sys
from array import array

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


# Extract the loose and tight histograms
looseFile = TFile("LooseMuons.root","READ")
tightFile = TFile("TightMuons.root","READ")

looseFile.ls()
tightFile.ls()

looseHisto=looseFile.Get("DYJetsToLL_M-50")
tightHisto=tightFile.Get("DYJetsToLL_M-50")

print "Sanity Check"
print "looseHisto: ",looseHisto.GetEntries()
print "tightHisto: ",tightHisto.GetEntries()

tightHisto.SetBinContent(1,0)#zero out first bin

MuonRatio=TGraphAsymmErrors()
MuonRatio.Divide(tightHisto,looseHisto,"b(1,1),mode") 
#https://root.cern.ch/doc/master/classTEfficiency.html#a3a14f2babaaecc09e0a8e96cbc3c2913

can1 = CreateCanvas("can1")
Frame = looseHisto.Clone(); Frame.Reset("MICES")


can1.Clear(); can1.cd()
SetgStyle(); can1.SetLogx(0); can1.SetLogy(1); gStyle.SetOptStat(0); can1.SetTickx(1); can1.SetTicky(1)
SetHistoStyle(Frame)
Frame.Draw("HIST")
Frame.GetXaxis().SetTitle("Muon pT (GeV)")
Frame.GetYaxis().SetTitle("Count")
Frame.GetXaxis().SetRangeUser(0,100)
Frame.GetYaxis().SetRangeUser(0.1,2000)
SetHistoStyle(looseHisto)
looseHisto.SetLineColor(2)
looseHisto.Draw("HISTsame")
SetHistoStyle(tightHisto)
tightHisto.SetLineColor(4)
tightHisto.Draw("HISTsame")
can1.RedrawAxis()
can1.Print("MCRatePlotter.pdf(")

can1.Clear(); can1.cd()
SetgStyle(); can1.SetLogx(0); can1.SetLogy(0); gStyle.SetOptStat(0); can1.SetTickx(1); can1.SetTicky(1); can1.SetGridx(1); can1.SetGridy(1)
SetHistoStyle(Frame)
Frame.Draw("HIST")
Frame.GetXaxis().SetTitle("Muon pT (GeV)")
Frame.GetYaxis().SetTitle("Tight/Loose Ratio")
Frame.GetXaxis().SetRangeUser(0,100)
Frame.GetYaxis().SetRangeUser(0,1.05)
MuonRatio.SetMarkerStyle(9)
MuonRatio.SetMarkerSize(0.8)
MuonRatio.Draw("Psame")
can1.RedrawAxis()
can1.Print("MCRatePlotter.pdf)")
