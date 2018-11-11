## Matrix Class

- **作者**: 冯颖雯 （fengyw8）
- **修订**: 冯颖雯 （fengyw8）
- **版本**: 1.0.0
- **日期**: 2018-11-11
- **摘要**: 一个矩阵运算的类（加，减，数乘，点乘，叉积，转置，行访问，列访问，初始化Zero matrix和Identity matrix，深复制）

---

### Required

For `Linux`:

+ g++ >= 3.0

---


### Compile and Run

**# compile**
```bash
g++ -c main.cpp
g++ -c matrix.cpp
g++ main.o matrix.o -o test
```

**# run**
```bash
./test
```
---
### Test Result
```
Matrix1:
1 2 
3 4 
5 6 

Matrix2:
6 5 
4 3 
2 1 

Matrix3:
1 2 3 
4 5 6 

Matrix1 + Matrix2:
7 7 
7 7 
7 7 

Matrix1 - Matrix2:
-5 -3 
-1 1 
3 5 

4 * Matrix1:
4 8 
12 16 
20 24 

Matrix1 * Matrix3:
9 12 15 
19 26 33 
29 40 51 

Transpose of Matrix1:
1 3 5 
2 4 6 

The 2nd row of Matrix1:
3 4 
The 2nd column of Matrix1:
2 4 6 
Set matrix1 to zero matrix:
0 0 
0 0 
0 0 

Modify the entry of matrix1 at (0,0) and (1,1) to 3 and 10:
3 0 
0 10 
0 0 

Identity matrix of 5:
1 0 0 0 0 
0 1 0 0 0 
0 0 1 0 0 
0 0 0 1 0 
0 0 0 0 1 

The rows of Matrix1:
3
The columns of Matrix2:
2

```
