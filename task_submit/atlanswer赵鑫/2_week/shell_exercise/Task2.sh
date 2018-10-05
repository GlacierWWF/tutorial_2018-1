#! /bin/bash
#Create a directory and switch
#-p, --parents      no error if existing, make parent directories as needed
mkdir -p /tmp/scripts
cd /tmp/scripts
#Copy file
#-r     copy recursively, non-directories as files
cp -r /etc/pam.d ./test
#Change owner
#-R, --recursive    Recursively change ownership of directories and their contents.
chown -R redhat ./test
#Change access permissions
#-R, --recursive    change files and directories recursively
chmod -R o-o ./test