#!/bin/bash
#monitor available disk space
Used=`df -h | sed -n '/\/$/p' | gawk '{print $5}'| sed 's/%//'`
if [ $Used -ge 75 ]
then
	echo "Disk Storage Warning $Used is Used"
fi	

