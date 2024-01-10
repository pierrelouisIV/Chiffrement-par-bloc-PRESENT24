#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

couple LM[MAX];			//couple chiffrement
couple LC[MAX];			//couple dechiffrement

couple LMChiffre1[MAX];

// Pointer function for qsort:
int compare_couple(const void* a, const void* b)
{
  couple *ca = (couple*) a;
  couple *cb = (couple*) b;
  return (ca->mot - cb->mot);
}

// function to print couple elements
void printArray(couple array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d-%d  ", array[i].mot,array[i].cle);
  }
  printf("\n");
}


void calcul_lm_lc(int mot, int chiffre)
{
	for(int i = 0; i < MAX; i++)
	{	
		LM[i].mot = encrypt(mot,i);
		LC[i].mot = decrypt(chiffre,i);
		
		LM[i].cle = i;
		LC[i].cle = i;
	}	
}

//Recherche dichotomique
int binarySearch(couple arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid].mot == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid].mot > x)
            return binarySearch(arr, l, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}


int attaque_mid()
{

	//Creation des listes
	clock_t tempscalc, temps1;
	temps1 = clock();
	calcul_lm_lc(M1,C1);
	tempscalc=clock();
	printf("Calcul des tableaux fini en %f s \n",(double) (tempscalc-temps1)/CLOCKS_PER_SEC);
	
	//Tri des listes (Quicksort)
	clock_t tempstri;
	int n = sizeof(LM) / sizeof(LM[0]);
  // use qsort:
  qsort(LM, MAX, sizeof(couple), compare_couple);
  qsort(LC, MAX, sizeof(couple), compare_couple);
	tempstri=clock();
	printf("Tri des tableaux fini en %f s \n",(double) (tempstri-tempscalc)/CLOCKS_PER_SEC);

	//Recherche element commun
	int j = 0;
    for(int i = 0; i < MAX; i++)
    {
        int test = binarySearch(LM,0,n-1,LC[i].mot); // On cherche si dans LM on trouve LC[i].mot
        if(test != -1)
        { 
			// On a une collision on sauvegarde donc les 2 clés de chaque tableau
            LMChiffre1[i].mot = LM[test].cle; 
            LMChiffre1[i].cle = LC[i].cle;
            
            j++;
        }
    }
    printf("Nombre de collisions trouvées : %d\n",j);
 
    
    printf("Utilisation de M2 et C2 pour trouver K1 et K2\n");
    
    for(int i = 0; i < MAX; i++)
    {
        int t1 = encrypt(M2,LMChiffre1[i].mot);
        int t2 = decrypt(C2,LMChiffre1[i].cle);
        
        if(t1 == t2)
        {
            printf("K1 = %x  -  K2 = %x\n",LMChiffre1[i].mot,LMChiffre1[i].cle);
        }   
    }
	return 0;
}
