# Timer
- Author: zhong zhicong
- Revised: zhong zhicong
- Date: 2018-10-06
- Version: 1.0.0
- Abstract: It is a tool for timing

### Functions: 
	A tool for timing can start timing, stop, pause, resume and close.
    And the time will show in a picture.
### Interfaces:
    //begin timing
	void startTiming();
    //quit the timer
    void close();
    // pause the timer
    void pause();
    //open the timer
    void open();
    //print the text to the image
    void textImage();
    // stop timing
    void stopTiming();

### Depend Libraries:
	opencv 3.4.3
    cmake

### Compilation prompt
    要将timer.hpp中的路径修改成当前设备图片路径(ps:不知道为什么相对路径用不了)
    mkdir build
    cd build
    cmake ..
    make

### test
    cd build
    ./Timer
    可执行程序在build中

### the structure of the program
    Timer
    | - timer.hpp（Timer类的头文件）
    | - timer.cpp（Timer类的实现文件）
    | - main.cpp（模块测试程序）
    | - CMakeLists.txt（编译文件）
    | - Readme.md（说明文档）
    | - build（编译文件）
    | - welcome.jpg (welcome picture)
