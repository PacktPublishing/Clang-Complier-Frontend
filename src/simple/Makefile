CLANG=~/works/myown/clangbook/llvm-project/build/bin/clang

fib: fib.cpp
	$(CLANG) -c fib.cpp -o fib.o

main: main.cpp
	$(CLANG) -g main.cpp -o main -lstdc++

all: main fib

clean:
	rm -rf *~ *.dSYM *.pch main *.o
