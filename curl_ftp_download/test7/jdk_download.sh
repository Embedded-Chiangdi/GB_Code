#!/bin/bash
jdk_env="/download/jdk-7u79-linux-x64.tar.gz"
md5_loc="/home/jiangdi/Code_Project/curl_ftp_download/test7/jdk-md5-hash.txt"
debug_time=`date`
if [ ! -d /download ]; then
	mkdir /download
fi
cd /download
echo $debug_time > debug_jdk_down.log
echo "move to /download" >> debug_jdk_down.log
echo "Start Check jdk pack " >> debug_jdk_down.log
if [ ! -e $jdk_env ]; then 
	echo "jdk pack file is not existed" >> debug_jdk_down.log
	ping -c1 www.baidu.com > /dev/null 2>&1
	if [ $? -ne 0 ]; then 
		echo "Connected is not establish" >> debug_jdk_down.log
		exit 1
	fi
	echo "Connect established" >> debug_jdk_down.log
	echo "Now start Download our files" >> debug_jdk_down.log
	./ftp_file_get jdk_pack.conf
#./ftp_file_get jdk_pack.conf > /dev/null 2>&1
fi
echo "jdk pack file is existed now" >> debug_jdk_down.log
echo "check our file's md5" >> debug_jdk_down.log
md5sum -c $md5_loc >> debug_jdk_down.log
if [ $? -ne 0 ];then
	echo "the file is not integrity" >> debug_jdk_down.log
	rm -f $jdk_env
	exit 1
fi
echo "JDK Download Success" >> debug_jdk_down.log

echo "Check JDK Version" >> debug_jdk_down.log
remove_list=`rpm -qa | grep java-1.8.0` >> debug_jdk_down.log
if [ ! $? == 1 ]; then
for remove_ap in $remove_list
	do
			echo $remove_ap "is removed" >> debug_jdk_down.log
			yum erase -y $remove_ap > /dev/null
	done
fi

echo "JAVA-1.8.0 series are not extisted now" >> debug_jdk_down.log

exit 0
#this is a test for install jdk 1.7.0

echo "Now build our java env"
if [ ! -e /usr/java ]; then
	mkdir /usr/java
	echo "File /usr/java is created"
fi
cp $jdk_env /usr/java/
pwd
echo "mv to /usr/java"
cd /usr/java/
pwd
tar -zxvf jdk-7u79-linux-x64.tar.gz > /dev/null
echo "JAVA_HOME=/usr/java/jdk1.7.0_79" >> /etc/profile
echo "PATH=\$JAVA_HOME/bin:\$PATH" >> /etc/profile
echo "CLASSPATH=\$JAVA_HOME/jre/lib/ext:\$JAVA_HOME/lib/tools.jar" >> /etc/profile
echo "export PATH JAVA_HOME CLASSPATH" >> /etc/profile
echo "configuration loaded "
source /etc/profile
echo "fine"
echo "wait"
java -version > /dev/null 2>&1
if [ $? -ne 0 ];then
	echo "build failed"
	exit 1
fi
echo "leave "
exit 0
