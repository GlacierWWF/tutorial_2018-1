#!/bin/bash
date
mkdir -v /tmp/lstest
cd /tmp/lstest
mkdir a1d b56e 6test
touch xy x2y 732
ls -al|grep a*
ls -al|grep x*
ls -al|grep 6*
ls [[:alpha:]][[:digit:]]* 
