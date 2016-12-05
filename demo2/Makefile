CC=clang
FLAGS=-O3 -msse3 -ftree-vectorize
PASSES=-Rpass=loop-vectorize -Rpass-analysis=loop-vectorize -Rpass-missed=loop-vectorize -ffast-math

.PHONY: all clean

demo: 
	${CC} ${FLAGS} ${PASSES} demo2.c -o demo

# Builds LLVM IR.
llvm:
	${CC} ${FLAGS} ${PASSES} demo2.c -S -emit-llvm

# Builds x86 Assembly.
asm:
	${CC} ${FLAGS} ${PASSES} demo2.c -S

# Clean up.
clean:
	rm -rf demo *.ll *.s
