#!/bin/bash

#----------------------------------------------------
#homework_3
#
#---------------------------------------------------
# @author   JackkiiChen
# @email    chenjq66@mail2.sysu.edu.cn
# @version  1.0.0
# @date     2018/10/06
# @brief    list of directories and documents
#
#----------------------------------------------------

#date
date

#create directory
mkdir -v /tmp/lstest

#enter
cd /tmp/lstest

#create directory
mkdir a1d b56e 6test

#create file
touch xy x2y 732

#list what begin with a,x or 6
ls [ax6]*

#list what begin with a number after an alpha
ls [[:alpha:]][[:digit:]]*
