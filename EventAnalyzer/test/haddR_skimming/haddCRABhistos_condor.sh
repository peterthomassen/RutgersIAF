#!/bin/bash
export VO_CMS_SW_DIR=/cms/base/cmssoft
export COIN_FULL_INDIRECT_RENDERING=1
echo $VO_CMS_SW_DIR
source $VO_CMS_SW_DIR/cmsset_default.sh
cd /users/h2/heindl/software/CMSSW_8_0_8_patch2/src
eval `scramv1 runtime -sh` 

echo ""
echo "-- Script to haddR AnalysisTrees (from combined AODR + EA) --"
echo ""
echo "This script is usable for haddR'ing a huge number of TTree-files,"
echo "e.g. the output from crab'ing over datasets."
echo ""

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
  echo "Missing arguments"
  echo " ./haddCRABhistos.sh  <OutputName> <InputOutputDirName> <Data/MC>"
  echo "   ex run command: ./haddAnalysisTrees.sh  DoubleMuon /cms/heindl/2016/AnalysisTrees/Data/output/DoubleMuon2015D_3__041516_114811/ Data"
  echo "..exiting!"
  echo ""
  exit 1
fi

echo "Output-file: "$1
echo "Input- & output-directory: "$2
echo ""

outFile=$1
DirName=$2
DataFlag=$3

SkimDrop="\"\$DROPBRANCHES\""
Skim2L="\"NLIGHTLEPTONS[0]>=2\""
Skim3L="\"NLIGHTLEPTONS[0]>=3\""

timestamp=`date +"%D-%T" | sed 's|/||g' |  sed 's|:||g'`

if [ "$DataFlag" = "Data" ]; then
    outFileFinal=$DirName"/"$outFile"_"$timestamp".data.root"
    outFileFinal2L=$DirName"/"$outFile"_"$timestamp".2L.data.root"
    outFileFinal3L=$DirName"/"$outFile"_"$timestamp".3L.data.root"
  else
    outFileFinal=$DirName"/"$outFile"_"$timestamp".simulation.root"
    outFileFinal2L=$DirName"/"$outFile"_"$timestamp".2L.simulation.root"
    outFileFinal3L=$DirName"/"$outFile"_"$timestamp".3L.simulation.root"
  fi
haddCmdFinal="haddR "$outFileFinal
haddCmdFinal2L="haddR -d "$SkimDrop" -c "$Skim2L" "$outFileFinal2L
haddCmdFinal3L="haddR -d "$SkimDrop" -c "$Skim3L" "$outFileFinal3L

for i in `seq 0 9`; do
  if [ "$DataFlag" = "Data" ]; then
    outputFileTemp[$i]=$DirName"/"$outFile"_"$timestamp"_"$i".data.root"
  else
    outputFileTemp[$i]=$DirName"/"$outFile"_"$timestamp"_"$i".simulation.root"
  fi

  haddCmdTemp="haddR "${outputFileTemp[$i]}
  haddCmdFinal=$haddCmdFinal" "${outputFileTemp[$i]}
  haddCmdFinal2L=$haddCmdFinal2L" "${outputFileTemp[$i]}
  haddCmdFinal3L=$haddCmdFinal3L" "${outputFileTemp[$i]}

  tmplist[$i]=tmp.tmp
  ls -l $DirName | grep $i'.root' > ${tmplist[$i]}
  while read line
  do
    ifdir=`echo -e $line | awk '{print $9}'`
    haddCmdTemp=$haddCmdTemp" "$DirName"/"$ifdir
  done < ${tmplist[$i]}
  rm -rf "tmp.tmp"
  eval $haddCmdTemp
done
eval $haddCmdFinal3L
eval $haddCmdFinal2L
eval $haddCmdFinal
