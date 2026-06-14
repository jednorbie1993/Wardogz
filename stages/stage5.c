#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage5.h"
#include "../battle.h"
#include "../dog.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "../enemies/enemy_stage5.h"
#include "../replay_system.h"

int getZoneMaxStage5(int zoneIndex)
{
    if (zoneIndex == 16) return 4;
    if (zoneIndex == 17) return 4;
    if (zoneIndex == 18) return 4;
    if (zoneIndex == 19) return 4;

    return 4;
}

void runStage5(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

        printf("====================================\n");
        printf("  STAGE 5: BLACKSITE LABORATORY\n");
        printf("====================================\n\n");

        printf("1. Enhanced Strays (%d/4)\n", progress[16]);

        if (progress[16] >= 4)
            printf("2. Feral Mutation Ward (%d/4)\n", progress[17]);
        else
            printf("2. Feral Mutation Ward (Locked)\n");

        if (progress[17] >= 4)
            printf("3. Combat Prototype Unit (%d/4)\n", progress[18]);
        else
            printf("3. Combat Prototype Unit (Locked)\n");

        if (progress[18] >= 4)
            printf("4. Elemental Apex Chamber (%d/4)\n", progress[19]);
        else
            printf("4. Elemental Apex Chamber (Locked)\n");

        printf("5. Back");
        printf("\n\nChoice: ");

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

        if (zoneChoice == 2 && progress[16] < 4)
        {
            printf("\nComplete Enhanced Strays first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 3 && progress[17] < 4)
        {
            printf("\nComplete Feral Mutation Ward first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 4 && progress[18] < 4)
        {
            printf("\nComplete Combat Prototype Unit first!");
            waitForEnter();
            continue;
        }

        int zoneIndex;

        if (zoneChoice == 1)
            zoneIndex = 16;
        else if (zoneChoice == 2)
            zoneIndex = 17;
        else if (zoneChoice == 3)
            zoneIndex = 18;
        else
            zoneIndex = 19;

        int zoneMax = getZoneMaxStage5(zoneIndex);

        // FIRST TIME INTRO ONLY - Zone 1
        if (zoneIndex == 16 && progress[16] == 0)
        {
            system("cls");
            typeText("[RESEARCH LOG - DR. BRICKY]\n\n", 25);

            typeText("\"At last... years of research, countless failures, and endless sacrifices have finally paid off.\"\n\n", 25);
            typeText("\"The Stray Enhancement Project is complete.\"\n\n", 25);
            typeText("\"What the world calls ordinary dogs... I see as untapped potential.\"\n\n", 25);
            typeText("\"Strength. Intelligence. Adaptation.\"\n\n", 25);
            typeText("\"Humanity has spent centuries trying to create the perfect soldier.\"\n\n", 25);
            typeText("\"They were looking in the wrong species.\"\n\n", 25);
            typeText("\"These subjects are no longer strays.\"\n\n", 25);
            typeText("\"They are the future.\"\n\n", 25);
            typeText("\"And soon... the entire world will witness my masterpiece.\"\n\n", 25);

            typeText("- Dr. Bricky\n", 25);
            waitForEnter();
        }
        // FIRST TIME INTRO ONLY - Zone 3
        else if (zoneIndex == 18 && progress[18] == 0)
        {
            system("cls");
            typeText("[BLACKSITE SECURITY LOG]\n\n", 25);
            typeText("The deeper wing of the laboratory opens.\n", 25);
            typeText("These subjects are different... trained, disciplined, and weaponized.\n", 25);
            typeText("They do not hunt like animals.\n", 25);
            typeText("They move like soldiers.\n\n", 25);
            typeText("Security System: Combat Prototype Unit activated.\n", 25);
            waitForEnter();
        }
        // FIRST TIME INTRO ONLY - Zone 4
        else if (zoneIndex == 19 && progress[19] == 0)
        {
            system("cls");
            typeText("[BLACKSITE CORE LOG]\n\n", 25);
            typeText("Elemental reactor pressure rising...\n", 25);
            typeText("Cryo, plasma, and thunder energy detected inside the chamber.\n", 25);
            typeText("These subjects are not simple mutations anymore.\n", 25);
            typeText("Their bodies are adapting to unstable elemental power.\n\n", 25);
            typeText("Security System: Elemental Apex Chamber unlocked.\n", 25);
            waitForEnter();
        }
        // REPLAY INTRO ONLY
        else if (progress[zoneIndex] >= zoneMax)
        {
            system("cls");

            if (zoneIndex == 18)
            {
                if (rand() % 2 == 0)
                {
                    typeText("Combat prototypes return to their patrol routes...\n", 25);
                    typeText("Their training never stops.\n", 25);
                }
                else
                {
                    typeText("The tactical ward resets its combat simulation...\n", 25);
                    typeText("Another prototype steps forward.\n", 25);
                }
            }
            else if (zoneIndex == 19)
            {
                if (rand() % 2 == 0)
                {
                    typeText("The Elemental Apex Chamber reactivates...\n", 25);
                    typeText("Unstable energy gathers around another subject.\n", 25);
                }
                else
                {
                    typeText("The core refuses to shut down...\n", 25);
                    typeText("A new elemental mutation awakens.\n", 25);
                }
            }
            else
            {
                if (rand() % 2 == 0)
                {
                    typeText("The laboratory remains active...\n", 25);
                    typeText("Enhanced subjects continue their patrols.\n", 25);
                }
                else
                {
                    typeText("The Blacksite grows quieter...\n", 25);
                    typeText("But the experiments are far from over.\n", 25);
                }
            }

            waitForEnter();
        }

        Dog enemy;
        createEnemy(&enemy);
        enemy.zoneType = ZONE_MUTANT;

        int i;

        if (progress[zoneIndex] >= zoneMax)
        {
            i = chooseReplayEnemyIndex(zoneIndex, progress, 0);
        }
        else
        {
            i = progress[zoneIndex];
        }

        loadStage5Enemies(&enemy, zoneIndex, i);

        if (i == zoneMax - 1)
        {
            enemy.attack += 20;
            enemy.defense += 16;
            enemy.speed += 12;
            enemy.maxHP += 90;
            enemy.hp = enemy.maxHP;
        }

        if (player->hp <= 0)
        {
            system("cls");
            typeText("Recover HP before entering the Blacksite Laboratory!\n", 25);
            waitForEnter();
            continue;
        }

        // ZONE 1 BOSS INTRO
        if (zoneIndex == 16 && i == 3)
        {
            system("cls");
            typeText("Dr. Bricky: So you made it this far...\n", 25);
            typeText("Dr. Bricky: Impressive.\n", 25);
            typeText("Dr. Bricky: Allow me to introduce my masterpiece.\n", 25);
            typeText("Dr. Bricky: Alpha-X... awaken.\n\n", 25);

            typeText("Alpha-X steps out of the containment chamber.\n", 25);
            typeText("Its eyes lock onto you.\n", 25);

            waitForEnter();
        }
        // ZONE 2 BOSS INTRO
        else if (zoneIndex == 17 && i == 3)
        {
            system("cls");

            typeText("Warning...\n", 25);
            typeText("Containment breach detected.\n", 25);
            typeText("Subject LYCAN-REX released.\n\n", 25);

            typeText("A massive werewolf-like beast emerges from the darkness.\n", 25);

            waitForEnter();
        }
        // ZONE 3 BOSS INTRO
        else if (zoneIndex == 18 && i == 3)
        {
            system("cls");

            typeText("Security System: Final prototype authorized.\n", 25);
            typeText("Blacksite doors lock behind you.\n\n", 25);
            typeText("A heavily trained combat subject steps forward.\n", 25);
            typeText("Its armor is scarred from countless test battles.\n", 25);
            typeText("Dr. Bricky: This one does not need rage.\n", 25);
            typeText("Dr. Bricky: It was built to end fights quickly.\n", 25);

            waitForEnter();
        }
        // ZONE 4 BOSS INTRO
        else if (zoneIndex == 19 && i == 3)
        {
            system("cls");

            typeText("Warning: Core stability failing.\n", 25);
            typeText("Elemental pressure has exceeded safe limits.\n\n", 25);
            typeText("The chamber doors open slowly.\n", 25);
            typeText("Apex-0 steps forward, surrounded by unstable energy.\n", 25);
            typeText("Dr. Bricky: This is not training anymore.\n", 25);
            typeText("Dr. Bricky: This is evolution under pressure.\n", 25);

            waitForEnter();
        }

        int result = battleWithEnemyIndex(player, zoneIndex, progress, i);

        if (result == 0)
            continue;

        if (result == 1)
        {
            if (zoneIndex == 16 && progress[16] < zoneMax)
            {
                printf("\n[DATA LOG]: Enhanced stray contained.");
                printf("\nZone Progress: %d/%d\n", progress[16], zoneMax);
                waitForEnter();
            }
            else if (zoneIndex == 17 && progress[17] < zoneMax)
            {
                printf("\n[DATA LOG]: Feral mutation contained.");
                printf("\nZone Progress: %d/%d\n", progress[17], zoneMax);
                waitForEnter();
            }
            else if (zoneIndex == 18 && progress[18] < zoneMax)
            {
                printf("\n[DATA LOG]: Combat prototype neutralized.");
                printf("\nZone Progress: %d/%d\n", progress[18], zoneMax);
                waitForEnter();
            }
            else if (zoneIndex == 19 && progress[19] < zoneMax)
            {
                printf("\n[DATA LOG]: Elemental apex subject stabilized.");
                printf("\nZone Progress: %d/%d\n", progress[19], zoneMax);
                waitForEnter();
            }

            if (zoneIndex == 16 && progress[16] >= 4)
            {
                system("cls");
                typeText("ZONE 1: ENHANCED STRAYS COMPLETE\n\n", 20);
                typeText("If the old Back Alley strays became this strong...\n", 28);
                typeText("what else is waiting deeper inside the laboratory?\n", 28);
                waitForEnter();
            }

            if (zoneIndex == 17 && progress[17] >= 4)
            {
                system("cls");
                typeText("ZONE 2: FERAL MUTATION WARD COMPLETE\n\n", 20);
                typeText("These were no longer ordinary strays...\n", 28);
                typeText("their instincts had evolved into something savage.\n", 28);
                waitForEnter();
            }

            if (zoneIndex == 18 && progress[18] >= 4)
            {
                system("cls");
                typeText("ZONE 3: COMBAT PROTOTYPE UNIT COMPLETE\n\n", 20);
                typeText("These subjects were not wild anymore...\n", 28);
                typeText("they were trained like weapons inside the Blacksite.\n", 28);
                waitForEnter();
            }

            if (zoneIndex == 19 && progress[19] >= 4)
            {
                system("cls");
                typeText("ZONE 4: ELEMENTAL APEX CHAMBER COMPLETE\n\n", 20);
                typeText("The Blacksite core begins to cool down...\n", 28);
                typeText("but the energy left behind still feels alive.\n", 28);
                waitForEnter();
            }
        }

        if (result == 2)
        {
            system("cls");

            char *defeatMsg[] =
            {
                "Subject overpowered the intruder...\n",
                "Enhanced combat instincts confirmed...\n",
                "Blacksite security remains active...\n",
                "Old strays are no longer ordinary enemies...\n",
                "The laboratory records another failed entry...\n",
                "Combat prototype efficiency confirmed...\n",
                "Tactical ward remains undefeated...\n",
                "Elemental pressure overwhelms the intruder...\n",
                "The Apex Chamber remains unstable...\n"
            };

            int msg = rand() % 9;
            typeText(defeatMsg[msg], 25);
            waitForEnter();
        }
    }
}