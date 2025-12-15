#include "affichage.h"
#include "jeu.h"
#include "parameters.h"
#include "fichiers.h"



int main() {
    clrscr();
    show_cursor();
    gotoxy(0,0);
    SetConsoleOutputCP(65001); // UTF-8
    int level = 1, life = 3, score = 0, timeremaining = 60, turnsleft = 20 ,squareleft = 50, triangleleft = 50 , circleleft = 50;
    int stats[8] = {level, life, score, timeremaining, turnsleft, squareleft, triangleleft, circleleft};
    bool gameover = false;
  
    char map[ymax][xmax];
    srand(time(NULL));
    menu();
    leveload();
    generate_map(map);
    gameover = print_map(map, stats);
    endscreen(gameover,level);
    return 0;
}