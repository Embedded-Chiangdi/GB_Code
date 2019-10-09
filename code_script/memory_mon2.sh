#!/bin/bash
for d in `df -h | grep / | awk '{print $5}' | cut -f 1 -d "%"`
do
	if [ $d -gt 70 ];then
	echo "Disk Warning of Service of Shanghai"
	echo "Used $d"
fi
done
