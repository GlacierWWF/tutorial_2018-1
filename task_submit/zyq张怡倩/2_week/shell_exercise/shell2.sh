#!/bin/bash
mkdir /tmp/scripts
cd /tmp/scripts
cp /etc/pam.d /tmp/scripts
mv /etc/pam.d ./test
chown -R redhat ./test
chmod -R o=--- ./test
