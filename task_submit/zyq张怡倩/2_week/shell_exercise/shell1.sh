#!/bin/bash
$1
$2
add=`expr $1 + $2`
minus=`expr $1 + $2`
mul=`expr $1 \* $2`
chu=`expr $1 / $2`

echo "$1 + $2 = $add"
echo "$1 - $2 = $minus"
echo "$1 * $2 = $mul"
echo "$1 / $2 = $chu"
