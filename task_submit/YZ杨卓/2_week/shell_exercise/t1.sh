#!/bin/bash

val1=`expr $1 + $2`
val2=`expr $1 - $2`
val3=`expr $1 \* $2`
val4=`expr $1 / $2`
echo "$1 + $2 =  $val1"
echo "$1 - $2 =  $val2"
echo "$1 * $2 =  $val3"
echo "$1 / $2 =  $val4"

