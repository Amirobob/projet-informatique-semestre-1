#include "Fichiers.h"
#include "jeu.h"
#define SAVEFILE "savegame.txt"

#define MAX_PLAYERS 100

typedef struct{
    char name[50];
    int stats[10];
}Player;

//charger tous
int load_all_players(Player players[]){
    FILE *f=fopen(SAVEFILE, "r");
    if(f==NULL) return 0;
    
    int count=0;
    while(count<MAX_PLAYERS && 
           fscanf(f, "%49s %d %d %d %d %d %d %d %d %d %d",  
                  players[count].name,
                  &players[count].stats[0],
                  &players[count].stats[1],
                  &players[count].stats[2],
                  &players[count].stats[3],
                  &players[count].stats[4],
                  &players[count].stats[5],
                  &players[count].stats[6],
                  &players[count].stats[7],
                  &players[count].stats[8],
                  &players[count].stats[9])==11){
        count++;
    }
    fclose(f);
    return count;
}

//sauvegarder tous
void save_all_players(Player players[], int count){
    FILE *f=fopen(SAVEFILE, "w");
    if(f==NULL){
        printf("Erreur sauvegarde.\n");
        getch();
        return;
    }
    
    for(int i=0; i<count; i++){
        fprintf(f, "%s %d %d %d %d %d %d %d %d %d %d\n",
                players[i].name,
                players[i].stats[0], players[i].stats[1],
                players[i].stats[2], players[i].stats[3],
                players[i].stats[4], players[i].stats[5],
                players[i].stats[6], players[i].stats[7],
                players[i].stats[8], players[i].stats[9]);
    }
    fclose(f);
}

//trouver joueur
int find_player(Player players[], int count, const char *name){
    for(int i=0; i<count; i++){
        if(strcmp(players[i].name, name)==0){
            return i;
        }
    }
    return -1;
}

//sauvegarder progres
void saveprogress(int stats[]){
    int exit=0;
    char playername[50];
    Player players[MAX_PLAYERS];
    do{
        set_color(WHITE, BLACK);
        printf("Entrez votre nom: ");
        scanf("%49s", playername);
        
        int count=load_all_players(players);
        int index=find_player(players, count, playername);
        
        if(index>=0){
            printf("Nom '%s' existe deja!\n", playername);
            getch();
        }
        
        //nouveau joueur
        else if(count>=MAX_PLAYERS){
            printf("Limite atteinte!\n");
            getch();
        }
        else{
            strcpy(players[count].name, playername);
            for(int i=0; i<10; i++){
                players[count].stats[i]=stats[i];
            }
            count++;
        
            save_all_players(players, count);
            printf("Progres sauvegarde '%s'!\n", playername);
            getch();
            exit=1;
        }
    }while(exit==0);
}

//charger partie
void leveload(int stats[]){
    char playername[50];
    Player players[MAX_PLAYERS];
    
    set_color(WHITE, BLACK);
    printf("Entrez votre nom: ");
    scanf("%49s", playername);
    
    int count=load_all_players(players);
    int index=find_player(players, count, playername);
    
    if(index>=0){
        for(int i=0; i<10; i++){
            stats[i]=players[index].stats[i];
        }
        printf("Bienvenue %s! Chargement...\n", playername);
        
        char map[ymax][xmax];
        generate_map(map);
        playgame(stats, map);
    }else{
        printf("\nNom introuvable\n");
    }
    getch();
}
