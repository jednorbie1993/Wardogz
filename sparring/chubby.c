#include "chubby.h"
#include <string.h>
#include <stdlib.h>

void createChubby(Dog *e)
{
    strcpy(e->name, "Chubby");

    e->maxHP = 100;
    e->hp = e->maxHP;

    e->attack = 60 + rand() % 20;
    e->defense = 130 + rand() % 40;
    e->speed = 50 + rand() % 15;
    e->accuracy = 70 + rand() % 10;
    e->intelligence = 60;
}

void assignChubbySkills(Dog *d)
{
    d->skillCount = 4;

    strcpy(d->skills[0].name, "Body Slam");
    d->skills[0].type = SKILL_DAMAGE;
    d->skills[0].power = 10;
    d->skills[0].accuracy = 95;

    strcpy(d->skills[1].name, "Slow Slam");
    d->skills[1].type = SKILL_DAMAGE;
    d->skills[1].power = 8;
    d->skills[1].accuracy = 95;

    strcpy(d->skills[2].name, "Guard Bash");
    d->skills[2].type = SKILL_DEBUFF;
    d->skills[2].power = 6;
    d->skills[2].accuracy = 85;

    strcpy(d->skills[3].name, "Heavy Crush");
    d->skills[3].type = SKILL_DAMAGE;
    d->skills[3].power = 12;
    d->skills[3].accuracy = 75;
    d->skills[3].cooldown = 2;
    d->skills[3].cdLeft = 0;
}