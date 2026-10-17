#include "sparring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../console.h"
#include "../stat.h"
#include "../skill.h"

#include "characters/ossas.h"
#include "characters/chubby.h"
#include "characters/jeward.h"
#include "characters/tiny.h"
#include "characters/snoop.h"

#include "sparring_ai.h"
#include "sparring_skills.h"
#include "sparring_status.h"
#include "sparring_system.h"

static void copySparringBaseStats(const Dog *orig, Dog *dest)
{
    strcpy(dest->name, orig->name);

    dest->maxHP = orig->maxHP;
    dest->hp = dest->maxHP;

    dest->attack = orig->attack;
    dest->defense = orig->defense;
    dest->speed = orig->speed;
    dest->accuracy = orig->accuracy;
    dest->intelligence = orig->intelligence;

    dest->isStunned = 0;
    dest->stunTurns = 0;
    dest->isBleeding = 0;
    dest->bleedTurns = 0;
    dest->isConfused = 0;
    dest->confuseTurns = 0;
}

static void createSparPlayer(Dog *orig, Dog *spar)
{
    copySparringBaseStats(orig, spar);

    spar->skillCount = orig->skillCount;
    for (int i = 0; i < spar->skillCount; i++)
    {
        spar->skills[i] = orig->skills[i];
    }
}

static void createRival(Dog *orig, Dog *rival)
{
    copySparringBaseStats(orig, rival);

    // Rival skills are assigned later in sparringBattle().
    rival->skillCount = 0;
}

static void showSparringIntro(Dog *enemy, int type)
{
    printBorder();
    printBlankLine();
    printCenteredFormat("SPARRING START: %s", enemy->name);
    printBlankLine();

    if (type == 1)
        printCenteredFormat("%s appears! Aggressive attacker!", enemy->name);
    else if (type == 2)
        printCenteredFormat("%s appears! Defensive tank!", enemy->name);
    else if (type == 3)
        printCenteredFormat("%s appears! Precision striker!", enemy->name);
    else if (type == 4)
        printCenteredFormat("%s appears! Smart strategist!", enemy->name);
    else if (type == 5)
        printCenteredFormat("%s appears! Speed demon!", enemy->name);
    else if (type == 6)
        printCenteredFormat("%s appears! Your lifelong rival!", enemy->name);

    pauseAndClear();
}

int sparringBattle(Dog *player, int type)
{
    Dog enemy = {0};
    Dog sparPlayer = {0};

    createSparPlayer(player, &sparPlayer); // FAIR STATS

    switch (type)
    {
        case 1:
            createOssas(&enemy);
            assignOssasSkills(&enemy);
            break;

        case 2:
            createChubby(&enemy);
            assignChubbySkills(&enemy);
            break;

        case 3:
            createJeward(&enemy);
            assignJewardSkills(&enemy);
            break;

        case 4:
            createTiny(&enemy);
            assignTinySkills(&enemy);
            break;

        case 5:
            createSnoopy(&enemy);
            assignSnoopySkills(&enemy);
            break;

        case 6:
            createRival(player, &enemy);

            enemy.skillCount = 6;

            if (player->dogType == 1)
                strcpy(enemy.name, "Kane");
            else
                strcpy(enemy.name, "Jamber");

            // Optional stat bonus
            enemy.attack += 25;
            enemy.defense += 25;
            enemy.speed += 25;
            enemy.accuracy += 25;
            enemy.intelligence += 25;

            enemy.hp = enemy.maxHP;

            // Fixed Rival Skills
            enemy.skills[0] = createBiteSkill();
            enemy.skills[1] = createScratchSkill();
            enemy.skills[2] = createChargeSkill();
            enemy.skills[3] = createHipCheckSkill();
            enemy.skills[4] = createPowerRushSkill();
            enemy.skills[5] = createGuardBreakSkill();

            printCenteredFormat("%s: Let's see how much you've improved.", enemy.name);
            break;
    }

    int bonus = 0;

    // Normal sparring partners only use progress scaling.
    // Rival Match has progress, but no +30 scaling bonus.
    if (type >= 1 && type <= 5)
        bonus = player->sparringProgress[type - 1] * 30;

    enemy.hp = enemy.maxHP;
    enemy.maxHP += bonus;
    enemy.attack += bonus;
    enemy.defense += bonus;
    enemy.speed += bonus;
    enemy.accuracy += bonus;
    enemy.intelligence += bonus;

    sparPlayer.hp = sparPlayer.maxHP;
    enemy.hp = enemy.maxHP;

    system("cls");
    showSparringIntro(&enemy, type);

    while (sparPlayer.hp > 0 && enemy.hp > 0)
    {
        // UPDATE DEBUFFS FIRST
        if (enemy.accDebuffTurns > 0)
        {
            enemy.accDebuffTurns--;
            if (enemy.accDebuffTurns == 0)
            {
                enemy.accTemp = enemy.accuracy;
                printCenteredFormat("%s recovered accuracy!", enemy.name);
            }
        }
        if (sparPlayer.accDebuffTurns > 0)
        {
            sparPlayer.accDebuffTurns--;
            if (sparPlayer.accDebuffTurns == 0)
            {
                sparPlayer.accTemp = sparPlayer.accuracy;
                printCentered("You recovered accuracy!");
            }
        }

        updateCooldowns(&sparPlayer);
        updateCooldowns(&enemy);

        printSparringStatus(&sparPlayer, &enemy);

        // CHECK PLAYER STUN
        if (sparPlayer.isStunned && sparPlayer.stunTurns > 0)
        {
            printCentered("YOU ARE STUNNED! Turn skipped!");
            sparPlayer.stunTurns--;
            if (sparPlayer.stunTurns == 0)
                sparPlayer.isStunned = 0;
        }
        else
        {
            printBlankLine();
            printCentered("CHOOSE MOVE");
            printBlankLine();
            printMenuItem(1, "Bite");
            printMenuItem(2, "Scratch");
            printMenuItem(3, "Charge");
            printMenuItem(4, "Hip Check");
            printBlankLine();
            printf("%35sChoice: ", "");

            int choice;
            char moveInput[10];
            fgets(moveInput, sizeof(moveInput), stdin);
            choice = atoi(moveInput);

            Skill tempSkill;

            switch (choice)
            {
                case 1:
                    tempSkill = createBiteSkill();
                    break;

                case 2:
                    tempSkill = createScratchSkill();
                    break;

                case 3:
                    tempSkill = createChargeSkill();
                    break;

                case 4:
                    tempSkill = createHipCheckSkill();
                    break;

                default:
                    printCentered("Invalid move!");
                    pauseAndClear();
                    continue;
            }

            // ================= PLAYER TURN =================
            system("cls");
            printSparringStatus(&sparPlayer, &enemy);

            printBlankLine();
            printCentered("--- PLAYER TURN ---");

            useSkill(&sparPlayer, &enemy, tempSkill);

            int fatigueCost = 3 + rand() % 6;   // random 3–8

            player->fatigue = clampFatigue(
                player->fatigue - fatigueCost,
                player->maxFatigue
            );

            sparPlayer.fatigue = player->fatigue;

            //printf("Fatigue -%d\n", fatigueCost);

            waitForEnter();
            system("cls");

            printSparringStatus(&sparPlayer, &enemy);
        }

        if (enemy.hp <= 0)
            break;

        // ================= ENEMY TURN =================
        if (enemy.isStunned && enemy.stunTurns > 0)
        {
            printBlankLine();
            printCentered("--- ENEMY TURN ---");
            printCenteredFormat("%s is STUNNED! Enemy turn skipped!", enemy.name);
            enemy.stunTurns--;
            if (enemy.stunTurns == 0)
                enemy.isStunned = 0;
        }
        else
        {
            int enemyMove = chooseEnemyMove(&enemy, &sparPlayer, type);
            printBlankLine();
            printCentered("--- ENEMY TURN ---");
            useSkill(&enemy, &sparPlayer, enemy.skills[enemyMove]);
        }

        if (sparPlayer.hp <= 0)
            break;

        // PAUSE BETWEEN TURNS
        waitForEnter();
        system("cls");
    }

    // HP CHECK
    printBlankLine();
    printCentered("=== BATTLE END ===");
    if (sparPlayer.hp > 0 && enemy.hp <= 0)
    {
        printCentered("YOU WIN SPARRING!");

        // SPARRING PROGRESS SYSTEM
        // Type 1-5 = normal partners, Type 6 = Rival Match.
        if (type >= 1 && type <= 6)
        {
            int enemyIndex = type - 1;
            updateSparringProgress(player, enemyIndex, 1); // WIN = +1 progress
        }

        applySparReward(player, type);
        return 1; // WIN
    }
    else
    {
        printCentered("YOU LOST SPARRING...");

        if (type >= 1 && type <= 6)
        {
            int enemyIndex = type - 1;
            updateSparringProgress(player, enemyIndex, 0); // LOSE
        }
        else
        {
            waitForEnter();
        }

        return 0;
    }
}
