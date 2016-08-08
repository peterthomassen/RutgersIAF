#!/bin/bash
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
export COIN_FULL_INDIRECT_RENDERING=1
echo $VO_CMS_SW_DIR
source $VO_CMS_SW_DIR/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc493
tar xzf CMSSW_7_6_3_patch2.tar.gz
cd CMSSW_7_6_3_patch2/src
scram b ProjectRename
eval `scramv1 runtime -sh` 
cd -
root -q -b -l dijetAnalysis.C\(\"$1\",\"$2\",$3,0,$4\)
xrdcp -f $2 root://cmseos.fnal.gov/$5/$2
rm $2

