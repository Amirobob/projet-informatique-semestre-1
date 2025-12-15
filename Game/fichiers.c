#include "Fichiers.h"



void saveprogress(int level) {
    char playername[50];
    set_color(WHITE, BLACK);
    printf("Enter your name to save progress: ");
    scanf("%49s", playername);
}



void leveload(void) {
    char playername[50];
    set_color(WHITE, BLACK);
    printf("Enter your name to load progress: ");
    scanf("%49s", playername);
    printf("welcome back john doe! loading level 2...\n");
    printf("\n name not found, try again\n");
}