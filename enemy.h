#ifndef ENEMY_H
#define ENEMY_H

#include "dog.h"

int enemyAttack(Dog *player, Dog *enemy, int *defending);
void createEnemy(Dog *e);
void enemyTurn(Dog *player, Dog *enemy, int *defending);

void createEnemy(Dog *e);
void setEnemyByZone(Dog *enemy, int zoneIndex, int i);
void setEnemySkillsWild(Dog *enemy, int zoneIndex, int enemyLevel);
void enemyQuickAttack(Dog *player, Dog *enemy);

// skill-type enemy actions
int usePackAttack(Dog *user, Dog *target);
int useAmbush(Dog *user, Dog *target);
int useHowlDebuff(Dog *user, Dog *target);
int useFeralRush(Dog *user, Dog *target);

#endif