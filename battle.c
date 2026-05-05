
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dog.h"
#include "enemy.h"
#include "skill.h"
#include "sparring.h"
#include "dog_utils.h"

// extern globals from dog.c
extern int animationOn;


void showHPBarPlayer(int hp, int maxHp)
{
    static int lastHP = -1;

    // 🔥 RESET SIGNAL (for new battle)
    if (hp == -1)
    {
        lastHP = -1;
        return;
    }

    // 👉 Clamp safety
    if (hp < 0) hp = 0;
    if (hp > maxHp) hp = maxHp;

    // 👉 FIRST DRAW (instant, no animation)
    if (lastHP == -1)
    {
        lastHP = hp;

        int bars = (hp * 10) / maxHp;

        printf("\rPLAYER: [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)\n", hp, maxHp);
        return;
    }

    // 👉 NO ANIMATION MODE
    if (!animationOn)
    {
        int bars = (hp * 10) / maxHp;

        printf("\rPLAYER: [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)\n", hp, maxHp);

        lastHP = hp;
        return;
    }

    // 👉 ANIMATION MODE
    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        int bars = (current * 10) / maxHp;

        printf("\rPLAYER: [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)   ", current, maxHp);

        fflush(stdout);
        Sleep(20);
    }

    // 👉 FINAL EXACT VALUE
    int bars = (hp * 10) / maxHp;

    printf("\rPLAYER: [");
    for (int i = 0; i < 10; i++)
        printf(i < bars ? "#" : "-");

    printf("] (%d/%d)\n", hp, maxHp);

    lastHP = hp;
}

// ================= HP BAR ENEMY =================
void showHPBarEnemy(int hp, int maxHp)
{
    static int lastHP = -1;

    // 🔥 RESET SIGNAL (para sa new battle)
    if (hp == -1)
    {
        lastHP = -1;
        return;
    }

    // 👉 Clamp safety
    if (hp < 0) hp = 0;
    if (hp > maxHp) hp = maxHp;

    // 👉 FIRST DRAW (no animation, instant)
    if (lastHP == -1)
    {
        lastHP = hp;

        int bars = (hp * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)\n", hp, maxHp);
        return;
    }

    // 👉 NO ANIMATION MODE
    if (!animationOn)
    {
        int bars = (hp * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)\n", hp, maxHp);

        lastHP = hp;
        return;
    }

    // 👉 ANIMATION
    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        int bars = (current * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)   ", current, maxHp);

        fflush(stdout);
        Sleep(20);
    }

    // 👉 FINAL EXACT VALUE
    int bars = (hp * 10) / maxHp;

    printf("\rENEMY : [");
    for (int i = 0; i < 10; i++)
        printf(i < bars ? "#" : "-");

    printf("] (%d/%d)\n", hp, maxHp);

    lastHP = hp;
}

// ================= DISPLAY =================
void displayBattleStatus(Dog player, Dog enemy)
{
    printf("\n--- BATTLE STATUS ---\n");

    printf("PLAYER: ");
    showHPBarPlayer(player.hp, player.maxHP);

    printf("ENEMY : ");
    showHPBarEnemy(enemy.hp, enemy.maxHP);
}

// ================= LOSE =================

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

int battle(Dog *player, int zoneIndex, int progress[])
{
    if (player->hp <= 0)
    {
        printf("You must rest before you battle again!\n");
        return -1;
    }

    int choice, move, defending = 0;
    int baseDef = player->defense;
    int baseSpd = player->speed;

    Dog enemy;
    createEnemy(&enemy);

    enemy.bleedDamage = 0;
    enemy.accuracyModifier = 0;
    enemy.numSkills = 0;
    player->bleedDamage = 0;  // Player safety too
    player->accuracyModifier = 0;
    
    // 🔥 ENEMY SETUP - CLEAN & SIMPLE
    int i = progress[zoneIndex];
    if (zoneIndex >= 3) { // Stage 2: Wild Territory
        if (zoneIndex == 5) if (i >= 4) i = 3;
        else if (i >= 3) i = 2;
        
        setEnemyByZone(&enemy, zoneIndex, i);
        setEnemySkillsWild(&enemy, zoneIndex, i);
        
        system("cls");
        printf("\n🐺 [WILD TERRITORY ENEMY]\n");
        printf("Enemy: %s\n", enemy.name);
        printf("Skills: Pack Attack | Ambush | Howl/Feral\n");
        waitForEnter();
    } 
    else { // Stage 1: Urban Strays
        if (i >= 3) i = 2;
        setEnemyByZone(&enemy, zoneIndex, i);
        enemy.numSkills = 0; // No wild skills
    }

    system("cls");
    preBattleScene();

    // 🔥 RESET HP BAR STATES (DITO MO ILALAGAY)
    showHPBarPlayer(-1, 1);
    showHPBarEnemy(-1, 1);

    // 🔥 MAIN BATTLE LOOP
    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");
        displayBattleStatus(*player, enemy);

        printf("\n--- YOUR TURN ---\n");
        if (player->fatigue <= 20) printf("⚠️  Exhausted!\n");

        printf("1. Attack  2. Defend  3. Heal  4. Surrender\n");
        printf("Choice: ");

        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &choice) != 1 || choice < 1 || choice > 4)
        {
            printf("Invalid!\n"); waitForEnter(); continue;
        }

        // 🔥 PLAYER ACTIONS
        if (choice == 1) // Attack
        {
            system("cls"); 
            displayBattleStatus(*player, enemy);

            printf("Skills:\n");

            for (int j = 0; j < 4; j++)
            {
                if (player->equipped[j] != -1)
                {
                    int idx = player->equipped[j];
                    printf("%d. %s (P:%d C:%d)\n", j+1, 
                        player->skills[idx].name, 
                        player->skills[idx].power, 
                        player->skills[idx].cost);
                }
                else printf("%d. ---\n", j+1);
            }

            fgets(buffer, sizeof(buffer), stdin);
            if (sscanf(buffer, "%d", &move) != 1 || move < 1 || move > 4)
            { 
                printf("Invalid skill!\n"); 
                waitForEnter(); 
                continue; 
            }

            int skillIdx = player->equipped[move - 1];
            if (skillIdx == -1) 
            { 
                printf("No skill!\n"); 
                waitForEnter(); 
                continue; 
            }

            Skill s = player->skills[skillIdx];

            if (player->fatigue < s.cost)
            {
                printf("Low energy! Weak attack...\n");
                useSkill(player, &enemy, s);
                player->fatigue = 0;
            }
            else
            {
                useSkill(player, &enemy, s);
                player->fatigue -= s.cost;
                player->fatigue = clampFatigue(player->fatigue, player->maxFatigue);
            }

            waitForEnter();
        } // ✅ IMPORTANT: ito yung kulang mo

        else if (choice == 2) // Defend
        {
            defending = 1;
            printf("Defending!\n"); 
            waitForEnter();
        }
        else if (choice == 3) // Heal
        {
            player->hp += 20;
            if (player->hp > player->maxHP) 
                player->hp = player->maxHP;

            printf("Healed +20 HP!\n"); 
            waitForEnter();
        }
        else if (choice == 4) // Surrender
        {
            printf("Surrendered...\n"); 
            waitForEnter();

            player->defense = baseDef; 
            player->speed = baseSpd;
            return 2;
        }

        // 🔥 ENEMY TURN
        if (player->hp > 0 && enemy.hp > 0)
        {
            int result = enemyAttack(player, &enemy, &defending);
            if (result == 0) player->hp = 0;
            if (result == 1) enemy.hp = 0;
        }
        // 👉 RESET DEFENSE AFTER TURN
        defending = 0;
        // 🔥 FATIGUE REGEN
        player->fatigue += 2;
        if (player->fatigue > player->maxFatigue) player->fatigue = player->maxFatigue;

        // 🔥 WIN/LOSE CHECK
        if (player->hp <= 0)
        {
            printf("\n💀 YOU LOSE 💀\n");
            player->fatigue = clampFatigue(player->fatigue + 20, player->maxFatigue);
            player->defense = baseDef; player->speed = baseSpd;
            waitForEnter(); return 0;
        }

        if (enemy.hp <= 0)
        {
            printf("\n🎉 YOU WIN! 🎉\n");
            applyBattleStatGain(player);
            checkSkillUnlock(player);
            
            /// 🔥 FIXED PROGRESS SYSTEM
            if (zoneIndex == 5) { // Mountain Den max 4
                if (progress[zoneIndex] < 4) progress[zoneIndex]++;
            } else { // All others max 3
                if (progress[zoneIndex] < 3) progress[zoneIndex]++;
            }

            player->fatigue = clampFatigue(player->fatigue + 20, player->maxFatigue);
            player->defense = baseDef; player->speed = baseSpd;
            waitForEnter(); return 1;
        }
    }

    player->defense = baseDef; player->speed = baseSpd;
    return -1;
}