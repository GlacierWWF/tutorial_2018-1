## OpenCV数码管图片识别具体任务说明
**编写一个能对含有四位数码管图片进行图像处理和数字识别的程序。**
在Mission 8中，我们需要通过识别数码管的数字来获得密码箱的密码。下面是一个简化版的数码管识别题目。

### 这个project重点需要预备队员掌握以下内容：
- 1、熟练运用所学OpenCV的知识。
- 2、makefile多文件编译。
- 3、数码管数字识别。

### 具体要求： 

- 1、给你一张带有四位数码管的图片，你需要利用OpenCV对图片进行处理，分别提取四个数字（或在图片上做标记）。定位到数字后，采用一定方法将数字值识别出来，将结果输出到**终端或图片**上。
- 2、该project的测试样本分为几个级别，你可以逐级尝试。
    - 级别一：使用电脑软件仿真的数码管图片，图片较清晰。[示例图](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week3_example1.jpg)。
    - 级别二：使用实际的数码管用摄像头拍摄的图片，图片噪声较大。[示例图](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week3_example2.jpg)。
    - 级别三：软件仿真的数码管图片。但是每组图有两段数码管，每段数码管只显示密码的一部分。你需要将两幅图用OpenCV组合，再识别出正确密码。[示例图](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples/week3_example3.jpg)。
- 3、每个级别提供5个Sample，即20个数码管数字。评分将以数字识别正确个数即识别正确率为标准。Samples放在了[这里](https://github.com/SYSU-AERO-SWIFT/tutorial_2018/blob/master/examples_and_samples)的三个文件夹。级别一即`sim_samples`，级别二即`act_samples`，级别三即`hard_samples`。请自行取用验证。
- 4、 请记得附上**简要图片处理过程和详细识别结果截图**，放在一个子文件夹内。请附上简明易懂的工程说明`README.md`。

### 终端输入与输出格式参考：
输入是在命令行参数中添加图片路径，输出是在命令行中显示图片对应的数值。格式仅供参考。  
级别一和级别二：
```
ubuntu$: ./bin/demo ./test.jpg
4321
ubuntu$:
```
级别三：
```
ubuntu$: ./bin/demo ./test_1.jpg ./test_2.jpg
1234
ubuntu$: 
```

### 提醒与建议：

- 1、你可以分一个个阶段即级别完成，在截止时间前完成尽量多的阶段。
- 2、不可以为每个级别指定一个单独的工程, 你需要一套足够健壮的识别系统来完成全部的内容
- 3、sim_samples和hard_samples的五幅图图片大小有细微差距，请留意。act_samples的五幅图图片大小均为800*600。
- 4、可能用到的算法或思路有：  
    - 1）取红色通道二值化。  
    - 2）flood fill（水漫金山）算法。  
    - 3）bounding box（边框回归）算法。  
    - 4）图形的畸变校正和归一化。  
    - 5）数字识别可以采用 比对距离（像素相减绝对值之和最小） / SVM（支持向量机） / NN（神经网络） 等等。  
    - PS：思路仅供参考，且提供了很多方向，你可以按照自己想做的思路完成。  


### 最终功能要求：

- 1、图片能够处理出四个数字，数字各自连贯。
- 2、能够定位图片中四个数字，并分割数字。
- 3、仿真测试样本识别率 >= 50% 。
- 4、实际测试样本识别率 >= 50% 。
- 5、实现拼接不完整数码管，仿真测试样本识别率 >= 20% 。  
   - PS：其中，数字识别正确率越高，积分越高，具体请看评分标准。

