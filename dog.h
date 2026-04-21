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

} Dog;

// prototypes (WALANG struct Dog dito!)
void createDog(Dog *d);
void printDog(Dog d);
void battle(Dog *player);
void displayBattleStatus(Dog player, Dog enemy);
void waitForEnter();
void showHPBarPlayer(int hp, int maxHp);
void pauseAndClear();
void loseSequence(Dog *player, Dog *enemy);
void applyBattleStatGain(Dog *d);

int clamp(int value);

#endif