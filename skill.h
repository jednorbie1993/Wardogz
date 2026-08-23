#ifndef SKILL_H
#define SKILL_H
#define TIER_NORMAL 1
#define TIER_STRONG 2
#define TIER_ULTIMATE 3

#include "dog.h"

void checkSkillUnlock(Dog *d);
void applySkillEffect(Dog *player, Dog *enemy, Skill s, int *damage);
int useSkill(Dog *user, Dog *target, Skill skill);
int calculateDamage(Dog *attacker, Dog *defender, Skill skill);
void applySpecialEffects(Dog *player, Dog *enemy, Skill s, int *damage);
int getSkillTier(Skill s);
int computeBaseDamage(Dog *player, Dog *enemy, Skill s);

#endif
