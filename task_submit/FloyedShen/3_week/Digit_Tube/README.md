Digit_Tube image Recognition by opencv
======================================

- **作者**:申国斌（Floyed_Shen）
- **修订**:Floyed_Shen
- **日期**:2018-10-12
- **版本**:1.0.0
- **摘要**:使用opencv对四位数码管的图片进行简单的合并、分割与识别

Funcitons:
-------------
```cpp
public:
    Digit_Tube();//初始化
    Digit_Tube(cv::Mat);//
    Digit_Tube(char[]);//
    Digit_Tube(std::string );//
    Digit_Tube(std::string,std::string);//
    bool open()const;//判断是否打开图像
    void identify();//图像识别
    void print()const;//打印ans
    ~Digit_Tube();//
```
Depend Libaries:
-----------------
    opencv2 required

Compilation prompt:
---------------------
    cmake .
    make
    bin/./Digit_Tube_PRO

How to run:
--------------------
    运行程序后在Terminal输入预计处理图像类型
    0 :一张图片
    1 :两张图片

    然后直接输入图片名称
    (图片路径已经定义到 [输入图片](./input) ,并忽略文件扩展名,默认为*.jpg)
    显示结果如 [输出结果](./output) 所示

test result:
---------------
    [输出结果](./output)
    注:s1 means sim_sample1.jpg
       a1 means act_sample1.jpg
       h1_1 means hard_sample1_1.jpg
