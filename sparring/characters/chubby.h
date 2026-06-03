#ifndef CHUBBY_H
#define CHUBBY_H

#include "../../dog.h"

void createChubby(Dog *e);
void assignChubbySkills(Dog *d);
void applyChubbyEffect(Dog *user, Dog *enemy, Skill skill, int dmg);

#endif