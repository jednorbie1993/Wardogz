#ifndef BATTLE_H
#define BATTLE_H

#include "dog.h"

int battle(Dog *player, int zoneIndex, int progress[]);
void displayBattleStatus(Dog player, Dog enemy);

#endif