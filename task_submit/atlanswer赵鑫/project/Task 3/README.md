# Task 3 Static gesture recognition

* Author: atlanswer
* Revised: atlanswer
* Date: 2018/11/10
* Version: debug
* Abstract: Use CNN to predict gestures captured from camera

---

## NOTE

**Codes are inspired from [CNNGestureRecognizer](https://github.com/asingh33/CNNGestureRecognizer) by asingh33.**

**我觉得很多选手都会照搬这个repo来完成这个任务，所以我认为重写一遍能够体现自己确实理解了这些内容。**  :joy:

**The CNN data format has been changed to NHWC, just for the love to my puny CPU.**

### Dependencies

* `opencv-python` 3.4.3.18
* `python` 3.6.7
* `tensorflow` 1.12.0
* `h5py` 2.8.0
* `numpy` 1.15.3
* `Pillow` 5.3.0
* `matplotlib` 2.1.2
* `send2trash` 1.5.0

### Usage

Run the script.</br>
The process is divided into three parts:</br>

1. capture seven scenarios

```shell
python .\capture.py
Action: 1 for capture gestures
2 for train the model
3 for predict gestures
Enter: 1
```

![capture](.\res\capture.png)

> Order: "OK", "fist", "five", "nothing", "plan C", "scissor", "stop"</br>
> **NOTE**: please make sure the ROI box's background is entire black.

2. train the model

```shell
python .\capture.py
Action: 1 for capture gestures
2 for train the model
3 for predict gestures
Enter: 2
```

3. test the result
```shell
python .\capture.py
Action: 1 for capture gestures
2 for train the model
3 for predict gestures
Enter: 2
```

![capture](.\res\OK.png)
![capture](.\res\fist.png)
![capture](.\res\five.png)
![capture](.\res\nothing.png)
![capture](.\res\plan_C.png)
![capture](.\res\scissor.png)
![capture](.\res\stop.png)

### Test environment

* OS info: Windows 10 Pro 1809
* CPU: Intel(R) Core(TM) i7-7660U CPU @ 2.50GHz