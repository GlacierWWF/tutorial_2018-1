#include<iostream>
int main()
{
	std::cout<<"Hello World!"<<std::endl;
	return 0;
}
/*   
g++编译过程： 
vim test.cpp            创建打开一个.cpp文件
a                       插入编辑
Esc                     退出编辑 
:wq                    保存并退出
g++ test.cpp -o test    编译test.cpp文件并生成test可执行文件
./test                  输出结果 
*/ 
