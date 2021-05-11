all: memory-test frag-eval

memory-test: dlist.o dnode.o allocator.o memory-test.o
	gcc -o $@ $^

memory-test.o: memory-test.c
	gcc -c -g $^ -o $@ -I../include

frag-eval: dlist.o dnode.o allocator.o frag-eval.o
	gcc -o $@ $^

frag-eval.o: frag-eval.c
	gcc -c -g $^ -o $@ -I../include

allocator.o: allocator.c
	gcc -c -g $^ -o $@ -I../include

dlist.o: dlist.c
	gcc -c -g $^ -o $@ -I../include

dnode.o: dnode.c
	gcc -c -g $^ -o $@ -I../include

clean:
	rm -rf *.o memory-test frag-eval