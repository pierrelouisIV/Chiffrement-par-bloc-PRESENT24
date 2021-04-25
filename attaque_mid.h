#ifndef H_ATTAQUE_MID
#define H_ATTAQUE_MID
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "chiffrer.h"
#include "dechiffrer.h"

typedef unsigned long uint32_t;

struct couple
{
    int mot;
    int cle;
};
typedef struct couple couple;

void calcul_lm_lc(int mot, int chiffre);

int attaque_mid(); //Main

// recherche dicho
int binarySearch(couple arr[], int borne_inf, int borne_sup, int x);

//Fonctions de tri
void quickSort(couple array[], int low, int high);
int partition(couple array[], int low, int high);
void swap(couple *a, couple *b);


#endif
