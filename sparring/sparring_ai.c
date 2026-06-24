#include "sparring_ai.h"
#include "../dog.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "characters/ossas.h"
#include "characters/chubby.h"
#include "characters/jeward.h"
#include "characters/snoop.h"
#include "characters/tiny.h"
#include "../skill.h"

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
    int hitChance = 75 + ((user->accuracy - enemy->speed) / 25);

    // skill accuracy bonus/penalty
    hitChance += (skill.accuracy - 80) / 4;

    if (hitChance < 45)
        hitChance = 45;

    if (hitChance > 95)
        hitChance = 95;

    int roll = rand() % 100;

    if (roll >= hitChance)
    {
        printf("%s used %s but MISSED!\n", user->name, skill.name);
        return 0; // NO DAMAGE
    }

    // ================= DAMAGE SKILLS =================
    if (skill.type == SKILL_DAMAGE)
    {
        /*int base = skill.power + (user->attack / 15);
        int reduce = enemy->defense / 18;
        int variance = rand() % 6;
        int dmg = base - reduce + variance;*/
        int diff = user->attack - enemy->defense;

        int dmg = 70 + (diff / 10) + skill.power + ((rand() % 21) - 10);

        if (dmg < 30)
            dmg = 30;

        if (dmg > 140)
            dmg = 140;

        if (rand() % 100 < 10)
        {
            dmg += dmg / 2;

            if (dmg > 180)
                dmg = 180;

            printf("CRITICAL HIT!\n");
        }

        int finalDamage = dmg;

        applySpecialEffects(user, enemy, skill, &finalDamage);

        enemy->hp -= finalDamage;

        if (enemy->hp < 0)
            enemy->hp = 0;

        printf("%s used %s! Dealt %d damage!\n", user->name, skill.name, finalDamage);
            
        /*if (rand() % 100 < 10)
        {
            dmg += 5;
            printf("CRITICAL HIT! +%d\n", 5);
        }*/

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
        // CHARACTER SPECIAL EFFECTS

        if (strcmp(user->name, "Ossas") == 0)
        {
            applyOssasEffect(user, enemy, skill, dmg);
        }
        else if (strcmp(user->name, "Chubby") == 0)
        {
            applyChubbyEffect(user, enemy, skill, dmg);
        }
        else if (strcmp(user->name, "Jeward") == 0)
        {
            applyJewardEffect(user, enemy, skill, dmg);
        }
        else if (strcmp(user->name, "Tiny") == 0)
        {
            applyTinyEffect(user, enemy, skill, dmg);
        }
        else if (strcmp(user->name, "Snoopy") == 0)
        {
            applySnoopyEffect(user, enemy, skill, dmg);
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
