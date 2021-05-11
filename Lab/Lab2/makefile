FLAGS = -g

all: fork_ex fork dfork fork-wait zombie shell

fork_ex: fork_ex.o
	gcc -o $@ $^

fork_ex.o: fork_ex.c
	gcc -c $^ -o $@

fork: fork.o
	gcc -o $@ $^

fork.o: fork.c
	gcc -c $^ -o $@

dfork: dfork.o
	gcc -o $@ $^

dfork.o: dfork.c
	gcc -c $^ -o $@

fork-wait: fork-wait.o
	gcc -o $@ $^

fork-wait.o: fork-wait.c
	gcc -c $^ -o $@

zombie: zombie.o
	gcc -o $@ $^

zombie.o: zombie.c
	gcc -c $^ -o $@

shell: shell.o
	gcc -o $@ $^

shell.o: shell.c
	gcc -c $^ -o $@

clean:
	rm -rf *.o fork_ex fork dfork fork-wait zombie shell