#ifndef STAGE_H
#define STAGE_H

#include "dog.h"

void startStage(Dog *player);
void setEnemyByZone(Dog *enemy, int zoneIndex, int i);
int battle(Dog *player, int zoneIndex, int progress[]);  // ✅ ADD THIS

void loadStage1Enemies(Dog *e, int zoneIndex, int enemyType);
void loadStage2Enemies(Dog *e, int zoneIndex, int enemyType);

#endif