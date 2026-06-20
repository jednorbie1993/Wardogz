#ifndef ARENA_H
#define ARENA_H

#include "../dog.h"

void arenaMenu(Dog *player);
void selectArenaMenu(Dog *player);
void enterArena(Dog *player, char selectedRank);
int arenaBattle(Dog *player, char selectedRank);

const char *getArenaClassName(char rank);
const char *getArenaRankName(char rank);
const char *getArenaTitle(char rank);

int getRequiredWins(char rank);
int isFinalArenaCleared(Dog *player);

#endif
