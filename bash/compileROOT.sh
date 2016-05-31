#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: ./compileROOT.sh <inputFile>"
    exit 1
fi

AutoCanv="autoCanv"
path=$PWD
rest=${path#*$AutoCanv}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

srcStr="src/"
output=${1#*$srcStr}

g++ $1 $(root-config --cflags --libs) -I $path -Werror -Wall -O2 -o "$path/bin/${output/%.C/}.exe"
