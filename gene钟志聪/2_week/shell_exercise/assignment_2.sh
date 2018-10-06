mkdir -p /tmp/scripts
cd /tmp/scripts
cp -rf /etc/profile.d /tmp/scripts
mv /tmp/scripts/profile.d /tmp/scripts/test
chown redhat /tmp/scripts/test -R
chmod -R 770 /tmp/scripts/test
