echo "第一个参数为：$1";
echo "第二个参数为：$2";
val=`expr $1 + $2`
echo "$1 + $2 : $val"

val=`expr $1 - $2`
echo "$1 - $2 : $val"

val=`expr $1 \* $2`
echo "$1 * $2 : $val"

val=`expr $2 / $1`
echo "$2 / $1 : $val"
