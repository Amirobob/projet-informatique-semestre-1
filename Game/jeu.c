#include "jeu.h"

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

char shapepick(char map[ymax][xmax], int x, int y, int direction) {
    switch (direction) {
        // this is very frustrating, I am taking a break
        // MUST DO A DO WHILE!!!!!
    }
    map[y][x] = CIRCLE ? SQUARE : SQUARE ? TRIANGLE : CIRCLE;
}