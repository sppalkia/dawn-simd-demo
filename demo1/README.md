#demo1

Shows a number of examples where compilers may or may not vectorize code
depending on various patterns.

Set the `#define` for the functions you want to see to`1` (e.g., `#define
ADD_ONE 1` if you want to see the report for the `add_one` function).

Run `make` to build an LLVM IR file.

## Compiler Flags

* `-O3`: Optimize lots
* `msse3`: Use SSE3; most Intel laptops will have this.
* `-Rpass=loop-vectorize`: Specify which loops were vectorized.
* `-Rpass-missed=loop-vectorize`: Specify which loops were not vectorized.
* `-Rpass-analysis=loop-vectorize`: Specify why unvectorized loops weren't vectorized.
* `-ffast-math`: Use fast math optimizations. See [this](http://stackoverflow.com/questions/7420665/what-does-gccs-ffast-math-actually-do).
