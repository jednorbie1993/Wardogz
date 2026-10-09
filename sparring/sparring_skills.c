#include "sparring_skills.h"

#include <string.h>

static Skill createDamageSkill(const char *name, int power, int accuracy)
{
    Skill skill;

    strcpy(skill.name, name);
    skill.type = SKILL_DAMAGE;
    skill.power = power;
    skill.accuracy = accuracy;

    return skill;
}

Skill createBiteSkill(void)
{
    return createDamageSkill("Bite", 10, 90);
}

Skill createScratchSkill(void)
{
    return createDamageSkill("Scratch", 8, 95);
}

Skill createChargeSkill(void)
{
    return createDamageSkill("Charge", 12, 80);
}

Skill createHipCheckSkill(void)
{
    return createDamageSkill("Hip Check", 9, 85);
}

Skill createPowerRushSkill(void)
{
    return createDamageSkill("Power Rush", 15, 80);
}

Skill createGuardBreakSkill(void)
{
    return createDamageSkill("Guard Break", 13, 90);
}
