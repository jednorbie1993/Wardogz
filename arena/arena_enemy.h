#ifndef ARENA_ENEMY_H
#define ARENA_ENEMY_H

#include "dog.h"

void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id);

void loadArenaClassFEnemy(Dog *enemy, int enemyIndex);

void showArenaEnemyEntrance(Dog *enemy, char selectedRank);

#endif