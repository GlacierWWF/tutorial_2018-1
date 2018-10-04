## 简易计时器
- Author: 马飞鹏
- Revised: 马飞鹏
- Date: 2018-10-3
- Version: 1.0.0
- Abstract: 利用opencv编写的具有可视化界面的计时器

### Function:  
创建一个窗口，并通过输入命令来控制计时器的开始，暂停，恢复，结束等。    

### Interfaces: 
``` 
 void Timer::open()		        ///打开计时器的欢迎界面
 void Timer::startTiming()		///开始计时
 void Timer::open()		        ///打开计时器的欢迎界面
 void Timer::startTiming()		///开始计时
 void Timer::stopTiming()		///结束计时，界面恢复欢迎界面
 void Timer:: pause()		  	///暂停计时
 void Timer:: resume()			///恢复计时
 void Timer:: close()			///关闭计时

```

### Depend Libraries
  
  
  
### how to compile  
```
make
```

### how to run
```
//启动计时器窗口，显示欢迎界面
./timer

//开始计时，同时可以输入start,pause,stop,resume来控制计时器

```

