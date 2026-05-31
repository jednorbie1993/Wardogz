#ifndef SPARRING_SYSTEM_H
#define SPARRING_SYSTEM_H

#include "../dog.h"
#include "sparring_system.h"

void initSparringProgress(Dog *d);
void updateSparringProgress(Dog *d, int enemyIndex, int win);
void updateCooldowns(Dog *dog);
void applySparReward(Dog *player, int type);
void sparringMenu(Dog *player);

#endif