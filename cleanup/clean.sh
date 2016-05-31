#!/bin/bash

AutoCanv="autoCanv"
path=$PWD
rest=${path#*$AutoCanv}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

rm $path/*.C~
rm $path/*_C.*
rm $path/src/*.C~
rm $path/src/*_C.*
rm $path/src/*.pcm
rm $path/bin/*.exe 
rm $path/include/*.h~
rm $path/bash/*.sh~
rm $path/cleanup/*.sh~

rm $path/outFileDir/*.root
rm $path/pdfDir/*.pdf
rmdir $path/outFileDir
rmdir $path/pdfDir