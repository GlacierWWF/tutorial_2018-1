## Timer报告
- **作者**: 冯颖雯 （fengyw8）
- **修订**: 冯颖雯 （fengyw8）
- **版本**: 1.0.0
- **日期**: 2018-10-6
- **摘要**:Timer半成品: 仅完成open部分，startTiming部分有运行错误；尚未实现多线程；单文件的makefile可编译成功并运行，多文件的makefile尚未完成。

---

### Required

For `Linux`:

+ gcc >= 3.0

---

### Dependence
- gcc
- opencv 2
- 一堆尚未理清的库


### How to use
multfile尚不可编译运行；unifile可通过make编译后运行
##### For unifile
- 将欢迎图片（th.jpg）复制到Makefile、Timer_unife.cpp所在目录下
- 在终端输入`make`，编译完成，在当前目录下会产生Timer_unifile.o和open文件
- 在终端输入`./open th.jpg` 运行程序，随即跳出一个图片窗口
- 对图片窗口输入回车，触发键入，随即终端会输出两行数字（编写时用于调试，无任何作用）
- 在终端输入一个数字，随即窗口中会再出现一行数字（同样用于调试，无任何作用），图片窗口关闭
- 若图片跳出后无法结束程序，则按`Ctrl+C`结束运行

##### For multifile



