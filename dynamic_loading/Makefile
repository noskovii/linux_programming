exe: solution.c
	gcc solution.c -fPIC -ldl -o solution

all: exe lib

lib: hello.h hello.c
	gcc -shared hello.c -fPIC -o libHello.so

.PHONY: clean

clean:
	-rm solution libHello.so 2>/dev/null

