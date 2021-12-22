#!/bin/sh

if [ $# -lt 1 ]
then
    echo "too few arguments"
    exit
fi

if [ "$1" == "all" ]
then
    echo "all"
    for dir in */
    do 
        dir=${dir%*/}
        cd $dir
        if [ $2 == "c" ]
        then
            gcc $dir.c -I../ -o $dir.elf -g
        fi
        ./$dir.elf
        cd ..
        echo ""
    done
else
    cd $1
    if [ "$2" == "c" ]
    then
        gcc $1.c -I../ -o $1.elf -g
    fi
    ./$1.elf
    cd ..
fi