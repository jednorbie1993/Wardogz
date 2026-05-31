#include "jeward.h"
#include <string.h>
#include <stdlib.h>

#include "jeward.h"

void createJeward(Dog *e)
{
    strcpy(e->name, "Jeward");

    e->maxHP = 100;
    e->hp = e->maxHP;

    e->attack = 80 + rand() % 20;
    e->defense = 70 + rand() % 20;
    e->speed = 80 + rand() % 20;
    e->accuracy = 140 + rand() % 30;
    e->intelligence = 80;
}

void assignJewardSkills(Dog *d)
{
    d->skillCount = 4;

    strcpy(d->skills[0].name, "Precision Bite");
    d->skills[0].type = SKILL_DAMAGE;
    d->skills[0].power = 14;
    d->skills[0].accuracy = 100;

    strcpy(d->skills[1].name, "Eye Strike");
    d->skills[1].type = SKILL_DEBUFF;
    d->skills[1].power = 7;
    d->skills[1].accuracy = 90;

    strcpy(d->skills[2].name, "Counter Snap");
    d->skills[2].type = SKILL_DAMAGE;
    d->skills[2].power = 10;
    d->skills[2].accuracy = 95;

    strcpy(d->skills[3].name, "Focus Jab");
    d->skills[3].type = SKILL_BUFF;
    d->skills[3].power = 5;
    d->skills[3].accuracy = 100;
}