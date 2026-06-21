#ifndef ARENA_ENEMY_S_H
#define ARENA_ENEMY_S_H

#include "../dog.h"

void loadArenaClassSEnemy(Dog *enemy, int enemyIndex);
void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id);

#endif
