#!/bin/bash

#---------------------------------------------------------------------------
#
# Shell 练习题 选做题
#
#题目要求：有文本文件stu.txt,该文件是所有学生的信息，每个学生存储一行信息，信息格式如下：学号:姓名:性别:专业 如(100:张三:男:计算机)设计一个shell，名称为stu.sh,该shell完成如下功能:
#
#    1、当输入stu.sh时，列出所有记录内容
#    2、当输入stu.sh -a 100:张三:男:计算机 时，首先判断100记录是否存在，如果不存在，则把该信息写入文件，如果存在，则给出提示，并输出文件中学号为100的该行信息
#    3、当输入stu.sh -d 100时，首先判断100记录是否存在，如果不存在，给出提示，如果存在，则提示用户确认是否要删除记录，如用户输入y或者yes，则删除文件中学号为100的该行信息，如果用户输入n或no时，则不做删除操作
#    4、当输入stu.sh -s 100时，首先判断100记录是否存在，如果不存在，给出提示，如果存在，则输出文件中学号为100的该行信息
#    5、当用户输入的选项不正确时，给出错误提示，并输入该shell的用法
#
#文本stu.txt内容为：
#100:张三:男:计算机
#101:张红:女:文秘
#102:张飞:男:体育
#103:张婷:女:英语
#104:张海洋:男:机电
#
# @author:    马飞鹏
# @email:     767102280@qq.com
# @version:   1.0.0
# @date:      2018/10/02
#----------------------------------------------------------------------------

if [ $# -eq 0 ];
then
	cat stu.txt 
	exit
fi
if [[ $1 == -a ]];
then 
	if ! grep -q $2 stu.txt	
	then 
		echo $2>>stu.txt
		exit
	else
		echo "该学生信息已存在"
		echo $2
		exit
	fi
elif [[ $1 == -d ]]
then
	if ! grep -q $2 stu.txt
	then 
		echo "该学生信息不存在，无法删除"
		exit
	else
		read -p "是否确定要删除该条信息[y/n]" input
		if [ $input == 'y' -o $input == 'yes' ]
		then
			sed -i "/$2/d" stu.txt
			echo "删除成功"
		elif [ $input == 'n' -o $input == 'no' ]
		then
			echo "取消删除"
			exit
		else
			echo "输入错误"
		fi
	fi
elif [[ $1 == -s ]]
then
	if ! grep -q $2 stu.txt
	then
		echo "该学生信息不存在"
		exit
	else
		grep $2 stu.txt
	fi
else
	echo "-a 学号:姓名:性别:专业  添加学生信息"
	echo "-d 学号		      删除该学号对应的学生信息"
	echo "-s 学号		      寻找该学号对应的学生信息并输出"

fi
