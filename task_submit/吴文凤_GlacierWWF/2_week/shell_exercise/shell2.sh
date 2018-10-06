#!/bin/bash
mkdir -v /tmp/scripts
cd /tmp/scripts
cp -r /etc/pam.d ./test
chown -R radhat ./test
chmod -R o=- ./test
