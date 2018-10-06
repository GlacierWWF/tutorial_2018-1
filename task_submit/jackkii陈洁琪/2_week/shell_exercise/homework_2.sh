#!/bin/bash

#-------------------------------------------
#homework_2
#
#--------------------------------------------
# @author      JackkiiChen
# @email       chenjq66@mail2.sysu.edu.cn
# @version     1.0.0
# @date        2018/10/06
# @brief       Directory operation


#create /tmp/scripts directory
mkdir -v /tmp/scripts

#enter 
cd /tmp/scripts

#copy and rename
cp -r /etc/pam.d ./test

#change master
chown -R redhat ./test

#change permission
chmod -R o=--- ./test
