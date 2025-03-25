# XPR

*X Place and Route, where X stands for your quantum computer architecture of choice*

## Installation

### Build XPR and run the standalone application

```console
$ cmake -S standalone -B build/standalone
$ cmake --build build/standalone
$ ./build/standalone/xpr [options]
```

## Usage

For full usage instructions, see

```console
$ xpr --help
```

## Development

### Build and run the XPR test suite

```console
$ cmake -S test -B build/test
$ cmake --build build/test
$ ./build/test/XprTests
```

### Code formatting

XPR uses the [`Format.cmake`](https://github.com/TheLartians/Format.cmake) package to manage code formatting with `clang-format` and `cmake-format`.

Show which files are affected by clang-format:

```console
$ cmake --build build --target format
```

Return an error if files are affected by clang-format (useful for CI integration):

```console
$ cmake --build build --target check-format
```

Apply `clang-format` to all affected files:

```console
$ cmake --build build --target fix-format
```

### Build everything at once

For convenience during development, the project also contains the `all` directory that allows building all targets at the same time.
This is useful during development, as it exposes all subprojects to your IDE and avoids redundant builds of the library.

```console
$ cmake -S all -B build
$ cmake --build build

$ # run tests
$ ./build/test/XprTests
$ # format code
$ cmake --build build --target fix-format
$ # run standalone
$ ./build/standalone/xpr [options]
```

### Generate the clang compile commands database

For use with the [`clangd`](https://clangd.llvm.org/) language server, you can generate the [`compile_commands.json`](https://clangd.llvm.org/installation#project-setup) file as follows:

```console
$ cmake -S all -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```
