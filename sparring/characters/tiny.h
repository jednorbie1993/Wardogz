#ifndef TINY_H
#define TINY_H

#include "../../dog.h"
#include "../../skill.h"

void createTiny(Dog *e);
void assignTinySkills(Dog *d);
void applyTinyEffect(Dog *user, Dog *enemy, Skill skill, int dmg);
#endif