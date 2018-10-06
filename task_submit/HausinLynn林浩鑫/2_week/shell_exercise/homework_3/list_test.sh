#!/bin/bash

#--------------------------------------
# Homework3: List Test
#--------------------------------------
#
#--------------------------------------
# Details.
#--------------------------------------
# @author     HausinLynn
# @email      linhx36@mail2.sysu.edu.cn
# @version    1.0.0.1
# @date       10/01/2018
# @brief      test for list
#--------------------------------------


echo `date`		# date


mkdir -v /tmp/lstest	# create directory
cd /tmp/lstest			# enter directory


mkdir a1d b56e 6test	# create directory
touch xy x2y 732		# create empty file


# list
echo "-------------------------------------------------------"

echo "list of what begin with a,x or 6:"
ls [ax6]*

echo "-------------------------------------------------------"

echo "list of what begin with a letter followed by a number:"
ls [[:alpha:]][[:digit:]]*

echo "-------------------------------------------------------"
