#include "affichage.h"

int endscreen(bool gameover, int level, int life) {
    set_color(WHITE, BLACK);
    char input = 0;
    int selected = 0;
    const int min_select = 0;
    const int max_select = 2;
    
    // Define both menus
    char gameover_menu[13][18] = {
        " _______________ ",
        "|  ___________  |",
        "| |  perdu !  | |",
        "| |___________| |",
        "|_______________|",
        " Meilleure fois!",
        " ________________",
        "|   Reessayer   |",
        "|________________|",
        "|sauver niveau  |",
        "|________________|",
        "|    Quitter    |",
        "|________________|"
    };
    
    char won_menu[13][34] = {
        " _______________________________ ",
        "|  ___________________________  |",
        "| |  Felicitations, gagne !   | |",
        "| |___________________________| |",
        "|_______________________________|",
        "                                ",
        "       ________________         ",
        "      | Niveau suivant|        ",
        "      |________________|        ",
        "      |Sauver progres |        ",
        "      |________________|        ",
        "      |    Quitter    |        ",
        "      |________________|        "
    };
    char wonforgood[13][34] = {
        " _______________________________ ",
        "|  ___________________________  |",
        "| |    Jeu termine ! Bravo!   | |",
        "| |___________________________| |",
        "|_______________________________|",
        "                                ",
        "       ________________         ",
        "      |  Mode infini  |        ",
        "      |________________|        ",
        "      |Sauver progres |        ",
        "      |________________|        ",
        "      |    Quitter    |        ",
        "      |________________|        "
    };
    char doneforgood[9][18] = {
        " _______________ ",
        "|  ___________  |",
        "| |  perdu !  | |",
        "| |___________| |",
        "|_______________|",
        "Plus de vies!   ",
        " ________________",
        "|    Quitter    |",
        "|________________|",
    };
    int running = 1;
    while (running) {
        clrscr();
        if (!gameover && level == 3) {
            for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 34; j++) {
                    if (i >= 0 && i <= 4) {
                        set_color(GREEN, BLACK);
                    }
                    else if (i == 5) {
                        set_color(WHITE, BLACK);
                    }
                    else if (i > 6 && i <= 8 && selected == 0 && j > 6 && j < 23) {
                        set_color(BLACK, WHITE);
                    }
                    else if (i >= 9 && i <= 10 && selected == 1 && j > 6 && j < 23) {
                        set_color(BLACK, WHITE);
                    }
                    else if (i >= 11 && i <= 12 && selected == 2 && j > 6 && j < 23) {
                        set_color(BLACK, WHITE);
                    }
                    else {
                        set_color(WHITE, BLACK);
                    }
                    printf("%c", wonforgood[i][j]);
                }
                printf("\n");
            }
        }
        else if (gameover && life == 0) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 18; j++) {
                    if (i <= 4) {
                        set_color(RED, BLACK);
                    }
                    else if (i >= 7 && i <= 8) {
                        set_color(BLACK, WHITE);
                    }
                    printf("%c", doneforgood[i][j]);
                }
                printf("\n");
            }
            while (getch() != ' ') {}
            return 2;
        }
        else if (gameover) {
            for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 18; j++) {
                    if (i >= 0 && i <= 4) {
                        set_color(RED, BLACK);
                    }
                    else if (i == 5) {
                        set_color(WHITE, BLACK);
                    }
                    else if (i > 6 && i <= 8 && selected == 0 && j > 0 && j < 17) {
                        set_color(BLACK, WHITE);
                    }
                    else if (i >= 9 && i <= 10 && selected == 1 && j > 0 && j < 17) {
                        set_color(BLACK, WHITE);
                    }
                    else if (i >= 11 && i <= 12 && selected == 2 && j > 0 && j < 17) {
                        set_color(BLACK, WHITE);
                    }
                    else {
                        set_color(WHITE, BLACK);
                    }
                    printf("%c", gameover_menu[i][j]);
                }
                printf("\n");
            }
        } else {
            for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 34; j++) {
                    if (i >= 0 && i <= 4) {
                        set_color(GREEN, BLACK);
                    }
                    else if (i == 5) {
                        set_color(WHITE, BLACK);
                    }
                    else if (i > 6 && i <= 8 && selected == 0 && j > 6 && j < 23) {
                        set_color(BLACK, WHITE);
                    }
                    else if (i >= 9 && i <= 10 && selected == 1 && j > 6 && j < 23) {
                        set_color(BLACK, WHITE);
                    }
                    else if (i >= 11 && i <= 12 && selected == 2 && j > 6 && j < 23) {
                        set_color(BLACK, WHITE);
                    }
                    else {
                        set_color(WHITE, BLACK);
                    }
                    printf("%c", won_menu[i][j]);
                }
                printf("\n");
            }
        }
        
        set_color(WHITE, BLACK);
        
        while (!kbhit()) {}
        input = getch();
        
        if (input == 's' && selected < max_select) selected++;
        else if ((input == 'w' || input == 'z') && selected > min_select) selected--;
        else if (input == '\n' || input == ' ') running = 0;
    }
    
    set_color(WHITE, BLACK);
    return selected;
}


int menu(void) {
    set_color(WHITE, BLACK);
    char input = 0;
    int selected = 3; 
    const int min_select = 3, max_select = 6;
    char menu[9][32] = {
        "|-----------------------------|",
        "|         ECE Heroes!         |",
        "|-----------------------------|",
        "|      1. Demarrer Jeu        |",
        "|      2. Continuer Jeu       |",
        "|      3. Instructions        |",
        "|      4. Quitter             |",
        "|-----------------------------|"
    };

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
        while (!kbhit()) {}
        input = getch();
        if (input == 's' && selected < max_select) selected++;
        else if (input == 'w' && selected > min_select || input == 'z' && selected > min_select) selected--;
        else if (input == '\n' || input == ' ') running = 0;
    }
    return selected;
}


void stat(int y, int stats[10]){
    switch(y){
        case 1:
            set_color(GREEN, BLACK);
            printf("   |Score: %d", stats[2]);
            break;
        case 2:
            set_color(MAGENTA, BLACK);
            printf("   |Niveau: %d\tVies: %d", stats[0]+1, stats[1]);
            break;
        case 3:
            set_color(RED, BLACK);
            printf("   |Temps: %d\tTours: %d", stats[3], stats[4]);
            break;
        case 4:
            set_color(YELLOW, BLACK);
            printf("   |Carres restants: %d", stats[5]);
            break;
        case 5:
            set_color(GREEN, BLACK);
            printf("   |Triangles restants: %d", stats[6]);
            break;
        case 6:
            set_color(BLUE, BLACK);
            printf("   |Cercles restants: %d", stats[7]);
            break;
        case 7:
            set_color(RED, BLACK);
            printf("   |Diamants restants: %d", stats[8]);
            break;
        case 8:
            set_color(CYAN, BLACK);
            printf("   |Hexagones restants: %d", stats[9]);
            break;
    } 
}


bool print_map(char map[ymax][xmax], int stats[10], int cursor_x, int cursor_y) {  // Changed from stats[8] to stats[10]
   
    // Get current time for star color animation (changes every second)
    time_t current_time = time(NULL);
    int color_cycle = (int)(current_time % 6); // 6 colors cycle
    int star_colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
    int star_color = star_colors[color_cycle];
    
    for (int y = 0; y < ymax; y++) {
        
        for (int x = 0; x < xmax; x++) {
            char c = map[y][x];
            
            bool is_cursor = (y == cursor_y && x == cursor_x);
            
            int bg_color = is_cursor ? WHITE : BLACK;
            
            if (c == CIRCLE) {
                set_color(BLUE, bg_color);
                printf("● ");
            } else if (c == SQUARE) {
                set_color(YELLOW, bg_color);
                printf("■ ");
            } else if (c == TRIANGLE) {
                set_color(GREEN, bg_color);
                printf("▲ ");
            } else if (c == DIAMOND) {  // Added diamond
                set_color(RED, bg_color);
                printf("◆ ");
            } else if (c == HEXAGON) {  // Added hexagon
                set_color(CYAN, bg_color);
                printf("⬡ ");
            } else if (c == STAR) {  // Special star block with color animation
                set_color(star_color, bg_color);
                printf("★ ");
            } else if (c == '#') {
                set_color(MAGENTA, bg_color);
                printf("▩ ");
            } else {
                set_color(WHITE, bg_color);
                printf("  ");
            }
        }
        
        set_color(WHITE, BLACK);
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
    printf("- navigue ce donjon avec ZQSD, et espace pour echanger deux formes adjacentes.\n");
    printf("- Nous, on sera la pour te rappeler combien il en reste à combattre !\n\n");

    set_color(CYAN, BLACK);
    printf("Mais detrompe-toi, ce n'est pas si facile. Ton temps sera compte.\n");
    printf("Une minute de gainage te semble longue ? Ici, elle semblera horriblement courte.\n");
    printf("Alors, ne te fais pas avoir par le chrono !\n\n");

    printf("On m'a dit que quand le cours est fini, tu es le premier a ranger tes affaires.\n");
    printf("Utilise cette rapidite comme un atout !\n\n");

    set_color(YELLOW, BLACK);
    printf("BONNN ca commence à vraiment urgent que tu nous aide, on y va ? ");
    printf("Clique pour continuer...");
    getch();
    
    // --- PARTIE 4 : DEMO INTERACTIVE ---
    clrscr();
    set_color(CYAN, BLACK);
    printf("\n=== DEMO INTERACTIVE - Entraîne-toi ! ===\n\n");
    set_color(WHITE, BLACK);
    printf("Avant de partir, essayons ensemble sur un petit terrain d'entrainement.\n");
    printf("C'est un espace 4x2, parfait pour comprendre les bases.\n\n");
    
    printf("Contrôles :\n");
    printf("  - ZQSD pour déplacer le curseur\n");
    printf("  - ESPACE pour échanger deux formes adjacentes\n");
    printf("  - Aligne 4 formes identiques (horizontalement ou verticalement)\n");
    printf("  - ESC pour quitter le tutoriel\n\n");
    
    set_color(GREEN, BLACK);
    printf("Objectif : Aligne les carrés jaunes ! ■ ■ ■ ■\n\n");
    set_color(WHITE, BLACK);
    printf("Appuie sur une touche pour commencer...");
    getch();
    
    // Création du mini-terrain 4x2 (avec bordures = 6x4)
    #define TUTORIAL_WIDTH 6
    #define TUTORIAL_HEIGHT 4
    char tutorial_map[TUTORIAL_HEIGHT][TUTORIAL_WIDTH] = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', 's', 's', 'c', 's', '#'},
        {'#', 't', 's', 'c', 't', '#'},
        {'#', '#', '#', '#', '#', '#'}
    };
    
    int t_cursor_x = 1;
    int t_cursor_y = 1;
    bool tutorial_running = true;
    int moves = 0;
    
    while (tutorial_running) {
        clrscr();
        
        // Affichage du titre
        set_color(CYAN, BLACK);
        printf("=== TERRAIN D'ENTRAINEMENT ===\n\n");
        
        // Affichage de la grille
        for (int y = 0; y < TUTORIAL_HEIGHT; y++) {
            printf("   ");
            for (int x = 0; x < TUTORIAL_WIDTH; x++) {
                char c = tutorial_map[y][x];
                bool is_cursor = (y == t_cursor_y && x == t_cursor_x);
                int bg_color = is_cursor ? WHITE : BLACK;
                
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
            set_color(WHITE, BLACK);
            printf("\n");
        }
        
        printf("\n");
        set_color(WHITE, BLACK);
        printf("   Mouvements effectués : %d\n", moves);
        set_color(YELLOW, BLACK);
        printf("   Astuce : Échange le cercle avec un carré !\n");
        set_color(WHITE, BLACK);
        printf("   [ESC] pour quitter\n");
        
        // Vérifier si le joueur a gagné (4 carrés alignés horizontalement)
        bool won = false;
        for (int y = 1; y < TUTORIAL_HEIGHT - 1; y++) {
            for (int x = 1; x <= TUTORIAL_WIDTH - 4; x++) {
                if (tutorial_map[y][x] == 's' && 
                    tutorial_map[y][x+1] == 's' && 
                    tutorial_map[y][x+2] == 's' && 
                    tutorial_map[y][x+3] == 's') {
                    won = true;
                }
            }
        }
        
        if (won) {
            set_color(GREEN, BLACK);
            printf("\n   ★ BRAVO ! Tu as aligné 4 carrés ! ★\n");
            set_color(WHITE, BLACK);
            printf("   Tu es prêt pour la vraie aventure !\n");
            printf("\n   Appuie sur une touche pour continuer...");
            getch();
            tutorial_running = false;
            break;
        }
        
        // Gestion des entrées
        char input = getch();
        int new_x = t_cursor_x;
        int new_y = t_cursor_y;
        
        switch (input) {
            case 27: // ESC
                tutorial_running = false;
                break;
            case 'w':
            case 'z':
                if (t_cursor_y > 1) new_y = t_cursor_y - 1;
                break;
            case 's':
                if (t_cursor_y < TUTORIAL_HEIGHT - 2) new_y = t_cursor_y + 1;
                break;
            case 'q':
            case 'a':
                if (t_cursor_x > 1) new_x = t_cursor_x - 1;
                break;
            case 'd':
                if (t_cursor_x < TUTORIAL_WIDTH - 2) new_x = t_cursor_x + 1;
                break;
            case ' ':
                // Demander dans quelle direction échanger
                clrscr();
                printf("\n\n   Dans quelle direction échanger ?\n");
                printf("   [Z]Haut [S]Bas [Q]Gauche [D]Droite [ESC]Annuler\n");
                char dir = getch();
                int swap_x = t_cursor_x;
                int swap_y = t_cursor_y;
                bool valid_swap = false;
                
                switch (dir) {
                    case 'w':
                    case 'z':
                        if (t_cursor_y > 1) {
                            swap_y = t_cursor_y - 1;
                            valid_swap = true;
                        }
                        break;
                    case 's':
                        if (t_cursor_y < TUTORIAL_HEIGHT - 2) {
                            swap_y = t_cursor_y + 1;
                            valid_swap = true;
                        }
                        break;
                    case 'q':
                    case 'a':
                        if (t_cursor_x > 1) {
                            swap_x = t_cursor_x - 1;
                            valid_swap = true;
                        }
                        break;
                    case 'd':
                        if (t_cursor_x < TUTORIAL_WIDTH - 2) {
                            swap_x = t_cursor_x + 1;
                            valid_swap = true;
                        }
                        break;
                }
                
                if (valid_swap) {
                    // Échanger les formes
                    char temp = tutorial_map[swap_y][swap_x];
                    tutorial_map[swap_y][swap_x] = tutorial_map[t_cursor_y][t_cursor_x];
                    tutorial_map[t_cursor_y][t_cursor_x] = temp;
                    moves++;
                }
                break;
        }
        
        t_cursor_x = new_x;
        t_cursor_y = new_y;
    }
    
    clrscr();
    set_color(GREEN, BLACK);
    printf("\n\n   Parfait ! Tu es maintenant prêt pour l'aventure !\n");
    printf("   N'oublie pas : courage et persévérance sont tes meilleurs alliés.\n");
    printf("   dans le fôret il existe des combinaisons des carrés et même l'élusive suite de 6...\n\n");
    set_color(WHITE, BLACK);
    printf("   Bonne chance, héros !\n\n");
    printf("   Appuie sur une touche pour revenir au menu...");
    getch();
}
