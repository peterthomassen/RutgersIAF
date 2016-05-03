#!/bin/bash
echo ""
echo "-- Script to haddR AnalysisTrees --"

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ] || [ -z "$4" ]; then
  echo "Missing arguments"
  echo " ./haddAnalysisTrees.sh  <OutputName> <InputOutputDirName> <Data/MC> <PartOfSample> "
  echo "   ex run command: ./haddAnalysisTrees.sh  DoubleMuon /cms/heindl/2016/AnalysisTrees/Data/output/DoubleMuon2015D_3__041516_114811/ Data 4"
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
Part=$4

declare -i CompPart
CompPart=$Part-1
declare -i maxFiles
ls -l $DirName | grep "root" | wc -l > NumFiles
  while read line
  do
    maxFiles=$line/100
done < NumFiles
rm -rf NumFiles

if [ "$DataFlag" = "Data" ]; then
    outFileFinal=$DirName"/"$outFile"_"$CompPart".data.root"
  else
    outFileFinal=$DirName"/"$outFile"_"$CompPart".simulation.root"
  fi
haddCmdFinal="haddR "$outFileFinal

for i in `seq 1 $maxFiles`; do
  if [ "$DataFlag" = "Data" ]; then
    outputFileTemp[$i]=$DirName"/"$outFile"_"$CompPart"_"$i".data.root"
  else
    outputFileTemp[$i]=$DirName"/"$outFile"_"$CompPart"_"$i".simulation.root"
  fi

  haddCmdTemp="haddR "${outputFileTemp[$i]}
  haddCmdFinal=$haddCmdFinal" "${outputFileTemp[$i]}

  tmplist[i]=tmp.tmp
  declare -i iPart
  iPart=($CompPart)*10+$i
  ls -l $DirName | grep 'results_'$iPart > ${tmplist[i]}
  while read line
  do
    ifdir=`echo -e $line | awk '{print $9}'`
    haddCmdTemp=$haddCmdTemp" "$DirName"/"$ifdir
  done < ${tmplist[i]}
  rm -rf "tmp.tmp"
  eval $haddCmdTemp
done
eval $haddCmdFinal
