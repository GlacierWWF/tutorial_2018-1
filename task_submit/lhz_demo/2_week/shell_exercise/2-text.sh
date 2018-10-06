#!/bin/sh
       
		mkdir -v /tmp/scripts
		cd /tmp/scripts
		cp -r /etc/pam.d ./test
		chown -R lhz ./test
		chmod -R o=--- ./test
