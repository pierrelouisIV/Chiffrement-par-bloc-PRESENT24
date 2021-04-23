#include "attaque_mid.h"

// taille des listes Lm et LC
#define MAX 16777216
// premier couple clair-chiffré
#define M1 0x444b7a
#define C1 0x114c98
// deuxième couple clair-chiffré
#define M2 0xcf31f2
#define C2 0x4ba36f

// variables globales :

int LM[MAX];			//mot clair
int LC[MAX];			//mot chiffre



void calcul_lm_lc(int mot, int chiffre)
{
	
	for(int i = 0; i < MAX; i++)
	{	
		LM[i] = chiffrer_sansecrire(mot,i);
		LC[i] = dechiffrer_sansecrire(chiffre,i);
		//printf("\nMessage chiffré (%d) : %X (16)\n\n", i,LM[i]);
		printf("%d\n",i);
	}
	
	printf("Done\n");
	
}





int attaque_mid()
{
	calcul_lm_lc(M1,C1);
	
	
	
	
	
	return 0;
}
