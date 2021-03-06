# cmdsuzdal library

[![Build Status](https://travis-ci.org/CmdSuzdal/libcmdsuzdal.svg?branch=main)](https://travis-ci.org/CmdSuzdal/libcmdsuzdal)
[![codecov](https://codecov.io/gh/CmdSuzdal/libcmdsuzdal/branch/main/graph/badge.svg?token=GBBPR7YIUX)](https://codecov.io/gh/CmdSuzdal/libcmdsuzdal)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/CmdSuzdal/libcmdsuzdal.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/CmdSuzdal/libcmdsuzdal/alerts/)


[Commander Suzdal] library: a C++ library to support the development of chess related software (e.g. Engines).

Developed using a TDD approach.

## How To build

Prerequisites: when test coverage computation is enabled, default configuration make use of [fastcov]. Install it using the following command:

```bash
sudo pip3 install fastcov
```

Command Line (basic) build instructions:

First of all, clone and build the project:

```bash
git clone --recurse-submodules https://github.com/CmdSuzdal/libcmdsuzdal.git
mkdir build
cd build
cmake [cmake_options] ../cmdsuzdal
cmake --build .
```

Possible `cmake_options`:

 - `-G <Generator>`: the generator to use to build the project. Suggested generator: [Ninja].
 - `-DCMAKE_INSTALL_PREFIX=<installation_directory>`: specify the installation directory for the `install` target
- `-DENABLE_COVERAGE_TEST=ON`: to enable test coverage computation

Example:
```bash
cmake -G Ninja -DCMAKE_INSTALL_PREFIX=../_INSTALL_ -DENABLE_COVERAGE_TEST=ON ../libcmdsuzdal
```


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
[fastcov]: https://github.com/RPGillespie6/fastcov