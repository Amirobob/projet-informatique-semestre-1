#include "jeu.h"
#include "affichage.h"


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
    int cursor_x = 0;
    int cursor_y = 0;
    
    gotoxy(1,1);
    show_cursor();
    int gamestate = 0;
    time_t last_update;
    time(&last_update);
    
    // Initial draw
    clrscr();
    print_map(map, stats, cursor_x, cursor_y);
    
    do {
        time_t current;
        time(&current);
        
        bool needs_redraw = false;
        
        // Check if timer needs update (every second)
        int diff = (int)difftime(current, last_update);
        if (diff >= 1) {
            stats[3] = stats[3] - diff; // Update time remaining
            time(&last_update); // Reset the timer
            needs_redraw = true;
        }
        
        // Check for keyboard input
        if (kbhit()) {
            char input = getch();
            switch (input) {
                case 'q':
                    gamestate = 2; // Game lost
                    break;
                case 'w':
                    if (cursor_y > 0) {
                        cursor_y--;
                        needs_redraw = true;
                    }
                    break;
                case 's':
                    if (cursor_y < ymax - 1) {
                        cursor_y++;
                        needs_redraw = true;
                    }
                    break;
                case 'a':
                    if (cursor_x > 0) {
                        cursor_x--;
                        needs_redraw = true;
                    }
                    break;
                case 'd':
                    if (cursor_x < xmax - 1) {
                        cursor_x++;
                        needs_redraw = true;
                    }
                    break;
                case ' ':
                // not done yet
                // dont forget to do stats[4]-- here
                    needs_redraw = true;
                    break;
            }
        }
        
        if (needs_redraw) {
            clrscr();
            print_map(map, stats, cursor_x, cursor_y);
        }

        // put end conditions
        
    } while (gamestate == 0);
    
    return gamestate;
}


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