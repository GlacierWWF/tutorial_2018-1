## Shell练习题报告
- **作者**: 冯颖雯 （fengyw8）
- **修订**: 冯颖雯 （fengyw8）
- **版本**: 1.0.0
- **日期**: 2018-10-6
- **摘要**:Shell练习题的作业报告

---

### 作业一

**代码**：
```bash
#!/bin/bash
read -p "please enter two integers (non-zero):" a b
echo "the integers are ${a} and ${b}"
echo "a+b= `expr $a + $b`"
echo "a-b= `expr $a - $b`"
echo "a*b= `expr $a \* $b`"
echo "a/b= `expr $a / $b`"
```
**如何运行**：
- 终端切换到shell1.sh文件所在目录
- 输入 `bash chmod +x shell1.sh` （给予shell1.sh执行的权限） 
- 输入 `./shell1.sh` （执行该文件）
- 终端输出提示字符后输入两个非零整数（这里用10 20）（用空格隔开）

**输出**：
```bash
>>> chmod +x shell1.sh
>>> ./shell1.sh
please enter two integers (non-zero):
>>>10 20
the integers are 10 and 20
a+b= 30
a-b= -10
a*b= 200
a/b= 0
```

---

### 作业二
**代码**：
```bash
# 无法直接通过./shell2.sh来执行，需逐句在命令行中执行
# 添加sudo以获得权限
# 本人电脑中无redhat用户，故以其他用户替代
sudo mkdir -p /tem/scripts
sudo cd /tem/scripts
sudo cp -r /etc/pam.d ./test
cat /etc/passwd|grep -v nologin|grep -v halt|grep -v shutdown|awk -F":" '{ print $1"|"$3"|"$4 }'|more #获取简略的用户列表
chown -R your_user_name ./test #将your_user_name替换成其中上一命令结果中的一个用户名
chmod -R o=--- ./test
```

**如何运行**：
- 在终端中（任何目录下均可）逐句输入 
```bash
  sudo mkdir -p /tem/scripts
  sudo cd /tem/scripts
  sudo cp -r /etc/pam.d ./test
```
- 获取简略的用户列表，终端输入 `bash cat /etc/passwd|grep -v nologin|grep -v halt|grep -v shutdown|awk -F":" '{ print $1"|"$3"|"$4 }'|more `
- 输入 `bash chown -R your_user_name ./test` (将your_user_name替换成其中上一命令结果中的一个用户名)
- 输入`bash chmod -R o=--- ./test`

**输出示例**：
```bash
>>> sudo mkdir -p /tem/scripts
>>> sudo cd /tem/scripts
>>> sudo cp -r /etc/pam.d ./test
>>> cat /etc/passwd|grep -v nologin|grep -v halt|grep -v shutdown|awk -F":" '{ print $1"|"$3"|"$4 }'|more
root|0|0
sync|4|65534
speech-dispatcher|111|29
whoopsie|112|117
hplip|118|7
gnome-initial-setup|120|65534
gdm|121|125
yvette|1000|1000
>>> chown -R yvette ./test
>>> chmod -R o=--- ./test
```

---

### 作业三

**代码**：
```bash
#无法直接通过./shell3.sh来执行，需在命令行逐句输入以下命令以执行
#sudo用于获取权限
date
sudo mkdir /tem/lstest
sudo cd /tmp/lstest
sudo mkdir a1d b56e 6test
sudotouch xy x2y 732
ls [ax6]*
ls [[:alpha:][:digit:]]*
```
**如何运行**：
- 在终端逐句输入 
```bash
 date
 sudo mkdir /tem/lstest
 sudo cd /tmp/lstest
 sudo mkdir a1d b56e 6test
 sudo touch xy x2y 732
 ls [ax6]*
 ls [[:alpha:][:digit:]]*
```

**输出示例**：
```bash
>>> date
Sat Oct  6 18:28:55 CST 2018
>>> sudo mkdir /tem/lstest
>>> sudo cd /tmp/lstest
>>> sudo mkdir a1d b56e 6test
>>> sudo touch xy x2y 732
>>> ls [ax6]*
x2y xy
6test
ald:
>>> ls [[:alpha:][:digit:]]*
732 x2y xy
6test:
ald:
b56e:
```
