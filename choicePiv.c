 // selection du pivot : le carré doit contenir le dernier jeton mis, et doit appartenir à la grille
 // la ligne du pivot soit être à n case de celle du jeton, n étant le nb de case pivotant autour du pivot (nbpivot/2), le carré doit rester dans la grille
 // la colonne du pivot soit être à n case de celle du jeton, n étant le nb de case pivotant autour du pivot (nbpivot/2), le carré doit rester dans la grille 
pivot choixPivot(int n, int lig, int col) {              //lig = (i+1) of previous fonction   &    col = 
  int i=0, j=0;
  int ligmin, ligmax, colmin, colmax;
  pivot c;
  char carlu;
  
  printf("Votre nouveau jeton est en l%d, c%d \n", lig+1, col+1);
    
  // le carré de rotation doit contenir le pion (en lig, col)
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
 
