all:
	gcc -Wall -Werror lsfunction.c lsadmin.c UnixLs.c -o UnixLs
demo:
	./UnixLs

valgrind-check:
	valgrind --leak-check=full ./UnixLs -lR . ~/sfuhome/cmpt-300 *

valgrind-show:
	valgrind --track-origins=yes ./UnixLs -liR .

sample-output:
	./UnixLs -i .

clean:
	rm -f UnixLs