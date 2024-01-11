#include <stdio.h>
#include <stdlib.h>
#include "attaque_mid.h"

const char banniere[] =
	"\n"
	"\n"
	"\t	    dMMMMb  dMMMMb  dMMMMMP .dMMMb  dMMMMMP dMMMMb dMMMMMMP            .aMMMb  dMP dMMMMb  dMP dMP dMMMMMP dMMMMb \n"
	"\t	   dMP.dMP dMP.dMP dMP     dMP' VP dMP     dMP dMP   dMP              dMP'VMP amr dMP.dMP dMP dMP dMP     dMP.dMP \n"
	"\t	  dMMMMP' dMMMMK' dMMMP    VMMMb  dMMMP   dMP dMP   dMP              dMP     dMP dMMMMP' dMMMMMP dMMMP   dMMMMK'  \n"
	"\t	 dMP     dMP'AMF dMP     dP .dMP dMP     dMP dMP   dMP              dMP.aMP dMP dMP     dMP dMP dMP     dMP'AMF   \n"
	"\t	dMP     dMP dMP dMMMMMP  VMMMP' dMMMMMP dMP dMP   dMP               VMMMP' dMP dMP     dMP dMP dMMMMMP dMP dMP    \n"
	"\n"
	"\n"                                         
	"\t							Tool for present 24 cipher v1.2						  \n"                                         
    "\n"                                             
;

int main(int argc, char **argv)
{
	int boucle = 1;
	while(boucle)
	{
		system("clear");
		printf("%s", banniere);
		printf("Veuillez choisir : \n");
		printf("- Chiffrement(1) : mot \n- Dechiffrement(2) : mot chiffré + clé maitre\n- Attaque par le milieu(3) : mot clair + mot chiffrer\n");
		printf("- Quitter(4)\n");
		int choix, choice1;
		uint32_t mot, cle;
		scanf("%d", &choix);
		switch (choix) {
			case 1:
				printf("CHIFFREMENT\n");
				printf("Veuillez rentrer votre mot (base 16)\n");
				//int mot;
				scanf("%X", &mot);
				printf("Veuillez rentrer votre clé maitre (base 16)\n");
				//int cle;
				scanf("%X", &cle);
				printf("\n");
				encrypt_print(mot,cle);
		
				printf("Voulez vous recommencer(1) ou quitter (0)\n");
				//int choice1;
				scanf("%d", &choice1);
				if(choice1 == 0)
					boucle = 0;
				break;
			case 2:
				printf("DECHIFFREMENT\n");
				printf("Veuillez rentrer votre mot chiffrer (base 16)\n");
				//int mot;
				scanf("%X", &mot);
				printf("Veuillez rentrer votre clé maitre (base 16)\n");
				//int cle;
				scanf("%X", &cle);
				printf("\n");
				decrypt_print(mot,cle);
		
				printf("Voulez vous recommencer(1) ou quitter (0)\n");
				//int choice1;
				scanf("%d", &choice1);
				if(choice1 == 0)
					boucle = 0;
				break;
			case 3:
				printf("ATTAQUE PAR LE MILIEU (sans threads) \n");
				printf("Veuillez patienter\n");
				attaque_mid();
				printf("Voulez vous recommencer(1) ou quitter (0)\n");
				//int choice1;
				scanf("%d", &choice1);
				if(choice1 == 0)
					boucle = 0;
				break;
			case 4:
				boucle = 0;
				break;
			default:
				printf("Veuillez donner un bon paramètre \n");
				break;
		}
	}
	//
	return 0;
}
