#!/bin/bash

#-----------------------------------------------------
#homework_1
#
#-----------------------------------------------------
# @author      JackkiiChen
# @email       chenjq66@mail2.sysu.edu.cn
# @version     1.0.0 
# @date        2018/10/06
# @brief       sum,minus,multply,divide of two numbers
#------------------------------------------------------


#sum of the two numbers
echo "$1+$2=`expr $1 + $2`"

#minus
echo "$1-$2=`expr $1 - $2`"

#multiply
echo "$1*$2=`expr $1 \* $2`"

#divide
echo "$1/$2=`expr $1 / $2`"
