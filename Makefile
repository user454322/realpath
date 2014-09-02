CC=clang

default: realpath

realpath: realpath.c
	$(CC) -o realpath realpath.c

clean:
	rm -f realpath
