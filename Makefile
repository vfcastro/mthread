all: mdata.o mthread.o
	ar crs lib/libmthread.a bin/mthread.o bin/mdata.o

mthread.o: src/mthread.c
	gcc -g -lrt -o bin/mthread.o -c src/mthread.c

mdata.o: src/mdata.c
	gcc -g -o bin/mdata.o -c src/mdata.c

clean:
	rm  lib/*.a bin/*.o
