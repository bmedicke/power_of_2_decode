# used links:

- [function declaration isn't a prototype &#10513;](https://stackoverflow.com/questions/42125/function-declaration-isnt-a-prototype)
  - fixes `warning: this function declaration is not a prototype`
  - `void func()` takes an arbitrary number of arguments, use `void func(void)` for 0 arguments
  - __this is different to C++ which uses `void func()` for functions with 0 arguments__
- [implicit conversions &#10513;](http://localdoc.scusa.lsu.edu/cppreference/en/c/language/conversion.html)
- [return value of malloc &#10513;](https://stackoverflow.com/questions/3585847/return-value-of-malloc)
  - __No cast is needed on `malloc()` in C; however, it is in C++.__

