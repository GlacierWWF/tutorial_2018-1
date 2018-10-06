#!/bin/bash
read -p "please enter two integers (non-zero):" a b
echo "the integers are ${a} and ${b}"
echo "a+b= `expr $a + $b`"
echo "a-b= `expr $a - $b`"
echo "a*b= `expr $a \* $b`"
echo "a/b= `expr $a / $b`"
