#!/bin/bash
echo ""
echo "-- Script to create Condor jobs for EventAnalyzer --"

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
    echo "Missing arguments"
    echo " ./createJobsToCondor.sh  <script.C> <SampleDirName> <SampleFileList>"
    echo "   ex: ./createJobsToCondorLPC.sh  exampleAnalysisTree.C TTJets ttjets.list"
    echo ""
    echo "..exiting!"
    echo ""
    exit 1
fi

echo "Input   .C: "$1
echo "Input Name: "$2
echo "Input filelist: "$3" nFiles:"`wc -l $3 | awk '{print $1}'`
echo ""
inC=$1
inSampleName=$2
inFileList=$3

############
####Uncomment following line for using files from grid
############You will need to have your grid certificate installed
##################
voms-proxy-init
#xrootdTag="root://cmsxrootd.fnal.gov//"
#xrootdTag="root://xrootd-cms.infn.it//"
xrootdTag=""

#you will never get an email but good to have this set properly
NOTIFYADDRESS="${USER}@physics.rutgers.edu"
MAINDIR=`pwd`
SCRIPTDIR=`pwd`
LOGDIR=$MAINDIR/logs
mkdir -p $LOGDIR
CMSDIR=$CMSSW_BASE/src
BASEOUTDIR=/store/user/`whoami`/2016/AnalysisTrees2
jsonFile="Cert_271036-274421_13TeV_PromptReco_Collisions16_JSON.txt"

echo ""
echo "WARNING: JSON file, macro, and helperMacro need to be in the directory from which you submit the jobs or you will need to adjust paths"
echo ""

source /cvmfs/cms.cern.ch/cmsset_default.sh
cd $CMSSW_BASE
eval `scramv1 runtime -sh`

cd $CMSSW_BASE/..
tar  --exclude-caches-all -czf ${SCRIPTDIR}/${CMSSW_VERSION}.tar.gz ${CMSSW_VERSION}/
cd $MAINDIR

eos root://cmseos.fnal.gov mkdir $BASEOUTDIR

# Specify input files here:
#link to folder with files
inputFolder=$inSampleName
#
datestamp=`date +"%D_%T" | sed 's|/||g' |  sed 's|:||g'`
inputFolder2=$inputFolder"__"$datestamp

condorFile=$SCRIPTDIR"/submitJobsCondor_"$USER"_"$inputFolder2".condor"

if [ -e $condorFile ]
then
    rm -rf $condorFile
fi
touch $condorFile

runScript=$SCRIPTDIR/runJobsCondor_tmp.sh #temporary script execution file
if [ -e $runScript ]
then
    rm -rf $runScript
fi
touch $runScript
chmod a+x $runScript

echo "#!/bin/bash" >> $runScript
echo "export VO_CMS_SW_DIR=/cms/base/cmssoft" >> $runScript
echo "export COIN_FULL_INDIRECT_RENDERING=1" >> $runScript
echo "export HOME="$HOME >> $runScript
echo 'echo $VO_CMS_SW_DIR' >> $runScript
echo 'source $VO_CMS_SW_DIR/cmsset_default.sh' >> $runScript
echo "export SCRAM_ARCH=$SCRAM_ARCH" >> $runScript
echo "tar xzf ${CMSSW_VERSION}.tar.gz" >> $runScript
echo "cd ${CMSSW_VERSION}/src" >> $runScript
echo "scram b ProjectRename" >> $runScript
echo 'eval `scramv1 runtime -sh` ' >> $runScript
#echo "cd $SCRIPTDIR/Datacards/coNLSP" >> $runScript
echo "cd -" >> $runScript
# Specify .C macro to be run here:
echo 'root -q -b -l '$inC'\(\"$1\",\"$2\",\"$3\",$4\,$5\,$6\,$7\,$8\)' >> $runScript
###echo 'root -q -b -l '$inC'\(\"$1\",\"$2\",\"$3\",$4\,$5\,$6\,$7\)' >> $runScript
###echo 'root -q -b -l '$inC'\(\"$1\",\"$2\",$3\,$4\,$5\,$6\,$7\)' >> $runScript
echo 'xrdcp -f $2 root://cmseos.fnal.gov//$BASEOUTDIR/$9/$2' >> $runScript
echo "" >> $runScript


echo "universe = vanilla" >> $condorFile
echo 'Requirements = OpSys == "LINUX" && (Arch != "DUMMY" )' >> $condorFile
echo "Executable = $runScript" >> $condorFile
echo "Should_Transfer_Files = YES" >> $condorFile
echo "request_disk = 10000000" >> $condorFile
echo "request_memory = 2100" >> $condorFile
echo "WhenTOTransferOutput  = ON_EXIT_OR_EVICT" >> $condorFile
echo "Notification=never" >> $condorFile
echo "notify_user = $NOTIFYADDRESS" >> $condorFile
echo 'x509userproxy = $ENV(X509_USER_PROXY)' >> $condorFile
echo "Transfer_Input_Files = runEfficiency.sh, ${CMSSW_VERSION}.tar.gz, helperMiniAODv2.C,$inC,$jsonFile" >> $condorFile
echo "" >> $condorFile
echo "" >> $condorFile

#

while read line
do
  #base=`echo $line | awk '{split($9,array,"_"); print array[1]}'`
    base=`echo $line | awk '{split($1,array,"results_"); split(array[2],array2,".");print array2[1]}'`
  # ---------------------------------------------------------------------------------
  # --------------------------------------------------------------------------------- 
  # Parameters to be specified by user
  mode=1 # primary dataset: 1=MUEG, 2=DOUBLEMU, 3=DOUBLEEG, 4=SINGLEMU, 5=SINGLEEL
  noFakes=0
  isMC=false
  suffix="data"
  #suffix="simulation"
  # -- -- -- -- -- -- --
  # These dont need to be modified usually:
  iLo=0
  iHi=-1
  # --------------------------------------------------------------------------------- 
  # ---------------------------------------------------------------------------------
  #
  ifname=$line
  ofname="histo_${inSampleName}_${base}.root"
  
  echo "output = $LOGDIR/\$(Cluster)_$suffix_${inSampleName}_${base}.out" >> $condorFile
  echo "error = $LOGDIR/\$(Cluster)_$suffix_${inSampleName}_${base}.err" >> $condorFile
  echo "log = $LOGDIR/\$(Cluster)_$suffix_${inSampleName}_${base}.log" >> $condorFile
  ###echo "arguments = CondorSimSamples/$inputFolder/$ifdir CondorPU/${ifdir}.pu.root $OUTDIR/\$(Cluster)_${ofile}_simulation.root $mode $iLo $iHi $noFakes" >> $condorFile
  ###echo "arguments = CondorSimSamples/$inputFolder/$ifdir  $OUTDIR/\$(Cluster)_${ofile}_simulation.root  $jsonFile $mode $iLo $iHi $noFakes $isMC" >> $condorFile
  echo "arguments =$ifname $ofname $jsonFile $mode $iLo $iHi $noFakes $isMC $inSampleName" >> $condorFile
  echo "queue" >> $condorFile
  echo "" >> $condorFile
done < $inFileList
rm -rf $tmplist
cp $condorFile $LOGDIR/
cp $runScript $LOGDIR/
#cp ./createJobsToCondor.sh $LOGDIR/
echo ""
echo "Submitting: "$inputFolder
echo ""
echo "To submit jobs:"
echo "condor_submit submitJobsCondor_"$USER"_"$inputFolder2".condor"
echo ""
echo "To watch job progress:"
echo "watch -n 10 'condor_q "$USER" | grep \";\"'"
echo ""
echo "Output  log files: "$LOGDIR
echo ""
echo "Output root files: "${BASEOUTDIR}/${inSampleName}
echo ""