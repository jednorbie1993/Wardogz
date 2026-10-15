#include "sparring_unlocks.h"

#include <string.h>

#include "../console.h"

static void unlockSkill(
    Dog *d,
    int progressIndex,
    char *skillName,
    int power,
    int cost,
    const char *message
)
{
    if (d->sparringProgress[progressIndex] != 10)
        return;

    if (d->skillCount >= MAX_SKILLS)
        return;

    if (hasSkill(d, skillName))
        return;

    strcpy(d->skills[d->skillCount].name, skillName);
    d->skills[d->skillCount].power = power;
    d->skills[d->skillCount].cost = cost;
    d->skills[d->skillCount].type = SKILL_DAMAGE;
    d->skillCount++;

    printCentered(message);
}

void checkSparringUnlock(Dog *d)
{
    unlockSkill(
        d,
        0,
        "Ossas Counter",
        18,
        12,
        "OSSAS DEFEATED 10/10! UNLOCKED: Ossas Counter!"
    );

    unlockSkill(
        d,
        1,
        "Chubby Bulldozer",
        22,
        14,
        "CHUBBY DEFEATED 10/10! UNLOCKED: Chubby Bulldozer!"
    );

    unlockSkill(
        d,
        2,
        "Jeward Precision",
        25,
        15,
        "JEWARD DEFEATED 10/10! UNLOCKED: Jeward Precision!"
    );

    unlockSkill(
        d,
        3,
        "Tiny Blitz",
        20,
        13,
        "TINY DEFEATED 10/10! UNLOCKED: Tiny Blitz!"
    );

    unlockSkill(
        d,
        4,
        "Snoop Phantom",
        28,
        16,
        "SNOOP DEFEATED 10/10! UNLOCKED: Snoop Phantom!"
    );

    if (
        d->sparringProgress[5] == 10 &&
        d->skillCount < MAX_SKILLS &&
        !hasSkill(d, "Rival Breaker")
    )
    {
        strcpy(d->skills[d->skillCount].name, "Rival Breaker");
        d->skills[d->skillCount].power = 35;
        d->skills[d->skillCount].cost = 20;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skillCount++;

        printBlankLine();
        printCentered("NEW SKILL UNLOCKED: Rival Breaker!");
    }
}
