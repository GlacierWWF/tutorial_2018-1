#!/bin/bash
date #显示当前系统日期和时间
mkdir /tmp/lstest
cd /tmp/lstest
mkdir a1d b56e 6test
touch xy x2y 732
ls -d  [a6x]* #*表示匹配任何长度的任意字符
ls -d  [[:alpha:]][[:digit:]]* #以字母开头，后跟一个任意数字，而后跟任意长度字符的文件或目录
