## 空中机器人团队代码规范
- **作者**：吉祥物-刘寅一（Champion-Liu）
- **修订**：吉祥物-刘寅一
- **日期**：2018-09-13
- **版本**：1.0.0
- **摘要**：这是空中机器人团队的代码规范，包含这么写代码及其注释、readme、测试程序、文件结构，git上怎么写comment和wiki、什么情况下可以commit、什么情况下建分支和merge。

---

### 一、如何写好一份文档
（1）**前言**：代码可以不会写，但是人话一定要会说。在大家看懂你写的bug之前，请先学会写好一份`人类可以正常快速看懂`的README。中英文都可以（吉祥物喜欢用英文）。   
（2）**表头信息**：表头信息非常重要，包含*这个坑是谁最先挖的（作者/Author）*、*最后一位添加bug的人（修订/Revised）*、*最后一次修改的日期（日期/Date）*、*最新的更改（版本/Version）*、*展示一下您最新添加的bug（摘要/Abstract）*。

```md
## Title Here: Readme Tutorial 
- Author: Champion-Liu
- Revised: Champion-Liu
- Date: 2018-09-13
- Version: 1.0.0
- Abstract: Hello, this is the readme tutorial about how to show out your bug.
```

（3）**说明内容**：包括模块怎么的功能是什么、接口是什么、需要哪些依赖库、怎么编译、测试程序怎么运行，如果没有的话统统不准git commit到master分支上。

```md
### Functions: 
	... //Brief is okay
### Interfaces:
	... //C++ style declaration
### Depend Libraries:
	... //should include origin websites
```

接口示例：

```cpp
/// Initialize the module
static bool Hello::init();
/// Quit the module
static void Hello::quit();
```

依赖库示例：

```md
# 尽量都放到submodule下面，然后利用：
git submodule init
git submodule update
```

编译提示：

```md
mkdir build
cd build
cmake .. -DGPU
make -j16
```

测试程序：

```md
# how to run:
cd bin
./hello_test

# the result if it is running well:
>>> hello
```

---

### 二、如何写好代码及其注释
（1）**前言**：doxygen是一款可以把注释转换为文档的工具，效果的话可以看下[opencv文档](http://docs.opencv.org/3.4.3/)。  
（2）**代码风格**：头文件使用`*.hpp`，源文件使用`*.cpp`；  
（3）**注释风格**：[可以看一下这里](https://blog.csdn.net/wenrenhua08/article/details/39591239)。  

---

### 三、项目的结构是怎么样的
对于独立的模块：

```
DigitsMerger(项目名)
|- inc/ (模块头文件)
|- src/ (模块源文件)
|- bin/ (编译后的模块测试执行文件)
|- test/ (模块测试的源文件)
|- readme.md (说明文档)
|- CMakeLists.txt (既作为项目子模块编译文件，又作为模块测试文件主编译文件)
```

---

### 四、如何与队友愉快地使用git
(1) **如何commit**: 编译通过而且文档写完才可以到master分支。  
(2) **如何merge**：使用GitKraken。  
(3) **什么时候需要新分支**：你自己挖坑的时候。  
(4) **Wiki怎么写**：参照tutorial_2018的wiki。

---

### 五、吉祥物御用的基础模块
+ 官方指定类：

```cpp
class Publisher; //!< 信息共享
class SRobot;		//!< 实用类型  
```

+ 官方指定多线程写法：

```cpp
#include <atomic>
#include <thread>
#include <mutex>

std::thread thr;

... //TODO: 而不是使用pthread
```