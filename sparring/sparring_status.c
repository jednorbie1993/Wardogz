#include <stdio.h>
#include <string.h>
#include "sparring_status.h"
#include "../console.h"

void printSparringStatus(Dog *player, Dog *enemy)
{
    char playerLine[160];
    char enemyLine[160];
    char playerBar[11];
    char enemyBar[11];

    int playerFilled = (player->hp * 10) / player->maxHP;
    int enemyFilled = (enemy->hp * 10) / enemy->maxHP;

    if (playerFilled < 0) playerFilled = 0;
    if (playerFilled > 10) playerFilled = 10;
    if (enemyFilled < 0) enemyFilled = 0;
    if (enemyFilled > 10) enemyFilled = 10;

    for (int i = 0; i < 10; i++)
    {
        playerBar[i] = (i < playerFilled) ? '#' : '-';
        enemyBar[i] = (i < enemyFilled) ? '#' : '-';
    }

    playerBar[10] = '\0';
    enemyBar[10] = '\0';

    snprintf(playerLine, sizeof(playerLine),
             "%-10s: [%s] [%4d/%4d]",
             player->name, playerBar, player->hp, player->maxHP);

    char playerStatus[12];

    if (player->isStunned && player->stunTurns > 0)
        snprintf(playerStatus, sizeof(playerStatus), "(STUN %d)", player->stunTurns);
    else
        strcpy(playerStatus, "");

    snprintf(playerLine, sizeof(playerLine),
            "%-10s: [%s] [%4d/%4d] %-10s",
            player->name,
            playerBar,
            player->hp,
            player->maxHP,
            playerStatus);

    snprintf(enemyLine, sizeof(enemyLine),
             "%-10s: [%s] [%4d/%4d]",
             enemy->name, enemyBar, enemy->hp, enemy->maxHP);

    char enemyStatus[12];

    if (enemy->isStunned && enemy->stunTurns > 0)
        snprintf(enemyStatus, sizeof(enemyStatus), "(STUN %d)", enemy->stunTurns);
    else
        strcpy(enemyStatus, "");

    snprintf(enemyLine, sizeof(enemyLine),
            "%-10s: [%s] [%4d/%4d] %-10s",
            enemy->name,
            enemyBar,
            enemy->hp,
            enemy->maxHP,
            enemyStatus);

    printBorder();
    printCentered(playerLine);
    printCentered(enemyLine);
    printBorder();
    printBlankLine();
}

void updateDebuffs(Dog *d)
{
    if (d->accDebuffTurns > 0)
    {
        d->accDebuffTurns--;

        if (d->accDebuffTurns == 0)
        {
            d->accTemp = d->accuracy;
            printCenteredFormat("%s recovered from daze/stun!", d->name);
        }
    }

    if (d->isStunned && d->stunTurns > 0)
    {
        d->stunTurns--;

        if (d->stunTurns == 0)
        {
            d->isStunned = 0;
            printCenteredFormat("%s recovered from stun!", d->name);
        }
    }
}

void printHPBar(int hp, int maxHP)
{
    int bars = 10;
    int filled = (hp * bars) / maxHP;

    printf("[");

    for (int i = 0; i < bars; i++)
    {
        if (i < filled)
            printf("#");
        else
            printf("-");
    }

    printf("]");
}