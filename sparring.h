#ifndef SPARRING_H
#define SPARRING_H

#include "dog.h"

// 🥊 SPARRING-SPECIFIC SKILL IDS (local only)
typedef enum {
    SP_SKILL_ATTACK = SKILL_DAMAGE,
    SP_SKILL_HEAL   = SKILL_HEAL,
    SP_SKILL_BUFF   = SKILL_BUFF,
    SP_SKILL_DEBUFF = SKILL_DEBUFF
} SparSkillType;

// sparring system
int sparringBattle(Dog *player, int type);
void createSparPartner(Dog *e, int type);
void sparringMenu(Dog *player);
int useSkill(Dog *user, Dog *enemy, Skill skill);
void applySparReward(Dog *player, int type);
void assignSkills(Dog *d, int type);
int chooseEnemyMove(Dog *enemy, Dog *player, int type);
void createSparPlayer(Dog *orig, Dog *spar);

#endif