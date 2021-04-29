#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "chiffrer.h"

#define D 0
#define l_boite 16
#define l_permute 24


// variables globales de la boîte-S
 int t2[] = {0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2};  //  S(x)


// pour stocker les sous_clefs
int sous_clefs[11];


// Effectue les trois étapes de Maj de la clef maître :
void mise_a_jour(uint8_t *clef, int tour)
{
	uint8_t Maj_clef[3]; // pour stocker la temporairement la clef
	Maj_clef[2] = clef[9];
	Maj_clef[1] = clef[8];
	Maj_clef[0] = clef[7]; 
	
	// Maj de la clef maitre (pivot de 61 bits ):
	clef[9] = (clef[6] << 5) | (clef[7] >> 3);
	clef[8] = (clef[5] << 5) | (clef[6] >> 3);
	clef[7] = (clef[4] << 5) | (clef[5] >> 3);
	clef[6] = (clef[3] << 5) | (clef[4] >> 3);
	clef[5] = (clef[2] << 5) | (clef[3] >> 3);
	clef[4] = (clef[1] << 5) | (clef[2] >> 3);
	clef[3] = (clef[0] << 5) | (clef[1] >> 3);
	clef[2] = (Maj_clef[2] << 5) | (clef[0] >> 3);
	clef[1] = (Maj_clef[1] << 5) | (Maj_clef[2] >> 3);
	clef[0] = (Maj_clef[0] << 5) | (Maj_clef[1] >> 3);

	// substitution des quatre premiers bits : [79,78,77,76]
	clef[0] = (clef[0] & 0x0F) | (t2[clef[0] >> 4] << 4);

	// xor des bits [19, 18, 17, 16, 15] + numéro de tour (i)
	clef[7] ^= tour >> 1;
	clef[8] ^= tour << 7;
}

// Fonction pour calculer et stocker les sous_clefs
void algo_cadencement(int K)
{
	int Ki = 0;					// la clef Ki au tour i :
	uint8_t clef_maitre[10];	// 10 paquets de 8 bits pour stocker la clef maitre de 80bits

	// Initialisation de la clef
	clef_maitre[0] = (K >> 16);	// on prend les 8 premiers bits
	K <<= 8;
	clef_maitre[1] = K >> 16;	// on prend les 8 bits suivants
	K <<= 8;
	clef_maitre[2] = K >> 16;	// on prend les 8 derniers bits de la clef
	
	// on remplit le reste de la clef maître avec 0
	clef_maitre[3] = 0;
	clef_maitre[4] = 0;
	clef_maitre[5] = 0;
	clef_maitre[6] = 0;
	clef_maitre[7] = 0;
	clef_maitre[8] = 0;
	clef_maitre[9] = 0;	
	
	// on remplit le tableau des sous-clefs :
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[0] = Ki;
	mise_a_jour(clef_maitre, 1);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[1] = Ki;
	mise_a_jour(clef_maitre, 2);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[2] = Ki;
	mise_a_jour(clef_maitre, 3);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[3] = Ki;
	mise_a_jour(clef_maitre, 4);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[4] = Ki;
	mise_a_jour(clef_maitre, 5);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[5] = Ki;
	mise_a_jour(clef_maitre, 6);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[6] = Ki;
	mise_a_jour(clef_maitre, 7);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[7] = Ki;
	mise_a_jour(clef_maitre, 8);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[8] = Ki;
	mise_a_jour(clef_maitre, 9);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[9] = Ki;
	mise_a_jour(clef_maitre, 10);
	Ki = ((clef_maitre[5] << 8) | clef_maitre[6]) << 8 | clef_maitre[7];
	sous_clefs[10] = Ki;
	mise_a_jour(clef_maitre, 11);
}


// Etape 1 : le Xor clef + etat
int clef_plus_etat(int clef, int etat)
{
	return clef ^ etat;
}


// Etape 2 : la boîte-S 
int substitution(int m)
{
	m = t2[(m >> 20)] << 20
		| t2[(m & 0x0f0000) >> 16] << 16
		| t2[(m & 0x00f000) >> 12] << 12
		| t2[(m & 0x000f00) >>  8] <<  8
		| t2[(m & 0x0000f0) >>  4] <<  4
		| t2[(m & 0x00000f)];
	return m;
}

// Etape 3 : la permutation
int permutation(int x)
{
	x = (x & 0x00800001)
  | ((x & 0x00004000) << 1)
  | ((x & 0x00000020) << 2)
  | ((x & 0x00080000) << 3)
  | ((x & 0x00000400) << 4)
  | ((x & 0x00000002) << 5)
  | ((x & 0x00008000) << 6)
  | ((x & 0x00000040) << 7)
  | ((x & 0x00000800) << 9)
  | ((x & 0x00000004) << 10)
  | ((x & 0x00000080) << 12)
  | ((x & 0x00000008) << 15)
  | ((x & 0x00100000) >> 15)
  | ((x & 0x00010000) >> 12)
  | ((x & 0x00200000) >> 10)
  | ((x & 0x00001000) >> 9)
  | ((x & 0x00020000) >> 7)
  | ((x & 0x00000100) >> 6)
  | ((x & 0x00400000) >> 5)
  | ((x & 0x00002000) >> 4)
  | ((x & 0x00000010) >> 3)
  | ((x & 0x00040000) >> 2)
  | ((x & 0x00000200) >> 1);
	return x;
}


int chiffrer(int mot, int cle_maitre)
{
	// %X affiche la valeur en hexadecimal

	int etat = mot;
	algo_cadencement(cle_maitre);

	for (int i = 0; i < 10; ++i)
	{
		printf("Tour (%d) : %X et %X\n", i, etat, sous_clefs[i]);
		etat ^= sous_clefs[i];
		etat = substitution(etat);
		etat = permutation(etat);
	}

	printf("Tour (%d) : %X et %X\n", 10, etat, sous_clefs[10]);
	etat ^= sous_clefs[10];
	printf("\nMessage chiffré : %X (16) - %d (10) \n\n", etat,etat);


	return 0;
}

int chiffrer_sansecrire(int mot, int cle_maitre)
{
	int etat = mot;
	algo_cadencement(cle_maitre);

	for (int i = 0; i < 10; ++i)
	{
		etat ^= sous_clefs[i];
		etat = substitution(etat);
		etat = permutation(etat);
	}
	etat ^= sous_clefs[10];


	return etat;
}
