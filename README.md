# cmdsuzdal

[![Build Status](https://travis-ci.org/fpiantini/cmdsuzdal.svg?branch=main)](https://travis-ci.org/fpiantini/cmdsuzdal)

[Commander Suzdal]: a project to build a chess engine in C++ with a TDD approach.


## How To build

Command Line (basic) instructions:

- Clone & Build:
```bash
git clone --recurse-submodules https://github.com/fpiantini/cmdsuzdal.git
mkdir build
cd build
cmake ../cmdsuzdal
cmake --build .
```
- Execute Tests:
```bash
ctest -V .
```



[Commander Suzdal]: https://www.fadedpage.com/showbook.php?pid=20170826
