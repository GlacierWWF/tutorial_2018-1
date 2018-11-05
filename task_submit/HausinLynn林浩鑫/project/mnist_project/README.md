# MNIST Project
- Author: HausinLynn
- Revised: HausinLynn
- Data: 10/27/2018
- Version: 1.0.0.1
- Abstract: Hello, this is a project about
MNIST, I realize it with keras and SVM
respectively.

---

### Dependencies
- python 3.6.6
- keras 2.2.4
- libsvm 3.23
- numpy
- PIL
- matplotlib


---

### Usage

For keras realization:

```
cd keras_realization

# train
python3 mnist_train.py

# test
python3 mnist_test.py

# recognize
python3 digit_recognize.py
input the path of the image: [image path]
PS: you can test the image in keras_realization/samples

```

For libsvm realization:

```
cd libsvm_realization

# train
python3 mnist_classify.py

```

---

### OUTPUT

Train with keras:

![window](keras_realization/res/train.png)

Train with libsvm:

![window](libsvm_realization/res/train.png)

```
We can see, when train with libsvm, cost 813.31s, but accuracy is 94%. When train with keras, cost 82.79s, but accuracy is 99.17%.
It's obviously that using keras to build neural networks is more efficient than using libsvm to classfy.
```

Recognize output:

0:
![window](keras_realization/res/demo_0.png)

1:
![window](keras_realization/res/demo_1.png)

2:
![window](keras_realization/res/demo_2.png)

3:
![window](keras_realization/res/demo_3.png)

4:
![window](keras_realization/res/demo_4.png)

5:
![window](keras_realization/res/demo_5.png)

6:
![window](keras_realization/res/demo_6.png)

7:
![window](keras_realization/res/demo_7.png)

8:
![window](keras_realization/res/demo_8.png)

9:
![window](keras_realization/res/demo_9.png)
