CC=clang

default: realpath

realpath: realpath.c
	$(CC) -o realpath realpath.c -Werror -Weverything

clean:
	rm -f realpath
