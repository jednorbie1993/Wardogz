#ifndef ARENA_ENEMY_H
#define ARENA_ENEMY_H

#include "../dog.h"

void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id);

void loadArenaClassFEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassEEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassDEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassCEnemy(Dog *enemy, int index)

void showArenaEnemyEntrance(Dog *enemy, char selectedRank);

#endif