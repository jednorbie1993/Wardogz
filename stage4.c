#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage4.h"
#include "battle.h"
#include "dog.h"
#include "cinematic.h"
#include "enemies/enemy.h"
#include "enemies/enemy_stage4.h"

int getZoneMaxStage4(int zoneIndex)
{
    if (zoneIndex == 12) return 2;   // Outer Facility
    if (zoneIndex == 13) return 4;  // Research Hallways
    if (zoneIndex == 14) return 4;  // Containment Labs
    if (zoneIndex == 15) return 3; // Core Chamber
    return 2;
}

void runStage4(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

        printf("====================================\n");
        printf("  STAGE 4: BIO-CONTAINMENT ZONE\n");
        printf("====================================\n\n");

        printf("1. Outer Facility (%d/2)\n", progress[12]);
        
        if (progress[12] >= 2)
            printf("2. Research Hallways (%d/4)\n", progress[13]);
        else
            printf("2. Research Hallways (LOCKED)\n");

        if (progress[13] >= 4)
            printf("3. Containment Labs (%d/4)\n", progress[14]);
        else
            printf("3. Containment Labs (LOCKED)\n");

        if (progress[14] >= 4)
            printf("4. Core Chamber (%d/3)\n", progress[15]);
        else
            printf("4. Core Chamber (LOCKED)\n");

        printf("5. Back\n");
        printf("\nChoice: ");

        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printf("\nPlease select a number.");
            waitForEnter();
            continue;
        }

        zoneChoice = atoi(input);

        if (zoneChoice < 1 || zoneChoice > 5)
        {
            printf("\nInvalid choice! Select 1-5 only.");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 5)
            return;

        // =========================
        // ZONE INDEX MAPPING
        // =========================
        int zoneIndex;
        if (zoneChoice == 1) zoneIndex = 12;
        else if (zoneChoice == 2) zoneIndex = 13;
        else if (zoneChoice == 3) zoneIndex = 14;
        else if (zoneChoice == 4) zoneIndex = 15;
        else continue;

        // =========================
        // LOCK CHECKS
        // =========================
        if (zoneChoice == 2 && progress[12] < 2)
        {
            printf("\n[ACCESS DENIED] Complete Outer Facility first!");
            waitForEnter();
            continue;
        }
        if (zoneChoice == 3 && progress[13] < 4)
        {
            printf("\n[ACCESS DENIED] Complete Research Hallways first!");
            waitForEnter();
            continue;
        }
        if (zoneChoice == 4 && progress[14] < 4)
        {
            printf("\n[ACCESS DENIED] Complete Containment Labs first!");
            waitForEnter();
            continue;
        }

        // =========================
        // INTRO SCENE
        // =========================
        system("cls");
        if (zoneIndex == 12)
        {
            typeText("[BIO-LAB EXTERIOR]\n", 20);
            typeText("Warning: Unauthorized personnel detected.\n", 25);
        }
        else if (zoneIndex == 13)
        {
            typeText("[RESEARCH HALLWAY]\n", 20);
            typeText("Note: Subject tests in progress...\n", 25);
        }
        else if (zoneIndex == 14)
        {
            typeText("[CONTAINMENT LAB]\n", 20);
            typeText("WARNING: Containment breach imminent!\n", 28);
        }
        else if (zoneIndex == 15)
        {
            typeText("[CORE CHAMBER - RESTRICTED AREA]\n", 25);
            typeText("WARNING: MAXIMUM SECURITY ACTIVE!\n", 30);
        }
        waitForEnter();

        // =========================
        // CREATE ENEMY
        // =========================
        Dog enemy;
        createEnemy(&enemy);
        enemy.zoneType = ZONE_BIOLAB;

        int i;
        int zoneMax = getZoneMaxStage4(zoneIndex);

        // =========================
        // REPLAY MODE
        // =========================
        if (progress[zoneIndex] >= zoneMax)
        {
            printf("\n[DATA LOG]: Containment subject recorded...\n");
            
            int enemyType = rand() % zoneMax;
            Dog tempEnemy;
            createEnemy(&tempEnemy);
            loadStage4Enemies(&tempEnemy, zoneIndex, enemyType);
            
            printf("Subject %s detected!\n", tempEnemy.name);
            if (systemLog)
                printf(" (REPLAY MODE)\n");
            
            waitForEnter();
            
            i = (rand() % 100 < 20) ? (zoneMax) : (rand() % zoneMax);
        }
        else
        {
            i = progress[zoneIndex];
        }

        // =========================
        // ENEMY SETUP
        // =========================
        loadStage4Enemies(&enemy, zoneIndex, i);

        // =========================
        // BOSS BUFF (Last enemy)
        // =========================
        if (i == zoneMax - 1)
        {
            printf("\n*** CONTAINMENT SUBJECT DETECTED! ***\n");
            printf("*** SUBJECT SHOWS EXTREME AGGRESSION ***\n");
            enemy.attack += 18;
            enemy.defense += 14;
            enemy.speed += 10;
            enemy.maxHP += 80;
            enemy.hp = enemy.maxHP;
        }

        // =========================
        // FINAL INTRO
        // =========================
        printf("\nENGAGING: %s\n", enemy.name);
        printf("HP: %d | ATK: %d | DEF: %d | SPD: %d\n", 
               enemy.hp, enemy.attack, enemy.defense, enemy.speed);
        waitForEnter();

        // =========================
        // PLAYER CHECK
        // =========================
        if (player->hp <= 0)
        {
            system("cls");
            typeText("Recover HP before engaging bio-subjects!\n", 25);
            waitForEnter();
            continue;
        }

        // =========================
        // FINAL BOSS INTRO (Zone 15, last enemy)
        // =========================
        if (zoneIndex == 15 && i == 2)
        {
            system("cls");
            typeText("======================================\n", 15);
            typeText("   !!! PROTOYPE ZERO ACTIVATED !!!\n", 25);
            typeText("======================================\n\n", 15);
            typeText("Prototype Zero: \"I AM THE FUTURE OF K-9.\"\n", 25);
            typeText("You have witnessed too much.\n", 25);
            typeText("I will complete the program myself.\"\n\n", 28);
            waitForEnter();
        }

        // =========================
        // BATTLE
        // =========================
        int result = battle(player, zoneIndex, progress);

        if (result == 0)
            continue;

        // =========================
        // VICTORY PROGRESS
        // =========================
        if (result == 1)
        {
            if (progress[zoneIndex] < zoneMax)
            {
                progress[zoneIndex]++;
                printf("\n[DATA LOG]: Subject contained.");
                printf("\nZone Progress: %d/%d\n", progress[zoneIndex], zoneMax);
                waitForEnter();
            }
            
            // Stage 4 Complete
            if (zoneIndex == 15 && progress[15] >= 3)
            {
                system("cls");
                typeText("======================================\n", 15);
                typeText("   STAGE 4: BIO-CONTAINMENT COMPLETE\n", 20);
                typeText("======================================\n\n", 15);
                typeText("WARNING: Containment failure detected.\n", 28);
                typeText("Mutant samples have been stolen.\n", 28);
                typeText("The FINAL STAGE is now open.\n\n", 28);
                waitForEnter();
            }
        }

        // =========================
        // DEFEAT MESSAGE
        // =========================
        if (result == 2)
        {
            system("cls");
            char *defeatMsg[] = {
                "Subject escaped containment...\n",
                "Their hybrid strength is overwhelming...\n",
                "Need more firepower for these prototypes...\n",
                "The lab has taken another test subject...\n",
                "Project success rate increases...\n"
            };
            int msg = rand() % 5;
            typeText(defeatMsg[msg], 25);
            waitForEnter();
        }
    }
}