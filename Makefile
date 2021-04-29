run: main
	./main

debug:
	valgrind ./main


#edition de lien
main:chiffrer.o dechiffrer.o attaque_mid.o main.o
	gcc -Wall chiffrer.o dechiffrer.o attaque_mid.o main.o -o main -lm -lpthread

#compilation de chiffrer.c
chiffrer.o: chiffrer.c chiffrer.h
	gcc -lm -c -Wall chiffrer.c
	
#compilation de dechiffrer.c
dechiffrer.o: dechiffrer.c dechiffrer.h
	gcc -c -lm -Wall dechiffrer.c

#compilation de attaque_mid.c
attaque_mid.o: attaque_mid.c attaque_mid.h
	gcc -c -lm -Wall attaque_mid.c

#compilation de main.c
main.o: main.c attaque_mid.h chiffrer.h dechiffrer.h
	gcc -lm -c -Wall main.c

clean: 
	rm -f main
	rm -f main.o
	rm -f chiffrer.o
	rm -f dechiffrer.o
	rm -f attaque_mid.o
