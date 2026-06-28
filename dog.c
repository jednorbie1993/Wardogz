#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h> // para sa strcspn
#include <ctype.h>
#include "sparring/sparring.h"
#include "skill.h"
#include "enemies/enemy.h"
#include "dog.h"
#include "battle.h"
#include "stat.h"
#include "cinematic.h"
#include "sparring/sparring_system.h"
#include "arena/arena.h"

int systemLog = 0;
int animationOn = 1; //  NEW (default ON)


// Intelligence critical bonus support.
// battle.c sets this before attacks using setCriticalUserIntelligence().
// Keeps the old isCritical(currentHP, maxHP) signature safe for existing code.
static int currentCritIntBonus = 0;

void setCriticalUserIntelligence(Dog *user)
{
    if (user == NULL)
    {
        currentCritIntBonus = 0;
        return;
    }

    // +1% Critical Chance every 100 INT
    currentCritIntBonus = user->intelligence / 100;

    // Safety cap so INT cannot make crit chance too overpowered.
    if (currentCritIntBonus > 15)
        currentCritIntBonus = 15;
}

int isCritical(int currentHP, int maxHP)
{
    int critChance;

    if (currentHP <= maxHP * 0.2)
    {
        // LOW HP → clutch mode
        critChance = (rand() % 16) + 20; // 20–35%
    }
    else
    {
        // NORMAL
        critChance = (rand() % 8) + 8; // 8–15%
    }

    // INT bonus is added directly to the same crit chance.
    critChance += currentCritIntBonus;

    // Final crit chance cap.
    if (critChance > 40)
        critChance = 40;

    int roll = rand() % 100;

    if (systemLog)
    {
        printf("[CRIT ] Roll: %-3d | Chance : %-3d\n", roll, critChance);
    }

    return roll < critChance;
}

void zoneStoryIntro(int zoneIndex, int progress)
{
    system("cls");

    // BACK ALLEY
    if (zoneIndex == 0 && progress == 0)
    {
        typeText("The alley reeks of rust and old blood.\n", 25);
        typeText("Weak strays wander these streets...\n", 25);
        typeText("But something stronger lurks deeper inside.\n", 25);
    }

    // JUNKYARD
    else if (zoneIndex == 1 && progress == 0)
    {
        typeText("Mountains of scrap tower around you.\n", 25);
        typeText("The junkyard dogs fight without fear.\n", 25);
    }

    // ABANDONED BLOCK
    else if (zoneIndex == 2 && progress == 0)
    {
        typeText("The abandoned block feels lifeless.\n", 25);
        typeText("But hidden eyes follow your every step.\n", 25);
    }

    // RIVER PACK HIDEOUT
    else if (zoneIndex == 3 && progress == 0)
    {
        typeText("The river carries the scent of wild packs.\n", 25);
        typeText("You are far from the city now.\n", 25);
    }

    printf("\n");
 
}

void preBattleScene(int zoneIndex)
{
    const char *messages[6];

    if (zoneIndex <= 2)
    {
        static const char *urbanMessages[] =
        {
            "The alley reeks of rust and old blood...",
            "You hear barking somewhere beyond the dark streets...",
            "Broken bottles crack beneath your paws...",
            "Something watches from the shadows nearby...",
            "A speeding car passes outside the alley...",
            "The deeper streets feel strangely quiet..."
        };

        for (int i = 0; i < 6; i++)
            messages[i] = urbanMessages[i];
    }
    else if (zoneIndex <= 7)
    {
        static const char *wildMessages[] =
        {
            "The forest air feels heavy with danger...",
            "Growls echo somewhere in the wild...",
            "Fresh claw marks cover the ground...",
            "Something moves between the trees...",
            "The wild territory feels unforgiving...",
            "Every step deeper feels dangerous..."
        };

        for (int i = 0; i < 6; i++)
            messages[i] = wildMessages[i];
    }
    else if (zoneIndex <= 11)
    {
        static const char *militaryMessages[] =
        {
            "Abandoned military structures surround the area...",
            "Boot prints remain in the dust...",
            "A distant siren echoes through the ruins...",
            "Old surveillance equipment flickers nearby...",
            "The checkpoint ahead feels strangely silent...",
            "Something patrols these grounds..."
        };

        for (int i = 0; i < 6; i++)
            messages[i] = militaryMessages[i];
    }
    else
    {
        static const char *bioMessages[] =
        {
            "The laboratory smells of chemicals and decay...",
            "Warning lights flash across the facility...",
            "Strange noises echo through the corridors...",
            "Containment chambers line the walls...",
            "A cold mechanical voice repeats an alert...",
            "Something escaped from the testing area..."
        };

        for (int i = 0; i < 6; i++)
            messages[i] = bioMessages[i];
    }

    int count = 6;
    int r = rand() % count;

    printf("\n");

    for (int i = 0; messages[r][i] != '\0'; i++)
    {
        printf("%c", messages[r][i]);
        fflush(stdout);
        Sleep(25);
    }

    printf("\n\nPress Enter to continue...");
    getchar();
}


int getTrainingFatigueBonus(int trainingCount)
{
    if (trainingCount >= 30)
        return 300;
    else if (trainingCount >= 20)
        return 200;
    else if (trainingCount >= 10)
        return 100;

    return 0;
}

void updateTrainingMaxFatigue(Dog *d)
{
    int fatigueBonus = 0;

    fatigueBonus += getTrainingFatigueBonus(d->powerTrainingCount);
    fatigueBonus += getTrainingFatigueBonus(d->speedTrainingCount);
    fatigueBonus += getTrainingFatigueBonus(d->balanceTrainingCount);

    d->maxFatigue = 100 + fatigueBonus;

    if (d->maxFatigue > 1000)
        d->maxFatigue = 1000;

    if (d->fatigue > d->maxFatigue)
        d->fatigue = d->maxFatigue;
}

void showTrainingMasteryMessage(int type, int count)
{
    char trainingName[20];

    if (type == 1)
        strcpy(trainingName, "POWER");
    else if (type == 2)
        strcpy(trainingName, "SPEED");
    else if (type == 3)
        strcpy(trainingName, "BALANCE");
    else
        return;

    if (count == 10)
        printf("%s TRAINING MASTERY I! Max Fatigue +100!\n", trainingName);
    else if (count == 20)
        printf("%s TRAINING MASTERY II! Max Fatigue +200!\n", trainingName);
    else if (count == 30)
        printf("%s TRAINING MASTERY III! Max Fatigue +300!\n", trainingName);
}

void applyPartnerStatBonus(Dog *d,
                           int *hpGain,
                           int *atkGain,
                           int *defGain,
                           int *spdGain,
                           int *accGain,
                           int *intGain)
{
    // dogType: 1 = Jamber, 2 = Kane
    // No extra printf here. Bonus is added directly to the same gain values.

    if (d->dogType == 1) // Jamber: HP / ATK / DEF
    {
        if (hpGain != NULL)
            *hpGain += randRange(1, 10);

        if (atkGain != NULL)
            *atkGain += randRange(1, 10);

        if (defGain != NULL)
            *defGain += randRange(1, 10);
    }
    else if (d->dogType == 2) // Kane: SPD / ACC / INT
    {
        if (spdGain != NULL)
            *spdGain += randRange(1, 10);

        if (accGain != NULL)
            *accGain += randRange(1, 10);

        if (intGain != NULL)
            *intGain += randRange(1, 10);
    }
}

void trainDog(Dog *d, int type)
{
    int oldHP = d->maxHP;

    printf("\nTraining");

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(200);
    }
    printf("\n");

    // ================= HARD BLOCK: NO ENERGY =================
    if (d->fatigue <= 0)
    {
        printf("Your dog is completely exhausted!\n");
        printf("You must REST before training again.\n");

        d->fatigue = 0;
        waitForEnter();
        return;
    }

    // ================= FATIGUE FAILURE SYSTEM =================
    int failChance;

    if (d->fatigue <= 30)
        failChance = 25;
    else if (d->fatigue <= 50)
        failChance = 15;
    else
        failChance = 5;

    int rollFail = rand() % 100;

    if (rollFail < failChance)
    {
        printf("Too exhausted... Training failed!\n");

        d->fatigue = clampFatigue(d->fatigue - 5, d->maxFatigue);

        waitForEnter();
        return;
    }

    int greatChance = rand() % 100;

    // ================= TRAINING SUCCESS =================
    if (greatChance < 10)
    {
        printf("GREAT TRAINING!\n");

        if (type == 1)
        {
            int g1 = randRange(11, 20);
            int g2 = randRange(11, 20);
            int g3 = randRange(11, 20);

            applyPartnerStatBonus(d, &g1, &g2, &g3, NULL, NULL, NULL);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);

            printf("HP +%d | ATK +%d | DEF +%d\n", g1, g2, g3);
        }
        else if (type == 2)
        {
            int g1 = randRange(11, 20);
            int g2 = randRange(11, 20);
            int g3 = randRange(11, 20);

            applyPartnerStatBonus(d, NULL, NULL, NULL, &g1, &g2, &g3);

            d->speed = clamp(d->speed + g1);
            d->accuracy = clamp(d->accuracy + g2);
            d->intelligence = clamp(d->intelligence + g3);

            printf("SPD +%d | ACC +%d | INT +%d\n", g1, g2, g3);
        }
        else
        {
            int g1 = randRange(11, 20);
            int g2 = randRange(11, 20);
            int g3 = randRange(11, 20);
            int g4 = randRange(11, 20);
            int g5 = randRange(11, 20);

            applyPartnerStatBonus(d, &g1, &g2, &g3, &g4, NULL, &g5);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);
            d->speed = clamp(d->speed + g4);
            d->intelligence = clamp(d->intelligence + g5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   g1, g2, g3, g4, g5);
        }

    }
    else
    {
        printf("Training successful!\n");

        int minGain, maxGain;

        if (d->fatigue <= 30)
        {
            minGain = 1;
            maxGain = 10;
        }
        else
        {
            minGain = 5;
            maxGain = 10;
        }

        if (type == 1)
        {
            int g1 = randRange(minGain, maxGain);
            int g2 = randRange(minGain, maxGain);
            int g3 = randRange(minGain, maxGain);

            applyPartnerStatBonus(d, &g1, &g2, &g3, NULL, NULL, NULL);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);

            printf("HP +%d | ATK +%d | DEF +%d\n", g1, g2, g3);
        }
        else if (type == 2)
        {
            int g1 = randRange(minGain, maxGain);
            int g2 = randRange(minGain, maxGain);
            int g3 = randRange(minGain, maxGain);

            applyPartnerStatBonus(d, NULL, NULL, NULL, &g1, &g2, &g3);

            d->speed = clamp(d->speed + g1);
            d->accuracy = clamp(d->accuracy + g2);
            d->intelligence = clamp(d->intelligence + g3);

            printf("SPD +%d | ACC +%d | INT +%d\n", g1, g2, g3);
        }
        else
        {
            int g1 = randRange(minGain, maxGain);
            int g2 = randRange(minGain, maxGain);
            int g3 = randRange(minGain, maxGain);
            int g4 = randRange(minGain, maxGain);
            int g5 = randRange(minGain, maxGain);

            applyPartnerStatBonus(d, &g1, &g2, &g3, &g4, NULL, &g5);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);
            d->speed = clamp(d->speed + g4);
            d->intelligence = clamp(d->intelligence + g5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   g1, g2, g3, g4, g5);
        }

    }
    int oldHundreds = oldHP / 100;
    int newHundreds = d->maxHP / 100;

    if (newHundreds > oldHundreds)
    {
        printf("Your endurance has improved!\n");
    }
    // ================= TRAINING COUNT =================
    if (type == 1)
    {
        d->powerTrainingCount++;
        showTrainingMasteryMessage(type, d->powerTrainingCount);
    }
    else if (type == 2)
    {
        d->speedTrainingCount++;
        showTrainingMasteryMessage(type, d->speedTrainingCount);
    }
    else if (type == 3)
    {
        d->balanceTrainingCount++;
        showTrainingMasteryMessage(type, d->balanceTrainingCount);
    }

    // ================= UPDATE MAX FATIGUE =================
    updateTrainingMaxFatigue(d);

    printf("Training Count: Power %d/30 | Speed %d/30 | Balance %d/30\n",
           d->powerTrainingCount,
           d->speedTrainingCount,
           d->balanceTrainingCount);

    printf("Max Fatigue: %d\n", d->maxFatigue);

    // ================= FATIGUE COST =================
    d->fatigue = clampFatigue(d->fatigue - randRange(5, 12), d->maxFatigue);

    waitForEnter();
}

void createDog(Dog *d)
{
    /*printf("Enter your dog's name: ");

    fgets(d->name, 50, stdin);
    d->name[strcspn(d->name, "\n")] = 0;*/

    d->hp = 900;
    d->maxHP = 900;
    d->attack = 920;
    d->speed = 900;

    d->defense = 915;
    d->accuracy = 918; // 80% hit chance
    d->intelligence = 920;

    d->fatigue = 100; // full energy
    d->maxFatigue = 100;

    d->skillCount = 2;

    d->isCountering = 0;
    d->counterDamage = 0;

    d->powerTrainingCount = 0;
    d->speedTrainingCount = 0;
    d->balanceTrainingCount = 0;
    d->stageClearBonus = 0;

    d->isBleeding = 0;
    d->bleedTurns = 0;
    d->bleedDamage = 0;  //  ADD THIS
    d->accuracyModifier = 0;  //  ADD THIS

    strcpy(d->skills[0].name, "Bite");
    d->skills[0].power = 5;
    d->skills[0].cost = 5;
    d->skills[0].type = SKILL_ATTACK;

    strcpy(d->skills[1].name, "Scratch");
    d->skills[1].power = 3;
    d->skills[1].cost = 3;
    d->skills[1].type = SKILL_ATTACK;

    /*strcpy(d->skills[0].name, "Hip Check");
    d->skills[0].power = 9;
    d->skills[0].cost = 8;
    d->skills[0].type = SKILL_DAMAGE;
    d->skills[0].cooldown = 1;
    d->skills[0].cdLeft = 0;

    strcpy(d->skills[1].name, "Rival Breaker");
    d->skills[1].power = 18;
    d->skills[1].cost = 10;
    d->skills[1].type = SKILL_DAMAGE;
    d->skills[1].cooldown = 0;
    d->skills[1].cdLeft = 0;*/

    d->maxSkillSlots = 4;

    for (int i = 0; i < MAX_EQUIPPED_SKILLS; i++)
    d->equipped[i] = -1;

    d->equipped[0] = 0;
    d->equipped[1] = 1;
    d->equipped[2] = -1;
    d->equipped[3] = -1;
    //secret enemy
    d->defeatedGrimfang = 0;
    d->defeatedDiremaw = 0;
    d->defeatedBlackclaw = 0;
    d->defeatedOmega = 0;
    d->defeatedGrimfangX = 0;

    d->arenaRank = 'X';
    d->arenaWins = 0;
    d->arenaLosses = 0;
    d->arenaDraws = 0;
    d->hipCheckUses = 0;
    d->isStunned = 0;
    d->stunTurns = 0;
    d->arenaProgress = 0;
    d->arenaRequiredWins = 1;
    d->maxRest = 3;

    initSparringProgress(d);
}

int hasSkill(Dog *d, char name[])
{
    for (int i = 0; i < d->skillCount; i++)
    {
        if (strcmp(d->skills[i].name, name) == 0)
        {
            return 1; // meron na
        }
    }
    return 0; // wala pa
}

void skillMenu(Dog *d)
{
    int choice;

    while (1)
    {
        system("cls");

        printf("===== SKILL MENU =====\n");
        printf("1. View All Skills\n");
        printf("2. Current Skills\n");
        printf("3. Equip Skills\n");
        printf("4. Back\n");
        printf("Choice: ");

        char input[20];
        int choice;

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (input[0] == '\0')
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        choice = atoi(input);

        // ================= VIEW ALL =================
        if (choice == 1)
        {
            system("cls");
            printf("--- ALL SKILLS ---\n");

            int half = (d->skillCount + 1) / 2;

            for (int i = 0; i < half; i++)
            {
                printf("%2d. %-18s (P:%2d/C:%2d)",
                        i + 1,
                        d->skills[i].name,
                        d->skills[i].power,
                        d->skills[i].cost);

                if (i + half < d->skillCount)
                {
                    int right = i + half;

                    printf("   %2d. %-18s (P:%2d/C:%2d)",
                        right + 1,
                        d->skills[right].name,
                        d->skills[right].power,
                        d->skills[right].cost);
                }

                printf("\n");
            }
            waitForEnter();
        }

        // ================= CURRENT EQUIPPED =================
        else if (choice == 2)
        {
            system("cls");
            printf("--- CURRENT SKILLS ---\n");

            for (int i = 0; i < d->maxSkillSlots; i++)
            {
                if (d->equipped[i] != -1)
                {
                    int idx = d->equipped[i];
                    printf("Slot %d: %s (P:%d C:%d)\n",
                           i + 1,
                           d->skills[idx].name,
                           d->skills[idx].power,
                           d->skills[idx].cost);
                }
                else
                {
                    printf("Slot %d: [EMPTY]\n", i + 1);
                }
            }

            waitForEnter();
        }

        // ================= EQUIP =================
        else if (choice == 3)
        {
            int slot, pick;

            system("cls");

            // 👉 show current first (very important UX)
            printf("--- CURRENT SKILLS ---\n");
            for (int i = 0; i < d->maxSkillSlots; i++)
            {
                if (d->equipped[i] != -1)
                {
                    int idx = d->equipped[i];
                    printf("Slot %d: %s\n", i + 1, d->skills[idx].name);
                }
                else
                {
                    printf("Slot %d: [EMPTY]\n", i + 1);
                }
            }

            printf("\nChoose slot (1-%d): ", d->maxSkillSlots);
            scanf("%d", &slot);
            while (getchar() != '\n')
                ;

            if (slot < 1 || slot > d->maxSkillSlots)
            {
                printf("Invalid slot!\n");
                waitForEnter();
                continue;
            }

            system("cls");
            printf("\n--- AVAILABLE SKILLS ---\n");

            int half = (d->skillCount + 1) / 2;

            for (int i = 0; i < half; i++)
            {
                int right = i + half;

                printf("%2d. %-18s (P:%2d/C:%2d)",
                    i + 1,
                    d->skills[i].name,
                    d->skills[i].power,
                    d->skills[i].cost);

                if (right < d->skillCount)
                {
                    printf("   %2d. %-18s (P:%2d/C:%2d)",
                        right + 1,
                        d->skills[right].name,
                        d->skills[right].power,
                        d->skills[right].cost);
                }

                printf("\n");
            }

            printf("Choice: ");
            scanf("%d", &pick);
            while (getchar() != '\n')
                ;

            if (pick < 1 || pick > d->skillCount)
            {
                printf("Invalid skill!\n");
                waitForEnter();
                continue;
            }

            d->equipped[slot - 1] = pick - 1;

            printf("Skill equipped to Slot %d!\n", slot);
            waitForEnter();
        }

        // ================= BACK =================
        else if (choice == 4)
        {
            break;
        }

        else
        {
            printf("Invalid choice!\n");
            waitForEnter();
        }
    }
}





void printDog(Dog d)
{
    printf("===== WARDOGZ INFO =====\n\n");

    printf("Trainer      : %s\n", d.trainerName);
    printf("Partner      : %s\n", d.name);

    //printf("\n");

    printf("HP           : %d/%d\n", d.hp, d.maxHP);
    printf("Attack       : %d\n", d.attack);
    printf("Defense      : %d\n", d.defense);
    printf("Speed        : %d\n", d.speed);
    printf("Accuracy     : %d\n", d.accuracy);
    printf("Intelligence : %d\n", d.intelligence);

    //printf("\n");

    printf("Fatigue      : %d/%d\n", d.fatigue, d.maxFatigue);

    //printf("\n");

    printf("Arena Rank   : Class %c\n", d.arenaRank);
    printf("Arena Title  : %s\n", getArenaTitle(d.arenaRank));

    printf("Arena Record : %dW - %dL - %dD\n",
           d.arenaWins,
           d.arenaLosses,
           d.arenaDraws);

    if (d.arenaRank == 'Z' && d.arenaProgress >= d.arenaRequiredWins)
    {
        printf("Arena Status : WORLD LEGEND\n");
    }
}

void typeText(const char *text, int delay)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delay);
    }
}
void waitForEnter()
{
    printf("\nPress Enter to continue...");
    while (getchar() != '\n')
        ; // wait until Enter lang
}

void pauseAndClear()
{
    printf("\nPress Enter to continue...");

    getchar(); // no loop, no fflush, simple lang

    system("cls");
}
