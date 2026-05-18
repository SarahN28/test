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

 // insert piece in column 'numcol'
 // 2 if first player, 3 if second player, etc...
int deplacement_bas(int tab[NBLIG][NBCOL], int nbJ, int numcol){
  int i = 0;
  while (tab[i][numcol]==0 && i<6){
    i = i+1;
   }
  if (i==0) {
    return (-1);          // insertion impossible, column full
  } 
  tab[i-1][numcol] = nbJ;               //nbJ : number of player
  return (i-1);
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
