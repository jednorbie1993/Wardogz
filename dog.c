#include <stdio.h>
#include "dog.h"
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h> // para sa strcspn
#include <ctype.h>

int systemLog = 0;
int animationOn = 1; //  NEW (default ON)

int randRange(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

// growth curve (higher stat = lower gain)
int getGrowthGain(int stat)
{
    int base = randRange(3, 5); // 3–5

    if (stat > 200)
        base -= 1;
    if (stat > 400)
        base -= 1;
    if (stat > 700)
        base -= 1;

    if (base < 1)
        base = 1;

    return base;
}

int clamp(int value)
{
    if (value > MAX_STAT)
        return MAX_STAT;
    if (value < MIN_STAT)
        return MIN_STAT;
    return value;
}

int clampFatigue(int value)
{
    if (value > 100)
        return 100;
    if (value < 0)
        return 0;
    return value;
}

int getFatiguePenalty(int fatigue)
{
    if (fatigue >= 80)
        return 0;
    else if (fatigue >= 60)
        return 2;
    else if (fatigue >= 40)
        return 6;
    else if (fatigue >= 20)
        return 12;
    else if (fatigue > 0)
        return 24;
    else
        return 50;
}

int isCritical(int currentHP, int maxHP)
{
    int critChance;

    if (currentHP <= maxHP * 0.2)
    {
        // LOW HP → clutch mode
        critChance = (rand() % 16) + 20; // 20–35%
    }
    else
    {
        // NORMAL
        critChance = (rand() % 8) + 8; // 8–15%
    }

    int roll = rand() % 100;

    if (systemLog)
    {
        printf("[CRIT ] Roll: %-3d | Chance : %-3d\n", roll, critChance);
    }

    return roll < critChance;
}

void trainDog(Dog *d, int type)
{
    printf("\nTraining");

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(200);
    }
    printf("\n");

    // 🔻 FATIGUE CHECK (fail chance)
    if (d->fatigue < 20)
    {
        printf("Too exhausted... Training failed!\n");
        d->fatigue = clampFatigue(d->fatigue - 5);
        return;
    }

    int greatChance = rand() % 100;

    // ⭐ GREAT TRAINING
    if (greatChance < 10)
    {
        int bonus = 10;

        printf("GREAT TRAINING!\n");

        if (type == 1) // POWER
        {
            int g1 = getGrowthGain(d->maxHP);
            int g2 = getGrowthGain(d->attack);
            int g3 = getGrowthGain(d->defense);

            int t1 = g1 + bonus;
            int t2 = g2 + bonus;
            int t3 = g3 + bonus;

            d->maxHP = clamp(d->maxHP + t1);
            d->attack = clamp(d->attack + t2);
            d->defense = clamp(d->defense + t3);

            printf("HP +%d | ATK +%d | DEF +%d\n", t1, t2, t3);
        }
        else if (type == 2) // SPEED
        {
            int g1 = getGrowthGain(d->speed);
            int g2 = getGrowthGain(d->accuracy);
            int g3 = getGrowthGain(d->intelligence);

            int t1 = g1 + bonus;
            int t2 = g2 + bonus;
            int t3 = g3 + bonus;

            d->speed = clamp(d->speed + t1);
            d->accuracy = clamp(d->accuracy + t2);
            d->intelligence = clamp(d->intelligence + t3);

            printf("SPD +%d | ACC +%d | INT +%d\n", t1, t2, t3);
        }
        else // BALANCE
        {
            int g1 = getGrowthGain(d->maxHP);
            int g2 = getGrowthGain(d->attack);
            int g3 = getGrowthGain(d->defense);
            int g4 = getGrowthGain(d->speed);
            int g5 = getGrowthGain(d->intelligence);

            int t1 = g1 + bonus;
            int t2 = g2 + bonus;
            int t3 = g3 + bonus;
            int t4 = g4 + bonus;
            int t5 = g5 + bonus;

            d->maxHP = clamp(d->maxHP + t1);
            d->attack = clamp(d->attack + t2);
            d->defense = clamp(d->defense + t3);
            d->speed = clamp(d->speed + t4);
            d->intelligence = clamp(d->intelligence + t5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   t1, t2, t3, t4, t5);
        }

        d->hp = d->maxHP;
    }
    else
    {
        // ⭐ NORMAL TRAINING

        int g1, g2, g3;

        if (type == 1) // POWER
        {
            g1 = getGrowthGain(d->maxHP);
            g2 = getGrowthGain(d->attack);
            g3 = getGrowthGain(d->defense);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);

            printf("HP +%d | ATK +%d | DEF +%d\n", g1, g2, g3);
        }
        else if (type == 2) // SPEED
        {
            g1 = getGrowthGain(d->speed);
            g2 = getGrowthGain(d->accuracy);
            g3 = getGrowthGain(d->intelligence);

            d->speed = clamp(d->speed + g1);
            d->accuracy = clamp(d->accuracy + g2);
            d->intelligence = clamp(d->intelligence + g3);

            printf("SPD +%d | ACC +%d | INT +%d\n", g1, g2, g3);
        }
        else // BALANCE
        {
            g1 = getGrowthGain(d->maxHP);
            g2 = getGrowthGain(d->attack);
            g3 = getGrowthGain(d->defense);

            int g4 = getGrowthGain(d->speed);
            int g5 = getGrowthGain(d->intelligence);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);
            d->speed = clamp(d->speed + g4);
            d->intelligence = clamp(d->intelligence + g5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   g1, g2, g3, g4, g5);
        }

        d->hp = d->maxHP;
    }

    // 🔻 FATIGUE COST
    d->fatigue = clampFatigue(d->fatigue - randRange(8, 15));
}

void createDog(Dog *d)
{
    printf("Enter your dog's name: ");

    fgets(d->name, 50, stdin);
    d->name[strcspn(d->name, "\n")] = 0;

    d->hp = 100;
    d->maxHP = 100;
    d->attack = 920;
    d->speed = 100;

    d->defense = 115;
    d->accuracy = 918; // 80% hit chance
    d->intelligence = 920;

    d->fatigue = 10; // full energy

    d->skillCount = 2;

    strcpy(d->skills[0].name, "Bite");
    d->skills[0].power = 5;
    d->skills[0].cost = 5;

    strcpy(d->skills[1].name, "Scratch");
    d->skills[1].power = 3;
    d->skills[1].cost = 3;

    d->equipped[0] = 0;
    d->equipped[1] = 1;
    d->equipped[2] = -1;
    d->equipped[3] = -1;
}

void checkSkillUnlock(Dog *d)
{
    if (d->speed >= 100 && d->skillCount < MAX_SKILLS)
    {
        strcpy(d->skills[d->skillCount].name, "Quick Dash");
        d->skills[d->skillCount].power = 7;
        d->skills[d->skillCount].cost = 6;

        printf("NEW SKILL UNLOCKED: Quick Dash!\n");

        d->skillCount++;
    }

    if (d->attack >= 150 && d->skillCount < MAX_SKILLS)
    {
        strcpy(d->skills[d->skillCount].name, "Heavy Bite");
        d->skills[d->skillCount].power = 10;
        d->skills[d->skillCount].cost = 8;

        printf("NEW SKILL UNLOCKED: Heavy Bite!\n");

        d->skillCount++;
    }
}

void skillMenu(Dog *d)
{
    int choice;

    while (1)
    {
        system("cls");

        printf("===== SKILL MENU =====\n");
        printf("1. View All Skills\n");
        printf("2. Current Skills\n");
        printf("3. Equip Skills\n");
        printf("4. Back\n");
        printf("Choice: ");

        char input[20];
        int choice;

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (input[0] == '\0')
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        choice = atoi(input);

        // ================= VIEW ALL =================
        if (choice == 1)
        {
            system("cls");
            printf("--- ALL SKILLS ---\n");

            for (int i = 0; i < d->skillCount; i++)
            {
                printf("%d. %s (Power:%d Cost:%d)\n",
                       i + 1,
                       d->skills[i].name,
                       d->skills[i].power,
                       d->skills[i].cost);
            }

            waitForEnter();
        }

        // ================= CURRENT EQUIPPED =================
        else if (choice == 2)
        {
            system("cls");
            printf("--- CURRENT SKILLS ---\n");

            for (int i = 0; i < 4; i++)
            {
                if (d->equipped[i] != -1)
                {
                    int idx = d->equipped[i];
                    printf("Slot %d: %s (P:%d C:%d)\n",
                           i + 1,
                           d->skills[idx].name,
                           d->skills[idx].power,
                           d->skills[idx].cost);
                }
                else
                {
                    printf("Slot %d: [EMPTY]\n", i + 1);
                }
            }

            waitForEnter();
        }

        // ================= EQUIP =================
        else if (choice == 3)
        {
            int slot, pick;

            system("cls");

            // 👉 show current first (very important UX)
            printf("--- CURRENT SKILLS ---\n");
            for (int i = 0; i < 4; i++)
            {
                if (d->equipped[i] != -1)
                {
                    int idx = d->equipped[i];
                    printf("Slot %d: %s\n", i + 1, d->skills[idx].name);
                }
                else
                {
                    printf("Slot %d: [EMPTY]\n", i + 1);
                }
            }

            printf("\nChoose slot (1-4): ");
            scanf("%d", &slot);
            while (getchar() != '\n')
                ;

            if (slot < 1 || slot > 4)
            {
                printf("Invalid slot!\n");
                waitForEnter();
                continue;
            }

            system("cls");
            printf("\n--- AVAILABLE SKILLS ---\n");

            for (int i = 0; i < d->skillCount; i++)
            {
                printf("%d. %s (P:%d C:%d)\n",
                       i + 1,
                       d->skills[i].name,
                       d->skills[i].power,
                       d->skills[i].cost);
            }

            printf("Choice: ");
            scanf("%d", &pick);
            while (getchar() != '\n')
                ;

            if (pick < 1 || pick > d->skillCount)
            {
                printf("Invalid skill!\n");
                waitForEnter();
                continue;
            }

            d->equipped[slot - 1] = pick - 1;

            printf("Skill equipped to Slot %d!\n", slot);
            waitForEnter();
        }

        // ================= BACK =================
        else if (choice == 4)
        {
            break;
        }

        else
        {
            printf("Invalid choice!\n");
            waitForEnter();
        }
    }
}

void createEnemy(Dog *e)
{
    strcpy(e->name, "Wild Dog");

    e->hp = 100;
    e->maxHP = 100;
    e->attack = 80;
    e->defense = 65;

    e->speed = 90;    // dagdag mo rin para kumpleto
    e->accuracy = 95; // important sa hit system
    e->intelligence = 55;
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
    // reset base stats muna (important!)
    createEnemy(enemy);

    if (zoneIndex == 0)
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
    else if (zoneIndex == 1)
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
    else if (zoneIndex == 2)
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

    // sync HP
    enemy->hp = enemy->maxHP;
}

void applyStatGain(Dog *d, int atk, int hp, int def, int spd, int acc, int intel)
{
    d->attack = clamp(d->attack + atk);
    float ratio = (float)d->hp / d->maxHP;

    d->maxHP = clamp(d->maxHP + hp);
    d->hp = (int)(d->maxHP * ratio);
    d->defense = clamp(d->defense + def);
    d->speed = clamp(d->speed + spd);
    d->accuracy = clamp(d->accuracy + acc);
    d->intelligence = clamp(d->intelligence + intel);
}

void applyBattleStatGain(Dog *d)
{
    int chosen[6] = {0}; // track kung alin na napili
    int count = 0;

    while (count < 3)
    {
        int stat = rand() % 6;

        if (chosen[stat] == 0)
        {
            chosen[stat] = 1;
            count++;

            int gain = (rand() % 5) + 1; // +1 to +5

            switch (stat)
            {
            case 0:
                d->attack = clamp(d->attack + gain);
                printf("ATK +%d\n", gain);
                break;
            case 1:
            {
                float ratio = (float)d->hp / d->maxHP;

                d->maxHP = clamp(d->maxHP + gain);
                d->hp = (int)(d->maxHP * ratio);

                printf("HP +%d\n", gain);
                break;
            }
            case 2:
                d->defense = clamp(d->defense + gain);
                printf("DEF +%d\n", gain);
                break;
            case 3:
                d->speed = clamp(d->speed + gain);
                printf("SPD +%d\n", gain);
                break;
            case 4:
                d->accuracy = clamp(d->accuracy + gain);
                printf("ACC +%d\n", gain);
                break;
            case 5:
                d->intelligence = clamp(d->intelligence + gain);
                printf("INT +%d\n", gain);
                break;
            }
        }
    }
}

void printDog(Dog d)
{
    printf("--- Dog Info ---\n");
    printf("Name: %s\n", d.name);
    printf("HP: %d\n", d.hp);
    printf("Attack: %d\n", d.attack);
    printf("Speed: %d\n", d.speed);

    printf("Defense: %d\n", d.defense);
    printf("Accuracy: %d\n", d.accuracy);
    printf("Intelligence: %d\n", d.intelligence);

    printf("Fatigue: %d/100\n", d.fatigue); // ✅ DITO LANG
}

void typeText(char *text, int speed)
{
    if (!animationOn)
    {
        printf("%s", text);
        return;
    }

    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout); // 👉 para real-time output
        Sleep(speed);
    }
}

void showHPBarPlayer(int hp, int maxHp)
{
    static int lastHP = -1;

    if (lastHP == -1)
        lastHP = hp;

    // 👉 Clamp safety (para di sumobra)
    if (hp < 0)
        hp = 0;
    if (hp > maxHp)
        hp = maxHp;

    if (!animationOn)
    {
        int bars = (hp * 10) / maxHp;

        printf("\rPLAYER: [");

        for (int i = 0; i < 10; i++)
        {
            if (i < bars)
                printf("#");
            else
                printf("-");
        }

        // 👉 IMPORTANT: clear leftover characters
        printf("] (%d/%d)        ", hp, maxHp);

        fflush(stdout);

        printf("\n"); // final line break so di sumunod ang next print

        lastHP = hp;
        return;
    }

    // 👉 determine direction
    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        int bars = (current * 10) / maxHp;

        printf("\rPLAYER: [");
        for (int i = 0; i < 10; i++)
        {
            if (i < bars)
                printf("#");
            else
                printf("-");
        }
        printf("] (%d/%d)   ", current, maxHp);

        fflush(stdout); // 🔥 IMPORTANT para smooth overwrite
        Sleep(25);
    }

    // 👉 final state (para exact hp)
    int bars = (hp * 10) / maxHp;

    printf("\rPLAYER: [");
    for (int i = 0; i < 10; i++)
    {
        if (i < bars)
            printf("#");
        else
            printf("-");
    }
    printf("] (%d/%d)   \n", hp, maxHp);

    lastHP = hp;
}

void showHPBarEnemy(int hp, int maxHp)
{
    static int lastHP = -1;

    if (lastHP == -1)
        lastHP = hp;

    if (hp < 0)
        hp = 0;
    if (hp > maxHp)
        hp = maxHp;

    // 👉 OFF animation (clean single print)
    if (!animationOn || hp == 0)
    {
        int bars = (hp * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
        {
            if (i < bars)
                printf("#");
            else
                printf("-");
        }

        printf("] (%d/%d)        \n", hp, maxHp);

        lastHP = hp;
        return;
    }

    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        int bars = (current * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
        {
            if (i < bars)
                printf("#");
            else
                printf("-");
        }

        printf("] (%d/%d)   ", current, maxHp);

        fflush(stdout);
        Sleep(25);
    }

    // 👉 final exact state
    int bars = (hp * 10) / maxHp;

    printf("\rENEMY : [");
    for (int i = 0; i < 10; i++)
    {
        if (i < bars)
            printf("#");
        else
            printf("-");
    }

    printf("] (%d/%d)        \n", hp, maxHp);

    lastHP = hp;
}

void displayBattleStatus(Dog player, Dog enemy)
{
    printf("\n--- BATTLE STATUS ---\n");

    printf("PLAYER: ");
    showHPBarPlayer(player.hp, player.maxHP);

    printf("ENEMY : ");
    showHPBarEnemy(enemy.hp, enemy.maxHP);
}

void loseSequence(Dog *player, Dog *enemy)
{
    printf("\nYOU LOST...\n");
    Sleep(500);

    printf("Recovering");
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(150);
    }

    player->hp = player->maxHP;
    enemy->hp = enemy->maxHP;

    printf("\nYou are back to full HP!\n");
}

void waitForEnter()
{
    printf("\nPress Enter to continue...");
    while (getchar() != '\n')
        ; // wait until Enter lang
}

void pauseAndClear()
{
    printf("\nPress Enter to continue...");

    getchar(); // no loop, no fflush, simple lang

    system("cls");
}
int battle(Dog *player, int zoneIndex, int progress[])
{
    if (player->hp <= 0)
    {
        printf("You must rest before you battle again!\n");
        return -1;
    }

    int choice;
    int defending = 0;
    int move;

    Dog enemy;
    createEnemy(&enemy);
    setEnemyByZone(&enemy, zoneIndex, progress[zoneIndex]);

    system("cls");

    // intro text dito...

    waitForEnter();

    // 🔥 MAIN BATTLE LOOP
    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");
        displayBattleStatus(*player, enemy);

        printf("\n--- YOUR TURN ---\n");

        if (player->fatigue <= 20)
            printf("Your dog is exhausted!\n");

        printf("1. Attack\n2. Defend\n3. Heal\n4. Surrender\n");
        printf("Choice: ");

        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &choice) != 1 || choice < 1 || choice > 4)
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        // ================= ATTACK =================
        if (choice == 1)
        {
            system("cls");
            displayBattleStatus(*player, enemy);

            printf("Choose Skill:\n");

            for (int i = 0; i < 4; i++)
            {
                if (player->equipped[i] != -1)
                {
                    int idx = player->equipped[i];
                    printf("%d. %s (P:%d C:%d)\n",
                        i + 1,
                        player->skills[idx].name,
                        player->skills[idx].power,
                        player->skills[idx].cost);
                }
                else
                {
                    printf("%d. ---\n", i + 1);
                }
            }
            fgets(buffer, sizeof(buffer), stdin);

            if (sscanf(buffer, "%d", &move) != 1 || move < 1 || move > 4)
            {
                printf("Invalid skill!\n");
                waitForEnter();
                continue;
            }

            int skillIndex = player->equipped[move - 1];

            if (skillIndex == -1)
            {
                printf("No skill equipped!\n");
                waitForEnter();
                continue;
            }

            Skill s = player->skills[skillIndex];

            if (player->fatigue < s.cost)
            {
                printf("Not enough energy! Using weak attack instead...\n");

                int damage = player->attack / 2;
                enemy.hp -= damage;

                if (enemy.hp < 0)
                enemy.hp = 0;

                player->fatigue = 0;
                waitForEnter();
                
            }

            printf("You used %s!\n", s.name);

            // ===== DAMAGE =====
            int penalty = getFatiguePenalty(player->fatigue);

            float atkRatio = (float)(player->attack - penalty) / 999.0f;
            if (atkRatio < 0.1f)
                atkRatio = 0.1f;

            int damage = (int)(atkRatio * 80) + 20;
            damage += s.power;

            float defRatio = (float)enemy.defense / 999.0f;
            damage -= (int)(defRatio * 30);

            if (isCritical(player->hp, player->maxHP))
            {
                damage += 10;
                printf("CRITICAL HIT!\n");
            }

            damage += (rand() % 11) - 5;

            if (damage < 1)
                damage = 1;
            if (damage > 120)
                damage = 120;

            if ((rand() % 100) < player->accuracy)
            {
                enemy.hp -= damage;
                enemy.hp = clamp(enemy.hp);
                printf("You dealt %d damage!\n", damage);
            }
            else
            {
                printf("You missed!\n");
            }

            // ✔️ ONLY COST (no regen here)
            player->fatigue -= s.cost;
            player->fatigue = clampFatigue(player->fatigue);

            waitForEnter();
        }

        // ================= DEFEND =================
        else if (choice == 2)
        {
            defending = 1;
            printf("You are defending!\n");
            waitForEnter();
        }

        // ================= HEAL =================
        else if (choice == 3)
        {
            player->hp += 20;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printf("You healed +20 HP!\n");
            waitForEnter();
        }

        // ================= SURRENDER =================
        else if (choice == 4)
        {
            printf("You surrendered...\n");
            waitForEnter();
            return 2;
        }

        // ================= ENEMY TURN =================
        if (player->hp > 0 && enemy.hp > 0)
        {
            int result = enemyAttack(player, &enemy, &defending);

            if (result == 0)
                player->hp = 0;
            if (result == 1)
                enemy.hp = 0;
        }

        // 🔥 FATIGUE REGEN (DITO LANG)
        player->fatigue += 2;

        if (player->fatigue > player->maxFatigue)
            player->fatigue = player->maxFatigue;

        // ================= RESULT =================
        if (player->hp <= 0)
        {
            printf("\n=== YOU LOSE ===\n");
            waitForEnter();
            return 0;
        }

        if (enemy.hp <= 0)
        {
            printf("\nYOU WIN!\n");

            applyBattleStatGain(player);

            checkSkillUnlock(player);

            if (progress[zoneIndex] < 3)
                progress[zoneIndex]++;

            waitForEnter();
            return 1;
        }
    }
}