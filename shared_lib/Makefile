lib: solution.h solution.c
	gcc -shared solution.c -fPIC -o libsolution.so

exe: solution.h main.c lib
	gcc main.c -fPIC -L. -lsolution -o solution

.PHONY: clean

clean:
	rm solution libsolution.so 2>/dev/null
