all: gpioexample.o
	cc -o gpioexample gpioexample.o
gpioexample.o: gpioexample.c
	cc -c gpioexample.c


