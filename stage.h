#ifndef STAGE_H
#define STAGE_H

#include "dog.h"

void startStage(Dog *player);
void setEnemyByZone(Dog *enemy, int zoneIndex, int i);
void battle(Dog *player, int zoneIndex, int progress[]);  // ✅ ADD THIS
void typeText(char *text, int speed);

#endif