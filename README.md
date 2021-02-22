# cmdsuzdal

[![Build Status](https://travis-ci.org/fpiantini/cmdsuzdal.svg?branch=main)](https://travis-ci.org/fpiantini/cmdsuzdal)
[![codecov](https://codecov.io/gh/fpiantini/cmdsuzdal/branch/main/graph/badge.svg?token=O6Y4AK3L9K)](https://codecov.io/gh/fpiantini/cmdsuzdal)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/fpiantini/cmdsuzdal.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/fpiantini/cmdsuzdal/context:cpp)
![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-blue.svg?style=rounded)](http://makeapullrequest.com)


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
