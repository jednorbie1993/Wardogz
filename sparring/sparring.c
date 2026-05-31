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


void createSparPlayer(Dog *orig, Dog *spar)
{
    // copy basic info (name, etc.)
    strcpy(spar->name, orig->name);

    spar->maxHP = 100;
    spar->hp = 100;

    spar->attack = 900;
    spar->defense = 100;
    spar->speed = 100;
    spar->accuracy = 100;
    spar->intelligence = 100;

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

// UPDATE DEBUFFS
void updateDebuffs(Dog *d)
{
    // DEBUFF TIMER
    if (d->accDebuffTurns > 0)
    {
        d->accDebuffTurns--;
        if (d->accDebuffTurns == 0)
        {
            d->accTemp = d->accuracy;
            printf("%s recovered from daze/stun!\n", d->name);
        }
    }

    // STUN TIMER
    if (d->isStunned && d->stunTurns > 0)
    {
        d->stunTurns--;
        if (d->stunTurns == 0)
        {
            d->isStunned = 0;
            printf("%s recovered from stun!\n", d->name);
        }
    }
}

int sparringBattle(Dog *player, int type)
{
    Dog enemy;
    Dog sparPlayer;

    createSparPlayer(player, &sparPlayer); // FAIR STATS
    if (type == 1)
    {
        createOssas(&enemy);
        assignOssasSkills(&enemy);

        printf("Ossas appears! Aggressive attacker!\n");
    }
    else if (type == 2)
    {
        createChubby(&enemy);
        assignChubbySkills(&enemy);

        printf("Chubby appears! Defensive tank!\n");
    }
    else if (type == 3)
    {
        createJeward(&enemy);
        assignJewardSkills(&enemy);

        printf("Jeward appears! Precision striker!\n");
    }
    else if (type == 4)
    {
        createTiny(&enemy);
        assignTinySkills(&enemy);

        printf("Tiny appears! Smart strategist!\n");
    }
    else if (type == 5)
    {
        createSnoopy(&enemy);
        assignSnoopySkills(&enemy);

        printf("Snoopy appears! Speed demon!\n");
    }

    pauseAndClear();

    sparPlayer.hp = sparPlayer.maxHP;
    enemy.hp = enemy.maxHP;

    printf("\n SPARRING START: %s\n\n", enemy.name);
    pauseAndClear();

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

        // STATUS WITH DEBUFFS
        printf("YOU: [%d/%d]", sparPlayer.hp, sparPlayer.maxHP);
        if (sparPlayer.accDebuffTurns > 0)
            printf(" (DAZED %d)", sparPlayer.accDebuffTurns);
        if (sparPlayer.isStunned && sparPlayer.stunTurns > 0)
            printf(" (STUN %d)", sparPlayer.stunTurns);
        printf("\n");

        printf("ENEMY: [%d/%d]", enemy.hp, enemy.maxHP);
        if (enemy.accDebuffTurns > 0)
            printf(" (DAZED %d)", enemy.accDebuffTurns);
        if (enemy.isStunned && enemy.stunTurns > 0)
            printf(" (STUN %d)", enemy.stunTurns);
        printf("\n\n");

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
            printf("\nChoose Move:\n");
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
                    continue;
            }

            // ================= PLAYER TURN =================
            printf("\n--- PLAYER TURN ---\n");
            useSkill(&sparPlayer, &enemy, tempSkill);
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
        int enemyIndex = type - 1; // 1 = Ossas, 2 = Chubby, etc.
        updateSparringProgress(player, enemyIndex, 1); // WIN = +1 progress

        applySparReward(player, type);
        return 1; // WIN
    }
    else
    {
        printf("YOU LOST SPARRING...\n");
        int enemyIndex = type - 1;
        updateSparringProgress(player, enemyIndex, 0); // LOSE
        return 0;
    }
}
