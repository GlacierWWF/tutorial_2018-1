在cmd里面cd到文件夹目录下
使用notepad filename.cpp  创建一个filename的cpp文件【用记事本打开】
使用g++ -E filename.cpp -o filename.i   生成filename.i
使用g++ -S filename.i -o filename.s    生成filename.s
使用g++ -c filename.s -o filename.o   生成filename.o
使用g++ -filename.o -o filename.exe  生成exe文件
输入：filename.exe  运行filename.exe文件
【可以直接创建cpp文件后直接g++ filename.cpp -o filename生成exe文件，再输入：filename.exe】
这样就可以再cmd里面直接编译程序。