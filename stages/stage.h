#ifndef STAGE_H
#define STAGE_H

#include "../dog.h"

void startStage(Dog *player, int progress[]);

void runStage1(Dog *player, int progress[]);
void runStage2(Dog *player, int progress[]);
void runStage3(Dog *player, int progress[]);
void runStage4(Dog *player, int progress[]);
void runStage5(Dog *player, int progress[]);

int getZoneMax(int zoneIndex);
int getZoneMaxStage4(int zoneIndex);
int getZoneMaxStage5(int zoneIndex);


#endif
