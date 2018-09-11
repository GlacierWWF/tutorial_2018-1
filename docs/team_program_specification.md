# 中大空中机器人队代码规范
制定本规范是为了让大家今后互相阅读代码更加方便.制定时参考的是Google C++风格的代码规范.
## 版本 V1.0.1
## 1.C++代码风格
### 1.1 `.h`头文件
#### 1.1.1 `.h`所有头文件要能够自给自足。换言之，用户和重构工具不需要为特别场合而包含额外的头文件.
#### 1.1.2 `.h`头文件必须包含`#define`保护.
``` 
//sysu-test.h
#ifndef SYSU_TEST
#define SYSU_TEST
...
#endif
```
#### 1.1.3 尽可能的避免前置声明，尽量使用`#include`.
```
//main.cpp
struct test
{
   int a;
   int b;
};
#include<iostream>
```
替代为:
```
//test-struct.inc
struct test
{
   int a;
   int b;
};
```
```
//main.cpp
#include"struct-test.inc"
#include<iostream>
```
#### 1.1.4 只有当函数只有 10 行甚至更少时才将其定义为内联函数.
#### 1.1.5 当大家使用`#include`插入文本的时候，请使用`.inc`作为后缀.
#### 1.1.6 头文件排序方式
|序号|头文件类型|
| -- | -- |
|1. | 相关头文件|
|2. | C 库|
|3. | C++ 库|
|4. | 其他库的 `.h`|
|5. | 本项目内的 `.h`|
```
//foo.cpp
#include "foo/public/foo.h" // 相关头文件

#include <sys/types.h> // C库
#include <unistd.h> 

#include <hash_map> // C++库
#include <vector>

#include"opencv/opencv2/core.hpp" // 其他库的 .h

#include "foo/public/bar.h" // 本项目的 .h
```

### 1.2 类
#### 1.2.1 构造函数
不要在构造函数中调用虚函数,也不要在无法报出错误时进行可能失败的初始化.
#### 1.2.2 隐式类型转换
不要定义隐式类型转换. 对于转换运算符和单参数构造函数, 请使用 `explicit`关键字.
#### 1.2.3 结构体 VS. 类
仅当只有数据成员时使用 `struct`, 其它一概使用 `class`.
#### 1.2.4 存取控制
将 所有 数据成员声明为 `private`, 除非是 `static const` 类型成员 (遵循 常量命名规则). 
#### 1.2.5 声明顺序
类定义一般应以 `public: `开始, 后跟 `protected:`, 最后是 `private:`. 省略空部分.

### 1.3 函数
#### 1.3.1 参数顺序
函数的参数顺序为: 输入参数在先, 后跟输出参数.(有的时候可以有所变通)
eg:`void RGB2HSV( Mat srcImg, Mat dstImg)`

## 2.命名规范
### 2.1 文件命名
文件名全部小写，每个单词之间使用`_`连接，例如:`example_test_submit`
### 2.2 类型命名
每个单词首字母大写，中间不使用任何连字符连接.
```
class HttpTest{};
struct MyFoo{};
```
### 2.3 变量命名
变量 (包括函数参数) 和数据成员名一律小写, 单词之间用下划线连接. 类的成员变量以下划线结尾, 但结构体的就不用, 如: `a_local_variable`, `a_struct_data_member`, `a_class_data_member_`.

### 2.4 常量命名
声明为 constexpr 或 const 的变量, 或在程序运行期间其值始终保持不变的, 命名时以 “k” 开头, 大小写混合. 例如:
```
const int kDaysInAWeek = 7;
```
### 2.5 函数命名
使用驼峰命名，即每个单词首字母大写，之后小写.
```
void AddNumber()
```
### 2.6 命名空间
命名空间采用全部小写，并且一般情况下使用项目全称.
```
namespace globalvision
{
...
}
```
### 2.7 枚举类型
枚举的命名应当和 常量 或 宏 一致: `kEnumName` 或是 `ENUM_NAME`.
```
enum UrlTableErrors {
    kOK = 0,
    kErrorOutOfMemory,
    kErrorMalformedInput,
};
enum AlternateUrlTableErrors {
    OK = 0,
    OUT_OF_MEMORY = 1,
    MALFORMED_INPUT = 2,
};
```
### 2.8 宏命名
全部大写，中间使用下划线连接.
```
#define MY_TEST_DEFINE_IN_SYSU
```

## 3.注释
### 3.1 文件注释
各位尽量在文件开头写上版权说明,在对其他人的代码改动时,请**保留**原本的版权说明，空一行写上**自己**的版权声明.(目的是让大家更好的找到作者).
样例:(格式没有严格限制)
```
//date: 2018-09-06
//Author: Zhang San
//Project name: global_vision

//date: 2018-09-06
//Author: Zhang Si
//Project name: global_vision
```
或者:
```
//时间: 2018-09-06
//作者: 
//项目名称: 全局视野
...
```
### 3.2 类注释
在类的定义时，请写一份注释描述类的用法,这样会避免让你的代码变成祖传代码.
### 3.3 函数注释
请描述函数的功能及用法.
### 3.4 注释注意事项
写注释的时候说**人话**，注释是给人看的.
### 3.5 TODO注释
对那些临时的, 短期的解决方案, 或已经够好但仍不完美的代码使用 `TODO` 注释.
`TODO`注释请写出名字和联系方式.
```
void TODO();
//TODO(ZHANG SAN) Description ,We need ...
//TODO(Email) Description, We need ...
//TODO(QQ:) Description, We need ...
```

## 4.版本管理
### 4.1 我们采用的是语义化版本规范
版本格式：主版本号.次版本号.修订号，版本号递增规则如下：

* 主版本号：当你做了不兼容的API 修改。
* 次版本号：当你做了向下兼容的功能性新增。
* 修订号：当你做了向下兼容的问题修正。(修复了一些bugs)

### 4.2 版本规范细则
* 使用语义化版本控制的软件“必须MUST”定义公共API。该API可以在代码中被定义或出现于严谨的文件内。无论何种形式都应该力求精确且完整。
* 标准的版本号“必须MUST”采用XYZ的格式，​​ 其中X、Y和Z为非负的整数，且“禁止MUST NOT”在数字前方补零。X是主版本号、Y是次版本号、而Z为修订号。每个元素“必须MUST”以数值来递增。例如：1.9.1 -> 1.10.0 -> 1.11.0。
* 标记版本号的软件发行后，“禁止MUST NOT”改变该版本软件的内容。任何修改都“必须MUST”以新版本发行。
* 主版本号为零（0.yz）的软件处于开发初始阶段，一切都可能随时被改变。这样的公共API 不应该被视为稳定版
* 1.0.0 的版本号用于界定公共API 的形成。这一版本之后所有的版本号更新都基于公共API 及其修改内容。
* 修订号Z（xyZ | x > 0）“必须MUST”在只做了向下兼容的修正时才递增。这里的修正指的是针对不正确结果而进行的内部修改。
* 次版本号Y（xYz | x > 0）“必须MUST”在有向下兼容的新功能出现时递增。在任何公共API的功能被标记为弃用时也“必须MUST”递增。也“可以MAY”在内部程序有大量新功能或改进被加入时递增，其中“可以MAY”包括修订级别的改变。每当次版本号递增时，修订号“必须MUST”归零。
* 主版本号X（Xyz | X > 0）“必须MUST”在有任何不兼容的修改被加入公共API时递增。其中“可以MAY”包括次版本号及修订级别的改变。每当主版本号递增时，次版本号和修订号“必须MUST”归零。

### 4.3 版本规范样例
```
project_name 
|- src  
|   |_ test.cpp 
|- inc 
|   |_ test.h 
|- bin
|   |_ project_name
|- main.cpp 
|_ makefile 
|_ README.md 
```

* 版本号请在git 提交时，在README.md中写明版本号,并且在`git commit -m `最后写明最新的版本号.
* 样例 `git commit -m "Fixed bugs V1.0.1"`.
* 请在每次修订程序后，修改README.md中的版本号和`git commit -m`中的版本号.

### 4.4为什么我们要确立版本管理规范
- 在我们的新版本出现问题时，可以快速回退到上一个稳定版本，便于团队整体进度的推进.
- 有利于对代码规范化管理.

## 5.目录规范
### 5.1 目录规范样例
```
project_name 
|- src 
|- inc 
|- bin 
|- pics (可以没有)
|- README.md 
|- main.cpp 
|_ makefile(或 CmakeLists.txt) 
```
src放置`.cpp` `.cc` `.c`文件 </br>
inc放置`.h` `.hpp` `.inc`文件 </br>
bin放置`a.out`可执行文件 </br>

## 6.文档编写守则
### 6.1 README.md的编写
```
# 工程(项目名称): project_test
## 版本号: V0.1.0 
## 时间: 2018-09-06
## 作者: 张三同学
```
有待完善

## 7.git多人共同开发模式
缺省
