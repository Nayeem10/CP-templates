#!/bin/bash
# Call as sh stress.sh ITERATIONS

g++ candidate.cpp -o candidate  # candidate solution
g++ bruteforce.cpp -o bruteforce # bruteforce solution
g++ generator.cpp -o generator # test case generator

> all.txt

for i in $(seq 1 "$1") ; do
    echo "Attempt $i/$1"
    ./generator > in.txt

    echo "Attempt $i/$1" >> all.txt 
    cat < in.txt >> all.txt

    ./bruteforce < in.txt > out1.txt
    ./candidate < in.txt > out2.txt

    diff -y out1.txt out2.txt > diff.txt
    if [ $? -ne 0 ] ; then
        echo -e "\nTest case:"
        cat in.txt
        echo -e "\nOutputs:"
        cat diff.txt
        break
    fi
done

files=("in.txt" "out1.txt" "out2.txt" "diff.txt" "candidate" "bruteforce" "generator")
for file in "${files[@]}"; do
    rm "$file"
done