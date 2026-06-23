#ifndef REPLAY_SYSTEM_H
#define REPLAY_SYSTEM_H
#define SECRET_GRIMFANG_INDEX 99
#define SECRET_DIREMAW_INDEX 98
#define SECRET_BLACKCLAW_INDEX 97
#define SECRET_OMEGA_INDEX 96
#define SECRET_GRIMFANG_X_INDEX 95


#include "dog.h"

int chooseReplayEnemyIndex(int zoneIndex, int progress[], int isWildTerritory);
void applyReplayEliteBonus(Dog *enemy, int zoneIndex, int enemyIndex);

#endif