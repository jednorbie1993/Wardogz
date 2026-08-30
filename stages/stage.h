#ifndef STAGE_H
#define STAGE_H

#include "../dog.h"

void startStage(Dog *player, int progress[]);

void loadStage1Enemies(Dog *e, int zoneIndex, int enemyType);
void loadStage2Enemies(Dog *e, int zoneIndex, int enemyType);
void loadStage4Enemies(Dog *e, int zoneIndex, int enemyType);
void runStage4(Dog *player, int progress[]);

#endif