#include "sparring_system.h"
#include "sparring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sparring_unlocks.h"
#include "../stat.h"

void initSparringProgress(Dog *d) {
    for (int i = 0; i < 5; i++) {
        d->sparringProgress[i] = 0;
    }
}

void updateSparringProgress(Dog *d, int enemyIndex, int win) {
    system("cls");

    // HARDCODE THE NAMES ARRAY HERE
    const char* sparringEnemies[5] = {"Ossas", "Chubby", "Jewar", "Tiny", "Snoopy"};

    printf("=== SPARRING RESULTS ===\n");

    if (win) {
        d->sparringProgress[enemyIndex]++;
        printf("WIN! %s progress: %d/10", sparringEnemies[enemyIndex], d->sparringProgress[enemyIndex]);

        if (d->sparringProgress[enemyIndex] == 10) {
            printf("  TECHNIQUE UNLOCKED!\n");
        } else {
            printf("\n");
        }
    } else {
        printf("LOSS! %s progress: %d/10 (no gain)\n", sparringEnemies[enemyIndex], d->sparringProgress[enemyIndex]);
    }

    // Show all progress
    printf("\n--- ALL PROGRESS ---\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %d/10", sparringEnemies[i], d->sparringProgress[i]);
        if (d->sparringProgress[i] == 10) printf(" [DONE]");
        printf("\n");
    }

    checkSparringUnlock(d);
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

    printf("\n=== STATS INCREASED ===\n");

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
    else // fallback / rival
    {
        hp = randGain(2, 5);
        atk = randGain(2, 5);
        def = randGain(2, 5);
        spd = randGain(2, 5);
    }

    player->maxHP += hp;
    player->hp += hp;
    player->attack += atk;
    player->defense += def;
    player->speed += spd;
    player->accuracy += acc;
    player->intelligence += intel;

    if (hp > 0) printf("HP  +%-2d   ", hp);
    if (atk > 0) printf("ATK +%-2d   ", atk);
    if (def > 0) printf("DEF +%-2d   ", def);
    if (spd > 0) printf("SPD +%-2d   ", spd);
    if (acc > 0) printf("ACC +%-2d   ", acc);
    if (intel > 0) printf("INT +%-2d   ", intel);

    printf("\n");

    waitForEnter();
}

void sparringMenu(Dog *player)
{
    int t;

    while (1)
    {
        system("cls");

        printf("==== SPARRING TRAINING ====\n");
        // SHOW PROGRESS
        printf("1. Ossas     (%d/10)", player->sparringProgress[0]);
        if (player->sparringProgress[0] == 10) printf(" [DONE]");
        printf(" (Attack Training)\n");

        printf("2. Chubby    (%d/10)", player->sparringProgress[1]);
        if (player->sparringProgress[1] == 10) printf(" [DONE]");
        printf(" (Defense Training)\n");

        printf("3. Jewar     (%d/10)", player->sparringProgress[2]);
        if (player->sparringProgress[2] == 10) printf(" [DONE]");
        printf(" (Accuracy Training)\n");

        printf("4. Tiny      (%d/10)", player->sparringProgress[3]);
        if (player->sparringProgress[3] == 10) printf(" [DONE]");
        printf(" (Intelligence Training)\n");

        printf("5. Snoopy    (%d/10)", player->sparringProgress[4]);
        if (player->sparringProgress[4] == 10) printf(" [DONE]");
        printf(" (Speed Training)\n");

        if (player->dogType == 1)
            printf("6. Kane      (Rival Match)\n");
        else
            printf("6. Jamber    (Rival Match)\n");

        printf("7. Return\n");
        printf("Choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (input[0] == '\0' || !isdigit(input[0]))
        {
            printf("Invalid input!\n");
            waitForEnter();
            continue;
        }

        t = atoi(input);

        if (t == 6)
        {
            system("cls");
            break;
        }

        if (t < 1 || t > 5)
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        // SIMPLE: HARDCODED NAMES ARRAY
        const char* names[5] = {"Ossas", "Chubby", "Jewar", "Tiny", "Snoopy"};
        int enemyIndex = t - 1;

        printf("\nSparring %s! Let's go!\n", names[enemyIndex]);
        waitForEnter();

        // BATTLE
        sparringBattle(player, t);

        // NO NEED for updateSparringProgress here anymore!
    }
}

