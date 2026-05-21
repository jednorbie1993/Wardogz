#ifndef ENEMY_H
#define ENEMY_H

#include "../dog.h"
#include "enemy_stage3.h"

int enemyAttack(Dog *player, Dog *enemy, int *defending);
void createEnemy(Dog *e);
void enemyTurn(Dog *player, Dog *enemy, int *defending);

void createEnemy(Dog *e);
void setEnemyByZone(Dog *enemy, int zoneIndex, int i);
void setEnemySkillsWild(Dog *enemy, int zoneIndex, int enemyLevel);
void enemyQuickAttack(Dog *player, Dog *enemy);

int handleStage1EnemyBehavior(Dog *player, Dog *enemy, int *enemyDamage);

// skill-type enemy actions
int usePackAttack(Dog *user, Dog *target);
int useAmbush(Dog *user, Dog *target);
int useHowlDebuff(Dog *user, Dog *target);
int useFeralRush(Dog *user, Dog *target);

int usePrecisionShot(Dog *user, Dog *target);
int useTacticalGuard(Dog *user, Dog *target);
int useReinforcement(Dog *user, Dog *target);
int useSelfDestruct(Dog *user, Dog *target);
int useMilitaryCharge(Dog *user, Dog *target);
int useBarrageFire(Dog *user, Dog *target);

void setEnemySkillsMilitary(Dog *enemy, int zoneIndex);

// Add this at the TOP of enemy.c (after your includes):

// 🧬 BIO LAB SKILLS FORWARD DECLARATIONS
int useMutationSurge(Dog *user, Dog *target);
int useBioShield(Dog *user, Dog *target);
int useCellRegen(Dog *user, Dog *target);
int useContainedExplosion(Dog *user, Dog *target);
int useAcidSpit(Dog *user, Dog *target);
int useNeuroToxin(Dog *user, Dog *target);

void loadStage1Enemies(Dog *enemy, int zoneIndex, int enemyIndex);
void loadStage2Enemies(Dog *enemy, int zoneIndex, int enemyIndex);
void loadStage3Enemies(Dog *enemy, int zoneIndex, int enemyIndex);

#endif