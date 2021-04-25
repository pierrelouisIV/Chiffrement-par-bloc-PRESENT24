#include "attaque_mid.h"
#include <time.h>

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

// function to swap elements
void swap(couple *a, couple *b) {
  couple t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(couple array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high].mot;
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j].mot <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(couple array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

// function to print couple elements
void printArray(couple array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%ld-%ld  ", array[i].mot,array[i].cle);
  }
  printf("\n");
}

void calcul_lm_lc(int mot, int chiffre)
{
	for(int i = 0; i < MAX; i++)
	{	
		LM[i].mot = chiffrer_sansecrire(mot,i);
		LC[i].mot = dechiffrer_sansecrire(chiffre,i);
		
		LM[i].cle = i;
		LC[i].cle = i;
	}	
}

//Recherche dichotomique
int binarySearch(couple arr[], int l, int r, uint32_t x)
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
	quickSort(LM, 0, n - 1);
	quickSort(LC, 0, n - 1);
	tempstri=clock();
	printf("Tri des tableaux fini en %f s \n",(double) (tempstri-tempscalc)/CLOCKS_PER_SEC);
	
	//Recherche element commun
	couple LMLC1[MAX];
	int j = 0;
    for(int i = 0; i < MAX; i++)
    {
        int LMLC1 = binarySearch(LM,0,n-1,LC[i].mot);
        if(LMLC1 != -1)
        { 
            LMLC1[i].mot = LM[i].cle; 
            LMLC1[i].cle = LC[i].cle;
            j++;
        }
    }
    printf("Nombre de collision trouvé : %d\n",j);
    
    printf("Utilisation de M2 et C2 pour trouver K1 et K2\n");
    
    for(int i = 0; i < MAX; i++)
    {
        int t1 = chiffrer_sansecrire(M2,LMLC1[i].mot);
        int t2 = dechiffrer_sansecrire(C2,LMLC1[i].cle);
        
        if(t1 == t2)
        {
            printf("K1 = %ld  -  K2 = %ld\n",LMLC1[i].mot,LMLC1[i].cle);
        }
        
    }
	printf("%d\n",j);
	
	
	return 0;
}
