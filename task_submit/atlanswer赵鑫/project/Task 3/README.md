# Task 3 Static gesture recognition

* Author: atlanswer
* Revised: atlanswer
* Date: 2018/11/10
* Version: debug
* Abstract: Use CNN to predict gestures captured from camera

---

## NOTE

**Codes are modified from [CNNGestureRecognizer](https://github.com/asingh33/CNNGestureRecognizer) by asingh33.**
**The CNN data format has been changed to NHWC, but train model on U series Intel CPU is extremly hard, thus there is no sample result nor comfirmation about whether it would actually work or not.**

### Dependencies

* `opencv-python` 3.4.3.18
* `python` 3.6.7
* `tensorflow` 1.12.0
* `h5py` 2.8.0
* `numpy` 1.15.3
* `Pillow` 5.3.0
* `matplotlib` 2.1.2

### Usage

Run the script

```shell
    python video_capture.py
```

### Test environment

* OS info: Windows 10 Pro 1809
* CPU: Intel(R) Core(TM) i7-7660U CPU @ 2.50GHz