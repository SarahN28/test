#define SIZE 20;

int nbCrash(Accident tab[SIZE], int year){
    Accident* cur = tab[year];
    if (cur==NULL){
        return 0;
    }
    int crash = 1;
    while(cur->next!=NULL){
        if(cur->next->accident.collision_id != cur->accident.collision_id){
            crash++;
        }
    }
    return crash;
}