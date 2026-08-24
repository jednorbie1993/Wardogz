#ifndef DOG_UTILS_H
#define DOG_UTILS_H

#include "dog.h"

void setEnemySkillsWild(Dog *enemy, int zoneIndex, int enemyLevel);
void preBattleScene(int zoneIndex);
void applyBattleStatGain(Dog *d);

#endif