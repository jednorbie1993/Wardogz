#include "sparring_unlocks.h"
#include <stdio.h>
#include <string.h>
#include "../console.h"

void checkSparringUnlock(Dog *d)
{
    if (d->sparringProgress[0] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Ossas Counter"))
    {
        strcpy(d->skills[d->skillCount].name, "Ossas Counter");
        d->skills[d->skillCount].power = 18;
        d->skills[d->skillCount].cost = 12;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printCentered("OSSAS DEFEATED 10/10! UNLOCKED: Ossas Counter!");
        d->skillCount++;
    }

    if (d->sparringProgress[1] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Chubby Bulldozer"))
    {
        strcpy(d->skills[d->skillCount].name, "Chubby Bulldozer");
        d->skills[d->skillCount].power = 22;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printCentered("CHUBBY DEFEATED 10/10! UNLOCKED: Chubby Bulldozer!");
        d->skillCount++;
    }

    if (d->sparringProgress[2] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Tiny Blitz"))
    {
        strcpy(d->skills[d->skillCount].name, "Tiny Blitz");
        d->skills[d->skillCount].power = 20;
        d->skills[d->skillCount].cost = 13;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printCentered("TINY DEFEATED 10/10! UNLOCKED: Tiny Blitz!");
        d->skillCount++;
    }

    if (d->sparringProgress[3] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Jeward Precision"))
    {
        strcpy(d->skills[d->skillCount].name, "Jeward Precision");
        d->skills[d->skillCount].power = 25;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printCentered("JEWARD DEFEATED 10/10! UNLOCKED: Jeward Precision!");
        d->skillCount++;
    }

    if (d->sparringProgress[4] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Snoop Phantom"))
    {
        strcpy(d->skills[d->skillCount].name, "Snoop Phantom");
        d->skills[d->skillCount].power = 28;
        d->skills[d->skillCount].cost = 16;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printCentered("SNOOP DEFEATED 10/10! UNLOCKED: Snoop Phantom!");
        d->skillCount++;
    }

    // ================= RIVAL SPARRING SKILL =================
    if (d->sparringProgress[5] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Rival Breaker"))
    {
        strcpy(d->skills[d->skillCount].name, "Rival Breaker");
        d->skills[d->skillCount].power = 35;
        d->skills[d->skillCount].cost = 20;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        d->skillCount++;

        printBlankLine();
        printCentered("NEW SKILL UNLOCKED: Rival Breaker!");
    }
}