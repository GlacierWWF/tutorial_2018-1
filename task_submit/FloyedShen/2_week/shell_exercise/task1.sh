#!/bin/bash
echo "x $1"
echo "y $2"
echo " $(($1+$2))"      （和）
echo "$[$1-$2]"         （差）
echo "$[$1*$2]"         （积）
echo "$[$1/$2]"         （商）