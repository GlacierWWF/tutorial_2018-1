#无法直接通过./shell2.sh来执行，需逐句在命令行中执行
#添加sudo以获得权限
sudo mkdir -p /tem/scripts
sudo cd /tem/scripts
sudo cp -r /etc/pam.d ./test
cat /etc/passwd|grep -v nologin|grep -v halt|grep -v shutdown|awk -F":" '{ print $1"|"$3"|"$4 }'|more #获取简略的用户列表
chown -R your_user_name ./test #将your_user_name替换成其中上一命令结果中的一个用户名
chmod -R o=--- ./test
