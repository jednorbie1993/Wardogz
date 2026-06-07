#ifndef REPLAY_SYSTEM_H
#define REPLAY_SYSTEM_H
#define SECRET_GRIMFANG_INDEX 99
#define SECRET_DIREMAW_INDEX 98

#include "dog.h"

int chooseReplayEnemyIndex(int zoneIndex, int progress[], int isWildTerritory);
void applyReplayEliteBonus(Dog *enemy, int zoneIndex, int enemyIndex);

#endif