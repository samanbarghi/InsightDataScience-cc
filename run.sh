#!/bin/bash

echo "Running 'make clean' ..."
make clean
echo
echo "Compiling the files ..."
make

echo
echo "Running the first feature ..."
./build/wordcount.o ./tweet_input/tweets.txt ./tweet_output/ft1.txt

echo
echo "Running the second feature ..."
./build/median.o ./tweet_input/tweets.txt ./tweet_output/ft2.txt