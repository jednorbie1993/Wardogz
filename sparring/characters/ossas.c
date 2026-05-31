#include "ossas.h"
#include <string.h>
#include <stdlib.h>

#include "ossas.h"

void createOssas(Dog *e)
{
    strcpy(e->name, "Ossas");

    e->maxHP = 100;
    e->hp = e->maxHP;

    e->attack = 120 + rand() % 30;
    e->defense = 60 + rand() % 20;
    e->speed = 70 + rand() % 20;
    e->accuracy = 80 + rand() % 10;
    e->intelligence = 50;
}

void assignOssasSkills(Dog *d)
{
    d->skillCount = 4;

    strcpy(d->skills[0].name, "Wild Bite");
    d->skills[0].type = SKILL_DAMAGE;
    d->skills[0].power = 12;
    d->skills[0].accuracy = 90;

    strcpy(d->skills[1].name, "Rush Claw");
    d->skills[1].type = SKILL_DAMAGE;
    d->skills[1].power = 11;
    d->skills[1].accuracy = 95;

    strcpy(d->skills[2].name, "Headbutt");
    d->skills[2].type = SKILL_DEBUFF;
    d->skills[2].power = 13;
    d->skills[2].accuracy = 80;

    strcpy(d->skills[3].name, "Rage Leap");
    d->skills[3].type = SKILL_DAMAGE;
    d->skills[3].power = 10;
    d->skills[3].accuracy = 65;
    d->skills[3].cooldown = 3;
    d->skills[3].cdLeft = 0;
}