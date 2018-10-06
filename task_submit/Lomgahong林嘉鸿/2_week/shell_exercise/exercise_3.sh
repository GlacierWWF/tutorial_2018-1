#!/bin/bash
date
mkdir -v /tmp/lstest
cd /tmp/lstest
echo "正在创建新文件或文件夹"
mkdir a1d b56e 6test
touch xy x2y 732
echo "以下文件或文件夹以a、x或6开头："
ls [ax6]*
echo "以下文件或文件夹以字母开头并且后面跟一个数字："
ls [[:alpha:]][[:digit:]]*
