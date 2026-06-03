#ifndef BATTLE_H
#define BATTLE_H

#include "dog.h"

int battle(Dog *player, int zoneIndex, int progress[]);
int battleWithEnemyIndex(Dog *player, int zoneIndex, int progress[], int enemyIndex);
void displayBattleStatus(Dog player, Dog enemy);
void zoneStoryIntro(int zoneIndex, int progress);

#endif