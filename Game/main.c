#include "affichage.h"
#include "jeu.h"
#include "parameters.h"
#include "fichiers.h"



int main(){ //main du jeu
    
    clrscr();
    SetConsoleOutputCP(65001); //UTF-8
    
    int level=0, life=3, score=0, timeremaining=60, turnsleft=20 ,squareleft=50, triangleleft=50 , circleleft=50 , diamondleft=50, hexagonleft=50;
    int stats[10]={level, life, score, timeremaining, turnsleft, squareleft, triangleleft, circleleft, diamondleft, hexagonleft};
    bool gameover=false;
   
    char map[ymax][xmax];
    int i;
    
    srand(time(NULL));
    
    do{
        i=menu();
   switch(i){
        case 3: //demarrer
            //reinit stats
            stats[0]=0;   //level
            stats[1]=3;   //life
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
            printf("Au revoir!\n");
            return 0;
        default:
            break;
        }
    }while(1);
    return 0;
}
