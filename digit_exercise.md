## OpenCV数码管图片识别具体任务说明
**编写一个能对含有四位数码管图片进行图像处理和数字识别的程序。**
在Mission 8中，我们需要通过识别数码管的数字来获得密码箱的密码。下面是一个简化版的数码管识别题目。

### 这个project重点需要预备队员掌握以下内容：
- 1、熟练运用所学OpenCV的知识。
- 2、makefile多文件编译。
- 3、数码管数字识别。

### 具体要求： 

- 1、给你一张带有四位数码管的图片，你需要利用OpenCV对图片进行处理，分别提取四个数字（或在图片上做标记）。定位到数字后，采用一定方法将数字值识别出来，将结果输出到终端或图片上。
- 2、该project的测试样本分为几个难度，你可以逐级尝试。
    - 第一级难度是使用电脑软件仿真的数码管图片，图片较清晰。[示例图](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week3_example1.jpg)。
    - 第二级难度是使用实际的数码管用摄像头拍摄的图片，图片噪声较大。[示例图](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week3_example2.jpg)。
    - 第三级难度是软件仿真的数码管图片。但是每组图有两段数码管，每段数码管只显示密码的一部分。你需要将两幅图用OpenCV组合，再识别出正确密码。[示例图](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week3_example3.jpg)。
- 3、每个级别提供5个Sample，即20个数码管数字。评分将以数字识别正确个数即识别正确率为标准。Samples放在了[这里](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples)的三个文件夹。级别一即sim_samples，级别二即act_samples，级别三即hard_samples。请自行取用验证。
- 4、 请记得附上图片处理过程和识别结果截图，放在一个子文件夹内。请附上简明易懂的工程说明`README.md`。


### 相关提醒与建议：

- 1、你可以分一个个阶段完成，在截止时间前完成尽量多的阶段。
- 2、sim_samples和hard_samples的五幅图图片大小有细微差距，请留意。act_samples的五幅图图片大小均为800*600。
- 3、可能用到的算法或思路有：（（TODO：补充提示））


### 最终功能要求：

- 1、图片能够处理出四个数字，数字各自连贯。
- 2、能够定位图片中四个数字，并分割数字。
- 3、仿真测试样本识别率 >= 50% 。
- 4、实际测试样本识别率 >= 50% 。
- 5、实现拼接不完整数码管，仿真测试样本识别率 >= 20% 。
   - PS：其中，数字识别正确率越高，积分越高，具体请看评分标准。

