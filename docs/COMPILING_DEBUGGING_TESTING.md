# Compiling, debugging and testing efficiently

This document describes ways of compiling, debugging, and testing efficiently for various use cases.

The intended audience is developers who want to use newer `CMake` workflows when working with Judecoin. This document aims to lower the entry barrier for these developers.

Before reading this document, please consult the "Build instructions" section in the main `README.md`.

Some information from `README.md` will be repeated here, but the aim is to go beyond it.

## Basic compilation

Judecoin can be compiled via the main `Makefile`, using one of several targets listed there.

The targets are actually presets for `CMake` calls with various options, plus `make` commands for building or, in some cases, `make test` for testing.

It is possible to extract these `CMake` calls and modify them for your specific needs. For example, a minimal external `CMake` command to compile Judecoin, executed from within a newly created build directory, could look like:

```bash
cmake -S "$DIR_SRC" -DCMAKE_BUILD_TYPE=Release && make
```

where the variable `DIR_SRC` is expected to store the path to the Judecoin source code.

## Use cases

### Test Driven Development (TDD) - shared libraries for release builds

Building shared libraries spares a lot of disk space and linkage time. By default, only debug builds produce shared libraries. If you would like to produce dynamic libraries for release builds for the same reasons as they are produced for debug builds, then you need to add the `BUILD_SHARED_LIBS=ON` flag to the `CMake` call, like the following:

```bash
cmake -S "$DIR_SRC" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON && make
```

A perfect use case for the above call is following the Test Driven Development (TDD) principles. In a nutshell, you would first write a couple of tests that describe the new requirements of the class or method that you are about to write or modify. The tests will typically compile for quite a long time, so ideally you should write them once. After you are done with the tests, the only thing left to do is to keep modifying the implementation for as long as the tests are failing. If the implementation is contained properly within a `.cpp` file, then the only time cost to be paid will be compiling the single source file and generating the implementation's shared library. The test itself will not have to be touched and will pick up the new version of the implementation, via the shared library, upon the next execution of the test.

### Project generation for IDEs

CMake allows project files to be generated for many IDEs. The list of supported project files can be obtained by writing in the console:

```bash
cmake -G
```

For instance, in order to generate Makefiles and project files for the Code::Blocks IDE, this part of the call would look like the following:

```bash
cmake -G "CodeBlocks - Unix Makefiles" (...)
```

The additional artifact of the above call is the `jude.cbp` Code::Blocks project file in the build directory.

### Debugging in Code::Blocks (CB)

First prepare the build directory for debugging using the following example command, assuming that the path to the source directory is being held in the `DIR_SRC` variable, and using 2 cores:

```bash
cmake -S "$DIR_SRC" -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON && make -j 2
```

After a successful build, open `jude.cbp` with CB. From the CB menu bar, select the target that you want to debug. Assuming these are unit tests:

```text
Build -> Select target -> Select target -> unit_tests
```

In order to lower the turnaround time, we will run a specific portion of code of interest without having to go through all the costly initialization and execution of unrelated parts. For this, we will use GTest's test filtering capabilities. From the build directory, run the following command to list all registered tests:

```bash
tests/unit_tests/unit_tests --gtest_list_tests
```

For example, if you are only interested in logging, you would find the label `logging.` and its subtests in the list. To execute all logging tests, write the following in the console:

```bash
tests/unit_tests/unit_tests --gtest_filter="logging.*"
```

This parameter is what we need to transfer to CB in order to reflect the same behavior in the CB debugger. From the main menu, select:

```text
Project -> Set program's arguments...
```

Then, in the `Program's arguments` textbox, write the following:

```bash
--gtest_filter="logging.*"
```

Verify that the expected unit tests are being properly executed with `F9`, or select:

```text
Build -> Build and run
```

If everything looks fine, then after setting some breakpoints of your choice, the target is ready for debugging in CB via:

```text
Debug -> Start/Continue
```