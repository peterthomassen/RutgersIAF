#!/bin/bash

MAINDIR=`pwd`
SCRIPTDIR=`pwd`/scripts
LOGDIR=$MAINDIR/logs
CMSDIR=$CMSSW_BASE/src

tag=TChiwz_200_100
#nevents=116755
nevents=10000

#hadronizer=Hadronizer_TuneCUETP8M1_13TeV_generic_LHE_pythia8_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO.py
#hadronizer=Hadronizer_TuneCUETP8M1_13TeV_generic_LHE_pythia8_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT_PU.py
#hadronizer=step0_LHEtoGENSIM.py
#hadronizer=step1_GEN_DIGI_L1_DIGI2RAW_HLT_PU.py
hadronizer=step3_PAT.py

###########
##Uncomment next line for grid
#voms-proxy-init -out $HOME/proxy

condorFile=$SCRIPTDIR/submitStep3_${tag}.sh

if [ -e $condorFile ]
then
    rm -rf $condorFile
fi
touch $condorFile
chmod a+x $condorFile


i=0
n=0
while [ $n -lt $nevents ]
  do
  runScript=$SCRIPTDIR/runJobsStep3_${tag}_${i}.sh
  if [ -e $runScript ]
      then
      rm -rf $runScript
  fi
  touch $runScript
  chmod a+x $runScript
  
  
  echo "#BSUB -o $LOGDIR/recoStep3_${tag}_${i}.out" >> $runScript
  echo "#BSUB -e $LOGDIR/recoStep3_${tag}_${i}.err" >> $runScript
  echo "#BSUB -L /bin/bash" >> $runScript
  echo "cd $CMSDIR" >> $runScript
  echo "export SCRAM_ARCH=$SCRAM_ARCH" >> $runScript
  echo "export X509_USER_PROXY=~/proxy" >> $runScript
  echo 'eval `scramv1 runtime -sh`' >> $runScript
  echo "cd $MAINDIR" >> $runScript
  
  echo "cmsRun $hadronizer file:output/step2_${tag}_${i}.root output/step3_${tag}_${i}.root" >> $runScript
  
  echo "bsub -R \"pool>30000\" -q 1nd < $runScript" >> $condorFile
  let i++  
  n=$(($i * 500))
done
