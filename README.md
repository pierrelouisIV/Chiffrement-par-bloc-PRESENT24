# Chiffrement-par-bloc-PRESENT24
 Implantation de l’attaque par le milieu contre un chiffrement par bloc PRESENT24

Commande (sur un terminal a la racine du projet) : - make pour compiler et executer 
                                                   - make clean pour effacer les fichiers de compilition et d'execution
                                                   - make debug pour utiliser valgrind
 
 (1) Chiffrement : Rentré un mot sous forme d'entier et une clé maitre. 
                   Recupérer votre mot chiffré et votre clé maitre.
                   
 (2) Dechiffrement : Rentré votre mot chiffré et la clé maitre associée.
                     Recupérer votre mot clair.
                     
 (3) Attaque par le milieu : Utilisation de (m1,c1) = (444b7a, 114c98) (m2,c2) = (cf31f2,4ba36f) clé de Gwennael Cannenpasse
                             Modifier les variables globales pour modifier l'attaque du milieu
