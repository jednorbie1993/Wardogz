#ifndef ARENA_ENEMY4_H
#define ARENA_ENEMY4_H

#include "../dog.h"


void loadArenaClassCEnemy(Dog *enemy, int enemyIndex);

void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id);


#endif