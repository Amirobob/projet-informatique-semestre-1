#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include "affichage_console.h"

//square grid size
#define xmax 12
#define ymax 12

// Shapes, we cannot change them to symbols here cuz switch case is annoying as hell
#define CIRCLE 'c'
#define TRIANGLE 't'
#define SQUARE 's'