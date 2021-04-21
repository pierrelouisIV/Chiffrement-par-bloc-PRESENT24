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
		printf("- Chiffrement(1) : mot \n- Dechiffrement(2) : mot chiffré + clé maitre\n- Attque par le milieu(3) : \n");
	
		int choice;
		scanf("%d", &choice);
		int state = 0;
		if(choice == 1)
		{
			printf("CHIFFREMENT\n");
			printf("Veuillez rentrer votre mot (entier)\n");
			int mot;
			scanf("%d", &mot);
			chiffrer(mot);
		
			printf("Voulez vous recommencer(1) ou quitter (0)\n");
			int choice1;
			scanf("%d", &choice1);
			if(choice1 == 0)
				break;
			
		}
		if (choice == 2)
		{
			//Appel de dechiffrement
		}
		if(choice == 3)
		{
			//Appel de l'attaque par le milieu
		}
	}
	
	
	
	
	return 0;
}
