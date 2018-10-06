#!/bin/bash
read a 
read b
var1=`expr $a + $b`
echo "两数之和为 : $var1"
var2=`expr $a - $b`
echo "两数之差为 ：$var2"
var3=`expr $a \* $b`
echo "两数之积为 ：$var3"
var4=`expr $a / $b`
echo "两数之商为 : $var4"
