## 数码管识别
- Author: 马飞鹏
- Revised: 马飞鹏
- Date: 2018-10-14
- Version: 1.0.0
- Abstract: 利用opencv编写识别数码管的工程

### Function:  
运行程序，输入图像路径，识别图像中的数码管中的数字。    

### Interfaces: 
``` 
int tell_num(Mat picture);	//判断截取的图片中的数字
int cut_picture(Mat &picture); 	//切割出图像中的数字部分
int merg(Mat p1,Mat p2,Mat &out) //融合级别三的图像

```

### Depend Libraries
  
  
  
### how to compile  
```
mkdir build  
cd build  
cmake ..   
make  

```

### how to run
```
//path为识别图像的路径
./processing path

//如果识别的是级别三的样本，则需要输入2个参数  
./processing path1 path2

```

###识别结果  
```

cd picture //进入存储识别结果图像的路径

```












