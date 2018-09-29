在cmd里面cd到文件夹目录下

使用g++ -E hello.cpp -o hello.i   生成hello.i
使用g++ -S hello.i -o hello.s    生成hello.s
使用g++ -c hello.s -o hello.o   生成hello.o
使用g++ -hello.o -o hello.exe  生成exe文件
输入：fhello.exe  运行hello.exe文件
【可以直接使用g++ hello.cpp -o hello生成exe文件，再输入：hello.exe】
这样就可以再cmd里面直接编译程序。