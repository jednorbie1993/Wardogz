#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy.h"
#include "arena_enemy2.h"
#include "arena_enemy3.h"
#include "arena_enemy4.h"
#include "arena_enemy5.h"
#include "arena_enemy6.h"
#include "arena_enemy7.h"
#include "arena_enemy8.h"
#include "arena.h"
#include "../battle.h"
#include "../skill.h"
#include "../stat.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "../console.h"


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
    case 'F':
        return "F";
    case 'E':
        return "E";
    case 'D':
        return "D";
    case 'C':
        return "C";
    case 'B':
        return "B";
    case 'A':
        return "A";
    case 'S':
        return "S";
    case 'X':
        return "SS";
    case 'Z':
        return "SSS";
    default:
        return "?";
    }
}

const char *getArenaRankName(char rank)
{
    switch (rank)
    {
    case 'F':
        return "Open Grounds";
    case 'E':
        return "Street Pit";
    case 'D':
        return "Junkyard Arena";
    case 'C':
        return "Victory Coliseum";
    case 'B':
        return "Royal Octagon";
    case 'A':
        return "Crown Arena";
    case 'S':
        return "Legend Island";
    case 'X':
        return "Mythic Dome";
    case 'Z':
        return "Final Apex";
    default:
        return "Unranked";
    }
}

const char *getArenaTitle(char rank)
{
    switch (rank)
    {
    case 'F':
        return "Open Challenger";
    case 'E':
        return "Street Fighter";
    case 'D':
        return "Scrap Contender";
    case 'C':
        return "Coliseum Warrior";
    case 'B':
        return "Royal Contender";
    case 'A':
        return "Crown Champion";
    case 'S':
        return "Living Legend";
    case 'X':
        return "Mythic Champion";
    case 'Z':
        return "World Legend";
    default:
        return "No Title";
    }
}

// ================= ARENA PROGRESS =================

int getRequiredWins(char rank)
{
    switch (rank)
    {
    case 'F':
        return 3;
    case 'E':
        return 5;
    case 'D':
        return 6; // 6
    case 'C':
        return 6; // 6
    case 'B':
        return 8; // 8
    case 'A':
        return 8; // 8
    case 'S':
        return 9; // 9
    case 'X':
        return 1; // SS
    case 'Z':
        return 1; // SSS final 1v1
    default:
        return 3;
    }
}

int getRankIndex(char rank)
{
    switch (rank)
    {
    case 'F':
        return 0;
    case 'E':
        return 1;
    case 'D':
        return 2;
    case 'C':
        return 3;
    case 'B':
        return 4;
    case 'A':
        return 5;
    case 'S':
        return 6;
    case 'X':
        return 7; // SS
    case 'Z':
        return 8; // SSS
    default:
        return 0;
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
        printCentered("You already cleared the highest Arena Class!");
        return;
    }

    player->arenaProgress = 0;
    player->arenaRequiredWins = getRequiredWins(player->arenaRank);

    printBlankLine();
    printCentered("===== RANK UP! =====");
    printCenteredFormat("New Rank: Class %s", getArenaClassName(player->arenaRank));
    printCenteredFormat("New Venue: %s", getArenaRankName(player->arenaRank));
    printCenteredFormat("New Title: %s", getArenaTitle(player->arenaRank));

    if (player->arenaRank == 'E')
        printCentered("Reward: Rest Capacity +1");
    else if (player->arenaRank == 'D')
        printCentered("Reward: Rest Capacity +1");
    else if (player->arenaRank == 'C')
        printCentered("Reward: Rest Capacity +1");
    else if (player->arenaRank == 'A')
        printCentered("Reward: Skill Slots increased to 5");
    else if (player->arenaRank == 'S')
        printCentered("Reward: Skill Slots increased to 6");
    else if (player->arenaRank == 'X')
        printCentered("Reward: Skill Slots increased to 7");
    else if (player->arenaRank == 'Z')
        printCentered("Reward: Skill Slots increased to 8");
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
                printBlankLine();
                printCentered("===== FINAL ARENA CLEARED! =====");
                printCentered("You defeated the SSS 1v1 champion!");
                printCentered("Arena Status: WORLD APEX LEGEND");
            }
            else
            {
                printBlankLine();
                printCenteredFormat("Progress: %d/%d",
                                    player->arenaProgress,
                                    player->arenaRequiredWins);
                rankUpArena(player);
            }
        }
        else
        {
            printBlankLine();
            printCenteredFormat("Arena Progress: %d/%d",
                                player->arenaProgress,
                                player->arenaRequiredWins);
        }
    }
    else
    {
        printBlankLine();
        printCentered("Victory recorded.");
    }
}

int arenaBattle(Dog *player, char selectedRank)
{
    if (player->hp <= 0)
    {
        printCentered("You must rest before entering the Arena!");
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
        loadArenaClassCEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'B')
    {
        int enemyIndex = rand() % 10;
        loadArenaClassBEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'A')
    {
        int enemyIndex = rand() % 10;
        loadArenaClassAEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'S')
    {
        int enemyIndex = rand() % 11;
        loadArenaClassSEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'X')
    {
        int enemyIndex = rand() % 7;
        loadArenaClassSSEnemy(&enemy, enemyIndex);
    }
    else if (selectedRank == 'Z')
    {
        int enemyIndex = rand() % 4;
        loadArenaClassSSSEnemy(&enemy, enemyIndex);
    }
    else
    {
        system("cls");
        printCenteredFormat("Class %s real battle is not built yet.", getArenaClassName(selectedRank));
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

        //printBorder();
        printCentered("ARENA BATTLE");
        printCenteredFormat("Opponent: %s", enemy.name);
        printBlankLine();
        printCentered("--- YOUR TURN ---");
        printCentered("1. Attack    2. Defend    3. Heal    4. Surrender");
        printBlankLine();
        printf("%35sChoice: ", "");

        char input[10];
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 4)
        {
            printCentered("Invalid choice!");
            waitForEnter();
            continue;
        }

        if (choice == 1)
        {
            system("cls");
            displayBattleStatus(*player, enemy);

            printCentered("SKILLS");
            printBlankLine();

            int half = (player->maxSkillSlots + 1) / 2;

            for (int i = 0; i < half; i++)
            {
                int left = i;
                int right = i + half;
                char leftName[30];
                char rightName[30];
                char line[120];

                if (player->equipped[left] != -1)
                {
                    int idx = player->equipped[left];
                    strcpy(leftName, player->skills[idx].name);
                }
                else
                {
                    strcpy(leftName, "---");
                }

                if (right < player->maxSkillSlots)
                {
                    if (player->equipped[right] != -1)
                    {
                        int idx = player->equipped[right];
                        strcpy(rightName, player->skills[idx].name);
                    }
                    else
                    {
                        strcpy(rightName, "---");
                    }

                    sprintf(line, "%2d. %-20s   %2d. %-20s",
                            left + 1,
                            leftName,
                            right + 1,
                            rightName);
                }
                else
                {
                    sprintf(line, "%2d. %-20s", left + 1, leftName);
                }

                printCentered(line);
            }

            printBlankLine();
            printf("%35sChoice: ", "");
            fgets(input, sizeof(input), stdin);

            if (sscanf(input, "%d", &move) != 1 || move < 1 || move > player->maxSkillSlots)
            {
                printCentered("Invalid skill!");
                waitForEnter();
                continue;
            }

            int skillIdx = player->equipped[move - 1];
            if (skillIdx == -1)
            {
                printCentered("No skill equipped!");
                waitForEnter();
                continue;
            }

            // =========================
            // PLAYER SKILL COOLDOWN CHECK
            // Works even if old save has cooldown = 0
            // =========================
            if (strcmp(player->skills[skillIdx].name, "Hip Check") == 0 &&
                player->skills[skillIdx].cdLeft > 0)
            {
                printCentered("Hip Check is on cooldown! Use another move this turn.");
                waitForEnter();
                continue;
            }

            if (strcmp(player->skills[skillIdx].name, "Rolling Tackle") == 0 &&
                player->skills[skillIdx].cdLeft > 0)
            {
                printCentered("Rolling Tackle is on cooldown! Use another move this turn.");
                waitForEnter();
                continue;
            }

            Skill s = player->skills[skillIdx];

            system("cls");
            displayBattleStatus(*player, enemy);

            if (player->fatigue < s.cost)
            {
                printBlankLine();
                printCentered("Low energy! Weak attack!");
                player->fatigue = 0;
            }
            else
            {
                player->fatigue -= s.cost;
            }

            useSkill(player, &enemy, s);

            // =========================
            // SET PLAYER COOLDOWN AFTER USE
            // cdLeft = 2 blocks the next player turn once
            // =========================
            if (strcmp(player->skills[skillIdx].name, "Hip Check") == 0)
                player->skills[skillIdx].cdLeft = 2;
            else if (strcmp(player->skills[skillIdx].name, "Rolling Tackle") == 0)
                player->skills[skillIdx].cdLeft = 3;

            if (enemy.hp < 0)
                enemy.hp = 0;

            waitForEnter();
        }
        else if (choice == 2)
        {
            defending = 1;
            printCentered("Defending!");
            waitForEnter();
        }
        else if (choice == 3)
        {
            player->hp += 20;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printCentered("Healed +20 HP!");
            waitForEnter();
        }
        else if (choice == 4)
        {
            printBlankLine();
            printCentered("You surrendered the arena match.");
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

        // =========================
        // REDUCE PLAYER SKILL COOLDOWNS AFTER A FULL TURN
        // =========================
        for (int i = 0; i < player->skillCount; i++)
        {
            if (player->skills[i].cdLeft > 0)
                player->skills[i].cdLeft--;
        }
    }

    system("cls");
    displayBattleStatus(*player, enemy);

    if (player->hp <= 0)
    {
        printBlankLine();
        printCentered("YOU LOST THE ARENA MATCH...");
        player->arenaLosses++;
        player->fatigue = clampFatigue(player->fatigue + 15, player->maxFatigue);

        player->defense = baseDef;
        player->speed = baseSpd;

        waitForEnter();
        return 0;
    }

    printBlankLine();
    printCentered("YOU WIN THE ARENA MATCH!");
    printCenteredFormat("%s can no longer fight.", enemy.name);

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

    printBorder();
    printBlankLine();
    printCentered("ARENA STATS");
    printBlankLine();

    printf("%38s%-15s : Class %s - %s\n",
           "",
           "Highest Class",
           getArenaClassName(player->arenaRank),
           getArenaRankName(player->arenaRank));
    printf("%38s%-15s : %s\n", "", "Title", getArenaTitle(player->arenaRank));
    printf("%38s%-15s : %dW - %dL - %dD\n",
           "",
           "Record",
           player->arenaWins,
           player->arenaLosses,
           player->arenaDraws);

    if (isFinalArenaCleared(player))
    {
        printf("%38s%-15s : WORLD APEX LEGEND\n", "", "Arena Status");
    }
    else
    {
        printf("%38s%-15s : %d/%d (Class %s)\n",
               "",
               "Progress",
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

        printBorder();
        printBlankLine();
        printCentered(getArenaRankName(selectedRank));
        printCenteredFormat("Class %s - %s",
                            getArenaClassName(selectedRank),
                            getArenaTitle(selectedRank));
        printBlankLine();

        if (selectedRank == player->arenaRank)
        {
            if (isFinalArenaCleared(player))
                printCentered("Progress: CLEARED");
            else
                printCenteredFormat("Progress: %d/%d",
                                    player->arenaProgress,
                                    player->arenaRequiredWins);
        }
        else
        {
            printCentered("Progress: Cleared Class");
        }

        printBlankLine();
        printMenuItem(1, "Start Match");
        printMenuItem(2, "Back");
        printBlankLine();
        printf("%35sChoice: ", "");

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
            printCentered("Invalid choice!");
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

        printBorder();
        printBlankLine();
        printCentered("SELECT ARENA");
        printBlankLine();

        printMenuItem(1, "Open Grounds       [Class F]");

        if (isRankUnlocked(player->arenaRank, 'E'))
            printMenuItem(2, "Street Pit         [Class E]");

        if (isRankUnlocked(player->arenaRank, 'D'))
            printMenuItem(3, "Junkyard Arena     [Class D]");

        if (isRankUnlocked(player->arenaRank, 'C'))
            printMenuItem(4, "Victory Coliseum   [Class C]");

        if (isRankUnlocked(player->arenaRank, 'B'))
            printMenuItem(5, "Royal Octagon      [Class B]");

        if (isRankUnlocked(player->arenaRank, 'A'))
            printMenuItem(6, "Crown Arena        [Class A]");

        if (isRankUnlocked(player->arenaRank, 'S'))
            printMenuItem(7, "Legend Island      [Class S]");

        if (isRankUnlocked(player->arenaRank, 'X'))
            printMenuItem(8, "Mythic Dome        [Class SS]");

        if (isRankUnlocked(player->arenaRank, 'Z'))
            printMenuItem(9, "Final Apex         [Class SSS]");

        printBlankLine();
        printMenuItem(0, "Back");
        printBlankLine();
        printf("%35sChoice: ", "");

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
            printCentered("Invalid choice or class not unlocked yet!");
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

        printBorder();
        printBlankLine();
        printCentered("ARENA");
        printBlankLine();
        printMenuItem(1, "Fight Arena");
        printMenuItem(2, "Arena Stats");
        printMenuItem(3, "Exit");
        printBlankLine();
        printf("%35sChoice: ", "");

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
            printCentered("Invalid choice! Select 1-3 only.");
            waitForEnter();
        }
    }
}
