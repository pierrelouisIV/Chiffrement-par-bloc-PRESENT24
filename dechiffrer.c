#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dechiffrer.h"

#define D 0
#define l_boite 16
#define l_permute 24

// variables globales :
int t1_dechiffrer[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};	// S(x)
int t2_dechiffrer[] = {0x5, 0xe, 0xf, 0x8, 0xc, 0x1, 0x2, 0xd, 0xb, 0x4, 0x6, 0x3, 0x0, 0x7, 0x9, 0xa};	// x

int P_dechiffrer[] = {0, 4, 8 ,12, 16, 20, 1, 5, 9, 13, 17, 21, 2, 6, 10, 14, 
 			18, 22, 3, 7, 11, 15, 19, 23};													// P_dechiffrer(i) -> i


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


// algorithme de recherche (recherche dans la boîte-S):
int recherche_dichotomique_2(int valeur, int borne_inf, int borne_sup)
{
	int milieu;
	if (borne_sup < borne_inf)
		return -1;
	else
	{
		milieu = (borne_inf+borne_sup) / 2;
		if (valeur == t1_dechiffrer[milieu])
			return milieu;
		else
		{
			if (valeur < t1_dechiffrer[milieu])
				return recherche_dichotomique_2(valeur, borne_inf, milieu-1);
			else
				return recherche_dichotomique_2(valeur, milieu+1, borne_sup);
		}
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
	int res1 = 0;
	int res2 = 0;
	int res3 = 0x0;
	int masque = 0xffffff;
	for (int i = 5; i >= 0; --i)
	{
		res1 = (m & masque) >> i*4;
		masque >>= 4;
		res2 = t2_dechiffrer[recherche_dichotomique_2(res1, D, l_boite)];
		res3 = concat_2(res3, res2);
	}
	return res3;
}


// pour transformer une suite de 0 et 1 en hexadecimal :
int calcul_binaire_en_hexa_2(int *tableau)
{
	int res1 = 0;
	int res2 = 0;
	int cpt = 0;
	int P_dechiffrer = 3;
	for (int i = 23; i >= -1; --i)
	{
		if(cpt == 4)
		{
			res2 = concat_2(res2, res1);
			cpt = 0;
			P_dechiffrer = 3;
			res1 = 0;
		}
		if (tableau[i])
			{
				res1 += pow(2,P_dechiffrer);
				cpt++;
				P_dechiffrer--;
			}
		else
		{
			cpt++;
			P_dechiffrer--;
		}
	}
	return res2;
}

// Etape 1 : la permutation
int permutation_inv(int n)
{
	int resultat = 0;
	int *nouveau = malloc(sizeof(int)*l_permute);
	for (int i = 0; i < l_permute; ++i)
		nouveau[i] = 0;

	int j = 0;
	int bit = 0;
	int masque = 1;
	for (int i = 0 ; i < 24 ; ++i)
	{
		bit = (n & masque) >> i ;
		masque <<= 1 ;
		nouveau[P_dechiffrer[j]] = bit;	// remplir tableau
		j++;
	}

	resultat = calcul_binaire_en_hexa_2(nouveau);
	free(nouveau);
	return resultat;
}

int dechiffrer(int mot_chiffre, int clef_maitre)
{
	int sous_clefs[] = {0x000000, 0x000000, 0x000001, 0x000001, 0x400062, 0x80002a,
						0xc00033, 0x40005b, 0x00064c, 0x800284, 0x400355};

	int etat = mot_chiffre;
	etat = clef_plus_etat_2(etat, sous_clefs[10]);
	printf("Tour (%d) : %X et %X\n", 10, etat, sous_clefs[10]);
	for (int i = 9; i >= 0; --i)
	{		
		etat = permutation_inv(etat);
		etat = substitution_inv(etat);
		etat = clef_plus_etat_2(etat, sous_clefs[i]);	
		printf("Tour (%d) : %X et %X\n", i, etat, sous_clefs[i]);
	}
	
	printf("\nLe mot clair est : %X (16) - %d (10)\n\n", etat, etat);
	return 0;
}
