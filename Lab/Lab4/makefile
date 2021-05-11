all: statistics sum_serial sum_pthread summation

statistics: statistics.o
	gcc -o $@ $^ -lpthread

statistics.o: statistics.c
	gcc -c $^ -o $@

sum_serial: sum_serial.o
	gcc -o $@ $^

sum_serial.o: sum_serial.c
	gcc -c $^ -o $@

sum_pthread: sum_pthread.o
	gcc -o $@ $^ -lpthread

sum_pthread.o: sum_pthread.c
	gcc -c $^ -o $@

summation: summation.o
	gcc -o $@ $^ -lpthread

summation.o: summation.c
	gcc -c $^ -o $@

clean:
	rm -rf *.o statistics sum_serial sum_pthread summation