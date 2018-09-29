## Palindrome for SYSU-IARC Tutorial Project
- **Author**: Champion-Liu
- **Revised**: Champion-Liu
- **Version**: 1.0.0
- **Date**: 2018-09-29
- **Abstract**: Code for Palindrome Online Judge.

---

### Required

For `Unix/Linux`:

+ gcc >= 3.0

---

### Usage

```bash
# compile
g++ palindrome.cpp -o palin

# run
./palin <your_text_here>
```

---

### Expected Output

```
 liuyinyi@MacBook-Pro >>> ./palin abcde                                                        ✔  9520  12:18:33 
abcde -- is not a palindrome.
 liuyinyi@MacBook-Pro >>> ./palin ISASI                                                        ✔  9521  12:18:43 
ISASI -- is a regular palindrome.
 liuyinyi@MacBook-Pro >>> ./palin 2A3MEAS                                                      ✔  9522  12:18:50 
2A3MEAS -- is a mirrored string.
 liuyinyi@MacBook-Pro >>> ./palin ATOYOTA                                                      ✔  9523  12:18:58 
ATOYOTA -- is a mirrored palindrome.
```