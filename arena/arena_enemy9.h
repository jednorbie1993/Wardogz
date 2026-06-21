#ifndef ARENA_ENEMY9_H
#define ARENA_ENEMY9_H

#include "../dog.h"

void loadArenaClassSSSEnemy(Dog *enemy, int enemyIndex);
void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id);

#endif
