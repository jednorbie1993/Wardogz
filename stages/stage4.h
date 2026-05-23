#ifndef STAGE4_H
#define STAGE4_H

#include "../dog.h"
#include <stdio.h>

void loadStage4Enemies(Dog *enemy, int zoneIndex, int enemyType);
int getZoneMaxStage4(int zoneIndex);
void runStage4(Dog *player, int progress[]);

#endif