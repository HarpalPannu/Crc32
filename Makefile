main: crc.o main.c
	@echo [*]Building Main
	gcc -o main main.c crc.o -lpthread

crc.o: crc.c crc.h
	@echo [*]Building crc.o
	gcc -c crc.c -o crc.o 

clean:
	@echo [*]Cleaning Project Dir
	rm -f crc.o main

run: main
	@echo [*] Runing main...
	./main

clear:
	clear