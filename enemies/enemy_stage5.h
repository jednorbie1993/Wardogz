#ifndef ENEMY_STAGE5_H
#define ENEMY_STAGE5_H

#include "../dog.h"

void loadStage5Enemies(Dog *enemy, int zoneIndex, int enemyIndex);

// Zone 1 skill setters / skills
void setEnhancedStraySkills(Dog *enemy);
int useReinforcedBite(Dog *user, Dog *target);
int useCombatRush(Dog *user, Dog *target);
int usePredatorInstinct(Dog *user, Dog *target);
int useEnhancedJawCrush(Dog *user, Dog *target);

// Zone 2 skill setters / skills
void setWildTerritorySkills(Dog *enemy);
int useRazorSlash(Dog *user, Dog *target);
int useBloodFrenzy(Dog *user, Dog *target);
int useFangStorm(Dog *user, Dog *target);

// Zone 3 skill setters / skills
void setCombatPrototypeSkills(Dog *enemy);
int useTacticalBite(Dog *user, Dog *target);
int useArmorBreak(Dog *user, Dog *target);
int useSuppressionHowl(Dog *user, Dog *target);
int useBlacksiteExecution(Dog *user, Dog *target);

#endif
