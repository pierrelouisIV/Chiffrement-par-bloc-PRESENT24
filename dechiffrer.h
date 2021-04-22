#ifndef H_DECHIFFRER
#define H_DECHIFFRER


// Fonctions complémentaires :
void affichebin(unsigned n); 
int concat_2(int m, int n);
int concat_uint8(int m, int n)

// Fonctions pour générer les sous clefs :
void mise_a_jour(uint8_t *clef, int tour);
void algo_cadencement(int K);

// Etape 3
int clef_plus_etat_2(int clef, int etat); // XOR

// Etape 2
int substitution_inv(int m);

// Etape 1
int calcul_binaire_en_hexa_2(int *tableau);
int permutation_inv(int n);

int dechiffrer(int mot, int cle_maitre); //Main

#endif
