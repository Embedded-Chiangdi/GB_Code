#!/bin/bash
echo "Start Write our file."
if [ -e "/home/jiangdi/wtest" ];then
        echo "file exists"
else
        echo "error"
        exit 1
fi
for num in {1..240}
do
        echo "address=/wifi"$num"dnstest.com/10.60.29.$num">> /home/jiangdi/wtest
        echo "writed $num ip and dns info"
done

