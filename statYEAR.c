#define SIZE 20;

void nbCrash(Accident tab[SIZE], int year){
    Accident* cur = tab[year];
    if (cur==NULL){
        printf("Il n'y a pas eu d'accidents routiers en %d.\n", &year);
    }
    int crash = 1;
    while(cur->next!=NULL){
        if(cur->next->accident.collision_id != cur->accident.collision_id){
            crash++;
        }
    }
    printf("En %d, il y a eu %d accidents.\n", &year, &crash);
}

void nbSeverity(Accident* tab[SIZE], int year){
    int indemne = 0;
    int tue = 0;
    int grave = 0;
    int leger = 0;
    Accident* cur = tab[year];
    if(cur==NULL){
        printf("Il n'y a pas eu d'accidents routiers en %d.\n", &year);
    }
    else {
        while (cur!=NULL){
            if(cur->accident.severity==1){
                indemne++;
            }
            else if(cur->accident.severity==2){
                tue++;
            }
            else if(cur->accident.severity==3){
                grave++;
            }
            else if(cur->accident.severity==4){
                leger++;
            }
            cur=cur->next;
        }
        printf("En %d, il y a eu :\n", &year);
        printf("  → %d indemnes\n", &indemne);
        printf("  → %d tués\n", &tue);
        printf("  → %d blessés gravement\n", &grave);
        printf("  → %d blessés légèrement\n", &leger);
    }
}