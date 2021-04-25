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



// affiche en binaire :
void affichebin(unsigned n)
{
	unsigned bit = 0 ;
	unsigned mask = 1 ;
	for (int i = 0 ; i < 32 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
	printf("\n\n");
}

// fonction pour concaténer par 8 bits :
int concat_uint8(int m, int n)
{
	return (m << 8) | n;
}
// pour concaténer deux mots de quatre bits :
int concat(int m, int n)
{
	return (m << 4) | n;
}

// Effectue les trois étapes de Maj de la clef maître :
void mise_a_jour(uint8_t *clef, int tour)
{
	uint8_t Maj_clef[10]; // pour stocker la nouvelle clef
	// Maj de la clef maitre (pivot de 61 bits ):
	Maj_clef[9] = (clef[6] << 5) | (clef[7] >> 3);
	Maj_clef[8] = (clef[5] << 5) | (clef[6] >> 3);
	Maj_clef[7] = (clef[4] << 5) | (clef[5] >> 3);
	Maj_clef[6] = (clef[3] << 5) | (clef[4] >> 3);
	Maj_clef[5] = (clef[2] << 5) | (clef[3] >> 3);
	Maj_clef[4] = (clef[1] << 5) | (clef[2] >> 3);
	Maj_clef[3] = (clef[0] << 5) | (clef[1] >> 3);
	Maj_clef[2] = (clef[9] << 5) | (clef[0] >> 3);
	Maj_clef[1] = (clef[8] << 5) | (clef[9] >> 3);
	Maj_clef[0] = (clef[7] << 5) | (clef[8] >> 3);

	// substitution des quatre premiers bits : [79,78,77,76]
	int res1 = t2[Maj_clef[0] >> 4];
	Maj_clef[0] = (Maj_clef[0] & 0x0F) | (res1 << 4);

	// xor des bits [19, 18, 17, 16, 15] + numéro de tour (i)
	Maj_clef[7] ^= tour >> 1;
	Maj_clef[8] ^= tour << 7;

	// On stocke dans la clef maître les nouvelles valeurs
	clef[0] = Maj_clef[0];
	clef[1] = Maj_clef[1];
	clef[2] = Maj_clef[2];
	clef[3] = Maj_clef[3];
	clef[4] = Maj_clef[4];
	clef[5] = Maj_clef[5];
	clef[6] = Maj_clef[6];
	clef[7] = Maj_clef[7];
	clef[8] = Maj_clef[8];
	clef[9] = Maj_clef[9];
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

	for (int i = 3; i < 10; ++i)
		clef_maitre[i] = 0x00;		// on remplit le reste de la clef maître avec 0


	// calculer les sous_clefs
	for (int i = 1; i <= 11; ++i)
	{
		Ki = concat_uint8(clef_maitre[5], clef_maitre[6]);	// on prend les bits à la position : [39, 38, ..., 17, 16]
		Ki = concat_uint8(Ki, clef_maitre[7]);
		sous_clefs[i-1] = Ki;
		mise_a_jour(clef_maitre, i);
	}
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
int permutation3(int x)
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
		etat = clef_plus_etat(etat, sous_clefs[i]);
		etat = substitution(etat);
		etat = permutation3(etat);
	}

	printf("Tour (%d) : %X et %X\n", 10, etat, sous_clefs[10]);
	etat = clef_plus_etat(etat, sous_clefs[10]);
	printf("\nMessage chiffré : %X (16) - %d (10) \n\n", etat,etat);


	return 0;
}

int chiffrer_sansecrire(int mot, int cle_maitre)
{
	int etat = mot;
	algo_cadencement(cle_maitre);

	for (int i = 0; i < 10; ++i)
	{
		etat = clef_plus_etat(etat, sous_clefs[i]);
		etat = substitution(etat);
		etat = permutation3(etat);
	}
	etat = clef_plus_etat(etat, sous_clefs[10]);


	return etat;
}
