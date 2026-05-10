#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dog.h"
#include <windows.h>
#include "enemy.h"
#include "cinematic.h"

extern int systemLog;

int usePackAttack(Dog *user, Dog *target)
{
    int hits = 2;
    int total = 0;
    printf("%s calls pack! ", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = (user->attack * 0.35) + (rand() % 4); // nerfed: 0.45->0.35, rand()%6->%4
        target->hp -= dmg;
        total += dmg;
        printf("Hit%d:-%d ", i + 1, dmg);
    }
    printf("\n");
    return total;
}

int useAmbush(Dog *user, Dog *target)
{
    int dmg = user->attack * 1.2 + (rand() % 6); // nerfed: 1.3->1.2, rand()%8->%6
    target->hp -= dmg;
    printf("%s ambushes from shadows! CRIT! -%d\n", user->name, dmg);
    user->speed += 5; // nerfed: 8->5
    return dmg;
}

int useHowlDebuff(Dog *user, Dog *target)
{
    target->accuracyModifier -= 20; // nerfed: 25->20
    target->accDebuffTurns = 3;
    int dmg = user->attack / 5; // nerfed: /4->/5
    target->hp -= dmg;
    printf("%s HOWLS! Accuracy DOWN! Echo:-%d\n", user->name, dmg);
    return dmg;
}

int useFeralRush(Dog *user, Dog *target)
{
    int dmg = (user->attack * 1.05) + (rand() % 4); // nerfed: 1.1->1.05, rand()%6->%4
    target->hp -= dmg;
    target->bleedTurns += 2;
    target->bleedDamage = 1; // nerfed: 2->1
    printf("%s FERAL RUSH! -%d +BLEED!\n", user->name, dmg);
    return dmg;
}

// WILD SKILL FUNCTIONS - nerfed stats
void setEnemySkillsWild(Dog *enemy, int zoneIndex, int enemyLevel)
{
    enemy->skills[0].id = SKILL_PACK_ATTACK;
    strcpy(enemy->skills[0].name, "Pack Attack");
    enemy->skills[0].power = 10; // nerfed: 12->10

    enemy->skills[1].id = SKILL_AMBUSH;
    strcpy(enemy->skills[1].name, "Ambush");
    enemy->skills[1].power = 14; // nerfed: 17->14

    if (zoneIndex == 3 || zoneIndex == 5)
    {
        enemy->skills[2].id = SKILL_HOWL_DEBUFF;
        strcpy(enemy->skills[2].name, "Howl");
    }
    else
    {
        enemy->skills[2].id = SKILL_FERAL_RUSH;
        strcpy(enemy->skills[2].name, "Feral Rush");
    }

    enemy->skills[2].power = 12; // nerfed: 14->12

    enemy->numSkills = 3;

    enemy->attack += 1; // nerfed: 2->1
    enemy->speed += 1;
}

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
}

void enemyQuickAttack(Dog *player, Dog *enemy)
{
    int dmg = (enemy->attack / 8) + 3;

    if (dmg < 1)
        dmg = 1;

    player->hp -= dmg;
    player->hp = clamp(player->hp);

    printf("Enemy quickly attacks! You took %d damage!\n", dmg);
}

void setEnemyByZone(Dog *enemy, int zoneIndex, int i)
{
    // reset base stats muna
    createEnemy(enemy);

    if (zoneIndex == 0) // Back Alley
    {
        if (i == 0)
            strcpy(enemy->name, "Skinny Stray");
        else if (i == 1)
        {
            strcpy(enemy->name, "Scrap Fighter");
            enemy->attack += 3;
            enemy->defense += 2;
        }
        else
        {
            strcpy(enemy->name, "Alley Alpha");
            enemy->attack += 6;
            enemy->defense += 4;
            enemy->maxHP += 20;
        }
    }
    else if (zoneIndex == 1) // Junkyard
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Rust Hound");
            enemy->defense += 3;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Guard Dog");
            enemy->defense += 5;
        }
        else
        {
            strcpy(enemy->name, "Iron Jaw");
            enemy->defense += 8;
            enemy->maxHP += 25;
        }
    }
    else if (zoneIndex == 2) // Abandoned Block
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Night Stray");
            enemy->speed += 3;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Sneak Biter");
            enemy->accuracy += 5;
        }
        else
        {
            strcpy(enemy->name, "Street King");
            enemy->speed += 5;
            enemy->attack += 5;
        }
    }

    // =========================
    // WILD TERRITORY
    // =========================

    else if (zoneIndex == 3)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "River Scout");
            enemy->attack += 4;
            enemy->speed += 2;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Pack Hunter");
            enemy->attack += 6;
            enemy->speed += 3;
            enemy->maxHP += 10;
        }
        else
        {
            strcpy(enemy->name, "River Alpha");
            enemy->attack += 7;
            enemy->speed += 3;
            enemy->maxHP += 12;
            enemy->defense += 3;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }
    else if (zoneIndex == 4)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Forest Stalker");
            enemy->speed += 4;
            enemy->accuracy += 5;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Ambush Leader");
            enemy->speed += 6;
            enemy->accuracy += 8;
            enemy->attack += 3;
        }
        else
        {
            strcpy(enemy->name, "Shadow Pack");
            enemy->speed += 4;
            enemy->accuracy += 5;
            enemy->attack += 3;
            enemy->maxHP += 8;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }
    else if (zoneIndex == 5)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Bloodfang Scout");
            enemy->attack += 7;
            enemy->speed += 6;
            enemy->accuracy += 5;
        }
        else
        {
            strcpy(enemy->name, "Ravine Stalker");
            enemy->attack += 6;
            enemy->speed += 4;
            enemy->accuracy += 8;
            enemy->maxHP += 15;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }
    else if (zoneIndex == 6)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Trial Challenger");
            enemy->attack += 8;
            enemy->speed += 7;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Trial Hunter");
            enemy->attack += 9;
            enemy->speed += 8;
            enemy->accuracy += 6;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Trial Alpha");
            enemy->attack += 10;
            enemy->speed += 9;
            enemy->maxHP += 15;
        }
        else
        {
            strcpy(enemy->name, "Trial Beast");
            enemy->attack += 12;
            enemy->speed += 11;
            enemy->maxHP += 35;
            enemy->defense += 7;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }
    else if (zoneIndex == 7)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Mountain Guard");
            enemy->defense += 7;
            enemy->maxHP += 18;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Peak Warrior");
            enemy->defense += 10;
            enemy->maxHP += 25;
            enemy->attack += 5;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Summit Enforcer");
            enemy->defense += 15;
            enemy->maxHP += 35;
            enemy->attack += 8;
            enemy->speed += 3;
        }
        else
        {
            strcpy(enemy->name, "Mountain King");
            enemy->defense += 20;
            enemy->maxHP += 50;
            enemy->attack += 12;
            enemy->speed += 6;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }
    else
    {
        strcpy(enemy->name, "Unknown Stray");
        enemy->attack += 20;
        enemy->speed += 20;
        enemy->maxHP += 50;
    }

    // sync HP
    enemy->hp = enemy->maxHP;
}

int enemyAttack(Dog *player, Dog *enemy, int *defending)
{
    // WILD SKILLS - SAFE CHECK (Stage 1 has numSkills=0)
    if (enemy->numSkills >= 3)
    {
        // ZONE PASSIVES (nerfed chances)
        if (strstr(enemy->name, "Ravine") && rand() % 100 < 15) // nerfed: 25->15
        {
            printf("Ambush bonus! Speed increased!\n");
            enemy->speed += 3; // nerfed: 5->3
        }

        if (strstr(enemy->name, "Trial") && enemy->hp < enemy->maxHP / 2)
        {
            printf("Trial Rage activated!\n");
            enemy->attack += 3; // nerfed: 5->3
        }

        int skillChoice;

        // Zone-based AI (nerfed aggression)
        if (strstr(enemy->name, "Ravine"))
        {
            if (rand() % 100 < 50) // nerfed: 60->50
                skillChoice = 0;
            else
                skillChoice = rand() % 2;
        }
        else if (strstr(enemy->name, "Trial"))
        {
            if (enemy->hp < enemy->maxHP / 2)
                skillChoice = 1;
            else if (rand() % 100 < 45) // nerfed: 50->45
                skillChoice = 0;
            else
                skillChoice = rand() % 3;
        }
        else
        {
            if (rand() % 100 < 65) // nerfed: 70->65
                skillChoice = 0;
            else
                skillChoice = rand() % enemy->numSkills;
        }

        printf("%s snarls viciously...\n", enemy->name);

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
        default:
            printf("%s uses basic attack!\n", enemy->name);
            break;
        }

        // STATUS EFFECTS
        if (player->accuracyModifier < 0)
        {
            player->accuracy += 20; // nerfed recovery: 25->20
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

    // =========================
    // ENEMY PERSONALITY
    // =========================

    if (strstr(enemy->name, "Alpha") || strstr(enemy->name, "King"))
    {
        enemyDamage += 6;

        if (rand() % 100 < 20)
        {
            printf("\n");

            typeText(enemy->name, 30);
            typeText(" is ENRAGED!\n", 30);

            enemyDamage += 8;

            waitForEnter();

            // CUT FRAME
            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (strstr(enemy->name, "Iron") || strstr(enemy->name, "Guard"))
    {
        enemyDamage -= 2;

        if (rand() % 100 < 30)
        {
            printf("\nEnemy HARDENED!\n");

            enemyDamage = (enemyDamage * 70) / 100;

            waitForEnter();

            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (strstr(enemy->name, "Scrap") || strstr(enemy->name, "Fighter"))
    {
        if (enemy->hp < enemy->maxHP / 2)
        {
            enemyDamage += 5;

            printf("\nEnemy is DESPERATE!\n");

            waitForEnter();

            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (strstr(enemy->name, "Skinny") || strstr(enemy->name, "Stray"))
    {
        enemyDamage -= 2;
    }

    // =========================
    // MOVE SELECTION
    // =========================

    int moveType = rand() % 3;
    char *moveName = "Attack";

    if (moveType == 0)
    {
        enemyDamage += 5;
        moveName = "Bite";
    }
    else if (moveType == 1)
    {
        enemyDamage += 3;
        moveName = "Scratch";
    }
    else
    {
        enemyDamage += 8;
        moveName = "Lock Jaw";
    }

    // =========================
    // ATTACK FRAME
    // =========================

    printf("\n");

    typeText(enemy->name, 25);
    typeText(" used ", 20);
    typeText(moveName, 35);
    printf("!\n");

    cinematicDots("Enemy attacking");

    // DAMAGE CALC
    enemyDamage += rand() % 5;
    enemyDamage -= player->defense / 40;
    if (enemyDamage < 3)
        enemyDamage = 3;

    // HIT CHANCE
    int dodgeChance = player->speed * 2;
    int hitChance = enemy->accuracy - dodgeChance;
    hitChance = (hitChance < 70) ? 70 : (hitChance > 95 ? 95 : hitChance);

    // ENEMY BLEED FIRST
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

    // ENEMY CONFUSION
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
        if (enemy->confuseTurns <= 0)
            enemy->isConfused = 0;
    }

    // HIT OR MISS
    int roll = rand() % 100;
    if (roll >= hitChance)
    {
        printf("Enemy MISSED!\n");
        waitForEnter();
        return -1;
    }

    // DEFEND/COUNTER SYSTEM
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
        // OSSAS COUNTER TRAP
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

        // FINAL DAMAGE
        player->hp -= enemyDamage;
        player->hp = clamp(player->hp);
        printf("%s dealt %d damage!\n", enemy->name, enemyDamage);
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