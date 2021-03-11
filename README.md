# cmdsuzdal library

[![Build Status](https://travis-ci.org/fpiantini/cmdsuzdal.svg?branch=main)](https://travis-ci.org/fpiantini/cmdsuzdal)
[![codecov](https://codecov.io/gh/fpiantini/cmdsuzdal/branch/main/graph/badge.svg?token=O6Y4AK3L9K)](https://codecov.io/gh/fpiantini/cmdsuzdal)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/fpiantini/cmdsuzdal.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/fpiantini/cmdsuzdal/context:cpp)
![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-blue.svg?style=rounded)](http://makeapullrequest.com)


[Commander Suzdal] library: a C++ library to support the development of chess related software (e.g. Engines).

Developed using a TDD approach.

## How To build

Command Line (basic) instructions:

First of all, clone and build the project:

```bash
git clone --recurse-submodules https://github.com/fpiantini/cmdsuzdal.git
mkdir build
cd build
cmake [cmake_options] ../cmdsuzdal
cmake --build .
```

Possible `cmake_options`:

 - `-G <Generator>`: the generator to use to build the project. Suggested generator: [Ninja].
 - `-DCMAKE_INSTALL_PREFIX=<installation_directory>`: specify the installation directory for the `install` target
- `-DENABLE_COVERAGE_TEST=OFF`: to disable test coverage computation

Execute tests:
```bash
ctest -V .
```

Compute test coverage:
```bash
cmake --build . --target libcmdsuzdal_coverage
```

See the test coverage results opening the `libcmdsuzdal_coverage/index.html` file.

Install the library to use it from another project:
```bash
cmake --build . --target install
```


[Commander Suzdal]: https://www.fadedpage.com/showbook.php?pid=20170826
[Ninja]: https://ninja-build.org/
