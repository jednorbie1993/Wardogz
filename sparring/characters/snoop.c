#include "snoop.h"
#include <string.h>
#include <stdlib.h>

#include "snoop.h"

void createSnoopy(Dog *e)
{
    strcpy(e->name, "Snoopy");

    e->maxHP = 100;
    e->hp = e->maxHP;

    e->attack = 70 + rand() % 20;
    e->defense = 60 + rand() % 20;
    e->speed = 110 + rand() % 20;
    e->accuracy = 85 + rand() % 15;
    e->intelligence = 70;
}

void assignSnoopySkills(Dog *d)
{
    d->skillCount = 4;

    strcpy(d->skills[0].name, "Speed Dash");
    d->skills[0].type = SKILL_DAMAGE;
    d->skills[0].power = 9;
    d->skills[0].accuracy = 100;
    d->skills[0].cooldown = 2;
    d->skills[0].cdLeft = 0;

    strcpy(d->skills[1].name, "Triple Bite");
    d->skills[1].type = SKILL_DAMAGE;
    d->skills[1].power = 15;
    d->skills[1].accuracy = 75;
    d->skills[1].cooldown = 3;
    d->skills[1].cdLeft = 0;

    strcpy(d->skills[2].name, "Wind Kick");
    d->skills[2].type = SKILL_DEBUFF;
    d->skills[2].power = 7;
    d->skills[2].accuracy = 90;

    strcpy(d->skills[3].name, "Flash Dodge");
    d->skills[3].type = SKILL_BUFF;
    d->skills[3].power = 8;
    d->skills[3].accuracy = 100;
}