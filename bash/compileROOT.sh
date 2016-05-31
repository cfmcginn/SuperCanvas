#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: ./compileROOT.sh <inputFile>"
    exit 1
fi

SuperCanvas="SuperCanvas"
path=$PWD
rest=${path#*$SuperCanvas}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

srcStr="src/"
output=${1#*$srcStr}

mkdir -p $path/bin

g++ $1 $(root-config --cflags --libs) -I $path -Werror -Wall -O2 -o "$path/bin/${output/%.C/}.exe"
