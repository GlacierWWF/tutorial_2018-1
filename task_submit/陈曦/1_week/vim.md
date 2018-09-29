## vim常用操作
vim默认进入normal mode，在此模式下可输入命令
按i进入insert mode，并从光标左侧开始输入
按a同样进入insert mode, 但从光标右侧开始输入
按o进入insert mode并插入一个空行
Esc 退出insert mode， 回到normal mode
#### 光标操作
使用hjkl控制光标，h--← j--↓ k--↑ l--→
0 移动光标到行首
$ 移动光标到行末
#### 删除操作
按x删除当前字符
按dd删除整行
数字+dd删除多行 例：3dd 删除3行
### 重复操作
. 重复上一次操作
命令前加数字 重复多次命令
### command mode
输入冒号":"进入command mode,:后加命令
:w write
:q quite
:q! 退出不保存
:e <file> 打开文件
### 其他常用操作
p paste
u undo


