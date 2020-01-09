#!/bin/bash
#for admin add
echo $1
echo $2
if [ -d $2 ];then
    cat /etc/passwd | grep -w $1
    #Avoid Fallback version Errors
    if [  $? == 1 ];then
        useradd $1 -g $1
        echo $1 | passwd $1 --stdin >/dev/null 2>&1
        chown -R $1 $2
    fi
else
    cat /etc/passwd | grep -w $1
    if [  $? == 1 ];then
    useradd $1
    echo $1 | passwd $1 --stdin >/dev/null 2>&1
    mkdir /home/$1/.ssh
    chown $1 /home/$1/.ssh
    chgrp $1 /home/$1/.ssh
    chmod 700 /home/$1/.ssh
    touch /home/$1/.ssh/authorized_keys
    chown $1 /home/$1/.ssh/authorized_keys
    chgrp $1 /home/$1/.ssh/authorized_keys
    chmod 600 /home/$1/.ssh/authorized_keys
    fi
fi