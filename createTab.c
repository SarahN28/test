typedef struct accident{
    BulkLoadedCarCrashCSVRow accident;
    struct accident* next;
} Accident;

Accident* insertAccident(Accident tab[], int index, Accident x){
    if(tab[index]==NULL){
        tab[index] = x;
    }
    else {
        Accident cur = tab[index].accident;
        while (cur->next !=NULL){
            cur = cur->next;
        }
        cur->next = x;
    }
    return tab;
}

Accident* createTab(FILE *file){
    if (file==NULL){
        exit(44);
    }
    Accident new;
    while(!feof(file)){
        fscanf(file, "%d;%d;%d;%d;%d;%d;%d;%d;%d", &new->accident.year, &new->accident.collision_id, &new->accident.vehicule_id,  &new->accident.location,  &new->accident.user_type,  &new->accident.severity, &new->accident.gender, &new->accident.birth_year, &new->accident.purpose);
        new->next = NULL;
        tab = insertAccident(tab, (new->accident.year)-2005, new);
    }
    return tab;
}