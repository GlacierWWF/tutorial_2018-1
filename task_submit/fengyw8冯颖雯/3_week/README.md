## OpenCV数码管图片识别报告

- **作者**: 冯颖雯 （fengyw8）
- **修订**: 冯颖雯 （fengyw8）
- **版本**: 1.0.0
- **日期**: 2018-10-14
- **摘要**:利用OpenCV对数码管数字进行识别，基本能识别全部sim_sample，只可识别部分act_sample，未实现识别hard_sample。

---

### Project structure

```
3_week
|- include/  (头文件)
|- src/  (源文件)
|- bin/  (可执行文件)
|- result_image/ (结果输出图)
|- sample_image/ (测试样本图)
|- procedure_image/ (测试过程图)
|- README.md
|- CMakelists.txt

```

---

### Dependence
- g++
- opencv 2
- camke

---

### Compile and Run

```
# compile
cmake .
make

# run
./bin/DigitRecognization ./sample_image/sim_sample1.jpg
./bin/DigitRecognization ./sample_image/sim_sample2.jpg
...

./bin/DigitRecognization ./sample_image/act_sample1.jpg
./bin/DigitRecognization ./sample_image/act_sample2.jpg
...

```

---
### Test Result
```
sim_sample1:2039    answer：2039
sim_sample2:0341    answer：0341
sim_sample3:5162    answer：5162
sim_sample4:8397    answer：8397
sim_sample5:571     answer：5671
sim_sample6:876     answer：8276
sim_sample7:2951    answer：2951
sim_sample8:8305    answer：8305

act_sample1:935     answer：9735
act_sample2:1441    answer：7841
act_sample3:8026    answer：8026
act_sample4:3146    answer：3146
act_sample6:0       answer：0163
act_sample8:1884    answer：1427

```

---

### Sample Output

![sim_sample1](sesult_image/sim_sample1.JPG)

![sim_sample8](sesult_image/sim_sample8.JPG)

![act_sample3](sesult_image/act_sample3.JPG)


