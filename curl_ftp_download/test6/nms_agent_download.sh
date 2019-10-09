#!/bin/bash
echo "Start Download nms agent "
if [ ! -e ginms.app.agent-v1.1.bin ]; then 
	echo "file is not existed"
	echo "Now start Download our files"
	./ftp_file_get nms_pack.conf > /dev/null 2>&1
fi
echo "file is existed now"
echo "check our file's md5"
pwd
md5sum -c nms-md5-hash.txt
if [ $? -ne 0 ];then
	echo "the file is not integrity"
	rm -f ginms.app.agent-v1.1.bin
	exit 1
fi
echo "Download Success"
