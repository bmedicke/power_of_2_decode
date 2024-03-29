# readme

# usage

See `decode -h`.

# notes on compiling

- Tested with [clang](https://clang.llvm.org) and [gcc](https://gcc.gnu.org).
- Tested on macos 10.13 and Arch Linux 4.13.
- Uses the C99 standard (for `_Bool`).
- Edit the `Makefile` to change settings.

## make commands

### make all

Compile everything that's out of date. The default compiler is `clang`.

### make clean

Remove all binaries, object files and other output files.

### make run

Runs the command with the default settings.

### make verbose

Runs the command with default settings plus enable verbose output.

### make help

Show the help text.

### make format

Format all source files and shows changes via a git diff to make individual decisions. Requires [astyle](http://astyle.sourceforge.net) and [git](http://git.com).

### make link

Create a symlink pointing to the binary. Default target is `/usr/local/bin`.

### make watch

Watches the source files for changes, recompiles and runs the binaries as necessary. Requires [hr](https://github.com/LuRsT/hr) and [entr](https://github.com/clibs/entr).

### make doc

Watches source and markdown files for changes, regenerates the documentation with Doxygen. Requires [doxygen](http://www.stack.nl/~dimitri/doxygen/) and [entr](https://github.com/clibs/entr).

### make report

Run to detect memory leaks. Removes PID from the `report` file to allow proper usage of `git diff`. Requires [Valgrind](http://valgrind.org) and `sponge` from the [moreutils](https://joeyh.name/code/moreutils/).

# used third party libraries

All code not written by me is in the `vendor` folder.

- [klib](https://github.com/attractivechaos/klib), MIT licensed
  - specifically `khash.h` for a hash map storing the count of the occurrences for the decoded words.
  - reasoning: fast, single file (header only), independent libraries; used in big projects (e.g. [Neovim](https://github.com/neovim/neovim))

# useful links and notes

## C

- [warning: function declaration isn't a prototype](https://stackoverflow.com/questions/42125/function-declaration-isnt-a-prototype)
  - fixes `warning: this function declaration is not a prototype`
  - `void func()` takes an arbitrary number of arguments, use `void func(void)` for 0 arguments
  - __This is different to C++ which uses `void func()` for functions with 0 arguments!__
- [implicit conversions](http://localdoc.scusa.lsu.edu/cppreference/en/c/language/conversion.html)
- [return value of malloc](https://stackoverflow.com/questions/3585847/return-value-of-malloc)
  - __No cast is needed on `malloc()` in C; however, it is in C++!__
- [Uninitialised value was created by a stack allocation valgrind C](https://stackoverflow.com/questions/24727764/uninitialised-value-was-created-by-a-stack-allocation-valgrind-c)

## IDE

get header search path for clang:

```sh
echo | clang -v -E -x c -
```
add paths to `.ycm_extra_conf.py`.

- [YouCompleteMe, header files](https://stackoverflow.com/questions/24438211/youcompleteme-header-files)
- [macOS c std lib completion and brew python problem](https://github.com/Valloric/YouCompleteMe/issues/2268)


## doxygen

- [Doxygen usage examples (for C)](http://fnch.users.sourceforge.net/doxygen_c.html)
- [How to make an introduction page with Doxygen](https://stackoverflow.com/questions/9502426/how-to-make-an-introduction-page-with-doxygen)

## klib

- [Implementing Generic Hash Library in C](https://attractivechaos.wordpress.com/2008/09/02/implementing-generic-hash-library-in-c/)
- [khash.h documentation (very outdated)](http://samtools.sourceforge.net/samtools/khash/index.html)

- [examples from the /test directory](https://github.com/attractivechaos/klib/tree/master/test)


# error handling

- input file characters not exclusively ones and zeroes
- input file characters outside the defined ASCII range (A-Z + space)
- input file characters not resolvable
- any file not writeable (chowned by root)


## known limitations

- can't handle words longer than `MAXWORDSIZE` defined in `helpers.c`
- order of words with same count is semi-random (based on hash table)
- assumes there's enough memory available to store entire decoded file
