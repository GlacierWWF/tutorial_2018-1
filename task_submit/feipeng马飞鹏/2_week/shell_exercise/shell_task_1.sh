#!/bin/bash

#--------------------------------------------------------------
#
# Shell 练习题 作业一
#
# 该脚本接收两个整数，然后计算并显示两个整数的和，差，积，商
#
# @author:    马飞鹏
# @email:     767102280@qq.com
# @version:   1.0.0
# @date:      2018/10/01
#---------------------------------------------------------------

addition=`expr $1 + $2`
subtraction=`expr $1 - $2`
multiplication=`expr $1 \* $2`
division=`expr $1 / $2`
echo "两数之和为${addition}"
echo "两数之差为${subtraction}"
echo "两数之积为${multiplication}"
echo "两数之商为${division}"

