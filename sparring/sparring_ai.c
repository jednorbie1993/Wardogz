#include "sparring_ai.h"
#include "../dog.h"
#include <string.h>
#include <stdlib.h>

int chooseEnemyMove(Dog *enemy, Dog *player, int type)
{
    int candidates[10];
    int count = 0;

    int mode;

    // ================= MODE DECISION =================
    if (enemy->hp < enemy->maxHP * 0.35)
        mode = CAUTIOUS;
    else if (player->hp < player->maxHP * 0.30)
        mode = AGGRESSIVE;
    else
        mode = BALANCED;

    // ================= TYPE-SPECIFIC BEHAVIOR =================
    if (type == 1) // OSSAS - Always aggressive
        mode = AGGRESSIVE;
    else if (type == 2) // CHUBBY - Defensive first
    {
        if (enemy->hp > enemy->maxHP * 0.7)
            mode = BALANCED;
        else
            mode = CAUTIOUS;
    }
    else if (type == 3) // JEWARD - Precision focus
        mode = BALANCED;
    else if (type == 4) // TINY - Smart decisions
    {
        if (player->hp < player->maxHP * 0.5)
            mode = AGGRESSIVE;
        else if (enemy->hp < enemy->maxHP * 0.5)
            mode = CAUTIOUS;
        else
            mode = BALANCED;
    }
    else if (type == 5) // SNOOPY - Aggressive rotation
        mode = AGGRESSIVE;

    // ALL DOGS: HP-BASED BUFF PRIORITY
    if (enemy->hp < enemy->maxHP * 0.5)
    {
        if (mode != CAUTIOUS) mode = BALANCED;
    }

    // ================= PICK SKILLS =================
    for (int i = 0; i < enemy->skillCount; i++)
    {
        if (enemy->skills[i].cdLeft > 0)
            continue;

        int score = enemy->skills[i].power;

        // ================= MODE BEHAVIOR =================
        if (mode == AGGRESSIVE)
            score += 25;
        else if (mode == BALANCED)
            score += rand() % 15;
        else if (mode == CAUTIOUS)
        {
            if (enemy->skills[i].type == SKILL_HEAL || enemy->skills[i].type == SKILL_BUFF)
                score += 35;
        }

        // ================= DOG-SPECIFIC SMART AI =================

        // OSSAS: Pure aggression, favors high damage
        if (type == 1)
        {
            if (strcmp(enemy->skills[i].name, "Rage Leap") == 0 && enemy->skills[i].cdLeft == 0)
                score += 28;
            else if (strcmp(enemy->skills[i].name, "Wild Bite") == 0)
                score += 26;
            else if (strcmp(enemy->skills[i].name, "Rush Claw") == 0)
                score += 24;
            else if (strcmp(enemy->skills[i].name, "Headbutt") == 0)
                score += 22;
        }

        // CHUBBY: Damage buffs first
        else if (type == 2)
        {
            if (strcmp(enemy->skills[i].name, "Body Slam") == 0)
                score += 28;
            else if (strcmp(enemy->skills[i].name, "Heavy Crush") == 0 && enemy->skills[i].cdLeft == 0)
                score += 27;
            else if (strcmp(enemy->skills[i].name, "Slow Slam") == 0)
                score += 25 + (rand() % 3);
            else if (strcmp(enemy->skills[i].name, "Guard Bash") == 0)
                score += 23;
        }
        //jeward
        else if (type == 3)
        {
            if (strcmp(enemy->skills[i].name, "Precision Bite") == 0)
                score += 28;
            else if (strcmp(enemy->skills[i].name, "Counter Snap") == 0)
                score += 25;
            else if (strcmp(enemy->skills[i].name, "Eye Strike") == 0)
                score += 23;
            else if (strcmp(enemy->skills[i].name, "Focus Jab") == 0)
                score += 21 + (rand() % 3);
        }

        // TINY: Damage + mind control
        else if (type == 4)
        {
            if (strcmp(enemy->skills[i].name, "Brain Crush") == 0 && enemy->skills[i].cdLeft == 0)
                score += 28;
            else if (strcmp(enemy->skills[i].name, "Mind Bite") == 0)
                score += 26;
            else if (strcmp(enemy->skills[i].name, "Quick Dodge Bite") == 0)
                score += 25 + (rand() % 3);
            else if (strcmp(enemy->skills[i].name, "Confuse Peck") == 0)
                score += 24;
        }

        // SNOOPY: rotation
        else if (type == 5)
        {
            if (strcmp(enemy->skills[i].name, "Triple Bite") == 0 && enemy->skills[i].cdLeft == 0)
                score += 25 + (rand() % 5);
            else if (strcmp(enemy->skills[i].name, "Wind Kick") == 0)
                score += 24 + (rand() % 3);
            else if (strcmp(enemy->skills[i].name, "Flash Dodge") == 0)
            {
                if (enemy->hp < enemy->maxHP * 0.6)
                    score += 26;
                else
                    score += 23 + (rand() % 3);
            }
            else if (strcmp(enemy->skills[i].name, "Speed Dash") == 0 && enemy->skills[i].cdLeft == 0)
                score += 24 + (rand() % 4);
        }

        candidates[count] = i;
        enemy->skills[i].aiScore = score;
        count++;
    }

    if (count == 0)
        return 0;

    // ================= PICK BEST WITH TIES BROKEN BY RANDOM =================
    int best = candidates[0];
    int bestScore = enemy->skills[best].aiScore;

    for (int i = 1; i < count; i++)
    {
        int idx = candidates[i];
        if (enemy->skills[idx].aiScore > bestScore ||
            (enemy->skills[idx].aiScore == bestScore && rand() % 3 == 0))  // 33% tiebreaker
        {
            best = idx;
            bestScore = enemy->skills[idx].aiScore;
        }
    }

    return best;
}