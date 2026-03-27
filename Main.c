#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "textures.h"
#include "affichage.h"

#define N 12
#define M 12
#define NB_ITEMS 34
#define T 32
#define MENU 386

int V[N][M];
int Tableau_final[N*T][M*T];
int a = 0;
int b = 0;
char c;
int collection_items;
time_t temps_depart_niveau = 0;


typedef struct {
    int objectif_score;
    int coups_max;
} Configuration_niveau;

int score = 0;
int coups_restants = 0;
int niveau_en_cours = 1;

int timer(int temps_max);
void afficher_score(int score);
void afficher_coups(int coups);

int niveau_1[N][M] = {
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,0,0,0,0,0,0,0,0,1,1},
{1,0,0,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0}
};

int niveau_2[N][M] = {
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1},
{1,1,0,0,0,0,0,0,0,0,1,1},
{1,1,1,0,0,0,0,0,0,1,1,1},
{1,1,0,0,0,0,0,0,0,0,1,1},
{1,0,0,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0}
};


int niveau_3[N][M] = {
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0}
};

int niveau_4[N][M] = {
{1,0,0,0,0,1,1,1,1,1,1,1},
{1,1,0,0,0,0,1,1,1,1,1,1},
{1,1,1,0,0,0,0,1,1,1,1,1},
{1,1,0,0,0,0,0,0,1,1,1,1},
{1,0,0,0,1,1,0,0,0,1,1,1},
{1,0,0,0,1,1,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,1},
{1,1,1,0,0,0,0,0,0,0,0,1},
{1,1,1,1,0,0,0,0,0,0,1,1},
{1,1,1,0,0,0,0,0,0,1,1,1},
{1,1,0,0,0,0,0,0,1,1,1,1},
{1,0,0,0,0,0,0,1,1,1,1,1}
};

int niveau_5[N][M] = {
{1,1,1,0,1,1,1,1,0,1,1,1},
{1,1,0,0,1,1,1,1,0,0,1,1},
{1,0,0,0,1,1,1,1,0,0,0,1},
{1,0,1,0,0,1,1,0,0,1,0,1},
{0,0,1,0,0,1,1,0,0,1,0,0},
{0,0,0,0,0,1,1,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,0,0},
{0,0,0,1,1,1,1,1,1,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,0,0,1,1,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1},
{1,1,0,0,0,0,0,0,0,0,1,1}
};



int (*item[NB_ITEMS])[T];

void sauvegarder_progression(int niveau_debloque) {
    FILE *fichier = fopen("save.txt", "w");
    if (fichier != NULL) {
        fprintf(fichier, "%d", niveau_debloque);
        fclose(fichier);
    }
}

int charger_progression() {
    int niveau_debloque = 1; 
    FILE *fichier = fopen("save.txt", "r");
    if (fichier != NULL) {
        fscanf(fichier, "%d", &niveau_debloque);
        fclose(fichier);
    }
    return niveau_debloque;
}


void copier_texture(int x0, int y0, int texture[T][T])
{
    for (int i = 0; i < T; i++)
        for (int j = 0; j < T; j++)
            Tableau_final[y0 + i][x0 + j] = texture[i][j];
}

void construire_tableau_final()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int id = V[i][j];
            int (*texture)[T] = item[id];

            int x0 = j * T;
            int y0 = i * T;

            copier_texture(x0, y0, texture);
        }
    }
}



void tableau(int V[N][M], int niv[N][M], int collection_items) 
{


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (collection_items == 1)
            {
                if (niv[i][j] == 1) 
                {
                V[i][j] = 1; 
                continue; 
                }
            }
            if (collection_items == 2)
            {
                if (niv[i][j] == 1) 
                {
                V[i][j] = 10; 
                continue; 
                }
            }
            if (collection_items == 3)
            {
                if (niv[i][j] == 1) 
                {
                V[i][j] = 18; 
                continue; 
                }
            }
            if (collection_items == 4)
            {
                if (niv[i][j] == 1) 
                {
                V[i][j] = 27; 
                continue; 
                }
            }
            if (collection_items == 5)
            {
                if (niv[i][j] == 1) 
                {
                V[i][j] = 1; 
                continue; 
                }
            }

           
            if(collection_items == 1) V[i][j] = rand() % 8 + 2;
            else if (collection_items == 2) V[i][j] = rand() % 7 + 11;
            else if (collection_items == 3) V[i][j] = rand() % 7 + 19;
            else if (collection_items == 4) V[i][j] = rand() % 6 + 28;

           

            int combo = 1;
            while (combo) {
                combo = 0; 


                if (j > 1 && V[i][j] == V[i][j-1] && V[i][j] == V[i][j-2]) {
                    combo = 1;
                }
        
                if (i > 1 && V[i][j] == V[i-1][j] && V[i][j] == V[i-2][j]) {
                    combo = 1;
                }

                if (combo) {
                    if(collection_items == 1) V[i][j] = rand() % 8 + 2;
                    else if (collection_items == 2) V[i][j] = rand() % 7 + 11;
                    else if (collection_items == 3) V[i][j] = rand() % 7 + 19;
                    else if (collection_items == 4) V[i][j] = rand() % 6 + 29;
                    else if (collection_items == 5) V[i][j] = rand() % 8 + 2;
                
                }
            }
        }
    }
}

 void crochets(int a, int b)
{
    static char ligne[200000]; 
    int pos;

    for (int i = 0; i < N; i++)
    {
        for (int px = 0; px < T; px++)
        {
            pos = 0;

            for (int j = 0; j < M; j++)
            {
                int id = V[i][j];
                int (*Tb)[T] = item[id];
                if (i == a && j == b)
                    pos += snprintf(ligne + pos,sizeof(ligne), "\033[41m  \033[0m"); 
                else
                    pos += snprintf(ligne + pos,sizeof(ligne), "\033[48;2;20;20;20m  \033[0m"); 

                for (int py = 0; py < T; py++)
                {
                    int c = Tb[px][py];
                    int r = (c / 32) * 85;          
                    int g = ((c % 32) / 8) * 85;     
                    int b = (c % 8) * 36;            

                    pos += snprintf(ligne + pos,sizeof(ligne), "\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
                }
                if (i == a && j == b)
                    pos += snprintf(ligne + pos,sizeof(ligne), "\033[41m  \033[0m");
                else
                    pos += snprintf(ligne + pos,sizeof(ligne), "\033[48;2;20;20;20m  \033[0m");
            }
            printf("%s\n", ligne);
        }
    }
}



void permutation(int a, int b, char sens)
{
    if(V[a][b] != 1 && V[a][b] != 10 && V[a][b] != 18 && V[a][b] != 27)
    {
        int temp;

        if (sens=='z' && a > 0)
        {
            if (V[a-1][b] != 1 && V[a-1][b] != 10 && V[a-1][b] != 18 && V[a-1][b] != 27 )
            {
                temp = V[a][b];
                V[a][b] = V[a-1][b];
                V[a-1][b] = temp;
            }
           
        }
        else if (sens=='s' && a < N-1)
        {
            if (V[a+1][b] != 1 && V[a+1][b] != 10 && V[a+1][b] != 18 && V[a+1][b] != 27 )
            {
                temp = V[a][b];
                V[a][b] = V[a+1][b];
                V[a+1][b] = temp; 
            }
           
        }
        else if (sens=='q' && b > 0)
        {
            if (V[a][b-1] != 1 && V[a][b-1] != 10 && V[a][b-1] != 18 && V[a][b-1] != 27 )
            {
                temp = V[a][b];
                V[a][b] = V[a][b-1];
                V[a][b-1] = temp;  
            }

        }
        else if (sens=='d' && b < M-1)
        {
            if (V[a][b+1] != 1 && V[a][b+1] != 10 && V[a][b+1] != 18 && V[a][b+1] != 27)
            {
                temp = V[a][b];
                V[a][b] = V[a][b+1];
                V[a][b+1] = temp;  
            }
           
        }
    }

}


int combo(int V[N][M], int score, int collection_items)
{
    int i, j, k, l;
    int points = 0;

    int sup[N][M] = {0};

            for (i = 2; i < N; i++)
                    for (j = 0; j < M; j++)
                        {
                        if(V[i][j] != 1 && V[i][j] != 10 && V[i][j] != 18 && V[i][j] != 27)
                        if (V[i][j] == V[i-1][j] && V[i][j] == V[i-2][j])       //si 3 sont allignés
                            {
                            if (V[i][j] == V[i-1][j] && V[i][j] == V[i-2][j] && V[i][j] == V[i-3][j])       //si 4 sont alignés

                                if (V[i][j] == V[i-1][j] && V[i][j] == V[i-2][j] && V[i][j] == V[i-3][j] && V[i][j] == V[i-4][j])
                                    {
                                    for (k = 0; k < N; ++k)
                                       for (l = 0; l < M; ++l)
                                       {
                                           if (V[k][l] == V[i][j])
                                              {
                                               sup[k][l] = 1;
                                               
                                              }
                                       }points += 500;
                                    }

                                    else
                                    {
                                        for (k = 0; k < N; ++k)
                                        {
                                            if (V[k][j] != 1 && V[k][j] != 10 && V[k][j] != 18 && V[k][j] != 27)
                                            {
                                                sup[k][j] = 1;
                                                
                                            }
                                            
                                        }
                                        points += 300;
                                    }
                                else {sup[i][j] = sup[i-1][j] = sup[i-2][j] = 1; points += 100;}
                            }

                        }


                for (i = 0; i < N; i++)
                    for (j = 2; j < M; j++)
                        {
                        if(V[i][j] != 1 && V[i][j] != 10 && V[i][j] != 18 && V[i][j] != 27)
                        if (V[i][j] == V[i][j-1] && V[i][j] == V[i][j-2])       //si 3 sont allignés
                            {
                            if (V[i][j] == V[i][j-1] && V[i][j] == V[i][j-2] && V[i][j] == V[i][j-3])       //si 4 sont alignés

                                if (V[i][j] == V[i][j-1] && V[i][j] == V[i][j-2] && V[i][j] == V[i][j-3] && V[i][j] == V[i][j-4])
                                    {
                                    for (k = 0; k < N; ++k)
                                       for (l = 0; l < M; ++l)
                                       {
                                           if (V[k][l] == V[i][j])
                                              {
                                               sup[k][l] = 1;
                                               
                                              }
                                       }points += 500;
                                    }

                                    else
                                    {
                                        for (k = 0; k < M; ++k)
                                        {
                                            if (V[i][k] != 1 && V[i][k] != 10 && V[i][k] != 18 && V[i][k] != 27)
                                            {
                                                sup[i][k] = 1;
                                                
                                            }

                                        }
                                        points += 300;
                                    }
                                else {sup[i][j] = sup[i][j-1] = sup[i][j-2] = 1; points += 100;}
                            }

                        }
    
     

                for (i = 0; i < N - 1; i++) {
                    for (j = 0; j < M - 1; j++) {
                     
                        if (V[i][j] > 1 && V[i][j] != 10 && V[i][j] != 18 && V[i][j] != 27) {

                            if (V[i+1][j] == V[i][j] && V[i][j+1] == V[i][j] && V[i+1][j+1] == V[i][j]) {
                                
                                sup[i][j] = sup[i+1][j] = sup[i][j+1] = sup[i+1][j+1] = 1;

                                if (i > 0 && V[i-1][j] > 1 && V[i-1][j] != 10 && V[i-1][j] != 18 && V[i-1][j] != 27 && V[i-1][j+1] > 1 && V[i-1][j+1] != 10 && V[i-1][j+1] != 18 && V[i-1][j+1] != 27) { sup[i-1][j] = 1; sup[i-1][j+1] = 1; }      
                                if (i < N - 2 && V[i+2][j] > 1 && V[i+2][j] != 10 && V[i+2][j] != 18 && V[i+2][j] != 27 && V[i+2][j+1] > 1 && V[i+2][j+1] != 10 && V[i+2][j+1] != 18 && V[i+2][j+1] != 27) { sup[i+2][j] = 1; sup[i+2][j+1] = 1; }    
                                if (j > 0 && V[i][j-1] > 1 && V[i][j-1] != 10 && V[i][j-1] != 18 && V[i][j-1] != 27 && V[i+1][j-1] > 1 && V[i+1][j-1] != 10 && V[i+1][j-1] != 18 && V[i+1][j-1] != 27) { sup[i][j-1] = 1; sup[i+1][j-1] = 1; }         
                                if (j < M - 2 && V[i+1][j+2] > 1 && V[i+1][j+2] != 10 && V[i+1][j+2] != 18 && V[i+1][j+2] != 27 && V[i][j+1] > 1 && V[i][j+1] != 10 && V[i][j+1] != 18 && V[i][j+1] != 27) { sup[i][j+1] = 1; sup[i+1][j+2] = 1; }    
                                
                     
                                if (i > 0 && j > 0 && V[i-1][j-1] > 1 && V[i-1][j-1] != 10 && V[i-1][j-1] != 18 && V[i-1][j-1] != 27) sup[i-1][j-1] = 1;
                                if (i < N - 2 && j < M - 2 && V[i+2][j+2] > 1 && V[i+2][j+2] != 10 && V[i+2][j+2] != 18 && V[i+2][j+2] != 27 ) sup[i+2][j+2] = 1;

                                points += 200; 
                            }
                        }
                    }
                }



    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (sup[i][j] == 1 )
                V[i][j] = 0;

    int n = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (V[i][j] == 0)
            {
                n++;
            }

    if (n > 2)
    {
        printf("\033[H");
        crochets(a, b);
        Sleep(300);
    }

    int mouvement = 1;
while (mouvement) {
    mouvement = 0;

    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < M; j++) {
            

            if (V[i][j] == 0) {
                

                if (i > 0 && V[i-1][j] > 1 && V[i-1][j] != 10 && V[i-1][j] != 18 && V[i-1][j] != 27) {
                    V[i][j] = V[i-1][j];
                    V[i-1][j] = 0;
                    mouvement = 1;
                }

                else if (i > 0) {

                    if (j < M - 1 && V[i-1][j+1] > 1 && V[i-1][j+1] != 10 && V[i-1][j+1] != 18 && V[i-1][j+1] != 27) {
                        V[i][j] = V[i-1][j+1];
                        V[i-1][j+1] = 0;
                        mouvement = 1;
                    }
 
                    else if (j > 0 && V[i-1][j-1] > 1 && V[i-1][j-1] != 10 && V[i-1][j-1] != 18 && V[i-1][j-1] != 27) {
                        V[i][j] = V[i-1][j-1];
                        V[i-1][j-1] = 0;
                        mouvement = 1;
                    }
                }

                if (i == 0 && V[i][j] == 0) {
                    if ( collection_items== 1) V[i][j] = rand() % 8 + 2;
                    else if ( collection_items== 2) V[i][j] = rand() % 7 + 11;
                    else if ( collection_items== 3) V[i][j] = rand() % 7 + 19;
                    else if ( collection_items== 4) V[i][j] = rand() % 6 + 28;
                    else if ( collection_items== 5) V[i][j] = rand() % 8 + 2;
                    mouvement = 1;
                }
            }
        }
    }
}
    return points;
}



int afficher_intro(int niv) {
    static char ligne[20000]; 
    printf("\033[H");
    int c;

    for (int i = 0; i < MENU; ++i) {
        int pos = 0; 
        for (int j = 0; j < MENU; ++j) {
            switch(niv){
                case 1:  c = intro_niveau_1[i][j];break;
                case 2:  c = intro_niveau_2[i][j];break;
                case 3:  c = intro_niveau_3[i][j];break;
                case 4:  c = intro_niveau_4[i][j];break;
            }
            int r = (c / 32) * 85;          
            int g = ((c % 32) / 8) * 85;     
            int b = (c % 8) * 36;            
            pos += snprintf(ligne + pos, sizeof(ligne) - pos, "\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
        }
        printf("%s\n", ligne);
    }

 
    int b = getch();
    if (b == 27) return 0; 
    else if (b == 32) return 1;
    return 1;
}


int afficher_menu(int niveau_max_atteint) {
    int choix;
    static char ligne[20000]; 
    
    printf("\033[H");

    for (int i = 0; i < MENU; ++i) {
        int pos = 0; 
        
        for (int j = 0; j < MENU; ++j) {
            int c;
            if (niveau_max_atteint <=1)  c = menu[i][j];
            else{c= menu2[i][j];}
       
            int r = (c / 32) * 85;          
            int g = ((c % 32) / 8) * 85;     
            int b = (c % 8) * 36;            

            pos += snprintf(ligne + pos, sizeof(ligne) - pos, "\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
        }
        printf("%s\n", ligne);
    }
                    

    int b = getch();

    switch(b){case 49: choix = 1; break; case 50: choix = 2;break; case 51: choix = 3;break; case 27: choix = 4;break;}
    if (b != 49 && b != 50 && b != 51 && b != 27)
    {
        printf("impossible");
    }
    else{return choix;}
}

int jouer_niveau(int num_niveau) {
   
    int k = afficher_intro(num_niveau);
    if (k == 0) {return num_niveau;}  
    else{
    Configuration_niveau config;
    int temps_max;
    int temps_ecoule = 1;
 
         if (num_niveau == 1) {tableau(V, niveau_1, collection_items); config.objectif_score = 3500; config.coups_max = 30; temps_max = 99;}
    else if (num_niveau == 2) {tableau(V, niveau_2, collection_items); config.objectif_score = 4500; config.coups_max = 20; temps_max = 90;}
    else if (num_niveau == 3) {tableau(V, niveau_3, collection_items); config.objectif_score = 5000; config.coups_max = 18; temps_max = 90;}
    else if (num_niveau == 4) {tableau(V, niveau_4, collection_items); config.objectif_score = 6000; config.coups_max = 15; temps_max = 90;}

    score = 0;
    coups_restants = config.coups_max;
    temps_depart_niveau = 0;

    int continuer = 1;
    construire_tableau_final();
    printf("\033[0;0H"); 
    crochets(a, b);

    while (continuer) {
        printf("\033[H");
        temps_ecoule = timer(temps_max);
        afficher_score(score);
        afficher_coups(coups_restants);
      
              
     if (_kbhit()) { 
        c = getch();
        if (c == 'z' && a > 0) a--;
        else if (c == 's' && a < N - 1) a++;
        else if (c == 'q' && b > 0) b--;
        else if (c == 'd' && b < M) b++;
        else if (c == 27) {
            system("cls");
            break;
        }
        else if (c == 'p') {
            
            char sens = getch();
            permutation(a, b, sens);
            
            int points = combo(V, score, collection_items); 
            score += points;
            coups_restants--;
        }
        printf("\033[0;0H"); 
        crochets(a, b);
        }

        if (score >= config.objectif_score) {
            system("cls");
            afficher_game_succes();
            num_niveau++;
           
            continuer = 0;
        } 
        else if (coups_restants <= 0 || temps_ecoule <= 0) {
            system("cls");
            afficher_game_over();
          
            continuer = 0;
        }

    }
    score = 0;
}
 return num_niveau;
}
void afficher_score(int score) {

    int (*nombre[10])[T] = {zero, un, deux, trois, quatre, cinq, six, sept, huit, neuf};

    
    static int dernier_score_affiche = -1;
    if (score == dernier_score_affiche) return;
    dernier_score_affiche = score;

    static char ligne[5000]; 

   
    int chiffres[4];
    chiffres[0] = (score / 1000) % 10;
    chiffres[1] = (score / 100) % 10;
    chiffres[2] = (score / 10) % 10;
    chiffres[3] = score % 10;

    for (int i = 0; i < T; i++) {
        int pos = 0;
 
  
        pos += snprintf(ligne + pos,sizeof(ligne), "\033[%d;1000H", 70 + i);

        for (int n = 0; n < 4; n++) {
            int num = chiffres[n];
            
            for (int j = 0; j < T; j++) {
                int pixel = nombre[num][i][j];
                
                if (pixel == 127) {
                   
                    int r = 50;
                    int g = (i * 4) % 256;
                    int b = 255 - (i * 2);
                    pos += snprintf(ligne + pos,sizeof(ligne), "\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
                } else {
                
                    pos += snprintf(ligne + pos,sizeof(ligne), "\033[40m  \033[0m");
                }
            }
        }

        printf("%s\n", ligne);
    }
    
}

void afficher_coups(int coups) {

    int (*nombre[10])[T] = {zero, un, deux, trois, quatre, cinq, six, sept, huit, neuf};


    static int derniers_coups_affiches = -1;
    if (coups == derniers_coups_affiches) return;
    derniers_coups_affiches = coups;

    static char ligne[2000];

    int dizaine = (coups / 10) % 10;
    int unite   = coups % 10;

    for (int i = 0; i < T; i++) {
        int pos = 0;

        pos += snprintf(ligne + pos,sizeof(ligne), "\033[%d;1000H", 140 + i);


        for (int j = 0; j < T; j++) {
            if (nombre[dizaine][i][j] == 127) {
                pos += snprintf(ligne + pos,sizeof(ligne), "\033[48;2;%d;200;%dm  \033[0m", (i*5)%256, (i*2)%256);
            } else {
                pos += snprintf(ligne + pos,sizeof(ligne), "  ");
            }
        }
        for (int j = 0; j < T; j++) {
            if (nombre[unite][i][j] == 127) {
                pos += snprintf(ligne + pos,sizeof(ligne), "\033[48;2;%d;200;%dm  \033[0m", (i*5)%256, (i*2)%256);
            } else {
                pos += snprintf(ligne + pos,sizeof(ligne), "  ");
            }
        }
        printf("%s\n", ligne);
    }

}


int timer(int temps_max) {
    if (temps_depart_niveau == 0) temps_depart_niveau = time(NULL);
    static char ligne[2000];

    int (*nombre[10])[T] = {zero, un, deux, trois, quatre, cinq, six, sept, huit, neuf};
    
    time_t actuel = time(NULL);
    int secondes_ecoulees = (int)difftime(actuel, temps_depart_niveau);
    int temps_restant = temps_max - secondes_ecoulees;

    if (temps_restant <= 0) return 0;

    static int derniere_seconde_affichee = -1;


    if (temps_restant != derniere_seconde_affichee) {
        derniere_seconde_affichee = temps_restant;

        int dizaine = (temps_restant / 10) % 10;
        int unite = temps_restant % 10;

       for (int i = 0; i < T; i++) {
        int pos = 0;

        pos += snprintf(ligne + pos,sizeof(ligne), "\033[%d;1000H", 0 + i);


        for (int j = 0; j < T; j++) {
            if (nombre[dizaine][i][j] == 127) {
                pos += snprintf(ligne + pos,sizeof(ligne), "\033[48;2;200;%d;%dm  \033[0m", (i*5)%256, (i*2)%256);
            } else {
                pos += snprintf(ligne + pos,sizeof(ligne), "  ");
            }
        }
        for (int j = 0; j < T; j++) {
            if (nombre[unite][i][j] == 127) {
                pos += snprintf(ligne + pos,sizeof(ligne), "\033[48;2;200;%d;%dm  \033[0m", (i*5)%256, (i*2)%256);
            } else {
                pos += snprintf(ligne + pos,sizeof(ligne), "  ");
            }
        }
        printf("%s\n", ligne);
    }
    }

    return 1;
}


void verifier_affichage() {
    system("cls");

    printf("Pour une experience de jeu optimale :\n");
    printf("1. Maintenez le touches \033[1m[CTRL] et [-]\033[0m enfoncee pendant 3 secondes.\n");
    printf("2. Utilisez la \033[1mmolette de la souris\033[0m vers le bas pour \033[1;32mDEZOOMER\033[0m.\n");
    printf("3. Arretez quand vous etes au dezoome maximum de la console\n");
    printf("Une fois le zoom regle, appuyez sur \033[1m[ESPACE]\033[0m pour lancer le menu.");
    
    while(getch() != 32); 
    system("cls");
}


int main() {
    system("cls");
    verifier_affichage();
    srand(time(NULL));

    item[0]  = croix;
    item[1]  = barriere;  item[10] = trounoir; item[18] = cloture;   item[27] = petanque;
    item[2]  = cerise;    item[11] = mercure;  item[19] = lapin;     item[28] = foot;
    item[3]  = citron;    item[12] = venus;    item[20] = chat;      item[29] = tennis;
    item[4]  = fraise;    item[13] = terre;    item[21] = mouton;    item[30] = basket;
    item[5]  = myrtille;  item[14] = mars;     item[22] = rino;      item[31] = volley;
    item[6]  = orange;    item[15] = jupiter;  item[23] = elephant;  item[32] = rugby;
    item[7]  = pasteque;  item[16] = saturne;  item[24] = dauphin;   item[33] = baseball;
    item[8]  = peche;     item[17] = uranus;   item[25] = crabe;
    item[9]  = pomme;  

    int niveau_max_atteint = charger_progression(); 
    int quitter = 0;

    while (!quitter) {
        int choix = afficher_menu(niveau_max_atteint);

        switch (choix) {
            case 1: 
                if (niveau_max_atteint>0)collection_items = niveau_max_atteint;
                else niveau_max_atteint=1;
                
                int resultat = jouer_niveau(niveau_max_atteint);
                
               
                if (resultat > niveau_max_atteint && resultat <= 4) {
                    niveau_max_atteint = resultat;
                    sauvegarder_progression(niveau_max_atteint);
                }
                break;

            case 2: 
            {
                int n = afficher_choix_des_niveaux();
                if (n >= 1 && n <= 4) {
                    if (n <= niveau_max_atteint) { 
                        collection_items = n;
                        int res = jouer_niveau(n);
                        if (res > niveau_max_atteint && res <= 4) {
                            niveau_max_atteint = res;
                            sauvegarder_progression(niveau_max_atteint);
                        }
                    } else {
                        afficher_niveau_bloque();
                    }
                }

                break;
            }

            case 3: 
                afficher_regles();
                break;

            case 4: 
                quitter = 1;
                break;

            default:

                break;
        }
    }

    system("cls");
    printf("Merci d'avoir joue !\n");
    return 0;
}