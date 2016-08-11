#!/usr/bin/env python
from ROOT import *

def CreateCanvas2D( canName ) :
    #can=TCanvas(canName,canName,0,0,650,650)
    can=TCanvas(canName,canName,0,0,750,650)
    can.cd()
    can.SetLogy(1)
    gStyle.SetOptStat(0)
    can.SetLeftMargin(0.13)
    can.SetRightMargin(0.12)
    can.SetTopMargin(0.07)
    can.SetBottomMargin(0.13)
    can.SetTickx(1)
    can.SetTicky(1)
    return can

def CreateCanvas1D( canName ) :
    #can=TCanvas(canName,canName,0,0,650,650)
    can=TCanvas(canName,canName,0,0,750,650)
    can.cd()
    can.SetLogy(1)
    gStyle.SetOptStat(0)
    can.SetLeftMargin(0.13)
    can.SetRightMargin(0.12)
    can.SetTopMargin(0.07)
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
    histo.GetYaxis().SetTitleOffset(1.1)
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
