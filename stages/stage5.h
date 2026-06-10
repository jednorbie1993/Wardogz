#ifndef STAGE5_H
#define STAGE5_H

#include "../dog.h"
#include <stdio.h>

void loadStage5Enemies(Dog *enemy, int zoneIndex, int enemyType);
int getZoneMaxStage5(int zoneIndex);
void runStage5(Dog *player, int progress[]);

#endif