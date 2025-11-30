#include "affichage_console.h"
#include "affichage.h"
#include "jeu.h"
#include "parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

char shapepick(char map[ymax][xmax], int x, int y, int direction) {
    switch (direction) {
        // this is very frustrating, I am taking a break
    }
    map[y][x] = CIRCLE ? SQUARE : SQUARE ? TRIANGLE : CIRCLE;
}

void generate_map(char map[ymax][xmax]) {
    int temp;
    for (int y = 0; y < ymax; y++) {
        for (int x = 0; x < xmax; x++) {
            bool onborder = (y == 0 || y == ymax - 1|| x == 0 || x == xmax - 1);
            if (onborder) map[y][x] = '#';
            else {
                switch(temp = rand() % 3) {
                case(0): map[y][x] = CIRCLE; break;
                case(1): map[y][x] = SQUARE; break;
                case(2): map[y][x] = TRIANGLE; break;
                }
            }
        }
    }

    // remove identicals
    int passes = 0;
    do{
        for (int y = 1; y < ymax - 2; y++) {
            for (int x = 1; x < xmax - 2; x++) {
                bool horizontal = (x <= xmax - 2 && map[y][x] == map[y][x+1] && map[y][x] == map[y][x+2]);
                bool vertical = (y <= ymax - 3 && map[y][x] == map[y+1][x] && map[y][x] == map[y+2][x]);
                bool diagonal_dr = (y <= ymax - 2 && x <= xmax - 2 && map[y][x] == map[y+1][x+1] && map[y][x] == map[y+2][x+2]);
                bool diagonal_dl = (y <= ymax - 2 && x <= xmax - 2 && map[y][x] == map[y+1][x-1] && map[y][x] == map[y+2][x-2]);
                // Horizontal
                if (horizontal) {
                    shapepick(map, x, y,1);
                }
                // Vertical
                if (vertical) {
                    shapepick(map, x, y,2);
                }
                // Diagonal down-right
                if (diagonal_dr) {
                    shapepick(map, x, y,3);
                }
                // Diagonal down-left
                if (diagonal_dl) {
                    shapepick(map, x, y,4);
                }
            }
        }
        passes++;
    }while (passes < 20);
}

void stat(int y,int stats[8]){
    switch(y) {
        case 1:
        set_color(GREEN, BLACK);
            printf("   |Score: %d", stats[2]);
            break;
        case 2:
        set_color(MAGENTA, BLACK);
            printf("   |Level: %d\tLives: %d", stats[0], stats[1]);
            break;
        case 3:
        set_color(RED, BLACK);
            printf("   |Time: %d\tTurns: %d", stats[3], stats[4]);
            break;
        case 4:
            set_color(YELLOW, BLACK);
            printf("   |Squares left: %d", stats[5]);
            break;
        case 5:
            set_color(GREEN, BLACK);
            printf("   |Triangles left: %d", stats[6]);
            break;
        case 6:
            set_color(BLUE, BLACK);
            printf("   |Circles left: %d", stats[7]);
            break;
    }
}

void menu(void) {
    set_color(WHITE, BLACK);
    char menu[9][32] = {
        "|-----------------------------|",
        "|         ECE Heroes!         |",
        "|-----------------------------|",
        "|       1. Start Game         |",
        "|       2. Continue Game      |",
        "|       3. Instructions       |",
        "|       4. Exit               |",
        "|-----------------------------|"
    };
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j<32; j++) {
            bool inside = (j>2 && j<30);
        set_color(WHITE, BLACK);
        if (i == 1 &&inside) set_color(YELLOW, BLACK);
        else if (i == 3 && inside || i == 4 && inside) set_color(GREEN, BLACK);
        else if (i == 5 && inside) set_color(BLUE, BLACK);
        else if (i == 6 && inside) set_color(RED, BLACK);
        else set_color(WHITE, BLACK);
        printf("%c", menu[i][j]);
        }
        printf("\n");
    }
}


bool print_map(char map[ymax][xmax], int stats[8]) {
    // Top coordinate header
    set_color(WHITE, BLACK);
    printf("   ");
    for (int x = 0; x < xmax; x++);
    printf("\n");
    for (int y = 0; y < ymax; y++) {
        for (int x = 0; x < xmax; x++) {
            char c = map[y][x];
            set_color(WHITE, BLACK);
            if (c == CIRCLE) {
                set_color(BLUE, BLACK);
                printf("● ");
            } else if (c == SQUARE) {
                set_color(YELLOW, BLACK);
                printf("■ ");
            } else if (c == TRIANGLE) {
                set_color(GREEN, BLACK);
                printf("▲ ");
            } else if (c == '#') {
                set_color(MAGENTA, BLACK);
                printf("▩ ");
            }
        }
        stat(y, stats);
        printf("\n");
    }
    set_color(WHITE, BLACK);
    return true;
}

void saveprogress(int level) {
    char playername[50];
    set_color(WHITE, BLACK);
    printf("Enter your name to save progress: ");
    scanf("%49s", playername);
}

void endscreen(bool gameover, int level) {
    if (gameover) {
        char gameovermessage[][18] = {
            " _______________ ",
            "|  ___________  |",
            "| | game over | |",
            "| |___________| |",
            "|_______________|",
        };
        set_color(RED, BLACK);
        for (int i = 0; i < 5; i++) {
            printf("%s\n", gameovermessage[i]);
        }
        set_color(WHITE, BLACK);
        printf("Better luck next time!\n");
        printf(" ________________\n");
        printf("|Try again       |\n");
        printf("|________________|\n");
        printf("|save last level |\n");
        printf("|________________|\n");
        printf("|leave game      |\n");
        printf("|________________|\n");
    } else {
        char won[][34] = {
            " _______________________________ ",
            "|  ___________________________  |",
            "| | congratulations, you won! | |",
            "| |___________________________| |",
            "|_______________________________|",
        };
        set_color(GREEN, BLACK);
        for (int i = 0; i < 5; i++) {
            printf("%s\n", won[i]);
        }
        set_color(WHITE, BLACK);
        printf("       ________________\n");
        printf("      |next level      |\n");
        printf("      |________________|\n");
        printf("      |save progress   |\n");
        printf("      |________________|\n");
        printf("      |leave game      |\n");
        printf("      |________________|\n");
        saveprogress(level);
    }
}

void leveload(void) {
    char playername[50];
    set_color(WHITE, BLACK);
    printf("Enter your name to load progress: ");
    scanf("%49s", playername);
    printf("welcome back john doe! loading level 2...\n");
    printf("\n name not found, try again\n");
}

int main() {
    clrscr();
    show_cursor();
    gotoxy(0,0);
    SetConsoleOutputCP(65001);
    int level = 1, life = 3, score = 0, timeremaining = 60, turnsleft = 20 ,squareleft = 50, triangleleft = 50 , circleleft = 50;
    int stats[8] = {level, life, score, timeremaining, turnsleft, squareleft, triangleleft, circleleft};
    bool gameover = false;
  
    char map[ymax][xmax];
    srand(time(NULL));
    menu();
    leveload();
    generate_map(map);
    gameover = print_map(map, stats);
    endscreen(gameover,level);
    return 0;
}