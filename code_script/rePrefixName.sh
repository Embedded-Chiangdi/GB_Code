#!/bin/bash
for files in $(ls *.txt)
	do mv $files "re"$files
done

