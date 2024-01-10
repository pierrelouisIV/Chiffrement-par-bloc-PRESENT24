#ifndef H_ATTAQUE_MID
#define H_ATTAQUE_MID

#include "present24.h"

struct couple
{
    int mot;
    int cle;
};
typedef struct couple couple;

// qsort function pointer
int compare_couple(const void* a, const void* b);

void calcul_lm_lc(int mot, int chiffre);

int attaque_mid(); //Main

// recherche dicho
int binarySearch(couple arr[], int borne_inf, int borne_sup, int x);

//Fonctions de tri
void quickSort(couple array[], int low, int high);
int partition(couple array[], int low, int high);
void swap(couple *a, couple *b);


#endif
