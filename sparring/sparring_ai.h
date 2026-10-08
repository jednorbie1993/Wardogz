#ifndef SPARRING_AI_H
#define SPARRING_AI_H

#include "../dog.h"

#define AGGRESSIVE 1
#define BALANCED 2
#define CAUTIOUS 3

int chooseEnemyMove(Dog *enemy, Dog *player, int type);

#endif
