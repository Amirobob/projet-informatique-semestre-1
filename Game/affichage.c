#include "affichage.h"

void endscreen(bool gameover, int level) { // il faut afficher ces menus lorsque le jeu est fini, ils doivent etre navigables comme le menu principal, n'oubliez pas d'augmenter le niveau du jeu
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
    while (running) { // vous pouvez en vrai essayer de copy coller ce code pour faire un menu
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
        else if (input == 'w' && selected > min_select || input == 'z' && selected > min_select) selected--;
        else if (input == '\n' || input == ' ') running = 0;
    }
    return selected;
}



void stat(int y,int stats[8]){ // ne touchez pas, celui ci est fait
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





bool print_map(char map[ymax][xmax], int stats[8], int cursor_x, int cursor_y) { // on peut rajouter des trucs apres, mais pas pour le moment
   
    for (int y = 0; y < ymax; y++) {
        
        for (int x = 0; x < xmax; x++) {
            char c = map[y][x];
            
            // Check if this position is under the cursor
            bool is_cursor = (y == cursor_y && x == cursor_x);
            
            // Set background color FIRST based on cursor
            int bg_color = is_cursor ? WHITE : BLACK;
            
            // Draw the candy with appropriate color and background
            if (c == CIRCLE) {
                set_color(BLUE, bg_color);
                printf("● ");
            } else if (c == SQUARE) {
                set_color(YELLOW, bg_color);
                printf("■ ");
            } else if (c == TRIANGLE) {
                set_color(GREEN, bg_color);
                printf("▲ ");
            } else if (c == '#') {
                set_color(MAGENTA, bg_color);
                printf("▩ ");
            } else {
                set_color(WHITE, bg_color);
                printf("  ");
            }
        }
        
        set_color(WHITE, BLACK); // Reset before printing stats
        stat(y, stats);
        printf("\n");
    }
    set_color(WHITE, BLACK);
    return true;
}







void instructions(void) { // ajouter des tutoriels ici pour expliquer le jeu, avec des printf et de photos si vous etes motivés
    clrscr();
    
    // --- PARTIE 1 : L'accueil ---
    set_color(CYAN, BLACK);
    printf("Oh, tu es la... \n");
    Sleep(1500);
    printf("Je n'aurais pas pensé te voir ici. Je te pensais moins courageux...\n\n");
    Sleep(1000);
    
    set_color(YELLOW, BLACK);
    printf("MAIS...\n\n");
    Sleep(1000);
    
    set_color(WHITE, BLACK);
    printf("Si on t'a envoyé ici, c'est qu'ils ont confiance en toi.\n");
    printf("On va avoir besoin de ton aide, cher aventurier(e) !\n");
    printf("Et puis, si tu es la, c'est que tu as reussi à survivre aux cours d'informatique\n");
    printf("du vendredi apres-midi. Ils savent tres bien ce qu'ils font en t'envoyant la ");
    set_color(YELLOW, BLACK); printf(":-) \n\n");
    
    set_color(WHITE, BLACK);
    printf("Tu viens de poser le pied sur un terrain dangereux, mais on croit TOUS en toi.\n");
    printf("Tu ne vas pas nous abandonner !!! C'est courageux (ou inconscient...).\n\n");
    Sleep(2000);

    // --- PARTIE 2 : L'ambiance ---
    set_color(GREEN, BLACK);
    printf("Cela ne va pas être de tout repos, les formes antiques n'ont pas envie de cooperer,\n");
    printf("mais on compte sur toi pour nous aider a restaurer l'ordre.\n");
    set_color(WHITE, BLACK);
    printf("Ne t'inquiete pas, on te suivra de tres pres... enfin, surtout de tres loin,\n");
    printf("bien a l'abri derriere nos ecrans pendant que tu transpires !\n\n");
    
    printf("On pourra meme te souffler des petites aides si tu as trop de mal...\n");
    printf("Mais cela ne risque pas d'arriver !!! On ne t'a pas choisi au hasard !!!\n\n");
    Sleep(2000);

    // --- PARTIE 3 : L'explication du jeu ---
    set_color(MAGENTA, BLACK);
    printf("Ah, mais tu ne sais toujours pas pourquoi on t'a amené ici ?\n");
    printf("Ils ne t'ont donc rien expliqué ?\n");
    set_color(WHITE, BLACK);
    printf("Bon mon cher ami, je vais t'expliquer tout ça rapidement car le temps presse !\n\n");
    
    printf("- Tu vas partir à la quete de pieces d'or.\n");
    printf("- Tu vas affronter 3 niveaux, mais gare a toi, ils sont de plus en plus durs.\n");
    printf("- Ton but : aligner des formes entre elles pour les faire disparaitre.\n");
    printf("- Nous, on sera la pour te rappeler combien il en reste à combattre !\n\n");

    set_color(CYAN, BLACK);
    printf("Mais detrompe-toi, ce n'est pas si facile. Ton temps sera compte.\n");
    printf("Une minute de gainage te semble longue ? Ici, elle semblera horriblement courte.\n");
    printf("Alors, ne te fais pas avoir par le chrono !\n\n");

    printf("On m'a dit que quand le cours est fini, tu es le premier a ranger tes affaires.\n");
    printf("Utilise cette rapidite comme un atout !\n\n");

    set_color(YELLOW, BLACK);
    printf("Appuyez sur une touche pour entrer dans la jungle...");
    getch();
}
