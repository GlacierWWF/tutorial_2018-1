#!/bin/bash
mkdir /tmp/scripts #创建/tmp/scripts目录
cd /tmp/scripts #切换到/tmp/scripts目录
cp -r /etc/pam.d /tmp/scripts/test #复制/etc/pam.d目录至当前目录,并改名为test
chown -R redhat ./test #修改test及它的下级目录和所有文件的属到redhat
chmod -R o=-r-w-x ./test #将test及其子目录中的文件的其它用户的权限改为没有任何权限
