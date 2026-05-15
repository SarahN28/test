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
