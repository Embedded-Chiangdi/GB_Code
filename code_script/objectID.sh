#!/bin/bash
Device=`uname -n`
SNMP_SYSDESCR_ADD_TO_CONFIG_FILE="/appfs/etc/snmp/snmpd.conf"
cat ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE} | grep sysObjectID > /dev/null
if [ $? == 0 ];then
    exit 0
fi
case $Device in
    CGW2000)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.100">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW3000)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.101">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW3000T)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.102">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW4000)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.103">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW4000T)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.104">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW4700)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.105">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW9000)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.106">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW3400T)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.107">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW3400)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.108">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    CGW2400)
    echo "sysObjectID .1.3.6.1.4.1.28723.888.3.109">> ${SNMP_SYSDESCR_ADD_TO_CONFIG_FILE}
    ;;
    *)
    echo "finished this chieck"
    ;;
esac
pidof snmpd > /dev/null
if [ $? == 0 ];then
    kill -9 `pidof snmpd`
    kill -9 `pidof snmpagentd`
    snmpd -C -c /appfs/etc/snmp/snmpd.conf 1>/dev/null 2>&1 &
    snmpagentd -p 10161 1>/dev/null 2>&1 &
fi
