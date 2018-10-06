#!/bin/bash
echo "第一个数字 $1"
echo "第二个数字 $2"
echo "$(($1+$2))"
echo "$[$1-$2]"
echo "$[$1*$2]"
echo "$[$1/$2]"

