#include "stdio.h"
#include <stdio.h>
#include "dechiffrer.h"
#include "chiffrer.h"
#include "attaque_mid.h"

int main()
{
	printf("Bienvenue sur le logiciel de chiffrement et dechiffrement PRESENT24 \n");
	
	
	while(1)
	{
		printf("Veuillez choisir : \n");
		printf("- Chiffrement(1) : mot \n- Dechiffrement(2) : mot chiffré + clé maitre\n- Attaque par le milieu(3) : mot clair + mot chiffrer\n");
	
		int choice;
		scanf("%d", &choice);
		if(choice == 1)
		{
			system("clear");
			printf("CHIFFREMENT\n");
			printf("Veuillez rentrer votre mot (base 16)\n");
			int mot;
			scanf("%X", &mot);
			printf("Veuillez rentrer votre clé maitre (base 16)\n");
			int cle;
			scanf("%X", &cle);
			printf("\n");
			chiffrer(mot,cle);
		
			printf("Voulez vous recommencer(1) ou quitter (0)\n");
			int choice1;
			scanf("%d", &choice1);
			if(choice1 == 0)
				break;
			
		}
		if (choice == 2)
		{
			system("clear");
			printf("DECHIFFREMENT\n");
			printf("Veuillez rentrer votre mot chiffrer (base 16)\n");
			int mot;
			scanf("%X", &mot);
			printf("Veuillez rentrer votre clé maitre (base 16)\n");
			int cle;
			scanf("%X", &cle);
			printf("\n");
			dechiffrer(mot,cle);
		
			printf("Voulez vous recommencer(1) ou quitter (0)\n");
			int choice1;
			scanf("%d", &choice1);
			if(choice1 == 0)
				break;
		}
		if(choice == 3)
		{
			system("clear");
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
	
	
	
	
	return 0;
}
