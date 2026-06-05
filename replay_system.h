#ifndef REPLAY_SYSTEM_H
#define REPLAY_SYSTEM_H

#include "dog.h"

int chooseReplayEnemyIndex(int zoneIndex, int progress[]);
void applyReplayEliteBonus(Dog *enemy, int zoneIndex, int enemyIndex);

#endif