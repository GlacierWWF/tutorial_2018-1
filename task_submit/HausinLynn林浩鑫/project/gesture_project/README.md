# Gesture Project
- Author: HausinLynn
- Revised: HausinLynn
- Data: 11/05/2018
- Version: 1.0.0.1
- Abstract: Hello, this is a project to
recognize gesture, including generating
gesture images, generating tfRecord data,
training, testing and recognizing with
opencv and model after training.

---

### Dependencies
- python 3.6.6
- TensorFlow 1.11.0
- opencv 3.4.3
- numpy 1.15.3
- PIL 5.1.0

---

### Usage

```
# Get Data
mkdir gesture_data
python3 generate_data.py

# Train
python3 gesture_train.py

# Test
python3 gesture_test.py

# Recognize
python3 capture_and_recognize.py
```

---

### OUTPUT

Test Result:
![window](res/test_result.png)

Recognize Result:
watch res/demo.mp4
