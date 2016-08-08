#!/bin/bash
echo ""
echo "-- Script to create Condor jobs for skimming single AnalysisTrees --"

if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Missing arguments"
    echo " ./createCondorJobs_SingleSkim.sh <Sample> <SampleDirPath> <Skim: 2L/3L; default 3L>"
    echo "   ex: ./createCondorJobs_SingleSkim.sh TTJets /cms/multilepton/NTUPLES/2015/MC/TTJets/0000 2L"
    echo ""
    echo "..exiting!"
    echo ""
    exit 1
fi

echo "Input  dir: "$1
echo ""

Sample=$1
inputDir=$2
if [ -z "$3" ]; then
   Skim="3L"
  else
   Skim=$3
  fi
ShortSkim=3

if [ "$Skim" = "2L" ]; then
   ShortSkim=2
fi


MAINDIR=`pwd`
datestamp=`date +"%D_%T" | sed 's|/||g' |  sed 's|:||g'`
mkdir -p $inputDir/"Skim"$Skim"_"$datestamp/
mkdir -p $inputDir/"Skim"$Skim"_"$datestamp/log/
outputDir=$inputDir/"Skim"$Skim"_"$datestamp/
logDir=$inputDir/"Skim"$Skim"_"$datestamp/log/
CMSDIR=$CMSSW_BASE/src

condorFile=$MAINDIR"/submitSingleSkim_"$Sample"_"$Skim"_"$datestamp".condor"

if [ -e $condorFile ]
then
    rm -rf $condorFile
fi
touch $condorFile

runScript=$MAINDIR/runSingleSkimCondor.sh
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
echo "" >> $runScript
echo 'inFile=$1' >> $runScript
echo 'inDir=$2' >> $runScript
echo 'outDir=$3' >> $runScript
echo 'SkimMode=$4' >> $runScript
echo 'outFile="Skim"$SkimMode"L_"$inFile' >> $runScript
echo "" >> $runScript
echo 'haddCmd="haddR -d \"\$DROPBRANCHES\" -c \"NLIGHTLEPTONS[0]>=$SkimMode\" "$outDir"/"$outFile" "$inDir"/"$inFile' >> $runScript
echo "" >> $runScript
echo 'eval $haddCmd' >> $runScript
echo "" >> $runScript


echo "universe = vanilla" >> $condorFile
echo '+AccountingGroup = "group_rutgers.'$USER'"' >> $condorFile
echo 'Requirements = (Arch == "X86_64")' >> $condorFile
echo "Executable = $runScript" >> $condorFile
echo "should_transfer_files = NO" >> $condorFile
echo "Notification=never" >> $condorFile
echo "" >> $condorFile
echo "" >> $condorFile

#
tmplist=tmp.tmp
#target directory
ls -l $inputDir | grep '.root' > $tmplist

while read line
do
  base=`echo $line | awk '{split($9,array,"_"); print array[1]}'`
  ofile=`echo $line | awk '{print $9}' | sed 's|.root||g'`
  ifdir=`echo $line | awk '{print $9}'`
  echo "output = $logDir/\$(Cluster)_${ifdir}.out" >> $condorFile
  echo "error = $logDir/\$(Cluster)_${ifdir}.err" >> $condorFile
  echo "log = $logDir/\$(Cluster)_${ifdir}.log" >> $condorFile
  echo "arguments = $ifdir $inputDir $outputDir $ShortSkim" >> $condorFile
  echo "queue" >> $condorFile
  echo "" >> $condorFile
done < $tmplist
rm -rf $tmplist
