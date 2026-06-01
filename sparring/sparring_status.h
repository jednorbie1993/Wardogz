#ifndef SPARRING_STATUS_H
#define SPARRING_STATUS_H

#include "../dog.h"

void printSparringStatus(Dog *player, Dog *enemy);
void updateDebuffs(Dog *d);
void printHPBar(int hp, int maxHP);

#endif