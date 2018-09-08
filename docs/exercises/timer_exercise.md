## 计时工具具体任务说明
**编写一个简易计时工具。**

### 这个project重点需要预备队员掌握以下内容：
- 1、多线程编程。
- 2、makefile多文件编译以及如何链接一个库。
- 3、读写锁。

### 具体要求：  
- 1、编写一个Timer类，至少包含以下函数：  
	1）open() //打开窗口。终端显示欢迎信息(在你输入行的下一行,用户回车,输入行清空,终端不滚动)。  
	2）startTiming() //开始计时。终端刷新秒数(在同一行写,不可换行)。  
	3）stopTiming() //结束计时。终端恢复欢迎信息。  
	4）close() //关闭窗口。  
	5）pause() //暂停计时，终端保持不变。（发挥部分）  
	6）resume() //从原来秒数继续计时。（发挥部分）  
    - PS：要求类的声明与定义分文件编写，即.h文件中声明，.cpp中定义  


//TODO:修改题目，没改完

用STL的Chrono类和pthread写一个多线程的简易计时工具Timer, Timer类声明放在Time.h下, Timer类定义放在Time.cpp下，main.cpp中使用Timer类,    
编写一个C++程序，一个简易读写锁。在main.cpp中启动四个线程同时计时，每1s记录一次过去的时间，放在一个全局的STL容器list中，然后另外启动一个线程从list中取出其余四个线程输出的时间, 并打印 `Thread X: xxx seconds elapsed.` 。为了保证线程安全，你需要使用你所编写的读写锁保护这个list。你可以选择一种读写锁来编写：读者优先、写者优先、公平竞争。



- 2、在main函数中使用这个类，并且在调用open()函数之后开始接收用户的终端输入。当用户输入`start`时调用startTiming开始计时，输入`stop`时调用stopTiming结束计时。输入`quit`退出。输入`pause`暂停，输入`resume`继续。窗口和终端示例效果可以参考[示例图1](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week2_example1.jpg)和[示例图2](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week2_example2.jpg)。  
    - PS：要实现同时处理终端输入和终端输出须使用多线程。  


- 3、编写makefile编译你的项目。  
    - PS：注意在编译时用恰当的方法引用所用到的pthread库，否则会在链接时出现"undefined referrence"错误。  
   
- 4、有关读写锁 (read write lock)
    - 网上有很多很多信息可以参考，这里不再提及。另外建议使用英文搜索，国内的很多博客都是复制粘贴的信息，不知所云。 

