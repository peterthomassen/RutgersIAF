#!/bin/bash
echo ""
echo "-- Script to create Condor jobs for EventAnalyzer --"

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
    echo "Missing arguments"
    echo " ./createJobsToCondor.sh  <script.C> <SampleDirName> <SampleDirPath>"
    echo "   ex: ./createJobsToCondor.sh  exampleAnalysisTree.C TTJets /cms/multilepton/NTUPLES/2015/MC/TTJets/0000"
    echo ""
    echo "..exiting!"
    echo ""
    exit 1
fi

echo "Input   .C: "$1
echo "Input Name: "$2
echo "Input  dir: "$3
echo ""
inC=$1
inSampleName=$2
inSampleDir=$3

############
####Uncomment following line for using files from grid
############You will need to have your grid certificate installed
##################
#voms-proxy-init --out $HOME/proxy
#xrootdTag="root://cmsxrootd.fnal.gov//"
#xrootdTag="root://xrootd-cms.infn.it//"
xrootdTag=""

MAINDIR=`pwd`
SCRIPTDIR=`pwd`
mkdir -p /cms/multilepton/$USER/CondorLogs/
LOGDIR=/cms/multilepton/$USER/CondorLogs
CMSDIR=$CMSSW_BASE/src


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
echo "cd $CMSDIR" >> $runScript
echo 'eval `scramv1 runtime -sh` ' >> $runScript
echo "cd $SCRIPTDIR" >> $runScript
# Specify .C macro to be run here:
#echo 'root -q -b -l '$inC'\(\"$1\",\"$2\",\"$3\",$4\,$5\,$6\,$7\)' >> $runScript
echo 'root -q -b -l '$inC'\(\"$1\",\"$2\",$3\,$4\,$5\,$6\,$7\)' >> $runScript
echo "" >> $runScript

echo "universe = vanilla" >> $condorFile
echo '+AccountingGroup = "group_rutgers.'$USER'"' >> $condorFile
echo 'Requirements = (Arch == "X86_64")' >> $condorFile
echo "Executable = $runScript" >> $condorFile
echo "should_transfer_files = NO" >> $condorFile
echo "Notification=never" >> $condorFile
echo "use_x509userproxy = true" >> $condorFile
echo "x509userproxy = $HOME/proxy" >> $condorFile 
echo "" >> $condorFile
echo "" >> $condorFile

LOGDIR=$LOGDIR/$inputFolder2/
mkdir -p $LOGDIR
OUTDIR=/cms/multilepton/$USER/CondorRootOut/$inputFolder2/
mkdir -p $OUTDIR
#
tmplist=tmp.tmp
#target directory
ls -l $inSampleDir | grep -v total > $tmplist

while read line
do
  base=`echo $line | awk '{split($9,array,"_"); print array[1]}'`
  #jsonFile=" "
  mode=0
  iLo=0
  iHi=500
  noFakes=0
  isMC=false
  ofile=`echo $line | awk '{print $9}' | sed 's|.root||g'`
  ifdir=`echo $line | awk '{print $9}'`
  echo "output = $LOGDIR/\$(Cluster)_simulation_${ifdir}.out" >> $condorFile
  echo "error = $LOGDIR/\$(Cluster)_simulation_${ifdir}.err" >> $condorFile
  echo "log = $LOGDIR/\$(Cluster)_simulation_${ifdir}.log" >> $condorFile
  #echo "arguments = CondorSimSamples/$inputFolder/$ifdir CondorPU/${ifdir}.pu.root $OUTDIR/\$(Cluster)_${ofile}_simulation.root $mode $iLo $iHi $noFakes" >> $condorFile
  #echo "arguments = CondorSimSamples/$inputFolder/$ifdir  $OUTDIR/\$(Cluster)_${ofile}_simulation.root  $jsonFile $mode $iLo $iHi $noFakes $isMC" >> $condorFile
  echo "arguments = CondorInputSamples/$inputFolder/$ifdir  $OUTDIR/\$(Cluster)_${ofile}_simulation.root $mode $iLo $iHi $noFakes $isMC" >> $condorFile
  echo "queue" >> $condorFile
  echo "" >> $condorFile
done < $tmplist
rm -rf $tmplist
cp $condorFile $LOGDIR/
cp $runScript $LOGDIR/
cp ./createJobsToCondor.sh $LOGDIR/
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
echo "Output root files: "$OUTDIR
echo ""