#include "affichage.h"
#include "jeu.h"
#include "parameters.h"
#include "fichiers.h"



int main() { // je sais pas si c'est necessaire de retoucher ceci, probablement oui -> j'ai retouché un peu le switch case 3 sinon c bon je crois
    
    clrscr();
    SetConsoleOutputCP(65001); // UTF-8
    
    int level = 0, life = 3, score = 0, timeremaining = 60, turnsleft = 20 ,squareleft = 50, triangleleft = 50 , circleleft = 50 , diamondleft =50, hexagonleft=50;
    int stats[10] = {level, life, score, timeremaining, turnsleft, squareleft, triangleleft, circleleft, diamondleft, hexagonleft};
    bool gameover = false;
   
    char map[ymax][xmax];
    int i;
    
    srand(time(NULL));
    
    do{
        i = menu();
   switch (i) {
        case 3: // Start game
            // réinitialisation des stats pour une nouvelle partie
            stats[0] = 0;   // level
            stats[1] = 3;   // life
            difficulty(stats);
            playgame(stats, map);
            break;
        case 4:
            leveload(stats);
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
