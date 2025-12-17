#include "affichage.h"
#include "jeu.h"
#include "parameters.h"
#include "fichiers.h"



int main() {
    clrscr();
    show_cursor();
    gotoxy(0,0);
    SetConsoleOutputCP(65001); // UTF-8
    int level = 0, life = 3, score = 0, timeremaining = 60, turnsleft = 20 ,squareleft = 50, triangleleft = 50 , circleleft = 50;
    int stats[7] = {level, life, score, timeremaining, turnsleft, squareleft, triangleleft, circleleft};
    bool gameover = false;
    char map[ymax][xmax];
    int i;
    srand(time(NULL));
    do{
        i = menu();
   switch (i) {
        case 3:
            playgame(stats, map);
            break;
        case 4:
            leveload();
            break;
        case 5:
            instructions();
            break;
        case 6:
            printf("Exiting game. Goodbye!\n");
            return 0;
        default:
            break;
        }
    } while (1);
    return 0;
}