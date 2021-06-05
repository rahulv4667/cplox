## cplox 

Creating an interpreter in C++ by following tutorials from [Crafting Interpreters](https://craftinginterpreters.com)


### Pitfalls

- `-123.abs()` or `-n.abs()` gives `-123` or `-n`. To get proper result, use `(-123).abs()` 
- No leading or trailing decimal points. `.1234` and `1234.` are invalid. `0.1234`, `1234.0` are right.
