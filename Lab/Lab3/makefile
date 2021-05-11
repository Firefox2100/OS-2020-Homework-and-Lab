FLAGS = -g

all: Shared_Memory pipes pipe_test upper fifo

fifo: fifo_client fifo_server

Shared_Memory: Shared_Memory.o
	gcc -o $@ $^ -lrt

Shared_Memory.o: Shared_Memory.c
	gcc -c $^ -o $@

pipes: pipes.o
	gcc -o $@ $^

pipes.o: pipes.c
	gcc -c $^ -o $@

pipe_test: pipe_test.o
	gcc -o $@ $^

pipe_test.o: pipe_test.c
	gcc -c $^ -o $@

upper: upper.o
	gcc -o $@ $^

upper.o: upper.c
	gcc -c $^ -o $@

fifo_server: fifo_server.o
	gcc -o $@ $^

fifo_server.o: fifo_server.c
	gcc -c $^ -o $@

fifo_client: fifo_client.o
	gcc -o $@ $^

fifo_client.o: fifo_client.c
	gcc -c $^ -o $@

clean:
	rm -rf *.o Shared_Memory pipes pipe_test upper fifo_server fifo_client