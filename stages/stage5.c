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
#include "../credit.h"
#include "../console.h"


static void typeTextCentered(const char *text, int delay)
{
    int len = strlen(text);
    int spaces = (CONSOLE_WIDTH - len) / 2;

    if (spaces < 0)
        spaces = 0;

    for (int i = 0; i < spaces; i++)
        printf(" ");

    typeText(text, delay);
}

static void typeTextCenteredLine(const char *text, int delay)
{
    typeTextCentered(text, delay);
    printf("\n");
}

static void typeTextCenteredBlank()
{
    printf("\n");
}

int getZoneMaxStage5(int zoneIndex)
{
    if (zoneIndex == 16) return 4;
    if (zoneIndex == 17) return 4;
    if (zoneIndex == 18) return 4;
    if (zoneIndex == 19) return 4;
    if (zoneIndex == 20) return 1; // FINAL ZONE: Project Cerberus

    return 4;
}

void showProjectCerberusEnding(Dog *player);

void runStage5(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

        printBorder();
        printBlankLine();
        printCentered("STAGE 5: BLACKSITE LABORATORY");
        printBlankLine();

        printMenuItemFormat(1, "Enhanced Strays (%d/4)", progress[16]);

        if (progress[16] >= 4)
            printMenuItemFormat(2, "Feral Mutation Ward (%d/4)", progress[17]);
        else
            printMenuItem(2, "Feral Mutation Ward (Locked)");

        if (progress[17] >= 4)
            printMenuItemFormat(3, "Combat Prototype Unit (%d/4)", progress[18]);
        else
            printMenuItem(3, "Combat Prototype Unit (Locked)");

        if (progress[18] >= 4)
            printMenuItemFormat(4, "Elemental Apex Chamber (%d/4)", progress[19]);
        else
            printMenuItem(4, "Elemental Apex Chamber (Locked)");

        if (progress[19] >= 4)
            printMenuItemFormat(5, "Final Containment: Project Cerberus (%d/1)", progress[20]);
        else
            printMenuItem(5, "Final Containment: Project Cerberus (Locked)");

        printMenuItem(6, "Back");
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

        if (zoneChoice < 1 || zoneChoice > 6)
        {
            printCentered("Invalid choice! Select 1-6 only.");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 6)
            return;

        if (zoneChoice == 2 && progress[16] < 4)
        {
            printCentered("Complete Enhanced Strays first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 3 && progress[17] < 4)
        {
            printCentered("Complete Feral Mutation Ward first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 4 && progress[18] < 4)
        {
            printCentered("Complete Combat Prototype Unit first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 5 && progress[19] < 4)
        {
            printCentered("Complete Elemental Apex Chamber first!");
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
        else if (zoneChoice == 4)
            zoneIndex = 19;
        else
            zoneIndex = 20;

        int zoneMax = getZoneMaxStage5(zoneIndex);

        // FIRST TIME INTRO ONLY - Zone 1
        if (zoneIndex == 16 && progress[16] == 0)
        {
            system("cls");
            typeTextCenteredLine("[RESEARCH LOG - DR. BRICKY]", 25);
            typeTextCenteredBlank();

            typeTextCenteredLine("\"At last... years of research, countless failures, and endless sacrifices have finally paid off.\"", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("\"The Stray Enhancement Project is complete.\"", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("\"What the world calls ordinary dogs... I see as untapped potential.\"", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("\"Strength. Intelligence. Adaptation.\"", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("\"Humanity has spent centuries trying to create the perfect soldier.\"", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("\"They were looking in the wrong species.\"", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("\"These subjects are no longer strays.\"", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("\"They are the future.\"", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("\"And soon... the entire world will witness my masterpiece.\"", 25);
            typeTextCenteredBlank();

            typeTextCenteredLine("- Dr. Bricky", 25);
            waitForEnter();
        }
        // FIRST TIME INTRO ONLY - Zone 3
        else if (zoneIndex == 18 && progress[18] == 0)
        {
            system("cls");
            typeTextCenteredLine("[BLACKSITE SECURITY LOG]", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("The deeper wing of the laboratory opens.", 25);
            typeTextCenteredLine("These subjects are different... trained, disciplined, and weaponized.", 25);
            typeTextCenteredLine("They do not hunt like animals.", 25);
            typeTextCenteredLine("They move like soldiers.", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("Security System: Combat Prototype Unit activated.", 25);
            waitForEnter();
        }
        // FIRST TIME INTRO ONLY - Zone 4
        else if (zoneIndex == 19 && progress[19] == 0)
        {
            system("cls");
            typeTextCenteredLine("[BLACKSITE CORE LOG]", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("Elemental reactor pressure rising...", 25);
            typeTextCenteredLine("Cryo, plasma, and thunder energy detected inside the chamber.", 25);
            typeTextCenteredLine("These subjects are not simple mutations anymore.", 25);
            typeTextCenteredLine("Their bodies are adapting to unstable elemental power.", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("Security System: Elemental Apex Chamber unlocked.", 25);
            waitForEnter();
        }
        // FIRST TIME INTRO ONLY - Zone 5 / Final Boss
        else if (zoneIndex == 20 && progress[20] == 0)
        {
            system("cls");
            typeTextCenteredLine("[FINAL CONTAINMENT - PROJECT CERBERUS]", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("The deepest door of the Blacksite opens.", 25);
            typeTextCenteredLine("No patrols. No cages. No warning lights.", 25);
            typeTextCenteredLine("Only one containment pod remains active.", 25);
            typeTextCenteredBlank();

            typeTextCenteredLine("Dr. Bricky: Every stray... every mutant... every soldier...", 25);
            typeTextCenteredLine("Dr. Bricky: They were all unfinished drafts.", 25);
            typeTextCenteredLine("Dr. Bricky: But this one... this is my true introduction to the world.", 25);
            typeTextCenteredBlank();

            typeTextCenteredLine("The glass pod cracks from the inside.", 25);
            typeTextCenteredLine("A humanoid mutant dog opens its eyes.", 25);
            typeTextCenteredLine("Its body is built like a weapon... but it breathes like something alive.", 25);
            typeTextCenteredBlank();

            typeTextCenteredLine("SYSTEM: Regeneration cycle unstable.", 25);
            typeTextCenteredLine("SYSTEM: Subject will fully heal after 22 to 24 turns.", 25);
            typeTextCenteredLine("SYSTEM: Blacksite self-destruct timer active: 5 minutes.", 25);
            waitForEnter();
        }
        // REPLAY INTRO ONLY
        else if (progress[zoneIndex] >= zoneMax)
        {
            system("cls");

            if (zoneIndex == 20)
            {
                typeTextCenteredLine("The final containment pod repairs itself...", 25);
                typeTextCenteredLine("Project Cerberus waits in silence.", 25);
            }
            else if (zoneIndex == 18)
            {
                if (rand() % 2 == 0)
                {
                    typeTextCenteredLine("Combat prototypes return to their patrol routes...", 25);
                    typeTextCenteredLine("Their training never stops.", 25);
                }
                else
                {
                    typeTextCenteredLine("The tactical ward resets its combat simulation...", 25);
                    typeTextCenteredLine("Another prototype steps forward.", 25);
                }
            }
            else if (zoneIndex == 19)
            {
                if (rand() % 2 == 0)
                {
                    typeTextCenteredLine("The Elemental Apex Chamber reactivates...", 25);
                    typeTextCenteredLine("Unstable energy gathers around another subject.", 25);
                }
                else
                {
                    typeTextCenteredLine("The core refuses to shut down...", 25);
                    typeTextCenteredLine("A new elemental mutation awakens.", 25);
                }
            }
            else
            {
                if (rand() % 2 == 0)
                {
                    typeTextCenteredLine("The laboratory remains active...", 25);
                    typeTextCenteredLine("Enhanced subjects continue their patrols.", 25);
                }
                else
                {
                    typeTextCenteredLine("The Blacksite grows quieter...", 25);
                    typeTextCenteredLine("But the experiments are far from over.", 25);
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

        if (zoneIndex == 20)
        {
            // Final Zone is 1/1 only.
            // NOTE: For full battle mechanics, battle.c/enemy_stage5.c must also support zoneIndex 20.
            // Regen rule target: random 10-12 turns = full heal.
            // Timer rule target: 2 minutes = lose/escape if time runs out.
            strcpy(enemy.name, "Project Cerberus");
            enemy.zoneType = ZONE_MUTANT;
            enemy.personalityType = PERSONALITY_ALPHA;
            enemy.attack += 35;
            enemy.defense += 28;
            enemy.speed += 18;
            enemy.maxHP += 130;
            enemy.hp = enemy.maxHP;
        }
        else
        {
            loadStage5Enemies(&enemy, zoneIndex, i);
        }

        if (i == zoneMax - 1 && zoneIndex != 20)
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
            typeTextCenteredLine("Recover HP before entering the Blacksite Laboratory!", 25);
            waitForEnter();
            continue;
        }

        // ZONE 1 BOSS INTRO
        if (zoneIndex == 16 && i == 3)
        {
            system("cls");
            printBlankLine();
            typeTextCenteredLine("Dr. Bricky: So you made it this far...", 25);
            typeTextCenteredLine("Dr. Bricky: Impressive.", 25);
            typeTextCenteredLine("Dr. Bricky: Allow me to introduce my masterpiece.", 25);
            typeTextCenteredLine("Dr. Bricky: Alpha-X... awaken.", 25);
            typeTextCenteredBlank();

            typeTextCenteredLine("Alpha-X steps out of the containment chamber.", 25);
            typeTextCenteredLine("Its eyes lock onto you.", 25);

            waitForEnter();
        }
        // ZONE 2 BOSS INTRO
        else if (zoneIndex == 17 && i == 3)
        {
            system("cls");

            typeTextCenteredLine("Warning...", 25);
            typeTextCenteredLine("Containment breach detected.", 25);
            typeTextCenteredLine("Subject LYCAN-REX released.", 25);
            typeTextCenteredBlank();

            typeTextCenteredLine("A massive werewolf-like beast emerges from the darkness.", 25);

            waitForEnter();
        }
        // ZONE 3 BOSS INTRO
        else if (zoneIndex == 18 && i == 3)
        {
            system("cls");

            typeTextCenteredLine("Security System: Final prototype authorized.", 25);
            typeTextCenteredLine("Blacksite doors lock behind you.", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("A heavily trained combat subject steps forward.", 25);
            typeTextCenteredLine("Its armor is scarred from countless test battles.", 25);
            typeTextCenteredLine("Dr. Bricky: This one does not need rage.", 25);
            typeTextCenteredLine("Dr. Bricky: It was built to end fights quickly.", 25);

            waitForEnter();
        }
        // ZONE 4 BOSS INTRO
        else if (zoneIndex == 19 && i == 3)
        {
            system("cls");

            typeTextCenteredLine("Warning: Core stability failing.", 25);
            typeTextCenteredLine("Elemental pressure has exceeded safe limits.", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("The chamber doors open slowly.", 25);
            typeTextCenteredLine("Apex-0 steps forward, surrounded by unstable energy.", 25);
            typeTextCenteredLine("Dr. Bricky: This is not training anymore.", 25);
            typeTextCenteredLine("Dr. Bricky: This is evolution under pressure.", 25);

            waitForEnter();
        }
        // ZONE 5 FINAL BOSS INTRO
        else if (zoneIndex == 20 && i == 0)
        {
            system("cls");

            typeTextCenteredLine("[BLACKSITE MELTDOWN WARNING]", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("Project Cerberus steps out of the broken pod.", 25);
            typeTextCenteredLine("It stands like a human... but growls like a beast.", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("Dr. Bricky: Do not waste time.", 25);
            typeTextCenteredLine("Dr. Bricky: In 22 to 24 turns, Cerberus will regenerate completely.", 25);
            typeTextCenteredLine("Dr. Bricky: And in 5 minutes... this whole laboratory disappears.", 25);
            typeTextCenteredBlank();
            typeTextCenteredLine("SYSTEM: Defeat Project Cerberus before regeneration and meltdown.", 25);

            waitForEnter();
        }

        int result = battleWithEnemyIndex(player, zoneIndex, progress, i);

        if (result == 0)
            continue;

        if (result == 1)
        {
            if (zoneIndex == 16 && progress[16] < zoneMax)
            {
                printCentered("[DATA LOG]: Enhanced stray contained.");
                printCenteredFormat("Zone Progress: %d/%d", progress[16], zoneMax);
                waitForEnter();
            }
            else if (zoneIndex == 17 && progress[17] < zoneMax)
            {
                printCentered("[DATA LOG]: Feral mutation contained.");
                printCenteredFormat("Zone Progress: %d/%d", progress[17], zoneMax);
                waitForEnter();
            }
            else if (zoneIndex == 18 && progress[18] < zoneMax)
            {
                printCentered("[DATA LOG]: Combat prototype neutralized.");
                printCenteredFormat("Zone Progress: %d/%d", progress[18], zoneMax);
                waitForEnter();
            }
            else if (zoneIndex == 19 && progress[19] < zoneMax)
            {
                printCentered("[DATA LOG]: Elemental apex subject stabilized.");
                printCenteredFormat("Zone Progress: %d/%d", progress[19], zoneMax);
                waitForEnter();
            }
            else if (zoneIndex == 20 && progress[20] < zoneMax)
            {
                printCentered("[DATA LOG]: Project Cerberus defeated.");
                printCenteredFormat("Zone Progress: %d/%d", progress[20], zoneMax);
                waitForEnter();
            }

            if (zoneIndex == 16 && progress[16] >= 4)
            {
                system("cls");
                typeTextCenteredLine("ZONE 1: ENHANCED STRAYS COMPLETE", 20);
            typeTextCenteredBlank();
                typeTextCenteredLine("If the old Back Alley strays became this strong...", 28);
                typeTextCenteredLine("what else is waiting deeper inside the laboratory?", 28);
                waitForEnter();
            }

            if (zoneIndex == 17 && progress[17] >= 4)
            {
                system("cls");
                typeTextCenteredLine("ZONE 2: FERAL MUTATION WARD COMPLETE", 20);
            typeTextCenteredBlank();
                typeTextCenteredLine("These were no longer ordinary strays...", 28);
                typeTextCenteredLine("their instincts had evolved into something savage.", 28);
                waitForEnter();
            }

            if (zoneIndex == 18 && progress[18] >= 4)
            {
                system("cls");
                typeTextCenteredLine("ZONE 3: COMBAT PROTOTYPE UNIT COMPLETE", 20);
            typeTextCenteredBlank();
                typeTextCenteredLine("These subjects were not wild anymore...", 28);
                typeTextCenteredLine("they were trained like weapons inside the Blacksite.", 28);
                waitForEnter();
            }

            if (zoneIndex == 19 && progress[19] >= 4)
            {
                system("cls");
                typeTextCenteredLine("ZONE 4: ELEMENTAL APEX CHAMBER COMPLETE", 20);
            typeTextCenteredBlank();
                typeTextCenteredLine("The Blacksite core begins to cool down...", 28);
                typeTextCenteredLine("but the energy left behind still feels alive.", 28);
                waitForEnter();
            }

            if (zoneIndex == 20 && progress[20] >= 1)
            {
                if (!player->campaignCompleted)
                {
                    showProjectCerberusEnding(player);

                    showCampaignEnding();
                    showCredits();

                    player->campaignCompleted = 1;

                    system("cls");
                    typeTextCenteredLine("[NEW FEATURE UNLOCKED]", 25);
                    typeTextCenteredBlank();
                    typeTextCenteredLine("Credits Viewer", 25);

                    waitForEnter();
                }
                else
                {
                    showReplayEnding();
                }
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
                "The Apex Chamber remains unstable...\n",
                "Project Cerberus begins another regeneration cycle...\n",
                "The self-destruct timer continues counting down...\n"
            };

            int msg = rand() % 11;
            typeTextCentered(defeatMsg[msg], 25);
            printf("\n");
            waitForEnter();
        }
    }
}

void showProjectCerberusEnding(Dog *player)
{
    system("cls");

    typeTextCenteredLine("[FINAL CONTAINMENT ROOM]", 25);
            typeTextCenteredBlank();
    typeTextCenteredLine("Project Cerberus collapses to the floor.", 25);
    typeTextCenteredLine("The Blacksite alarms begin to fade.", 25);
            typeTextCenteredBlank();

    waitForEnter();
    system("cls");

    typeTextCenteredLine("Dr. Bricky slowly steps out from behind the broken chamber.", 25);
            typeTextCenteredBlank();
    typeTextCenteredLine("Dr. Bricky: Amazing...", 25);
    typeTextCenteredLine("Dr. Bricky: You actually defeated my final subject.", 25);
            typeTextCenteredBlank();
    typeTextCenteredLine("Dr. Bricky: Your dog is not ordinary either.", 25);
    typeTextCenteredLine("Dr. Bricky: That strength... that loyalty...", 25);
    typeTextCenteredLine("Dr. Bricky: That is exactly what I have been searching for.", 25);
            typeTextCenteredBlank();

    waitForEnter();
    system("cls");

    typeTextCenteredLine("Dr. Bricky: Come with me.", 25);
    typeTextCenteredLine("Dr. Bricky: Together, we can create something greater.", 25);
    typeTextCenteredLine("Dr. Bricky: No more weak creatures.", 25);
    typeTextCenteredLine("Dr. Bricky: Only evolution.", 25);
            typeTextCenteredBlank();

    typeTextCenteredLine("You refuse.", 25);
            typeTextCenteredBlank();

    waitForEnter();
    system("cls");

    typeTextCenteredLine("Project Cerberus suddenly moves.", 25);
    typeTextCenteredLine("Your dog jumps in front of you.", 25);
            typeTextCenteredBlank();
    typeTextCenteredLine("Dr. Bricky raises a hidden injector.", 25);
    typeTextCenteredLine("A black serum enters the wound.", 25);
            typeTextCenteredBlank();

    waitForEnter();
    system("cls");

    typeTextCenteredLine("Dr. Bricky: Interesting...", 25);
    typeTextCenteredLine("Dr. Bricky: Let us see how long this curse follows you.", 25);
            typeTextCenteredBlank();
    typeTextCenteredLine("Dr. Bricky: Not by time.", 25);
    typeTextCenteredLine("Dr. Bricky: Not by death.", 25);
    typeTextCenteredLine("Dr. Bricky: Not even by another timeline.", 25);
            typeTextCenteredBlank();

    waitForEnter();
    system("cls");

    typeTextCenteredLine("[BLACKSITE LABORATORY DESTROYED]", 25);
            typeTextCenteredBlank();
    typeTextCenteredLine("The final chamber falls silent.", 25);
    typeTextCenteredLine("The story is over...", 25);
    typeTextCenteredLine("Or so it seems.", 25);

    waitForEnter();
}