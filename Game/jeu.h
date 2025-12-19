#include "parameters.h"

// IN: map vide | OUT: rien | genere carte initiale
void generate_map(char map[ymax][xmax]);

// IN: map, pos x,y, direction | OUT: char | remplace formes identiques
char shapepick(char map[ymax][xmax], int x, int y, int direction);

// IN: stats, map | OUT: rien | lance une partie
void playgame(int stats[], char map[ymax][xmax]);

// IN: stats | OUT: rien | calcule difficulte niveau
void difficulty(int stats[]);
