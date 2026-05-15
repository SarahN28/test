#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main () {
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
