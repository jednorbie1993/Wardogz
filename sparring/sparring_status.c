#include <stdio.h>
#include "sparring_status.h"

void printSparringStatus(Dog *player, Dog *enemy)
{
    printf("YOU: ");
    printHPBar(player->hp, player->maxHP);
    printf(" [%d/%d]", player->hp, player->maxHP);

    if (player->accDebuffTurns > 0)
        printf(" (DAZED %d)", player->accDebuffTurns);

    if (player->isStunned && player->stunTurns > 0)
        printf(" (STUN %d)", player->stunTurns);

    printf("\n");

    printf("ENEMY: ");
    printHPBar(enemy->hp, enemy->maxHP);
    printf(" [%d/%d]", enemy->hp, enemy->maxHP);

    if (enemy->accDebuffTurns > 0)
        printf(" (DAZED %d)", enemy->accDebuffTurns);

    if (enemy->isStunned && enemy->stunTurns > 0)
        printf(" (STUN %d)", enemy->stunTurns);

    printf("\n\n");
}

void updateDebuffs(Dog *d)
{
    if (d->accDebuffTurns > 0)
    {
        d->accDebuffTurns--;

        if (d->accDebuffTurns == 0)
        {
            d->accTemp = d->accuracy;
            printf("%s recovered from daze/stun!\n", d->name);
        }
    }

    if (d->isStunned && d->stunTurns > 0)
    {
        d->stunTurns--;

        if (d->stunTurns == 0)
        {
            d->isStunned = 0;
            printf("%s recovered from stun!\n", d->name);
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