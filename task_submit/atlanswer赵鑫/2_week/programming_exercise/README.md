## Programming exercise

* Author: Atlanwer (atlanswer@gmail.com)
* Revised: Atlanswer
* Date: 2018-10-05
* Version: Beta-1
* Abstract: Project files for IP network exercise.

---

### Dependencies

* `gcc` 8.2.1
* `cmake` 3.2.2

---

### Usage

#### How to build

Use `cmake`

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

#### How to run

```shell
$ cd build
$ ./IPNetwork
```

Provided input file: `input.dat`

```
3 
194.85.160.177 
194.85.160.183 
194.85.160.178
```

Expected output: `output.dat`

```
194.85.160.176 
255.255.255.248
```

---

#### Test environment

* Arch Linux 4.18.12
* cmake 3.2.2