#!/bin/zsh
name="test"

for ((;1;))
do
    ./${name}D >${name}.in
    ./${name}B <${name}.in >${name}.out
    ./${name}  <${name}.in >${name}.out
    diff ${name}.out ${name}.ans
    if [ $? -ne "0" ]; then
        echo "Fucked!"
        exit
    else
        echo "Continue to fuck!"
    fi
done