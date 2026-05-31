#include "sparring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../dog.h"
#include "../cinematic.h"
#include "../battle.h"
#include "characters/ossas.h"
#include "characters/chubby.h"
#include "characters/snoop.h"
#include "characters/tiny.h"
#include "characters/jeward.h"
#include "sparring_unlocks.h"
#include "sparring_ai.h"

void initSparringProgress(Dog *d) {
    for (int i = 0; i < 5; i++) {
        d->sparringProgress[i] = 0;
    }
}

void updateSparringProgress(Dog *d, int enemyIndex, int win) {
    system("cls");

    // HARDCODE THE NAMES ARRAY HERE
    const char* sparringEnemies[5] = {"Ossas", "Chubby", "Jewar", "Tiny", "Snoopy"};

    printf("=== SPARRING RESULTS ===\n");

    if (win) {
        d->sparringProgress[enemyIndex]++;
        printf("WIN! %s progress: %d/10", sparringEnemies[enemyIndex], d->sparringProgress[enemyIndex]);

        if (d->sparringProgress[enemyIndex] == 10) {
            printf("  TECHNIQUE UNLOCKED!\n");
        } else {
            printf("\n");
        }
    } else {
        printf("LOSS! %s progress: %d/10 (no gain)\n", sparringEnemies[enemyIndex], d->sparringProgress[enemyIndex]);
    }

    // Show all progress
    printf("\n--- ALL PROGRESS ---\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %d/10", sparringEnemies[i], d->sparringProgress[i]);
        if (d->sparringProgress[i] == 10) printf(" [DONE]");
        printf("\n");
    }

    checkSparringUnlock(d);
    waitForEnter();
}

void updateCooldowns(Dog *d)
{
    for (int i = 0; i < d->skillCount; i++)
    {
        if (d->skills[i].cdLeft > 0)
            d->skills[i].cdLeft--;
    }
}

void applySparReward(Dog *player, int type)
{
    if (type == 1)
        player->attack += 1;
    if (type == 2)
        player->defense += 1;
    if (type == 3)
        player->accuracy += 1;
    if (type == 4)
        player->intelligence += 1;
    if (type == 5)
        player->speed += 1;

    printf("Spar reward applied!\n");
    waitForEnter();
}

void sparringMenu(Dog *player)
{
    int t;

    while (1)
    {
        system("cls");

        printf("==== SPARRING TRAINING ====\n");
        // SHOW PROGRESS
        printf("1. Ossas     (%d/10)", player->sparringProgress[0]);
        if (player->sparringProgress[0] == 10) printf(" [DONE]");
        printf(" (Attack Training)\n");

        printf("2. Chubby    (%d/10)", player->sparringProgress[1]);
        if (player->sparringProgress[1] == 10) printf(" [DONE]");
        printf(" (Defense Training)\n");

        printf("3. Jewar     (%d/10)", player->sparringProgress[2]);
        if (player->sparringProgress[2] == 10) printf(" [DONE]");
        printf(" (Accuracy Training)\n");

        printf("4. Tiny      (%d/10)", player->sparringProgress[3]);
        if (player->sparringProgress[3] == 10) printf(" [DONE]");
        printf(" (Intelligence Training)\n");

        printf("5. Snoopy    (%d/10)", player->sparringProgress[4]);
        if (player->sparringProgress[4] == 10) printf(" [DONE]");
        printf(" (Speed Training)\n");

        printf("6. Return\n");
        printf("Choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (input[0] == '\0' || !isdigit(input[0]))
        {
            printf("Invalid input!\n");
            waitForEnter();
            continue;
        }

        t = atoi(input);

        if (t == 6)
        {
            system("cls");
            break;
        }

        if (t < 1 || t > 5)
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        // SIMPLE: HARDCODED NAMES ARRAY
        const char* names[5] = {"Ossas", "Chubby", "Jewar", "Tiny", "Snoopy"};
        int enemyIndex = t - 1;

        printf("\nSparring %s! Let's go!\n", names[enemyIndex]);
        waitForEnter();

        // BATTLE
        sparringBattle(player, t);

        // NO NEED for updateSparringProgress here anymore!
    }
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

void createSparPlayer(Dog *orig, Dog *spar)
{
    // copy basic info (name, etc.)
    strcpy(spar->name, orig->name);

    spar->maxHP = 100;
    spar->hp = 100;

    spar->attack = 900;
    spar->defense = 100;
    spar->speed = 100;
    spar->accuracy = 100;
    spar->intelligence = 100;

    spar->isStunned = 0;
    spar->stunTurns = 0;
    spar->isBleeding = 0;
    spar->bleedTurns = 0;
    spar->isConfused = 0;
    spar->confuseTurns = 0;

    spar->skillCount = orig->skillCount;
    for (int i = 0; i < spar->skillCount; i++)
    {
        spar->skills[i] = orig->skills[i];
    }
}

void assignSkills(Dog *d, int type)
{

    if (type == 1)
    {
        createOssas(d);
        assignOssasSkills(d);
    }
    else if (type == 2)
    {
        createChubby(d);
        assignChubbySkills(d);
    }
    else if (type == 3)
    {
        createJeward(d);
        assignJewardSkills(d);
    }
    else if (type == 4)
    {
        createTiny(d);
        assignTinySkills(d);
    }
    else if (type == 5)
    {
        createSnoopy(d);
        assignSnoopySkills(d);
    }
}

// UPDATE DEBUFFS
void updateDebuffs(Dog *d)
{
    // DEBUFF TIMER
    if (d->accDebuffTurns > 0)
    {
        d->accDebuffTurns--;
        if (d->accDebuffTurns == 0)
        {
            d->accTemp = d->accuracy;
            printf("%s recovered from daze/stun!\n", d->name);
        }
    }

    // STUN TIMER
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

int sparringBattle(Dog *player, int type)
{
    Dog enemy;
    Dog sparPlayer;

    createSparPlayer(player, &sparPlayer); // FAIR STATS
    if (type == 1)
    {
        createOssas(&enemy);
        assignOssasSkills(&enemy);

        printf("Ossas appears! Aggressive attacker!\n");
    }
    else if (type == 2)
    {
        createChubby(&enemy);
        assignChubbySkills(&enemy);

        printf("Chubby appears! Defensive tank!\n");
    }
    else if (type == 3)
    {
        createJeward(&enemy);
        assignJewardSkills(&enemy);

        printf("Jeward appears! Precision striker!\n");
    }
    else if (type == 4)
    {
        createTiny(&enemy);
        assignTinySkills(&enemy);

        printf("Tiny appears! Smart strategist!\n");
    }
    else if (type == 5)
    {
        createSnoopy(&enemy);
        assignSnoopySkills(&enemy);

        printf("Snoopy appears! Speed demon!\n");
    }

    pauseAndClear();

    sparPlayer.hp = sparPlayer.maxHP;
    enemy.hp = enemy.maxHP;

    printf("\n SPARRING START: %s\n\n", enemy.name);
    pauseAndClear();

    while (sparPlayer.hp > 0 && enemy.hp > 0)
    {
        // UPDATE DEBUFFS FIRST
        if (enemy.accDebuffTurns > 0)
        {
            enemy.accDebuffTurns--;
            if (enemy.accDebuffTurns == 0)
            {
                enemy.accTemp = enemy.accuracy;
                printf("%s recovered accuracy!\n", enemy.name);
            }
        }
        if (sparPlayer.accDebuffTurns > 0)
        {
            sparPlayer.accDebuffTurns--;
            if (sparPlayer.accDebuffTurns == 0)
            {
                sparPlayer.accTemp = sparPlayer.accuracy;
                printf("You recovered accuracy!\n");
            }
        }

        updateCooldowns(&sparPlayer);
        updateCooldowns(&enemy);

        // STATUS WITH DEBUFFS
        printf("YOU: [%d/%d]", sparPlayer.hp, sparPlayer.maxHP);
        if (sparPlayer.accDebuffTurns > 0)
            printf(" (DAZED %d)", sparPlayer.accDebuffTurns);
        if (sparPlayer.isStunned && sparPlayer.stunTurns > 0)
            printf(" (STUN %d)", sparPlayer.stunTurns);
        printf("\n");

        printf("ENEMY: [%d/%d]", enemy.hp, enemy.maxHP);
        if (enemy.accDebuffTurns > 0)
            printf(" (DAZED %d)", enemy.accDebuffTurns);
        if (enemy.isStunned && enemy.stunTurns > 0)
            printf(" (STUN %d)", enemy.stunTurns);
        printf("\n\n");

        // CHECK PLAYER STUN
        if (sparPlayer.isStunned && sparPlayer.stunTurns > 0)
        {
            printf("YOU ARE STUNNED! Turn skipped!\n");
            sparPlayer.stunTurns--;
            if (sparPlayer.stunTurns == 0)
                sparPlayer.isStunned = 0;
        }
        else
        {
            printf("\nChoose Move:\n");
            printf("1. Bite\n");
            printf("2. Scratch\n");
            printf("3. Charge\n");
            printf("4. Hip Check\n");

            int choice;
            char moveInput[10];
            fgets(moveInput, sizeof(moveInput), stdin);
            choice = atoi(moveInput);

            Skill tempSkill;

            if (choice == 1)
            {
                strcpy(tempSkill.name, "Bite");
                tempSkill.type = SKILL_DAMAGE;
                tempSkill.power = 10;
                tempSkill.accuracy = 90;
            }
            else if (choice == 2)
            {
                strcpy(tempSkill.name, "Scratch");
                tempSkill.type = SKILL_DAMAGE;
                tempSkill.power = 8;
                tempSkill.accuracy = 95;
            }
            else if (choice == 3)
            {
                strcpy(tempSkill.name, "Charge");
                tempSkill.type = SKILL_DAMAGE;
                tempSkill.power = 12;
                tempSkill.accuracy = 80;
            }
            else if (choice == 4)
            {
                strcpy(tempSkill.name, "Hip Check");
                tempSkill.type = SKILL_DAMAGE;
                tempSkill.power = 9;
                tempSkill.accuracy = 85;
            }
            else
            {
                printf("Invalid move!\n");
                continue;
            }

            // ================= PLAYER TURN =================
            printf("\n--- PLAYER TURN ---\n");
            useSkill(&sparPlayer, &enemy, tempSkill);
        }

        if (enemy.hp <= 0)
            break;

        // ================= ENEMY TURN =================
        if (enemy.isStunned && enemy.stunTurns > 0)
        {
            printf("\n--- ENEMY TURN ---\n");
            printf("%s is STUNNED! Enemy turn skipped!\n", enemy.name);
            enemy.stunTurns--;
            if (enemy.stunTurns == 0)
                enemy.isStunned = 0;
        }
        else
        {
            int enemyMove = chooseEnemyMove(&enemy, &sparPlayer, type);
            printf("\n--- ENEMY TURN ---\n");
            useSkill(&enemy, &sparPlayer, enemy.skills[enemyMove]);
        }

        if (sparPlayer.hp <= 0)
            break;

        // PAUSE BETWEEN TURNS
        printf("\nPress Enter to continue...");
        getchar();
        system("cls");
    }

    // HP CHECK
    printf("\n=== BATTLE END ===\n");
    if (sparPlayer.hp > 0 && enemy.hp <= 0)
    {
        printf("YOU WIN SPARRING!\n");

        // SPARRING PROGRESS SYSTEM
        int enemyIndex = type - 1; // 1 = Ossas, 2 = Chubby, etc.
        updateSparringProgress(player, enemyIndex, 1); // WIN = +1 progress

        applySparReward(player, type);
        return 1; // WIN
    }
    else
    {
        printf("YOU LOST SPARRING...\n");
        int enemyIndex = type - 1;
        updateSparringProgress(player, enemyIndex, 0); // LOSE
        return 0;
    }
}
