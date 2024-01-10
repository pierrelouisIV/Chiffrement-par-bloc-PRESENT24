#include <stdio.h>
#include <stdlib.h>
#include "attaque_mid.h"

int main(int argc, char **argv)
{
	printf(" ------ PRESENT24 ------ \n");
	while(1)
	{
		printf("Veuillez choisir : \n");
		printf("- Chiffrement(1) : mot \n- Dechiffrement(2) : mot chiffré + clé maitre\n- Attaque par le milieu(3) : mot clair + mot chiffrer\n");
	
		int choice;
		scanf("%d", &choice);
		if(choice == 1)
		{
			printf("CHIFFREMENT\n");
			printf("Veuillez rentrer votre mot (base 16)\n");
			int mot;
			scanf("%X", &mot);
			printf("Veuillez rentrer votre clé maitre (base 16)\n");
			int cle;
			scanf("%X", &cle);
			printf("\n");
			encrypt_print(mot,cle);
		
			printf("Voulez vous recommencer(1) ou quitter (0)\n");
			int choice1;
			scanf("%d", &choice1);
			if(choice1 == 0)
				break;
			
		}
		if (choice == 2)
		{
			printf("DECHIFFREMENT\n");
			printf("Veuillez rentrer votre mot chiffrer (base 16)\n");
			int mot;
			scanf("%X", &mot);
			printf("Veuillez rentrer votre clé maitre (base 16)\n");
			int cle;
			scanf("%X", &cle);
			printf("\n");
			decrypt_print(mot,cle);
		
			printf("Voulez vous recommencer(1) ou quitter (0)\n");
			int choice1;
			scanf("%d", &choice1);
			if(choice1 == 0)
				break;
		}
		if(choice == 3)
		{
			printf("ATTAQUE PAR LE MILIEU (sans threads) \n");
			printf("Veuillez patienter\n");
			attaque_mid();
			printf("Voulez vous recommencer(1) ou quitter (0)\n");
			int choice1;
			scanf("%d", &choice1);
			if(choice1 == 0)
				break;
		}
	}
	//
	return 0;
}
