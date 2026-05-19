#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NBLIG 6
#define NBCOL 8

typedef struct {
  int ligne;
  int colonne;
} pivot;

typedef struct {
  int numJoueur;
  char nomJoueur[11];
  int aGagner;
} defJoueur;

// les données du jeu : sont mises dans une structure pour pourvoir sauvegarder dans un fichier binaire, et les récupérer facilement
typedef struct {
  int nbJoueur;
  int numeroJoueur;                           //prochain joueur à jouer
  defJoueur jo[3];
  int grille[6][8];
} jeu;

int constructJoueur (defJoueur joueur[3]){
  int n = 0;
  int j;
  char carlu;
  do{
     printf("Veuillez choisir le mode du jeu ! \n");
     printf("  2 : 2 joueurs | 3 : 3 joueurs | pour sortir : tapez 99 \n");
     scanf("%d", &n);
     carlu = getchar();                                       //verif que l'utilisateur n'a mis qu'un nombre
     while (carlu !='\n') {
      carlu = getchar();                                      //verif que l'utilisateur n'a mis qu'un nombre
     }
     if (n!=2 && n!=3 && n!=99) {
       printf("Erreur : Le nombre de joueur est incorrect\n");                   //verif que le nombre donne est prenable
     }
  } while (n!=2 && n!=3 && n!=99);
  if (n==99) {
   return (n);
  }
  for(int i=0; i<n; i++) {
   joueur[i].numJoueur = i+1;
   joueur[i].aGagner = 0;
   carlu = ' ';
   j=0;
   do {
     if (carlu=='\n'){
       printf("erreur de saisie\n");
     }
     printf("Entrez le nom du joueur %d et tapez sur la touche Entrée \n", i+1);
     scanf("%c", &carlu);
   } while (carlu=='\n');
   joueur[i].nomJoueur[j] = carlu;
   j++;
   while (carlu !='\n') {
     scanf("%c", &carlu);
     if (j < 10 && carlu != '\n') {
       joueur[i].nomJoueur[j] = carlu;
       j++;
     }
   }
   while (j<10) {
     joueur[i].nomJoueur[j] = ' ';
     j++;
   }
   joueur[i].nomJoueur[10] = '\0';
  }
  return (n);
 }

 void createPiste(int tab[NBLIG][NBCOL], int nbl, int nbc){
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

void printGame(jeu nvjeu, int nbl, int nbc){
  int k;
  printf("-\n");
  printf("    1   2   3   4   5   6   7   8\n");
  for (int i=0; i<nbl; i++){ 
    printf ("%d ", i+1);
    for (int j=0; j<nbc; j++){
      if(nvjeu.grille[i][j]==0){
        printf("|   ");
       }
      else if(nvjeu.grille[i][j]==1){
        printf("|###");
       }
      else if(nvjeu.grille[i][j]==2){
        printf("| ¤ ");
       }
      else if(nvjeu.grille[i][j]==3){
        printf("| & ");
       }
      else if(nvjeu.grille[i][j]==4){
        printf("| ¥ ");
       }
     }
    printf("| \n");
    printf("  ");
    for (k = 0; k<nbc; k++) {
    printf("----");
    }  
    printf("-\n");
   }
 }

int selectionpivot(){
  int piv;
  piv = rand()%2;
  if(piv==0){
    piv = 3;
  }
  else {
    piv = 5;
  }
printf("Le carré pivotant a une largeur de %d cases \n", piv);
return piv;
}

int deplacement_bas(int tab[NBLIG][NBCOL], int nbJ, int numcol){                          // insert piece in column 'numcol'
  int i = 0;
  while (tab[i][numcol]==0 && i<6){
    i = i+1;                                                                // 2 if first player, 3 if second player, etc...
   }
  if (i==0) {
    return (-1);          // insertion impossible, column full
  } 
  tab[i-1][numcol] = nbJ;               //nbJ : number of player
  return (i-1);
 }

pivot choixPivot(int n, int lig, int col) {               // lig = i-1 de deplacement et col = numcol = n de saisiecolonne
  int i=0, j=0;
  int ligmin, ligmax, colmin, colmax;
  pivot c;
  char carlu;
  printf("Votre nouveau jeton est en l%d, c%d \n", lig+1, col+1);
  ligmin = lig-n;
  ligmax = lig+n;
  colmin = col-n;
  colmax = col+n;  
  if ((ligmin-n) < 0) {
    ligmin = n;
   }
  if ((ligmax+n) > 5 ) {
    ligmax = 5 - n;
   }
  if ((colmin-n) < 0) {
    colmin = n;
   }
  if ((colmax + n) > 7 ) {
    colmax = 7-n;
  }
  while (j<(colmin+1) || (j>(colmax+1) && j!=99)){                                         // la ligne affichée est à +1 de l'indice
    printf("Choisir la colonne du pivot : comprise entre %d et %d ou 99 pour sortir du jeu\n", colmin+1, colmax+1);
    scanf("%d", &j);
    carlu = getchar();
    while (carlu != '\n') {
      carlu = getchar();
     }
   }   
  if (j!=99) {
    while (i<(ligmin+1) || i>(ligmax+1)) {
      printf("Choisir la ligne du pivot : comprise entre %d et %d \n", ligmin+1, ligmax+1);
      scanf("%d", &i);
      carlu = getchar();
      while (carlu != '\n') {
        carlu = getchar();
       }
     }
    printf("Votre pivot est en l%d, c%d \n", i, j);
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

int demanderRotation(){
  int choix = 0;
  char carlu;
  carlu = ' ';
  while(choix!=1 && choix !=2) {
    printf("Choisir un sens de rotation :\n");
    printf("     1 : Horaire  |  2 : Anti-Horaire\n");
    scanf("%d", &choix);
    carlu = getchar();                                      // pour supprimer les caractères restants au cas où...
    while (carlu != '\n') {
      carlu = getchar();
     }
   }
  if(choix == 1){
    printf(" Activation de la rotation Horaire\n");
   }
  else {
    printf(" Activation de la rotation Anti-Horaire\n");
   }
  return choix;
 }

void rotationHoraire(int tab[NBLIG][NBCOL], int n, pivot p) {
  int i, j, k, k2;
  int t[5][5];                                                                                             //definir en constante
  k2 = 0;
  for (i=0; i<5; i++) {                                                                      // initialisation table intermédiaire
    for (j=0; j<5; j++) {
      t[i][j] = 0;
    }
   }
  for(i=(p.ligne+n); i>=(p.ligne-n); i--) {                          // remplissage table intermédiaire avec nouvelle valeur suite à rotation
    k = 0;
    for(j=(p.colonne-n); j<=(p.colonne+n); j++) {
      t[k][k2] = tab[i][j];
      k++;
     }
    k2++;
   }
  k = 0; 
  for(i=(p.ligne-n); i<=(p.ligne+n); i++) {
    k2 = 0;
    for(j=(p.colonne-n); j<=(p.colonne+n); j++) {
      tab[i][j] = t[k][k2];
      k2++;
     }
    k++;
   }
}

void rotationAntiHoraire(int tab[NBLIG][NBCOL], int n, pivot p) {
  int i,j,k, k2;
  int t[5][5];
  for (i=0; i<5; i++) {
    for (j=0; j<5; j++) {
      t[i][j] = 0;
     }
   }
  k2 = 2*n;                                                         // remplissage table intermédiaire avec nouvelle valeur
  for(i=(p.ligne+n); i>=(p.ligne-n); i--) {
    k = 2*n;
    for(j=(p.colonne-n); j<=(p.colonne+n); j++) {
      t[k][k2] = tab[i][j];
      k--;
     }
    k2--;
   }
  k = 0;                                            // nouvelles valeur à mettre dans la grille : substitution par celle de t renseignée
  for(i=(p.ligne-n); i<=(p.ligne+n); i++) {
    k2 = 0;
    for(j=(p.colonne-n); j<=(p.colonne+n); j++) {
      tab[i][j] = t[k][k2];
      k2++;
     }
    k++;
   }
}

void gravitePivot(int tab[NBLIG][NBCOL], pivot pi, int nbc) {
  int t[NBCOL];
  int k;
  int i, j ;
  for(j=(pi.colonne-nbc); j<=(pi.colonne+nbc); j++){
    for(k=0; k<=5; k++) {
      t[k] = 0;
     }
    k = 5;
    for(i=5; i>=0; i--) {
      if (tab[i][j] != 0 && tab[i][j] != 1) {
        t[k] = tab[i][j];
        k--;
       }
      else if (tab[i][j] == 1) {
        t[i] = tab[i][j];
        k = i-1;
       }
     }
    for(i=0; i<=5; i++) {
      tab[i][j]=t[i];
     }
   }
}

// fin = 1 : non terminée, fin = 0 : joueur(s) gagnant(s), fin = 2 : Partie Nulle
int finJeu(int tab[NBLIG][NBCOL], defJoueur resJ[3]) {
  int i, j, k;
  int fin = 1;
  for (i=0; i<NBLIG; i++) {                                                                         // verif gagnant en ligne
    for(j=0; j<=NBCOL-5; j++) {
      if (tab[i][j]==tab[i][j+1] && tab[i][j]==tab[i][j+2] && tab[i][j]==tab[i][j+3] && tab[i][j]==tab[i][j+4] && tab[i][j] != 0) {
        k = tab[i][j] - 2;
        resJ[k].aGagner = 1;
        printf("Gagnant en ligne %d \n", i+1);
        fin = 0;
       }
     }
   }
  for (j=0; j<NBCOL; j++) {                                                                        // vérif gagnant en colonne : NON Testée
    for(i=0; i<=NBLIG-5; i++) {
      if (tab[i][j]==tab[i+1][j] && tab[i][j]==tab[i+2][j] && tab[i][j]==tab[i+3][j] && tab[i][j]==tab[i+4][j]  && tab[i][j] != 0) {
        k = tab[i][j] - 2;
        resJ[k].aGagner = 1;
        printf("Gagnant en colonne %d \n", j+1);
        fin = 0;
       }
     }
   }
  for(i=4; i<6; i++) {                                                                            // verif gagnant en diagonale /
    for(j=0; j<4; j++) {
      if (tab[i][j]==tab[i-1][j+1] && tab[i][j]==tab[i-2][j+2] && tab[i][j]==tab[i-3][j+3] && tab[i][j]==tab[i-4][j+4] && tab[i][j]!=0){
        k=tab[i][j] - 2;
        resJ[k].aGagner = 1;
        printf("Gagnant en diagnonale %d \n", i+1);
        fin = 0;
       }
     }
   }
  for(i=4; i<6; i++) {                                                                    // verif gagnant en diagonale inversée
    for(j=4; j<8; j++) {
      if (tab[i][j]==tab[i-1][j-1] && tab[i][j]==tab[i-2][j-2] && tab[i][j]==tab[i-3][j-3] && tab[i][j]==tab[i-4][j-4] && tab[i][j]!=0){
        k=tab[i][j] - 2;
        resJ[k].aGagner = 1;
        printf("Gagnant en diagonale inversée %d \n", i+1);
        fin = 0;
       }
     }
   }
  if (fin==1) {                                                                         // verif si partie NULLE
    fin = 2;
    for(j=0; j<NBCOL; j++) {
      if(tab[0][j] ==0) {
        fin = 1;
       }
     }
   }
  return fin;
}

int sauvJeux(jeu sjeu, FILE *fic){
  int save = 0;
  fic = fopen("SauvP5.txt", "wb+") ;
  if (fic!=NULL) {
    save = fwrite(&sjeu, sizeof(jeu), 1, fic);
    save = fclose(fic);
   }
 }


// programme principal
int main () {
 int nvlig, nbpivot, nbcase;
 int numerocol = 0;
 int finpartie = 1;
 int retF = 0;
 char carlu;
 char reprise = ' ';
 pivot piv;
 jeu nvJeu;
 FILE *f = NULL;
 srand(time(NULL));
   
 f=fopen("SauvP5.txt", "rb") ;
 if(f!= NULL) {                                                                                                      // verification si sauvegarde du jeu existe
  while(reprise != 'o' && reprise != 'O' && reprise != 'n' && reprise != 'N') {
    do {
      if (reprise == '\n'){
        printf("erreur 2 de saisie\n");
      }
      printf("Voulez vous reprendre l'ancienne partie ? O pour Oui, N pour Non \n");
      scanf("%c", &reprise);
    } while (reprise == '\n');
    carlu = getchar();
    while (carlu != '\n') {
      carlu = getchar();
    }
  }
}
if (reprise=='o' || reprise == 'O') {                                                                    // initialisation jeu avec sauvegarde
  retF = fread(&nvJeu, sizeof(jeu), 1, f);
  if (retF!=1) {
    printf("Dernier jeux introuvable, vous allez commencer une nouvelle partie \n");
  }
}
// initialisation du jeu si non récupérer du fichier de sauvegarde
if (retF != 1) {
  nvJeu.nbJoueur=constructJoueur(nvJeu.jo);
  if (nvJeu.nbJoueur == 99) {
    return 0;
  }                                                               //finpartie
  createPiste(nvJeu.grille, NBLIG, NBCOL);
  nvJeu.numeroJoueur = 0; 
}
if(f!= NULL) {                                                                                         // suppression du fichier de sauvegarde
 retF = fclose(f);
 retF = remove("SauvP5.txt");
}
printGame(nvJeu, NBLIG, NBCOL);
while(finpartie == 1) {                                                                                  // a faire tant que partie non terminée
  printf("Au tour du joueur %s \n", nvJeu.jo[nvJeu.numeroJoueur].nomJoueur);
  nvlig = -1;
   // calcul largeur carré à pivoter
  nbpivot = selectionpivot();
  nbcase = nbpivot/2;
  
  //insertion du jeton du nv joueur
  while(nvlig==-1) {
    // demander la colonne où insérer le jeton ou 99 pour sortir
    numerocol = saisiecolonne(nvJeu.numeroJoueur); 
    if (numerocol ==99) {
      finpartie = 2;
      reprise = ' ';
      do {
        printf("Voulez vous sauvegarder la partie ? O pour Oui, N pour Non \n");
        scanf("%c", &reprise);
        if(reprise == 'o' || reprise == 'O') { 
          sauvJeux(nvJeu, f);
          return 0;
        }
      } while (reprise!='o' && reprise!='O' && reprise!='n' && reprise!='N' || reprise == '\n');
      carlu = getchar();
      while (carlu != '\n') {
        carlu = getchar();
       }
    }
    nvlig= deplacement_bas(nvJeu.grille, nvJeu.numeroJoueur+2, numerocol);                  // insertion du jeton : valeur jeton = indice  du joueur + 2
   }                                                                                        // fin insertion du jeton : le nouveau pion sera en nvlig, numerocol
  printGame(nvJeu, NBLIG, NBCOL);
  piv = choixPivot(nbcase, nvlig, numerocol);                                               // demande position du pivot
  if (piv.ligne==99) {
    finpartie = 2;
    return 0;
   }
  if (demanderRotation() ==1 ) {                                                            // demande du type de rotation
   rotationHoraire(nvJeu.grille, nbcase, piv);
   }
  else {
    rotationAntiHoraire(nvJeu.grille, nbcase, piv);
   }
  printGame(nvJeu, NBLIG, NBCOL);
  gravitePivot(nvJeu.grille, piv, nbcase);                                                 // gravité suite à la rotation
  printGame(nvJeu, NBLIG, NBCOL);
  finpartie = finJeu(nvJeu.grille, nvJeu.jo);                                              // si finpartie = 2 => Terminée pas de gagnant, si = 0 : gagnant
  if (nvJeu.numeroJoueur >= nvJeu.nbJoueur-1) {                                            // calcul du nouveau joueur qui doit jouer
    nvJeu.numeroJoueur = 0;
   }
   else {
     nvJeu.numeroJoueur =  nvJeu.numeroJoueur+1;
    }
}                                                                                         //fin de partie
if (finpartie == 2) {                                                                      // affichage résultat 
  printf("La partie est terminée, SANS gagnant \n");
 }
 else {
   for (int i=0; i<3; i++) {
     if (nvJeu.jo[i].aGagner == 1) {
       printf("BRAVO au joueur %s, vous avez gagné\n", nvJeu.jo[i].nomJoueur);
      }
    }
  }
return 0;
}
