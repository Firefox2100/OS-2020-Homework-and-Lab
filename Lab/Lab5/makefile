all: Prod_com Dining_Philosophers Prod_com _circle Barber

Prod_com: Prod_com.o
	gcc -o $@ $^ -lpthread

Prod_com.o: Prod_com.c
	gcc -c -g $^ -o $@

Prod_com_circle: Prod_com_circle.o
	gcc -o $@ $^ -lpthread

Prod_com_circle.o: Prod_com_circle.c
	gcc -c -g $^ -o $@

Dining_Philosophers: Dining_Philosophers.o
	gcc -o $@ $^ -lpthread

Dining_Philosophers.o: Dining_Philosophers.c
	gcc -c -g $^ -o $@

Barber: Barber.o
	gcc -o $@ $^ -lpthread

Barber.o: Barber.c
	gcc -c -g $^ -o $@

clean:
	rm -rf *.o Prod_com Dining_Philosophers Prod_com_circle Barber