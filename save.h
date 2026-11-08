#ifndef SAVE_H
#define SAVE_H

#include "dog.h"

#define SAVE_FILE "save.dat"

typedef struct
{
    Dog player;
    int restCount;
    int progress[21];
} GameData;

int saveGame(GameData *game);
/* 1 loaded, 0 missing, -1 invalid/unreadable; never overwrite an invalid save. */
int loadGame(GameData *game);

#endif