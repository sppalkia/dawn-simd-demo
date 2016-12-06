#demo1

Shows a number of examples where compilers may or may not vectorize code
depending on various patterns. These use `clang` and were tested on
`clang version 3.7.1 (Target: x86_64-apple-darwin16.1.0)`.

Set the `#define` for the functions you want to see to`1` (e.g., `#define
ADD_ONE 1` if you want to see the report for the `add_one` function).

Run `make` to build an LLVM IR file.

## Compiler Flags

* `-O3`: Optimize lots
* `-msse3`: Use SSE3; most Intel laptops will have this.
* `-Rpass=loop-vectorize`: Specify which loops were vectorized.
* `-Rpass-missed=loop-vectorize`: Specify which loops were not vectorized.
* `-Rpass-analysis=loop-vectorize`: Specify why unvectorized loops weren't vectorized.
* `-ffast-math`: Use fast math optimizations. See [this](http://stackoverflow.com/questions/7420665/what-does-gccs-ffast-math-actually-do).

## Some Notes

### `-ffast-math`

Fast math can enable the use of vector instructions for math functions like
`sqrt`, which usually have checks for NaN or negative numbers which preclude
vectorization. The flag can also enable vectorization of patterns like
reduction (e.g, summing an array of floats into a single value) since the
compiler will ignore the non-associativity rule of the floating point standard.

### `restrict`

The `restrict` keyword specifies that pointers are not aliased; in other words,
it states that the data pointed to by two pointers will never be the same. It
prevents runtime memory checks which can improve performance if a function is
called repeatedly.

For example, the `update` function in `simd_demo.c` has the following LLVM IR snippet:

```
vector.memcheck:                                  ; preds = %for.body.preheader
  %3 = add i32 %length, -1, !dbg !64
  %4 = zext i32 %3 to i64, !dbg !64
  %scevgep = getelementptr float, float* %v1, i64 %4, !dbg !64
  %scevgep12 = getelementptr float, float* %v2, i64 %4, !dbg !64
  %bound0 = icmp uge float* %scevgep12, %v1, !dbg !64
  %bound1 = icmp uge float* %scevgep, %v2, !dbg !64
  %memcheck.conflict = and i1 %bound0, %bound1, !dbg !64
  br i1 %memcheck.conflict, label %middle.block, label %vector.body.preheader, !dbg !64
```

This intimidating block of code just checks if the two input pointers ever clash.
`update_restrict` does not have this check since we defined the pointers as
`restrict`.
