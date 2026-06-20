#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "arena.h"
#include "../battle.h"
#include "../skill.h"
#include "../stat.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "arena_enemy.h"

void showHPBarPlayer(int hp, int maxHp);
void showHPBarEnemy(int hp, int maxHp);

// ================= ARENA RANK NOTES =================
// F, E, D, C, B, A, S = normal rank letters
// X = SS
// Z = SSS
// Ginamit muna ang X at Z para hindi baguhin ang Dog.arenaRank na char.

// ================= ARENA NAMES =================

const char *getArenaClassName(char rank)
{
    switch (rank)
    {
        case 'F': return "F";
        case 'E': return "E";
        case 'D': return "D";
        case 'C': return "C";
        case 'B': return "B";
        case 'A': return "A";
        case 'S': return "S";
        case 'X': return "SS";
        case 'Z': return "SSS";
        default: return "?";
    }
}

const char *getArenaRankName(char rank)
{
    switch (rank)
    {
        case 'F': return "Open Grounds";
        case 'E': return "Street Pit";
        case 'D': return "Junkyard Arena";
        case 'C': return "Victory Coliseum";
        case 'B': return "Royal Octagon";
        case 'A': return "Crown Arena";
        case 'S': return "Legend Island";
        case 'X': return "Mythic Dome";
        case 'Z': return "Final Apex";
        default: return "Unranked";
    }
}

const char *getArenaTitle(char rank)
{
    switch (rank)
    {
        case 'F': return "Open Challenger";
        case 'E': return "Street Fighter";
        case 'D': return "Scrap Contender";
        case 'C': return "Coliseum Warrior";
        case 'B': return "Royal Contender";
        case 'A': return "Crown Champion";
        case 'S': return "Living Legend";
        case 'X': return "Mythic Champion";
        case 'Z': return "World Legend";
        default: return "No Title";
    }
}

// ================= ARENA PROGRESS =================

int getRequiredWins(char rank)
{
    switch (rank)
    {
        case 'F': return 3;
        case 'E': return 5;
        case 'D': return 1; //6
        case 'C': return 1; //6
        case 'B': return 1; //8
        case 'A': return 1; //8
        case 'S': return 9;
        case 'X': return 4; // SS
        case 'Z': return 1; // SSS final 1v1
        default: return 3;
    }
}

int getRankIndex(char rank)
{
    switch (rank)
    {
        case 'F': return 0;
        case 'E': return 1;
        case 'D': return 2;
        case 'C': return 3;
        case 'B': return 4;
        case 'A': return 5;
        case 'S': return 6;
        case 'X': return 7; // SS
        case 'Z': return 8; // SSS
        default: return 0;
    }
}

int isRankUnlocked(char highestRank, char selectedRank)
{
    return getRankIndex(selectedRank) <= getRankIndex(highestRank);
}

int isFinalArenaCleared(Dog *player)
{
    return player->arenaRank == 'Z' &&
           player->arenaProgress >= player->arenaRequiredWins;
}

void rankUpArena(Dog *player)
{
    if (player->arenaRank == 'F')
    {
        player->arenaRank = 'E';
        player->maxRest++;
    }
    else if (player->arenaRank == 'E')
    {
        player->arenaRank = 'D';
        player->maxRest++;
    }
    else if (player->arenaRank == 'D')
    {
        player->arenaRank = 'C';
        player->maxRest++;
    }
    else if (player->arenaRank == 'C')
    {
        player->arenaRank = 'B';
        player->maxRest++;
    }
    else if (player->arenaRank == 'B')
    {
        player->arenaRank = 'A';
        player->maxSkillSlots = 5;
    }
    else if (player->arenaRank == 'A')
    {
        player->arenaRank = 'S';
        player->maxSkillSlots = 6;
    }
    else if (player->arenaRank == 'S')
    {
        player->arenaRank = 'X'; // SS
        player->maxSkillSlots = 7;
    }
    else if (player->arenaRank == 'X')
    {
        player->arenaRank = 'Z'; // SSS
        player->maxSkillSlots = 8;
    }
    else
    {
        printf("\nYou already cleared the highest Arena Class!\n");
        return;
    }

    player->arenaProgress = 0;
    player->arenaRequiredWins = getRequiredWins(player->arenaRank);

    printf("\n===== RANK UP! =====\n");
    printf("New Rank: Class %s\n", getArenaClassName(player->arenaRank));
    printf("New Venue: %s\n", getArenaRankName(player->arenaRank));
    printf("New Title: %s\n", getArenaTitle(player->arenaRank));

    if (player->arenaRank == 'E')
        printf("Reward: Rest Capacity +1\n");
    else if (player->arenaRank == 'D')
        printf("Reward: Rest Capacity +1\n");

    else if (player->arenaRank == 'C')
        printf("Reward: Rest Capacity +1\n");

    else if (player->arenaRank == 'A')
        printf("Reward: Skill Slots increased to 5\n");

    else if (player->arenaRank == 'S')
        printf("Reward: Skill Slots increased to 6\n");

    else if (player->arenaRank == 'X')
        printf("Reward: Skill Slots increased to 7\n");

    else if (player->arenaRank == 'Z')
        printf("Reward: Skill Slots increased to 8\n");
    }

// ================= ARENA BATTLE CORE =================

void applyArenaWinProgress(Dog *player, char selectedRank)
{
    player->arenaWins++;

    if (selectedRank == player->arenaRank && !isFinalArenaCleared(player))
    {
        player->arenaProgress++;

        if (player->arenaProgress >= player->arenaRequiredWins)
        {
            if (player->arenaRank == 'Z')
            {
                printf("\n===== FINAL ARENA CLEARED! =====\n");
                printf("You defeated the SSS 1v1 champion!\n");
                printf("Arena Status: WORLD APEX LEGEND\n");
            }
            else
            {
                printf("\nProgress: %d/%d\n",
                       player->arenaProgress,
                       player->arenaRequiredWins);
                rankUpArena(player);
            }
        }
        else
        {
            printf("\nArena Progress: %d/%d\n",
                   player->arenaProgress,
                   player->arenaRequiredWins);
        }
    }
    else
    {
        printf("\nVictory recorded.\n");
    }
}

int arenaBattle(Dog *player, char selectedRank)
{
    if (player->hp <= 0)
    {
        printf("You must rest before entering the Arena!\n");
        waitForEnter();
        return -1;
    }

    Dog enemy;

    if (selectedRank == 'F')
    {
        int enemyIndex = rand() % 4;
        loadArenaClassFEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'E')
    {
        int enemyIndex = rand() % 6;
        loadArenaClassEEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'D')
    {
        int enemyIndex = rand() % 8;
        loadArenaClassDEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'C')
    {
        int enemyIndex = rand() % 8;
        loadArenaClassDEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'B')
    {
        int enemyIndex = rand() % 10;
        loadArenaClassDEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'A')
    {
        int enemyIndex = rand() % 10;
        loadArenaClassDEnemy(&enemy, enemyIndex);
    }                        
    else
    {
        system("cls");
        printf("Class %s real battle is not built yet.\n", getArenaClassName(selectedRank));
        waitForEnter();
        return -1;
    }

    int choice, move;
    int defending = 0;
    int baseDef = player->defense;
    int baseSpd = player->speed;

    player->bleedDamage = 0;
    player->accuracyModifier = 0;
    enemy.bleedDamage = 0;
    enemy.accuracyModifier = 0;

    showArenaEnemyEntrance(&enemy, selectedRank);

    showHPBarPlayer(-1, 1);
    showHPBarEnemy(-1, 1);

    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");
        displayBattleStatus(*player, enemy);

        printf("===== ARENA BATTLE =====\n");
        printf("Opponent: %s\n\n", enemy.name);

        printf("--- YOUR TURN ---\n");
        printf("1. Attack  2. Defend  3. Heal  4. Surrender\n");
        printf("Choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 4)
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        if (choice == 1)
        {
            system("cls");
            displayBattleStatus(*player, enemy);

            printf("Skills:\n");
            for (int j = 0; j < player->maxSkillSlots; j++)
            {
                if (player->equipped[j] != -1)
                {
                    int idx = player->equipped[j];
                    printf("%d. %s (P:%d C:%d)\n", j + 1,
                           player->skills[idx].name,
                           player->skills[idx].power,
                           player->skills[idx].cost);
                }
                else
                    printf("%d. ---\n", j + 1);
            }

            printf("Choice: ");
            fgets(input, sizeof(input), stdin);

            if (sscanf(input, "%d", &move) != 1 || move < 1 || move > player->maxSkillSlots)
            {
                printf("Invalid skill!\n");
                waitForEnter();
                continue;
            }

            int skillIdx = player->equipped[move - 1];
            if (skillIdx == -1)
            {
                printf("No skill equipped!\n");
                waitForEnter();
                continue;
            }

            Skill s = player->skills[skillIdx];

            system("cls");
            displayBattleStatus(*player, enemy);

            if (player->fatigue < s.cost)
            {
                printf("\nLow energy! Weak attack!\n");
                player->fatigue = 0;
            }
            else
            {
                player->fatigue -= s.cost;
            }

            useSkill(player, &enemy, s);

            if (enemy.hp < 0)
                enemy.hp = 0;

            waitForEnter();
        }
        else if (choice == 2)
        {
            defending = 1;
            printf("Defending!\n");
            waitForEnter();
        }
        else if (choice == 3)
        {
            player->hp += 20;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printf("Healed +20 HP!\n");
            waitForEnter();
        }
        else if (choice == 4)
        {
            printf("\nYou surrendered the arena match.\n");
            player->arenaLosses++;
            player->defense = baseDef;
            player->speed = baseSpd;
            waitForEnter();
            return 2;
        }

        if (enemy.hp <= 0)
            break;

        Sleep(400);
        enemyAttack(player, &enemy, &defending);
        defending = 0;

        player->fatigue += 2;
        if (player->fatigue > player->maxFatigue)
            player->fatigue = player->maxFatigue;
    }

    system("cls");
    displayBattleStatus(*player, enemy);

    if (player->hp <= 0)
    {
        printf("\nYOU LOST THE ARENA MATCH...\n");
        player->arenaLosses++;
        player->fatigue = clampFatigue(player->fatigue + 15, player->maxFatigue);

        player->defense = baseDef;
        player->speed = baseSpd;

        waitForEnter();
        return 0;
    }

    printf("\nYOU WIN THE ARENA MATCH!\n");
    printf("%s can no longer fight.\n", enemy.name);

    applyArenaWinProgress(player, selectedRank);
    applyBattleStatGain(player);
    checkSkillUnlock(player);

    player->fatigue = clampFatigue(player->fatigue + 10, player->maxFatigue);
    player->defense = baseDef;
    player->speed = baseSpd;

    waitForEnter();
    return 1;
}

// ================= ARENA RECORD =================

void showArenaRecord(Dog *player)
{
    system("cls");

    printf("===== ARENA STATS =====\n\n");
    printf("Highest Class: %s - %s\n",
           getArenaClassName(player->arenaRank),
           getArenaRankName(player->arenaRank));
    printf("Title: %s\n", getArenaTitle(player->arenaRank));
    printf("Record: %dW - %dL - %dD\n",
           player->arenaWins,
           player->arenaLosses,
           player->arenaDraws);

    if (isFinalArenaCleared(player))
    {
        printf("Arena Status: WORLD APEX LEGEND\n");
    }
    else
    {
        printf("Progress: %d/%d (Class %s)\n",
               player->arenaProgress,
               player->arenaRequiredWins,
               getArenaClassName(player->arenaRank));
    }

    waitForEnter();
}

// ================= ENTER VENUE =================

void enterArena(Dog *player, char selectedRank)
{
    int choice;
    char input[10];

    while (1)
    {
        system("cls");

        printf("===== %s =====\n", getArenaRankName(selectedRank));
        printf("Class %s - %s\n",
               getArenaClassName(selectedRank),
               getArenaTitle(selectedRank));

        if (selectedRank == player->arenaRank)
        {
            if (isFinalArenaCleared(player))
                printf("Progress: CLEARED\n\n");
            else
                printf("Progress: %d/%d\n\n",
                       player->arenaProgress,
                       player->arenaRequiredWins);
        }
        else
        {
            printf("Progress: Cleared Class\n\n");
        }

        printf("1. Start Match\n");
        printf("2. Back\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1)
        {
            arenaBattle(player, selectedRank);
        }
        else if (choice == 2)
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

// ================= SELECT ARENA MENU =================

void selectArenaMenu(Dog *player)
{
    int choice;
    char input[10];

    while (1)
    {
        system("cls");

        printf("===== SELECT ARENA =====\n\n");

        printf("1. Open Grounds       [Class F]\n");

        if (isRankUnlocked(player->arenaRank, 'E'))
            printf("2. Street Pit         [Class E]\n");

        if (isRankUnlocked(player->arenaRank, 'D'))
            printf("3. Junkyard Arena     [Class D]\n");

        if (isRankUnlocked(player->arenaRank, 'C'))
            printf("4. Victory Coliseum   [Class C]\n");

        if (isRankUnlocked(player->arenaRank, 'B'))
            printf("5. Royal Octagon      [Class B]\n");

        if (isRankUnlocked(player->arenaRank, 'A'))
            printf("6. Crown Arena        [Class A]\n");

        if (isRankUnlocked(player->arenaRank, 'S'))
            printf("7. Legend Island      [Class S]\n");

        if (isRankUnlocked(player->arenaRank, 'X'))
            printf("8. Mythic Dome        [Class SS]\n");

        if (isRankUnlocked(player->arenaRank, 'Z'))
            printf("9. Final Apex         [Class SSS]\n");

        printf("\n0. Back\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1)
            enterArena(player, 'F');
        else if (choice == 2 && isRankUnlocked(player->arenaRank, 'E'))
            enterArena(player, 'E');
        else if (choice == 3 && isRankUnlocked(player->arenaRank, 'D'))
            enterArena(player, 'D');
        else if (choice == 4 && isRankUnlocked(player->arenaRank, 'C'))
            enterArena(player, 'C');
        else if (choice == 5 && isRankUnlocked(player->arenaRank, 'B'))
            enterArena(player, 'B');
        else if (choice == 6 && isRankUnlocked(player->arenaRank, 'A'))
            enterArena(player, 'A');
        else if (choice == 7 && isRankUnlocked(player->arenaRank, 'S'))
            enterArena(player, 'S');
        else if (choice == 8 && isRankUnlocked(player->arenaRank, 'X'))
            enterArena(player, 'X');
        else if (choice == 9 && isRankUnlocked(player->arenaRank, 'Z'))
            enterArena(player, 'Z');
        else if (choice == 0)
            break;
        else
        {
            printf("Class locked or invalid choice!\n");
            waitForEnter();
        }
    }
}

// ================= MAIN ARENA MENU =================

void arenaMenu(Dog *player)
{
    int choice;
    char input[10];

    while (1)
    {
        system("cls");

        printf("===== ARENA =====\n\n");
        printf("1. Fight Arena\n");
        printf("2. Arena Stats\n");
        printf("3. Exit\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1)
            selectArenaMenu(player);
        else if (choice == 2)
            showArenaRecord(player);
        else if (choice == 3)
            break;
        else
        {
            printf("Invalid choice! Select 1-3 only.\n");
            waitForEnter();
        }
    }
}
