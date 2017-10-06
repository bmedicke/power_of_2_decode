# used links:

- [function declaration isn't a prototype &#10513;](https://stackoverflow.com/questions/42125/function-declaration-isnt-a-prototype)
  - fixes `warning: this function declaration is not a prototype`
  - `void func()` takes an arbitrary number of arguments, use `void func(void)` for 0 arguments
  - __this is different to C++ which uses `void func()` for functions with 0 arguments__

