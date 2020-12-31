# cmdsuzdal

[![Build Status](https://travis-ci.org/fpiantini/cmdsuzdal.svg?branch=main)](https://travis-ci.org/fpiantini/cmdsuzdal)

[Commander Suzdal]: a project to build a chess engine in C++ with a TDD approach.


## How To build

Command Line (basic) instructions:

```bash
git clone https://github.com/fpiantini/cmdsuzdal.git
cd cmdsuzdal
git submodule update --init --recursive
cd ..
mkdir build
cd build
cmake ../cmdsuzdal
cmake --build .
```

Verify tests:

```bash
ctest -V .
```



[Commander Suzdal]: https://www.fadedpage.com/showbook.php?pid=20170826
