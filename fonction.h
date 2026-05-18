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
