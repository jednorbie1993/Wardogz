#include "tiny.h"
#include <string.h>
#include <stdlib.h>

#include "tiny.h"

void createTiny(Dog *e)
{
    strcpy(e->name, "Tiny");

    e->maxHP = 100;
    e->hp = e->maxHP;

    e->attack = 70 + rand() % 20;
    e->defense = 60 + rand() % 20;
    e->speed = 60 + rand() % 20;
    e->accuracy = 80 + rand() % 15;
    e->intelligence = 150 + rand() % 40;
}

void assignTinySkills(Dog *d)
{
    d->skillCount = 4;

    strcpy(d->skills[0].name, "Mind Bite");
    d->skills[0].type = SKILL_DAMAGE;
    d->skills[0].power = 11;
    d->skills[0].accuracy = 90;

    strcpy(d->skills[1].name, "Quick Dodge Bite");
    d->skills[1].type = SKILL_DAMAGE;
    d->skills[1].power = 11;
    d->skills[1].accuracy = 95;

    strcpy(d->skills[2].name, "Confuse Peck");
    d->skills[2].type = SKILL_DEBUFF;
    d->skills[2].power = 8;
    d->skills[2].accuracy = 80;

    strcpy(d->skills[3].name, "Brain Crush");
    d->skills[3].type = SKILL_DAMAGE;
    d->skills[3].power = 13;
    d->skills[3].accuracy = 85;
    d->skills[3].cooldown = 2;
    d->skills[3].cdLeft = 0;
}