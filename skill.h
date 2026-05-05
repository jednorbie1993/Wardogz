#ifndef SKILL_H
#define SKILL_H

#include "dog.h"

void checkSkillUnlock(Dog *d);
void applySkillEffect(Dog *player, Dog *enemy, Skill s, int *damage);
int useSkill(Dog *user, Dog *target, Skill skill);
int calculateDamage(Dog *attacker, Dog *defender, Skill skill);
void applySkillEffect(Dog *user, Dog *target, Skill skill, int *damage);

#endif