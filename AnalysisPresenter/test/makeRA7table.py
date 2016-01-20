import os
from ROOT import *
 
values = open("RA7table.txt").readlines()

print "Creating RA7 OnZ and OffZ signal regions plots..."

gStyle.SetOptStat(0)
OnZstack = THStack("OnZstack", "RA7 table: OnZ signal regions")
hOnZ = TH1F("hOnZ", "RA7 table: OnZ signal regions", 15, 0, 15)
hOnZ.SetFillColor(38)
hOnZerror = TH1F("hOnZerror", "RA7 table: OnZ signal regions", 15, 0, 15)
hOnZerror.SetFillColor(1)
hOnZerror.SetMarkerColor(1)
hOnZerror.SetFillStyle(3018);
hOnZdata = TH1F("hOnZdata", "RA7 table: OnZ signal regions", 15, 0, 15)
hOnZdata.SetMarkerStyle(33)
hOnZdata.SetMarkerColor(kRed)

for i in range(0, 15):
 rate = values[i].split()
 for x in range(0, len(rate)):
  hOnZ.GetXaxis().SetBinLabel(i+1, "SR"+str(i+1))
  hOnZ.SetBinContent(i+1, float(rate[2]))
  hOnZerror.GetXaxis().SetBinLabel(i+1, "SR"+str(i+1))
  hOnZerror.SetBinContent(i+1, float(rate[2]))
  hOnZerror.SetBinError(i+1, float(rate[4])+float(rate[6]))
  hOnZdata.GetXaxis().SetBinLabel(i+1, "SR"+str(i+1))
  hOnZdata.SetBinContent(i+1, float(rate[0]))
OnZstack.Add(hOnZ, "B")
OnZstack.Add(hOnZerror, "E2")
OnZstack.Add(hOnZdata, "P0")
OnZstack.Draw("nostack")
OnZstack.GetYaxis().SetTitle("Rate")
c1.SaveAs("RA7_OnZ_SR.pdf")

OffZstack = THStack("OffZstack", "RA7 table: OffZ signal regions")
hOffZ = TH1F("hOffZ", "RA7 table: OffZ signal regions", 15, 0, 15)
hOffZ.SetFillColor(38)
hOffZerror = TH1F("hOffZerror", "RA7 table: OffZ signal regions", 15, 0, 15)
hOffZerror.SetFillColor(1)
hOffZerror.SetMarkerColor(1)
hOffZerror.SetFillStyle(3018);
hOffZdata = TH1F("hOffZdata", "RA7 table: OffZ signal regions", 15, 0, 15)
hOffZdata.SetMarkerStyle(33)
hOffZdata.SetMarkerColor(kRed)

for j in range(15, 30):
 rate = values[j].split()
 for y in range(0, len(rate)):
  hOffZ.GetXaxis().SetBinLabel(j-14, "SR"+str(j-14))
  hOffZ.SetBinContent(j-14, float(rate[2]))
  hOffZerror.GetXaxis().SetBinLabel(j-14, "SR"+str(j-14))
  hOffZerror.SetBinContent(j-14, float(rate[2]))
  hOffZerror.SetBinError(j-14, float(rate[4])+float(rate[6]))
  hOffZdata.GetXaxis().SetBinLabel(j-14, "SR"+str(j-14))
  hOffZdata.SetBinContent(j-14, float(rate[0]))
OffZstack.Add(hOffZ, "B")
OffZstack.Add(hOffZerror, "E2")
OffZstack.Add(hOffZdata, "P0")
OffZstack.Draw("nostack")
OffZstack.GetYaxis().SetTitle("Rate")
c1.SaveAs("RA7_OffZ_SR.pdf")

with open('RA7table.tex', 'wb') as texfile:
 texfile.write("\\documentclass[a4paper,11pt,landscape]{article}\n")
 texfile.write("\\usepackage[landscape]{geometry}\n")
 texfile.write("\\usepackage{fixltx2e}\n")
 texfile.write("\\usepackage{hyperref}\n")
 texfile.write("\\usepackage{multirow}\n")
 texfile.write("\\usepackage{graphicx}\n")
 texfile.write("\\begin{document}\n")
 texfile.write("\\renewcommand{\\arraystretch}{2}\n")
 texfile.write("\\begin{center}\n")
 texfile.write("\\large{Baseline selection: 3 tight leptons with $p_T > 20 / 15 / 10$ GeV, min. 2 jets, $E^{miss}_T > 50$ GeV and $M_{ll} \geq 12$ GeV}\\normalsize \\\\ \\vspace{2cm}\n")
 texfile.write("\\begin{tabular}{|c|c|c|c|c|}\n")
 texfile.write("\\hline \n")
 texfile.write("b-tags & $E^{miss}_T$ & $60 < H_T \leq 400$ & $400 \leq H_T < 600$ & $H_T \geq 600$\\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("\\multirow{2}{*}{0 b-tags} & $50 \leq E^{miss}_T < 150$ & SR1 & SR3 & \multirow{7}{*}{SR14}\\\\ \n")
 texfile.write("\\cline{2-4} \n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & SR2 & SR4 &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("\\multirow{2}{*}{1 b-tag} & $50 \leq E^{miss}_T < 150$ & SR5 & SR7 &\\\\ \n")
 texfile.write("\\cline{2-4}\n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & SR6 & SR8 &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("\\multirow{2}{*}{2 b-tags} & $50 \leq E^{miss}_T < 150$ & SR9 & SR11 &\\\\ \n")
 texfile.write("\\cline{2-4}\n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & SR10 & SR12 &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("$ \geq 3$ b-tags & $50 \leq E^{miss}_T < 300$ & \multicolumn{2}{|c|}{SR13} &\\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("inclusive & $E^{miss}_T \geq 300$ & \multicolumn{3}{|c|}{SR15} \\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("\\end{tabular} \\\\ \\vspace{0.2cm} \n")
 texfile.write("\\newpage \n")
 texfile.write("\\large{Baseline selection: 3 tight leptons with $p_T > 20 / 15 / 10$ GeV, min. 2 jets, $E^{miss}_T > 50$ GeV and $M_{ll} \geq 12$ GeV}\\normalsize \\\\ \\vspace{1cm}\n")
 texfile.write("OnZ signal regions: OSSF-pair with $76 < M_{ll} < 106$ GeV \\ \\vspace{0.5cm} \\\\ \n")
 texfile.write("\\begin{tabular}{|c|c|c|c|c|}\n")
 texfile.write("\\hline \n")
 texfile.write("b-tags & $E^{miss}_T$ & $60 < H_T \leq 400$ & $400 \leq H_T < 600$ & $H_T \geq 600$\\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("\\multirow{2}{*}{0 b-tags} & $50 \leq E^{miss}_T < 150$ & ")
 texfile.write(values[0])
 texfile.write(" & ")
 texfile.write(values[2])
 texfile.write(" & \multirow{7}{*}{")
 texfile.write(values[13])
 texfile.write("}\\\\ \n")
 texfile.write("\\cline{2-4} \n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & ")
 texfile.write(values[1])
 texfile.write(" & ")
 texfile.write(values[3])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("\\multirow{2}{*}{1 b-tag} & $50 \leq E^{miss}_T < 150$ & ")
 texfile.write(values[4])
 texfile.write(" & ")
 texfile.write(values[6])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{2-4}\n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & ")
 texfile.write(values[5])
 texfile.write(" & ")
 texfile.write(values[7])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("\\multirow{2}{*}{2 b-tags} & $50 \leq E^{miss}_T < 150$ & ")
 texfile.write(values[8])
 texfile.write(" & ")
 texfile.write(values[10])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{2-4}\n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & ")
 texfile.write(values[9])
 texfile.write(" & ")
 texfile.write(values[11])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("$ \geq 3$ b-tags & $50 \leq E^{miss}_T < 300$ & \multicolumn{2}{|c|}{")
 texfile.write(values[12])
 texfile.write("} &\\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("inclusive & $E^{miss}_T \geq 300$ & \multicolumn{3}{|c|}{")
 texfile.write(values[14])
 texfile.write("}\\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("\\end{tabular} \\\\ \\vspace{0.2cm} \n")
 texfile.write("Explanation of rates: \\quad $\\textrm{observed : expected } \\pm \\textrm{ stat } \\pm \\textrm{ syst}$")
 texfile.write("\\newpage \n")
 texfile.write("\\large{Baseline selection: 3 tight leptons with $p_T > 20 / 15 / 10$ GeV, min. 2 jets, $E^{miss}_T > 50$ GeV and $M_{ll} \geq 12$ GeV}\\normalsize \\\\ \\vspace{1cm}\n")
 texfile.write("OffZ signal regions: OSSF-pair with $M_{ll} < 76$ GeV or $M_{ll} > 106$ GeV \\\\ \\vspace{0.5cm}\n")
 texfile.write("\\begin{tabular}{|c|c|c|c|c|}\n")
 texfile.write("\\hline \n")
 texfile.write("b-tags & $E^{miss}_T$ & $60 < H_T \leq 400$ & $400 \leq H_T < 600$ & $H_T \geq 600$\\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("\\multirow{2}{*}{0 b-tags} & $50 \leq E^{miss}_T < 150$ & ")
 texfile.write(values[15])
 texfile.write(" & ")
 texfile.write(values[17])
 texfile.write(" & \multirow{7}{*}{")
 texfile.write(values[28])
 texfile.write("}\\\\ \n")
 texfile.write("\\cline{2-4} \n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & ")
 texfile.write(values[16])
 texfile.write(" & ")
 texfile.write(values[18])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("\\multirow{2}{*}{1 b-tag} & $50 \leq E^{miss}_T < 150$ & ")
 texfile.write(values[19])
 texfile.write(" & ")
 texfile.write(values[21])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{2-4}\n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & ")
 texfile.write(values[20])
 texfile.write(" & ")
 texfile.write(values[22])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("\\multirow{2}{*}{2 b-tags} & $50 \leq E^{miss}_T < 150$ & ")
 texfile.write(values[23])
 texfile.write(" & ")
 texfile.write(values[25])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{2-4}\n")
 texfile.write("& $150 \leq E^{miss}_T < 300$ & ")
 texfile.write(values[24])
 texfile.write(" & ")
 texfile.write(values[26])
 texfile.write(" &\\\\ \n")
 texfile.write("\\cline{1-4}\n")
 texfile.write("$ \geq 3$ b-tags & $50 \leq E^{miss}_T < 300$ & \multicolumn{2}{|c|}{")
 texfile.write(values[27])
 texfile.write("} &\\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("inclusive & $E^{miss}_T \geq 300$ & \multicolumn{3}{|c|}{")
 texfile.write(values[29])
 texfile.write("}\\\\ \n")
 texfile.write("\\hline \n")
 texfile.write("\\end{tabular} \\\\ \\vspace{0.2cm} \n")
 texfile.write("Explanation of rates: \\quad $\\textrm{observed : expected } \\pm \\textrm{ stat } \\pm \\textrm{ syst}$")
 texfile.write("\\newpage \n")
 texfile.write("\\begin{figure}[htbp] \n")
 texfile.write("\\includegraphics{RA7_OnZ_SR.pdf} \n")
 texfile.write("\\end{figure} \n")
 texfile.write("\\newpage \n")
 texfile.write("\\begin{figure}[htbp] \n")
 texfile.write("\\includegraphics{RA7_OffZ_SR.pdf} \n")
 texfile.write("\\end{figure} \n")
 texfile.write("\\end{center}\n")
 texfile.write("\\renewcommand{\\arraystretch}{1}\n")
 texfile.write("\\end{document}\n")
 texfile.close()

os.system("pdflatex RA7table.tex")

os.remove("RA7table.tex")
os.remove("RA7table.log")
os.remove("RA7table.aux")
os.remove("RA7table.out")
os.remove("RA7_OnZ_SR.pdf")
os.remove("RA7_OffZ_SR.pdf")