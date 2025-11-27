#include "affichage_console.h"
#include "affichage.h"
#include "jeu.h"
#include "parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

void generate_map(char map[xmax][ymax]) {
    int temp;
    
    // Initial map generation
    for (int i = 0; i < ymax; i++){
        for (int j = 0 ; j < xmax; j++){
            temp = rand()%3;
            if (i == 0 || i == ymax-1 || j == 0 || j == xmax-1 ){
                map[j][i] = '#';
            }
            else if (temp == 0){
                map[j][i] = 'O '; // circle
            }
            else if (temp == 1){
                map[j][i] = 'H '; // square
            }
            else if (temp == 2){
                map[j][i] = 'T '; // triangles
            }
        }
    }

    // Ensure no three consecutive identical shapes horizontally or vertically
    for (int i = 0; i < ymax; i++){
        for (int j = 0 ; j < xmax; j++){
            // Check for horizontal repeats
            if (j <= xmax - 3 && map[j][i] == map[j+1][i] && map[j][i] == map[j+2][i]) {
                switch(map[j][i]) {
                    case 'O':
                        map[j][i] = 'H ';
                        break;
                    case 'H':
                        map[j][i] = 'T ';
                        break;
                    case 'T':
                        map[j][i] = 'O ';
                        break;
                }
            }
            // Check for vertical repeats
            if (i <= ymax - 3 && map[j][i] == map[j][i+1] && map[j][i] == map[j][i+2]) {
                switch(map[j][i]) {
                    case 'O':
                        map[j][i] = 'H';
                        break;
                    case 'H':
                        map[j][i] = 'T';
                        break;
                    case 'T':
                        map[j][i] = 'O';
                        break;
                }
            }
        }
    }
}

int main() {
    int level = 1, life = 3, score = 0, timeremaining = 60, turnsleft = 20, squareleft = 50, triangleleft = 50 , circleleft = 50;
    char map[xmax][ymax];
    clrscr();
    srand(time(NULL));
    show_cursor();
    printf("welcome to ECE Heroes!\n\n");
    set_color(GREEN, BLACK);
    printf("SCORE : %d\n", score);

    // Generate the map
    generate_map(map);

    // map display //
    for (int i = 0; i < ymax; i++){
        for (int j = 0 ; j < xmax; j++){
            set_color(WHITE, BLACK);
            if (map[j][i] == 'O'){
                set_color(BLUE, BLACK);
            }
            else if (map[j][i] == 'H'){
                set_color(YELLOW, BLACK);
            }
            else if (map[j][i] == 'T'){
                set_color(GREEN, BLACK);
            }
            printf("%c",map[j][i]);


            // side information display //
            if (i == 0 && j == xmax-1){
                set_color(MAGENTA, BLACK);
                printf(" |Level: %d\t lives remaining: %d", level , life);
            }
            if (i == 2 && j == xmax-1){
                set_color(RED, BLACK);
                printf(" |time remaining: %d\t turns left: %d", timeremaining, turnsleft);
            }
            if (i == 4 && j == xmax-1){
                set_color(YELLOW, BLACK);
                printf(" |squares left: %d", squareleft);
            }
            if (i == 5 && j == xmax-1){
                set_color(GREEN, BLACK);
                printf(" |triangles left: %d", triangleleft);
            }
            if (i == 6 && j == xmax-1){
                set_color(BLUE, BLACK);
                printf(" |circles left: %d", circleleft);
            }
        }
        printf("\n");
    }
}