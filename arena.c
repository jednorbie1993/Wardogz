#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

// ================= ARENA NAMES =================

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
        case 'D': return 6;
        case 'C': return 6;
        case 'B': return 8;
        case 'A': return 8;
        case 'S': return 9;
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
        default: return 0;
    }
}

int isRankUnlocked(char highestRank, char selectedRank)
{
    return getRankIndex(selectedRank) <= getRankIndex(highestRank);
}

void rankUpArena(Dog *player)
{
    if (player->arenaRank == 'F')
        player->arenaRank = 'E';
    else if (player->arenaRank == 'E')
        player->arenaRank = 'D';
    else if (player->arenaRank == 'D')
        player->arenaRank = 'C';
    else if (player->arenaRank == 'C')
        player->arenaRank = 'B';
    else if (player->arenaRank == 'B')
        player->arenaRank = 'A';
    else if (player->arenaRank == 'A')
        player->arenaRank = 'S';
    else
    {
        printf("\nYou already cleared the highest Arena Class!\n");
        return;
    }

    player->arenaProgress = 0;
    player->arenaRequiredWins = getRequiredWins(player->arenaRank);

    printf("\n===== RANK UP! =====\n");
    printf("New Rank: Class %c\n", player->arenaRank);
    printf("New Venue: %s\n", getArenaRankName(player->arenaRank));
    printf("New Title: %s\n", getArenaTitle(player->arenaRank));
}

// ================= ARENA RECORD =================

void showArenaRecord(Dog *player)
{
    system("cls");

    printf("===== ARENA STATS =====\n\n");
    printf("Highest Class: %c - %s\n", player->arenaRank, getArenaRankName(player->arenaRank));
    printf("Title: %s\n", getArenaTitle(player->arenaRank));
    printf("Record: %dW - %dL - %dD\n",
           player->arenaWins,
           player->arenaLosses,
           player->arenaDraws);

    if (player->arenaRank == 'S')
        printf("Progress: CLEARED\n");
    else
        printf("Progress: %d/%d\n", player->arenaProgress, player->arenaRequiredWins);

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
        printf("Class %c - %s\n", selectedRank, getArenaTitle(selectedRank));

        if (selectedRank == player->arenaRank && player->arenaRank != 'S')
        {
            printf("Progress: %d/%d\n\n",
                   player->arenaProgress,
                   player->arenaRequiredWins);
        }
        else if (selectedRank == 'S' && player->arenaRank == 'S')
        {
            printf("Progress: CLEARED\n\n");
        }
        else
        {
            printf("Progress: Cleared Class\n\n");
        }

        printf("1. Win Test Battle\n");
        printf("2. Lose Test Battle\n");
        printf("3. Draw Test Battle\n");
        printf("4. Back\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1)
        {
            player->arenaWins++;

            printf("\nYou won the arena match!\n");

            // Progress only moves when fighting your current highest class.
            // Old unlocked classes are just normal repeat battles.
            if (selectedRank == player->arenaRank && player->arenaRank != 'S')
            {
                player->arenaProgress++;

                printf("Progress: %d/%d\n",
                       player->arenaProgress,
                       player->arenaRequiredWins);

                if (player->arenaProgress >= player->arenaRequiredWins)
                {
                    rankUpArena(player);
                }
            }
            else
            {
                printf("Victory recorded.\n");
            }

            waitForEnter();
        }
        else if (choice == 2)
        {
            player->arenaLosses++;
            printf("\nYou lost the arena match!\n");
            waitForEnter();
        }
        else if (choice == 3)
        {
            player->arenaDraws++;
            printf("\nThe arena match ended in a draw!\n");
            waitForEnter();
        }
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

        printf("\n8. Back\n");
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
        else if (choice == 8)
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
