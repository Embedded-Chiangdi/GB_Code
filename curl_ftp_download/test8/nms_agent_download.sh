#!/bin/bash
nms_agent_pack_loc="/download/nms.app.proxy-v2.2.bin"
nms_agent_conf_loc="/appfs/etc/nms_agent/nms_pack.conf"
md5_loc="/appfs/etc/nms_agent/nms-md5-hash.txt"
debug_time=`date`

echo $debug_time > /download/debug_nms.log
echo "Start Download nms agent " >> /download/debug_nms.log
if [ ! -e $nms_agent_pack_loc ]; then 
	echo "file is not existed" >> /download/debug_nms.log
	cd /download
	echo "move to /download" >> /download/debug_nms.log
	echo "Now start Download nms agent files" >> /download/debug_nms.log
	ftp_file_get $nms_agent_conf_loc > /dev/null 2>&1
	chmod +x $nms_agent_pack_loc
fi
echo "nms agent file is existed " >> /download/debug_nms.log
echo "check our file's md5" >> /download/debug_nms.log
md5sum -c $md5_loc >> /download/debug_nms.log
if [ $? -ne 0 ];then
	echo "the file is not integrity" >> /download/debug_nms.log
	rm -f $nms_agent_pack_loc
	exit 1
fi
echo "the file is integrity" >> /download/debug_nms.log
if [ ! -e /home/server-agent/apache-tomcat-6.0.18/bin/startup.sh ];then
	echo "start install nms agent " >> /download/debug_nms.log
	$nms_agent_pack_loc install  > /dev/null 2>&1
	pidof java >> /download/debug_nms.log
	killall java
	echo "installed" >> /download/debug_nms.log
else
	echo  "nms agent alread installed"
fi
exit 0
