CC=clang

default: realpath

realpath: realpath.c
	$(CC) -o realpath realpath.c -Werror -Weverything

clean:
	rm -f realpath
	rm -fr test_files_*

test:
	./test.sh

