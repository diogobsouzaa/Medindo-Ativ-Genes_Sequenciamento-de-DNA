all: main

run:
	./main

main : main.o proj_digitos.o
	gcc -o main main.o proj_digitos.o

proj_digitos.o : proj_digitos.c
	gcc -o proj_digitos.o -c proj_digitos.c 

main.o : main.c
	gcc -o main.o -c main.c

clean:
	rm Main
	rm Main.o
	rm proj_digitos.o