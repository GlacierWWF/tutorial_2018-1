# SYSU AERO-SWIFT 入门教程汇总

## 0. Ubuntu系统安装指南  
电脑启动方式分为UEFI和BIOS两种方式，其中UEFI是近年来新电脑的主要启动方式，所以本教程针对的是UEFI启动方式的Windows和ubuntu 18.04双系统的安装教程.
### 0.1 UEFI启动方式的查看
运行->输入msinfo32->系统信息->bios模式
![UEFI启动方式查看](https://gss0.baidu.com/9vo3dSag_xI4khGko9WTAnF6hhy/zhidao/wh=600,800/sign=bbcb4c9ee7c4b74534c1bf10ffcc322f/d0c8a786c9177f3ed69736ba7ccf3bc79e3d56e2.jpg)
</br>
如果是UEFI启动方式，请看下一步.

### 0.2 下载ubuntu 18.04 和写入硬盘映像
* 首先下载ubuntu映像文件[ubuntu 18.04 LTS下载链接](https://www.ubuntu.com/download/desktop).
* 其次下载UltraISO[UltraISO下载地址](https://cn.ultraiso.net/xiazai.html).
* 打开软件UltraISO，文件----打开-----找到下载好的ubuntu.ISO文件.
* 使用Ubuntu 16.04和Ubuntu 18.04 都是可以的,推荐使用**Ubuntu 18.04**.
* 启动------写入硬盘镜像
</br>
![软碟通图片](https://upload-images.jianshu.io/upload_images/1272002-312fb39ebb48bd19.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/670)
</br>

默认参数写入即可，如果此处写入失败，请使用管理员权限打开UltraISO

### 0.3 Windows磁盘设置
在Windows 10中打开“磁盘管理器”，找一个空闲的磁盘分区，压缩出来一部分空间给Ubuntu使用，压缩出来的硬盘应处于未分配状态。或者通过删除某个不使用的本地磁盘使其处于未分配状态。
![磁盘管理](https://upload-images.jianshu.io/upload_images/1272002-334e3e33d83fd8b8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)
</br>

* 如果想学习Linux的话，留给Ubuntu使用的空间建议大于60G。
* 这里是一整个未分配空间，这样可以在安装Ubuntu的时候直接选择和Windows共存安装，自动分配空间，不用自己再给系统分区设置大小了。

### 0.4 重启进入 BIOS
* 关机，重新打开电脑，进入BIOS，关闭Windows系统的快速启动（Fast Boot）选项，即设置为Disable状态.
* 关闭 Secure Boot.
* 启动项优先级 Boot Priorities中，将ubuntu 18.04设置成第一启动项.
![boot manager](https://upload-images.jianshu.io/upload_images/1272002-42f06103698c8961.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)
</br>
大家的boot 界面各有不同，所以不一定是这个界面.
重启进入u盘引导的ubuntu启动界面，选择第二个install ubuntu进入安装环节.

### 0.5 安装Ubuntu
选择语言等等就不赘述了，重点是安装类型的设置.
![ubuntu安装类型](https://upload-images.jianshu.io/upload_images/1272002-6eb497d6e84d50d2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)
选择其他选项，进行磁盘分区.初步划分成4个区域
</br>

|挂载点`/`|30g|文件类型ext4|
| -- | -- | -- |
|挂载点`/home`|29G|文件类型ext4|
|SWAP|800mb| |
|挂载点`/boot`|400mb|文件类型ext4|

然后将下方的“安装启动引导器的设备”选择刚划分的固态硬盘上/boot的sda（或sdb）名字.下一步安装即可.
这样做的好处:
* 删除ubuntu时不会影响windows,直接在windows上面把之前给Ubuntu划分的区域，在磁盘管理里面全部格式化，就可以做到直接删除.(日后大家不避免的会遇到系统崩溃等问题，方便大家安装)
* 安装`opencv`是在`/home`目录下安装的，留够充足的空间有利于安装过程不出现错误.
* 这个系统分区一旦设置好了以后很难更改.所以推荐大家分配的空间越多越好.
## 1. Linux应用相关资料
[鸟哥的Linux教程](http://linux.vbird.org/)  
[Github的正确打开方式](https://github.com/baixing/FE-Blog/issues)  
[Shell入门笔记](https://shimo.im/doc/eN7lHqW2l2IZdTbT)  
[GitHub 风格的 Markdown 语法](https://github.com/baixing/FE-Blog/issues/6)  


## 2. OpenCV - Linux安装指南
安装OpenCV，有两种安装方式。
### （1）源码安装
第一种方式较复杂，但能得到最新的opencv3版本。教程可见[opencv源码安装教程](http://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)  
需要注意的是需要确定安装opencv的版本，在cmake之前，分别在终端输入
```
cd ~/opencv
git checkout 3.4.3
cd ~/opencv_contrib
git checkout 3.4.3
```
目前最新版本是3.4.3，于2017.08.29发布，也可以安装3.3.0以上其它版本。

- 关于cmake
你可以按照教程中的cmake -D +一堆参数,我们建议使用 cmake-gui以将项目中cmake可选择的参数通过图形化界面全部显示出来
首先安装cmake-gui  
`sudo apt-get install cmake-qt-gui`
接着直接在命令行输入  
`cmake-gui`
按照图形化界面的提示选择 源码：opencv文件夹 build：opencv/build文件夹，configure后generate即可。  

- 关于make
如果你的机子支持多线程，为加快编译速度，可以选择  
`make -j9`

### （2）apt-get (ubuntu)
第二种方式非常简单，但只提供opencv2版本[opencv-apt-get安装教程](http://blog.csdn.net/tina_ttl/article/details/52745807)  
这个教程对apt-get方式提供了详细的说明，其实里面也只有一条指令`sudo apt-get install libcv-dev`

另外，安装opencv遇到的一些问题，可参见：[opencv3常见问题合集](https://shimo.im/doc/p3gRFoLd7Z43lkXZ)

## 3. 团队推荐阅读资料
- [团队代码规范(18版)](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/docs/team_program_specification.md)
- [团队编程规范(17版)](https://shimo.im/doc/rfK9ome7WLEZ0xrA/)
- [程序员的自我修养（1-4章，其余选读）](https://leohxj.gitbooks.io/a-programmer-prepares/content/) （可能需要翻墙阅读）


## 4. 飞行器操作训练说明
训练方法（具体的操作我们会在内培中介绍）  
油门的精准控制是飞手训练的重中之重  
1. 悬停——精准控制油门，保持位置和高度大体不变
2. 迅速地定点降落
3. 左右旋转飞行器的同时保持高度（油门）不变
4. 沿着固定路线快速飞行（例如严格按照边长为4米的正方形路线飞行，越快完成越好）
5. 模拟失控飞行（给飞行器的一角挂上重物，使飞行器飞行不稳）
6. 花式飞行，换更高难度的飞行路线，灵巧变换飞行旋转角
7. （难度最高）在飞行器倒转角度飞行情况下仍能控制好飞行器的方向
8. 其他：  
（1） 让飞行器灵巧地飞回自己的手上  
（2） 远距离精准降落  

