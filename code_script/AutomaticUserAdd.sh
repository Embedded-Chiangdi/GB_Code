#!/bin/bash
cat /etc/passwd | grep -w 'admin'
if [  $? == 1 ];then
useradd admin
echo "admin" | passwd admin --stdin >/dev/null 2>&1
mkdir /home/admin/.ssh
chown admin /home/admin/.ssh
chgrp admin /home/admin/.ssh
chmod 700 /home/admin/.ssh
touch /home/admin/.ssh/authorized_keys
chown admin /home/admin/.ssh/authorized_keys
chgrp admin /home/admin/.ssh/authorized_keys
chmod 600 /home/admin/.ssh/authorized_keys
echo "admin   ALL=(ALL)       NOPASSWD:ALL" >> /etc/sudoers
fi
cat /etc/passwd | grep -w 'wifiadmin'
if [  $? == 1 ];then
useradd admin
echo "wifiadmin" | passwd wifiadmin--stdin >/dev/null 2>&1
mkdir /home/wifiadmin/.ssh
chown admin /home/wifiadmin/.ssh
chgrp admin /home/wifiadmin/.ssh
chmod 700 /home/wifiadmin/.ssh
touch /home/wifiadmin/.ssh/authorized_keys
chown admin /home/wifiadmin/.ssh/authorized_keys
chgrp admin /home/wifiadmin/.ssh/authorized_keys
chmod 600 /home/wifiadmin/.ssh/authorized_keys
echo "wifiadmin   ALL=(ALL)       NOPASSWD:ALL" >> /etc/sudoers
fi

