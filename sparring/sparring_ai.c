#include "sparring_ai.h"
#include "../dog.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

int useSkill(Dog *user, Dog *enemy, Skill skill)
{

    // ================= HIT CHANCE CALC =================
    int hitChance = skill.accuracy + (user->accuracy / 5) - (enemy->speed / 6);
    if (hitChance < 20) hitChance = 20;
    if (hitChance > 95) hitChance = 95;

    // ================= DODGE CHECK (ONCE ONLY) =================
    int dodgeChance = enemy->speed / 8;
    if (dodgeChance > 40) dodgeChance = 40;

    int dodgeRoll = rand() % 100;

    if (dodgeRoll < dodgeChance)
    {
        printf("%s used %s but %s DODGED!\n", user->name, skill.name, enemy->name);
        return 0; // NO DAMAGE
    }

    // ================= DAMAGE SKILLS =================
    if (skill.type == SKILL_DAMAGE)
    {
        int base = skill.power + (user->attack / 15);
        int reduce = enemy->defense / 18;
        int variance = rand() % 6;
        int dmg = base - reduce + variance;

        if (dmg < 10) dmg = 10;
        enemy->hp -= dmg;

        if (rand() % 100 < 10)
        {
            dmg += 5;
            printf("CRITICAL HIT! +%d\n", 5);
        }

        printf("%s used %s! Dealt %d damage!\n", user->name, skill.name, dmg);

        // APPLY COOLDOWN
        for (int i = 0; i < user->skillCount; i++)
        {
            if (strcmp(user->skills[i].name, skill.name) == 0)
            {
                user->skills[i].cdLeft = user->skills[i].cooldown;
                break;
            }
        }

        // ================= ALL SPECIAL EFFECTS =================
        // BASIC PLAYER
        if (strcmp(skill.name, "Hip Check") == 0 && rand() % 100 < 40)
        {
            enemy->isStunned = 1; enemy->stunTurns = 2;
            printf("%s STUNNED!\n", enemy->name);
        }
        if (strcmp(skill.name, "Charge") == 0)
        {
            int recoil = dmg / 5; user->hp -= recoil;
            printf("%s recoil: %d\n", user->name, recoil);
        }

        // OSSAS
        if (strcmp(skill.name, "Wild Bite") == 0 && rand() % 100 < 35)
        { enemy->isBleeding = 1; enemy->bleedTurns = 3; printf("%s BLEEDING!\n", enemy->name); }
        if (strcmp(skill.name, "Rush Claw") == 0 && rand() % 100 < 25)
        { int extra = user->attack / 8; enemy->hp -= extra; printf("Extra slash! %d\n", extra); }
        if (strcmp(skill.name, "Headbutt") == 0 && rand() % 100 < 30)
        { enemy->isStunned = 1; enemy->stunTurns = 1; printf("%s dazed!\n", enemy->name); }
        if (strcmp(skill.name, "Rage Leap") == 0)
        { int recoil = dmg / 4; user->hp -= recoil; printf("%s recoil: %d\n", user->name, recoil); }

        // CHUBBY NEW MOVES
        if (strcmp(skill.name, "Body Slam") == 0)
        {
            user->defense += 4;  // Self buff
            printf("%s tougher!\n", user->name);
        }
        if (strcmp(skill.name, "Heavy Crush") == 0 && rand() % 100 < 30)
        {
            enemy->isStunned = 1; enemy->stunTurns = 1;
            printf("%s CRUSHED!\n", enemy->name);
        }
        // JEWARD
        if (strcmp(skill.name, "Counter Snap") == 0 && rand() % 100 < 30)
        { int counter = user->attack / 7; enemy->hp -= counter; printf("Counter! %d damage\n", counter); }

        // TINY NEW MOVES
        if (strcmp(skill.name, "Mind Bite") == 0 && rand() % 100 < 35)
        {
            enemy->isConfused = 1; enemy->confuseTurns = 2;
            printf("%s MIND BROKEN!\n", enemy->name);
        }
        if (strcmp(skill.name, "Brain Crush") == 0)
        {
            user->intelligence += 5;
            printf("%s smarter!\n", user->name);
        }
        // SNOOPY
        if (strcmp(skill.name, "Triple Bite") == 0)
        {
            int hits = 2 + (rand() % 2);
            for (int i = 0; i < hits; i++)
            { int extra = user->attack / 10; enemy->hp -= extra; printf("Extra bite #%d: %d\n", i+1, extra); }
        }
        if (strcmp(skill.name, "Wind Kick") == 0 && rand() % 100 < 30)
        { enemy->accuracy = (enemy->accuracy > 30) ? enemy->accuracy - 20 : 30; printf("%s vision blurred!\n", enemy->name); }

        return 1;
    }

    // ================= OTHER SKILL TYPES =================
    else if (skill.type == SKILL_HEAL)
    {
        int heal = (user->intelligence / 5) + skill.power;
        user->hp = (user->hp + heal > user->maxHP) ? user->maxHP : user->hp + heal;
        printf("%s healed %d HP!\n", user->name, heal);
        return 1;
    }
    else if (skill.type == SKILL_BUFF)
    {
        user->attack += skill.power;
        printf("%s attack UP!\n", user->name);
        return 1;
    }
    else if (skill.type == SKILL_DEBUFF)
    {
        enemy->attack -= skill.power;
        if (enemy->attack < 1) enemy->attack = 1;
        printf("%s attack DOWN!\n", enemy->name);
        return 1;
    }

    return 1;
}
