#ifndef SPARRING_AI_H
#define SPARRING_AI_H
#define AGGRESSIVE 1
#define BALANCED 2
#define CAUTIOUS 3

#include "../dog.h"

int chooseEnemyMove(Dog *enemy, Dog *player, int type);
int useSkill(Dog *attacker, Dog *target, Skill skill);

#endif