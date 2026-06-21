#ifndef ARENA_ENEMY_H
#define ARENA_ENEMY_H

#include "../dog.h"

void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id);

void loadArenaClassFEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassEEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassDEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassCEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassBEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassAEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassSEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassSSEnemy(Dog *enemy, int enemyIndex);
void loadArenaClassSSSEnemy(Dog *enemy, int enemyIndex);

void showArenaEnemyEntrance(Dog *enemy, char selectedRank);

#endif