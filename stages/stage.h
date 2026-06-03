#ifndef STAGE_H
#define STAGE_H

#include "../dog.h"

void startStage(Dog *player, int progress[]);
void setEnemyByZone(Dog *enemy, int zoneIndex, int i);
int battle(Dog *player, int zoneIndex, int progress[]);
int battleWithEnemyIndex(Dog *player, int zoneIndex, int progress[], int enemyIndex);  // ✅ ADD THIS

void loadStage1Enemies(Dog *e, int zoneIndex, int enemyType);
void loadStage2Enemies(Dog *e, int zoneIndex, int enemyType);
void loadStage4Enemies(Dog *e, int zoneIndex, int enemyType);
void runStage4(Dog *player, int progress[]);

#endif