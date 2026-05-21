#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../dog.h"
#include <windows.h>
#include "enemy.h"
#include "../cinematic.h"

extern int systemLog;

// =========================
// CREATE ENEMY
// =========================
void createEnemy(Dog *e)
{
    strcpy(e->name, "Wild Dog");

    e->hp = 100;
    e->maxHP = 100;
    e->attack = 10;
    e->defense = 65;

    e->speed = 90;
    e->accuracy = 95;
    e->intelligence = 55;

    e->isConfused = 0;
    e->confuseTurns = 0;

    e->isBleeding = 0;
    e->bleedTurns = 0;
    e->bleedDamage = 0;

    e->accuracyModifier = 0;
    e->numSkills = 0;

    e->isConfused = 0;
    e->confuseTurns = 0;

    // NEW DEFAULTS
    e->zoneType = ZONE_NORMAL;
    e->personalityType = PERSONALITY_NORMAL;
}

// =========================
// QUICK ATTACK
// =========================
void enemyQuickAttack(Dog *player, Dog *enemy)
{
    int dmg = (enemy->attack / 8) + 3;

    if (dmg < 1)
        dmg = 1;

    player->hp -= dmg;
    player->hp = clamp(player->hp);

    printf("Enemy quickly attacks! You took %d damage!\n", dmg);
}

// =========================
// MAIN ENEMY ATTACK
// =========================
int enemyAttack(Dog *player, Dog *enemy, int *defending)
{

    // =========================
    // WILD SKILLS SYSTEM
    // =========================
    if (enemy->numSkills >= 3 && enemy->zoneType != ZONE_CITY)
    {
        if (enemy->zoneType == ZONE_RAVINE && rand() % 100 < 15)
        {
            printf("Ambush bonus! Speed increased!\n");
            enemy->speed += 3;
        }

        if (enemy->zoneType == ZONE_TRIAL && enemy->hp < enemy->maxHP / 2)
        {
            printf("Trial Rage activated!\n");
            enemy->attack += 3;
        }

        int skillChoice = 0;

        // =========================
        // ZONE: RAVINE
        // =========================
        if (enemy->zoneType == ZONE_RAVINE)
        {
            int pool[] = {0, 1};
            skillChoice = pool[rand() % 2];
        }

        // =========================
        // ZONE: TRIAL
        // =========================
        else if (enemy->zoneType == ZONE_TRIAL)
        {
            if (enemy->hp < enemy->maxHP / 2)
                skillChoice = 1;
            else
            {
                int pool[] = {0, 1, 2};
                skillChoice = pool[rand() % 3];
            }
        }

        // =========================
        // ZONE: MILITARY (FIXED PROPERLY)
        // =========================
        else if (enemy->zoneType == ZONE_MILITARY)
        {
            int r = rand() % 100;

            if (enemy->hp < enemy->maxHP * 0.2)
                skillChoice = 3; // Self Destruct
            else if (r < 25)
                skillChoice = 0; // Precision Shot
            else if (r < 45)
                skillChoice = 1; // Tactical Guard
            else if (r < 60)
                skillChoice = 2; // Reinforcement
            else if (r < 80)
                skillChoice = 4; // Barrage Fire
            else
                skillChoice = 5; // Military Charge
        }

        // =========================
        // ZONE: BIO-LAB (ADD THIS)
        // =========================
        else if (enemy->zoneType == ZONE_BIOLAB)
        {
            int r = rand() % 100;

            if (enemy->hp < enemy->maxHP * 0.25)
                skillChoice = 3; // Contained Explosion
            else if (r < 20)
                skillChoice = 0; // Mutation Surge
            else if (r < 35)
                skillChoice = 1; // Bio Shield
            else if (r < 50)
                skillChoice = 2; // Cell Regeneration
            else if (r < 70)
                skillChoice = 4; // Acid Spit
            else
                skillChoice = 5; // Neuro Toxin
        }

        // =========================
        // DEFAULT SAFETY
        // =========================
        else
        {
            skillChoice = rand() % enemy->numSkills;
        }

        printf("%s snarls viciously...\n", enemy->name);

        // SAFETY CHECK (IMPORTANT)
        if (skillChoice < 0 || skillChoice >= MAX_SKILLS)
        {
            printf("%s hesitates...\n", enemy->name);
            skillChoice = 0;
        }

        SkillID skillId = enemy->skills[skillChoice].id;

        switch (skillId)
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

        // =========================
        // MILITARY SKILLS
        // =========================
        case SKILL_PRECISION_SHOT:
            usePrecisionShot(enemy, player);
            break;

        case SKILL_TACTICAL_GUARD:
            useTacticalGuard(enemy, player);
            break;

        case SKILL_REINFORCEMENT:
            useReinforcement(enemy, player);
            break;

        case SKILL_SELF_DESTRUCT:
            useSelfDestruct(enemy, player);
            break;

        case SKILL_BARRAGE_FIRE:
            useBarrageFire(enemy, player);
            break;

        case SKILL_MILITARY_CHARGE:
            useMilitaryCharge(enemy, player);
            break;
        // =========================
        // BIO LAB SKILLS (ADD THIS)
        // =========================
        case SKILL_MUTATION_SURGE:
            useMutationSurge(enemy, player);
            break;

        case SKILL_BIO_SHIELD:
            useBioShield(enemy, player);
            break;

        case SKILL_CELL_REGEN:
            useCellRegen(enemy, player);
            break;

        case SKILL_CONTAINED_EXPLOSION:
            useContainedExplosion(enemy, player);
            break;

        case SKILL_ACID_SPIT:
            useAcidSpit(enemy, player);
            break;

        case SKILL_NEURO_TOXIN:
            useNeuroToxin(enemy, player);
            break;    

        default:
            printf("%s uses basic attack!\n", enemy->name);
            break;
        }

        if (player->accuracyModifier < 0)
        {
            player->accuracy += 20;
            player->accuracyModifier = 0;
            printf("Accuracy recovering...\n");
        }

        if (player->bleedTurns > 0)
        {
            player->hp -= player->bleedDamage;
            player->hp = clamp(player->hp);

            printf("Bleed: -%d HP\n", player->bleedDamage);

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

    // =========================
    // CINEMATIC ENEMY TURN
    // =========================
    system("cls");

    displayBattleStatus(*player, *enemy);

    printf("\n--- ENEMY TURN ---\n");

    int enemyDamage = (enemy->attack / 6) + 4;

    if (enemy->zoneType == ZONE_CITY)
    {
        handleStage1EnemyBehavior(player, enemy, &enemyDamage);
    }
    else
    {
        handleStage1EnemyBehavior(player, enemy, &enemyDamage);
    }

    enemyDamage += rand() % 5;
    enemyDamage -= player->defense / 40;

    if (enemyDamage < 3)
        enemyDamage = 3;

    int dodgeChance = player->speed * 2;
    int hitChance = enemy->accuracy - dodgeChance;

    hitChance = (hitChance < 70) ? 70 : (hitChance > 95 ? 95 : hitChance);

    // =========================
    // BLEED CHECK
    // =========================
    if (enemy->isBleeding && enemy->bleedTurns > 0)
    {
        int bleedDmg = (rand() % 5) + 3;

        printf("Enemy BLEEDING: -%d HP\n", bleedDmg);

        enemy->hp -= bleedDmg;
        enemy->hp = clamp(enemy->hp);

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

    // =========================
    // CONFUSION CHECK
    // =========================
    if (enemy->isConfused && enemy->confuseTurns > 0)
    {
        printf("%s is CONFUSED!\n", enemy->name);

        if (rand() % 100 < 50)
        {
            printf("Confused enemy MISSED!\n");

            enemy->confuseTurns--;

            if (enemy->confuseTurns <= 0)
                enemy->isConfused = 0;

            waitForEnter();
            return -1;
        }

        enemy->confuseTurns--;

        if (enemy->confuseTurns <= 0)
            enemy->isConfused = 0;
    }

    // =========================
    // HIT CHECK
    // =========================
    int roll = rand() % 100;

    if (roll >= hitChance)
    {
        printf("Enemy MISSED!\n");
        waitForEnter();
        return -1;
    }

    // =========================
    // DEFEND SYSTEM
    // =========================
    if (*defending)
    {
        int counterChance = player->intelligence / 2;

        if (player->fatigue <= 20)
            counterChance = 0;

        if (counterChance > 25)
            counterChance = 25;

        if (rand() % 100 < counterChance)
        {
            int counterDmg = (player->attack / 2) + (player->intelligence / 4);

            printf("COUNTER ATTACK!\n");
            printf("Counter: %d damage!\n", counterDmg);

            enemy->hp -= counterDmg;
            enemy->hp = clamp(enemy->hp);

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

            player->hp -= enemyDamage;
            player->hp = clamp(player->hp);

            printf("Defended! Took %d damage\n", enemyDamage);
        }

        *defending = 0;
    }
    else
    {
        if (player->isCountering && player->counterDamage > 0)
        {
            int triggerChance = 65 + (player->intelligence / 20);

            if (triggerChance > 85)
                triggerChance = 85;

            if (rand() % 100 < triggerChance)
            {
                printf("OSSAS COUNTER TRIGGERS!\n");

                int reflect = player->counterDamage;

                if (reflect > enemy->hp)
                    reflect = enemy->hp;

                enemy->hp -= reflect;
                enemy->hp = clamp(enemy->hp);

                printf("Reflected %d damage!\n", reflect);

                enemyDamage /= 2;
            }
            else
            {
                printf("Ossas Counter failed!\n");
            }

            player->isCountering = 0;
            player->counterDamage = 0;
        }

        player->hp -= enemyDamage;
        player->hp = clamp(player->hp);

        printf("%s dealt %d damage!\n", enemy->name, enemyDamage);
    }

    // =========================
    // END CHECK
    // =========================
    if (player->hp <= 0)
    {
        printf("You were defeated...\n");
        waitForEnter();
        return 0;
    }

    waitForEnter();
    return -1;
}