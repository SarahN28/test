#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <struct.h>
#define NBLIG 6
#define NBCOL 8

// saisie du nombre de joueur
int constructJoueur (defJoueur joueur[3]){
  int n = 0;
  int j;
  char carlu;
  do{
     printf("Entrez le nombre de joueurs : 2 ou 3, pour sortir tapez 99 :\n");
     scanf("%d", &n);
     carlu = getchar();
     while (carlu !='\n') {
      carlu = getchar();
     }
     if (n!=2 && n!=3 && n!=99) {
       printf("Erreur :  le nombre de joueur est incorrect\n");}
  } while (n!=2 && n!=3 && n!=99);
  if (n==99) {
   return n;
  }
  for(int i=0; i<n; i++) {
   joueur[i].numJoueur = i+1;
   joueur[i].pieceJoueur = i+2;
   joueur[i].aGagner = 0;
   printf("Entrez le nom du joueur %d et tapez sur la touche Entrée \n", i+1);
   carlu = ' ';
   j=0;
   while (carlu !='\n') {
     scanf("%c", &carlu);
     if (j < 10) {
       joueur[i].nomJoueur[j] = carlu;
       j++;
     }
   }
  }
  return n;
 }


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

// affichage de la grille de jeu
void printGame(int tab[][NBCOL], int nbl, int nbc){
  int k;
  printf("-\n");
  printf("    1  2  3  4  5  6  7  8\n");
  for (int i=0; i<=5; i++){ 
    printf ("%d ", i+1);
    for (int j=0; j<nbc; j++){
      if(tab[i][j]==0){
        printf("|    ");
       }
      else if(tab[i][j]==1){
        printf("|####");
       }
      else if(tab[i][j]==2){
        printf("| )( ");
       }
      else if(tab[i][j]==3){
        printf("| >< ");
       }
      else if(tab[i][j]==4){
        printf("| ¤¤ ");
       }
     }
    printf("| \n");
    printf("  ");
    for (k = 0; k<nbc; k++) {
    printf("------");
    }  
    printf("-\n");
   }
 }
 
