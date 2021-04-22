#ifndef H_CHIFFRER
#define H_CHIFFRER

typedef unsigned char uint8_t;

// Fonctions complémentaires :
void affichebin(unsigned n);
int concat(int m, int n);
int concat_uint8(int m, int n);

// Fonctions pour générer les sous clefs :
void mise_a_jour(uint8_t *clef, int tour);
void algo_cadencement(int K);

// Etape 3 :
int calcul_binaire_en_hexa(int *tableau);
int permutation(int n);

// Etape 2 :
int substitution(int m);

// Etape 1 :
int clef_plus_etat(int clef, int etat); // XOR

int chiffrer(int mot, int cle_maitre); //Main

#endif