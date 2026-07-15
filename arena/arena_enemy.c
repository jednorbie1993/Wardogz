#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy.h"
#include "arena.h"
#include "../skill.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "../console.h"

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
static void typeArenaTextCentered(const char *text, int delay)
{
    int len = strlen(text);
    int spaces = (CONSOLE_WIDTH - len) / 2;

    if (spaces < 0)
        spaces = 0;

    for (int i = 0; i < spaces; i++)
        printf(" ");

    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delay);
    }

    printf("\n");
}

void showArenaEnemyEntrance(Dog *enemy, char selectedRank)
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered(getArenaRankName(selectedRank));
    printCenteredFormat("Class %s Match", getArenaClassName(selectedRank));
    printBlankLine();

    const char *arenaQuotes[5];

    if (selectedRank == 'F')
    {
        arenaQuotes[0] = "The arena gates creak open.";
        arenaQuotes[1] = "A challenger steps onto the dusty grounds.";
        arenaQuotes[2] = "The crowd watches the next match in silence.";
        arenaQuotes[3] = "Paws scrape against the arena floor.";
        arenaQuotes[4] = "Another fighter enters the Open Grounds.";
    }
    else if (selectedRank == 'E')
    {
        arenaQuotes[0] = "The crowd roars as another challenger enters the pit.";
        arenaQuotes[1] = "Dust rises from the arena floor as the battle begins.";
        arenaQuotes[2] = "The spectators lean forward in anticipation.";
        arenaQuotes[3] = "A fierce opponent steps into the fighting grounds.";
        arenaQuotes[4] = "The arena falls silent before the clash.";
    }
    else if (selectedRank == 'D')
    {
        arenaQuotes[0] = "Scrap metal rattles across the junkyard.";
        arenaQuotes[1] = "A fighter emerges from between rusted wrecks.";
        arenaQuotes[2] = "The scent of oil fills the air.";
        arenaQuotes[3] = "Broken steel echoes through the arena.";
        arenaQuotes[4] = "The junkyard crowd gathers for another fight.";
    }
    else if (selectedRank == 'C')
    {
        arenaQuotes[0] = "The crowd falls silent as the next contender appears.";
        arenaQuotes[1] = "Strange scars cover the fighter's body.";
        arenaQuotes[2] = "The arena lights flicker for a brief moment.";
        arenaQuotes[3] = "An unnatural growl echoes through the battleground.";
        arenaQuotes[4] = "The spectators whisper as the challenger steps forward.";
    }
    else if (selectedRank == 'B')
    {
        arenaQuotes[0] = "Veteran fighters watch closely from the shadows.";
        arenaQuotes[1] = "The arena trembles as a powerful contender approaches.";
        arenaQuotes[2] = "Countless battles have shaped the warrior before you.";
        arenaQuotes[3] = "A chilling presence spreads across the battlefield.";
        arenaQuotes[4] = "The crowd senses that this match will not be an easy one.";
    }
    else if (selectedRank == 'A')
    {
        arenaQuotes[0] = "Elite contenders gather beneath the arena lights.";
        arenaQuotes[1] = "Every fighter here has survived countless battles.";
        arenaQuotes[2] = "The air grows heavy as an A-Class warrior steps forward.";
        arenaQuotes[3] = "The crowd erupts as another elite challenger enters the arena.";
        arenaQuotes[4] = "Only the strongest reach this level of competition.";
    }
    else if (selectedRank == 'S')
    {
        arenaQuotes[0] = "Silence falls as a legendary warrior enters the battlefield.";
        arenaQuotes[1] = "Few fighters ever reach the realm of Class S.";
        arenaQuotes[2] = "The ground trembles beneath the footsteps of a champion.";
        arenaQuotes[3] = "Veterans watch carefully, knowing a monster has arrived.";
        arenaQuotes[4] = "A powerful aura spreads across the arena.";
    }
    else if (selectedRank == 'X')
    {
        arenaQuotes[0] = "The arena gates open to reveal a near-mythical contender.";
        arenaQuotes[1] = "The crowd can barely believe what stands before them.";
        arenaQuotes[2] = "Every battle fought until now has led to this moment.";
        arenaQuotes[3] = "A terrifying presence fills every corner of the arena.";
        arenaQuotes[4] = "Even champions hesitate before an SS-Class warrior.";
    }
    else if (selectedRank == 'Z')
    {
        arenaQuotes[0] = "The atmosphere itself feels distorted by the fighter's presence.";
        arenaQuotes[1] = "Legends speak of warriors who reached this level.";
        arenaQuotes[2] = "The arena falls completely silent before the final challenge.";
        arenaQuotes[3] = "An apex predator stands before you, unmatched and undefeated.";
        arenaQuotes[4] = "This is no longer a battle. This is a test of survival.";
    }
    else
    {
        arenaQuotes[0] = "The arena grows quiet.";
        arenaQuotes[1] = "A challenger enters the battlefield.";
        arenaQuotes[2] = "The next match is about to begin.";
        arenaQuotes[3] = "The crowd waits for the first move.";
        arenaQuotes[4] = "Another opponent steps forward.";
    }

    typeArenaTextCentered(arenaQuotes[rand() % 5], 20);

    printBlankLine();
    printCenteredFormat("%s entered the arena!", enemy->name);

    waitForEnter();
}
