#!/bin/bash
files=$(ls .)
for filename in $files
do
	echo $filename >> filename.txt
done
