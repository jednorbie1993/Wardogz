#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dog.h"
#include <windows.h>

extern int systemLog;

int enemyAttack(Dog *player, Dog *enemy, int *defending)
{
    system("cls");
    printf("\n--- ENEMY TURN ---\n");

    // 🔥 WILD SKILLS - SAFE CHECK (Stage 1 has numSkills=0)
    if (enemy->numSkills >= 3) 
    {
        printf("🐺 %s snarls viciously...\n", enemy->name);
        int skillChoice = rand() % enemy->numSkills;
        SkillID skillId = enemy->skills[skillChoice].id;
        
        switch(skillId) 
        {
            case SKILL_PACK_ATTACK:
                usePackAttack(enemy, player);
                break;
            case SKILL_AMBUSH:
                useAmbush(enemy, player);
                break;
            case SKILL_HOWL_DEBUFF:
                useHowlDebuff(enemy, player);
                break;
            case SKILL_FERAL_RUSH:
                useFeralRush(enemy, player);
                break;
            default:
                printf("%s uses basic attack!\n", enemy->name);
                break;
        }
        
        // 🔥 STATUS EFFECTS
        if (player->accuracyModifier < 0) 
        {
            player->accuracy += 25;
            player->accuracyModifier = 0;
            printf("Accuracy recovering...\n");
        }
        
        if (player->bleedTurns > 0) 
        {
            player->hp -= player->bleedDamage;
            player->hp = clamp(player->hp);
            printf("🩸 Bleed: -%d HP\n", player->bleedDamage);
            player->bleedTurns--;
            if (player->bleedTurns <= 0) 
            {
                player->bleedDamage = 0;
                printf("Bleeding stopped.\n");
            }
        }
        
        waitForEnter();
        return -1;
    }

    // 🔥 REGULAR ENEMY ATTACK
    int enemyDamage = (enemy->attack / 6) + 4;

    // ================= ENEMY PERSONALITY =================
    if (strstr(enemy->name, "Alpha") || strstr(enemy->name, "King"))
    {
        enemyDamage += 6;
        if (rand() % 100 < 20) 
        {
            printf("Enemy is ENRAGED!\n");
            enemyDamage += 8;
        }
    }
    else if (strstr(enemy->name, "Iron") || strstr(enemy->name, "Guard"))
    {
        enemyDamage -= 2;
        if (rand() % 100 < 30)
        {
            printf("Enemy HARDENED!\n");
            enemyDamage = (enemyDamage * 70) / 100;
        }
    }
    else if (strstr(enemy->name, "Scrap") || strstr(enemy->name, "Fighter"))
    {
        if (enemy->hp < enemy->maxHP / 2)
        {
            enemyDamage += 5;
            printf("Enemy is DESPERATE!\n");
        }
    }
    else if (strstr(enemy->name, "Skinny") || strstr(enemy->name, "Stray"))
    {
        enemyDamage -= 2;
    }

    // ================= ATTACK MOVE =================
    int moveType = rand() % 3;
    char *moveName = "Attack";
    
    if (moveType == 0) { enemyDamage += 5; moveName = "Bite"; }
    else if (moveType == 1) { enemyDamage += 3; moveName = "Scratch"; }
    else { enemyDamage += 8; moveName = "Lock Jaw"; }

    printf("%s used **%s**!\n", enemy->name, moveName);

    // 🔥 ATTACK ANIMATION
    printf("Attacking");
    for (int i = 0; i < 3; i++) 
    {
        printf("."); fflush(stdout); Sleep(120);
    }
    printf("\n");

    // ================= DAMAGE CALC =================
    enemyDamage += rand() % 6;
    enemyDamage -= player->defense / 25;
    if (enemyDamage < 1) enemyDamage = 1;

    // ================= HIT CHANCE =================
    int dodgeChance = player->speed * 2;
    int hitChance = enemy->accuracy - dodgeChance;
    hitChance = (hitChance < 70) ? 70 : (hitChance > 95 ? 95 : hitChance);

    // 🔥 ENEMY BLEED FIRST
    if (enemy->isBleeding && enemy->bleedTurns > 0)
    {
        int bleedDmg = (rand() % 5) + 3;
        printf("Enemy BLEEDING: -%d HP\n", bleedDmg);
        enemy->hp -= bleedDmg; enemy->hp = clamp(enemy->hp);
        enemy->bleedTurns--;
        
        if (enemy->bleedTurns <= 0) 
        {
            enemy->isBleeding = 0;
            printf("Bleeding stopped.\n");
        }
        
        waitForEnter();
        if (enemy->hp <= 0) 
        {
            printf("Enemy DIED from bleeding!\n");
            return 1;
        }
    }

    // 🔥 ENEMY CONFUSION
    if (enemy->isConfused && enemy->confuseTurns > 0)
    {
        printf("%s is CONFUSED!\n", enemy->name);
        if (rand() % 100 < 50)
        {
            printf("Confused enemy MISSED!\n");
            enemy->confuseTurns--;
            if (enemy->confuseTurns <= 0) 
            {
                enemy->isConfused = 0;
                printf("Enemy recovered!\n");
            }
            waitForEnter();
            return -1;
        }
        enemy->confuseTurns--;
        if (enemy->confuseTurns <= 0) enemy->isConfused = 0;
    }

    // 🔥 HIT OR MISS
    int roll = rand() % 100;
    if (roll >= hitChance)
    {
        printf("Enemy MISSED!\n");
        waitForEnter();
        return -1;
    }

    // 🔥 DEFEND/COUNTER SYSTEM
    if (*defending)
    {
        int counterChance = player->intelligence / 2;
        if (player->fatigue <= 20) counterChance = 0;
        if (counterChance > 25) counterChance = 25;

        if (rand() % 100 < counterChance)
        {
            int counterDmg = (player->attack / 2) + (player->intelligence / 4);
            printf("✅ COUNTER ATTACK!\n");
            printf("Counter: %d damage!\n", counterDmg);
            
            enemy->hp -= counterDmg; enemy->hp = clamp(enemy->hp);
            if (enemy->hp <= 0) 
            {
                printf("Enemy defeated by COUNTER!\n");
                waitForEnter();
                return 1;
            }
        }
        else
        {
            enemyDamage = (enemyDamage * 60) / 100;
            player->hp -= enemyDamage; player->hp = clamp(player->hp);
            printf("🛡️ Defended! Took %d damage\n", enemyDamage);
        }
        *defending = 0;
    }
    else // 🔥 NORMAL HIT
    {
        // OSSAS COUNTER TRAP
        if (player->isCountering && player->counterDamage > 0) 
        {
            int triggerChance = 65 + (player->intelligence / 20);
            if (triggerChance > 85) triggerChance = 85;
            
            if (rand() % 100 < triggerChance)
            {
                printf("🛡️ OSSAS COUNTER TRIGGERS!\n");
                int reflect = player->counterDamage;
                if (reflect > enemy->hp) reflect = enemy->hp;
                
                enemy->hp -= reflect; enemy->hp = clamp(enemy->hp);
                printf("Reflected %d damage!\n", reflect);
                enemyDamage /= 2;
            }
            else
            {
                printf("❌ Ossas Counter failed!\n");
            }
            player->isCountering = 0;
            player->counterDamage = 0;
        }
        
        // FINAL DAMAGE
        player->hp -= enemyDamage; player->hp = clamp(player->hp);
        printf("💥 %s dealt %d damage!\n", enemy->name, enemyDamage);
    }

    if (player->hp <= 0)
    {
        printf("You were defeated...\n");
        waitForEnter();
        return 0;
    }

    waitForEnter();
    return -1;
}