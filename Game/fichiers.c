#include "Fichiers.h"
#define SAVEFILE "savegame.txt"


void saveprogress(int level) {
    char playername[50];
    set_color(WHITE, BLACK);
    printf("Enter your name to save progress: ");
    scanf("%49s", playername);

    FILE *f = fopen(SAVEFILE, "a"); // ouvre le fichier pour écrire/ajouter, sans écraser
    if (f == NULL) {
        printf("Error: cannot open save file.\n");
        return;
    }

    // sauvegarde : pseudo + toutes les stats
    fprintf(f, "%s %d %d %d %d %d %d %d %d\n",
            playername,
            stats[0], stats[1], stats[2], stats[3], stats[4],
            stats[5], stats[6], stats[7]);
    fclose(f);

    printf("Progress saved for player '%s'!\n", playername);

}


// charge progression d’un joueur
void leveload(void) {
    char playername[50], , line[200], name_in_file[50];
    bool found = false;
    
    set_color(WHITE, BLACK);
    printf("Enter your name to load progress: ");
    scanf("%49s", playername);
    FILE *f = fopen(SAVEFILE, "r");
    if (f == NULL) {
        printf("No save file found.\n");
        return;
    }

    // Parcours du fichier ligne par ligne
    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%s %d %d %d %d %d %d %d %d",
               name_in_file,
               &stats[0], &stats[1], &stats[2], &stats[3], &stats[4],
               &stats[5], &stats[6], &stats[7]);

        if (strcmp(name_in_file, playername) == 0) {
            found = true;
            break;
        }
    }

    fclose(f);
    
    if (found) {
        printf("welcome back john doe! loading last level...\n");
    } else{
        printf("\n name not found, try again\n");
    }
    
}
