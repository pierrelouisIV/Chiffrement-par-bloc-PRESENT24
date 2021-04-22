#ifndef H_CHIFFRER
#define H_CHIFFRER


// Fonctions complémentaires :
void affichebin(unsigned n);
int concat(int m, int n);

// Etape 3 :
int calcul_binaire_en_hexa(int *tableau);
int permutation(int n);

// Etape 2 :
int substitution(int m);

// Etape 1 :
int clef_plus_etat(int clef, int etat); // XOR

int chiffrer(int mot, int cle_maitre); //Main

#endif