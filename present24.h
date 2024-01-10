#ifndef H_PRESENT24
#define H_PRESENT24


#include "types.h"


// Fonctions pour générer les sous clefs :
void mise_a_jour(uint8_t *clef, int tour);
void algo_cadencement(int K);

// Etape 3 :
int permutation(int n);

// Etape 2 :
int substitution(int m);


int encrypt_print(int mot, int cle_maitre); //Main

int encrypt(int mot, int cle_maitre); //Main sans ecrire dans le terminal

// ------------------------------------- DECHIFFRER ---------------------------------------------------- //
// Fonctions pour générer les sous clefs :
void mise_a_jour_2(uint8_t *clef, int tour);
void algo_cadencement_2(int K);


// Etape 2
int substitution_inv(int m);

// Etape 1
int permutation_inv(int n);

int decrypt_print(int mot, int cle_maitre); //Main
int decrypt(int mot, int cle_maitre); //Main

#endif
