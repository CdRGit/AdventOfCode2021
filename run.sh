#!/bin/sh

if [ $# -lt 1 ]
then
    echo "too few arguments"
    exit
fi

if [ "$1" == "all" ]
then
    echo "all"
else
    cd $1
    if [ "$2" == "c" ]
    then
        gcc $1.c -I../ -o $1.elf -g
    fi
    ./$1.elf
    cd ..
fi