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
  int aGagner;
} defJoueur;

// les données du jeu : sont mises dans une structure pour pourvoir sauvegarder dans un fichier binaire, et les récupérer facilement
typedef struct {
  int nbJoueur;
  int numeroJoueur;                           //prochain joueur à jouer
  defJoueur jo[3];
  int grille[6][8];
} jeu;


// saisie du nombre de joueur
int constructJoueur (defJoueur joueur[3]){
  int n = 0;
  int j;
  char carlu;
  do{
     printf("Entrez le nombre de joueurs : 2 ou 3, pour sortir : tapez 99 \n");
     scanf("%d", &n);
     carlu = getchar();                                       //verif que l'utilisateur n'a mis qu'un nombre
     while (carlu !='\n') {
      carlu = getchar();                                      //verif que l'utilisateur n'a mis qu'un nombre
     }
     if (n!=2 && n!=3 && n!=99) {
       printf("Erreur :  le nombre de joueur est incorrect\n");                   //verif que le nombre donne est prenable
     }
  } while (n!=2 && n!=3 && n!=99);
  if (n==99) {
   return (n);
  }
  for(int i=0; i<n; i++) {
   joueur[i].numJoueur = i+1;
   joueur[i].aGagner = 0;
   printf("Entrez le nom du joueur %d et tapez sur la touche Entrée \n", i+1);
   carlu = ' ';
   j=0;
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
printf("la largeur du carré pivotant est de %d cases \n", piv);
return piv;
}


 // initialisation de la grille de jeu
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

// affichage de la grille de jeu
void printGame(jeu nvjeu, int nbl, int nbc){
  int k;
  printf("-\n");
  printf("    1  2  3  4  5  6  7  8\n");
  for (int i=0; i<nbl; i++){ 
    printf ("%d ", i+1);
    for (int j=0; j<nbc; j++){
      if(nvjeu.grille[i][j]==0){
        printf("|  ");
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
    printf("---");
    }  
    printf("-\n");
   }
 }
 
 // saisie de la colonne ou 99 pour sortir du jeu
 int saisiecolonne() {
   int n=0;
   char carlu;
    do{
     printf("Entrez le numéro de colonne pour insérer votre jeton, ou 99 pour sortir : \n");
     scanf("%d", &n);
     carlu = getchar();
     while (carlu != '\n') {
       carlu = getchar();
     }
     if (n<1 || (n>8 && n!=99)) {
       printf("Erreur :  le numéro de colonne est incorrecte\n");
     }
  } while (n<1 || (n>8 && n!=99));
  if (n!=99) {
    return (n-1);
  }
  else {
    return (n);
  } 
 }

 // insertion  valeur  en colonne c numcol
 // vaut 2 si premier joueur, 3 si second joueur, 4 si troisieme joueur
int deplacement_bas(int tab[NBLIG][NBCOL], int nbJ, int numcol){          //numcol = n de fonction precedente
  int i;
  i=0;
  while (tab[i][numcol]==0 && i<6){
    i = i+1;
  }
  // i contient la première ligne non vide (arrêt car !=0)
  if (i==0) {
    return (-1);
  } // la colonne est pleine : insertion du jeton impossible
  tab[i-1][numcol] = nbJ;
  return(i-1);
 }

 // selection du pivot : le carré doit contenir le dernier jeton mis, et doit appartenir à la grille
 // la ligne du pivot soit être à n case de celle du jeton, n étant le nb de case pivotant autour du pivot (nbpivot/2), le carré doit rester dans la grille
 // la colonne du pivot soit être à n case de celle du jeton, n étant le nb de case pivotant autour du pivot (nbpivot/2), le carré doit rester dans la grille 
pivot choixPivot(int n, int lig, int col) {               // lig = i-1 de deplacement et col = numcol = n de saisiecolonne
  int i=0, j=0;
  int ligmin, ligmax, colmin, colmax;
  pivot c;
  char carlu;
  
  printf("Votre nouveau jeton est en l%d, c%d \n", lig+1, col+1);
  
  // le carré de rotation doit contenir le pion
  ligmin = lig-n;
  ligmax = lig+n;
  colmin = col-n;
  colmax = col+n;
  
  // le carré doit être dans grille : donc le pivot - n case, et picot + n cases doit être dans la grille
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
   
  // la ligne affichée est à +1 de l'indice
    while (j<(colmin+1) || (j>(colmax+1) && j!=99)){
      printf("Choisir la colonne du pivot : comprise entre %d et %d ou 99 pour sortir du jeu\n", colmin+1, colmax+1);
      scanf("%d", &j);
      carlu = getchar();
      while (carlu != '\n') {
       carlu = getchar();
      }
     }
     
    if (j!=99) {
      while (i<(ligmin +1) || i>(ligmax+1)) {
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
 

// Type de rotation 
int demanderRotation(){
int choix = 0;
char carlu;

carlu = ' ';
while(choix!=1 && choix !=2) {
  printf("Choisissez le sens de la rotation : 1 pour Horaire et 2 pour Anti-Horaire :\n");
  scanf("%d", &choix);
  carlu = getchar();                                      // pour supprimer les caractères restants au cas où...
  while (carlu != '\n') {
    carlu = getchar();
  }
}

if(choix == 1){
    printf(" Vous avez choisi : Horaire\n");
}
else {
    printf(" Vous avez choisi : Anti-Horaire\n");
}
return choix;
}

// rotation horaire
void rotationHoraire(int tab[NBLIG][NBCOL], int n, pivot p) {
 int i,j,k, k2;
 int t[5][5];
 
 // initialisation table intermédiaire
 for (i=0; i<5; i++) {
   for (j=0; j<5; j++) {
     t[i][j]=0;
   }
  }
 // remplissage table intermédiaire avec nouvelle valeur suite à rotation
 k2 = 0;

 for(i=(p.ligne+n); i>=(p.ligne-n); i--) {
  k = 0;
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

void rotationAntiHoraire(int tab[NBLIG][NBCOL], int n, pivot p) {
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

void gravitePivot(int tab[NBLIG][NBCOL], pivot pi, int nbc) {
int t[NBCOL];
int k;
int i, j ;
for(j=pi.colonne-nbc; j<=pi.colonne+nbc; j++){
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
int finJeu(int tab[NBLIG][NBCOL], defJoueur resJ[3]) {
int i, j, k;
int ret = 1;

// verif gagnant en ligne
for (i=0; i<NBLIG; i++) {
  for(j=0; j<=NBCOL-5; j++) {
    if (tab[i][j]==tab[i][j+1] && tab[i][j]==tab[i][j+2] && tab[i][j]==tab[i][j+3] && tab[i][j]==tab[i][j+4] && tab[i][j] != 0) {
      k = tab[i][j] - 2;
      resJ[k].aGagner = 1;
      printf("Gagnant en ligne %d \n", i+1);
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
      printf("Gagnant en colonne %d \n", j+1);
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
      printf("Gagnant en diagnonale %d \n", i+1);
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
      printf("Gagnant en diagonale inversée %d \n", i+1);
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
return (ret);
}


int sauvJeux(jeu sjeu, FILE *fic){
 int ret=0;
 fic=fopen("SauvP5.txt", "wb+") ;
 if (fic!=NULL) {
   ret=fwrite(&sjeu, sizeof(jeu), 1, fic);
   ret=fclose(fic);
 }
 }
 
 // programme principal
 int main () {
 int numerocol = 0;
 int finpartie = 1;
 int nvlig;
 int nbpivot;
 int nbcase;
 int ok;
 int retF = 0;
 char reprise, carlu;
 pivot piv;
 jeu nvJeu;
 FILE *f = NULL;
 
 srand(time(NULL));
  
 // verification si sauvegarde du jeu existe
 reprise = ' ';
 f=fopen("SauvP5.txt", "rb") ;
 if(f!= NULL) {
  while(reprise != 'o' && reprise != 'O' && reprise != 'n' && reprise != 'N') {
    printf("Voulez vous reprendre l'ancienne partie ? O pour Oui, N pour Non \n");
    scanf("%c", &reprise);
    carlu = getchar();
    while (carlu != '\n') {
      carlu = getchar();
    }
  }
}

// initialisation jeu avec sauvegarde
if (reprise=='o' || reprise == 'O') {
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
// suppression du fichier de sauvegarde
if(f!= NULL) {
 retF = fclose(f);
 retF = remove("SauvP5.txt");
}

printGame(nvJeu, NBLIG, NBCOL);


// a faire tant que partie non terminée
while(finpartie == 1) {
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
      printf("Voulez vous sauvegarder la partie ? O pour Oui, N pour Non \n");
      scanf("%c", &reprise);
      if(reprise == 'o' || reprise == 'O') { 
        sauvJeux(nvJeu, f);}
      return 0;
    }
    // insertion du jeton : valeur jeton = indice  du joueur + 2
    nvlig= deplacement_bas(nvJeu.grille, nvJeu.numeroJoueur+2, numerocol);
   
  }
  // fin insertion du jeton : le nouveau pion sera en nvlig, numerocol
  printGame(nvJeu, NBLIG, NBCOL);
 
 
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
   rotationHoraire(nvJeu.grille, nbcase, piv);
   }
  else {
    rotationAntiHoraire(nvJeu.grille, nbcase, piv);
   }
 
   printGame(nvJeu, NBLIG, NBCOL);
   
   // gravité suite à la rotation
   gravitePivot(nvJeu.grille, piv, nbcase);
   
   printGame(nvJeu, NBLIG, NBCOL);
  
  // si finpartie = 2 => Terminée pas de gagnant, si = 0 : gagnant
  finpartie = finJeu(nvJeu.grille, nvJeu.jo);
  
  // calcul du nouveau joueur qui doit jouer
  if (nvJeu.numeroJoueur >= nvJeu.nbJoueur-1) {
    nvJeu.numeroJoueur = 0;
  }
  else {
    nvJeu.numeroJoueur =  nvJeu.numeroJoueur+1;
  }
}
//fin de partie

// affichage résultat :
if (finpartie == 2) {
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
