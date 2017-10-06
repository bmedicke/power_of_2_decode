# used links:

## C

- [function declaration isn't a prototype &#10513;](https://stackoverflow.com/questions/42125/function-declaration-isnt-a-prototype)
  - fixes `warning: this function declaration is not a prototype`
  - `void func()` takes an arbitrary number of arguments, use `void func(void)` for 0 arguments
  - __this is different to C++ which uses `void func()` for functions with 0 arguments__
- [implicit conversions &#10513;](http://localdoc.scusa.lsu.edu/cppreference/en/c/language/conversion.html)
- [return value of malloc &#10513;](https://stackoverflow.com/questions/3585847/return-value-of-malloc)
  - __No cast is needed on `malloc()` in C; however, it is in C++.__

## doxygen

- [Doxygen usage examples (for C) &#10513;](http://fnch.users.sourceforge.net/doxygen_c.html)
# compiling

Tested with both [clang &#10513;](https://clang.llvm.org) and [gcc &#10513;](https://gcc.gnu.org).

## make commands

### all

Compile everything that's out of date. The default compiler is `clang`.

### clean

Remove all binaries, object files and other output files.

### run

Runs the command with the default settings.

### verbose

Runs the command with default settings plus enable verbose output.

### help

Show the help text.

### format

Format all source files and shows changes via git diff. Requires [astyle &#10513;](http://astyle.sourceforge.net).

### link

Create a symlink pointing to the binary in `/usr/local/bin`.

### watch

Watches the source files for changes, recompiles and runs the binaries as necessary. Requires [hr &#10513;](https://github.com/LuRsT/hr) and [entr &#10513;](https://github.com/clibs/entr).
