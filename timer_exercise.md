## OpenCV计时工具具体任务说明
**编写一个简易可视化计时工具。**

### 这个project重点需要预备队员掌握以下内容：
- 1、多线程编程。
- 2、makefile多文件编译以及如何链接一个库。
- 3、一点点关于OpenCV的知识。

### 具体要求：  
- 1、编写一个Timer类，至少包含以下函数：  
	1）open() //打开窗口。窗口显示一幅欢迎图片。  
	2）startTiming() //开始计时。窗口出现秒钟计时显示，每秒更新一次。终端同时输出秒数。
	3）stopTiming() //结束计时。窗口恢复欢迎图片。
	4）close() //关闭窗口。  
	5）pause() //暂停计时，窗口保持不变。（发挥部分）
	6）resume() //从原来秒数继续计时。（发挥部分）
    - PS：要求类的声明与定义分文件编写，即.h文件中声明，.cpp中定义  
</br>
</br>
- 2、在main函数中使用这个类，并且在调用open()函数之后开始接收用户的终端输入。当用户输入start时调用startTiming开始计时，输入stop时调用stopTiming结束计时。输入quit退出。输入pause暂停，输入resume继续。窗口和终端的示例效果可以参考[图片1](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week2_sample1.jpg)和[图片2](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week2_sample2.jpg)。
   - PS：要实现同时处理终端输入和图像输出需要用到多线程。  
</br>
</br>
- 3、编写makefile编译你的项目。  
   - PS：注意在编译时用恰当的方法引用所用到的opencv库，否则会在链接时出现"undefined referrence"错误。  
