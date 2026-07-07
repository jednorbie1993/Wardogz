#ifndef SAVE_H
#define SAVE_H

#include "dog.h"

#define SAVE_FILE "save.dat"

typedef struct
{
    Dog player;
    int restCount;
    int progress[19];
} GameData;

int saveGame(GameData *game);
int loadGame(GameData *game);

#endif