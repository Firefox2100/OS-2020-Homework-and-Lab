all: fdump file_stat traverse

fdump: hexdump.o fdump.o
	gcc -o $@ $^

fdump.o: fdump.c
	gcc -c -g $^ -o $@ -I../include

file_stat: file_stat.o
	gcc -o $@ $^

file_stat.o: file_stat.c
	gcc -c -g $^ -o $@

traverse: traverse.o
	gcc -o $@ $^

traverse.o: traverse.c
	gcc -c -g $^ -o $@

hexdump.o: hexdump.c
	gcc -c -g $^ -o $@ -I../include

clean:
	rm -rf *.o fdump file_stat traverse