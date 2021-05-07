#ifndef H_DECHIFFRER
#define H_DECHIFFRER

// structure pour la clef maitre
typedef unsigned char uint8_t;


// Fonctions pour générer les sous clefs :
void mise_a_jour_2(uint8_t *clef, int tour);
void algo_cadencement_2(int K);


// Etape 2
int substitution_inv(int m);

// Etape 1
int permutation_inv(int n);

int dechiffrer(int mot, int cle_maitre); //Main
int dechiffrer_sansecrire(int mot, int cle_maitre); //Main
#endif
