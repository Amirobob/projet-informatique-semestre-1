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
// Map[x][y] where x is column, y is row
char shapepick(char map[xmax][ymax], int x, int y) {
    // Try shapes that won't create a new triple with neighbors
    char candidates[3] = { CIRCLE, SQUARE, TRIANGLE };
    for (int k = 0; k < 3; k++) {
        char s = candidates[(k + rand()) % 3];
        bool ok = true;
        // Check horizontal triples centered at (x,y)
        if (x >= 2 && map[x-1][y] == s && map[x-2][y] == s) ok = false;
        if (x >= 1 && x+1 < xmax && map[x-1][y] == s && map[x+1][y] == s) ok = false;
        if (x+2 < xmax && map[x+1][y] == s && map[x+2][y] == s) ok = false;
        // Vertical
        if (y >= 2 && map[x][y-1] == s && map[x][y-2] == s) ok = false;
        if (y >= 1 && y+1 < ymax && map[x][y-1] == s && map[x][y+1] == s) ok = false;
        if (y+2 < ymax && map[x][y+1] == s && map[x][y+2] == s) ok = false;
        // Diagonal down-right
        if (x >= 2 && y >= 2 && map[x-1][y-1] == s && map[x-2][y-2] == s) ok = false;
        if (x >= 1 && y >= 1 && x+1 < xmax && y+1 < ymax && map[x-1][y-1] == s && map[x+1][y+1] == s) ok = false;
        if (x+2 < xmax && y+2 < ymax && map[x+1][y+1] == s && map[x+2][y+2] == s) ok = false;
        // Diagonal down-left
        if (x+2 < xmax && y >= 2 && map[x+1][y-1] == s && map[x+2][y-2] == s) ok = false;
        if (x >= 1 && y >= 1 && x+1 < xmax && y+1 < ymax && map[x+1][y-1] == s && map[x-1][y+1] == s) ok = false;
        if (x >= 2 && y+2 < ymax && map[x-1][y+1] == s && map[x-2][y+2] == s) ok = false;
        if (ok) return s;
    }
    // if hell lets loose
    switch (map[x][y]) {
        case CIRCLE:   return SQUARE;
        case SQUARE:   return TRIANGLE;
        default:       return CIRCLE;
    }
}
void generate_map(char map[xmax][ymax]) {
    int temp;
    for (int y = 0; y < ymax; y++) {
        for (int x = 0; x < xmax; x++) {
            if (y == 0 || y == ymax - 1 || x == 0 || x == xmax - 1) {
                map[x][y] = '#';
            } else {
                temp = rand() % 3;
                if (temp == 0)      map[x][y] = CIRCLE;
                else if (temp == 1) map[x][y] = SQUARE;
                else                map[x][y] = TRIANGLE;
            }
        }
    }

    // remove identicals
    bool changed = true;
    int passes = 0;
    while (changed && passes < 16) {
        changed = false;
        passes++;
        for (int y = 1; y < ymax - 1; y++) {
            for (int x = 1; x < xmax - 1; x++) {
                // Horizontal
                if (x <= xmax - 3 && map[x][y] == map[x+1][y] && map[x][y] == map[x+2][y]) {
                    map[x][y] = shapepick(map, x, y);
                    changed = true;
                    continue;
                }
                // Vertical
                if (y <= ymax - 3 && map[x][y] == map[x][y+1] && map[x][y] == map[x][y+2]) {
                    map[x][y] = shapepick(map, x, y);
                    changed = true;
                    continue;
                }
                // Diagonal down-right
                if (y <= ymax - 3 && x <= xmax - 3 && map[x][y] == map[x+1][y+1] && map[x][y] == map[x+2][y+2]) {
                    map[x][y] = shapepick(map, x, y);
                    changed = true;
                    continue;
                }
                // Diagonal down-left
                if (y <= ymax - 3 && x >= 2 && map[x][y] == map[x-1][y+1] && map[x][y] == map[x-2][y+2]) {
                    map[x][y] = shapepick(map, x, y);
                    changed = true;
                    continue;
                }
            }
        }
    }
}

void stat(int y, int level, int life, int score, int timeremaining, int turnsleft, int squareleft, int triangleleft, int circleleft){
    switch(y) {
        case 1:
        set_color(GREEN, BLACK);
            printf("   |Score: %d", score);
            break;
        case 2:
        set_color(MAGENTA, BLACK);
            printf("   |Level: %d\tLives: %d", level, life);
            break;
        case 3:
        set_color(RED, BLACK);
            printf("   |Time: %d\tTurns: %d", timeremaining, turnsleft);
            break;
        case 4:
            set_color(YELLOW, BLACK);
            printf("   |Squares left: %d", squareleft);
            break;
        case 5:
            set_color(GREEN, BLACK);
            printf("   |Triangles left: %d", triangleleft);
            break;
        case 6:
            set_color(BLUE, BLACK);
            printf("   |Circles left: %d", circleleft);
            break;
    }
}

void print_map(char map[xmax][ymax], int level, int life, int score, int timeremaining, int turnsleft, int squareleft, int triangleleft, int circleleft) {
    // Top coordinate header
    SetConsoleOutputCP(65001);
    set_color(WHITE, BLACK);
    printf("   ");
    for (int x = 0; x < xmax; x++);
    printf("\n");
    for (int y = 0; y < ymax; y++) {
        for (int x = 0; x < xmax; x++) {
            char c = map[x][y];
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
        stat(y, level, life, score, timeremaining, turnsleft, squareleft, triangleleft, circleleft);
        printf("\n");
    }
    set_color(WHITE, BLACK);
}

void print_stats(int level, int life, int score, int timeremaining, int turnsleft, int squareleft, int triangleleft, int circleleft) {
    set_color(GREEN, BLACK);
    printf("Score: %d\n", score);
    set_color(MAGENTA, BLACK);
    printf("Level: %d\tLives: %d\n", level, life);
    set_color(RED, BLACK);
    printf("Time: %d\tTurns: %d\n", timeremaining, turnsleft);
    set_color(YELLOW, BLACK);
    printf("Squares left: %d\n", squareleft);
    set_color(GREEN, BLACK);
    printf("Triangles left: %d\n", triangleleft);
    set_color(BLUE, BLACK);
    printf("Circles left: %d\n", circleleft);
}

void legend(void) {
    set_color(WHITE, BLACK);
    printf("\nLegend: ");
    set_color(BLUE, BLACK);   printf("%c Circle  ", CIRCLE);
    set_color(YELLOW, BLACK); printf("%c Square  ", SQUARE);
    set_color(GREEN, BLACK);  printf("%c Triangle  ", TRIANGLE);
    set_color(MAGENTA, BLACK);printf("# Border\n\n");
    set_color(WHITE, BLACK);
}

int main() {
    int level = 1, life = 3, score = 0, timeremaining = 60, turnsleft = 20;
    int squareleft = 50, triangleleft = 50 , circleleft = 50;
    char map[xmax][ymax];
    clrscr();
    srand((unsigned)time(NULL));
    show_cursor();
    printf("Welcome to ECE Heroes!\n\n");
    generate_map(map);
    print_map(map, level, life, score, timeremaining, turnsleft, squareleft, triangleleft, circleleft);
    return 0;
}