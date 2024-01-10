run: main
	./main

debug:
	valgrind ./main

# main program
main: present24.o attaque_mid.o main.o
	gcc -Wall present24.o attaque_mid.o main.o -o main -lm

# compilation present24.c
present24.o: present24.c present24.h
	gcc -lm -c -Wall present24.c

# compilation attaque_mid.c
attaque_mid.o: attaque_mid.c attaque_mid.h
	gcc -c -lm -Wall attaque_mid.c

# compilation main.c
main.o: main.c attaque_mid.h present24.h
	gcc -lm -c -Wall main.c

clean: 
	rm -f main
	rm -f main.o
	rm -f present24.o
	rm -f attaque_mid.o
