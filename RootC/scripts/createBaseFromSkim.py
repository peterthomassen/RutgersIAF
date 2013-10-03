#!/usr/bin/env python
import sys,math
from array import array
from optparse import OptionParser
import operator
import os
argv_org = list(sys.argv)
sys.argv = [e for e in sys.argv if e != '-h']
sys.argv.append('-b')
sys.argv = sys.argv[:-1]
sys.argv = argv_org

jetVariables = dict()
photonVariables = dict()
electronVariables = dict()
muonVariables = dict()
trackVariables = dict()
tauVariables = dict()
mcPartVariables = dict()
triggerVariables = dict()
vertexVariables = dict()
metVariables = dict()
enums = dict()

skipListKin = set(["pt","et","px","py","pz","pmag","eta","phi","energy"])
skipListIso = set(["caloIso","ecaloIso","hcaloIso","trackIso","allTrackIso","vertTrackIso","ecalIsoDep","hcalIsoDep"])
skipListRecoTrack = set()

def makeRead(variables,object):
    for k,p in variables.iteritems():
        if k in skipListKin: continue
        if k not in skipListRecoTrack:
            if p[1] < 0:
                print "    "+object+"->set"+k[:1].upper()+k[1:]+"("+p[2]+"[i]);"
            else:
                print "***    "+object+"->add"+k[:1].upper()+k[1:]+"("+p[2]+"[i][j]);"
        else:
            if p[1] < 0:
                print "    "+object+"->set"+k[:1].upper()+k[1:]+"("+p[2]+"[i]);//###"
            else:
                print "***    "+object+"->add"+k[:1].upper()+k[1:]+"("+p[2]+"[i][j]);"
def makeReadTrack(object):
    variables = trackVariables
    for k,p in variables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        if p[1] < 0:
            print "    "+object+"->set"+k[:1].upper()+k[1:]+"("+p[2]+"[gtID]);"
        else:
            print "***    "+object+"->add"+k[:1].upper()+k[1:]+"("+p[2]+"[gtID][j]);"

def makeSO(variables,name):
    print "======"+name+"======"
    for k,p in variables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        if k in skipListRecoTrack: continue
        if p[1] < 0:
            print "  "+p[0]+" get"+k[:1].upper()+k[1:]+"(){return m_"+k+";}"
        else:
            print "  std::vector<"+p[0]+"> get"+k[:1].upper()+k[1:]+"(){return m_"+k+";}"
            print "  "+p[0]+" get"+k[:1].upper()+k[1:]+"At(int i){return m_"+k+"[i];}"

    print ""
    
    for k,p in variables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        if k in skipListRecoTrack: continue
        if p[1] < 0:
            print "  void set"+k[:1].upper()+k[1:]+"("+p[0]+" c){m_"+k+" = c;}"
        else:
            print "  void add"+k[:1].upper()+k[1:]+"("+p[0]+" c){m_"+k+".push_back(c);}"

    print ""
    print " private:"
    for k,p in variables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        if k in skipListRecoTrack: continue
        if p[1] < 0:
            print "  "+p[0]+" m_"+k+";"
        else:
            print "  std::vector<"+p[0]+"> m_"+k+";"

    print "-------------"

    for k,p in variables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        if k in skipListRecoTrack: continue
        if p[1] < 0: print "  m_"+k+" = -10000;"

    print "======"+name+"======"

def makeSORecoTrack():
    print "=====RECOTRACK======"
    for k,p in trackVariables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        print "  "+p[0]+" get"+k[:1].upper()+k[1:]+"(){return m_"+k+";}"

    print ""

    for k,p in trackVariables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        print "  void set"+k[:1].upper()+k[1:]+"("+p[0]+" c){m_"+k+" = c;}"

    print ""
    print " private:"

    for k,p in trackVariables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        print "  "+p[0]+" m_"+k+";"

    print "--------------"
    for k,p in trackVariables.iteritems():
        if k in skipListKin: continue
        if k in skipListIso: continue
        print "  m_"+k+" = -10000;"
    print "=====RECOTRACK======"

def makeSOMET():
    print "=====MET======"
    for k,p in metVariables.iteritems():
        if k in skipListKin: continue
        if p[1] < 0:
            print "  "+p[0]+" get"+k[:1].upper()+k[1:]+"(){return m_"+k+";}"
        else:
            print "  std::vector<"+p[0]+"> get"+k[:1].upper()+k[1:]+"(){return m_"+k+";}"
            print "  "+p[0]+" get"+k[:1].upper()+k[1:]+"At(int i){return m_"+k+"[i];}"

    print ""

    for k,p in metVariables.iteritems():
        if k in skipListKin: continue
        if p[1] < 0:
            print "  void set"+k[:1].upper()+k[1:]+"("+p[0]+" c){m_"+k+" = c;}"
        else:
            print "  void add"+k[:1].upper()+k[1:]+"("+p[0]+" c){m_"+k+".push_back(c);}"

    print ""
    print " private:"

    for k,p in metVariables.iteritems():
        if k in skipListKin: continue
        if p[1] < 0:
            print "  "+p[0]+" m_"+k+";"
        else:
            print "  std::vector<"+p[0]+"> m_"+k+";"

    print "--------------"
    for k,p in metVariables.iteritems():
        if k in skipListKin: continue
        if p[1] < 0: print "  m_"+k+" = -10000;"
    print "=====MET======"
def makeSOMCPart():
    print "=====MCPART======"
    for k,p in mcPartVariables.iteritems():
        if k in skipListKin: continue
        if p[1] < 0:
            print "  "+p[0]+" get"+k[:1].upper()+k[1:]+"(){return m_"+k+";}"
        else:
            print "  std::vector<"+p[0]+"> get"+k[:1].upper()+k[1:]+"(){return m_"+k+";}"
            print "  "+p[0]+" get"+k[:1].upper()+k[1:]+"At(int i){return m_"+k+"[i];}"

    print ""

    for k,p in mcPartVariables.iteritems():
        if k in skipListKin: continue
        if p[1] < 0:
            print "  void set"+k[:1].upper()+k[1:]+"("+p[0]+" c){m_"+k+" = c;}"
        else:
            print "  void add"+k[:1].upper()+k[1:]+"("+p[0]+" c){m_"+k+".push_back(c);}"

    print ""
    print " private:"

    for k,p in mcPartVariables.iteritems():
        if k in skipListKin: continue
        if p[1] < 0:
            print "  "+p[0]+" m_"+k+";"
        else:
            print "  std::vector<"+p[0]+"> m_"+k+";"

    print "--------------"
    for k,p in mcPartVariables.iteritems():
        if k in skipListKin: continue
        if p[1] < 0: print "  m_"+k+" = -10000;"
    print "=====MCPART======"

def readEnums(file):
    for line in file:
        if line.find("enum") == -1: continue
        if line.find("---") != -1: continue
        ls0 = line.split("=")
        ls1 = ls0[0].split("{")
        ls2 = ls0[1].split("}")
        enums[ls1[1].strip()] = int(ls2[0].strip())

def getVariable(line):
    ls0 = line.split()
    ls1 = ls0[1].split("[")
    return ls1[0].strip()

def getLength(line):
    length = -1
    if line.find("][") != -1:
        ls0 = line.split("][")
        ls1 = ls0[1].split("]")
        if enums.has_key(ls1[0].strip()):
            length = enums[ls1[0].strip()]
        else:
            length = int(ls1[0].strip())
    return length

def getType(line):
    ls0 = line.split()
    type = ls0[0].strip()
    if type.find("string") != -1: type = "TString"
    return type

def getName(sep,line):
    ls0 = line.split()
    ls1 = ls0[1].split("[")
    ls2 = ls1[0].split(sep)
    return ls2[1].strip()

def getNameTrigger(line):
    ls0 = line.split()
    ls1 = ls0[1].split("[")
    ls2 = ls1[0].split("triggers_")
    if len(ls2) < 2: return "name"
    return ls2[1].strip()    

def getNameMET(line):
    ls0 = line.split()
    ls1 = ls0[1].split(";")
    ls2 = ls1[0].split("[")
    return ls2[0].replace("met_","")


def readSkim(inputTag):
    cwd=os.getcwd()
    dirsplit = cwd.split("/src/")
    inputDir=dirsplit[0]+"/src/"+inputTag+"/RutgersEDAnalyzer/interface/"
    print inputDir
    inputSkim = open(inputDir+"SkimNtuple.h")
    all_lines = inputSkim.readlines()

    readEnums(all_lines)

    for line in all_lines:
        if line.find("enum") != -1: continue
        if line.strip().find("//") == 0: continue
        if line.find("[MAXNMUON]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getName("muon_",line)
            variable = getVariable(line)
            #print line
            muonVariables[name] = (type,length,variable)
        elif line.find("[MAXNELECTRON]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getName("electron_",line)
            variable = getVariable(line)
            electronVariables[name] = (type,length,variable)
        elif line.find("[MAXNPHO]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getName("photon_",line)
            variable = getVariable(line)
            photonVariables[name] = (type,length,variable)
        elif line.find("[MAXNJET]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getName("jet_",line)
            variable = getVariable(line)
            jetVariables[name] = (type,length,variable)
        elif line.find("[MAXNTAU]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getName("tau_",line)
            variable = getVariable(line)
            tauVariables[name] = (type,length,variable)
        elif line.find("[MAXNTRACK]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getName("track_",line)
            variable = getVariable(line)
            trackVariables[name] = (type,length,variable)
            skipListRecoTrack.add(name)
        elif line.find("[MAXTRIGGERS]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getNameTrigger(line)
            variable = getVariable(line)
            triggerVariables[name] = (type,length,variable)
        elif line.find("[MAXNMCPART]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getName("part_",line)
            variable = getVariable(line)
            mcPartVariables[name] = (type,length,variable)
        elif line.find("[MAXVERTEX]") != -1:
            length = getLength(line)
            type = getType(line)
            name = getName("vertex_",line)
            variable = getVariable(line)
            vertexVariables[name] = (type,length,variable)
        elif line.find("pat_met") != -1 or line.find("pf_met") != -1:
            length = -1
            if line.find("MAXTRIGFILTER") != -1: length = enums["MAXTRIGFILTER"]
            type = getType(line)
            name = getNameMET(line)
            variable = getVariable(line)
            metVariables[name] = (type,length,variable)

    #print jetVariables
    #print photonVariables
    #print electronVariables
    #print muonVariables
    #print trackVariables
    #print tauVariables
    #print mcPartVariables
    #print triggerVariables
    #print vertexVariables
    #print metVariables

def main():
    argv = sys.argv[1:]
    sys.argv = sys.argv[:1]
    parser = OptionParser(usage = "%prog [OPTION]... [FILE]...", version = "%prog 1.0")
    parser.add_option("-o", "--output-filename", action = "store", default = './dataPlots.root',
                      type = 'string', help = "globe file")
    parser.add_option("-i", "--input-tag", action = "store", default = 'RutgersTools50X',
                      type = 'string', help = "input RutgersToolsNNX")

    (options, args) = parser.parse_args(argv)

    #ofname = options.output_filename
    ggfname = options.input_tag

    #print "aa"

    readSkim(ggfname)
    #makeSORecoTrack()
    #makeSO(electronVariables,"ELECTRON")
    makeSO(muonVariables,"MUON")
    #makeSO(tauVariables,"TAU")
    #makeSO(photonVariables,"PHOTON")
    #makeSOMET()
    #makeSOMCPart()
    #makeSO(jetVariables,"JET")
    #makeSO(triggerVariables,"TRIGGER")
    #makeSO(vertexVariables,"VERTEX")
    #makeReadTrack("photon")
    #makeRead(photonVariables,"photon")
    #makeRead(jetVariables,"jet")
    #makeReadTrack("tau")
    #makeRead(mcPartVariables,"mcpart")
    makeReadTrack("muon")
    makeRead(muonVariables,"muon")
    return

if __name__ == '__main__':
    main()
