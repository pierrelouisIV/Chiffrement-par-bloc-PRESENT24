#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define D 0
#define l_boite 16
#define l_permute 24
// variables globales de la boîte-S
 int t1[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
 int t2[] = {0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2};
// variable globale permutation :
 int P[] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4,
 			 10, 16, 22, 5, 11, 17, 23};



// etape une : le Xor clef + etat
int clef_plus_etat(int clef, int etat)
{
	return clef ^ etat;
}

// pour concaténer deux mots de quatre bits :
int concat(int m, int n)
{
	return (m << 4) | n;
}


// algorithme de recherche :
int recherche_dichotomique(int valeur, int borne_inf, int borne_sup)
{
	int milieu;
	if (borne_sup < borne_inf)
		return -1;
	else
	{
		milieu = (borne_inf+borne_sup) / 2;
		if (valeur == t1[milieu])
			return milieu;
		else
		{
			if (valeur < t1[milieu])
				return recherche_dichotomique(valeur, borne_inf, milieu-1);
			else
				return recherche_dichotomique(valeur, milieu+1, borne_sup);
		}
	}
}


// la boîte-S 
int substitution(int m)
{
	int res1 = 0;
	int res2 = 0;
	int res3 = 0x0;
	int masque = 0xffffff;
	for (int i = 5; i >= 0; --i)
	{
		res1 = (m & masque) >> i*4;
		masque >>= 4;
		res2 = t2[recherche_dichotomique(res1, D, l_boite)];
		res3 = concat(res3, res2);
	}
	return res3;
}

// pour transformer une suite de 0 et 1 en hexadecimal :
int calcul_binaire_en_hexa(int *tableau)
{
	int res1 = 0;
	int res2 = 0;
	int cpt = 0;
	int p = 3;
	for (int i = 23; i >= -1; --i)
	{
		if(cpt == 4)
		{
			res2 = concat(res2, res1);
			cpt = 0;
			p = 3;
			res1 = 0;
		}
		if (tableau[i])
			{
				res1 += pow(2,p);
				cpt++;
				p--;
			}
		else
		{
			cpt++;
			p--;
		}
	}
	return res2;
}


// etape 2 : la permutation
int permutation(int n)
{
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
		nouveau[P[j]] = bit;	// remplir tableau
		j++;
	}
	return calcul_binaire_en_hexa(nouveau);
}


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


int main(int argc, char const *argv[])
{
	// %X affiche la valeur en hexadecimal


	int K = 0x000000;	// la clef maître
	int m = 0x000000;	// message clair

	int etat = m;
	int sous_clefs[] = {0x000000, 0x000000, 0x000001, 0x000001, 0x400062, 0x80002a,
						0xc00033, 0x40005b, 0x00064c, 0x800284, 0x400355};

	for (int i = 0; i < 10; ++i)
	{
		printf("%X et %X\n", etat, sous_clefs[i]);
		etat = clef_plus_etat(etat, sous_clefs[i]);
		etat = substitution(etat);
		etat = permutation(etat);
	}

	etat = clef_plus_etat(etat, sous_clefs[10]);
	printf("%X\n", etat);


	// pour K :
	// K de 80 bits = K <<= 28 bits
	//		 puis   = K >>= 28 bits

	// pour mettre à jour K : r1 = K << 61 bits
	//  puis 				  r2 = K >> 19 bits
	//	puis 			K = concat_80(r1,r2)

	return 0;
}