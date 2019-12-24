#!/bin/sh
CRONTAB="/home/jiangdi/test"
sed -i '/clientmqueue/d;/dfh_flag/d' $CRONTAB
cat $CRONTAB | grep clientmqueue > /dev/null
if [ $? == 1 ]; then
	echo "0 0 * * * root ls /var/spool/clientmqueue/* 2>/dev/null | xargs -n 10 rm -f " >> $CRONTAB
fi
