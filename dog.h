#ifndef DOG_H
#define DOG_H

#define MAX_STAT 999
#define MIN_STAT 0

extern int systemLog;
extern int animationOn;

typedef struct {
    char name[50];
    int hp;
    int maxHP;
    int attack;
    int speed;

    int defense;
    int accuracy;
    int intelligence;

    int fatigue;

} Dog;

// ================= CORE =================
void createDog(Dog *d);
void printDog(Dog d);
void battle(Dog *player);
void displayBattleStatus(Dog player, Dog enemy);
void waitForEnter();
void pauseAndClear();
void loseSequence(Dog *player, Dog *enemy);

// ================= PLAYER SYSTEM (🔥 ADD THIS) =================
void playerTurn(Dog *player, Dog *enemy, int *defending);
void playerAttack(Dog *player, Dog *enemy);
void healPlayer(Dog *player);

// ================= UI =================
void showHPBarPlayer(int hp, int maxHp);

// ================= SYSTEM =================
void applyBattleStatGain(Dog *d);
void trainDog(Dog *d, int type);

// ================= ENEMY =================
void createEnemy(Dog *e);
void enemyAttack(Dog *player, Dog *enemy, int *defending);
void enemyQuickAttack(Dog *player, Dog *enemy);
void setEnemyByZone(Dog *enemy, int zoneIndex, int i);

// ================= UTIL =================
int clamp(int value);
int clampFatigue(int value);
int getFatiguePenalty(int fatigue);
int isCritical(int hp, int maxHP);   // 🔥 ADD THIS (ginagamit mo na)

#endif