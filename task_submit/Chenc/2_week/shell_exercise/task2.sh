#!/bin/bash
mkdir tmp
cd tmp
mkdir scripts
cd scripts
cp -r /etc/pam.d ./test
chown -R redhat ./test
chmod -R o=--- ./test
