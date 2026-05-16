// sélection du pivot
int sizePivot(){
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
