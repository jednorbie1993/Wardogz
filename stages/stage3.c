#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage3.h"
#include "../battle.h"
#include "../dog.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "../enemies/enemy_stage3.h"
#include "../replay_system.h"
#include "../console.h"

int getZoneMax(int zoneIndex)
{
    if (zoneIndex == 8) return 2;   // Military Outpost
    if (zoneIndex == 9 || zoneIndex == 10) return 4;  // Training/Sniper
    if (zoneIndex == 11) return 3;  // Commander Base
    return 2; // default
}

void runStage3(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

        printBorder();
        printBlankLine();
        printCentered("STAGE 3: MILITARY ZONE");
        printBlankLine();

        printMenuItemFormat(1, "Military Outpost (%d/2)", progress[8]);

        if (progress[8] >= 2)
            printMenuItemFormat(2, "Tactical Training Grounds (%d/4)", progress[9]);
        else
            printMenuItem(2, "Tactical Training Grounds (LOCKED)");

        if (progress[9] >= 4)
            printMenuItemFormat(3, "Sniper Valley (%d/4)", progress[10]);
        else
            printMenuItem(3, "Sniper Valley (LOCKED)");

        if (progress[10] >= 4)
            printMenuItemFormat(4, "Commander Base (%d/3)", progress[11]);
        else
            printMenuItem(4, "Commander Base (LOCKED)");

        printMenuItem(5, "Back");
        printBlankLine();
        printf("%35sChoice: ", "");

        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printCentered("Please select a number.");
            waitForEnter();
            continue;
        }

        zoneChoice = atoi(input);

        if (zoneChoice < 1 || zoneChoice > 5)
        {
            printCentered("Invalid choice! Select 1-5 only.");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 5)
            return;

        // =========================
        // ZONE INDEX MAPPING
        // =========================
        int zoneIndex;
        if (zoneChoice == 1) zoneIndex = 8;
        else if (zoneChoice == 2) zoneIndex = 9;
        else if (zoneChoice == 3) zoneIndex = 10;
        else if (zoneChoice == 4) zoneIndex = 11;
        else continue;

        // =========================
        // LOCK CHECKS
        // =========================
        if (zoneChoice == 2 && progress[8] < 2)
        {
            printCentered("Complete Military Outpost first!");
            waitForEnter();
            continue;
        }
        if (zoneChoice == 3 && progress[9] < 4)
        {
            printCentered("Complete Tactical Training Grounds first!");
            waitForEnter();
            continue;
        }
        if (zoneChoice == 4 && progress[10] < 4)
        {
            printCentered("Complete Sniper Valley first!");
            waitForEnter();
            continue;
        }

        // =========================
        // CREATE ENEMY
        // =========================
        Dog enemy;
        createEnemy(&enemy);
        enemy.zoneType = ZONE_MILITARY;

        int i;
        int zoneMax = getZoneMax(zoneIndex);

        // =========================
        // REPLAY MODE (SIMPLE & SAFE)
        // =========================
        if (progress[zoneIndex] >= zoneMax)
        {
            /*printf("\n[MILITARY INTEL]: Training data acquired...\n");
            
            int enemyType = rand() % zoneMax;
            Dog tempEnemy;
            createEnemy(&tempEnemy);
            loadStage3Enemies(&tempEnemy, zoneIndex, enemyType);
            
            printf("%s patrol pattern recorded!\n", tempEnemy.name);
            if (systemLog)
                printf(" (REPLAY MODE)\n");
            
            waitForEnter();*/
            
            i = chooseReplayEnemyIndex(zoneIndex, progress, 0);
        }
        else
        {
            i = progress[zoneIndex];
        }

        // =========================
        // ENEMY SETUP
        // =========================
        loadStage3Enemies(&enemy, zoneIndex, i);

        // =========================
        // BOSS FIGHT (Last enemy)
        // =========================
        if (i == zoneMax - 1)
        {
            printBlankLine();
            printCentered("*** ELITE MILITARY DOGZ BOSS DETECTED! ***");

            enemy.attack += 15;
            enemy.defense += 12;
            enemy.speed += 8;
            enemy.maxHP += 60;
            enemy.hp = enemy.maxHP;
        }

        // =========================
        // INTRO
        // =========================
        /*printf("\nENGAGING: %s\n", enemy.name);
        waitForEnter();*/

        // =========================
        // PLAYER CHECK
        // =========================
        if (player->hp <= 0)
        {
            system("cls");
            printCentered("Recover HP before engaging Military Dogz!");
            waitForEnter();
            continue;
        }

        // =========================
        // FINAL BOSS INTRO
        // =========================
        /*if (zoneIndex == 11 && i == 2)
        {
            system("cls");
            typeText("ALERT: COMMANDER DOGZ DEPLOYED\n", 30);
            typeText("Military Dogz Commander: \"Discipline will crush chaos!\"\n\n", 28);
            waitForEnter();
        }*/

        // =========================
        // BATTLE
        // =========================
        int result = battleWithEnemyIndex(player, zoneIndex, progress, i);

        if (result == 0)
            continue;

        // =========================
        // VICTORY PROGRESS
        // =========================
        if (result == 1)
        {
            if (progress[zoneIndex] < zoneMax)
            {
                //progress[zoneIndex]++;
                printCenteredFormat("Zone Progress: %d/%d", progress[zoneIndex], zoneMax);
                waitForEnter();
            }
        }

        // =========================
        // DEFEAT MESSAGE / SURRENDER
        // =========================
        if (result == 2)
        {
            system("cls");

            char *defeatMsg[] =
            {
                "Military Dogz tactics too strong...",
                "Their formation overwhelmed me...",
                "Need better strategy against elites...",
                "Commander Dogz precision is deadly..."
            };

            int msg = rand() % 4;
            printCentered(defeatMsg[msg]);
            waitForEnter();
        }
    }
}
