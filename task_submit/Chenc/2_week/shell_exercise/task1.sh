#!/bin/bash
echo -e "\e[1;31mNumber one is $1\e[0m"
echo -e "\e[1;31mNumber two is $2\e[0m"
echo "Sum = $(($1+$2))"
echo "Difference = $(($1-$2))"
echo "Product = $[$1*$2]"
echo "Quotient = $[$1/$2]"
