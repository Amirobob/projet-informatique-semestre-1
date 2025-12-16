#include "affichage.h"

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
    }
}


int menu(void) {
    // setup
    set_color(WHITE, BLACK);
    char input = 0;
    int selected = 3; 
    const int min_select = 3, max_select = 6;
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

    // menu select
    int running = 1;
    while (running) {
        clrscr();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 32; j++) {
                bool inside = (j > 2 && j < 30);

                if (i == selected && inside) set_color(BLACK, WHITE);
                else if (i == 1 && inside) set_color(YELLOW, BLACK);
                else if ((i == 3 && inside) || (i == 4 && inside)) set_color(GREEN, BLACK);
                else if (i == 5 && inside) set_color(BLUE, BLACK);
                else if (i == 6 && inside) set_color(RED, BLACK);
                else set_color(WHITE, BLACK);
                printf("%c", menu[i][j]);
            }
            printf("\n");
        }
        // Wait for key press
        while (!kbhit()) {}
        input = getch();
        if (input == 's' && selected < max_select) selected++;
        else if (input == 'w' && selected > min_select) selected--;
        else if (input == '\n' || input == ' ') running = 0;
    }
    return selected;
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







void instructions(void) {
    clrscr();
    set_color(WHITE, BLACK);
    getch();
}