#include "sparring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void initSparringProgress(Dog *d) {
    for (int i = 0; i < 5; i++) {
        d->sparringProgress[i] = 0;
    }
}

void updateSparringProgress(Dog *d, int enemyIndex, int win) {
    system("cls");
    
    // 🔥 HARDCODE THE NAMES ARRAY HERE
    const char* sparringEnemies[5] = {"Ossas", "Chubby", "Jewar", "Tiny", "Snoopy"};
    
    printf("=== SPARRING RESULTS ===\n");
    
    if (win) {
        d->sparringProgress[enemyIndex]++;
        printf("✅ WIN! %s progress: %d/10", sparringEnemies[enemyIndex], d->sparringProgress[enemyIndex]);
        
        if (d->sparringProgress[enemyIndex] == 10) {
            printf(" → TECHNIQUE UNLOCKED!\n");
        } else {
            printf("\n");
        }
    } else {
        printf("❌ LOSS! %s progress: %d/10 (no gain)\n", sparringEnemies[enemyIndex], d->sparringProgress[enemyIndex]);
    }
    
    // Show all progress
    printf("\n--- ALL PROGRESS ---\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %d/10", sparringEnemies[i], d->sparringProgress[i]);
        if (d->sparringProgress[i] == 10) printf(" ✅");
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

void checkSparringUnlock(Dog *d) {
    // Check each sparring enemy
    if (d->sparringProgress[0] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Ossas Counter")) {
        strcpy(d->skills[d->skillCount].name, "Ossas Counter");
        d->skills[d->skillCount].power = 18;
        d->skills[d->skillCount].cost = 12;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printf("🎉 OSSAS DEFEATED 10/10! UNLOCKED: Ossas Counter!\n");
        d->skillCount++;
    }
    
    if (d->sparringProgress[1] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Chubby Bulldozer")) {
        strcpy(d->skills[d->skillCount].name, "Chubby Bulldozer");
        d->skills[d->skillCount].power = 22;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printf("🎉 CHUBBY DEFEATED 10/10! UNLOCKED: Chubby Bulldozer!\n");
        d->skillCount++;
    }
    
    if (d->sparringProgress[2] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Tiny Blitz")) {
        strcpy(d->skills[d->skillCount].name, "Tiny Blitz");
        d->skills[d->skillCount].power = 20;
        d->skills[d->skillCount].cost = 13;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printf("🎉 TINY DEFEATED 10/10! UNLOCKED: Tiny Blitz!\n");
        d->skillCount++;
    }
    
    if (d->sparringProgress[3] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Jeward Precision")) {
        strcpy(d->skills[d->skillCount].name, "Jeward Precision");
        d->skills[d->skillCount].power = 25;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printf("🎉 JEWARD DEFEATED 10/10! UNLOCKED: Jeward Precision!\n");
        d->skillCount++;
    }
    
    if (d->sparringProgress[4] == 10 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Snoop Phantom")) {
        strcpy(d->skills[d->skillCount].name, "Snoop Phantom");
        d->skills[d->skillCount].power = 28;
        d->skills[d->skillCount].cost = 16;
        d->skills[d->skillCount].type = SKILL_ATTACK;
        printf("🎉 SNOOP DEFEATED 10/10! UNLOCKED: Snoop Phantom! 🔥\n");
        d->skillCount++;
    }
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
        e->speed = 110 + rand() % 20;     // 🔥 FIXED: 110-130 (not 150-190!)
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
        player->sparringProgress[0] = 9;
        // 🔥 SHOW PROGRESS (KEEP THIS - perfect!)
        printf("1. Ossas     (%d/10)", player->sparringProgress[0]);
        if (player->sparringProgress[0] == 10) printf(" ✅");
        printf(" (Attack Training)\n");
        
        printf("2. Chubby    (%d/10)", player->sparringProgress[1]);
        if (player->sparringProgress[1] == 10) printf(" ✅");
        printf(" (Defense Training)\n");
        
        printf("3. Jewar     (%d/10)", player->sparringProgress[2]);
        if (player->sparringProgress[2] == 10) printf(" ✅");
        printf(" (Accuracy Training)\n");
        
        printf("4. Tiny      (%d/10)", player->sparringProgress[3]);
        if (player->sparringProgress[3] == 10) printf(" ✅");
        printf(" (Intelligence Training)\n");
        
        printf("5. Snoopy    (%d/10)", player->sparringProgress[4]);
        if (player->sparringProgress[4] == 10) printf(" ✅");
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

        // 🔥 SIMPLE: HARDCODED NAMES ARRAY (NO FUNCTION NEEDED)
        const char* names[5] = {"Ossas", "Chubby", "Jewar", "Tiny", "Snoopy"};
        int enemyIndex = t - 1;
        
        printf("\nSparring %s! Let's go!\n", names[enemyIndex]);
        waitForEnter();
        
        // 🥊 BATTLE (progress handled INSIDE sparringBattle now)
        sparringBattle(player, t);
        
        // NO NEED for updateSparringProgress here anymore!
    }
}

int useSkill(Dog *user, Dog *enemy, Skill skill)
{
    printf("DEBUG: %s using %s\n", user->name, skill.name);

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
            printf("💥 CRITICAL HIT! +%d\n", 5);
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
            printf("💥 %s STUNNED!\n", enemy->name);
        }
        if (strcmp(skill.name, "Charge") == 0)
        {
            int recoil = dmg / 5; user->hp -= recoil;
            printf("💥 %s recoil: %d\n", user->name, recoil);
        }

        // OSSAS
        if (strcmp(skill.name, "Wild Bite") == 0 && rand() % 100 < 35)
        { enemy->isBleeding = 1; enemy->bleedTurns = 3; printf("🩸 %s BLEEDING!\n", enemy->name); }
        if (strcmp(skill.name, "Rush Claw") == 0 && rand() % 100 < 25)
        { int extra = user->attack / 8; enemy->hp -= extra; printf("Extra slash! %d\n", extra); }
        if (strcmp(skill.name, "Headbutt") == 0 && rand() % 100 < 30)
        { enemy->isStunned = 1; enemy->stunTurns = 1; printf("😵 %s dazed!\n", enemy->name); }
        if (strcmp(skill.name, "Rage Leap") == 0)
        { int recoil = dmg / 4; user->hp -= recoil; printf("💥 %s recoil: %d\n", user->name, recoil); }

        // 🔥 CHUBBY NEW MOVES
        if (strcmp(skill.name, "Body Slam") == 0)
        {
            user->defense += 4;  // Self buff
            printf("💪 %s tougher!\n", user->name);
        }
        if (strcmp(skill.name, "Heavy Crush") == 0 && rand() % 100 < 30)
        {
            enemy->isStunned = 1; enemy->stunTurns = 1;
            printf("💥 %s CRUSHED!\n", enemy->name);
        }
        // JEWARD
        if (strcmp(skill.name, "Counter Snap") == 0 && rand() % 100 < 30)
        { int counter = user->attack / 7; enemy->hp -= counter; printf("🔄 Counter! %d damage\n", counter); }

        // 🔥 TINY NEW MOVES
        if (strcmp(skill.name, "Mind Bite") == 0 && rand() % 100 < 35)
        {
            enemy->isConfused = 1; enemy->confuseTurns = 2;
            printf("🌀 %s MIND BROKEN!\n", enemy->name);
        }
        if (strcmp(skill.name, "Brain Crush") == 0)
        {
            user->intelligence += 5;
            printf("🧠 %s smarter!\n", user->name);
        }
        // SNOOPY
        if (strcmp(skill.name, "Triple Bite") == 0)
        {
            int hits = 2 + (rand() % 2);
            for (int i = 0; i < hits; i++)
            { int extra = user->attack / 10; enemy->hp -= extra; printf("Extra bite #%d: %d\n", i+1, extra); }
        }
        if (strcmp(skill.name, "Wind Kick") == 0 && rand() % 100 < 30)
        { enemy->accuracy = (enemy->accuracy > 30) ? enemy->accuracy - 20 : 30; printf("🌪️ %s vision blurred!\n", enemy->name); }

        return 1;
    }

    // ================= OTHER SKILL TYPES =================
    else if (skill.type == SKILL_HEAL)
    {
        int heal = (user->intelligence / 5) + skill.power;
        user->hp = (user->hp + heal > user->maxHP) ? user->maxHP : user->hp + heal;
        printf("❤️ %s healed %d HP!\n", user->name, heal);
        return 1;
    }
    else if (skill.type == SKILL_BUFF)
    {
        user->attack += skill.power;
        printf("⚔️ %s attack UP!\n", user->name);
        return 1;
    }
    else if (skill.type == SKILL_DEBUFF)
    {
        enemy->attack -= skill.power;
        if (enemy->attack < 1) enemy->attack = 1;
        printf("⬇️ %s attack DOWN!\n", enemy->name);
        return 1;
    }

    return 1;
}

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

    // 🔥 ALL DOGS: HP-BASED BUFF PRIORITY
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
        
        // 🔥 OSSAS: Pure aggression, favors high damage
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

        // 🔥 CHUBBY: Damage buffs first
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

        // 🔥 TINY: Damage + mind control
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


        // 🔥 SNOOPY: Perfect rotation like you love!
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
    d->skillCount = 4;

    if (type == 1) // OSSAS
    {
        strcpy(d->skills[0].name, "Wild Bite");
        d->skills[0].type = SKILL_DAMAGE;
        d->skills[0].power = 12;
        d->skills[0].accuracy = 90;

        strcpy(d->skills[1].name, "Rush Claw");
        d->skills[1].type = SKILL_DAMAGE;
        d->skills[1].power = 11;
        d->skills[1].accuracy = 95;

        strcpy(d->skills[2].name, "Headbutt");
        d->skills[2].type = SKILL_DEBUFF;
        d->skills[2].power = 13;
        d->skills[2].accuracy = 80;

        strcpy(d->skills[3].name, "Rage Leap");
        d->skills[3].type = SKILL_DAMAGE;
        d->skills[3].power = 10;
        d->skills[3].accuracy = 65;
        d->skills[3].cooldown = 3;
        d->skills[3].cdLeft = 0;
    }

    // CHUBBY - TANK WITH DAMAGE BUFF
    else if (type == 2)
    {
        strcpy(d->skills[0].name, "Body Slam");        // 🔥 BUFF+DAMAGE
        d->skills[0].type = SKILL_DAMAGE;
        d->skills[0].power = 10;
        d->skills[0].accuracy = 95;

        strcpy(d->skills[1].name, "Slow Slam");
        d->skills[1].type = SKILL_DAMAGE;
        d->skills[1].power = 8;
        d->skills[1].accuracy = 95;

        strcpy(d->skills[2].name, "Guard Bash");
        d->skills[2].type = SKILL_DEBUFF;
        d->skills[2].power = 6;
        d->skills[2].accuracy = 85;

        strcpy(d->skills[3].name, "Heavy Crush");       // 🔥 BUFF+DAMAGE
        d->skills[3].type = SKILL_DAMAGE;
        d->skills[3].power = 12;
        d->skills[3].accuracy = 75;
        d->skills[3].cooldown = 2;
        d->skills[3].cdLeft = 0;
    }

    else if (type == 3) // JEWARD
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

    // TINY - SMART DAMAGE DEALER
    else if (type == 4)
    {
        strcpy(d->skills[0].name, "Mind Bite");         // 🔥 DAMAGE+DEBUFF
        d->skills[0].type = SKILL_DAMAGE;
        d->skills[0].power = 11;
        d->skills[0].accuracy = 90;

        strcpy(d->skills[1].name, "Quick Dodge Bite");
        d->skills[1].type = SKILL_DAMAGE;
        d->skills[1].power = 11;
        d->skills[1].accuracy = 95;

        strcpy(d->skills[2].name, "Confuse Peck");
        d->skills[2].type = SKILL_DEBUFF;
        d->skills[2].power = 8;
        d->skills[2].accuracy = 80;

        strcpy(d->skills[3].name, "Brain Crush");        // 🔥 DAMAGE+BUFF
        d->skills[3].type = SKILL_DAMAGE;
        d->skills[3].power = 13;
        d->skills[3].accuracy = 85;
        d->skills[3].cooldown = 2;
        d->skills[3].cdLeft = 0;
    }

    else if (type == 5) // SNOOPY - BALANCED ROTATION
    {
        // Speed Dash (CD: 2)
        strcpy(d->skills[0].name, "Speed Dash");
        d->skills[0].type = SKILL_DAMAGE; d->skills[0].power = 9; d->skills[0].accuracy = 100;
        d->skills[0].cooldown = 2; d->skills[0].cdLeft = 0;

        // Triple Bite (CD: 3) ← SPAM FIXED!
        strcpy(d->skills[1].name, "Triple Bite");
        d->skills[1].type = SKILL_DAMAGE; d->skills[1].power = 15; d->skills[1].accuracy = 75;
        d->skills[1].cooldown = 3; d->skills[1].cdLeft = 0;

        // Wind Kick
        strcpy(d->skills[2].name, "Wind Kick");
        d->skills[2].type = SKILL_DEBUFF; d->skills[2].power = 7; d->skills[2].accuracy = 90;

        // Flash Dodge
        strcpy(d->skills[3].name, "Flash Dodge");
        d->skills[3].type = SKILL_BUFF; d->skills[3].power = 8; d->skills[3].accuracy = 100;
    }
}

// 🔥 NEW FUNCTION - LAGYAN MO SA TOP NG FILE
void updateDebuffs(Dog *d)
{
    // DEBUFF TIMER
    if (d->accDebuffTurns > 0)
    {
        d->accDebuffTurns--;
        if (d->accDebuffTurns == 0)
        {
            d->accTemp = d->accuracy;
            printf("✅ %s recovered from daze/stun!\n", d->name);
        }
    }

    // STUN TIMER
    if (d->isStunned && d->stunTurns > 0)
    {
        d->stunTurns--;
        if (d->stunTurns == 0)
        {
            d->isStunned = 0;
            printf("✅ %s recovered from stun!\n", d->name);
        }
    }
}

int sparringBattle(Dog *player, int type)
{
    Dog enemy;
    Dog sparPlayer;

    createSparPlayer(player, &sparPlayer); // FAIR STATS
    createSparPartner(&enemy, type);
    assignSkills(&enemy, type);

    sparPlayer.hp = sparPlayer.maxHP;
    enemy.hp = enemy.maxHP;

    printf("\n SPARRING START: %s\n\n", enemy.name);
    pauseAndClear();

    while (sparPlayer.hp > 0 && enemy.hp > 0)
    {
        // 🔥 NEW: UPDATE DEBUFFS FIRST
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

        // 🔥 BETTER STATUS WITH DEBUFFS
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

        // 🔥 CHECK PLAYER STUN
        if (sparPlayer.isStunned && sparPlayer.stunTurns > 0)
        {
            printf("😵 YOU ARE STUNNED! Turn skipped!\n");
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
            printf("😵 %s is STUNNED! Enemy turn skipped!\n", enemy.name);
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

        // 🔥 FIX: CLEAR INPUT BUFFER
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nPress Enter to continue...");
        getchar();
        system("cls");
    }

    // 🔥 BETTER HP CHECK + INPUT CLEAN
    printf("\n=== BATTLE END ===\n");
    if (sparPlayer.hp > 0 && enemy.hp <= 0)
    {
        printf("🎉 YOU WIN SPARRING!\n");
        
        // 🥊 SPARRING PROGRESS SYSTEM
        int enemyIndex = type - 1; // 1→0(Ossas), 2→1(Chubby), etc.
        updateSparringProgress(player, enemyIndex, 1); // WIN = +1 progress
        
        applySparReward(player, type);
        waitForEnter();
        return 1; // WIN
    }
    else
    {
        printf("💥 YOU LOST SPARRING...\n");
        int enemyIndex = type - 1;
        updateSparringProgress(player, enemyIndex, 0); // LOSE
        waitForEnter();
        return 0;
    }
}