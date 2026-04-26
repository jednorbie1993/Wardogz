/*

void battle(Dog *player)
{
    int invalidCount = 0;

    char input[10];
    Dog enemy;

    createEnemy(&enemy);

    int choice;
    int defending = 0;

    printf("\n=== BATTLE START ===\n");

    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");

        displayBattleStatus(*player, enemy);

        printf("\n--- YOUR TURN ---\n");

        if (player->fatigue <= 20)
        {
            printf("Your dog is exhausted!\n");
        }

        printf("1. Attack\n2. Defend\n3. Item (Heal)\n4. Surrender\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);

        // Enter lang
        if (input[0] == '\n')
        {
            printf("Please select a number.\n");
            waitForEnter();
            continue;
        }

        choice = atoi(input);

        // invalid range
        if (choice < 1 || choice > 4)
        {
            printf("Invalid choice! Select 1-4 only.\n");
            waitForEnter();
            continue;
        }

        // ================= PLAYER TURN =================
        if (choice == 1) // ================= ATTACK =================
        {
            system("cls");
            displayBattleStatus(*player, enemy);

            printf("\nChoose Attack:\n");
            printf("1. Bite\n2. Scratch\n3. Growl\n4. Lock Jaw\n");

            fgets(input, sizeof(input), stdin);

            // ❗ INVALID INPUT HANDLER
            if (input[0] == '\n' || !isdigit((unsigned char)input[0]))
            {
                invalidCount++;

                system("cls");
                displayBattleStatus(*player, enemy);

                if (invalidCount == 1)
                    printf("\nHey, focus on your battle!\n");
                else if (invalidCount == 2)
                    printf("\nHey! Hey! I told you to focus!\n");
                else
                    printf("\nCome on! Wake up! What's wrong with you?\n");

                waitForEnter();

                printf("\nEnemy takes advantage of your hesitation!\n");
                enemyQuickAttack(player, &enemy);

                waitForEnter();
                continue;
            }

            int move = atoi(input);

            if (move < 1 || move > 4)
            {
                invalidCount++;

                system("cls");
                displayBattleStatus(*player, enemy);

                printf("\nInvalid move!\n");
                waitForEnter();

                printf("\nEnemy takes advantage!\n");
                enemyAttack(player, &enemy, &defending);

                waitForEnter();
                continue;
            }

            // ✅ VALID MOVE
            invalidCount = 0;

            int penalty = getFatiguePenalty(player->fatigue);
            int effectiveAttack = player->attack - penalty;
            if (effectiveAttack < 1) effectiveAttack = 1;
            if (effectiveAttack > 999) effectiveAttack = 999;

            char *moveName = "Unknown";

            if (move == 1) moveName = "Bite";
            else if (move == 2) moveName = "Scratch";
            else if (move == 3) moveName = "Growl";
            else if (move == 4) moveName = "Lock Jaw";

            printf("\nYou used %s...\n", moveName);

            printf("Attacking");
            for (int i = 0; i < 3; i++)
            {
                printf(".");
                fflush(stdout);
                Sleep(200);
            }
            printf("\n");

            // 🎯 ACCURACY
            int dodgeChance = enemy.speed * 2;
            int finalAccuracy = player->accuracy - dodgeChance;

            if (finalAccuracy < 70) finalAccuracy = 70;
            if (finalAccuracy > 95) finalAccuracy = 95;

            int roll = rand() % 100;

            if (roll < finalAccuracy)
            {
                if (move == 3) // GROWL
                {
                    enemy.attack -= 2;
                    if (enemy.attack < 1) enemy.attack = 1;

                    printf("Enemy attack reduced!\n");
                }
                else
                {
                    int baseDamage = (effectiveAttack / 6) + 5;

                    // 🎲 randomness (balanced range)
                    baseDamage += (rand() % 11) - 5; // -5 to +5

                    // ⚔️ move bonus
                    if (move == 1) baseDamage += 5;  // Bite
                    else if (move == 2) baseDamage += 3;  // Scratch
                    else if (move == 4) baseDamage += 8;  // Lock Jaw

                    // 🛡️ defense reduction (light lang)
                    baseDamage -= enemy.defense / 20;

                    // 💥 critical (optional pero maganda feel)
                    if (isCritical(player->hp, player->maxHP))
                    {
                        baseDamage += 10;
                        printf("CRITICAL HIT!\n");
                    }

                    // 😴 fatigue
                    float fatigueFactor = 1.0 - (player->fatigue / 200.0);
                    if (fatigueFactor < 0.6) fatigueFactor = 0.6;

                    int finalDamage = (int)(baseDamage * fatigueFactor);

                    // minimum safety
                    if (finalDamage < 1)
                        finalDamage = 1;

                    enemy.hp -= finalDamage;
                    enemy.hp = clamp(enemy.hp);

                    printf("You dealt %d damage!\n", finalDamage);
                }
            }
            else
            {
                printf("You missed!\n");
            }

            waitForEnter();
        }
        else if (choice == 2) // ================= DEFEND =================
        {
            defending = 1;
            printf("You are defending!\n");
            waitForEnter();
        }
        else if (choice == 3) // ================= HEAL =================
        {
            player->hp += 20;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printf("You healed +20 HP!\n");
            waitForEnter();
        }
        else if (choice == 4) // ================= SURRENDER =================
        {
            printf("You surrendered...\n");
            pauseAndClear();
            break;
        }

        // ================= WIN CHECK =================
        if (enemy.hp <= 0)
        {
            system("cls");
            printf("\nYOU WIN!\n");
            applyBattleStatGain(player);
            pauseAndClear();
            break;
        }
        // ================= ENEMY TURN =================
        system("cls");
        displayBattleStatus(*player, enemy);

        enemyAttack(player, &enemy, &defending);
        printf("\nPress Enter to continue...");
        fflush(stdout);
        getchar();

        // ================= LOSE CHECK =================
        if (player->hp <= 0)
        {
            loseSequence(player, &enemy);
            pauseAndClear();
            break;
            }
        }
    }
        
    */
                