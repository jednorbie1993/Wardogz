#ifndef ARENA_ENEMY8_H
#define ARENA_ENEMY8_H

#include "../dog.h"

void loadArenaClassSSEnemy(Dog *enemy, int enemyIndex);
void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id);

#endif

