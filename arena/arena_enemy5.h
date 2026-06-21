#ifndef ARENA_ENEMY5_H
#define ARENA_ENEMY5_H

#include "../dog.h"

void loadArenaClassBEnemy(Dog *enemy, int enemyIndex);
void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id);
#endif
