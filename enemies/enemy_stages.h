#ifndef ENEMY_STAGES_H
#define ENEMY_STAGES_H

#include "../dog.h"

void loadStage1Enemies(Dog *enemy, int zoneIndex, int enemyIndex);
void loadStage2Enemies(Dog *enemy, int zoneIndex, int enemyIndex);
void loadStage3Enemies(Dog *enemy, int zoneIndex, int enemyIndex);
void loadStage4Enemies(Dog *enemy, int zoneIndex, int enemyIndex);
void loadStage5Enemies(Dog *enemy, int zoneIndex, int enemyIndex);

void setEnemySkillsStage1(Dog *enemy);
void setEnemySkillsMilitary(Dog *enemy, int zoneIndex);
void setEnemySkillsBio(Dog *enemy, int zoneIndex);

#endif
