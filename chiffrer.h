#ifndef H_CHIFFRER
#define H_CHIFFRER

// structure pour la clef maitre
typedef unsigned char uint8_t;


// Fonctions pour générer les sous clefs :
void mise_a_jour(uint8_t *clef, int tour);
void algo_cadencement(int K);

// Etape 3 :
int permutation(int n);

// Etape 2 :
int substitution(int m);


int chiffrer(int mot, int cle_maitre); //Main

int chiffrer_sansecrire(int mot, int cle_maitre); //Main sans ecrire dans le terminal

#endif
