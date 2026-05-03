#include "dog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int enemyAI(Dog *enemy, Dog *player, int type)
{
    int move = rand() % 4;

    if (type == 1) // Ossas aggressive
        return (enemy->attack / 10) + rand() % 6;

    if (type == 2) // Chubby tank
        return (enemy->attack / 14) + rand() % 3;

    if (type == 5) // Snoopy speed
        return (enemy->attack / 11) + rand() % 5;

    // default
    return (enemy->attack / 12) + rand() % 4;
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

void sparringDog(Dog *player, int type)
{
    Dog spar;

    // create sparring partner
    createSparPartner(&spar, type);

    printf("\n Sparring Match Started!\n");
    printf("Opponent: %s\n", spar.name);

    int playerHP = player->maxHP;
    int sparHP = spar.maxHP;

    while (playerHP > 0 && sparHP > 0)
    {
        // PLAYER TURN
        int dmg = (player->attack / 10) + rand() % 3;
        sparHP -= dmg;

        printf("You dealt %d damage!\n", dmg);

        if (sparHP <= 0)
            break;

        // SPAR TURN
        int enemyDmg = (spar.attack / 10) + rand() % 3;
        playerHP -= enemyDmg;

        printf("%s dealt %d damage!\n", spar.name, enemyDmg);
    }

    // RESULT
    if (playerHP > 0)
    {
        printf("\nYou won sparring!\n");

        // small stat gain ONLY
        if (type == 1)
            player->attack += rand() % 3 + 1;
        if (type == 2)
            player->defense += rand() % 3 + 1;
        if (type == 3)
            player->accuracy += rand() % 3 + 1;
        if (type == 4)
            player->intelligence += rand() % 3 + 1;
        if (type == 5)
            player->speed += rand() % 3 + 1;
    }
    else
    {
        printf("\nYou lost sparring...\n");
    }

    waitForEnter();
}
void createSparPartner(Dog *e, int type)
{
    // reset basic stats first
    memset(e, 0, sizeof(Dog));

    e->maxHP = 80 + rand() % 30;
    e->hp = e->maxHP;

    e->fatigue = 100;
    e->maxFatigue = 100;

    e->isConfused = 0;
    e->confuseTurns = 0;
    e->isBleeding = 0;
    e->bleedTurns = 0;

    e->skillCount = 0;

    // ================= OSSAS (ATTACK) =================
    if (type == 1)
    {
        strcpy(e->name, "Ossas");

        e->attack = 120 + rand() % 30;
        e->defense = 60 + rand() % 20;
        e->speed = 70 + rand() % 20;
        e->accuracy = 80 + rand() % 10;
        e->intelligence = 50;

        printf("Ossas appears! Aggressive attacker!\n");
    }

    // ================= CHUBBY (DEFENSE) =================
    else if (type == 2)
    {
        strcpy(e->name, "Chubby");

        e->attack = 60 + rand() % 20;
        e->defense = 130 + rand() % 40;
        e->speed = 50 + rand() % 15;
        e->accuracy = 70 + rand() % 10;
        e->intelligence = 60;

        printf("Chubby appears! Defensive tank!\n");
    }

    // ================= JWEAR (ACCURACY) =================
    else if (type == 3)
    {
        strcpy(e->name, "Jeward");

        e->attack = 80 + rand() % 20;
        e->defense = 70 + rand() % 20;
        e->speed = 80 + rand() % 20;
        e->accuracy = 140 + rand() % 30;
        e->intelligence = 80;

        printf("Jeward appears! Precision striker!\n");
    }

    // ================= TINY (INTELLIGENCE) =================
    else if (type == 4)
    {
        strcpy(e->name, "Tiny");

        e->attack = 70 + rand() % 20;
        e->defense = 60 + rand() % 20;
        e->speed = 60 + rand() % 20;
        e->accuracy = 80 + rand() % 15;
        e->intelligence = 150 + rand() % 40;

        printf("Tiny appears! Smart strategist!\n");
    }

    // ================= SNOOPY (SPEED) =================
    else if (type == 5)
    {
        strcpy(e->name, "Snoopy");

        e->attack = 70 + rand() % 20;
        e->defense = 60 + rand() % 20;
        e->speed = 150 + rand() % 40;
        e->accuracy = 85 + rand() % 15;
        e->intelligence = 70;

        printf("Snoopy appears! Speed demon!\n");
    }

    // fallback safety
    else
    {
        strcpy(e->name, "Unknown");
    }
    pauseAndClear();
}
void sparringMenu(Dog *player)
{
    int t;

    while (1)
    {
        system("cls");

        printf("==== SPARRING TRAINING ====\n");
        printf("1. Ossas (Attack Training)\n");
        printf("2. Chubby (Defense Training)\n");
        printf("3. Jewar (Accuracy Training)\n");
        printf("4. Tiny (Intelligence Training)\n");
        printf("5. Snoopy (Speed Training)\n");
        printf("6. Return\n");
        printf("Choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        // ================= EMPTY INPUT =================
        if (input[0] == '\0')
        {
            printf("Invalid input! Please enter a number.\n");
            waitForEnter();
            continue;
        }

        // ================= NOT A NUMBER =================
        if (!isdigit(input[0]))
        {
            printf("Invalid input! Numbers only.\n");
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

        // 🥊 START SPARRING BATTLE
        sparringBattle(player, t);
    }
}

int useSkill(Dog *user, Dog *enemy, Skill skill)
{
    int roll = rand() % 100;

    if (roll > skill.accuracy)
    {
        printf("%s missed!\n", skill.name);
        return 0;
    }

    int dmg = 0;

    // ================= DAMAGE =================
    if (skill.type == SKILL_DAMAGE)
    {
        dmg = skill.power + (rand() % 6);

        if (rand() % 100 < 10)
        {
            dmg += 5;
            printf("Critical hit!\n");
        }

        if (dmg > 20)
            dmg = 20;

        enemy->hp -= dmg;

        printf("%s used %s and dealt %d damage!\n",
               user->name, skill.name, dmg);

        // ===== BASIC PLAYER SKILLS =====
        if (strcmp(skill.name, "Hip Check") == 0)
        {
            if (rand() % 100 < 40)
            {
                enemy->isStunned = 1;
                enemy->stunTurns = 2;
                printf("%s is STUNNED!\n", enemy->name);
            }
        }

        if (strcmp(skill.name, "Charge") == 0)
        {
            int recoil = dmg / 5;
            user->hp -= recoil;
            printf("%s took %d recoil damage!\n", user->name, recoil);
        }

        // ================= OSSAS =================
        if (strcmp(skill.name, "Wild Bite") == 0)
        {
            if (rand() % 100 < 35)
            {
                enemy->isBleeding = 1;
                enemy->bleedTurns = 3;
                printf("%s is BLEEDING!\n", enemy->name);
            }
        }

        if (strcmp(skill.name, "Rush Claw") == 0)
        {
            if (rand() % 100 < 25)
            {
                int extra = user->attack / 8;
                enemy->hp -= extra;
                printf("Extra slash! %d damage!\n", extra);
            }
        }

        if (strcmp(skill.name, "Headbutt") == 0)
        {
            if (rand() % 100 < 30)
            {
                enemy->isStunned = 1;
                enemy->stunTurns = 1;
                printf("%s is dazed!\n", enemy->name);
            }
        }

        if (strcmp(skill.name, "Rage Leap") == 0)
        {
            int recoil = dmg / 4;
            user->hp -= recoil;
            printf("%s took %d recoil!\n", user->name, recoil);
        }

        // ================= JEWAR =================
        if (strcmp(skill.name, "Counter Snap") == 0)
        {
            if (rand() % 100 < 30)
            {
                int counter = user->attack / 7;
                enemy->hp -= counter;
                printf("Counter hit! %d damage!\n", counter);
            }
        }

        // ================= TINY =================
        if (strcmp(skill.name, "Quick Dodge Bite") == 0)
        {
            user->speed += 3;
            printf("%s became quicker!\n", user->name);
        }

        // ================= SNOOPY =================
        if (strcmp(skill.name, "Triple Bite") == 0)
        {
            int hits = 2 + rand() % 2;
            for (int i = 0; i < hits; i++)
            {
                int extra = user->attack / 10;
                enemy->hp -= extra;
                printf("Extra bite! %d damage!\n", extra);
            }
        }
    }

    // ================= HEAL =================
    else if (skill.type == SKILL_HEAL)
    {
        int heal = (user->intelligence / 5) + skill.power;

        user->hp += heal;
        if (user->hp > user->maxHP)
            user->hp = user->maxHP;

        printf("%s healed %d HP!\n", user->name, heal);
    }

    // ================= BUFF =================
    else if (skill.type == SKILL_BUFF)
    {
        user->attack += skill.power;
        printf("%s gained attack boost!\n", user->name);

        if (strcmp(skill.name, "Body Block") == 0)
        {
            user->defense += 3;
            printf("Defense increased!\n");
        }

        if (strcmp(skill.name, "Flash Dodge") == 0)
        {
            user->accuracy += 10;
            printf("Harder to hit!\n");
        }
    }

    // ================= DEBUFF =================
    else if (skill.type == SKILL_DEBUFF)
    {
        enemy->attack -= skill.power;
        if (enemy->attack < 1)
            enemy->attack = 1;

        printf("%s attack reduced!\n", enemy->name);

        if (strcmp(skill.name, "Eye Strike") == 0)
        {
            enemy->accuracy -= 10;
            if (enemy->accuracy < 50)
                enemy->accuracy = 50;

            printf("%s accuracy dropped!\n", enemy->name);
        }

        if (strcmp(skill.name, "Mind Feint") == 0)
        {
            if (rand() % 100 < 40)
            {
                enemy->isConfused = 1;
                enemy->confuseTurns = 2;
                printf("%s is CONFUSED!\n", enemy->name);
            }
        }
    }

    return 1;
}  

void assignSkills(Dog *d, int type)
{
    d->skillCount = 4;

    if (type == 1) // OSSAS
    {

        strcpy(d->skills[0].name, "Wild Bite");
        d->skills[0].type = SKILL_DAMAGE;
        d->skills[0].power = 12;
        d->skills[0].accuracy = 90;

        strcpy(d->skills[1].name, "Rush Claw");
        d->skills[1].type = SKILL_DAMAGE;
        d->skills[1].power = 10;
        d->skills[1].accuracy = 95;

        strcpy(d->skills[2].name, "Headbutt");
        d->skills[2].type = SKILL_DEBUFF;
        d->skills[2].power = 5;
        d->skills[2].accuracy = 80;

        strcpy(d->skills[3].name, "Rage Leap");
        d->skills[3].type = SKILL_DAMAGE;
        d->skills[3].power = 18;
        d->skills[3].accuracy = 65;
    }

    else if (type == 2) // CHUBBY
    {

        strcpy(d->skills[0].name, "Body Block");
        d->skills[0].type = SKILL_BUFF;
        d->skills[0].power = 5;
        d->skills[0].accuracy = 100;

        strcpy(d->skills[1].name, "Slow Slam");
        d->skills[1].type = SKILL_DAMAGE;
        d->skills[1].power = 8;
        d->skills[1].accuracy = 95;

        strcpy(d->skills[2].name, "Guard Bash");
        d->skills[2].type = SKILL_DEBUFF;
        d->skills[2].power = 6;
        d->skills[2].accuracy = 85;

        strcpy(d->skills[3].name, "Heavy Sit");
        d->skills[3].type = SKILL_BUFF;
        d->skills[3].power = 8;
        d->skills[3].accuracy = 100;
    }

    else if (type == 3) // JEWAR
    {

        strcpy(d->skills[0].name, "Precision Bite");
        d->skills[0].type = SKILL_DAMAGE;
        d->skills[0].power = 14;
        d->skills[0].accuracy = 100;

        strcpy(d->skills[1].name, "Eye Strike");
        d->skills[1].type = SKILL_DEBUFF;
        d->skills[1].power = 7;
        d->skills[1].accuracy = 90;

        strcpy(d->skills[2].name, "Counter Snap");
        d->skills[2].type = SKILL_DAMAGE;
        d->skills[2].power = 10;
        d->skills[2].accuracy = 95;

        strcpy(d->skills[3].name, "Focus Jab");
        d->skills[3].type = SKILL_BUFF;
        d->skills[3].power = 5;
        d->skills[3].accuracy = 100;
    }

    else if (type == 4) // TINY
    {

        strcpy(d->skills[0].name, "Mind Feint");
        d->skills[0].type = SKILL_DEBUFF;
        d->skills[0].power = 6;
        d->skills[0].accuracy = 90;

        strcpy(d->skills[1].name, "Quick Dodge Bite");
        d->skills[1].type = SKILL_DAMAGE;
        d->skills[1].power = 11;
        d->skills[1].accuracy = 95;

        strcpy(d->skills[2].name, "Confuse Peck");
        d->skills[2].type = SKILL_DEBUFF;
        d->skills[2].power = 8;
        d->skills[2].accuracy = 80;

        strcpy(d->skills[3].name, "Smart Counter");
        d->skills[3].type = SKILL_BUFF;
        d->skills[3].power = 6;
        d->skills[3].accuracy = 100;
    }

    else if (type == 5) // SNOOPY
    {

        strcpy(d->skills[0].name, "Speed Dash");
        d->skills[0].type = SKILL_DAMAGE;
        d->skills[0].power = 9;
        d->skills[0].accuracy = 100;

        strcpy(d->skills[1].name, "Triple Bite");
        d->skills[1].type = SKILL_DAMAGE;
        d->skills[1].power = 15;
        d->skills[1].accuracy = 75;

        strcpy(d->skills[2].name, "Wind Kick");
        d->skills[2].type = SKILL_DEBUFF;
        d->skills[2].power = 7;
        d->skills[2].accuracy = 90;

        strcpy(d->skills[3].name, "Flash Dodge");
        d->skills[3].type = SKILL_BUFF;
        d->skills[3].power = 8;
        d->skills[3].accuracy = 100;
    }
}

int sparringBattle(Dog *player, int type)
{
    Dog enemy;
    createSparPartner(&enemy, type);

    assignSkills(&enemy, type);

    player->hp = player->maxHP;
    enemy.hp = enemy.maxHP;

    printf("\n SPARRING START: %s\n\n", enemy.name);
    pauseAndClear();

    while (player->hp > 0 && enemy.hp > 0)
    {
        printf("\nYOU:    [%d/%d]\n", player->hp, player->maxHP);
        printf("ENEMY:  [%d/%d]\n\n", enemy.hp, enemy.maxHP);

        printf("\nChoose Move:\n");
        printf("1. Bite\n");
        printf("2. Scratch\n");
        printf("3. Charge\n");
        printf("4. Hip Check\n");

        int choice;
        scanf("%d", &choice);
        getchar();

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

        useSkill(player, &enemy, tempSkill);

        if (enemy.hp <= 0)
            break;

        int enemyMove = rand() % enemy.skillCount;
        useSkill(&enemy, player, enemy.skills[enemyMove]);

        if (player->hp <= 0)
            break;

        printf("\nPress Enter to continue...");
        getchar();
        system("cls");
    }

    // ✅ RESULT CHECK (NASA LABAS NA)
    if (player->hp > 0)
    {
        printf("\n YOU WIN SPARRING!\n");
        applySparReward(player, type);
        return 1;
    }
    else
    {
        printf("\n YOU LOST SPARRING...\n");
        return 0;
    }
}