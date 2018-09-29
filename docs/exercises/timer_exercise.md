## OpenCV计时工具具体任务说明
**编写一个简易可视化计时工具。**

### 这个project重点需要预备队员掌握以下内容：
- 1、多线程编程。
- 2、makefile多文件编译以及如何链接一个库。
- 3、一点点关于OpenCV的知识。

### 具体要求：  
- 1、编写一个Timer类，至少包含以下函数：  
	1）open() //打开窗口。窗口显示一幅欢迎图片。    
	2）startTiming() //开始计时。窗口出现秒钟计时显示，终端也同时输出秒数。（图片窗口计秒数保留至小数点一位，终端计时秒数每秒更新一次。）  
	3）stopTiming() //结束计时。窗口恢复欢迎图片。  
	4）close() //关闭窗口。    
	5）pause() //暂停计时，窗口保持不变。（发挥部分）  
	6）resume() //从原来秒数继续计时。（发挥部分）  
    - PS：要求类的声明与定义分文件编写，即.h文件中声明，.cpp中定义。  
	- PS：计时请使用STL的Chrono类。  

- 2、在main函数中使用Timer类，并且在调用open()函数之后开始接收用户的终端输入。当用户输入`start`时调用startTiming开始计时，输入`stop`时调用stopTiming结束计时。输入`quit`退出。输入`pause`暂停，输入`resume`继续。窗口和终端示例效果可以参考[示例图1](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week2_example1.jpg)和[示例图2](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week2_example2.jpg)，仅供参考。  
	- PS：要实现同时处理输入和输出须使用多线程。  

- 3、多线程编程方面，你可以使用pthread库，也可以使用std::thread，此工程没有强制要求，但希望你二者都了解。  

- 4、编写makefile编译你的项目。  
    - PS：注意在编译时用恰当的方法引用所用到的库，否则会在链接时出现"undefined reference"错误。  
   

