CFLAGS= -Wall -std=c99 -ansi -pedantic -O2  -lm
CC= gcc

ppm: ppm.c 
	${CC} -o $@ $^ ${CFLAGS}

clean: 
	rm -rf *.o *.gch ppm

run: ppm
	./ppm imagem.ppm saida.ppm 10 4
