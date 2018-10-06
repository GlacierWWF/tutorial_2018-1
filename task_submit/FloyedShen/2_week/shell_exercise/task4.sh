data="stu.txt";
sid="学号";
sname="姓名";
ssex="性别";
smajor="专业";
help(){
  echo "不加参数，显示所有记录";
  echo "-a 添加记录";
  echo "-d 删除记录";
  echo "-s 搜索记录";
}
if [ $# -eq 0  ];
then
  printf "%-s\t%-s\t%-s\t%-s\n" $sid $sname $ssex $smajor;
  #cat $data |awk -F ":" '{printf("%-s\t%-s\t%-s\t%-s\n",$1,$2,$3,$4);}';二选一
  cat $data|tr ':' '\t';
  exit;
fi
case $1 in
-a)
  if ! grep -q $2 $data 2>&1;
  then
        echo $2>>$data;
        exit;
  else
        echo "存在";
        printf "%-s\t%-s\t%-s\t%-s\n" $sid $sname $ssex $smajor;
        echo $2|tr ':' '\t';
  fi
;;
-d)
  if ! grep -q $2 $data 2>&1;
  then
        echo "记录不存在。。";
        exit;
  else
        read -p "确定要删除？(y/n)" confirm;
        if [ $confirm == "y" -o $confirm == "yes" ];
        then
                sed -i "/$2/d" $data 2>&1;
        elif [ $confirm == "n" -o $confirm == "no" ];
        then
                echo "用户取消";
        else
                echo "错误的输入";
        fi
  fi
;;
-s)
  if ! grep -q $2 $data 2>&1;
  then
        echo "记录不存在。。";
        exit;
  else
        printf "%-s\t%-s\t%-s\t%-s\n" $sid $sname $ssex $smajor;
        #sed -n "/$2/p" $data |tr ':' '\t';
        grep $2 $data|tr ':' '\t';
  fi
;;
*)
  help
;;
esac