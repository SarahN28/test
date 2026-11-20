#include <stdlib.h>
#include <stdio.h>

void displayMenu(){
    printf("☆ Statistique par année :\n");
    for (int i= 0; i<20; i++){
        printf("    ► %d\n", 2005+i);
    }
}

int main(){
    displayMenu();
    return 0;
}