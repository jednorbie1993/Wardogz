#ifndef SNOOP_H
#define SNOOP_H

#include "../../dog.h"

void createSnoopy(Dog *e);
void assignSnoopySkills(Dog *d);
void applySnoopyEffect(Dog *user, Dog *enemy, Skill skill, int dmg);

#endif