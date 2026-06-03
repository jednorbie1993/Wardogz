#ifndef JEWARD_H
#define JEWARD_H

#include "../../dog.h"

void createJeward(Dog *e);
void assignJewardSkills(Dog *d);
void applyJewardEffect(Dog *user, Dog *enemy, Skill skill, int dmg);

#endif