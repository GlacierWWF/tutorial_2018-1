#!/bin/bash

#---------------------------------------------------------------------------
#
# Shell 练习题 作业二
#
#
# 该脚本         创建目录/tmp/scripts
#		 切换到此目录
#		 复制 /etc/pam.d目录到当前目录，重命名为test
#                将当前目录的test及其里面的文件和子目录的属主改为redhat
#                将test及其子目录中的文件的其他用户的权限改为没有任何权限
#
#
# @author:    马飞鹏
# @email:     767102280@qq.com
# @version:   1.0.0
# @date:      2018/10/01
#----------------------------------------------------------------------------

mkdir /tmp/scripts
cd /tmp/scripts
cp -r /etc/pam.d ./test
#若用户redhat不存在，需要先创建一个用户
chown -R redhat ./test
chmod -R o=--- ./test
