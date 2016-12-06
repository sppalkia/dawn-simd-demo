demo2
===

Implements a simple reduction with a branch using Intel intrinsics.

See [this](https://software.intel.com/sites/landingpage/IntrinsicsGuide/) link for the authoratitive source on the intrinsics.
Some might not be available for your computer. As a set of general guidelines:

* You almost certainly have SSE, SSE2, SSE3, and SSE4.1/4.2.
* The SVML functions are available on most computers.
* Computers after around 2013 will have AVX.
* Computers after around 2015 will have AVX2.

##Explanation of `demo2.c`

`sum_large_floats_vectorized` vectorizes `sum_large_floats` using
the following steps:

1. Load four values into a register (`_mm_loadu_ps`).
2. Compare the four values with the cutoff to create a mask (`_mm_cmpge_ps`). If the
comparison is true, the instruction writes `0xffffffff` into the corresponding
output vector lane. Otherwise, it writes `0`.
3. `AND` the mask with the loaded data (`_mm_and_ps`) to elimate elements that didn't pass the
comparison.
4. Add the masked data into `sum` (`_mm_add_ps`), which keeps the aggregate.
5. After the loop, handle any fringing (in case the array size isn't a multiple
of the vector size).
6. Store the values from the `sum` register into a `float[4]` (`_mm_store_ps`)and sum them up,
adding them to the result.

This is a very simple SIMD-enabled function; for simple straight line code like
this, a good strategy is to load your data into a SIMD variable (e.g.,
`__m128`, but there are others), do some computation with it, and then store it
back to read the result. Avoid casting vector types to other types.
