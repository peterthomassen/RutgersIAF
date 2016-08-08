#!/bin/bash


MAINDIR=`pwd`
SCRIPTDIR=`pwd`/scripts
LOGDIR=$MAINDIR/logs
CMSDIR=$CMSSW_BASE/src
DATAPATH=/store/user/stata/AnalysisTrees

source /cvmfs/cms.cern.ch/cmsset_default.sh
cd $CMSSW_BASE
eval `scramv1 runtime -sh`

cd $CMSSW_BASE/..
tar  --exclude-caches-all -czf ${MAINDIR}/${CMSSW_VERSION}.tar.gz ${CMSSW_VERSION}/
cd $MAINDIR

echo "done copying CMSSW"

#sleep 50m

runScript=$MAINDIR/runEfficiency.sh
if [ -e $runScript ]
then
    rm -rf $runScript
fi
touch $runScript
chmod a+x $runScript

submitScript=$MAINDIR/submitJobs.sh
if [ -e $submitScript ]
then
    rm -rf $submitScript
fi
touch $submitScript


echo "#!/bin/bash" >> $runScript
echo "export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch" >> $runScript
echo "export COIN_FULL_INDIRECT_RENDERING=1" >> $runScript
echo 'echo $VO_CMS_SW_DIR' >> $runScript
echo 'source $VO_CMS_SW_DIR/cmsset_default.sh' >> $runScript
echo "export SCRAM_ARCH=$SCRAM_ARCH" >> $runScript
echo "tar xzf ${CMSSW_VERSION}.tar.gz" >> $runScript
echo "cd ${CMSSW_VERSION}/src" >> $runScript
echo "scram b ProjectRename" >> $runScript
echo 'eval `scramv1 runtime -sh` ' >> $runScript
#echo "cd $SCRIPTDIR/Datacards/coNLSP" >> $runScript
echo "cd -" >> $runScript
echo 'root -q -b -l dijetAnalysis.C\(\"$1\",\"$2\",$3,0,$4\)' >> $runScript
echo 'xrdcp -f $2 root://cmseos.fnal.gov/$5/$2' >> $runScript
echo 'rm $2' >> $runScript
echo "" >> $runScript


haddScript=$MAINDIR/runHaddR.sh
if [ -e $haddScript ]
then
    rm -rf $haddScript
fi
touch $haddScript
chmod a+x $haddScript
echo "#!/bin/bash" >> $haddScript
echo "export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch" >> $haddScript
echo "export COIN_FULL_INDIRECT_RENDERING=1" >> $haddScript
echo 'echo $VO_CMS_SW_DIR' >> $haddScript
echo 'source $VO_CMS_SW_DIR/cmsset_default.sh' >> $haddScript
echo "export SCRAM_ARCH=$SCRAM_ARCH" >> $haddScript
echo "tar xzf ${CMSSW_VERSION}.tar.gz" >> $haddScript
echo "cd ${CMSSW_VERSION}/src" >> $haddScript
echo "scram b ProjectRename" >> $haddScript
echo 'eval `scramv1 runtime -sh` ' >> $haddScript
#echo "cd $SCRIPTDIR/Datacards/coNLSP" >> $haddScript
echo "cd -" >> $haddScript
echo 'sample=$1' >> $haddScript
echo 'OUTDIR=$2' >> $haddScript
echo 'haddR -f  -c "(hasGoodVertex && (hasSingleElTriggers || hasSingleMuTriggers))" allHistos_${sample}.root `xrdfs root://cmseos.fnal.gov ls -u $OUTDIR | grep "\.root"`' >> $haddScript
echo 'xrdcp -f allHistos_${sample}.root root://cmseos.fnal.gov/'${DATAPATH}'/addedHistos/allHistos_${sample}.part' >> $haddScript
echo 'xrdfs root://cmseos.fnal.gov/ mv '${DATAPATH}'/addedHistos/allHistos_${sample}.part /store/user/stata/AnalysisTrees/addedHistos/allHistos_${sample}.root' >> $haddScript
echo 'rm -rf allHistos_${sample}.root' >> $haddScript
echo "" >> $haddScript


eos root://cmseos.fnal.gov mkdir -p ${DATAPATH}/addedHistos

processlist=process_20160613_isSignal.list
while read processAndIsSignal
do
    echo $processAndIsSignal
    process=`echo $processAndIsSignal | awk '{split($1,array,"+"); print array[1]}'`
    echo $process

    filelist=${SCRIPTDIR}/lists/${process}.list
    sample=`echo $process | sed 's/--//g'`
    
    isSignal=`echo $processAndIsSignal | awk '{split($1,array,"+"); print array[2]}'`
    echo $isSignal
    isMC=true
    echo $isMC

    dir1=`eos root://cmseos.fnal.gov ls -l /store/group/lpchbb/mwalker/2016/DisplacedDijet/${process}/ | awk '{print $9}'`
    dir2=`eos root://cmseos.fnal.gov ls -l /store/group/lpchbb/mwalker/2016/DisplacedDijet/${process}/${dir1}/ | awk '{print $9}'`
    dir3=`eos root://cmseos.fnal.gov ls -l /store/group/lpchbb/mwalker/2016/DisplacedDijet/${process}/${dir1}/${dir2}/ | awk '{print $9}'`
    indir=/store/group/lpchbb/mwalker/2016/DisplacedDijet/${process}/${dir1}/${dir2}/${dir3}/
    
    if [ -e $filelist ]
    then
	rm -rf $filelist
    fi

    eos root://cmseos.fnal.gov ls -l $indir | grep root | awk -v indir="root://cmseos.fnal.gov/$indir" '{print indir $9}' > $filelist
    
    OUTDIR=${DATAPATH}/${sample}/
    eos root://cmseos.fnal.gov mkdir -p $OUTDIR
    condorFileEff=$SCRIPTDIR/Efficiency/submitEfficiency_${sample}.condor
    if [ -e $condorFileEff ]
    then
	rm -rf $condorFileEff
    fi
    touch $condorFileEff

    echo "condor_submit $condorFileEff" >> $submitScript
    
    echo "universe = vanilla" >> $condorFileEff
    echo 'Requirements = OpSys == "LINUX" && (Arch != "DUMMY" )' >> $condorFileEff
    echo "Executable = $runScript" >> $condorFileEff
    echo "Should_Transfer_Files = YES" >> $condorFileEff
    echo "request_disk = 10000000" >> $condorFileEff
    echo "request_memory = 2100" >> $condorFileEff
    echo "WhenTOTransferOutput  = ON_EXIT_OR_EVICT" >> $condorFileEff
    echo "Notification=never" >> $condorFileEff
    echo "notify_user = stata@physics.rutgers.edu" >> $condorFileEff
    echo 'x509userproxy = $ENV(X509_USER_PROXY)' >> $condorFileEff
    echo "Transfer_Input_Files = runEfficiency.sh, ${CMSSW_VERSION}.tar.gz, dijetAnalysis.C, helperDisplacedDijets.C, helperDisplacedDijetTriggers.C" >> $condorFileEff
    echo "" >> $condorFileEff
    echo "" >> $condorFileEff
    
    i=0
    while read line
    do
	base=`echo $line | awk '{split($1,array,"results_"); split(array[2],array2,".");print array2[1]}'`
	ifname=$line
	mode=0
	ofile=histo_${sample}_${base}.root
	echo "output = $LOGDIR/\$(Cluster)_${i}_${base}_efficiency_${sample}.out" >> $condorFileEff
	echo "error = $LOGDIR/\$(Cluster)_${i}_${base}_efficiency_${sample}.err" >> $condorFileEff
	echo "log = $LOGDIR/\$(Cluster)_${i}_${base}_efficiency_${sample}.log" >> $condorFileEff
	echo "arguments = $ifname $ofile $isSignal $isMC $OUTDIR" >> $condorFileEff
	echo "queue" >> $condorFileEff
	echo "" >> $condorFileEff
	((i++))
    done < $filelist

    condorFileHadd=$SCRIPTDIR/HaddR/submitHaddR_${sample}.condor
    if [ -e $condorFileHadd ]
    then
        rm -rf $condorFileHadd
    fi
    touch $condorFileHadd

    echo "universe = vanilla" >> $condorFileHadd
    echo 'Requirements = OpSys == "LINUX" && (Arch != "DUMMY" )' >> $condorFileHadd
    echo "Executable = $haddScript" >> $condorFileHadd
    echo "Should_Transfer_Files = YES" >> $condorFileHadd
    echo "request_disk = 10000000" >> $condorFileHadd
    echo "request_memory = 2100" >> $condorFileHadd
    echo "WhenTOTransferOutput  = ON_EXIT_OR_EVICT" >> $condorFileHadd
    echo "Notification=never" >> $condorFileHadd
    echo "notify_user = stata@physics.rutgers.edu" >> $condorFileHadd
    echo 'x509userproxy = $ENV(X509_USER_PROXY)' >> $condorFileHadd
    echo "Transfer_Input_Files = runHaddR.sh,${CMSSW_VERSION}.tar.gz" >> $condorFileHadd
    echo "" >> $condorFileHadd
    echo "" >> $condorFileHadd

    echo "output = $LOGDIR/\$(Cluster)_haddR_${sample}.out" >> $condorFileHadd
    echo "error = $LOGDIR/\$(Cluster)_haddR_${sample}.err" >> $condorFileHadd
    echo "log = $LOGDIR/\$(Cluster)_haddR_${sample}.log" >> $condorFileHadd
    echo "arguments = $sample $OUTDIR" >> $condorFileHadd
    echo "queue" >> $condorFileHadd
    echo "" >> $condorFileHadd


done < $processlist