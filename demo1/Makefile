CC=clang
FLAGS=-O3 -msse3 -ftree-vectorize
PASSES=-Rpass=loop-vectorize -Rpass-analysis=loop-vectorize -Rpass-missed=loop-vectorize -ffast-math

.PHONY: all clean

# Builds LLVM IR.
llvm:
	${CC} ${FLAGS} ${PASSES} simd_demo.c -S -emit-llvm

# Builds x86 Assembly.
asm:
	${CC} ${FLAGS} ${PASSES} simd_demo.c -S

# Clean up.
clean:
	rm -rf demo1 *.ll *.s
