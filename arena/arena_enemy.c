#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy.h"
#include "arena.h"
#include "../skill.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"

void setArenaSkill(Dog *enemy, int slot, const char *name, int power, int accuracy, SkillID id)
{
    enemy->skills[slot] = (Skill){"", power, 0, SKILL_DAMAGE, accuracy, id, 0, 0, 10};
    strcpy(enemy->skills[slot].name, name);
}

// ================= CLASS F =================
void loadArenaClassFEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->zoneType = ZONE_NORMAL;
    enemy->personalityType = PERSONALITY_NORMAL;
    enemy->numSkills = 4;

    // Class F scale:
    // Normal high stat: 120-140
    // Boss / specialty stat: up to 150-155
    // Weak stat: 45-80

    if (enemyIndex == 0)
    {
        // Fast beginner type
        strcpy(enemy->name, "Ace");
        enemy->maxHP = 115;
        enemy->attack = 72;
        enemy->defense = 58;
        enemy->speed = 135;
        enemy->accuracy = 115;
        enemy->intelligence = 55;

        setArenaSkill(enemy, 0, "Stray Bite", 8, 92, SKILL_STRAY_BITE);
        setArenaSkill(enemy, 1, "Ambush", 9, 88, SKILL_AMBUSH);
        setArenaSkill(enemy, 2, "Dirty Scratch", 7, 95, SKILL_DIRTY_SCRATCH);
        setArenaSkill(enemy, 3, "Quick Rush", 10, 90, SKILL_FERAL_RUSH);
    }
    else if (enemyIndex == 1)
    {
        // Power type, pero mabagal at hindi pa tanky
        strcpy(enemy->name, "Rexx");
        enemy->maxHP = 130;
        enemy->attack = 145;
        enemy->defense = 70;
        enemy->speed = 68;
        enemy->accuracy = 88;
        enemy->intelligence = 50;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Lock Jaw", 12, 82, SKILL_LOCK_JAW);
        setArenaSkill(enemy, 1, "Pack Attack", 10, 90, SKILL_PACK_ATTACK);
        setArenaSkill(enemy, 2, "Bone Breaker", 13, 78, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 3, "Feral Rush", 11, 86, SKILL_FERAL_RUSH);
    }
    else if (enemyIndex == 2)
    {
        // Tank type, mataas HP/DEF pero mahina attack/speed
        strcpy(enemy->name, "Knox");
        enemy->maxHP = 150;
        enemy->attack = 65;
        enemy->defense = 145;
        enemy->speed = 55;
        enemy->accuracy = 86;
        enemy->intelligence = 60;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Tactical Guard", 0, 100, SKILL_TACTICAL_GUARD);
        setArenaSkill(enemy, 1, "Stray Bite", 8, 92, SKILL_STRAY_BITE);
        setArenaSkill(enemy, 2, "Armor Snap", 11, 85, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 3, "Pack Attack", 10, 90, SKILL_PACK_ATTACK);
    }
    else
    {
        // Class F boss, konting lampas pero hindi pa E level
        strcpy(enemy->name, "Vex");
        enemy->maxHP = 155;
        enemy->attack = 135;
        enemy->defense = 90;
        enemy->speed = 125;
        enemy->accuracy = 110;
        enemy->intelligence = 75;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Ambush Strike", 14, 88, SKILL_AMBUSH_STRIKE);
        setArenaSkill(enemy, 1, "Combat Rush", 13, 90, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 2, "Blood Frenzy", 12, 85, SKILL_BLOOD_FRENZY);
        setArenaSkill(enemy, 3, "Alpha Rage", 15, 82, SKILL_ALPHA_RAGE);
    }

    enemy->hp = enemy->maxHP;
}



// ================= ENTRANCE =================
void showArenaEnemyEntrance(Dog *enemy, char selectedRank)
{
    system("cls");

    printf("===== %s =====\n", getArenaRankName(selectedRank));
    printf("Class %s Match\n\n", getArenaClassName(selectedRank));

    if (selectedRank == 'F')
    {
        char *arenaQuotes[] =
        {
            "The arena gates creak open.\n",
            "A challenger steps onto the dusty grounds.\n",
            "The crowd watches the next match in silence.\n",
            "Paws scrape against the arena floor.\n",
            "Another fighter enters the Open Grounds.\n"
        };

        typeText(arenaQuotes[rand() % 5], 20);
    }
    else if (selectedRank == 'E')
    {
        char *arenaQuotes[] =
        {
            "The crowd roars as another challenger enters the pit.\n",
            "Dust rises from the arena floor as the battle begins.\n",
            "The spectators lean forward in anticipation.\n",
            "A fierce opponent steps into the fighting grounds.\n",
            "The arena falls silent before the clash.\n"
        };

        typeText(arenaQuotes[rand() % 5], 20);
    }
    else if (selectedRank == 'D')
    {
        char *arenaQuotes[] =
        {
            "Scrap metal rattles across the junkyard.\n",
            "A fighter emerges from between rusted wrecks.\n",
            "The scent of oil fills the air.\n",
            "Broken steel echoes through the arena.\n",
            "The junkyard crowd gathers for another fight.\n"
        };

        typeText(arenaQuotes[rand() % 5], 20);
    }

    printf("\n%s entered the arena!\n", enemy->name);
    waitForEnter();
}