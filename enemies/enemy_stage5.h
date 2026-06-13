#ifndef ENEMY_STAGE5_H
#define ENEMY_STAGE5_H

#include "../dog.h"

void loadStage5Enemies(Dog *enemy, int zoneIndex, int enemyIndex);
int useReinforcedBite(Dog *user, Dog *target);
int useCombatRush(Dog *user, Dog *target);
int usePredatorInstinct(Dog *user, Dog *target);
int useEnhancedJawCrush(Dog *user, Dog *target);

int useRazorSlash(Dog *user, Dog *target);
int useBloodFrenzy(Dog *user, Dog *target);
int useFangStorm(Dog *user, Dog *target);

void setWildTerritorySkills(Dog *enemy);

#endif