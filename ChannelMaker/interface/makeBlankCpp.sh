#!/bin/bash

basedir=`pwd`
srcdir=`echo $basedir | sed 's/interface/src/'`
CMSDIR=`echo $basedir | awk '{split($1,array,"RutgersIAF2012"); print array[1]}'`
echo $basedir $srcdir $CMSDIR
tmpfile=tmp.tmp
ls -l $basedir/*.h | awk '{print $9}' > $tmpfile
lnkdef=$srcdir/LinkDef.h

while read line
do
  srcfile=`echo $line | sed 's/interface/src/' | sed 's/\.h/\.cpp/'`
  if [ ! -e $srcfile ]
  then
      headline=`echo $line | sed "s,$CMSDIR,,"`
      classname=`echo $headline | sed 's,\.h,,' | sed 's,RutgersIAF2012/ChannelMaker/interface/,,'`
      echo $headline $classname
      touch $srcfile
      echo "#include \"$headline\"" >> $srcfile
      echo "" >> $srcfile
      echo "ClassImp(${classname})" >> $srcfile

      sed -i "/ChannelHandler.h/ a #include \"$headline\"" $lnkdef
      sed -i "/#endif/ i #pragma link C++ class ${classname}+;" $lnkdef

  fi
done < $tmpfile
rm -rf $tmpfile
