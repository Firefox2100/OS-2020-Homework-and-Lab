FLAGS = -g

all: Fibonacci_Threads Collatz_conjecture

Fibonacci_Threads: Fibonacci_Threads.o
	gcc -o $@ $^ -lpthread

Fibonacci_Threads.o: Fibonacci_Threads.c
	gcc -c $^ -o $@

Collatz_conjecture: Collatz_conjecture.o
	gcc -o $@ $^

Collatz_conjecture.o: Collatz_conjecture.c
	gcc -c $^ -o $@

clean:
	rm -rf *.o Fibonacci_Threads Collatz_conjecture