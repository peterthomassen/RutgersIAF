#!/bin/bash

basedir=`pwd`
srcdir=`echo $basedir | sed 's/interface/src/'`
CMSDIR=`echo $basedir | awk '{split($1,array,"RutgersIAF"); print array[1]}'`
echo $basedir $srcdir $CMSDIR
tmpfile=tmp.tmp
ls -l $basedir/*.h | awk '{print $9}' > $tmpfile
#lnkdef=$srcdir/LinkDef.h

while read line
do
  srcfile=`echo $line | sed 's/interface/src/' | sed 's/\.h/\.cpp/'`
  lnkdef=`echo $srcfile | sed 's/\.cpp/_LinkDef\.h/'`
  headline=`echo $line | sed "s,$CMSDIR,,"`
  classname=`echo $headline | sed 's,\.h,,' | sed 's,RutgersIAF/EventAnalyzer/interface/,,'`
  if [ ! -e $srcfile ]
      then
      echo $headline $classname
      touch $srcfile
      echo "#include \"$headline\"" >> $srcfile
      echo "" >> $srcfile
      echo "ClassImp(${classname})" >> $srcfile

      #sed -i "/SignatureObject.h/ a #include \"$headline\"" $lnkdef
      #sed -i "/#endif/ i #pragma link C++ class ${classname}+;" $lnkdef
  fi
  if [ ! -e $lnkdef ]
      then
      touch $lnkdef
      echo $lnkdef
      echo "#include \"$headline\"" >> $lnkdef
      echo "" >> $lnkdef
      echo "#ifdef __CINT__" >> $lnkdef
      echo "#pragma link off all globals;" >> $lnkdef
      echo "#pragma link off all classes;" >> $lnkdef
      echo "#pragma link off all functions;" >> $lnkdef
      echo "#pragma link C++ nestedclasses;" >> $lnkdef
      echo "#pragma link C++ class ${classname}+;" >> $lnkdef
      echo "#endif" >> $lnkdef
  fi
done < $tmpfile
rm -rf $tmpfile
