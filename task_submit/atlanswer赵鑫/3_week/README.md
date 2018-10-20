# Seven segment display OCR

* Author: Atlanswer (atlanswer@gmail.com)
* Revised: Atlanswer
* Date: 2018-10-20
* Version: Beta-2
* Abstract: Project file for seven-segment display recognition

---

## Usage

### Dependencies

Their version numbers are read from test environment.

* `g++` 8.2.1
* `cmake` 3.12.3
* `make` 4.2.1
* `opencv` 3.4.3-4
* `hdf5` 1.10.3-2
* `vtk` 8.1.1-2
* `glew` 2.1.0-1

---

### Build

Using `cmake` build system, run it twice to produce `compile_commands.json` for IntelliSence, see [this issue](https://gitlab.kitware.com/cmake/cmake/issues/16588).

```shell
mkdir build
cd build
cmake ..
cmake ..
make
```

The executable shoule be in `./bin`

### Run

```shell
cd bin
./ocr <relativePathToImage> <relativePathToImage2(optional)>
```

Example
> ./ocr ../../../../examples_and_samples/hard_samples/hard_sample1_1.jpg ../../../../examples_and_samples/hard_samples/hard_sample1_2.jpg

Results are listed in `./screenshots`

#### Test environment

* Arch Linux 4.18.14
* Gnome 3.30.1