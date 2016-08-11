#!/bin/bash

# run this script in a 'screen' session so you can turn off your computer and let this run in the background

haddList=hadded.list
# list of all hadded samples

declare -A clusterEA
# dictionary that stores the EventAnalyzer condor cluster of each sample


declare -A processStatus
# this stores the status of each sample
# "-1" = EventAnalyzer condor_submit failed
# "0" = Event Analyzer submitted, not yet done
# "1" = done with EA
# "2" = hadd submitted


processList=process_20160613.list
# list of processes to run on. example included in directory

while read sample
do
  processStatus+=(["$sample"]="-1")
  clusterEA+=(["$sample"]="unset")
done < $processList

while read sample
do
  echo $sample
  echo "${processStatus["$sample"]}"
  echo "${clusterEA["$sample"]}"
  echo
done < $processList

while true
do
  restartLoop="false" # to control for condor failure, but hasn't been tested
  
  expect /uscms/home/stata/private/gridinit.exp # voms-proxy-init, script included in directory
  
  while read sample
  do
    echo $sample
    echo "${processStatus["$sample"]}"
    echo "${clusterEA["$sample"]}"
  done < $processList
  
  
  #submit EA
  while read sample
  do
    if [ ! "${processStatus["$sample"]}" == "-1" ]; then
      # continue if already submitted EA
      continue
    fi

    #submit and get cluter ID
    condorOutput=`condor_submit scripts/Efficiency/submitEfficiency_${sample}.condor`
    if [ "$condorOutput" == *"ERROR"* ]; then
      restartLoop="true"
      break
    fi
    condorOutput=`echo $condorOutput | sed -r 's/ /+/g'`
    echo $condorOutput
    cEA=`echo $condorOutput | awk '{n=split($1,array,"+"); split(array[n],array2,".");print array2[1]}'`
    echo $cEA;echo

    clusterEA["$sample"]="$cEA"
    processStatus["$sample"]="0"
  done < $processList
  
  if [ "$restartLoop" == "true" ]; then
    sleep 2m
    continue
  fi
  
  #parse and check if done with EA
  for sample in "${!clusterEA[@]}"
  do
    if [ ! "${processStatus["$sample"]}" == "0" ]; then
      continue
    fi
    
    cEA="${clusterEA["$sample"]}"
    
    tempEff=eff_${sample}.tmp
    
    condor_q $cEA >> $tempEff
    if grep -q 'Failed to fetch ads' "$tempEff"; then
      restartLoop="true"
      rm -rf $tempEff
      break
    fi
    
    if grep -q runEfficiency.sh "$tempEff"; then
      :
    else
      if [ "${processStatus["$sample"]}" == "0" ]; then
        processStatus["$sample"]="1"
      fi
    fi
    
    rm -rf $tempEff
  done

  if [ "$restartLoop" == "true" ]; then
    sleep 2m
    continue
  fi
  
  allAdded="true"
  # if done with EA, submit Hadd
  for sample in "${!clusterEA[@]}"
  do
    if [ "${processStatus["$sample"]}" == "0" ]; then
      allAdded="false"
      continue
    elif [ "${processStatus["$sample"]}" == "1" ]; then
      allAdded="false"
      
      if condor_submit scripts/HaddR/submitHaddR_${sample}.condor | grep -q 'Failed to fetch ads'; then
        restartLoop="true"
        rm -rf $tempEff
        break
      fi
      processStatus["$sample"]="2"
    fi
  done
  
  if [ "$restartLoop" == "true" ]; then
    sleep 2m
    continue
  fi

  # list of all complete added samples  
  if [ -e $haddList ]; then
    rm -rf $haddList
  fi
  touch $haddList
  eos root://cmseos.fnal.gov ls /store/user/stata/AnalysisTrees/addedHistos/ | grep .root >> $haddList

  #if [ "$allAdded" == "true" ]; then
  #  break
  #fi
  
  sleep 10m
done

echo "DONE HADD"