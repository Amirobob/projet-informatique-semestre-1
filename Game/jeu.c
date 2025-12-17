#include "jeu.h"
#include "affichage.h"

void playgame(int stats[], char map[ymax][xmax]) {
    // stats numbers: 0: level, 1: life, 2: score, 3: timeremaining, 4: turnsleft, 5:squareleft, 6:triangleleft, 7:circleleft
    generate_map(map);
    switch(game_loop(stats, map)) { // I think it's called a helper function?
        case 1: //gamewon!!!
        break;
        case 2: //gamelost :(
        break;
    }
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
                bool horizontal = (x <= xmax - 3 && map[y][x] == map[y][x+1] && map[y][x] == map[y][x+2]);
                bool vertical = (y <= ymax - 3 && map[y][x] == map[y+1][x] && map[y][x] == map[y+2][x]);
                // Horizontal
                if (horizontal) {
                    shapepick(map, x, y,1);
                }
                // Vertical
                if (vertical) {
                    shapepick(map, x, y,2);
                }
            }
        }
        passes++;
    }while (passes < 20);
}

char shapepick(char map[ymax][xmax], int x, int y, int direction) {
    int temp;
    switch (direction) {
        case 1: // Horizontal
                do {
                for (int i = 0; i < 3; i++) {
                    temp = rand() % 3;
                    switch (temp) {
                        case 0: map[y][x+i] = CIRCLE; break;
                        case 1: map[y][x+i] = SQUARE; break;
                        case 2: map[y][x+i] = TRIANGLE; break;
                    }
                }
            } while (map[y][x] == map[y][x+1] && map[y][x] == map[y][x+2]);
            break;
        case 2: // Vertical
            do {
                for (int i = 0; i < 3; i++) {
                    temp = rand() % 3;
                    switch (temp) {
                        case 0: map[y+i][x] = CIRCLE; break;
                        case 1: map[y+i][x] = SQUARE; break;
                        case 2: map[y+i][x] = TRIANGLE; break;
                    }
                }
            } while (map[y][x] == map[y+1][x] && map[y][x] == map[y+2][x]);
            break;
    }
    return 0;
}

int game_loop(int stats[7], char map[ymax][xmax]) {
    int gamestate = 0;
    
    do {
        print_map(map, stats);


    } while (gamestate == 0);
    return gamestate;
}