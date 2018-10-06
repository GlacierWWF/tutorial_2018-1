#!/bin/bash

#---------------------------------------
# Homework2: Directory operation
#---------------------------------------
#
#---------------------------------------
# Details.
#---------------------------------------
# @author      HausinLynn
# @email       linhx36@mail2.sysu.edu.cn
# @version     1.0.0.1
# @date        10/01/2018
# @brief       operations for directory
#---------------------------------------


mkdir -v /tmp/scripts		# create directory
cd /tmp/scripts				# enter directory

cp -R /etc/pam.d ./test		# copy

chown -R redhat ./test		# change owner
chmod -R o=--- ./test		# change mode

