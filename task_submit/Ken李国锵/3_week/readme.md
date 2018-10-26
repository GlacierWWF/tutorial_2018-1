# DIGIT TUBE IDENTIFIER

- AUTHOR: KEN李国锵
- DATE: 2018-10-24
- VERSION: 1.1.0
- ABSTRACT: DIGIT TUBE IDENTIFIER

---
#### 截图已存放在PICTURE文件夹中
---
## 问题

- 由于难度对于入门者来说太大，故参考了众多专门针对性的网上教程，虽说有点投机取巧，但也基本理解了各种思路以及如何使用Opencv处理图片。
- 由于个人原因，项目进度受到严重影响
- 对HARD图片的旋转仍不到位，导致完全无法识别

---
## 如何编译
- 事实上已经用cmake方法编译好了，只需 
- $ cd build
- $ cmake ..
- $ make

---
## 如何运行

- **首先先从sample文件夹中将第三周图片复制到bin文件夹中**

#### 对于simple sample和act sample

- $ cd bin
- $ ./main.out *sim_sample1.jpg*
- 或
- $ ./main.out *act_sample1.jpg*

####  对于hard sample

- $ cd bin
- $ ./main.out *hard_sample3_1.jpg hard_sample3_2.jpg*



