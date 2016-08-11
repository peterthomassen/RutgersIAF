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
sample=$1
OUTDIR=$2
haddR -f  -c "(hasGoodVertex && (hasSingleElTriggers || hasSingleMuTriggers))" allHistos_${sample}.root `xrdfs root://cmseos.fnal.gov ls -u $OUTDIR | grep "\.root"`
xrdcp -f allHistos_${sample}.root root://cmseos.fnal.gov//store/user/stata/AnalysisTrees/addedHistos/allHistos_${sample}.part
xrdfs root://cmseos.fnal.gov/ mv /store/user/stata/AnalysisTrees/addedHistos/allHistos_${sample}.part /store/user/stata/AnalysisTrees/addedHistos/allHistos_${sample}.root
rm -rf allHistos_${sample}.root

