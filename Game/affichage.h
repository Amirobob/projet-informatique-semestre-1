#include "parameters.h"

// IN: gameover, level, life | OUT: int choix | affiche ecran fin
int endscreen(bool gameover, int level, int life);

// IN: rien | OUT: int choix | affiche menu principal
int menu(void);

// IN: map, stats, curseur | OUT: bool | affiche grille jeu
bool print_map(char map[ymax][xmax], int stats[10], int cursor_x, int cursor_y);

// IN: rien | OUT: rien | affiche tutoriel + demo
void instructions(void);
