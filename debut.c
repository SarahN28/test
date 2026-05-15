#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define int NBLIG
#
const int NBLIG = 6;
const int NBCOL = 8;
typedef struct {
  int ligne;
  int colonne;
} pivot;

typedef struct {
  int numJoueur;
  char nomJoueur[11];
  char pieceJoueur;
  int aGagner;
} defJoueur;

// initialisation de la grille de jeu
 void createPiste(int tab[][NBCOL], int nbl, int nbc){
  for (int i=0; i<nbl; i++){
    for(int j=0; j<nbc; j++) {
      tab[i][j] = 0;
    }
  }
  tab[0][0]=1;                //carré sur L1 C1
  tab[0][nbc-1]=1;                //carré sur L1 C8
  tab[nbl-1][0]=1;                //carré sur L6 C1
  tab[nbl-1][nbc-1]=1;                //carré sur L6 C8
}
