#include "sparring_skills.h"

#include <string.h>

Skill createBiteSkill(void)
{
    Skill skill;

    strcpy(skill.name, "Bite");
    skill.type = SKILL_DAMAGE;
    skill.power = 10;
    skill.accuracy = 90;

    return skill;
}

Skill createScratchSkill(void)
{
    Skill skill;

    strcpy(skill.name, "Scratch");
    skill.type = SKILL_DAMAGE;
    skill.power = 8;
    skill.accuracy = 95;

    return skill;
}

Skill createChargeSkill(void)
{
    Skill skill;

    strcpy(skill.name, "Charge");
    skill.type = SKILL_DAMAGE;
    skill.power = 12;
    skill.accuracy = 80;

    return skill;
}

Skill createHipCheckSkill(void)
{
    Skill skill;

    strcpy(skill.name, "Hip Check");
    skill.type = SKILL_DAMAGE;
    skill.power = 9;
    skill.accuracy = 85;

    return skill;
}