## 项目考核题目

**欢迎来到项目考核。项目考核有多个可选方向供你选择，你可以选择其中一个方向进行专攻。**  

#### 项目方向  
- [编程技术方向](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/docs/exercises/projects.md#编程技术方向)
- [图像处理方向](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/docs/exercises/projects.md#图像处理方向)
- [性能优化方向](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/docs/exercises/projects.md#性能优化方向)
- [嵌入式与控制方向](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/docs/exercises/projects.md#嵌入式与控制方向)
- [导航与编队方向](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/docs/exercises/projects.md#导航与编队方向)  

#### 注意事项  
你有四周的时间完成你所选择的方向。**第五周周一（10.22）** 就可以开始提交，截止提交时间为**第七周结束（11.9 23:00）**。各方向都有难度很大的项目，发挥部分可以选做，在保证工程质量的基础上尽量多完成即可。  

Project根据具体要求，需要提交工程代码或者技术报告。  
对于**技术报告**，请使用Word或PDF格式撰写。  
对于**工程代码**，每一个工程需要有适当的演示（demo），可以选择**程序运行截图**（三张图以上），也可以选择**演示视频**（为方便下载，单个视频文件大小请压缩至50MB以下），工程还需要配有README文件。  


- - - - - -  

## 编程技术方向
**注意：大二同学选择此方向，项目考核积分将乘0.7倍的因子。大三和大四同学不能选择此方向。**

### 一、学习C++、STL、数据结构

#### Content

- 学习指针、类、结构体。
- 学习STL的使用方法，学习模版，重载，类
- 学习基本的数据结构。
- 学习模版。

#### Project

*（分数占比30%）*  
- 1、使用STL分别实现下列简单工程。
  - 完成一个栈的操作。
  - 完成一个队列的操作。
  - 完成一个二叉树的操作。
  - 利用vector进行选择排序。
  - 用list进行归并排序。
  - 使用map，并按照Key排序。
- 2、写一个矩阵运算的类（加，减，数乘，点乘，叉积，转置，行访问，列访问，初始化Zero matrix和Identity matrix，深复制）。
- 3、写一个模版类型的排序函数，并且在检测到输入类型有iterator时用iterator进行排序，否则对原始C数组进行排序，对于`vector<string>`类型按字典母ASCII和的升序进行排序。同时支持用户提供的比较函数，即模版自己提供一个前面规则的Comparator。  


### 二、学习Python语言和numpy模块，学习Python和C/C++通信方式的使用

#### Content

- 学习UDP和TCP协议。
- 熟练使用Python，学会使用相关模块。
    - 参考教程：[菜鸟Python基础教程](http://www.runoob.com/python/python-tutorial.html)、[廖雪峰的Python教程](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000)。
- 了解数据库的基本使用。

#### Project

*（分数占比70%）*  
- 1、利用UDP/TCP协议，实现一个至少有3个人的简易聊天室功能（类似于QQ群）。
- 2、使用Python，实现A*寻路算法，并输出可视化结果。  
- 3、使用Python，利用pyaudio、wave等模块，实现一个可以语音播放和录制的小程序。
- 4、使用Python，利用numpy等模块，复现第三周的数码管数字识别工程。

- 5、（发挥部分）使用Python完成一个简单的数据库。Python仅作为封装层，数据库内核使用C++实现。Python仅仅将命令用regex处理后再将格式化好的数据传递给C++，数据库要保存信息，要求支持一些简单的命令行交互（schema, insert, sort, search, delete, 操作对象是有多个时要询问用户）。  
    - 语法如下：
    ```C++
        SimpleDB >> schema(“name”:string, “age”:int, “income”:double)
        // 设置数据库的存储格式
        SimpleDB >> insert(“ZhangSan”, 16, 0.0)
        SimpleDB >> sort(“name”)
        //按”name”属性进行字典升序排序
        SimpleDB >> search(“ZhangSan” in “name”)
        SimpleDB >> search(“ZhanSan”)
        //in表示指定属性，否则全局查找
        SimpleDB >> delete(“name” is “ZhangSan”)
        //is表示等于
        SimpleDB >> exit
    ```


- - - - - -  

## 图像处理方向

#### Content

- 学习图像处理的相关算法。
- 查找文献，阅读SIFT算法原理，实现SIFT算法。
- 阅读各种光流算法的资料，深入了解SAD光流算法，阅读px4flow开源的光流算法。
- 入门Python语言。
- 了解神经网络和深度学习。
- 学习深度学习框架，包括keras和TensorFlow。
- 学习使用libSVM库。
- 熟悉CNN原理，利用TensorFlow编写神经网络。
- 了解静态手势识别和动态手势识别原理。
    - 参考资源：[廖雪峰的Python教程](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000)、[CS231n](http://cs231n.stanford.edu/)、[TensorFlow中文社区](http://www.tensorfly.cn/)、[MOOC《人工智能实践》](https://www.icourse163.org/course/PKU-1002536002)。  

#### Project
*（分数占比30%, 20%, 50%）*  
**注意，1-1和1-2两个题目二选一。**  

- 1-1、利用keras和LibSVM，然后完成一个简单的神经网络或分类器来对图像进行十分类，与SVM进行对比测试。数据集需采用[MNIST](http://yann.lecun.com/exdb/mnist/)或者[CIFAR-10](http://www.cs.toronto.edu/~kriz/cifar.html)。

- 1-2、完成以下工程。输入两张图片，输出两张图片对应的SIFT特征点的的坐标，尺度和方向，并且能够实现两张图片的特征点匹配。根据SIFT算法原理实现它，且不能调用OpenCV自带的用于计算SIFT特征点的函数。[示例图](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/project_example1.jpg)。  

- 2、使用C++完成简单光流算法项目，实现以下功能。
    - 使用videocapture读取笔记本摄像头数据。
    - 对图像进行一定的预处理。
    - 参照px4flow的代码进行光流计算。
    - 输出视频的平均像素位移。

- 3、使用TensorFlow构造基于CNN的静态手势识别系统。
    - 要求利用多线程技术使用摄像头进行实时捕捉和实时输出，而且保证在桌面型CPU上可以达到尽量高（如15fps）的实时识别速度。
    - 要求至少有六种不同的手势（如012345）。尽可能提高手势识别的准确率。
    - 你可以使用CPU内置的GPU进行加速。
    - 请自己寻找或者制作合适的数据集来源。
    - 此外，请撰写一份技术报告，阐述你的手势识别系统，并思考在比赛中怎么恰当地使用手势识别系统。



- - - - - -  

## 性能优化方向

### 一、学习计算机的组成架构和操作系统的基本原理

#### Content

- 学习什么是计算机的内存模型，处理器是如何执行指令的。
- 学习什么是并行，并发，以及多线程，多进程。进程在计算机中是如何表现的，线程在计算机中是如何表现的。
- 操作系统是如何加载程序的。程序是如何链接的。什么是动态链接和静态链接。ld是如何动态加载库的。
    - 参考资源：《计算机组成与设计：硬件/软件接口》、《操作系统原理》、bilibili上的视频教程。

#### Project

*（分数占比30%）*  
- 1、将Content中的所有问题整理写成一份详尽的技术报告。
- 2、了解读者与写者问题，使用pthread实现简单的读写锁（至少两种）。
- 3、使用boost_interprocess或shm实现进程间的数据交换，A进程用opencv读取一个Mat（或者用CImage库），然后B进程把它转置并缩放后再写入文件。进一步，我们可以加一个控制进程C，C读取用户的指令，然后操纵A读取文件，操纵B进行数据操作，操作功能用protobuf进行serialization。请完成两步。
- 4、请使用objdump导出.o文件的符号列表并详细解释每个参数栏的含义。


### 二、学习程序优化与并行化计算

#### Content

- 1、高性能程序优化，使用循环分块，展开等等技巧，学会使用vtune或perf来优化程序。
- 2、学会使用SIMD指令并行化高斯模糊，并和OpenCV的内置高斯模糊函数进行比较。
- 3、学习使用OpenMP并行化程序，测试矩阵乘法的性能，再使用vtune或perf进行分析并再次优化。
- 4、学习使用OpenCL或CUDA（如果有N卡最好使用CUDA）。
    - 推荐资源：《并行程序设计导论》。

#### Project

*（分数占比70%）*  
- 1、将Content中的所有内容整理写成一份详尽的技术报告。
- 2、实现一个核大小为13x13，图片分辨率为4000x4000的串行高斯模糊程序，然后进行并行优化，对比前后两种方式的差异。
- 3、使用串行方式实现一个1000x1000大小的矩阵的50次幂，然后使用并行化的方法优化，对比前后两种方式的差异。
- 4、利用OpenCL或CUDA，完成一个树形累加的计算程序。


- - - - - -  

## 嵌入式与控制方向
**选择此方向需要自己提前准备材料，包括Arduino或STM32核心板、四位数码管模块、MPU6050传感器模块、USB-TTL转接模块、激光发射模块、激光接收模块、其它电子元件等。**  

#### Content

- 学习单片机的原理与应用。
    - 建议没有单片机基础的同学学习Arduino，比较容易入门。
    - 参考资源：[Arduino中文社区](https://www.arduino.cn/)、[STM32官方参考手册和数据手册](https://www.stmcu.com.cn/Designresource/design_list/cat_code/document/pro_cat/STM32/is_first/1)、[正点原子的《STM32开发指南》电子书](http://www.stmcu.org/module/forum/forum.php?mod=viewthread&tid=615919)、bilibili上的入门教程。
- 学习 Arduino / STM32 基础编程，安装 Arduino IDE / Keil5。（可在Windows上玩）
- 掌握单片机系统架构，学习GPIO、中断、定时器、PWM、串口通信、ADC、I2C通信、SPI通信的原理与应用。（如果对单片机还不熟悉，推荐按照这个顺序学习。）
- 学习使用外设，如LED灯、按键、数码管、激光发射器、激光接收器、MPU6050六轴传感器等。学会查阅芯片数据手册。
- 学习STM32单片机的需要了解标准库。
- 了解四元数和欧拉角，阅读[《Quadrotor Dynamics and Control》](http://scholarsarchive.byu.edu/cgi/viewcontent.cgi?article=2324&context=facpub&sei-redir=1&referer=http%3A%2F%2Fcn.bing.com%2Fsearch%3Fq%3Dquadrotor%2Bdynamics%2Band%2Bcontrol%26qs%3DAS%26pq%3Dquadrotor%2Bdynamics%2Band%2Bc%26sc%3D2-24%26cvid%3D87AAD3B1893942708BA5918528A944E3%26FORM%3DQBRE%26sp%3D1#search=%22quadrotor%20dynamics%20control%22) 论文第一章。
- 阅读[libserial文档](https://github.com/crayzeewulf/libserial)，学习如何使用串口库读取串口传感器的数据。
- 学习卡尔曼滤波。  
    - 推荐资料：[《Probabilistic Robotics》](http://www.probabilistic-robotics.org/)、《多传感器最优估计理论及其应用》、["How a Kalman filter works, in pictures"](http://www.bzarg.com/p/how-a-kalman-filter-works-in-pictures/) 。  
- 了解PID算法，通过查找文献改进基本PID算法。 

#### Project

*（分数占比30%, 40%, 5%, 25%）*  
**注意，1-1和1-2两个题目二选一。**  
- 1-1、编写一个工程，实现以下功能。
    - 使用 Arduino/STM32 单片机为主控，使用两个四位数码管。
    - 仿照Mission 8的规则，四位数码管显示残缺的四位数字（即密码），而且拼起来能够形成完整数字。
    - 每5秒定时随机（或看起来像随机）变换一次残缺数码管值，但拼接的四位密码不变。
    - 使用串口中断在上位机上输入四位数字，使其能够改变显示四位密码的值。
    - （发挥部分）在上位机制作GUI来调整程序运行时参数。

- 1-2、编写一个工程，实现以下功能。
    - 1、使用 Arduino/STM32 读取MPU6050的状态，使用串口库定时输出输出四元数和加速度到上位机。（可以调用标准库）
    - 2、通过加速度数据计算出姿态（因为重力加速度一直朝下，在传感器模块不动的情况下，可以根据重力加速度在传感器各个轴上的分量来计算传感器的姿态）。  
    - 3、通过角速度积分计算出姿态。   
    - 4、通过卡尔曼滤波融合加速度数据和角速度数据得到更精确的姿态数据。  
    - PS: 直接通过加速度计算姿态会收到很多因为模块运动带来的干扰，而通过角速度积分会有较大的积分误差，卡尔曼滤波可以弥补这个缺陷。其实网上有很多现成的代码来通过加速度计和陀螺仪计算姿态，你可以参考，搜索关键词“无人机姿态解算”。

- 2、在Mission 8中，进入赛场的人需要佩戴一个激光装置，装置能够接收敌方无人机和己方无人机的激光照射从而“失血”和“补血”。装置[如图所示](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/project_example2.jpg)。你的任务是简要仿造激光发射装置、激光接收与生命值计数装置。
    - （1）对于激光接收装置，请实现以下功能。
        - 1、使用 Arduino/STM32 作为主控单片机。
        - 2、使用一个四位数码管，右边两位显示生命值（00~10），最左边数码管用于提示被敌方击中（生命值-1）。
        - 3、用一个类似头盔的东西，在上面安装至少三个激光接收器。并与单片机连接。
        - 4、当有激光照射到接收器时，生命值-1，五秒后才能继续改变生命值。
    - （2）对于激光发射装置，请实现以下功能。
        - 1、使用 Arduino/STM32 作为主控单片机。（如果单片机数量不够，允许与接收装置共用一块单片机）
        - 2、可以发射激光，按键或开关控制激光的发射。
        - 3、使得最长有效发射与接收距离尽量长。
    - （3）（发挥部分）将激光分开为攻击激光（生命值-1）和治疗激光（生命值+1）。要求如下。
        - 1、攻击激光光线频率约为36kHz。治疗激光光线频率约为13kHz。
        - 2、发射器可以通过按键或开关转换发射攻击激光和治疗激光。
        - 3、发射器需要对激光进行调制（PWM输出），接收器需要对激光进行解调（输入捕获）。
        - 4、治疗激光最多只能接收四次，超过次数不加生命值。
    - （4）（发挥部分）每架飞机只能对人治疗一次。因此需要在治疗激光发射的信号中加入通信协议（可参考红外通信协议），使激光能发射出四种载波频率相同但携带信息不同的信号，能够被接收装置识别。如治疗光线带有第一架飞机的信息，接收装置接收到后能知道是第一架飞机发射过来的。

- 3、用自己的话归纳总结串口通信、I2C通信、SPI通信、红外通信的原理与应用，写在一份技术报告中，字数一千字左右。角度可以包括从芯片数据手册、时序图、程序代码、实际工程测试等分析。  

- 4、通过查找文献的方式认识和改进基本的PID算法（如位置式PID、增量式PID、串级PID等），并阐述PID如何运用到四轴飞行器的控制上。撰写一份技术报告。如有余力，请实现PID改进算法，在 MATLAB/Python 平台上仿真，一并写在报告中。


- - - - - -  

## 导航与编队方向

### 一、学习基本避障算法与编队基础

#### Content

- 了解基本的避障算法，学习人工势场法的基本原理，尝试改进算法。
- 学习简易仿真平台的搭建。

#### Project

*（分数占比60%）*  
- 请使用 C++/MATLAB/Python 编写一个仿真平台，在平台上进行简单无人机编队仿真，实现以下功能。并撰写一份技术报告。
    - 1、你需要仿真八架无人机。四架己方无人机，四架敌方无人机。建模的环境简化为二维（或者三维高度固定），无人机建模可简化为一个矩形（或长方体）。无人机可以不加入PID控制。
    - 2、敌方无人机飞行情况设定为慢速逼近己方无人机（但是敌方不会撞上来，只会干扰前行）。己方无人机的方案为一台主飞机和三台子飞机。己方飞机都知道自己的绝对位置和敌方飞机的位置。
    - 3、你的任务是通过人给主飞机发命令（外部输入），主飞机发指令给子飞机，一同前往前方25m的四个密码箱。飞行过程中保证己方飞机不撞上敌方飞机，己方飞机互不相撞（使用改进后的人工势场法），己方飞机不要飞出场外。
    - 4、把你的仿真结果输出。输出形式可以是路径轨迹，或者飞机动画等。
    - 5、（发挥部分）尝试多种己方前进策略。

    - PS：相关参数
        - 场地大小：28m x 15m （设平面直角坐标系(x, y)下，场地左下角为原点，侧边为长边y轴，底边为短边x轴）
        - 主飞机规格：0.9m x 0.9m x 0.4m
        - 子飞机和敌方飞机规格：0.3m x 0.25m x 0.2m
        - 己方无人机起点位置：离底边0.5m，可自行安排，即(xi, 0.5) (i=1,2,3,4)
        - 敌方无人机起点位置：离侧边0.5m，即(0.5, 10) (14.5, 10) (0.5, 20) (14.5, 20)
        - 四个密码箱位置：离顶边2m，即(1.5, 26) (5.5, 26) (9.5, 26) (13.5, 26)
        - 己方无人机飞行速率：<= 1m/s
        - 敌方无人机飞行速率：<= 0.6m/s


### 二、学习自动控制原理与无人机建模知识

#### Content

- 了解PID算法，通过查找文献学习基本PID算法。
- 了解四元数和欧拉角，阅读[《Quadrotor Dynamics and Control》](http://scholarsarchive.byu.edu/cgi/viewcontent.cgi?article=2324&context=facpub&sei-redir=1&referer=http%3A%2F%2Fcn.bing.com%2Fsearch%3Fq%3Dquadrotor%2Bdynamics%2Band%2Bcontrol%26qs%3DAS%26pq%3Dquadrotor%2Bdynamics%2Band%2Bc%26sc%3D2-24%26cvid%3D87AAD3B1893942708BA5918528A944E3%26FORM%3DQBRE%26sp%3D1#search=%22quadrotor%20dynamics%20control%22) 论文第一章。
- 简单了解三维建模知识。

#### Project

*（分数占比40%）*  
- 在已经完成的仿真平台上，继续做下列改进（均为发挥部分，根据自己的情况实现尽量多个点）。
    - 1、环境由二维变为三维（飞行高度可变）。无人机的建模和状态也需要相应细化。
    - 2、己方无人机控制加入PID算法，使其运动更真实。
    - 3、加大难度，敌方无人机逼近拦截己方无人机，最大速率改为1m/s。
    - 4、加大难度，“己方飞机都知道自己的绝对位置和敌方飞机的位置” 改为 “子飞机只知道自己与主飞机的相对位置，不知道敌方飞机位置；主飞机知道自己的绝对位置，知道子飞机和敌方飞机的相对位置”。
    - 5、优化己方前进策略。
    - 6、要求在提供的三维仿真平台（详见考核群）或自己制作的三维仿真平台上观察仿真结果。平台需要导入的轨迹数据可以使用格式化输出批量生成。

