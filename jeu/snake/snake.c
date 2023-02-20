#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define HAUT 72
#define BAS 80
#define GAUCHE 75
#define DROITE 77

#define COMMANDE_INVALIDE -1

#define VITESSE_BASE 52

#define N_ligne 20
#define N_colone 40

//création d'un type booléen...
typedef enum booleen{
    False,
    True
}booleen;

// variables globales

int espace[N_ligne][N_colone] = {0}, x, y, tmp_y, Queue, Tete, repas, posX_repas, posY_repas, depl, direction, votre_score = 0, SCORE_MAX;
FILE *fic;
booleen jeu = True;
int vitesse_jeu = VITESSE_BASE;

// prototypes...
void cadre ();
void init_snake ();
void reinitialisation_ecran();
void position_repas();
int commande ();
void deplacement ();
void choix_direction();
void retire_Queue();
void manger ();
booleen morsure ();
void vitesse();


//___________________
//Le :::: MAIN ::::
//___________________

int main (){

    init_snake();

    while (jeu){
        cadre();
        reinitialisation_ecran();
        position_repas();
        deplacement();
        retire_Queue();
        Sleep (vitesse_jeu);
    }


    return 0;
}
//___________________


// cadre où se deroule le jeu
void cadre (){

    int j, i;
    //conception du cadre...

    for (j = 0; j <= N_colone+1; j++){
        if (j>0 && j < N_colone+1) printf ("%c", 205);
        else if (j == 0) printf ("%c", 201);
        else printf ("%c", 187);
    }

    printf ("\n");

    for (i = 0; i < N_ligne; i++){
        printf ("%c", 186);
        for (j = 0; j < N_colone; j++){
            if (espace[i][j]==0) printf (" ");
            if (espace[i][j]>0 && espace[i][j]!= Tete) printf ("%c", 249);
            else if (espace[i][j]==Tete) printf ("%c", 249);
            else if (espace[i][j]==-1) printf ("%c", 223);
            if (j == N_colone-1) printf ("%c\n", 186);
        }

    }

    for (j = 0; j <= N_colone+1; j++){
        if (j>0 && j < N_colone+1) printf ("%c", 205);
        else if (j == 0) printf ("%c", 200);
        else printf ("%c", 188);
    }


    printf ("\t  score : %d    MAX : %d", votre_score, SCORE_MAX);

}

// initialisation du serpent ...

//.......................................................................................
void init_snake (){
    fic=fopen("record.txt","r");

    SCORE_MAX = 0;

    if (fic != NULL){
        fscanf(fic,"%d",&SCORE_MAX);
        fclose(fic);
    }
       int i,j;
        direction = DROITE;

        x = N_ligne/2, y = N_colone/2, tmp_y = y, Queue = 1, Tete = 10;

        for (i = 0; i < Tete; i++){
            tmp_y++;
            espace[x][tmp_y-Tete] = i+1;
        }
}

//.......................................................................................
void reinitialisation_ecran(){
    COORD Position;
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}

//.......................................................................................
void position_repas(){
    srand(time(0));
    posX_repas = 1+ rand() % (N_ligne-2);
    posY_repas = 1 + rand() % (N_colone-2);

    if(repas == 0 && espace[posX_repas][posY_repas]==0){
        espace[posX_repas][posY_repas]= -1;
        repas = 5;
        //if(Speed>10 && score!=0) Speed = Speed - 5;
    }
}

//.......................................................................................
int commande(){
    if(_kbhit())
        return _getch();
    else
        return COMMANDE_INVALIDE;
}

//.......................................................................................
void deplacement(){
    depl = commande();
    choix_direction();

    if (depl == DROITE){
        y++;
        if (y == N_colone-1) y = 0;
        if (morsure()) Fin_Partie();
        manger();
        Tete++;
        espace[x][y] = Tete;
    }
    else if (depl == GAUCHE){
        y--;
        if (y == -1) y = N_colone-1;
        if (morsure()) Fin_Partie();
        manger();
        Tete++;
        espace[x][y] = Tete;
    }
    else if (depl == HAUT){
        x--;
        if (x == -1) x = N_ligne-1;
        if (morsure()) Fin_Partie();
        manger();
        Tete++;
        espace[x][y] = Tete;
    }
    else if (depl == BAS){
        x++;
        if (x == N_ligne-1) x = 0;
        if (morsure()) Fin_Partie();
        manger();
        Tete++;
        espace[x][y] = Tete;
    }
}

//.......................................................................................
void choix_direction (){
    if ((depl == DROITE && direction == GAUCHE) || (depl == GAUCHE && direction == DROITE) || (depl == HAUT && direction == BAS) || (depl == BAS && direction == HAUT))
        depl = direction;
    else if (depl == HAUT || depl == BAS || depl == GAUCHE || depl == DROITE)
        direction = depl;
    else depl = direction;
}

//.......................................................................................
void retire_Queue(){
    int i, j;
    for(i=0;i<N_ligne;i++){
        for(j=0;j<N_colone;j++){
            if(espace[i][j]== Queue)
                espace[i][j] = 0;
        }
    }
    Queue++;
}

//.......................................................................................
void manger (){
    if(espace[x][y]==-1){
            repas = 0;
            votre_score+=5;
            Queue -= 1;
            vitesse();
    }
}

//.......................................................................................
booleen morsure (){
    return (espace[x][y]!=0 && espace[x][y]!=-1);
}

//.......................................................................................
void Fin_Partie(){
    system("cls");
    printf("\n FIN DE LA PARTIE ... !!!!!!!!!!!!!!!");
    Sleep(2000);
    system("Cls");

    if(votre_score>SCORE_MAX){

        printf(" NOUVEAU RECORD %d!!!!!!\n\n",votre_score);

  //      sleep (200);

        fic=fopen("record.txt","w");
        if (fic == NULL)
            exit(1);

        fprintf(fic,"%d",votre_score);
        fclose(fic);
    }

    jeu = False;
}

//.......................................................................................
void vitesse (){
    if (vitesse_jeu > 5)
        vitesse_jeu -= 5;
    else
        vitesse_jeu = 0;
}
