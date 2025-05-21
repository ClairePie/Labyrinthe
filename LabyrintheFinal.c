#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <setjmp.h> // Pour quitter la récursivité au cas ou le programme à plusieurs solutions

jmp_buf buf;
//                      ALGO 2

    // STRUCTURE
typedef struct coor{ //Structure de coordonnées
    int colonne;
    int ligne;
}tcoor;
typedef struct elListe*pelListe;//      LISTE
typedef struct elListe{ //Liste de coordonnées pour enregistrer toutes les possibilitées
    tcoor v;
    pelListe next;
}telListe;
typedef struct elListetot*pelListetot;//      LISTE total
typedef struct elListetot{ // Liste d'entiers pour enregistrer le nombre de pas
    int v;
    pelListetot next;
}telListetot;

// GENERATION LABYRINTHE

void deleteSolution(int size, int **matrice, int colonne, int ligne, int *newcolonne, int *newligne){
    struct timeval tv; //with microsecondes bigger diversity of numbers
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    int val2 = rand()%2+1;
    int i;
    for(i=0; i<100000000; i++); //Boucle d'un certain temps (depends du CPU), permet d'avoir des nombres plus aléatoires
    switch (val2){
        case 1 : 
            if(colonne<size-2){ // A Droite
                matrice[ligne][colonne+1]=0;
                *newcolonne = colonne+2;
                *newligne=ligne;
            }
            else if(ligne>1){ // Au dessus
                matrice[ligne-1][colonne]=0;
                *newcolonne= colonne;
                *newligne=ligne-2;
            }
            break;
        case 2 :
            if(ligne<size-2){ // En dessous
                matrice[ligne+1][colonne]=0;
                *newcolonne = colonne;
                *newligne=ligne+2;
            }
            else if(colonne>1){ // A gauche
                matrice[ligne][colonne-1]=0;
                *newcolonne = colonne-2;
                *newligne=ligne;
            }
            break; 
    }
}
void CreationSolution(int size, int **matrice, int entre, int sortie){
    int i, colonne, ligne, newcolonne=0, newligne=0, colonneFin;
    colonne = entre; 
    ligne =1;
    do{//Créer le chemin 
        deleteSolution(size, matrice, colonne, ligne, &newcolonne, &newligne);
        colonne=newcolonne;
        ligne=newligne;
    }while(newcolonne!=sortie || newligne!=size-2);
}
void creationPassage( int size, int **matrice){
    int i, j, entre, sortie, val2; 
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    do{
        entre=rand()%((size-1)/2);
    }while(entre%2==0);
    matrice[0][entre]=0; //Entre
    do{
        sortie=(rand()%((size-1)/2))+((size-1)/2);
    }while(sortie%2==0);
    matrice[size-1][sortie]=0;//Sortie
    CreationSolution(size, matrice, entre, sortie);
    for(i=1; i<size-1; i++){
        for(j=1; j<size-1; j++){
            if(i%2==1&&j%2==1){
                val2=rand()%2+1;
                switch (val2){
                    case 1 : 
                        if(j!=size-2){
                            matrice[i][j+1]=0;
                        }
                        else if(i!=size-2){
                            matrice[i+1][j]=0;
                        }
                        break;
                    case 2 :
                        if(i!=size-2){
                            matrice[i+1][j]=0;
                        }
                        else if(j!=size-2){
                            matrice[i][j+1]=0;
                        }
                    break;       
                }
            }
        }
    }
    
}

//          Merged algorithm
void affiche(int size, int t[size][size]){
    int i, j;
    printf("Labyrinthe :\n");
    for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            if(t[i][j]==1){ // Affiche les murs
                printf("- ");
            }else if(t[i][j]==5){ //Affiche passage utilisé
                printf(". ");
            }else if(t[i][j]==6){ //Affiche Cul-de-sac
                printf("x ");
            }else if(t[i][j]==2){ // Affiche position
                printf("I ");
            }else if(i==0){
                printf("S ");
            }else if(i==size-1){
                printf("E ");
            }else { //Affiche les passages
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
void comparaison(int *pasAlgo1, int *pasAlgo2, int *pasAlgo3){
    if((*pasAlgo1)<(*pasAlgo2)){
        if((*pasAlgo1)<(*pasAlgo3)){
            printf("L algorithme 1 est le plus rapide.\n");
        }else if((*pasAlgo1)==(*pasAlgo3)){
            printf("Les algorithmes 1 et 3 sont les plus rapides.\n");
        }else {
            printf("L algorithme 3 est le plus rapide.\n");
        }
    }else if((*pasAlgo1)==(*pasAlgo2)){
        if((*pasAlgo1)<(*pasAlgo3)){
            printf("Les algorithmes 1 et 2 sont les plus rapides.\n");
        }else if((*pasAlgo1)==(*pasAlgo3)){
            printf("Les algorithmes 1, 2 et 3 sont egalement rapides.\n");
        }else {
            printf("L algorithme 3 est le plus rapide.\n");
        }
    }else{
        if((*pasAlgo2)<(*pasAlgo3)){
            printf("L algorithme 2 est le plus rapide.\n");
        } else if((*pasAlgo2)==(*pasAlgo3)){
            printf("Les algorithmes 2 et 3 sont les plus rapides.\n");
        }else {
            printf("L algorithme 3 est le plus rapide.\n");
        }
    }
    printf("\n\n");
}
int **dimension (int *size, int **t){
    int i, j;
    do{
        printf("Entrez les dimensions de la matrice (impaire) :\n"); // Nombre impair 
        scanf("%i", &(*size));
    }while((*size)%2!=1);
    t = (int **)malloc((*size) * sizeof(int));
    for(i=0; i<(*size); i++){
        t[i]=(int*)malloc((*size) * sizeof(int));
    }
    for(i=0; i<(*size); i++){ //ligne
        for(j=0; j<(*size); j++){//colonne
            if(j==((*size)-1)||j==0){ //Les colonnes sur le cotés et la fin 
                t[i][j]=1;
            }else if(i%2==0){
                t[i][j]=1;
            }else if(j%2==0){
                t[i][j]=1;
            }else{
                t[i][j]=0;
            }
        }
    }
    printf("Veuillez patientez, generation du labyrinthe...\n\n");
    creationPassage(*size, t);
    return t;
}
void copieLabyrinthe(int **t, int size, int c[size][size]){ //** Car crée un **t
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            c[i][j]=t[i][j];
        }
    }
}
void traductionAlgo12(int size, int c[size][size]){
    int i;
    for(i=0; i<size; i++){
        if(c[0][i]==0){ //Entrée
            c[0][i]=3;
        }
    }
}


//                      ALGO 1
void changement(int size, int t[size][size], int i, int j, int o, int k, int s){ // déplacement du 2 (position)
    if(s<=0){
        t[o][k] = 2;
        t[i][j] = 5;
    }
    else{
        t[o][k] = 2;
        t[i][j] = 6;
    }
}
int gagner1(int size, int t[size][size], int n){ // lorsque labyrinthe fini
    affiche(size, t);
    printf("L algorithme 1 a necessite %i pas.\n\n",n);
    return 1;
}
int verif(int size, int t[size][size],int *p, int *q, int *pas, int *s){ // verif de déplacement
    int i = *p; //ligne 
    int j = *q; //colonne
    if(t[i][j+1]==3){ // si gagner
        *p = i;
        *q = j+1;
        *s = 0;
        changement(size, t,i,j,i,j+1,*s);
        (*pas)++;
        return gagner1 (size, t, *pas); // retourne le nombre de pas final
    }
    if(((t[i+1][j+1]==1)||(t[i+1][j+1]==6))&&((t[i-1][j+1]==1)||(t[i-1][j+1]==6))&&((t[i][j+2]==1)||(t[i][j+2]==6))&&((t[i][j+1]==0)||(t[i][j+1]==5))){ // si cul de sac après
        (*pas) = (*pas)+2;
        t[i][j+1]=6;
        return 0;
    }
    if(t[i][j+1]==0){ // espace libre droite
        *p = i;
        *q = j+1;
        (*pas)++;
        (*s) --;
        changement(size, t,i,j,i,j+1,*s);
        return 0;
    }
    if(t[i][j+1]==5){ // espace libre droite
        *p = i;
        *q = j+1;
        (*pas)++;
        changement(size, t,i,j,i,j+1,*s);
        *s = 2;
        return 0;
    }
    if((t[i][j+1]==1)||(t[i][j+1])==4||(t[i][j+1]==6)){ // si mur droite
        if(t[i-1][j]==3){
            (*pas)++;
            return gagner1(size, t, *pas);
        }
        if(((t[i-1][j-1]==1)||(t[i-1][j-1]==6))&&((t[i-2][j]==1)||(t[i-2][j]==6))&&((t[i-1][j+1]==1)||(t[i-1][j+1]==6))&&((t[i-1][j]==0)||(t[i-1][j]==5))){ // si cul de sac après
            (*pas) = (*pas)+2;
            t[i-1][j]=6;
            return 0;
        }
        if((t[i-1][j])==0){ // espace libre haut
            changement(size, t,i,j,i-1,j,*s);
            *p = i-1;
            *q = j;
            (*pas)++;
            (*s) --;
            return 0;
        }
        if(t[i-1][j]==5){ // espace libre haut
            *p = i-1;
            *q = j;
            (*pas)++;
            changement(size, t,i,j,i-1,j,*s);
            *s = 2;
            return 0;
            }
        if((t[i-1][j]==1)||(t[i-1][j]==4)||(t[i-1][j]==6)){ // si mur haut
            if(t[i][j-1]==3){
                (*pas)++;
                return gagner1(size, t, *pas);
            }
            if(((t[i][j-2]==1)||(t[i][j-2]==6))&&((t[i-1][j-1]==1)||(t[i-1][j-1]==6))&&((t[i+1][j-1]==1)||(t[i+1][j-1]==6))&&((t[i][j-1]==0)||(t[i][j-1]==5))){ // si cul de sac après
                (*pas) = (*pas)+2;
                t[i][j-1]=6;
                return 0;
            }
            if((t[i][j-1])==0){ // espace libre gauche
                changement(size, t,i,j,i,j-1,*s);
                *p = i;
                *q = j-1;
                (*pas)++;
                (*s) --;
                return 0;
            }
            if(t[i][j-1]==5){ // espace libre gauche
                *p = i;
                *q = j-1;
                (*pas)++;
                changement(size, t,i,j,i,j-1,*s);
                *s = 2;
                return 0;
                }
            if(((t[i][j-1]==1)||(t[i][j-1]==6))&&((t[i-1][j]==1)||(t[i-1][j]==6))&&((t[i+1][j]==1)||(t[i+1][j]==6))&&((t[i][j+1]==1)||(t[i][j+1]==6))){ // si cul de sac après
                *p = i;
                *q = j-1;
                t[i][j] = 6;
                t[i][j-1] = 2;
                (*pas)++;
                (*s)--;
                return 0;
            }
            if((t[i][j-1])==1||(t[i][j-1]== 4)||(t[i][j-1]==6)){ // si mur à gauche
                if(t[i+1][j]==3){
                    (*pas)++;
                    return gagner1(size, t, *pas);
                }
                if(((t[i+2][j]==1)||(t[i+2][j]==6))&&((t[i+1][j-1]==1)||(t[i+1][j-1]==6))&&((t[i+1][j+1]==1)||(t[i+1][j+1]==6))&&((t[i+1][j]==0)||(t[i+1][j]==5))){ // si cul de sac après
                    (*pas) = (*pas)+2;
                    t[i+1][j]=6;
                    return 0;
                }
                if(t[i+1][j]==0){ // espace libre bas
                    changement(size, t, i, j, i+1, j,*s);
                    *p = i+1;
                    *q = j;
                    (*pas)++;
                    (*s) --;
                    return 0;
                }
                if(t[i+1][j]==5){ // espace libre bas
                    *p = i+1;
                    *q = j;
                    (*pas)++;
                    changement(size, t,i,j,i+1,j,*s);
                    *s = 2;
                    return 0;
                }
                if((t[i+1][j]==1)||(t[i+1][j])==4||(t[i+1][j]==6)){ // si mur bas
                    return -1;
                }
            }
        }
    }
    return -1;
}
void algo1(int size, int t[size][size], int *pasAlgo1){
    int x,y,res, s = 0, i; 
    for(i=0; i<size; i++){
        if(t[size-1][i]==0){
            x=size-1;
            y=i;
        }
    }
    while(1){ // boucle infinie 
        res = verif(size, t, &x, &y, pasAlgo1, &s);
        if(res==1) {
            break;
        }
        else if(res==-1) {
            printf("Echec, vous etes bloque.\n");
            break;
        }
    }
}


//                      ALGO 2
    //  LISTE
pelListe deleteListe(pelListe I, tcoor val){ //Supprime de la liste de coordonnées 
    pelListe aux; 
    if(I==NULL){
        return I;
    }
    else{
        if(I->v.colonne==val.colonne&&I->v.ligne==val.ligne){ //SI les coordonnées sont déja enregistrer (utile aprés AddListe): supprime les coordonnées 
            aux=I;
            I=I->next;
            free(aux);
            return I;
        }
        else{
            I->next=deleteListe(I->next, val); //Sinon continue à chercher
            return I;
        }
    }
}
pelListe deleteListeAll(pelListe I){ // SUpprime la totalité de la liste après modification 
    pelListe aux;
    while(I!=NULL){
        aux=I;
        I=I->next;
        free(aux);
    }
    return I;
}
pelListe elemCreationListe(tcoor val){ // Ajoute dans la liste de coordonnées
    pelListe aux=(pelListe)malloc(sizeof(telListe));
    aux->v=val;
    aux->next=NULL;
    return aux;
}
pelListe addListe(pelListe I, tcoor val, int *dest){
    pelListe aux;
    int tmp=0;
    aux = I;
    if(I==NULL){
        return elemCreationListe(val);
    }
    else{
        while(aux!=NULL){
            if(val.colonne==aux->v.colonne&&val.ligne==aux->v.ligne){ // Si les coordonnées sont déja présentent dans la liste, les supprime
                I=deleteListe(I, val);
                (*dest)--; // Du coup une destination en moins
                return I;
            }
            aux=aux->next;
        }
        aux=elemCreationListe(val); //Sinon ajoute les coordonnées
        aux->next =I;
        return aux;
    }
}
    //  LISTE
pelListetot deleteListetot(pelListetot I, int val){ //Supprime les éléments de la liste qui ne servent à rien (cul-de-sac et chemin qui ne mènent pas à la solution)
    pelListetot aux; 
    if(I==NULL){
        return I;
    }
    else{
        if(I->v==val){
            aux=I;
            I=I->next;
            free(aux);
            return I;
        }
        else{
            I->next=deleteListetot(I->next, val);
            return I;
        }
    }
}
pelListetot deleteListeAlltot(pelListetot I){ // Free la totalité de la mémoire alloc to my computer add the end of the programme
    pelListetot aux;
    while(I!=NULL){
        aux=I;
        I=I->next;
        free(aux);
    }
    return I;
}
pelListetot elemCreationListetot(int val){ //Ajoute des éléments à la liste d'entier
    pelListetot aux=(pelListetot)malloc(sizeof(telListetot));
    aux->v=val;
    aux->next=NULL;
    return aux;
}
pelListetot addListetot(pelListetot I, int val){ //Ajoute à la liste d'entier
    pelListetot aux;
    int tmp=0;
    aux = I;
    if(I==NULL){
        return elemCreationListetot(val); //Si liste vide
    }
    else{
        while(aux!=NULL){
            aux=aux->next;
        }
        aux=elemCreationListetot(val); //Sinon cherche la fin de la liste
        aux->next =I;
        return aux;
    }
}
    // ALGO 2 
tcoor findBegin(int size, int t[size][size]){ //trouve le début du labyrinth
    int j;
    tcoor n; 
    for(j=0; j<size; j++){
        if(t[size-1][j]==0){
            n.colonne=j;
            n.ligne=size-1;
        }
    }
    return n;
}
pelListe destination (int size, int t[size][size], tcoor n, int *dest, pelListe I){
    tcoor tmp;
    if( n.colonne+1!=size-1 && t[n.ligne][n.colonne+1]==0 ){ // A droite // Test les possibilité de déplacement et les enregistre dans la liste
        tmp.colonne = n.colonne+1; // Les bornes avec size et 0 ne sont pas utile
        tmp.ligne = n.ligne;
        (*dest)++; //Augmente le nombre de possibilité
        I=addListe(I, tmp, dest);// Si la possibilité est dèja enregistrer (position précédente) Supprime les coordonnées et dest - 1
    }
    if(n.ligne+1!=size-1 && t[n.ligne+1][n.colonne]==0){ // En dessous
        tmp.colonne = n.colonne;
        tmp.ligne = n.ligne+1;
        (*dest)++;
        I=addListe(I, tmp, dest);
    }
    if(n.colonne != 0 && t[n.ligne][n.colonne-1]==0){ // A gauche
        tmp.colonne = n.colonne-1;
        tmp.ligne = n.ligne;
        (*dest)++;
        I=addListe(I, tmp, dest);
    }
    if(n.ligne!= 0 && t[n.ligne-1][n.colonne]==0){ // Au dessus
        tmp.colonne = n.colonne;
        tmp.ligne = n.ligne-1;
        (*dest)++;
        I=addListe(I, tmp, dest);
    }
    return I;
}
int cheminCreation(int pas, pelListe *I, tcoor *n, tcoor *tmp, int *dest){
    tcoor tmpI;
        // Enregistre nouvelle destination : 
    tmpI.colonne=(*I)->v.colonne;
    tmpI.ligne=(*I)->v.ligne;
        //Enregistre ancienne position pour future liste 
    (*tmp).colonne=(*n).colonne;
    (*tmp).ligne=(*n).ligne;
        //Supprime ce qui était utilisé avant (pour trouver les première possibilité)
    *I=deleteListeAll(*I); // new liste for I (the number/coordonnées of the potential destination)
    *dest = 0;  
        //Enregistre dernière position pour ne pas repasser
    *I=addListe(*I, *n, dest);        
        //Nouvelle position (déplace le pion)
    (*n).colonne=tmpI.colonne;
    (*n).ligne=tmpI.ligne;
    pas++;// Enregistre le nombre de pas
    return pas;//return is useless because pas est un pointeur
}
void lecture(pelListetot tot, int *pasAlgo2){ // compte les nombres de la liste (le nombre de pas de l'entré à la sortie)
    pelListetot aux=tot;
    int pasTot=0;
    while(aux!=NULL){
        pasTot=pasTot+aux->v;
        aux=aux->next;
    }
    (*pasAlgo2)=pasTot;
    printf("L algorithme 2 a necessite %i pas.\n\n", pasTot);
}
pelListetot moveAlgo2(int size, int t[size][size], tcoor *n, int *pas, pelListetot tot, tcoor tmp, int *pasAlgo2){ 
    int dest=0, pval, val, stop; 
    pelListe I=NULL, aux; 
    tcoor tmpI;
    I=addListe(I, tmp, &dest);  // ENregistre la position précedente
    I=destination(size, t, *n, &dest, I); // En fonction de dest s'occupe des déplacements
    switch(dest){
        case 0 : 
            if((*n).ligne==0){ // Si trouve la sortie Affiche le nombre de pas 
                (*pas)++;
                //printf("Le labyrinthe est résolu !!\n");
                tot = addListetot(tot, *pas);
                lecture(tot, pasAlgo2);
                longjmp(buf, 1);
            }
            *pas=0; //Sinon pas = 0 (chemin inutile, cul de sac)
            break;
        case 1 :
            *pas= cheminCreation(*pas, &I, n, &tmp, &dest); //Jusqu'a prochain carrefour pas ++ 
            tot=moveAlgo2(size, t, n, pas, tot, tmp, pasAlgo2); 
            break;
        case 2 : 
            aux=I;
            val=*pas;// SI plusieurs possibilité les étudient chacune leurs tours. Je pourrais utiliser une boucle for pour moins de ligne
            tot = addListetot(tot, *pas);
            *pas=1;
            tmp=*n;
            *n=aux->v;// Update les positions
            tot = moveAlgo2(size, t, n, pas, tot, tmp, pasAlgo2);//Recommence avec le nouveau chemin
            tot = addListetot(tot, *pas);
            aux=aux->next;
            *pas=1;
            (*n)=aux->v;
            tot = moveAlgo2(size, t, n, pas, tot, tmp, pasAlgo2);//Recommence avec le nouveau chemin
            tot = deleteListetot(tot, val);// Si aucune des possibilité à trouver la solution supprime le nombre de pas de la liste
            break; 
        case 3 : // Même chose que case 2 
            aux=I;
            val=*pas;
            tot = addListetot(tot, *pas);
            *pas=1;
            tmp=*n;
            *n=aux->v;
            tot = moveAlgo2(size, t, n, pas, tot, tmp, pasAlgo2);
            tot =addListetot(tot, *pas);
            aux=aux->next;
            *pas=1;
            *n=aux->v;
            tot = moveAlgo2(size, t, n, pas, tot, tmp, pasAlgo2);
            tot = addListetot(tot, *pas);
            aux=aux->next;
            *pas=1;
            *n=aux->v;
            tot = moveAlgo2(size, t, n, pas, tot, tmp, pasAlgo2);
            tot =deleteListetot(tot, val);
            break; 
    }
    return tot;
}
void algo2(int size, int t[size][size], int *pasAlgo2){
    int dest =0, pas =0;
    tcoor n, tmp;
    pelListe I = NULL;
    pelListetot tot=NULL;
    n =findBegin(size, t); //trouve le début
    I=destination(size, t, n, &dest, I); //Lance le debut (deplacement à la première position possible dans le labyrinthe)
    tmp=n;
    n=I->v;
    pas=2;// Update les paramètres
    if(setjmp(buf)==0){ //permet de quitter la récursivité
        tot = moveAlgo2(size, t, &n, &pas, tot, tmp, pasAlgo2);
    }
    I=deleteListeAll(I); //libére la mémoire de mon ordi 
    tot = deleteListeAlltot(tot);
}


//                      ALGO 3
void changementAlgo3(int size, int t[size][size], int i, int j, int o, int k){
    t[o][k]=2;
    t[i][j]=5;
}
int gagner1Algo3(int size, int t[size][size], int n){ // lorsque labyrinthe fini
    affiche(size, t);
    printf("L algorithme 3 a necessite %i pas.\n\n",n);
    return 1;
}
int deplaceAlgo3(int size, int t[size][size], int *p, int *q,int *pas){
    int i,j;
    i = *p;
    j = *q;
    int pos = rand()%4+1;
    if(pos==1){
        if(((t[i+1][j+1]==1)||(t[i+1][j+1]==6))&&((t[i-1][j+1]==1)||(t[i-1][j+1]==6))&&((t[i][j+2]==1)||(t[i][j+2]==6))&&((t[i][j+1]==0)||(t[i][j+1]==5))){ // si cul de sac après
            (*pas) = (*pas)+2;
            t[i][j+1]=6;
            return 0;
        }
        if(t[i][j+1]==1||t[i][j+1]==6){
            return 0;
        }
        if(t[i][j+1]==0||t[i][j+1]==5){
            *p = i;
            *q = j+1;
            (*pas)++;
            changementAlgo3(size, t,i,j,i,j+1);
            return 0;
        }
        if(t[i][j+1]==3){
            *p = i;
            *q = j+1;
            changementAlgo3(size, t,i,j,i,j+1);
            (*pas)++;
            return gagner1Algo3(size, t, *pas); // retourne le nombre de pas final    
        }
    }
    if(pos==2){
        if(((t[i-1][j-1]==1)||(t[i-1][j-1]==6))&&((t[i-2][j]==1)||(t[i-2][j]==6))&&((t[i-1][j+1]==1)||(t[i-1][j+1]==6))&&((t[i-1][j]==0)||(t[i-1][j]==5))){ // si cul de sac après
            (*pas) = (*pas)+2;
            t[i-1][j]=6;
            return 0;
        }
        if(t[i-1][j]==1||t[i-1][j]==6){
            return 0;
        }
        if(t[i-1][j]==0||t[i-1][j]==5){
            *p = i-1;
            *q = j;
            (*pas)++;
            changementAlgo3(size, t,i,j,i-1,j);
            return 0;
        }
        if(t[i-1][j]==3){
            *p = i-1;
            *q = j;
            changementAlgo3(size, t,i,j,i-1,j);
            (*pas)++;
            return gagner1Algo3(size, t, *pas); // retourne le nombre de pas final    
        }
    }
    if(pos==3){
        if(((t[i][j-2]==1)||(t[i][j-2]==6))&&((t[i-1][j-1]==1)||(t[i-1][j-1]==6))&&((t[i+1][j-1]==1)||(t[i+1][j-1]==6))&&((t[i][j-1]==0)||(t[i][j-1]==5))){ // si cul de sac après
            (*pas) = (*pas)+2;
            t[i][j-1]=6;
            return 0;
        }
        if(t[i][j-1]==1||t[i][j-1]==6){
            return 0;
        }
        if(t[i][j-1]==0||t[i][j-1]==5){
            *p = i;
            *q = j-1;
            (*pas)++;
            changementAlgo3(size, t,i,j,i,j-1);
            return 0;
        }
        if(t[i][j-1]==3){
            *p = i;
            *q = j-1;
            changementAlgo3(size, t,i,j,i,j-1);
            (*pas)++;
            return gagner1Algo3(size, t, *pas); // retourne le nombre de pas final    
        }
    }
    if(pos==4){
        if(((t[i+2][j]==1)||(t[i+2][j]==6))&&((t[i+1][j-1]==1)||(t[i+1][j-1]==6))&&((t[i+1][j+1]==1)||(t[i+1][j+1]==6))&&((t[i+1][j]==0)||(t[i+1][j]==5))){ // si cul de sac après
            (*pas) = (*pas)+2;
            t[i+1][j]=6;
            return 0;
        }
        if(t[i+1][j]==1||t[i+1][j]==6){
            return 0;
        }
        if(t[i+1][j]==0||t[i+1][j]==5){
            *p = i+1;
            *q = j;
            (*pas)++;
            changementAlgo3(size, t,i,j,i+1,j);
            return 0;
        }
        if(t[i+1][j]==3){
            *p = i+1;
            *q = j;
            changementAlgo3(size, t,i,j,i+1,j);
            (*pas)++;
            return gagner1Algo3(size, t, *pas); // retourne le nombre de pas final    
        }
    }
}
void algo3(int size, int t[size][size], int *pasAlgo3){
    int x,y,res, i; 
    for(i=0; i<size; i++){
        if(t[size-1][i]==0){
            x=size-1;
            y=i;
        }
    }
    while(1){
        res = deplaceAlgo3(size, t, &x, &y, pasAlgo3);
        if(res==1) {
            break;
        }
    }
    
}

int main(){
    int pasAlgo1=0, pasAlgo2, pasAlgo3 =0, i;
    int size;
    int **p=dimension(&size, p);
    int c[size][size], t[size][size];
    copieLabyrinthe(p, size, c); //passe de double pointeur à matrice
    traductionAlgo12(size, c);
    copieLabyrinthe(p, size, t);
    affiche(size, t);
    algo1(size, c, &pasAlgo1);
    algo2(size, t, &pasAlgo2);
    copieLabyrinthe(p, size, c);
    traductionAlgo12(size, c);
    algo3(size, c, &pasAlgo3);
    comparaison(&pasAlgo1, &pasAlgo2, &pasAlgo3);
    for(i=0; i<size; i++){
        free(p[i]);
    }
    free(p);
}
