#include "jeu.h"
#include "affichage.h"
#include "fichiers.h"


void generate_map(char map[ymax][xmax]) {
    int temp;
    for (int y = 0; y < ymax; y++) {
        for (int x = 0; x < xmax; x++) {
            bool onborder = (y == 0 || y == ymax - 1|| x == 0 || x == xmax - 1);
            if (onborder) map[y][x] = '#';
            else {
                switch(temp = rand() % 5) {  // Changed from 3 to 5
                case(0): map[y][x] = CIRCLE; break;
                case(1): map[y][x] = SQUARE; break;
                case(2): map[y][x] = TRIANGLE; break;
                case(3): map[y][x] = DIAMOND; break;
                case(4): map[y][x] = HEXAGON; break;
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
                if (horizontal) {
                    shapepick(map, x, y,1);
                }
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
                    temp = rand() % 5;  // Changed from 3 to 5
                    switch (temp) {
                        case 0: map[y][x+i] = CIRCLE; break;
                        case 1: map[y][x+i] = SQUARE; break;
                        case 2: map[y][x+i] = TRIANGLE; break;
                        case 3: map[y][x+i] = DIAMOND; break;
                        case 4: map[y][x+i] = HEXAGON; break;
                    }
                }
            } while (map[y][x] == map[y][x+1] && map[y][x] == map[y][x+2]);
            break;
        case 2: // Vertical
            do {
                for (int i = 0; i < 3; i++) {
                    temp = rand() % 5;  // Changed from 3 to 5
                    switch (temp) {
                        case 0: map[y+i][x] = CIRCLE; break;
                        case 1: map[y+i][x] = SQUARE; break;
                        case 2: map[y+i][x] = TRIANGLE; break;
                        case 3: map[y+i][x] = DIAMOND; break;
                        case 4: map[y+i][x] = HEXAGON; break;
                    }
                }
            } while (map[y][x] == map[y+1][x] && map[y][x] == map[y+2][x]);
            break;
    }
    return 0;
}

void moveshape(char map[ymax][xmax], int x, int y, int stats[10]) {
    char input;
    
    clrscr();
    print_map(map, stats, x, y);
    
    input = getch();
    
    int new_x = x;
    int new_y = y;
    
    switch (input) {
        case 'w':
        case 'z':
            if (y > 1) new_y = y - 1;
            break;
        case 's':
            if (y < ymax - 2) new_y = y + 1;
            break;
        case 'a':
        case 'q':
            if (x > 1) new_x = x - 1;
            break;
        case 'd':
            if (x < xmax - 2) new_x = x + 1;
            break;
    }
    
    if (new_x != x || new_y != y) {
        char temp = map[new_y][new_x];
        map[new_y][new_x] = map[y][x];
        map[y][x] = temp;
        stats[4]--;
    }
} 

void clear_type(char map[ymax][xmax], int stats[10], char c) {
    int count = 0;
    for (int i = 1; i < ymax - 1; i++) {
        for (int j = 1; j < xmax - 1; j++) {
            if (map[i][j] == c) {
                map[i][j] = ' ';
                count++;
            }
        }
    }
    stats[2] += count;
    if (c == SQUARE && stats[5] > 0) stats[5] -= count;
    else if (c == TRIANGLE && stats[6] > 0) stats[6] -= count;
    else if (c == CIRCLE && stats[7] > 0) stats[7] -= count;
    else if (c == DIAMOND && stats[8] > 0) stats[8] -= count;
    else if (c == HEXAGON && stats[9] > 0) stats[9] -= count;
}

void gravity(char map[ymax][xmax]) {
    bool moved = true;
    while (moved) {
        moved = false;
        for (int y = ymax - 3; y >= 1; y--) {
            for (int x = 1; x < xmax - 1; x++) {
                if (map[y][x] != ' ' && map[y+1][x] == ' ') {
                    map[y+1][x] = map[y][x];
                    map[y][x] = ' ';
                    moved = true;
                }
            }
        }
    }
    
    char types[] = {CIRCLE, SQUARE, TRIANGLE, DIAMOND, HEXAGON};  // Added new shapes
    for (int x = 1; x < xmax - 1; x++) {
        for (int y = 1; y < ymax - 1; y++) {
            if (map[y][x] == ' ') {
                map[y][x] = types[rand() % 5];  // Changed from 3 to 5
            }
        }
    }
}

bool destroy(char map[ymax][xmax], int stats[10]) {
    bool destroyed = false;
    
    for (int y = 1; y < ymax - 1; y++) {
        for (int x = 1; x < xmax - 1; x++) {
            char c = map[y][x];
            if (c == ' ') continue;
            
            // Horizontal 6
            bool h6 = (x <= xmax - 7 && 
                      map[y][x+1] == c && map[y][x+2] == c && 
                      map[y][x+3] == c && map[y][x+4] == c && map[y][x+5] == c);
            
            // Vertical 6
            bool v6 = (y <= ymax - 7 && 
                      map[y+1][x] == c && map[y+2][x] == c && 
                      map[y+3][x] == c && map[y+4][x] == c && map[y+5][x] == c);
            
            if (h6 || v6) {
                clear_type(map, stats, c);
                destroyed = true;
                continue;
            }
            
            // Cross 5x5
            bool cross = (x >= 3 && x <= xmax - 4 && y >= 3 && y <= ymax - 4 &&
                         map[y-2][x] == c && map[y-1][x] == c && 
                         map[y+1][x] == c && map[y+2][x] == c &&
                         map[y][x-2] == c && map[y][x-1] == c && 
                         map[y][x+1] == c && map[y][x+2] == c);
            
            if (cross) {
                int count = 0;
                for (int j = 1; j < xmax - 1; j++) {
                    if (map[y][j] == c) {
                        map[y][j] = ' ';
                        count++;
                    }
                }
                for (int i = 1; i < ymax - 1; i++) {
                    if (map[i][x] == c) {
                        map[i][x] = ' ';
                        count++;
                    }
                }
                stats[2] += count;
                if (c == SQUARE && stats[5] > 0) stats[5] -= count;
                else if (c == TRIANGLE && stats[6] > 0) stats[6] -= count;
                else if (c == CIRCLE && stats[7] > 0) stats[7] -= count;
                else if (c == DIAMOND && stats[8] > 0) stats[8] -= count;
                else if (c == HEXAGON && stats[9] > 0) stats[9] -= count;
                destroyed = true;
                continue;
            }
            
            // Hollow square
            bool square = (x <= xmax - 5 && y <= ymax - 5 &&
                          map[y][x+1] == c && map[y][x+2] == c && map[y][x+3] == c &&
                          map[y+1][x] == c && map[y+1][x+3] == c &&
                          map[y+2][x] == c && map[y+2][x+3] == c &&
                          map[y+3][x] == c && map[y+3][x+1] == c && 
                          map[y+3][x+2] == c && map[y+3][x+3] == c);
            
            if (square) {
                int count = 0;
                int border_count = 0;
                for (int i = 0; i < 4; i++) {
                    if (map[y][x+i] != ' ') {
                        map[y][x+i] = ' ';
                        count++;
                        border_count++;
                    }
                    if (map[y+3][x+i] != ' ') {
                        map[y+3][x+i] = ' ';
                        count++;
                        border_count++;
                    }
                }
                for (int i = 1; i < 3; i++) {
                    if (map[y+i][x] != ' ') {
                        map[y+i][x] = ' ';
                        count++;
                        border_count++;
                    }
                    if (map[y+i][x+3] != ' ') {
                        map[y+i][x+3] = ' ';
                        count++;
                        border_count++;
                    }
                }
                for (int i = 1; i < 3; i++) {
                    for (int j = 1; j < 3; j++) {
                        if (map[y+i][x+j] != ' ') {
                            char inside = map[y+i][x+j];
                            map[y+i][x+j] = ' ';
                            count++;
                            if (inside == SQUARE && stats[5] > 0) stats[5]--;
                            else if (inside == TRIANGLE && stats[6] > 0) stats[6]--;
                            else if (inside == CIRCLE && stats[7] > 0) stats[7]--;
                            else if (inside == DIAMOND && stats[8] > 0) stats[8]--;
                            else if (inside == HEXAGON && stats[9] > 0) stats[9]--;
                        }
                    }
                }
                stats[2] += count;
                if (c == SQUARE && stats[5] > 0) stats[5] -= border_count;
                else if (c == TRIANGLE && stats[6] > 0) stats[6] -= border_count;
                else if (c == CIRCLE && stats[7] > 0) stats[7] -= border_count;
                else if (c == DIAMOND && stats[8] > 0) stats[8] -= border_count;
                else if (c == HEXAGON && stats[9] > 0) stats[9] -= border_count;
                destroyed = true;
                continue;
            }
            
            // Horizontal 4
            bool h4 = (x <= xmax - 5 && 
                map[y][x+1] == c && map[y][x+2] == c && map[y][x+3] == c);
            if (h4) {
                for (int i = 0; i < 4; i++) map[y][x+i] = ' ';
                destroyed = true;
                stats[2] += 4;
                if (c == SQUARE && stats[5] > 0) stats[5] -= 4;
                else if (c == TRIANGLE && stats[6] > 0) stats[6] -= 4;
                else if (c == CIRCLE && stats[7] > 0) stats[7] -= 4;
                else if (c == DIAMOND && stats[8] > 0) stats[8] -= 4;
                else if (c == HEXAGON && stats[9] > 0) stats[9] -= 4;
            }
            
            // Vertical 4
            bool v4 = (y <= ymax - 5 && 
                      map[y+1][x] == c && map[y+2][x] == c && map[y+3][x] == c);
            if (v4) {
                for (int i = 0; i < 4; i++) map[y+i][x] = ' ';
                destroyed = true;
                stats[2] += 4;
                if (c == SQUARE && stats[5] > 0) stats[5] -= 4;
                else if (c == TRIANGLE && stats[6] > 0) stats[6] -= 4;
                else if (c == CIRCLE && stats[7] > 0) stats[7] -= 4;
                else if (c == DIAMOND && stats[8] > 0) stats[8] -= 4;
                else if (c == HEXAGON && stats[9] > 0) stats[9] -= 4;
            }
            if (stats[5] < 0) stats[5] = 0;
            if (stats[6] < 0) stats[6] = 0;
            if (stats[7] < 0) stats[7] = 0;
            if (stats[8] < 0) stats[8] = 0;
            if (stats[9] < 0) stats[9] = 0;
        }
    }
    
    return destroyed;
}

int game_loop(int stats[10], char map[ymax][xmax]) {
    int cursor_x = 1;
    int cursor_y = 1;
    
    gotoxy(1,1);
    show_cursor();
    int gamestate = 0;
    time_t last_update;
    time(&last_update);
    
    clrscr();
    print_map(map, stats, cursor_x, cursor_y);
    
    do {
        time_t current;
        time(&current);
        
        bool needs_redraw = false;
        
        int diff = (int)difftime(current, last_update);
        if (diff >= 1) {
            stats[3] = stats[3] - diff;
            time(&last_update);
            needs_redraw = true;
        }
        
        if (kbhit()) {
            char input = getch();
            switch (input) {
                case 'w':
                case 'z':
                    if (cursor_y > 1) {
                        cursor_y--;
                        needs_redraw = true;
                    }
                    break;
                case 's':
                    if (cursor_y < ymax - 2) {
                        cursor_y++;
                        needs_redraw = true;
                    }
                    break;
                case 'a':
                case 'q':
                    if (cursor_x > 1) {
                        cursor_x--;
                        needs_redraw = true;
                    }
                    break;
                case 'd':
                    if (cursor_x < xmax - 2) {
                        cursor_x++;
                        needs_redraw = true;
                    }
                    break;
                case ' ':
                    moveshape(map, cursor_x, cursor_y, stats);
                    while (kbhit()) {
                        getch();
                    }
                    while (destroy(map, stats)) {
                        clrscr();
                        print_map(map, stats, cursor_x, cursor_y);
                        Sleep(500);
                        
                        gravity(map);
                        
                        clrscr();
                        print_map(map, stats, cursor_x, cursor_y);
                        Sleep(500);
                    }
                    needs_redraw = true;
                    break;
            }
        }
        
        if (needs_redraw) {
            clrscr();
            print_map(map, stats, cursor_x, cursor_y);
        }

        if (stats[1] <= 0 || stats[3] <= 0 || stats[4] <= 0) {
            gamestate = 2;
        }
        if (stats[5] <= 0 && stats[6] <= 0 && stats[7] <= 0 && stats[8] <= 0 && stats[9] <= 0) {
            gamestate = 1;
        }
        
    } while (gamestate == 0);
    
    return gamestate;
}

void difficulty(int stats[]) {
    int level = stats[0];
    
    stats[3] = 60 - (level * 2);
    stats[4] = 20 - level;
    for (int i = 5; i <= 9; i++) {
        stats[i] = level * 2 + rand() % 20;
    }
    if (stats[3] < 30) stats[3] = 30;
    if (stats[4] < 10) stats[4] = 10;
}

void playgame(int stats[], char map[ymax][xmax]) {
    generate_map(map);
    switch(game_loop(stats, map)) {
        case 1:
        stats[0]++;
        switch (endscreen(0, stats[0], stats[1])) {
            case 0:
                generate_map(map);
                difficulty(stats);
                playgame(stats, map);
                break;
            case 1:
                saveprogress(stats[0], stats);
                break;
            case 2:
                break;
        }
        break;
        case 2:
        stats[1]--;
        switch (endscreen(1, stats[0], stats[1])) {
            case 0:
                generate_map(map);
                stats[3] = 60;
                stats[4] = 20;
                difficulty(stats);
                playgame(stats, map);
                break;
            case 1:
                saveprogress(stats[0], stats);
                break;
            case 2:
                break;
        }
        break;
    }
}