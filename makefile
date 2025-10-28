all: compila

compila: main.o estatistica.o lista.o
	gcc main.o estatistica.o lista.o -o prog -lm

main.o: main.c
	gcc -c main.c

estatistica.o: estatistica.c
	gcc -c estatistica.c

lista.o: lista.c
	gcc -c lista.c

rm:
	rm main.o estatistica.o lista.o prog
