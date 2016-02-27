#!/bin/bash
pre="ch"
for i in 1 2 3 4
do
    dir="$pre$i"
    echo $dir
    cd $dir
    sh runscript.sh
    cd ..
done

