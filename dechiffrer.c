#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dechiffrer.h"

#define D 0
#define l_boite 16
#define l_permute 24

// variables globales :	
int t2_dechiffrer[] = {0x5, 0xe, 0xf, 0x8, 0xc, 0x1, 0x2, 0xd, 0xb, 0x4, 0x6, 0x3, 0x0, 0x7, 0x9, 0xa};	// S(x) -> x


// pour stocker les sous clefs :
int sous_clefs_dechiffre[11]; 

// pour générer les sous clefs (boiteS non inversée):
int t2_2[] = {0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2};




// Fonctions complémentaires :

// affiche en binaire :
void affichebin_2(unsigned n)
{
	unsigned bit = 0 ;
	unsigned masque = 1 ;
	for (int i = 0 ; i < 32 ; ++i)
	{
		bit = (n & masque) >> i ;
		printf("%d", bit) ;
		masque <<= 1 ;
	}
	printf("\n\n");
}


// pour concaténer deux mots de quatre bits :
int concat_2(int m, int n)
{
	return (m << 4) | n;
}

// fonction pour concaténer par 8 bits :
int concat_uint8_2(int m, int n)
{
	return (m << 8) | n;
}

// Effectue les trois étapes de Maj de la clef maître :
void mise_a_jour_2(uint8_t *clef, int tour)
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
	int res1 = t2_2[Maj_clef[0] >> 4];
	Maj_clef[0] = (Maj_clef[0] & 0x0F) | (res1 << 4);

	// xor des bits [19, 18, 17, 16, 15] + numéro de tour (i)
	Maj_clef[7] ^= tour >> 1;
	Maj_clef[8] ^= tour << 7;

	// On stocke dans la clef maître les nouvelles valeurs :
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

// Fonction pour calculer et stocker les sous_clefs_dechiffre
void algo_cadencement_2(int K)
{
	int j = 10;
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


	// calculer les sous_clefs_dechiffre
	for (int i = 1; i <= 11; ++i)
	{
		Ki = concat_uint8_2(clef_maitre[5], clef_maitre[6]);	// on prend les bits à la position : [39, 38, ..., 17, 16]
		Ki = concat_uint8_2(Ki, clef_maitre[7]);
		sous_clefs_dechiffre[j] = Ki;
		mise_a_jour_2(clef_maitre, i);
		j--;
	}
}

// Etape 3 : xor de la clef et de l'etat
int clef_plus_etat_2(int clef, int etat)
{
	return clef ^ etat;
}



//Etape 2 : la boîte-S 
int substitution_inv(int m)
{
	m = t2_dechiffrer[m >> 20] << 20
		| t2_dechiffrer[(m & 0x0f0000) >> 16] << 16
		| t2_dechiffrer[(m & 0x00f000) >> 12] << 12
		| t2_dechiffrer[(m & 0x000f00) >>  8] <<  8
		| t2_dechiffrer[(m & 0x0000f0) >>  4] <<  4
		| t2_dechiffrer[(m & 0x00000f)];
	return m;
}

// Etape 1 : la permutation
int permutation_inv3(int x)
{
	x = (x & 0x00800001)
  | ((x & 0x00000100) << 1)
  | ((x & 0x00010000) << 2)
  | ((x & 0x00000002) << 3)
  | ((x & 0x00000200) << 4)
  | ((x & 0x00020000) << 5)
  | ((x & 0x00000004) << 6)
  | ((x & 0x00000400) << 7)
  | ((x & 0x00000008) << 9)
  | ((x & 0x00000800) << 10)
  | ((x & 0x00000010) << 12)
  | ((x & 0x00000020) << 15)
  | ((x & 0x00040000) >> 15)
  | ((x & 0x00080000) >> 12)
  | ((x & 0x00001000) >> 10)
  | ((x & 0x00100000) >> 9)
  | ((x & 0x00002000) >> 7)
  | ((x & 0x00200000) >> 6)
  | ((x & 0x00000040) >> 5)
  | ((x & 0x00004000) >> 4)
  | ((x & 0x00400000) >> 3)
  | ((x & 0x00000080) >> 2)
  | ((x & 0x00008000) >> 1);
	return x;
}

int dechiffrer(int mot_chiffre, int clef_maitre)
{
	int etat = mot_chiffre;
	algo_cadencement_2(clef_maitre);

	etat = clef_plus_etat_2(etat, sous_clefs_dechiffre[0]);
	printf("Tour (%d) : %X et %X\n", 0, etat, sous_clefs_dechiffre[0]);
	for (int i = 1; i < 11; ++i)
	{		
		etat = permutation_inv3(etat);
		etat = substitution_inv(etat);
		etat = clef_plus_etat_2(etat, sous_clefs_dechiffre[i]);	
		printf("Tour (%d) : %X et %X\n", i, etat, sous_clefs_dechiffre[i]);
	}
	
	printf("\nLe mot clair est : %X (16) - %d (10)\n\n", etat, etat);
	return 0;
}

int dechiffrer_sansecrire(int mot_chiffre, int clef_maitre)
{
	int etat = mot_chiffre;
	algo_cadencement_2(clef_maitre);

	etat = clef_plus_etat_2(etat, sous_clefs_dechiffre[0]);
	for (int i = 1; i < 11; ++i)
	{		
		etat = permutation_inv3(etat);
		etat = substitution_inv(etat);
		etat = clef_plus_etat_2(etat, sous_clefs_dechiffre[i]);	
	}
	return etat;
}
