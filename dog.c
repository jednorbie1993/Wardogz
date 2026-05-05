#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h> // para sa strcspn
#include <ctype.h>
#include "sparring.h"
#include "skill.h"
#include "enemy.h"
#include "dog.h"
#include "battle.h"
#include "stat.h"

int systemLog = 0;
int animationOn = 1; //  NEW (default ON)


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

    int roll = rand() % 100;

    if (systemLog)
    {
        printf("[CRIT ] Roll: %-3d | Chance : %-3d\n", roll, critChance);
    }

    return roll < critChance;
}
void preBattleScene()
{
    const char *messages[] = {
        "Stay focused...",
        "You hear footsteps nearby...",
        "A sudden noise echoes...",
        "Something is watching you...",
        "Car passing... be careful!",
        "The air feels tense..."};

    int count = sizeof(messages) / sizeof(messages[0]);

    system("cls");

    // 🔥 random message
    int r = rand() % count;

    printf("\n");
    for (int i = 0; messages[r][i] != '\0'; i++)
    {
        printf("%c", messages[r][i]);
        fflush(stdout);
        Sleep(40); // animation speed
    }

    printf("\n\nPress Enter to continue...");
    getchar();
}
void trainDog(Dog *d, int type)
{
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

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);
            d->speed = clamp(d->speed + g4);
            d->intelligence = clamp(d->intelligence + g5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   g1, g2, g3, g4, g5);
        }

        d->hp = d->maxHP;
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

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);
            d->speed = clamp(d->speed + g4);
            d->intelligence = clamp(d->intelligence + g5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   g1, g2, g3, g4, g5);
        }

        d->hp = d->maxHP;
    }

    // ================= FATIGUE COST =================
    d->fatigue = clampFatigue(d->fatigue - randRange(5, 12), d->maxFatigue);

    waitForEnter();
}

void createDog(Dog *d)
{
    printf("Enter your dog's name: ");

    fgets(d->name, 50, stdin);
    d->name[strcspn(d->name, "\n")] = 0;

    d->hp = 100;
    d->maxHP = 100;
    d->attack = 920;
    d->speed = 300;

    d->defense = 315;
    d->accuracy = 918; // 80% hit chance
    d->intelligence = 920;

    d->fatigue = 100; // full energy
    d->maxFatigue = 100;

    d->skillCount = 2;

    d->isCountering = 0;
    d->counterDamage = 0;

    d->isBleeding = 0;
    d->bleedTurns = 0;
    d->bleedDamage = 0;  // 🔥 ADD THIS
    d->accuracyModifier = 0;  // 🔥 ADD THIS

    strcpy(d->skills[0].name, "Bite");
    d->skills[0].power = 5;
    d->skills[0].cost = 5;
    d->skills[0].type = SKILL_ATTACK;

    strcpy(d->skills[1].name, "Scratch");
    d->skills[1].power = 3;
    d->skills[1].cost = 3;
    d->skills[1].type = SKILL_ATTACK;

    d->equipped[0] = 0;
    d->equipped[1] = 1;
    d->equipped[2] = -1;
    d->equipped[3] = -1;


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

            for (int i = 0; i < d->skillCount; i++)
            {
                printf("%d. %s (Power:%d Cost:%d)\n",
                       i + 1,
                       d->skills[i].name,
                       d->skills[i].power,
                       d->skills[i].cost);
            }

            waitForEnter();
        }

        // ================= CURRENT EQUIPPED =================
        else if (choice == 2)
        {
            system("cls");
            printf("--- CURRENT SKILLS ---\n");

            for (int i = 0; i < 4; i++)
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
            for (int i = 0; i < 4; i++)
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

            printf("\nChoose slot (1-4): ");
            scanf("%d", &slot);
            while (getchar() != '\n')
                ;

            if (slot < 1 || slot > 4)
            {
                printf("Invalid slot!\n");
                waitForEnter();
                continue;
            }

            system("cls");
            printf("\n--- AVAILABLE SKILLS ---\n");

            for (int i = 0; i < d->skillCount; i++)
            {
                printf("%d. %s (P:%d C:%d)\n",
                       i + 1,
                       d->skills[i].name,
                       d->skills[i].power,
                       d->skills[i].cost);
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
    printf("--- Dog Info ---\n");
    printf("Name: %s\n", d.name);
    printf("HP: %d\n", d.hp);
    printf("Attack: %d\n", d.attack);
    printf("Speed: %d\n", d.speed);

    printf("Defense: %d\n", d.defense);
    printf("Accuracy: %d\n", d.accuracy);
    printf("Intelligence: %d\n", d.intelligence);

    printf("Fatigue: %d/100\n", d.fatigue); // ✅ DITO LANG
}

void typeText(char *text, int speed)
{
    if (!animationOn)
    {
        printf("%s", text);
        return;
    }

    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout); // 👉 para real-time output
        Sleep(speed);
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
