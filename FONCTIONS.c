#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "p5types.h"
#include "p5function.h"

// programme principal
int main () {
 int nwline, nbpivot, nbcase, ret;
 int numerocol = 0;
 int endMatch = 1;
 int retF = 0;
 int sGrid[NBLIN][NBCOL];
 char carlu;
 char reprise = ' ';
 char topinit = '0';
 pivot piv;
 Game nwGame;
 FILE *f = NULL;
 srand(time(NULL));
   
 f = fopen("SauvP5.txt", "rb") ;
 if(f!= NULL) {                                                                                                      // verification si sauvegarde du jeu existe
  while(reprise != 'o' && reprise != 'O' && reprise != 'n' && reprise != 'N') {
    do {
      if (reprise == '\n'){
        printf("erreur de saisie 2\n");
      }
      printf("Voulez vous reprendre l'ancienne partie ? O pour Oui, N pour Non \n");
      scanf("%c", &reprise);
    } while (reprise == '\n');
    carlu = getchar();
    while (carlu != '\n') {
      carlu = getchar();
     }
   }
  if (reprise=='o' || reprise == 'O') {                                                                    // initialisation jeu avec sauvegarde
    retF = fread(&nwGame, sizeof(Game), 1, f);
    if (retF!=1) {
      printf("Dernier jeu introuvable, vous allez commencer une nouvelle partie \n");
     }
    else{
      topinit = '1';
     }
   }
  retF = fclose(f);
  retF = remove("SauvP5.txt");
 }
if (topinit != '1') {
  nwGame.nbPlayer=constructPlayer(nwGame.pl);
  if (nwGame.nbPlayer == 99) {
    return 0;
  }                                                               //endMatch
  createGrid(nwGame.grid, NBLIN, NBCOL);
  nwGame.noPlayer = 0; 
}

printGame(nwGame, NBLIN, NBCOL);
while(endMatch == 1) {                                                                                  // a faire tant que partie non terminée
  saveGrid(nwGame.grid, sGrid);
  printf("Au tour du joueur %s \n", nwGame.pl[nwGame.noPlayer].namePlayer);
  nwline = -1;
   // calcul largeur carré à pivoter
  nbpivot = sizePiv();
  nbcase = nbpivot/2;
  while(nwline==-1) {                                                                                       //insertion du jeton du nv joueur
    // demander la colonne où insérer le jeton ou 99 pour sortir
    numerocol = selectCol(nwGame.noPlayer); 
    if (numerocol == 99) {
      endMatch = 2;
      reprise = ' ';
      do {
        printf("Voulez vous sauvegarder la partie ? O pour Oui, N pour Non \n");
        scanf("%c", &reprise);
        if(reprise == 'o' || reprise == 'O') { 
          saveGrid(sGrid, nwGame.grid);
          ret=saveGame(nwGame, f);
          return 0;
        }
        else if (reprise == 'n' || reprise == 'N'){
          return 0;
         }
      } while ((reprise!='o' && reprise!='O' && reprise!='n' && reprise!='N') || (reprise == '\n'));
      carlu = getchar();
      while (carlu != '\n') {
        carlu = getchar();
       }
    }
    nwline= fall(nwGame.grid, nwGame.noPlayer+2, numerocol);                  // insertion du jeton : valeur jeton = indice  du joueur + 2
   }                                                                                        // fin insertion du jeton : le nouveau pion sera en nwline, numerocol
  printGame(nwGame, NBLIN, NBCOL);
  piv = selectPiv(nbcase, nwline, numerocol);                                               // demande position du pivot
  if (piv.line==99) {
    endMatch = 2;
    reprise = ' ';
    while(reprise != 'o' && reprise != 'O' && reprise != 'n' && reprise != 'N') {
        printf("Voulez vous sauvegarder la partie ? O pour Oui, N pour Non \n");
        scanf("%c", &reprise);
        carlu = reprise;
        while (carlu != '\n') {
         scanf("%c", &carlu);
        }
    }
    if(reprise == 'o' || reprise == 'O') { 
        saveGrid(sGrid, nwGame.grid);
        ret=saveGame(nwGame, f);
    }
    return 0;
   }
  if (askRotation()==1 ) {                                                            // demande du type de rotation
   Clockwise(nwGame.grid, nbcase, piv);
   }
  else {
    counterClock(nwGame.grid, nbcase, piv);
   }
  printGame(nwGame, NBLIN, NBCOL);
  gravityPivot(nwGame.grid, piv, nbcase);                                                 // gravity suite à la rotation
  printGame(nwGame, NBLIN, NBCOL);
  endMatch = endGame(nwGame.grid, nwGame.pl);                                              // si endMatch = 2 => Terminée pas de gagnant, si = 0 : gagnant
  if (nwGame.noPlayer >= nwGame.nbPlayer-1) {                                            // calcul du nouveau joueur qui doit jouer
    nwGame.noPlayer = 0;
   }
   else {
     nwGame.noPlayer =  nwGame.noPlayer+1;
    }
}                                                                                         //fin de partie
if (endMatch == 2) {                                                                      // affichage résultat 
  printf("La partie est terminée, SANS gagnant \n");
 }
 else {
   for (int i=0; i<3; i++) {
     if (nwGame.pl[i].Win == 1) {
       printf("BRAVO au joueur %s, vous avez gagné\n", nwGame.pl[i].namePlayer);
      }
    }
  }
return 0;
}
