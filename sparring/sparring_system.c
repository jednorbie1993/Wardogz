#include "sparring_system.h"
#include "sparring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sparring_unlocks.h"
#include "../stat.h"
#include "../console.h"

void initSparringProgress(Dog *d) {
    for (int i = 0; i < 6; i++) {
        d->sparringProgress[i] = 0;
    }
}

void updateSparringProgress(Dog *d, int enemyIndex, int win) {
    system("cls");

    const char* sparringEnemies[6] = {"Ossas", "Chubby", "Jewar", "Tiny", "Snoopy", "Rival"};

    if (enemyIndex < 0 || enemyIndex >= 6)
    {
        printCentered("Invalid sparring enemy index!");
        waitForEnter();
        return;
    }

    printBorder();
    printBlankLine();
    printCentered("SPARRING RESULTS");
    printBlankLine();

    if (win) {
        int oldProgress = d->sparringProgress[enemyIndex];

        if (d->sparringProgress[enemyIndex] < 10)
            d->sparringProgress[enemyIndex]++;

        printCenteredFormat("WIN! %s progress: %d/10", sparringEnemies[enemyIndex], d->sparringProgress[enemyIndex]);

        if (oldProgress < 10 && d->sparringProgress[enemyIndex] == 10) {
            //printf("  TECHNIQUE UNLOCKED!\n");
            checkSparringUnlock(d);
        }
    } else {
        printCenteredFormat("LOSS! %s progress: %d/10 (no gain)", sparringEnemies[enemyIndex], d->sparringProgress[enemyIndex]);
    }

    waitForEnter();
}

void updateCooldowns(Dog *d)
{
    for (int i = 0; i < d->skillCount; i++)
    {
        if (d->skills[i].cdLeft > 0)
            d->skills[i].cdLeft--;
    }
}

int randGain(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void applySparReward(Dog *player, int type)
{
    int hp = 0, atk = 0, def = 0, spd = 0, acc = 0, intel = 0;

    printBlankLine();
    printCentered("STATS INCREASED");
    printBlankLine();

    if (type == 1) // Ossas
    {
        atk = randGain(3, 6);
        hp  = randGain(1, 3);
        def = randGain(1, 2);
    }
    else if (type == 2) // Chubby
    {
        def = randGain(3, 6);
        hp  = randGain(2, 4);
        atk = randGain(1, 2);
    }
    else if (type == 3) // Jewar
    {
        acc = randGain(3, 6);
        spd = randGain(1, 2);
        intel = randGain(1, 2);
    }
    else if (type == 4) // Tiny
    {
        intel = randGain(3, 6);
        acc = randGain(1, 2);
        hp = randGain(1, 3);
    }
    else if (type == 5) // Snoopy
    {
        spd = randGain(3, 6);
        acc = randGain(1, 2);
        atk = randGain(1, 2);
    }
    else if (type == 6) // Rival Match
    {
        hp    = randGain(2, 5);
        atk   = randGain(2, 5);
        def   = randGain(2, 5);
        spd   = randGain(2, 5);
        acc   = randGain(2, 5);
        intel = randGain(2, 5);
    }

    player->maxHP = clamp(player->maxHP + hp);
    player->hp = clamp(player->hp + hp);

    player->attack = clamp(player->attack + atk);
    player->defense = clamp(player->defense + def);
    player->speed = clamp(player->speed + spd);
    player->accuracy = clamp(player->accuracy + acc);
    player->intelligence = clamp(player->intelligence + intel);

    char rewardLine[160] = "";

    if (hp > 0)
    {
        char part[24];
        snprintf(part, sizeof(part), "HP +%d  ", hp);
        strncat(rewardLine, part, sizeof(rewardLine) - strlen(rewardLine) - 1);
    }

    if (atk > 0)
    {
        char part[24];
        snprintf(part, sizeof(part), "ATK +%d  ", atk);
        strncat(rewardLine, part, sizeof(rewardLine) - strlen(rewardLine) - 1);
    }

    if (def > 0)
    {
        char part[24];
        snprintf(part, sizeof(part), "DEF +%d  ", def);
        strncat(rewardLine, part, sizeof(rewardLine) - strlen(rewardLine) - 1);
    }

    if (spd > 0)
    {
        char part[24];
        snprintf(part, sizeof(part), "SPD +%d  ", spd);
        strncat(rewardLine, part, sizeof(rewardLine) - strlen(rewardLine) - 1);
    }

    if (acc > 0)
    {
        char part[24];
        snprintf(part, sizeof(part), "ACC +%d  ", acc);
        strncat(rewardLine, part, sizeof(rewardLine) - strlen(rewardLine) - 1);
    }

    if (intel > 0)
    {
        char part[24];
        snprintf(part, sizeof(part), "INT +%d", intel);
        strncat(rewardLine, part, sizeof(rewardLine) - strlen(rewardLine) - 1);
    }

    printCentered(rewardLine);

    waitForEnter();
}

void sparringMenu(Dog *player)
{
    int t;

    while (1)
    {
        system("cls");

        printBorder();
        printBlankLine();
        printCentered("SPARRING TRAINING");
        printBlankLine();

        printMenuItemFormat(1, "Ossas  (%d/10) (Attack Training)",
                            player->sparringProgress[0]);
        printMenuItemFormat(2, "Chubby (%d/10) (Defense Training)",
                            player->sparringProgress[1]);
        printMenuItemFormat(3, "Jeward (%d/10) (Accuracy Training)",
                            player->sparringProgress[2]);
        printMenuItemFormat(4, "Tiny   (%d/10) (Intelligence Training)",
                            player->sparringProgress[3]);
        printMenuItemFormat(5, "Snoopy (%d/10) (Speed Training)",
                            player->sparringProgress[4]);

        if (player->dogType == 1)
            printMenuItemFormat(6, "Kane   (%d/10) (Rival Match)",
                                player->sparringProgress[5]);
        else
            printMenuItemFormat(6, "Jamber (%d/10) (Rival Match)",
                                player->sparringProgress[5]);

        printMenuItem(7, "Return");
        printBlankLine();
        printf("%35sChoice: ", "");

        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (input[0] == '\0' || !isdigit(input[0]))
        {
            printCentered("Invalid input!");
            waitForEnter();
            continue;
        }

        t = atoi(input);

        if (t == 7)
        {
            system("cls");
            break;
        }

        if (t < 1 || t > 6)
        {
            printCentered("Invalid choice!");
            waitForEnter();
            continue;
        }

        // SIMPLE: HARDCODED NAMES ARRAY
        const char* names[6] = {"Ossas", "Chubby", "Jewar", "Tiny", "Snoopy", "Rival"};
        int enemyIndex = t - 1;

        if (t == 6)
        {
            if (player->dogType == 1)
            {
                printBlankLine();
                printCentered("Rival Match: Kane! Let's go!");
            }
            else
            {
                printBlankLine();
                printCentered("Rival Match: Jamber! Let's go!");
            }
        }
        else
        {
            printBlankLine();
            printCenteredFormat("Sparring %s! Let's go!", names[enemyIndex]);
        }

        waitForEnter();

        // BATTLE
        sparringBattle(player, t);

        // NO NEED for updateSparringProgress here anymore!
    }
}

