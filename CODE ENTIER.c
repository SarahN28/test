#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// saisie du nombre de joueur
int constructJoueur (defJoueur joueur[3]){
  int n = 0;
  int j;
  char carlu;
  do{
     printf("Entrez le nombre de joueurs : 2 ou 3, pour sortir tapez 99 :\n");
     scanf("%d", &n);
     getchar();
     if (n!=2 && n!=3 && n!=99) {
       printf("Erreur :  le nombre de joueur est incorrect\n");}
  } while (n!=2 && n!=3 && n!=99);
  if (n==99) {
   return(n);
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
  return(n);
 }

// sélection du pivot
int selectionpivot(){
  int piv;
  piv = rand()%2;
  if(piv==0){
    piv = 3;
  }
  else{
  piv = 5;
  }
return piv;
}

 
 // initialisation de la grille de jeu
 void createPiste(int (*tab)[NBCOL], int nbl, int nbc){
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
void printGame(int (*tab)[NBCOL], int nbl, int nbc){
  int k;
  printf("-\n");
  printf("    1  2  3  4  5  6  7  8\n");
  for (int i=0; i<=5; i++){ 
    printf ("%d ", i+1);
    for (int j=0; j<nbc; j++){
      if(tab[i][j]==0){
        printf("|  ");
       }
      else if(tab[i][j]==1){
        printf("|##");
       }
      else if(tab[i][j]==2){
        printf("| 1");
       }
      else if(tab[i][j]==3){
        printf("| 2");
       }
      else if(tab[i][j]==4){
        printf("| 3");
       }
       
     }
    printf("| \n");
    printf("  ");
    for (k = 0; k<nbc; k++) {
    printf("---");
    }  
    printf("-\n");
   }
 }
 
 // saisie de la colonne ou 99 pour sortir du jeu
 int saisiecolonne() {
   int n=0;
    do{
     printf("Entrez le numéro de colonne pour insérer votre jeton, ou 99 pour sortir : \n");
     scanf("%d", &n);
     getchar();
     if (n<1 || (n>8 && n!=99)) {
       printf("Erreur :  le numéro de colonne est incorrecte\n");}
  } while (n<1 || (n>8 && n!=99));
  if (n!=99) {
    return(n-1);}
  else {return(n);
  } 
 }
 
 // insertion  valeur  en colonne c numcol
 // vaut 2 si premier joueur, 3 si second joueur 
int deplacement_bas(int (*tab)[NBCOL], int nbJ, int numcol){
  int i;
  i=0;
  while(tab[i][numcol]==0 && i<6){
    i = i+1;
  }
  // i contient la première ligne non vide (arrêt car !=0)
  if (i==0) { return(-1);} // la colonne est pleine : insertion du jeton impossible
  tab[i-1][numcol] = nbJ;
  return(i-1);
 }

 // selection du pivot : le carré doit contenir le dernier jeton mis, et doit appartenir à la grille
 // la ligne du pivot soit être à n case de celle du jeton, n étant le nb de case pivotant autour du pivot (nbpivot/2), le carré doit rester dans la grille
 // la colonne du pivot soit être à n case de celle du jeton, n étant le nb de case pivotant autour du pivot (nbpivot/2), le carré doit rester dans la grille 
pivot choixPivot(int n, int lig, int col) {
  int i=0, j=0;
  int ligmin, ligmax, colmin, colmax;
  pivot c;
  
  printf("Votre nouveau jeton est en l%d, c%d \n", lig+1, col+1);
  printf("la largeur du carré pivotant est de %d cases \n", (n*2)+1);
  
  // le pion doit être dans le carré (les valeurs sont celles affichées soit a +1 de l'indice du tableau)
  ligmin = lig-n +1;
  ligmax = lig+n +1;
  colmin = col-n +1;
  colmax = col+n + 1;
  
  // carré doit être dans grille
  if ((ligmin-n) < 1) {
    ligmin = 1;
  }
  if ((ligmax + n) > 6 ) {
    ligmax = 6 - n;
  }
  
   if ((colmin-n) < 1) {
    colmin = 1;
  }
  if ((colmax + n) > 8 ) {
    colmax = 8-n;
  }
   

    while (j<colmin || (j>colmax && j!=99)){
      printf("Choisir la colonne du pivot : comprise entre %d et %d ou 99 pour sortir du jeu\n", colmin, colmax);
      scanf("%d", &j);
      getchar();
     }
     
    if (j!=99) {
      while (i<ligmin || i>ligmax) {
        printf("Choisir la ligne du pivot : comprise entre %d et %d \n", ligmin, ligmax);
        scanf("%d", &i);
        getchar();
      }
     i--;
     j--;
    }
    else {
     i = 99;
    }
   
  c.ligne = i;
  c.colonne = j;
  return c;
 }
 
 
 // vérification nv jeton (en ligne, colonne : lig, col) est bien dans la zone de pivot
 int verifpivot(pivot p, int nbcase, int lig, int col) {
 if (lig > (p.ligne + nbcase) || lig < (p.ligne - nbcase)) {
  return(1);
 }
 if (col > (p.colonne + nbcase) || col < (p.colonne - nbcase)) {
  return(1);
 }
 return(0);
 }
 
// Type de rotation 
int demanderRotation(){
int choix = 0;

while(choix!=1 && choix !=2) {
  printf("choisissez le sens de la rotation : 1 pour Horaire et 2 pour Anti-Horaire :\n");
  scanf("%d", &choix);
  getchar();
}

if(choix == 1){
    printf(" vous avez choisi : Horaire\n");
}
else {
    printf(" vous avez choisi : Anti-Horaire\n");
}
return choix;
}

// rotation horaire
void rotationHoraire(int (*tab)[NBCOL], int n, pivot p) {
 int i,j,k, k2;
 int t[5][5];
 printf("n vaut %d\n", n);
 // initialisation table intermédiaire
 for (i=0; i<5; i++) {
   for (j=0; j<5; j++) {
     t[i][j]=0;
   }
  }
 // remplissage table intermédiaire avec nouvelle valeur suite à rotation
 k2 = 0;
 printf("intervalle de i :  %d %d \n", (p.ligne+n), (p.ligne-n)); 
 for(i=(p.ligne+n); i>=(p.ligne-n); i--) {
  k = 0;
  printf("i=%d ",i);
  for(j=(p.colonne-n); j<=(p.colonne+n); j++) {
   t[k][k2]=tab[i][j];
   k++;
  }
  k2++;
 }
 // nouvelles valeur à mettre dans la grille : substitution par celle de t renseignée
 k=0; 
 for(i=(p.ligne-n); i<=(p.ligne+n); i++) {
  k2=0;
  for(j=(p.colonne-n); j<=(p.colonne+n); j++) {
   tab[i][j]=t[k][k2];
   k2++;
  }
  k++;
 }
}

void rotationAntiHoraire(int (*tab)[NBCOL], int n, pivot p) {
 int i,j,k, k2;
 int t[5][5];
 for (i=0; i<5; i++) {
   for (j=0; j<5; j++) {
     t[i][j]=0;
   }
  }
 // remplissage table intermédiaire avec nouvelle valeur
 k2 = 2*n;
 for(i=(p.ligne+n); i>=(p.ligne-n); i--) {
  k = 2*n;
  for(j=(p.colonne-n); j<=(p.colonne+n); j++) {
   t[k][k2]=tab[i][j];
   k--;
  }
  k2--;
 }
 // nouvelles valeur à mettre dans la grille : substitution par celle de t renseignée
 k=0; 
 for(i=(p.ligne-n); i<=(p.ligne+n); i++) {
  k2=0;
  for(j=(p.colonne-n); j<=(p.colonne+n); j++) {
   tab[i][j]=t[k][k2];
   k2++;
  }
  k++;
 }
}

// gravité pour les colonnes du pivot : pour chaque colonne du pivot : chaque élement d'une colonne descend jusqu'à la dernière colonne vide, sauf si block : ne bouge pas.

void gravitePivot(int (*tab)[NBCOL], pivot pi, int nbc) {
int t[NBCOL];
int k=5;
int i, j ;
for(j=pi.colonne-nbc; j<=pi.colonne+nbc;j++){
  for(k=0; k<=5; k++) {
    t[k]=0;
  }
  k=5;
  for(i=5; i>=0;i--) {
    if (tab[i][j] != 0 && tab[i][j] != 1) {
      t[k]=tab[i][j];
      k--;
    }
    else if (tab[i][j] == 1) {
        t[i]=tab[i][j];
        k=i-1;
    }
  }

  for(i=0; i<=5; i++) {
   tab[i][j]=t[i];
  }
}
}

// fin fct

// Fin de jeu  ? ret = 1 : non terminée, ret=0 : joueur(s) gagnant(s), ret=2 : Partie Nulle
int finJeu(int (*tab)[NBCOL], defJoueur resJ[3]) {
int i, j, k;
int ret = 1;

// verif gagnant en ligne
for (i=0; i<NBLIG; i++) {
  for(j=0; j<=NBCOL-5; j++) {
    if (tab[i][j]==tab[i][j+1] && tab[i][j]==tab[i][j+2] && tab[i][j]==tab[i][j+3] && tab[i][j]==tab[i][j+4] && tab[i][j] != 0) {
      k=tab[i][j] - 2;
      resJ[k].aGagner = 1;
      printf("gagnant en ligne %d \n", i);
      ret = 0;
    }
  }
}
  
// vérif gagnant en colonne : NON Testée
for (j=0; j<NBCOL; j++) {
  for(i=0; i<=NBLIG-5; i++) {
    if (tab[i][j]==tab[i+1][j] && tab[i][j]==tab[i+2][j] && tab[i][j]==tab[i+3][j] && tab[i][j]==tab[i+4][j]  && tab[i][j] != 0) {
      k=tab[i][j] - 2;
      resJ[k].aGagner = 1;
      printf("gagnant en colonne %d \n", j);
      ret = 0;
    }
  }
}
// verif gagnant en diagonale /
for(i=4; i<6; i++) {
  for(j=0; j<4; j++) {
    if (tab[i][j]==tab[i-1][j+1] && tab[i][j]==tab[i-2][j+2] && tab[i][j]==tab[i-3][j+3] && tab[i][j]==tab[i-4][j+4] && tab[i][j]!=0){
      k=tab[i][j] - 2;
      resJ[k].aGagner = 1;
      printf("gagnant en diagnonale %d \n", i);
      ret = 0;
    }
  }
}

// verif gagnant en diagonale inversée

for(i=4; i<6; i++) {
  for(j=4; j<8; j++) {
    if (tab[i][j]==tab[i-1][j-1] && tab[i][j]==tab[i-2][j-2] && tab[i][j]==tab[i-3][j-3] && tab[i][j]==tab[i-4][j-4] && tab[i][j]!=0){
      k=tab[i][j] - 2;
      resJ[k].aGagner = 1;
      printf("gagnant en diag inversee %d \n", i);
      ret = 0;
    }
  }
}


// verif si partie NULLE
if (ret==1) {
 ret=2;
 for(j=0; j<NBCOL; j++) {
  if(tab[0][j] ==0) {
    ret=1;
  }
 }
 }
 return(ret);
}
 
int main () {
 // programme principal
 int nbjoueur;
 int numerojoueur = 0;
 int numerocol = 0;
 int grille[NBLIG][NBCOL];
 int finpartie = 1;
 int nvlig;
 int nbpivot;
 int nbcase;
 int ok;
 pivot piv;
 defJoueur jo[3];
 
 nbjoueur = constructJoueur(jo);
 if (nbjoueur == 99) {return 0; }
 createPiste(grille, NBLIG, NBCOL);

numerojoueur = 0; 
// a faire tant que partie non terminée
while(finpartie == 1) {

  printGame(grille, NBLIG, NBCOL);
  printf("Au tour du joueur %s \n", jo[numerojoueur].nomJoueur);
  nvlig = -1;
  
  //insertion du jeton du nv joueur
  while(nvlig==-1) {
    // demander la colonne où insérer le jeton ou 99 pour sortir
    numerocol = saisiecolonne(numerojoueur); 
    if (numerocol ==99) {
      finpartie = 2;
      return 0;
    }
    // insertion du jeton : valeur jeton = indice  du joueur + 2
    nvlig = deplacement_bas(grille, numerojoueur+2, numerocol);
  }
  // fin insertion du jeton : le nouveau pion sera en nvlig, numerocol
  printGame(grille, NBLIG, NBCOL);
  
  // calcul largeur carré à pivoter
  nbpivot = selectionpivot();
  nbcase = nbpivot/2;
 
 // sélection du pivot
  ok = 1;
  while(ok==1) {
  // demande position du pivot
  piv = choixPivot(nbcase, nvlig, numerocol);
  if (piv.ligne==99) {
      finpartie = 2;
      return 0;
    }
  
  // a tester : vérification que le nouveau pion est bien dans la zone de pivot 
    ok = verifpivot(piv, nbcase, nvlig, numerocol);
    if (ok==1) {
     printf("votre pion n'est pas dans la zone de rotation : %d case(s) autour du pivot. Veuillez re-saisir le pivot \n", nbcase);
     }
  }

 
  // demande du type de rotation
  if (demanderRotation() ==1 ) {
   rotationHoraire(grille, nbcase, piv);
   }
  else {
    rotationAntiHoraire(grille, nbcase, piv);
   }
   printGame(grille, NBLIG, NBCOL);
   // gravité suite à la rotation
   gravitePivot(grille, piv, nbcase);
   
   printGame(grille, NBLIG, NBCOL);
  
 // si finpartie = 2 => Terminée pas de gagnant, si = 0 : gagnant
  finpartie = finJeu(grille, jo);
  
  // calcul du nouveau joueur qui doit jouer
  if (numerojoueur >= nbjoueur-1) {
    numerojoueur = 0;}
  else {
    numerojoueur =  numerojoueur+1;
  }
}
//fin de partie

// affichage résultat :
if (finpartie == 2) {
 printf("La partie est terminée, SANS gagnant \n");
 }
 else {
  for (int i=0; i<3; i++) {
    if (jo[i].aGagner == 1) {
      printf("BRAVO au joueur %s, vous avez gagné\n", jo[i].nomJoueur);
    }
  }
 }


return 0;
}

