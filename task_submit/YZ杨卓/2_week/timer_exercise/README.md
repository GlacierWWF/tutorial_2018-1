# Timer class for SYSU-IARC Tutorial Project

____
- **Author**: 杨卓
- **Revised**: 杨卓
- **Version**: 1.0.0
- **Date**: 2018-10-6
- **Abstract**:  Code for Timer class
____

## Required

For Unix/Linux:

- gcc >= 3.0
- opencv >= 3.0

___

## Description

---

-  ### Functions:

          void* thread_timing(void *t1); // 传递到新线程的函数，用于计时并显示图片

-  ### Interfaces:

                void open(); // 打开欢迎图片
              	void startTiming(); // 进入计时，显示图片
                void stopTiming(); // 用于关闭计时窗口，打开欢迎窗口
                void close(); // 关闭所有窗口
             	void pause(); // 暂停计时功能。实际为计算暂停时间
              	bool resume();// 恢复计时

-  ### Depend Libraries:

                1. pthread
                2. opencv
---

## Usage

___

```
# compile
```
g++ -c op.h op.cpp 

g++ main.cpp op.o -o main.out -lpthread `pkg-config --cflags --libs opencv`

- **or**
```
make
```

```
# run
```

./main.out

---

## Expected Output

---

``>>>`` ./main.out

[INFO] Welcome to my bug!

[INFO] Input 'start' to continue

``>>>`` start

[INFO] Start counting.

Counting: 0

Counting: 1

``>>>`` pause

[INFO] Now your command is : pause

[INFO] Paused.

``>>>`` resume

[INFO] Now your command is : resume

[INFO] Resumed.

Counting: 2

Counting: 3

``>>>`` stop

[INFO] Now your command is : stop

[INFO] Stop counting.

[INFO] Now only 'quit' works.

``>>>`` quit

[INFO] Now your command is : quit

[INFO] Congratulation! You finally exit the bug!

---




