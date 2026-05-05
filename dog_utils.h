#ifndef DOG_UTILS_H
#define DOG_UTILS_H

#include "dog.h"

void setEnemyByZone(Dog *enemy, int zoneIndex, int i);
void setEnemySkillsWild(Dog *enemy, int zoneIndex, int enemyLevel);
void preBattleScene();
void applyBattleStatGain(Dog *d);

#endif