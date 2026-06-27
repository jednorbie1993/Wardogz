#include "sparring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../dog.h"
#include "../cinematic.h"
#include "../battle.h"
#include "characters/ossas.h"
#include "characters/chubby.h"
#include "characters/snoop.h"
#include "characters/tiny.h"
#include "characters/jeward.h"
#include "sparring_unlocks.h"
#include "sparring_ai.h"
#include "sparring_skills.h"
#include "sparring_system.h"
#include "sparring_status.h"


void createSparPlayer(Dog *orig, Dog *spar)
{
    // copy basic info (name, etc.)
    strcpy(spar->name, orig->name);

    spar->maxHP = orig->maxHP;
    spar->hp = spar->maxHP;

    spar->attack = orig->attack;
    spar->defense = orig->defense;
    spar->speed = orig->speed;
    spar->accuracy = orig->accuracy;
    spar->intelligence = orig->intelligence;

    spar->isStunned = 0;
    spar->stunTurns = 0;
    spar->isBleeding = 0;
    spar->bleedTurns = 0;
    spar->isConfused = 0;
    spar->confuseTurns = 0;

    spar->skillCount = orig->skillCount;
    for (int i = 0; i < spar->skillCount; i++)
    {
        spar->skills[i] = orig->skills[i];
    }
}

void assignSkills(Dog *d, int type)
{

    if (type == 1)
    {
        createOssas(d);
        assignOssasSkills(d);
    }
    else if (type == 2)
    {
        createChubby(d);
        assignChubbySkills(d);
    }
    else if (type == 3)
    {
        createJeward(d);
        assignJewardSkills(d);
    }
    else if (type == 4)
    {
        createTiny(d);
        assignTinySkills(d);
    }
    else if (type == 5)
    {
        createSnoopy(d);
        assignSnoopySkills(d);
    }
}

void showSparringIntro(Dog *enemy, int type)
{
    printf("\n=================================\n");
    printf("SPARRING START: %s\n", enemy->name);
    printf("=================================\n\n");

    if (type == 1)
        printf("%s appears! Aggressive attacker!\n", enemy->name);
    else if (type == 2)
        printf("%s appears! Defensive tank!\n", enemy->name);
    else if (type == 3)
        printf("%s appears! Precision striker!\n", enemy->name);
    else if (type == 4)
        printf("%s appears! Smart strategist!\n", enemy->name);
    else if (type == 5)
        printf("%s appears! Speed demon!\n", enemy->name);
    else if (type == 6)
        printf("%s appears! Your lifelong rival!\n", enemy->name);

    pauseAndClear();
}

int sparringBattle(Dog *player, int type)
{
    Dog enemy = {0};
    Dog sparPlayer = {0};

    createSparPlayer(player, &sparPlayer); // FAIR STATS
    if (type == 1)
    {
        createOssas(&enemy);
        assignOssasSkills(&enemy);

    }
    else if (type == 2)
    {
        createChubby(&enemy);
        assignChubbySkills(&enemy);

    }
    else if (type == 3)
    {
        createJeward(&enemy);
        assignJewardSkills(&enemy);

    }
    else if (type == 4)
    {
        createTiny(&enemy);
        assignTinySkills(&enemy);

    }
    else if (type == 5)
    {
        createSnoopy(&enemy);
        assignSnoopySkills(&enemy);

    }
    else if (type == 6)
    {
        createSparPlayer(player, &enemy);

        if (player->dogType == 1)
        {
            strcpy(enemy.name, "Kane");
            enemy.speed += 25;
            enemy.accuracy += 20;

            printf("Kane: Let's see how much faster you've become.\n");
        }
        else
        {
            strcpy(enemy.name, "Jamber");
            enemy.attack += 25;
            enemy.maxHP += 30;
            enemy.hp = enemy.maxHP;

            printf("Jamber: Show me your strength. Don't hold back!\n");
        }
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
                printf("%s recovered accuracy!\n", enemy.name);
            }
        }
        if (sparPlayer.accDebuffTurns > 0)
        {
            sparPlayer.accDebuffTurns--;
            if (sparPlayer.accDebuffTurns == 0)
            {
                sparPlayer.accTemp = sparPlayer.accuracy;
                printf("You recovered accuracy!\n");
            }
        }

        updateCooldowns(&sparPlayer);
        updateCooldowns(&enemy);

        printSparringStatus(&sparPlayer, &enemy);

        // CHECK PLAYER STUN
        if (sparPlayer.isStunned && sparPlayer.stunTurns > 0)
        {
            printf("YOU ARE STUNNED! Turn skipped!\n");
            sparPlayer.stunTurns--;
            if (sparPlayer.stunTurns == 0)
                sparPlayer.isStunned = 0;
        }
        else
        {
            printf("Choose Move:\n");
            printf("1. Bite\n");
            printf("2. Scratch\n");
            printf("3. Charge\n");
            printf("4. Hip Check\n");

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
                    printf("Invalid move!\n");
                    pauseAndClear();
                    continue;
            }

            // ================= PLAYER TURN =================
            printf("\n--- PLAYER TURN ---\n");

            useSkill(&sparPlayer, &enemy, tempSkill);

            int fatigueCost = 3 + rand() % 6;   // random 3–8

            player->fatigue = clampFatigue(
                player->fatigue - fatigueCost,
                player->maxFatigue
            );

            sparPlayer.fatigue = player->fatigue;

            //printf("Fatigue -%d\n", fatigueCost);

            printf("\nPress Enter to continue...");
            getchar();
            system("cls");

            printSparringStatus(&sparPlayer, &enemy);
        }

        if (enemy.hp <= 0)
            break;

        // ================= ENEMY TURN =================
        if (enemy.isStunned && enemy.stunTurns > 0)
        {
            printf("\n--- ENEMY TURN ---\n");
            printf("%s is STUNNED! Enemy turn skipped!\n", enemy.name);
            enemy.stunTurns--;
            if (enemy.stunTurns == 0)
                enemy.isStunned = 0;
        }
        else
        {
            int enemyMove = chooseEnemyMove(&enemy, &sparPlayer, type);
            printf("\n--- ENEMY TURN ---\n");
            useSkill(&enemy, &sparPlayer, enemy.skills[enemyMove]);
        }

        if (sparPlayer.hp <= 0)
            break;

        // PAUSE BETWEEN TURNS
        printf("\nPress Enter to continue...");
        getchar();
        system("cls");
    }

    // HP CHECK
    printf("\n=== BATTLE END ===\n");
    if (sparPlayer.hp > 0 && enemy.hp <= 0)
    {
        printf("YOU WIN SPARRING!\n");

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
        printf("YOU LOST SPARRING...\n");

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
