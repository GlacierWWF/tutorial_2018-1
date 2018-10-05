#! /bin/bash
expt=2
echo "List parameter(s): $*."
echo "The number of parameter(s) passed to this script: $#."
if [ $# != ${expt} ]
then
    echo "Expected: ${expt}, number incorrect!"
    exit 1
fi
#Addition
result=`expr $1 + $2`
echo "$1 + $2 = ${result}"
#Subtraction
result=`expr $1 - $2`
echo "$1 - $2 = ${result}"
#Multiplication
result=`expr $1 \* $2`
echo "$1 * $2 = ${result}"
#Division, and exit if $2 is zero
result=`expr $1 / $2` || exit 1
echo "$1 / $2 = ${result}"