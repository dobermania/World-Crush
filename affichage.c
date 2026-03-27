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


int afficher_game_succes() {
    static char ligne[20000]; 
    printf("\033[H");

    for (int i = 0; i < MENU; ++i) {
        int pos = 0; 
        for (int j = 0; j < MENU; ++j) {
            int c = game_succes[i][j];
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
}

int afficher_niveau_bloque() {
    static char ligne[20000]; 
    printf("\033[H");

    for (int i = 0; i < MENU; ++i) {
        int pos = 0; 
        for (int j = 0; j < MENU; ++j) {
            int c = niveau_bloque[i][j];
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
}

int afficher_game_over() {
    static char ligne[20000]; 
    printf("\033[H");

    for (int i = 0; i < MENU; ++i) {
        int pos = 0; 
        for (int j = 0; j < MENU; ++j) {
            int c = game_over[i][j];
            int r = (c / 32) * 85;          
            int g = ((c % 32) / 8) * 85;     
            int b = (c % 8) * 36;            
            pos += snprintf(ligne + pos, sizeof(ligne) - pos, "\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
        }
        printf("%s\n", ligne);
    }

 
    int b = getch();
    if (b == 27) return 4; 
    return 0;
}

int afficher_regles() {
    static char ligne[20000]; 
    printf("\033[H");

    for (int i = 0; i < MENU; ++i) {
        int pos = 0; 
        for (int j = 0; j < MENU; ++j) {
            int c = regles[i][j];
            int r = (c / 32) * 85;          
            int g = ((c % 32) / 8) * 85;     
            int b = (c % 8) * 36;            
            pos += snprintf(ligne + pos, sizeof(ligne) - pos, "\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
        }
        printf("%s\n", ligne);
    }


    int b = getch();
    if (b == 27) return 4; 
    return 0;
}

int afficher_choix_des_niveaux() {
    static char ligne[20000]; 
    int n;
    
    printf("\033[H");

    for (int i = 0; i < MENU; ++i) {
        int pos = 0; 
        
        for (int j = 0; j < MENU; ++j) {
            int c = choix_des_niveaux[i][j];
       
            int r = (c / 32) * 85;          
            int g = ((c % 32) / 8) * 85;     
            int b = (c % 8) * 36;            

            pos += snprintf(ligne + pos, sizeof(ligne) - pos, "\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
        }
        printf("%s\n", ligne);
    }
                    
    int b = getch();

    switch(b) {
        case 27: n = 6; break; 
        case 49: n = 1; break; 
        case 50: n = 2; break;
        case 51: n = 3; break; 
        case 52: n = 4; break;
        case 53: n = 5; break; 
    }   
return n;
    
}