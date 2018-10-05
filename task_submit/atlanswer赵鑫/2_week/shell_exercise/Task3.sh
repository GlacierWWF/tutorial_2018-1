#! /bin/bash
#Show time
date
#Create directory and switch
#-p, --parents      no error if existing, make parent directories as needed
mkdir -p /tmp/lstest
cd /tmp/lstest
mkdir -p a1d b56e 6test
#Create empty files
> xy
> x2y
> 732
#List directory contents, using regular expressions
ls [ax6]*
ls [[:alpha:]][[:digit:]]*