all: process_schedule safety bankers

process_schedule: process_schedule.o
	gcc -o $@ $^

process_schedule.o: process_schedule.c
	gcc -c -g $^ -o $@

safety: safety.o
	gcc -o $@ $^

safety.o: safety.c
	gcc -c -g $^ -o $@

bankers: bankers.o
	gcc -o $@ $^ -lpthread

bankers.o: bankers.c
	gcc -c -g $^ -o $@

clean:
	rm -rf *.o process_schedule safety bankers